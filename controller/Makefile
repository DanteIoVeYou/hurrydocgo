CC=g++
TARGET=hurrydocgo
FLAG=-std=c++17 -I ../third_party/cppjieba/include -lpthread -ljsoncpp -lboost_system
$(TARGET): controller.cpp ../index/index.cpp ../searcher/searcher.cpp ../preprocessor/preprocessor.cpp
	$(CC) -o $@ $^ $(FLAG)
.PHONY:clean
clean:
	rm -rf $(TARGET)
	rm -rf ../data/output/raw_input
