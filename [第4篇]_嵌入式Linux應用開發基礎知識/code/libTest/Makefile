CC=/usr/local/linaro-aarch64-2020.09-gcc10.2-linux5.4/bin/aarch64-linux-gnu-gcc
INSTALL_PATH :=/mnt/disk2/SF/test

LD_FLAGS := -ladd
C_FLAGS := -g
C_INC := -I.          

LD_PATH := -L.

MAIN_OBJS := $(INSTALL_PATH)/main.o
TARGET := $(INSTALL_PATH)/main

all:$(MAIN_OBJS)
	gcc ${C_INC} ${C_FLAGS} -o $(TARGET) main.c ${LD_PATH} ${LD_FLAGS}

.PHONY:clean
clean:
	-rm $(INSTALL_PATH)/$(TARGET)