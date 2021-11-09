/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:54:56 by azamario          #+#    #+#             */
/*   Updated: 2021/11/10 00:37:49 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// apos imprimir o PID, fica em loop infinito esperando a string do cliente
// recebe a string do client
// imprime a string do client

#include <signal.h>
#include "libft.h"


char	*print_string(char *str)
{
	ft_putstr_fd(str, 1);
	return (NULL);
}

void sig_handler(int signal, siginfo_t *siginfo, void *context)
{
	static char	current;
	static int bits;
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

int save_actions(void){
    struct sigaction action;
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

int	main(void)
{
	char	*pid;

	pid = ft_itoa(getpid());
	ft_putstr_fd("Server running... [PID]: ", 1);
	ft_putstr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
	save_actions();
	while (1)
		pause();
	return (0);
}
