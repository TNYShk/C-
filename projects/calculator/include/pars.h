 /**********************************************
 * Parser - Header File                       *
 * Approver: AMIT                             *
 * Written: 2022-1-20                         *
 *                                            *
 * Reviewer: AMIT                             *
 **********************************************/
#ifndef __PARS_H__
#define __PARS_H__

/* DESCRIPTION: 
 * 
 *
 * PARAMS: 
 *  
 * 
 * RETURN:
 * TRUE(1) if empty, otherwise Zero
 *
 *  Complexity: O(1) time, O(1) space.
 */
int ParseNum(const char *str, char **next_ptr, double *result);


/* DESCRIPTION: 
 * 
 *
 * PARAMS: 
 *  
 * 
 * RETURN:
 * TRUE(1) if empty, otherwise Zero
 *
 *  Complexity: O(1) time, O(1) space.
 */
char ParseChar(const char *str, char **str_after_parse);


#endif 
/* __PARS_H__ */
