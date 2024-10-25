/*
João Victor Vacari
José Paulo Macedo
Leonardo Picanço
Maurício Neto
Thiago de Castro Genasio Lessa
*/

#include <stdio.h>
#include <string.h>

typedef struct _End
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2]; // Ao Espaço no final da linha + quebra de linha
} End;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Uso: %s <cep>\n", argv[0]);
        return 1;
    }

    FILE *file;
    End endereco;
    int count = 0;

    file = fopen("./aula-04/cep_ordenado.dat", 'rb'); // r+b para poder escrever no arquivo

    int inicio = 0;
    fseek(file, sizeof(End), SEEK_END);

    int fim = ftell(SEEK_END) / sizeof(End);

    while (inicio <= fim)
    {
        count++;
        int meio = (inicio + fim) / 2;
        fseek(file, (meio * sizeof(End)), SEEK_SET);
        fread(&endereco, sizeof(End), 1, file);
        if (strcmp(endereco.cep, argv[1]) == 0)
        {
            printf("CEP: %7s encontrado na posicao: %d\n", endereco.cep, &count);
            break;
        }
        else if ((atoi(argv) > atoi(endereco.cep)))
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    fclose(file);
}
