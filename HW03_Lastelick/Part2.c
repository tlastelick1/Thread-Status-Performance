//Trevor Lastelick
// COSC 4348 W01 - Systems Programming
// Assignment 3 Part 2

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>

int openFileForRW(char * file);
int truncateFile(char * file);
void copyfile(int sourceFileFd, int destinationFileFd, int numBytesToCopy);

#define CREATE_FLAGS (O_WRONLY | O_CREAT | O_TRUNC)
#define CREATE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
char buffer[512];

int main() {

  int sourceFileFd, destinationFileFd;
  int numberOfBytes = 0;
  //char buffer[512];
  char sourceFile[50];
  char destinationFile[50];


  // Get sourceFile
  printf("Professor type: data.dat\n");
  printf("Enter source file: ");
  scanf("%s", sourceFile);
  
  sourceFileFd = openFileForRW(sourceFile);
  
  printf("Your source file is: %s\n", sourceFile);
  
  // Get destinationFile
  printf("Professor type any file name here\n");
  printf("Enter destination file: ");
  scanf("%s", destinationFile);
  
  destinationFileFd = truncateFile(destinationFile);
  
  printf("Your destinationFile is: %s\n", destinationFile);
  
  // Get number of bytes 
  printf("Enter number of bytes to copy at a time: ");
  scanf("%d", &numberOfBytes);
  
  printf("Number of bytes is: %d\n", numberOfBytes); 
  
  // Copy file.
  copyfile(sourceFileFd, destinationFileFd, numberOfBytes);

return 0;
}

// Open a file for reading and writing. 
// @param file, The name of the file to open.
int openFileForRW(char * file)
{

int fd;

fd = open(file, O_RDWR);
if (fd == -1)
    {
    perror("Error opening source file");
    exit(0);
    }
else
  printf("Successfully opened: %s\n", file);

return fd;
}

// If file does not exist then create it
// or if it does exist then open it for reading and writing and truncate it. 
// @param file, The name of the file to open.
int truncateFile(char * file)
{

int fd;

fd = open(file, CREATE_FLAGS, CREATE_MODE);

return fd;
}

// Identically copy one file to another.
// Precondition: Both files must exist and be opened. 
// @param sourceFile, The file to be copied from.
// @param destinationFile, The file to copy to.
// @param numberOfBytes, The number of bytes to copy at a time. 
void copyfile(int sourceFileFd, int destinationFileFd, int numberOfBytes)
{

  double start;
  double end;
  double cpu_time_used;

  // Start keeping track of time.
  start = clock();
  
  // Copy the file n bytes at a time.
  while(read(sourceFileFd, &buffer, numberOfBytes) != 0)
    write(destinationFileFd, &buffer, numberOfBytes);

  // Stop keeping track of time.
  end = clock();
  
  // Total time taken to copy file. 
  cpu_time_used = (end - start) / CLOCKS_PER_SEC;
  printf("Total clock time: %f", cpu_time_used);
}
   

/* 
Sources
https://stackoverflow.com/questions/12944758/reading-integers-from-a-file-in-c
https://stackhowto.com/scanf-string-in-c/
https://www.tutorialspoint.com/c_standard_library/c_function_exit.htm#:~:text=The%20C%20library%20function%20void%20exit%20%28int%20status%29,Following%20is%20the%20declaration%20for%20exit%20%28%29%20function.
https://www.geeksforgeeks.org/how-to-measure-time-taken-by-aprogram-in-c/
pg. 73 textbook
pg. 202-209 textbook
Unix I/O slide 20
dup2_slid38.c
https://loremipsum.io/generator/
*/ 
