rm -f *.o
g++ -c main.cc 
g++ -c vanilla.cc
g++ -c eytzinger.cc
g++ -c btree.cc
g++ main.o vanilla.o eytzinger.o btree.o
./a.out
