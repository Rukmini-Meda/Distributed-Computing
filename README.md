## Distributed-Computing

### Odd Even Transposition Sort

#### About & Execution instructions

The source code is in C language and no external libraries are required. To compile the code, use the following command:

```	
				gcc .\odd_even_transposition_sort.c –pthread
```

To run the code:

```
				./a.out (Ubuntu) or ./a.exe (Windows)
```

#### Implementation details & assumptions

1. The algorithm is implemented using threads, hence the –pthread tag is necessary to compile the code. The input sequence is sorted in ascending order. This is assumed.
2. Array data structure is used for storing the elements and manipulating them.
3. Appropriate swaps are done in process first at odd positions and then at even positions (indexing assuming 1 here, but array indices start with 0). Processes wait till the other processes complete in that round.
4. An extra structure for storing the arguments to the comparison function in thread is implemented with required arguments like position, array and total number of elements.

#### Sample Input & Output

```
Enter the number of elements in your sequence:
5
Enter your sequence:
9 2 4 6 8
By odd even transposition sort, the sorted sequence is:
2 4 6 8 9 
```
 
### Sasaki's time optimal distributed sorting algorithm

#### About & Execution instructions

The source code is in C language and no external libraries are required. To compile the code, use the following command:
```	
				gcc .\sasaki_time_optimal.c –pthread
```
To run the code:
```
				./a.out (Ubuntu) or ./a.exe (Windows)
```
#### Implementation details & assumptions

1. The algorithm is implemented using threads, hence the –pthread tag is necessary to compile the code. The input sequence is sorted in ascending order. This is assumed.
2. Linked List data structure is used for storing the elements and manipulating them. The node in the linked list represents a process and has the following properties:
	a. Two pointers to left and right elements (from Element structure which have the properties of value and isMarked)
	b. Two pointers to left and right nodes of the process
	c. One integer variable for storing area of the process node
3. An extra structure for storing the arguments to the comparison function in thread is implemented with required arguments of a pointer to a process node. We do not use position or index information here. Hence, a linked list is used instead of an array.
4. A process waits for the other processes to compelete in the same round. In each round, the processes exchange values with it's corresponding left and right nodes and update their areas.

#### Sample Input & Output
```
Enter the number of elements in your sequence:
5
Enter your sequence:
9 2 4 6 8
By Sasaki's algorithm, the sorted sequence is:
2 4 6 8 9 
```

### An alternate time optimal sorting algorithm using medians

#### About & Execution instructions

The source code is in C language and no external libraries are required. To compile the code, use the following command:
```
				gcc .\alternate_time_optimal.c –pthread
```
To run the code:
```
				./a.out (Ubuntu) or ./a.exe (Windows)
```
#### Implementation details & assumptions

1. The algorithm is implemented using threads, hence the –pthread tag is necessary to compile the code. The input sequence is sorted in ascending order. This is assumed.
2. Array data structure is used for storing the elements and manipulating them.
3. An extra structure for storing the arguments to the comparison function in thread is implemented which includes the pointer to input array, total number of numbers, and the center of each triplet in a round.
4. A process waits for the other processes to compelete in the same round. In each process, the triplets are updated with numbers sorted in ascending order.

#### Sample Input & Output
```
Enter the number of elements in your sequence:
5
Enter your sequence:
9 2 4 6 8
By alternate time optimal sorting method, the sorted sequence is:
2 4 6 8 9 
```

