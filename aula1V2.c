//NESSA VERSÃO ELA IMPRIME O NUMERO DE LINHAS DE UM ARQUIVO 1 PARA UM ARQUIVO 2
//gcc -o ex1 ex1.c
//./ex1 aula.txt aula1.txt

#include <stdio.h>

// stdout, stdin, stderr

int main(int argc, char** argv)
{
    FILE *entrada, *saida;
    int c;
    int count = 0;

    if (argc != 3)
    {
        fprintf(stderr, "Erro na chamada do comando.\n");
        fprintf(stderr, "Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);
        return 1;
    }

    // Abre o arquivo de origem para leitura
    entrada = fopen(argv[1], "rb");
    if (entrada == NULL)
    {
        fprintf(stderr, "Arquivo %s não pode ser aberto para leitura\n", argv[1]);
        return 1;
    }

    // Abre o arquivo de destino para escrita
    saida = fopen(argv[2], "w");
    if (saida == NULL)
    {
        fprintf(stderr, "Arquivo %s não pode ser aberto para escrita\n", argv[2]);
        fclose(entrada);
        return 1;
    }

    // Contagem de linhas
    c = fgetc(entrada);
    while (c != EOF)
    {
        if (c == '\n') {
            count++;
        }
        c = fgetc(entrada); // Lê o próximo caractere
    }

    fclose(entrada); // Fecha o arquivo de origem

    // Escreve a contagem de linhas no arquivo de destino
    fprintf(saida, "O arquivo %s possui %d linhas\n", argv[1], count);
    fclose(saida); // Fecha o arquivo de destino

    return 0;
}
