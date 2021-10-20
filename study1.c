
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

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

int main(void)
{
    signal(15, handle_signal);
    signal(2, reinit_a);
    printf("PID = %d\n", getpid());
    while (1)
    {
        printf("a = %d\n", a);
        a++;
        sleep(2);
    }
}