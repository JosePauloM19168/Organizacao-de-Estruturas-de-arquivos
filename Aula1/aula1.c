//aula 1 primeira versão
//gcc -o ex1 ex1.c
//./ex1 aula.txt aula1.txt


#include <stdio.h>

// stdout, stdin, stderr

int main(int argc, char** argv)
{
    FILE *entrada;
    int c;
    int count = 0;

    if (argc != 3)
    {
        fprintf(stderr, "Erro na chamada do comando.\n");
        fprintf(stderr, "Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);
        return 1;
    }

    entrada = fopen(argv[1], "rb");
    if (entrada == NULL)
    {
        fprintf(stderr, "Arquivo %s não pode ser aberto para leitura\n", argv[1]);
        return 1;
    }

    c = fgetc(entrada);
    while (c != EOF)
    {
        if (c == '\n') {
            count++;
        }
        c = fgetc(entrada); // Lê o próximo caractere
    }

    fclose(entrada); // Fecha o arquivo após a leitura
    printf("O arquivo possui %d linhas\n", count);
    return 0;
}
