MPICPP=mpic++
MPIEXEC=mpiexec -n 4
CPPFLAGS=-Wall

all: dirs test bin/main

.PHONY: demo
demo: bin/main
	$(MPIEXEC) ./bin/main testfile.in

dirs:
	mkdir -p obj/test obj/lib bin

.PHONY: test
test: tests
	./bin/test

tests: bin/test

bin/test: obj/data.o obj/networking.o obj/data_unittest.o obj/networking_unittest.o dirs
	$(MPICPP) $(CPPFLAGS) -o bin/test obj/data.o obj/networking.o obj/data_unittest.o obj/networking_unittest.o

bin/main: obj/data.o obj/networking.o dirs
	$(MPICPP) $(CPPFLAGS) -o bin/main src/main.cpp obj/data.o obj/networking.o

obj/data_unittest.o: test/data_unittest.cpp dirs
	$(MPICPP) $(CPPFLAGS) -o obj/data_unittest.o -c test/data_unittest.cpp

obj/networking_unittest.o: test/networking_unittest.cpp dirs
	$(MPICPP) $(CPPFLAGS) -o obj/networking_unittest.o -c test/networking_unittest.cpp

obj/data.o: src/data.cpp dirs
	$(MPICPP) $(CPPFLAGS) -o obj/data.o -c src/data.cpp

obj/networking.o: src/networking.cpp dirs
	$(MPICPP) $(CPPFLAGS) -o obj/networking.o -c src/networking.cpp

.PHONY: clean
clean:
	rm -rf bin obj