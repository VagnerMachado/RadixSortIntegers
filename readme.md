
Argumets needed for the program:

argv[1] - an input text file with positive and/or negative numbers thta can be in different rows.
argv[2] - an output text file that will contain the iteration of the sort
argv[3] - an output file that will contain the sorted integers



(1) It will read the input data file twice.  The first reading is to determine:


i) the largest positive integer and 

ii) the largest negative number in the data file.


The second reading is the actual process of the Radix sort.
(2) The largest positive number will be used to control the number iterations (digits) of the Radix sort to do the sorting.

(3)  The largest negative number is to see if there are negative numbers in the data file so as to take care of the negative numbers as follows: it will take the *absolute value* of the largest negative integer, called it offset.   If offset  > 0, it means that there are negative numbers in the input data file.  For simplicity, it will add offset to each input data before Radix sort process to take place, even if offset is zero. After Radix completing its sorting, if offset is > 0, each data in the sorted list will be subtracted by the offset to get back their original values. 

(4) There are only two hash tables of 10 buckets will be used in the Radix sort.

(5) Each of the hash table is an array of * linked list queues*. 

(6) To reduce the complexity of the algorithm, there is a* linked list stack* to hold the initially data as nodes.

(7) Then, the nodes in the stack will be up-load  to one of the first hashTable used in the program.

Algorithms steps in main

Step 0: inFile <- open the input file 

	outFile1 <- open outFile1
	
outFile2 <- open outFile2

Step 1: firstReading (inFile, maxDigits, offSet) 

Step 2:  close inFile 

 inFile <- open the input file
 
Step 3: loadStack (inFile, Top)

Step 4: RadixSort (Top)

Step 5: Output sorted data to outFile1, debug and data about sorted integers to outFile2

