/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:55:23 by azamario          #+#    #+#             */
/*   Updated: 2021/11/15 15:17:25 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"

static int	g_done;

void	wait_server_response(void)
{
	while (g_done == 0)
		;
	g_done = 0;
}

/*
	4. When the Server sends the SIGUSR1 signal indicating that it received the bit sent by the Client,
	the variable value g_done is changed to 1 and the wait_server_response function ends the wait loop.
*/

void	sig_handler(int signal)
{
	g_done = 1;
	(void)signal;
}

/*
	3. This function will decompose the string into bits using bitwise operators and send it to the 
	Server, using signals SIGUSR1 representing bit 1 and SIGUSR2 representing bit 0.
	Counter variable is initialized using bitwise left shift and incremented using bitwise right shift.
	A bitwise & operation is used to get the bit that will be sent to the Server.
	For each bit sent, an acknowledgment of receipt by the Server is expected.
*/

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

/*
	2. This function receives the string that will be processed through the send_signal function. 
	When the string ends, 8 bits 0 are sent to the Server. For each bit sent, a confirmation of receipt -
	by Server - is awaited.
*/

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

/*
	1. Here the sigaction function is used to handle the SIGUSR1 signal received by the Server. 
	This signal will be used as confirmation of receiving - by the Server - the signals sent by the Client.
	The process_str function receives the Server PID and the string that will be sent to the Server.
*/

int	main(int argc, char const *argv[])
{
	struct sigaction	action;
	int					pid;

	if (argc != 3)
		exit(EXIT_FAILURE);
	ft_bzero(&action, sizeof(struct sigaction));
	action.sa_handler = sig_handler;
	if (sigaction(SIGUSR1, &action, NULL))
		exit(EXIT_FAILURE);
	pid = ft_atoi(argv[1]);
	process_str(pid, argv[2]);
	return (EXIT_SUCCESS);
}
