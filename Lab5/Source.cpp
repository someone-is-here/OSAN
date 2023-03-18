#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#define PERIOD 10

using namespace std;

static unsigned long n_count;
static int b_exitflag;

/* -- Signal handler (old-style signal handling) -- */

void SigHandler (int n_signal) {
  switch (n_signal) {
    case SIGHUP:
      n_count = 0;		//re-initializing must be here!
      break;
    case SIGTERM:
      b_exitflag = 1;		//flag to exit the process
      break;
    default:
      break;
    }
  signal (n_signal, SigHandler);	//restore
  return;
}

/* -- Main module entry point -- */
int main (int argc, char *argv[]) {
  ofstream writeFile("Log.txt");
  
  pid_t n_pid;
  unsigned long n_lastcount = n_count;
  
//- initializing
  n_count = 0;
  n_pid = getpid ();

 writeFile << "Starting" << endl;
//- installing daemon
//- step 1
  n_pid = fork ();
  switch (n_pid) {
    case -1:			//the parent is here, an error occured
    	writeFile << "fork() error!" << endl;
        exit (-1);
    case 0:			//the child is here
      n_pid = getpid ();
      writeFile << "The process was switched" << n_pid << endl;
      break;
    default:			//parent is here, child was started
      exit (0);
    }
    
//- step 2 (child is here)
  setsid ();			//new personal session
  
//- step 3
  n_pid = fork ();
  
  switch (n_pid){
    case -1:			//parent (first child) is here, error
    	writeFile << "fork() error!" << endl;
     // LogPost ("fork() error!", 0);
      exit (-1);
    case 0:			//the child (second child) is here
      n_pid = getpid ();
      writeFile << "The process was double switched " << n_pid << endl;
      //LogPost ("The process was double switched", n_pid);	//with new PID
      break;
    default:			//parent (first child) is here,
//and second child was started
      exit (0);
    }
//- step 4 (the second child is here)
  signal (SIGTTOU, SIG_IGN);
  signal (SIGTTIN, SIG_IGN);
  signal (SIGTSTP, SIG_IGN);
  signal (SIGHUP, SigHandler);
  signal (SIGTERM, SigHandler);
//- step 5

  fclose (stdin);
  fclose (stdout);
  fclose (stderr);
//- main loop
 // LogPost ("Waiting for events", 0);
writeFile << "Waiting for events" << endl;
  while (!b_exitflag) {
      sleep (PERIOD);

      if (n_count < n_lastcount) {			//detect re-initializing (indirectly);
	writeFile << "Re-initialization occured!" << endl;
      }
      n_count += PERIOD;
      n_lastcount = n_count;
      
      writeFile <<  "Counter: " << n_count << " sec" << endl;

    }
    
//- closing, then exit
  writeFile.close();
  exit (0);
}

