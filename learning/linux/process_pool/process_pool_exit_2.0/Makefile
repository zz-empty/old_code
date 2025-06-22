CC:=gcc
srcs:=$(wildcard src/*.c)
objs:=$(patsubst %.c, %.o, $(srcs))
ELF:=process_pool
#CFLAGS:= -g -Wall

$(ELF):$(objs)
	gcc -o $@ $^ -lpthread

.PHONY:clean 
clean:
	$(RM) $(ELF) $(objs)
