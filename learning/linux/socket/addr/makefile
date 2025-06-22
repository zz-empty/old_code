CC:=gcc
srcs:=$(wildcard *.c) 
exe:=$(patsubst %.c, %, $(srcs)) 
all:$(exe)
%:%.c
	$(CC) $^ -o $@ 
.PHONY:clean rebuild
clean:
	$(CC) $(exe)
rebuild:clean all
