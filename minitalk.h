# ifndef MINITALK_H
# define MINITALK_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

# define SIGUSR1 10
# define SIGUSR2 12

#define _POSIX_SOURCE

void    send_string(int signal);

# endif