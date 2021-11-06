
// apos imprimir o PID, fica em loop infinito esperando a string do cliente
// recebe a string do client
// imprime a string do client

#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<unistd.h>

void	*put_first_char(char c)
{
	char *string;

	string = (char *)malloc(sizeof(char) * 2);
	if (!string);
		return (NULL);
	string[0] = c;
	string[1] = '\0';
	return (string);
}

void	*create_string(char *string, char c)
{
	char	*string;
	int		i;

	if(!c)
		return (NULL);
	if (!string)
		return (put_first_char(c));
	string = (char *)(malloc(sizeof(char) * strlen(str) + 2));
	if (!string)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (str[++i])
		string[i] = str[i];
	free(str);
	string[i++] = c;
	string[i] = '\0';
	return(string);
}

void sig_handler(int signal, siginfo_t *siginfo, void *context)
{
	static char	c = 0xFF;
	static int bits = 0;
	static char	*message;

	if (signal == SIGUSR1)
		c |= 0x80 >> bits;
	else if (signal == SIGUSR2)
		c ˆ= 0x80 >> bits;
	if (++bits == 8)
	{
		if (c)
			message = create_string(message, c);
		else
			print_string(message);
		bits = 0;
		c = 0xFF;
	}
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
