CC:=gcc
srcs:=stat.c
exe:=$(patsubst %.c,%,$(srcs))
all:$(exe)
%:%.c
	$(CC) $^ -o $@ 
.PHONY:clean rebuild
clean:
	$(RM) $(exe)
rebuild:clean all
