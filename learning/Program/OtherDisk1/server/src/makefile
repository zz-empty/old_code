SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=server
CC:=gcc
CFLAGS:=-g -Wall -I ../include/
$(ELF):$(OBJS)
		gcc $^ -o $@ -lpthread -lmysqlclient -lcrypt

clean:
		rm -rf $(OBJS)  $(ELF)

