
// apos imprimir o PID, fica em loop infinito esperando a string do cliente
// recebe a string do client
// imprime a string do client

#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

char *print_string(char *str)
{
    printf("\n%s\n", str);
    return (NULL);
}

void	*put_first_char(char c)
{
	char *string;

	string = (char *)malloc(sizeof(char) + 1);
	if (!string)
		return (NULL);
	string[0] = c;
	string[1] = '\0';
	return (string);
}

void	*handle_string(char *str, char c)
{
	char	*string;
	int		index;

	if(!c)
		return (NULL);
	if (!str)
		return (put_first_char(c));
	string = (char *)(malloc(sizeof(char) * strlen(str) + 2));
	if (!string)
		return (NULL);
	index = -1;
	while (str[index])
	{
		string[index] = str[index];
		index++;
	}
	string[index++] = c;
	string[index] = '\0';
	return(string);
}

void sig_handler(int signal, siginfo_t *siginfo, void *context)
{
	static char	current = 0xFF;
	static int bits = 0;
	static char	*message;

  	if (signal == SIGUSR1) // 1
    	current |= 0x80 >> bits;
  	else if (signal == SIGUSR2) // 0
    	current ^= 0x80 >> bits;
	if (++bits == 8)
	{
		if (current)
			message = handle_string(message, current);
		else
		{
			message = print_string(message);
			free(message);
			message = NULL;
		}
		current = 0xFF;
		bits = 0;
	}
	kill(siginfo->si_pid, SIGUSR1);
	(void)context;
}

int save_actions(void){
    struct sigaction action;
    bzero(&action, sizeof(struct sigaction));
    sigemptyset(&action.sa_mask);
    action.sa_sigaction = sig_handler;
    action.sa_flags = SA_SIGINFO;
    if (sigaction(SIGUSR1, &action, NULL)) //it returns 0 on success, -1 on error
        exit(EXIT_FAILURE);
    if (sigaction(SIGUSR2, &action, NULL))
		    exit(EXIT_FAILURE);
    return (0);
}

/*
    struct sigaction
	{
        void		(*sa_handler)(int);
        void		(*sa_sigaction)(int, siginfo_t *, void *);
        sigset_t	sa_mask;
        int			sa_flags;
        void		(*sa_restorer)(void);
    };
*/

int main(void)
{
    printf("Server running... [PID]: %d\n", getpid());
    save_actions();
    while (1)
        pause();
    return (0);
}
