/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:54:56 by azamario          #+#    #+#             */
/*   Updated: 2021/11/15 14:49:47 by azamario         ###   ########.fr       */
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

/*
	3. This function is called every time Server receives a signal (SIGUSR1 or SIGUSR2) from Client.
	SIGUSR1 represents 1; SIGUSR2 represents 0. 
	- The string is decomposed into bits by the Client using bitwise operations and sent via signals here
	to the Server. 
	- It is then processed again via bitwise. Every 8 bits processed, they are stored in the static 
	  variable message using function ft_strappendchar.
	- For each bit received, a signal is sent to the Client. When the string finishes being processed
	  by the Client, 8 bits 0 are sent to the Server and then the message is printed by the Server.
*/

void	sig_handler(int signal, siginfo_t *siginfo, void *context)
{
	static char	current;
	static int	bits;
	static char	*message;

	if (current == 0)
		current = 0xFF;
	if (signal == SIGUSR1)
		current |= 0x80 >> bits;
	else if (signal == SIGUSR2)
		current ^= 0x80 >> bits;
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
	kill(siginfo->si_pid, SIGUSR1);
	(void)context;
}

/*
	2. We will process two signals received from the Client: SIGUSR1 and SIGUSR2
*/

int	initialize_server(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(struct sigaction));
	sigemptyset(&action.sa_mask);
	action.sa_sigaction = sig_handler;
	action.sa_flags = SA_SIGINFO;			
	if (sigaction(SIGUSR1, &action, NULL))
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR2, &action, NULL))
		exit(EXIT_FAILURE);
	return (0);
}

/*
	1. Here we get and print the Server PID and initialize the settings of the sigaction function that will be used
	to process the signals received by the Client	
*/

int	main(void)
{
	char	*pid;

	pid = ft_itoa(getpid());
	ft_putstr_fd("Server running... [PID]: ", 1);
	ft_putstr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
	initialize_server();
	while (1)
		pause();
	return (0); 
}		
