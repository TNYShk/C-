#ifndef __SEMAPHORE_SYS_V_H__
#define __SEMAPHORE_SYS_V_H__

int SysVSemManipulation(const char **cmd);

/*
	argv: "name size"

	decrement: "name D number (optional)u"  
	increment: "name I number (optional)u"
	view: name V
	exit: name X 
	remove : name R
 */


#endif /* __SEMAPHORE_SYS_V_H__ */
