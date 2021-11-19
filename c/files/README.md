# Files ws 
## *aka Death of me*

 ***

a very basic Word Processor program, to be used in terminal command line. built using various ffunctions from I/O stream FILEs

 ```
# functions
* fopen  
* fclose & fflush
* fgets & fgetc
* fputs &fputc
* fread & fwrite
* fseek & ftell
 ```
## Usage & Installation 

``` c compiler
compile and run  > ./a.out *file_name*
## must provide argv[1] otherwise program quits

open text file, enter new lines to append. 

# prints line count
> "-count"

# removes file
> "-remove"

# exit the program
> "-exit"

# add line to the beginning of the file, 
> '<' line  
*this creates a new copy of the file*
``` 