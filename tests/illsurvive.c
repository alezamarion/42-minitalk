
/*
1. 	Em ciência da computação, um sinal é uma forma limitada de comunicação entre processos 
	 utilizada em sistemas Unix e outros sistemas operacionais compatíveis com o padrão POSIX.[1] 
	Um sinal é uma notificação assíncrona enviada a processos com o objetivo de notificar a ocorrência
	 de um evento. 
	Quando um sinal é enviado a um processo, o sistema operacional interrompe o seu fluxo normal de 
	 execução. 
	Um processo pode registrar uma rotina de tratamento de sinal (signal handler) para tratar um 
	 determinado sinal, se não for desejado que a rotina padrão para este sinal seja executada.
	Exemplo de sinais: SIGINT - interrompe o processo | SIGSEGV - falha de segmentação

2.	Sinais podem ser enviados pelo SHELL:
	 kill <signal> <PID>
	Sinais pode ser enviados por processos: 
	 #include <signal.h>
     int kill(pid_t pid, int sig);

3.	This program will override the default behavior of a signal (signal handler)
	
4.	SIGINT: interrupt process -> CTRL + C
	SIGKILL and SIGSTOP cannot be changed

5.	O objetivo do Minitalk é enviar uma string de um processo para outro, através de sinais

6.	Existem dois sinais que podem ser configurados pelo utilizador: SIGUSR1 e SIGUSR2

7.	Não é possível enviar informações através de sinais (uma string)

8.	Mas podemos decompor a string em binários e mandar 0 e 1 através de sinais

9.	Nosso programa envia o SIGUSR1 com valor 1 e o SIGUSR2 como valor 0

10.	A letra "A" tem valor 65, não dá pra enviar o valor, mas podemos enviar 01000001

11.	Utilizando bitwise, nós decompomos o "A" em 0s e 1s e mandamos para o server

12.	O menor espaço de memória que tem um endereço é 1 byte = 1 char = "A" = 8 bits

12. O server irá receber esses 8 bits = 1 char = "A" e imprimir

*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//handler for common signal that terminate process
static void signal_handler(int signal)
{
    printf("I'll survive, baby\n");
}

int main(int argc, char *argv[])
{
	//get PID
    printf("PID = %d\n", getpid());
   
    //set handlers
    if (signal(SIGINT, signal_handler));

    //infinite loop	
	int a = 0;
    while (1)
    {
        printf("a = %d\n", a);
        a++;
        sleep(2);
    }
    return (0); 

}
