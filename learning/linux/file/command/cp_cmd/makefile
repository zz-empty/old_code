CC:=gcc
srcs:=$(wildcard *.c)
out:=main
$(out):$(srcs)
	$(CC) $^ -o $@
.PHONY:clean rebuild
clean:
	$(RM) $(out)
rebuild:clean all
