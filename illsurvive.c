
// This program will override the default behavior of a signal (signal handler)
// SIGINT: interrupt process -> CTRL + C
// SIGHUP: sent to a process when its controlling terminal is closed
// SIGTERM: sent to a process to request its termination
// ps aux | grep illsurvive | grep -v grep -> to get current PID 
// SIGKILL and SIGSTOP cannot be changed

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//handler for common signal that terminate process
static void end_handler(int signal)
{
    printf("I'll survive, baby\n");
}

int main(int argc, char *argv[])
{
    printf("PID = %d\n", getpid());
    int a = 0;
  
    //set handlers
    if ((signal(SIGINT, end_handler) == SIG_ERR) || (signal(SIGHUP, end_handler) == SIG_ERR)
        || (signal(SIGTERM, end_handler) == SIG_ERR))
    {
        printf("Error while setting a signal handler\n");
        exit(EXIT_FAILURE);
    }
    //infinite loop
    while (1)
    {
        printf("a = %d\n", a);
        a++;
        sleep(2);
    }
    return (0); 

}
