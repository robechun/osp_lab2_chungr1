all: new_cat new_echo new_tail new_wc

new_cat: new_cat.c
	gcc -Wall -o new_cat new_cat.c 
new_echo: new_echo.c
	gcc -Wall -o new_echo new_echo.c 
new_tail: new_tail.c
	gcc -Wall -o new_tail new_tail.c 
new_wc: new_wc.c
	gcc -Wall -o new_wc new_wc.c 

clean:
	rm -f new_cat new_echo new_tail new_wc
