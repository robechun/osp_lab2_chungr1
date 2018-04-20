# osp_lab2_chungr1

## Introducting UNIX utilties! new_cat, new_echo, new_tail, and new_wc

Before starting, go ahead and issue the commands:
<br>
```make clean``` <br>
```make all``` <br>
<br>

This will create executables to run -- so that you can run them.

### new_cat
- Prints the contents of FILE -- or if none specified -- mirrors what is typed in STDIN <br>
- Use via ```./new_cat <FILE>``` <br>

### new_echo
- Prints out the arguments after call <br>
- Use via ```./new_echo <arg> <arg> ... <arg>``` <br>
- Any number of arguments >= 1 <br>
- Prints out exactly as typed <br>


### new_tail
- Prints last N number of lines of FILE or STDIN <br>
- N is default 5 <br>


- Use via ```./new_tail <FILE> <-n N>```
- The <FILE> and <-n N> are interchangeable (order does not matter)<br>
- However, "N" must follow "-n"<br>
- If no argument is passed, then read from STDIN <br>
  
### new_wc
- Prints out word count and (line count or character count) <br>
- Use via ```./new_wc <-l | -c> <FILE>``` <br>
- If <FILE> not specified, read from STDIN <br>
- only one flag allowed <br>
- Order of flag and FILE does not matter <br>
- "-l" gives # of lines, "-c" gives # of characters <br>
  
  
<br>
<br>
**Exit out of STDIN by using Ctrl-D**
