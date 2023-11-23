CC := g++

TARGET := test

SRC := tests/test.cpp

OBJ := $(SRC:.cpp=.o)

COMMONFLAGS := -Wall -Werror -Wextra
CPPFLAGS := $(COMMONFLAGS) -std=c++17

ifeq ($(DEBUG),1)
	CFLAGS += -O0
else
	CFLAGS += -O3 -DNDEBUG
endif

$(TARGET): $(OBJ)
	$(CC) $^ -o $@

%.o: %.cpp Makefile
	$(CC) $(CPPFLAGS) -I src -c $< -o $@

clean:
	rm -f **/*.o main test
