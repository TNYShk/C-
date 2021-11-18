#ifndef __LISTEN2KEYS_H__
#define __LISTEN2KEYS_H__

/*******************************************************************************
 WORKSHEET 4: FUNCTIONS - EXERCISE SOLUTION
 DATE: 15/11/2021
 LAB: OL114-115
 VERSION: 1.0
*******************************************************************************/

/* DESCRIPTION:
 * Prints "A-pressed" or "T-pressed" when one these characters is pressed.
 * The function terminates when ESC is pressed.
 *
 * PARAMS:
 * None
 * 
 * RETURN:
 * None
 */
void iAT();
void ifAT();
void PrintAT();

/* DESCRIPTION:
 * Prints "A-pressed" or "T-pressed" when one these characters is pressed.
 * The function terminates when ESC is pressed.
 *
 * PARAMS: 
 * char to evaluate
 * 
 * RETURN:
 * None
 */
void PrintChar(char);

/* DESCRIPTION:
 * Prints "A-pressed" or "T-pressed" when one these characters is pressed.
 * The function terminates when ESC is pressed.
 *
 * PARAMS: uses PrintChar func
 * None
 * 
 * RETURN:
 * None
 */
void ActionFunc();



#endif
