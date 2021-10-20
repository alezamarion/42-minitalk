// apos imprimir o PID, fica em loop infinito esperando a string do cliente
// recebe a string do client
// imprime a string do client

#include "minitalk.h"

int main(void)
{
    printf("PID = %d\n", getpid());
    while(1)
    {
        sleep(2);
    }
}

