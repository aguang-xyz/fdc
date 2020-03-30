TARGET = ./bin/fdc

CC = g++
CFLAGS = -O3

HEADERS = src/fdc/types.h src/fdc/utils.h
SOURCES = src/main.cpp src/fdc/utils.cpp

run: bin doc
	$(TARGET) > log/run.log 2>&1

bin: log bin $(HEADERS) $(SOURCES)
	mkdir -p bin
	
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) > log/build.log 2>&1

doc: Doxyfile $(HEADERS) $(SOURCES)
	doxygen ./Doxyfile

log:
	mkdir -p log
