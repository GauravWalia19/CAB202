# Makefile for the ZDK
#
# $Revision:Wed Mar  2 15:21:10 EAST 2016$

TARGET=libzdk.a
FLAGS=-Wall -Werror -std=gnu99

all: $(TARGET)

clean:
	rm $(TARGET)
	rm *.o

rebuild: clean all

$(TARGET): *.c *.h
	gcc -c *.c $(FLAGS)
	ar r $(TARGET) *.o
