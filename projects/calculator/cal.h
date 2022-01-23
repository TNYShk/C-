/**********************************************
 * Calculator                                 *
 * Developer:                                 *
 * Written:                                   *
 * Reviewer:                                  *
 *                                            *
 **********************************************/

#ifndef __CALC_H__
#define __CALC_H__

typedef enum
{
    CALC_SUCCESS = 0,
    CALC_MATH_ERROR = 1,
    CALC_ALLOC_ERROR = 2,
    CALC_SYNTAX_ERROR = 3
} calc_status_t;


calc_status_t Calculator(const char *string, double *result);

#endif /* __CALC_H__ */