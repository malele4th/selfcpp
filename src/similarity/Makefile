
CXX = g++
AR = ar

CMD = -O3 -g
CFLAGS = $(CMD) -Wall -fno-strict-aliasing -fPIC -Wfloat-equal -Wshadow -DNDEBUG -w

TARGET = libsimilarity.a
OBJ = similarity.o
SRC = similarity.cpp

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(AR) -r $@ $^

$(OBJ) : $(SRC)
	$(CXX) $(CFLAGS) -c $^ -o $@

clean:
	rm -f *.o *.a

