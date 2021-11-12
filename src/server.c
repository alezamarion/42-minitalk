/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:54:56 by azamario          #+#    #+#             */
/*   Updated: 2021/11/11 22:07:45 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"

char	*print_string(char *str)
{
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
	return (NULL);
}

void	sig_handler(int signal, siginfo_t *siginfo, void *context) // siginfo pega automaticamente o pid do sinal recebido
{
	static char	current;
	static int	bits;
	static char	*message;			//recebe char 'A': 01000001

	if (current == 0)
		current = 0xFF;				//current == 11111111
	if (signal == SIGUSR1)			//segunda passagem:  01111111 | 10000000 >> 1 == 01111111 | 01000000 == 01111111
		current |= 0x80 >> bits;
	else if (signal == SIGUSR2)		//primeira passagem: 11111111 ˆ 10000000 >> 0 == 11111111 ^ 10000000 == 01111111
		current ^= 0x80 >> bits;	//terceita passagem: 01111111 ^ 10000000 >> 2 == 01111111 ^ 00100000 == 01011111
	if (++bits == 8)
	{
		if (current)
			message = ft_strappendchar(message, current);
		else
		{
			message = print_string(message);
			free(message);
			message = NULL;
		}
		current = 0xFF;
		bits = 0;
	}
	kill(siginfo->si_pid, SIGUSR1); 				//si_pid = pid do client, dispara o sighandler do client, mandando um SIGUSR1
	(void)context;
}

int	initialize_server(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(struct sigaction));
	sigemptyset(&action.sa_mask);					//initialize and empty a signal set
	action.sa_sigaction = sig_handler;
	action.sa_flags = SA_SIGINFO;					// para utilizar a sa_sigaction				
	if (sigaction(SIGUSR1, &action, NULL))			//retorna 0 se sucesso
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &action, NULL))
		exit(EXIT_FAILURE);
	return (0);
}

int	main(void)
{
	char	*pid;

	pid = ft_itoa(getpid());
	ft_putstr_fd("Server running... [PID]: ", 1);
	ft_putstr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
	initialize_server();
	while (1)
		pause();									//sleep until a signal is delivered that either
	return (0);										//terminates the process or causes the invocation 
}													//of a signal handler			
