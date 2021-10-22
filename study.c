
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define _GNU_SOURCE
#define _XOPEN_SOURCE

int a = 0;

void    handle_signal(int signal)
{
    printf("Encerrando a execucao\n");
    exit(15);
}

void    reinit_a(int signal)
{
    printf("Um sinal foi enviado\n");
    printf("Executar o handler desse sinal:\n");
    printf("Reiniciando a...\n");
    a = 0;
}

int main(int argc, char *argv[])
{
    struct sigaction sinal;
    struct sigaction sinal1;
    
    sinal.sa_handler = handle_signal;
    sinal.sa_flags = 0;

    sinal1.sa_handler = reinit_a;
    sinal1.sa_flags = 0;
    
    sigaction(15, &sinal, NULL);
    sigaction(2, &sinal1, NULL);
    printf("PID = %d\n", getpid());
    while (1)
    {
        printf("a = %d\n", a);
        a++;
        sleep(2);
    }
}
