
CXX = g++
CMD = -O3 -g
CFLAGS = $(CMD) -Wall -fno-strict-aliasing -fPIC -Wfloat-equal -Wshadow -DNDEBUG -w

#export LD_LIBRARY_PATH=/da1/malele/mycode/cpp/qmodule/boost/lib:$LD_LIBRARY_PATH

QMODULE = ../qmodule

INCLUDE = -I ./readFile -I ./splitString -I ./similarity -I $(QMODULE)/boost/include -I ./splitData -I ./scaler -I ./kmeans
LIB = -L ./scaler/ -lscaler -L ./readFile -lreadfile -L ./splitString -lsplitstring -L ./similarity -lsimilarity -L $(QMODULE)/boost/lib -lboost_system -lboost_thread -L ./kmeans -lkmeans

SRC = v2_main_kmeans.cpp   ## 主函数文件 

all : prepare main

prepare:
	make -C ./splitString
	make -C ./similarity
	make -C ./readFile
	make -C ./scaler
	make -C ./kmeans

main:
	$(CXX) $(CFLAGS) $(SRC) -o $@ $(INCLUDE) $(LIB)

clean:
	make -C ./splitString clean
	make -C ./similarity clean
	make -C ./readFile clean
	make -C ./scaler clean
	make -C ./kmeans clean
	rm -f *.o main

