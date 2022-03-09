# PROJECT 
## *WATCHDOG Library*

 ***
the folder contains Watchdod program, designed to safe guard user's running process.
1. watchdog_start.c should call user's program
2. watchdog.c - library
3. kickdog.c - protect the protector 

 ```
# functions
*  
* WDStart- Begin Barking Process [keep user's program alive]
* WDStop - Protection no longer needed

 ```
## Usage & Installation 

```
# user's program MUST be in current folder
> add and run user's program from watchdog_test.c
> use makefile to compile and link accordingly
> in terminal run 'make test'
> in terminal run ./watchdog_test

> to test functionality, in terminal enter: kill pid/ppid
> ppid/pid is printed when program starts

``` 
