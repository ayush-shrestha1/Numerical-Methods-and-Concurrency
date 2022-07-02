# TASK 3: Finding prime numbers from multiple text files using multithreading 
You will be given files containing a list of numbers. The amount and numbers themselves will be
random. You will create a C program which counts the number of prime numbers there are within
the files and output to a file the amount of prime numbers found, along with the prime numbers
themselves. The aim of this task is to use POSIX threads to parallelise the task to take advantage of
the multicore processor within your machine to speed up the task. The threads you spawn within the
program must compute an equal or close to an equal amount of computations to make the program
more efficient in relation to speed. For this section, you will be reading the data from three files and
splitting it across many threads, you should load in the data from files and split the data into equal
parts, then process each slice within your threads. This task also tests your knowledge of dynamic
memory allocation. NOTE – this program should work with any amount of threads.
Creating an algorithm to detect prime numbers
Using dynamic memory – “malloc”
Using multithreading with equal computations
Outputting correct output to a file