/**
 * @file NumOperation.h
 * @author naudhizb (naudhizb@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef NUMOPERATION_H_
#define NUMOPERATION_H_

#if __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define NumOp_Saturate(data, min, max) ((data) < (min))?(min):((max) < (data))?(max):(data)

float NumOp_GetPercentage(float data, float min, float max);
float NumOp_MapValue(float input, float input_min, float input_max, float map_min, float map_max);
int32_t NumOp_GetDiff(uint32_t curr, uint32_t prev, uint32_t max);


#if __cplusplus
}
#endif

#endif /* NUMOPERATION_H_ */
