/*************************************
 * Calculator Header file            *
 * Developer: Tanya                  *
 * Jan 24, 2022                      *
 * Reviewer: AMIT                    *
 *************************************/

#ifndef __CALC_H__
#define __CALC_H__



typedef enum
{
    CALC_SUCCESS = 0,
    CALC_MATH_ERROR = 1,
    CALC_ALLOC_ERROR = 2,
    CALC_SYNTAX_ERROR = 3
} calc_status_t;

/* DESCRIPTION: 
 * Basic calculator,
 * !! please note, only 6 digits post decimal point are allowed !!
 *
 * PARAMS: 
 * Mathematical string to calculate
 * double result
 *  
 * 
 * RETURN:
 * calc_status_t - status of the calculation, as shown in enum above
 *
 *  Complexity: O(1) time, O(n) space.
 */
calc_status_t Calculator(const char *string, double *result);

#endif /* __CALC_H__ */
