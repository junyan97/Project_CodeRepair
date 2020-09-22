CC = g++

CFLAGS = -c -Wall

repairTool: build

clean:
        rm -f *o repairTool

build: repairTool.o ioUtility.o mutatedProg.o mutationUtility.o parser.o repairUtility.o
		$(CC) epairTool.o ioUtility.o mutatedProg.o mutationUtility.o parser.o repairUtility.o -o repairTool

repairTool.o: repairTool.cpp
				$(CC) $(CFLAGS) repairTool.cpp

ioUtility.o: ioUtility.cpp
				$(CC) $(CFLAGS) ioUtility.cpp

mutatedProg.o: mutatedProg.cpp
				$(CC) $(CFLAGS) mutatedProg.cpp

mutationUtility.o: mutationUtility.cpp
				$(CC) $(CFLAGS) mutationUtility.cpp

parser.o: parser.cpp
				$(CC) $(CFLAGS) parser.cpp

repairUtility.o: repairUtility.cpp
				$(CC) $(CFLAGS) repairUtility.cpp
