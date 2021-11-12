/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:55:23 by azamario          #+#    #+#             */
/*   Updated: 2021/11/11 20:17:26 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#include <signal.h>
#include "libft.h"

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

	count = 1 << 7;							//00000001 << 7 == 10000000
	while (count)
	{										// string "A" == 01000001
		bit = *str & count;					// 1a passagem: 01000001 & 10000000 == 00000000 envia 0	
		if (bit)							// 2a passagem: 01000001 & 01000000 == 01000000 envia 1
		{
			if (kill(pid, SIGUSR1))			//pid server - dispara sighandler do server
				exit(EXIT_FAILURE);
		}
		else
		{
			if (kill(pid, SIGUSR2))
				exit(EXIT_FAILURE);
		}
		wait_server_response();				//aguarda resposta server
		count >>= 1;						//após a primeira passagem == 01000000
	}
}

void	process_str(int pid, const char *str)
{
	int	count;

	while (*str)								//transforma a string em 0 e 1 e envia para o server
	{
		send_signal(pid, str);
		str++;
	}		
	count = 8;								
	while (count--)								//envia byte nulo quando acaba a string
	{
		if (kill(pid, SIGUSR2))
			exit(EXIT_FAILURE);
		wait_server_response();
	}
}

void	sig_handler(int signal) 				//é disparado pelo kill do server
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
	ft_bzero(&action, sizeof(struct sigaction));
	action.sa_handler = sig_handler;
	if (sigaction(SIGUSR1, &action, NULL))		//server só envia o sigusr1 para o client para confirmar que recebeu sinal
		exit(EXIT_FAILURE);
	pid = ft_atoi(argv[1]);
	process_str(pid, argv[2]);
	return (EXIT_SUCCESS);
}
