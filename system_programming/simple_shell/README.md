# system_programming- simple shell WS 
## *very simple shell*

 ***

a very simple shell app, that also saves history as a separate file, 2 modes available: system() and fork(). to exit type "exit". to switch between modes need to restart app.
upon running the app must provide a name for the history file. please notice upon exit from app the history file is deleted.

 ```
# functions
* system() 
* fork()

 ```
## Usage & Installation 

``` c compiler
compile and run  > ./a.out *history_file_name*
## must provide argv[1] otherwise program quits

write/choose desired mode: eixther fork or system 

# enter commands in fork mode
> "fork"

# enter commands in system mode
> "system"

# exit the program and remove history file
> "exit"

``` 
