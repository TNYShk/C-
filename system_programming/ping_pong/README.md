# system_programming- Ping Pong WS 
## *Ping Pong*

 ***
the folder contains 3 separate programs, divided into folders
1. ex1 - clean ping pong, pingpong, pingpong1 -  3 version of excerise 1 using only fork().
2. ex2 - ping pong using fork() *knife* & exec()
4. ex4 - 2 separate files ping ponging each other

 ```
# functions
*  
* fork(), exec|l|v|p(), sigaction(), sigemptyset(),sigaddset(), sigsuspend()

 ```
## Usage & Installation 

```
# ex1. 3 versions for basic ping pong!
>cleanpingpong.c -  mentor's version
> pingpong.c - as requested using SUGUSR1,SUGUSR2
> pingpong1.c - using sig_() funcs, and SIGUSR1

# ex2. in c compiler
first compile "gd ex2_exec.c -o *name*" then compile "gd ex2.c". then run both ./a.out name

# ex4. in c compiler
first compile "gd pong.c -o *pong*" then run "./*name* &" to get PID.  \n
next compile "gd ping.c". finaly, run ./a.out + PID



``` 
