// Trevor Lastelick
// COSC-4348-W01-Systems Programming
// Assignment #3 Part 1 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <math.h>

#define N 6

void My_Exit_Status_Check(int status)
{
  int pid;
  int twoByteBinary[16];
  int holder = 0;
  int successExitDecimal = 0;
  int failureDecimal = 0;

  // Convert two-bytes into binary.  
  for (int i = 15; i >= 0; i--)
  {
  twoByteBinary[i] = status % 2;
  status = status/2;
  }
  
  // Check Low-End byte for normal or abnormal termination. 
  for (int i = 15; i >= 9; i--)
    holder += twoByteBinary[i];
  
  // If normal check high-end byte for decimal exit value.
  if (holder == 0)
  {
    for (int i = 7; i >= 0; i--)
    {
      if (i == 7 && twoByteBinary[i] == 1)
        successExitDecimal += 1; 
      if (i == 6 && twoByteBinary[i] == 1)
        successExitDecimal += 2;
      if (i == 5 && twoByteBinary[i] == 1)
        successExitDecimal += 4;
      if (i == 4 && twoByteBinary[i] == 1)
        successExitDecimal += 8;
      if (i == 3 && twoByteBinary[i] == 1)
        successExitDecimal += 16;
      if (i == 2 && twoByteBinary[i] == 1)
        successExitDecimal += 32;
      if (i == 1 && twoByteBinary[i] == 1)
        successExitDecimal += 64;
      if (i == 0 && twoByteBinary[i] == 1)
        successExitDecimal += 128;
    }
    printf("The exit status for child %d using my status check function is: Normal termination, exit status is: %d\n", getpid(), successExitDecimal); 
  }
    
  // Else check low-end byte for decimal signal. 
  // Always 8 in this case. 
  else
  {
    for (int i = 15; i >= 9; i--)
    {
      if (i == 15 && twoByteBinary[i] == 1)
        failureDecimal += 1; 
      if (i == 14 && twoByteBinary[i] == 1)
        failureDecimal += 2;
      if (i == 13 && twoByteBinary[i] == 1)
        failureDecimal += 4;
      if (i == 12 && twoByteBinary[i] == 1)
        failureDecimal += 8;
      if (i == 11 && twoByteBinary[i] == 1)
        failureDecimal += 16;
      if (i == 10 && twoByteBinary[i] == 1)
        failureDecimal += 32;
      if (i == 9 && twoByteBinary[i] == 1)
        failureDecimal += 64;      
    } 
     printf("The exit status for child %d using my status check function is: Abnormal Termination, signal is: %d\n", getpid(), failureDecimal);
  }
}

void C_Macros_Exit_Status_Check(int status)
{
  int pid;

    // If child terminated normally, via a call to exit or a return.
   if (WIFEXITED(status))                    
		printf("The exit status for child %d using C status check macros is: Normal termination, exit status is: %d\n", getpid(), WEXITSTATUS(status));  

   // If child terminated abnormally.
   else 
   {      
    // If the child that caused the return is currently stopped.
    if (WIFSTOPPED(status))
      printf("The exit status for child %d using C status check macros is: Abnormal Termination, signal is: %d\n", getpid(), WSTOPSIG(status));
          
    // If child process terminated because of a signal that was not caught.  
    if (WIFSIGNALED(status))
      printf("The exit status for child %d using C status check macros is: Abnormal Termination, signal is: %d\n", getpid(), WTERMSIG(status)); 
   }	
		    
}

int main() 
{
    unsigned int status, i;
    int pid; //Replaced pid_t with int because Riddler could not understand it. 
    
    /* Parent creates N children */
    for(i = 0; i < N; i++)                       
		if((pid = fork()) == 0)  /* child */
		{
			if(i == 3)		
      exit(i/0);
			exit(100 + i);                     
		}
   
    /* Parent reaps N children in no particular order */
    while ((pid = waitpid(-1, &status, 0)) > 0) 
	{
		My_Exit_Status_Check(status);			// call your code here.
		C_Macros_Exit_Status_Check(status);     // and here.
	}

    /* The only normal termination is if there are no more children */
    if (errno != ECHILD)                          
	   perror("waitpid error");

    exit(0);
}

/*
Sources
https://www.ibm.com/docs/en/xl-fortran-aix/15.1.0?topic=procedures-waitstat-loc
https://chortle.ccsu.edu/java5/Notes/chap85/ch85_12.html
Processes in Unix Slides 30-32
*/