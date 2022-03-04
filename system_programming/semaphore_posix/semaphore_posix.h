#ifndef __SEMAPHORE_POSIX_H__
#define __SEMAPHORE_POSIX_H__




int PosixSemManipulation(const char **cmd);

/*
	argv: "name size"

	decrement: "name D number (optional)u"  
	increment: "name I number (optional)u"
	view: name V
	exit: name X 
	remove : name R
 */

#endif /* __SEMAPHORE_POSIX_H__ */
