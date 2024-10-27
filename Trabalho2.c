/*
João Victor Vacari
José Paulo Macedo
Leonardo Picanço
Maurício Neto
Thiago de Castro Genasio Lessa
*/

#include <stdio.h>
#include <string.h>

typedef struct Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2]; // espaço + quebra de linha
} Endereco;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Uso: %s <cep>\n", argv[0]);
        return 1;
    }

    FILE *file;
    Endereco endereco;
    int count = 0;

    file = fopen("../aula-04/cep_ordenado.dat", "rb");
    if (!file)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    else
    {
        printf("Arquivo aberto com sucesso.\n");
    }

    int inicio = 0;
    fseek(file, 0, SEEK_END);
    int fim = ftell(file) / sizeof(Endereco) - 1;

    while (inicio <= fim)
    {
        count++;
        int meio = (inicio + fim) / 2;
        fseek(file, meio * sizeof(Endereco), SEEK_SET);
        fread(&endereco, sizeof(Endereco), 1, file);

        endereco.cep[8] = '\0';

        printf("Lendo CEP: %s na posicao: %d\n", endereco.cep, meio);

        int cmp = strncmp(endereco.cep, argv[1], 8);
        if (cmp == 0)
        {
            printf("CEP:%7s encontrado na posicao: %d\n", endereco.cep, count);
            printf("Endereço encontrado:\n");
            printf("Logradouro: %.72s\n", endereco.logradouro);
            printf("Bairro: %.72s\n", endereco.bairro);
            printf("Cidade: %.72s\n", endereco.cidade);
            printf("UF: %.72s\n", endereco.uf);
            printf("Sigla: %.2s\n", endereco.sigla);
            printf("CEP: %.8s\n", endereco.cep);
            printf("Posicao: %d\n", count);
            fclose(file);
            return 0;
        }
        else if (cmp < 0)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    printf("CEP %s nao encontrado.\n", argv[1]);
    fclose(file);
    return 0;
}
