all: logo logo2 draw_chars calc_sqrt

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

draw_chars: draw_chars.c
	gcc $(FLAGS) $@.c -o $@ $(DIRS) $(LIBS) 

calc_sqrt: calc_sqrt.c
	gcc $(FLAGS) $@.c -o $@ $(DIRS) $(LIBS) 
