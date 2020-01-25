
CXX = g++
CMD = -O3 -g
CFLAGS = $(CMD) -Wall -fno-strict-aliasing -fPIC -Wfloat-equal -Wshadow -DNDEBUG -w

#export LD_LIBRARY_PATH=/da1/malele/mycode/cpp/qmodule/boost/lib:$LD_LIBRARY_PATH

QMODULE = ../qmodule

INCLUDE = -I ./readFile -I ./splitString -I ./similarity -I $(QMODULE)/boost/include -I ./splitData
LIB = -L ./readFile -lreadfile -L ./splitString -lsplitstring -L ./similarity -lsimilarity -L $(QMODULE)/boost/lib -lboost_system -lboost_thread

OBJ = main.o
SRC = main.cpp

all : prepare main

prepare:
	make -C ./splitString
	make -C ./similarity
	make -C ./readFile

main:
	 $(CXX) $(CFLAGS) $(SRC) -o $@ $(INCLUDE) $(LIB)

clean:
	make -C ./splitString clean
	make -C ./similarity clean
	make -C ./readFile clean
	rm -f *.o main

