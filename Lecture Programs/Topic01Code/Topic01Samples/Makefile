all: hello logo tables

LIBS=-lzdk -lncurses -lm -lrt
DIRS=-I../ZDK -L../ZDK
FLAGS=-std=gnu99 -D_XOPEN_SOURCE=500 -Wall -Werror

clean:
	rm hello.exe logo.exe tables.exe

rebuild: clean all

hello: hello.c
	gcc $(FLAGS) $@.c -o $@ $(DIRS) $(LIBS) 

logo: logo.c
	gcc $(FLAGS) $@.c -o $@ $(DIRS) $(LIBS) 

tables: tables.c
	gcc $(FLAGS) $@.c -o $@ $(DIRS) $(LIBS) 
