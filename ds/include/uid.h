#ifndef __UID_H__
#define __UID_H__

#include <sys/types.h> /* size_t, time_t, pid_t */

typedef struct
{
	size_t u_id;
	time_t t_id;
	pid_t p_id;
} ilrd_uid_t;

extern const ilrd_uid_t UIDBadUID;

/*
 * DESCRIPTION: 
 * Creates UID
 * 
 * PARAMS: None
 * 
 * RETURN: UID Struct
 * Complexity: O(1) time, O(1) space. */
ilrd_uid_t UIDCreate(void);

/*
 * DESCRIPTION: 
 * Compares two UID's
 * 
 * PARAMS: UID's to compare
 * 
 * RETURN: 1 if TRUE, 0 of not
 * Complexity: O(1) time, O(1) space. */
int UIDIsSame(const ilrd_uid_t uid1, const ilrd_uid_t uid2);

#endif /* __UID_H__ */
