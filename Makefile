
run: main
	./bin/main > log/run.log 2>&1

main: log bin src/rdm.cpp src/main.cpp
	g++ src/main.cpp -o bin/main > log/build.log 2>&1

log:
	mkdir -p log

bin:
	mkdir -p bin

