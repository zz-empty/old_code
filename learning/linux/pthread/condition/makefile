CC:=gcc
srcs:=$(wildcard *.c)
exe:=$(patsubst %.c, %, $(srcs))
all:$(exe)
%:%.c
	$(CC) $^ -o $@ -lpthread
.PHONY:clean rebuild
clean:
	$(RM) $(exe)
rebuild:clean all
