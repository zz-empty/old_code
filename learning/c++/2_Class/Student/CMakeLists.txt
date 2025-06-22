# Cmake最低版本，可以不写
CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

# 指定项目的名字, 项目版本，当前项目的描述，网站地址，这个项目是用什么语言写的
project(SIS)

# 增加std=c++11
set(CMAKE_CXX_STANDARD 11)

# 指定生成程序的家目录
set(HOME /home/zkong/myexec/)

# 搜索源文件
# aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)

# 指定头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 指定可执行程序输出的路径
# set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin)

# 生成一个可执行程序
# add_executable(stu ${SRC})

# 指定库文件生成的路径
set(LIBRARY_OUTPUT_PATH ${HOME}lib)

# 指定最终生成的库的名字
# add_library(stu SHARED ${SRC})
add_library(stu STATIC ${SRC})
