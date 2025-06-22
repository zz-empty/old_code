CC:=gcc
srcs:=$(wildcard *.c)
out:=$(patsubst %.c,%,$(srcs))
#objs:=$(patsubst %.c, %.o, $(srcs))

$(out) : $(srcs)
	$(CC) $^ -o $@

.PHONY:clean rebuild
clean:
	$(RM) $(objs) $(out)
rebuild: clean $(out)
