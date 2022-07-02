# Thread-Status-Performance
1. Check exit status of threads. 2. Test Performance read/write functions.

Part 1:
Write your own function to check the exit status of a child. The function should take as input the exit status of a child and returns the following information:

1.If the child terminated normally or abnormally.

2.If the child terminated normally, it should return its exit status.

3.If the child terminated abnormally, it should return the signal number that caused the abnormal termination.

Part 2:
Design and implement an experiment to test the performance of read and write functions. Write a function called "copyfile" that will copy one file to another using read/write functions. Your function should take three parameters: source file, destination file and the number of bytes to copy at time. The function should return the time taken to copy the file. Run this experiment using different number of bytes to copy(1, 3, 5, 7, ....) and record the time for each experiment. Plot the graph (time, number of byte). What are your conclusions.
