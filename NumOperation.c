/**
 * @file NumOperation.c
 * @author naudhizb (naudhizb@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "NumOperation.h"
#include <stdio.h>

float NumOp_GetPercentage(float data, float min, float max){
    float percent = (data - min) / (max - min);
    return percent;
}
float NumOp_MapValue(float input, float input_min, float input_max, float map_min, float map_max){
    float percent = NumOp_GetPercentage(input, input_min, input_max);
    float diff = (map_max - map_min);
    float output = (diff * percent) + map_min;
    return output;
}


/**
 * @brief Get Rotary Encoder differential.
 *        curr, prev value must be in [0 max)
 * 
 * @param curr current encoder counter
 * @param prev previous encodeer counter
 * @param max  maximum encoder counter value curr < max, prev < max. up to 0x3FFFFFFF
 * @return int32_t differential value [-max/2 max/2]
 */
int32_t NumOp_GetDiff(uint32_t curr, uint32_t prev, uint32_t max){
    int32_t diff = 0;
    const uint32_t half_max = max/2;
    diff = (int32_t)curr - (int32_t)prev;
    diff += half_max;
    if(diff < 0){        
        diff += max;        
    }
    diff %= max;
    diff -= half_max;
    return diff;
}

int32_t NumOp_GetDiffTest(uint32_t curr, uint32_t prev, uint32_t max, int32_t diff_expect){
    int32_t diff_result;
    
    printf("Start:[%d]:[%d] @ %lu %lu max: 0x%08X\n", diff_expect, diff_result, curr, prev, max);
    for(uint32_t i = 0; i < max; i++){
        uint32_t curr_i = (curr+i)%(max);
        uint32_t prev_i = (prev+i)%(max);
        diff_result = NumOp_GetDiff(curr_i, prev_i, max);
        if(diff_result != diff_expect){
            printf("diff:(index:%lu)[%d]:[%d] @ curr_i:%lu prev_i:%lu\n\n", i, diff_expect, diff_result, curr_i, prev_i);
            return 1;
        } else {
            // printf("diff:(index:%lu)[%d]:[%d] @ curr_i:%lu prev_i:%lu\n", i, diff_expect, diff_result, curr_i, prev_i);
        }
        if(i == max){
            printf("Max reached. break\n");
            break;
        }
    }
    printf("final:[%d]:[%d] @ %lu %lu max: 0x%08X\n\n", diff_expect, diff_result, curr, prev, max);
    return 0;
}
int main(void){
    printf("Hello world!\n");
    const uint32_t max = UINT32_MAX & (~0xC0000000);
    // NumOp_GetDiff(0, 255, max); // error case 
    NumOp_GetDiffTest(1, 0, max, 1);    
    NumOp_GetDiffTest(0, 1, max, -1);
    NumOp_GetDiffTest(2, 0, max, 2);
    NumOp_GetDiffTest(0, 2, max, -2);
    NumOp_GetDiffTest(0, max/2-1, max, -(max/2-1));
    NumOp_GetDiffTest((max/2-1), 0, max, (max/2-1));
    return 0;
}
