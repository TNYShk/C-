/**********************************************
 * Knight's Tour - H File                      *
 * Developer: Ziv Luger                        *
 * Written:   14/02/2022                       *
 *                                             *
 * Reviewer:  Gal Tsaig                        *
 **********************************************/
#ifndef __KNIGHTS_TOUR_H__
#define __KNIGHTS_TOUR_H__

/*index 0 = (upper left corner), index 63 = (bottom right corner)*/
void KnightsTour(unsigned char pos, unsigned char *tour);

void Warnsdorff(unsigned char pos, unsigned char *tour);

#endif /* __KNIGHTS_TOUR_H__ */
