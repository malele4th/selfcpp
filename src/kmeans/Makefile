
CXX = g++
AR = ar
CMD = -O3 -g
CFLAGS = $(CMD) -Wall -fno-strict-aliasing -fPIC -Wfloat-equal -Wshadow -DNDEBUG -w

TOP_DIR = ..
QMODULE = ../../qmodule

INCLUDE = -I $(TOP_DIR)/readFile -I $(TOP_DIR)/splitString -I $(QMODULE)/boost/include -I $(TOP_DIR)/scaler
LIB = -L $(TOP_DIR)/readFile -lreadfile -L $(TOP_DIR)/splitString -lsplitstring -L $(QMODULE)/boost/lib -lboost_system -lboost_thread -L $(TOP_DIR)/scaler -lscaler

TARGET = libkmeans.a
OBJ = kmeans.o
SRC = kmeans.cpp

all : prepare $(TARGET)

prepare:
	make -C $(TOP_DIR)/splitString
	make -C $(TOP_DIR)/similarity
	make -C $(TOP_DIR)/readFile
	make -C $(TOP_DIR)/scaler

$(TARGET) : $(OBJ)
	$(AR) -r $@ $^

$(OBJ): $(SRC)
	$(CXX) $(CFLAGS) -c $^ -o $@ $(INCLUDE) $(LIB)

clean:
	make -C $(TOP_DIR)/splitString clean
	make -C $(TOP_DIR)/similarity clean
	make -C $(TOP_DIR)/readFile clean
	make -C $(TOP_DIR)/scaler clean
	rm -f *.o *.a

