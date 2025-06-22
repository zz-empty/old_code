#定义源目录和目标文件的路径
SRC_DIR = ../src
OBJS_DIR = ../obj

#使用wildcard函数获取src目录下的所有.c文件
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
#使用patsubst函数，将.c文件替换成.o文件
OBJS_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRC_FILES))

#目标文件
OUT = client
#编译器
CC = gcc

#从目标文件生成可执行文件
#链接阶段，需要加上动态库
$(OUT):$(OBJS_FILES)
	$(CC) $^ -o $@

#从源文件生成目标文件
#编译阶段，需要加上头文件
$(OBJS_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) -c $^ -o $@ -I ../include

#伪目标--->一定会执行，因为没有依赖文件
.PHONY:clean rebuild
clean:
	$(RM) $(OBJS_DIR)/* $(OUT)
rebuild: clean $(OUT)
