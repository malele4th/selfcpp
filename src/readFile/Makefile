
CXX = g++
AR = ar

CMD = -O3 -g
CFLAGS = $(CMD) -Wall -fno-strict-aliasing -fPIC -Wfloat-equal -Wshadow -DNDEBUG -w

TOP_DIR = ".."

INCLUDE = -I $(TOP_DIR)/splitString
LIB = -L $(TOP_DIR)/splitString -lsplitstring

TARGET = libreadfile.a
OBJ = readFile.o
SRC = readFile.cpp

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(AR) -r $@ $^

#$(OBJ) : $(SRC)
#	$(CXX) $(CFLAGS) -c $^ -o $@

$(OBJ) : $(SRC)
	$(CXX) $(CFLAGS) -c $^ -o $@ $(INCLUDE) $(LIB) 

#$(OBJ) : $(SRC)
#	$(CXX) $(CFLAGS) $^ -o $@ $(INCLUDE) $(LIB)

clean:
	rm -f *.o *.a


