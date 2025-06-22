CC:=gcc
srcs:=$(wildcard *.c)
objs:=$(patsubst %.c, %.o, $(srcs))
ELF:=client
#CFLAGS:= -g -Wall

$(ELF):$(objs)
	gcc -o $@ $^ -lpthread

.PHONY:clean 
clean:
	$(RM) $(ELF)
