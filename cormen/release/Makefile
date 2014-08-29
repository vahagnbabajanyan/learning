CC=g++
CFLAGS=-c -Wall
BASEDIR=/home/vahagnbabajanyan/Projects/learning
UTILDIR=$(BASEDIR)/cormen/utilities
SORTDIR=$(BASEDIR)/cormen/sorting
INC=-I$(BASEDIR)/cormen/utilities \
    -I$(BASEDIR)/cormen/sorting \
    -I$(BASEDIR)/cormen/searching \
    -I$(BASEDIR)/cormen/algs

all : exe

exe : main.o utilities.o sort_lib.a
	$(CC) main.o utilities.o sort_lib.a -o exe

main.o: main.cpp
	$(CC) $(INC) $(CFLAGS)  main.cpp

insertion_sort.o: $(SORTDIR)/insertion_sort.cpp
	$(CC) $(INC) $(CFLAGS) $(SORTDIR)/insertion_sort.cpp 

selection_sort.o: $(SORTDIR)/selection_sort.cpp
	$(CC) $(INC) $(CFLAGS) $(SORTDIR)/selection_sort.cpp 

merge_sort.o: $(SORTDIR)/merge_sort.cpp
	$(CC) $(INC) $(CFLAGS) $(SORTDIR)/merge_sort.cpp

recursive_insertion_sort.o: $(SORTDIR)/recursive_insertion_sort.cpp
	$(CC) $(INC) $(CFLAGS) $(SORTDIR)/recursive_insertion_sort.cpp 

sort_lib.a : insertion_sort.o recursive_insertion_sort.o selection_sort.o merge_sort.o
	ar cr sort_lib.a insertion_sort.o selection_sort.o merge_sort.o recursive_insertion_sort.o

utilities.o: $(UTILDIR)/utilities.cpp
	$(CC) $(INC) $(CFLAGS) $(UTILDIR)/utilities.cpp

clean:
	rm -rf *o exe
