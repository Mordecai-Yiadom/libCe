CC = gcc
CCFLAGS := -Wall -Wextra -Werror

SRC_DIR := src/
BIN_DIR := bin/
TARGET_DIR := target/
LIB_DIR := lib/
INCLUDE_DIR := include

INCLUDE := -I$(INCLUDE_DIR) -Isrc


SRCS := $(wildcard $(SRC_DIR)*.c) $(wildcard $(SRC_DIR)**/*.c) $(wildcard $(SRC_DIR)**/**/*.c) $(wildcard $(SRC_DIR)**/**/**/*.c) $(wildcard $(SRC_DIR)**/**/**/**/*.c) $(wildcard $(SRC_DIR)**/**/**/**/**/*.c)

ifeq ($(CC), g++)
	SRCS += $(wildcard $(SRC_DIR)*.cpp) $(wildcard $(SRC_DIR)**/*.cpp) $(wildcard $(SRC_DIR)**/**/*.cpp) $(wildcard $(SRC_DIR)**/**/**/*.cpp) $(wildcard $(SRC_DIR)**/**/**/**/*.cpp)
endif

OBJS := $(SRCS:%=%.o)
OBJS := $(subst $(SRC_DIR), $(BIN_DIR), $(OBJS))
LIBS := $(wildcard $(LIB_DIR)*.a) $(wildcard $(LIB_DIR)*.o) $(wildcard $(LIB_DIR)*.dll) $(wildcard $(LIB_DIR)*.so)


TARGET := main
TARGET_ARGS := 


#Query OS type
ifeq ($(OS), Windows_NT)
	TARGET := $(TARGET).exe
else
	TARGET_DIR := $(TARGET_DIR)
	RM ?= rm -rf
endif

TARGET := $(TARGET_DIR)$(TARGET)

.PHONY: all
all: $(TARGET)

.PHONY: run
run: all
	./$(TARGET) $(TARGET_ARGS)

.PHONY: clean clear
clean:
	cd $(BIN_DIR) && $(RM) *.o && cd ..
	cd $(TARGET_DIR) && $(RM) $(notdir $(TARGET)) && cd ..
clear:
	make clean

.PHONY: init
init:
	mkdir "$(SRC_DIR)"
	mkdir "$(BIN_DIR)"
	mkdir "$(TARGET_DIR)"
	mkdir "$(LIB_DIR)"
	mkdir $(INCLUDE_DIR)

#Make Main.exe
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(foreach obj, $(OBJS), $(BIN_DIR)$(notdir $(obj))) $(LIBS)

$(BIN_DIR)%.o: $(SRC_DIR)%
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $(BIN_DIR)$(notdir $@)
