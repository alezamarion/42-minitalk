

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

#include "minitalk.h"

void    send_string(int signal)
{

}


int main(int argc, char *argv[])
{
    if (argc == 2)
    {

        //recebe o pid + string
        int pid;
        char *string;

        pid = (int)argv[0];
        string = argv[1];

        signal(10, send_string);      
        // envia a string para o server
    }
}