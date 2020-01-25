
CXX = g++
AR = ar

CMD = -O3 -g
CFLAGS = $(CMD) -Wall -fno-strict-aliasing -fPIC -Wfloat-equal -Wshadow -DNDEBUG -w

TOP_DIR = ..
QMODULE = $(TOP_DIR)/../qmodule

INCLUDE = -I $(QMODULE)/boost/include
LIB = -L $(QMODULE)/boost/lib -lboost_system -lboost_thread

TARGET = test_boost_thread
SRC = boost_thread_test6_class_external.cpp 

all : $(TARGET)

$(TARGET) :
	$(CXX) $(CFLAGS) $(SRC) -o $@ $(INCLUDE) $(LIB)

clean:
	rm -f *.o *.a $(TARGET)

