OBJS:=$(wildcard ../src/*.c)
server:$(OBJS)
	gcc $^ -o $@ -I ../include -lpthread -lcrypt
clean:
	rm server
