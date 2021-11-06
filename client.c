

/* 
1 - o cliente recebe dois parametros:
    - o PID do server
    - a string que sera enviada

2 - o cliente tem que passar a string como parametro para o server 
3 - assim que o server receber a string, ele deve imprimi-la
4 - a comunicacao entre os programas sera feira entre sinais UNIX
5 - o server tem que ser capaz de imprimir a string rapidamente
6 - o server deve ser capaz de receber strings de varios clientes, sem precisar ser reinicializado
7 - apenas dois sinais sao permitidos: SIGUSR1 e SIGUSR2

cliente manda para o server
*/

#include<signal.h>
#include<stdlib.h>
#include<strings.h>
#include<stdio.h>

static int	g_done;

void	wait_server_response(void)
{
	while (g_done == 0)
		;
	g_done = 0;
}

void	send_signal(int pid, const char *str)
{
	int	count;
	int	bit;

	count = 1 << 7;
	while (count)
	{						
		bit = *str & count;
		if (bit)
		{
			if (kill(pid, SIGUSR1))
				exit(EXIT_FAILURE);
		}
		else
		{
			if (kill(pid, SIGUSR2))
				exit(EXIT_FAILURE);
		}
		wait_server_response();
		count >>= 1;
	}
}

void	process_str(int pid, const char *str)
{
	int	count;
	       
	while (*str)
	{
		send_signal(pid, str);
		str++;
	}		
	count = 8;
	while (count--)
	{
		if (kill(pid, SIGUSR2))
			exit(EXIT_FAILURE);
		wait_server_response();
	}
}

void	sig_handler(int signal)
{
	g_done = 1;
	(void)signal;
}

int	main(int argc, char const *argv[])
{
	struct sigaction	action;
	int					pid;

	if (argc != 3)
		exit(EXIT_FAILURE);
	bzero(&action, sizeof(struct sigaction));
	action.sa_handler = sig_handler;
	if (sigaction(SIGUSR1, &action, NULL))
		exit(EXIT_FAILURE);
	pid = atoi(argv[1]);
	process_str(pid, argv[2]);
	return (EXIT_SUCCESS);
}

