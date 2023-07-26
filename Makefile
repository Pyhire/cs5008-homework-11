CC = clang   # This variable is which compiler to use, we will use the variable later by $(CC)
CFLAGS = -Wall  # this variable is command line arguments
CFILES =  my_program.c my_matrix.c my_file_reading.c # this variable is the list of files to compile - UPDATE THIS LINE with your files
CTESTFILES = my_matrix.c my_file_reading.c my_tests.c 

all: myprogram  #runs target myprogram is nothing is passed into make

myprogram: # it needs to compile out to >>>map.out<<<!
	$(CC) $(CFLAGS) -o map.out $(CFILES)  
	
test: # for unit tests
	$(CC) $(CFLAGS) -o test.out $(CTESTFILES)  

clean: #this is a clean target, it removes all the .out files, called via > make clean
	rm  *.out