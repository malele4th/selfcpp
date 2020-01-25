
CXX = g++
AR = ar

CMD = -O3 -g
CFLAGS = $(CMD) -Wall -fno-strict-aliasing -fPIC -Wfloat-equal -Wshadow -DNDEBUG -w

TARGET = libsplitstring.a
OBJ = splitString.o
SRC = splitString.cpp

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(AR) -r $@ $^

$(OBJ) : $(SRC)
	$(CXX) $(CFLAGS) -c $^ -o $@

clean:
	rm -f *.o *.a

