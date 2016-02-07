program_SRC_DIR := src
program_BUILD_DIR := build
program_TARGET := bin/app
program_INCLUDE_DIRS :=
program_LIBRARY_DIRS :=
program_LIBRARIES := SDL2 SDL2_image SDL2_ttf SDL2_mixer
program_SRCS = $(wildcard $(program_SRC_DIR)/*.cc)
program_OBJS = $(patsubst $(program_SRC_DIR)/%,$(program_BUILD_DIR)/%,$(program_SRCS:.cc=.o))
CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS := -g -Wall -Wextra -pedantic -O0 -std=c++14
CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDLIBS += $(foreach library,$(program_LIBRARIES),-l$(library))

all: $(program_TARGET)

$(program_TARGET): $(program_OBJS)
	$(CXX) -g $(LDFLAGS) -o $(program_TARGET) $(program_OBJS) $(LDLIBS)

$(program_BUILD_DIR)/%.o: $(program_SRC_DIR)/%.cc
	$(CC) $(CPPFLAGS) -c -o $@ $<


clean:
	$(RM) $(program_OBJS)

dist-clean: clean