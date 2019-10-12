CXXFLAGS+=-O2
CXX=g++

all: out out/main

run: out out/main
	./out/main

out/main: src/main.cpp
	$(CXX) $^ $(CXXFLAGS) -o out/main

pack:
	zip task.zip -r Makefile src

out:
	mkdir -p out

clean:
	rm -rf out