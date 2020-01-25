
CXX = g++
CMD = -O3 -g
CFLAGS = $(CMD) -Wall -fno-strict-aliasing -fPIC -Wfloat-equal -Wshadow -DNDEBUG -w

TOP_DIR = ..
QMODULE = ../../qmodule

INCLUDE = -I $(TOP_DIR)/readFile -I $(TOP_DIR)/splitString -I $(QMODULE)/boost/include
LIB = -L $(TOP_DIR)/readFile -lreadfile -L $(TOP_DIR)/splitString -lsplitstring -L $(QMODULE)/boost/lib -lboost_system -lboost_thread

TARGET = kmeans
SRC = kmeans.cpp

all : prepare $(TARGET)

prepare:
	make -C $(TOP_DIR)/splitString
	make -C $(TOP_DIR)/similarity
	make -C $(TOP_DIR)/readFile

$(TARGET):
	 $(CXX) $(CFLAGS) $(SRC) -o $@ $(INCLUDE) $(LIB)

clean:
	make -C $(TOP_DIR)/splitString clean
	make -C $(TOP_DIR)/similarity clean
	make -C $(TOP_DIR)/readFile clean
	rm -f *.o $(TARGET)

