all: logo logo2 array_ex_01 logo3

LIBS=-lzdk -lncurses -lm
DIRS=-I../ZDK -L../ZDK
FLAGS=-std=gnu99 -D_XOPEN_SOURCE=500 -Wall -Werror

clean:
	rm hello.exe logo.exe tables.exe

rebuild: clean all

logo: logo.c
	gcc $(FLAGS) $@.c -o $@ $(DIRS) $(LIBS) 

logo2: logo2.c
	gcc $(FLAGS) $@.c -o $@ $(DIRS) $(LIBS) 

array_ex_01: array_ex_01.c
	gcc $(FLAGS) $@.c -o $@ $(DIRS) $(LIBS) 

logo3: logo3.c
	gcc $(FLAGS) $@.c -o $@ $(DIRS) $(LIBS) 
