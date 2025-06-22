CC:=gcc
srcs:=$(wildcard *.c)
out:=$(patsubst %.c,%,$(srcs))
all:$(out)
%:%.c
	$(CC) $^ -o $@
.PHONY:clean rebuild
clean:
	$(RM) $(out)
rebuild:clean all
