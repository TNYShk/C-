 /**********************************************
 * Parser - Header File                       *
 * Approver: 	                              *
 * Written: 2022-1-20                         *
 *                                            *
 * Reviewer:  	                              *
 **********************************************/
#ifndef __PARS_H__
#define __PARS_H__



typedef enum pars_status
{
	INVALID_READ,
	READ_NUMBER,
	READ_OPERATOR
	
}pars_status_p;



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
char *ParseChar2(const char *str, char *ch);
int ParseChar1(const char *str, char **str_after_parse, char *result);


#endif 
/* __PARS_H__ */
