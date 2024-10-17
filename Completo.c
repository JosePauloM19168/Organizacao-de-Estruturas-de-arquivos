#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_ESTOQUE "estoque.bin"
#define DESCRICAO_MAX 40

typedef struct {
    char descricao[DESCRICAO_MAX];
    int quantidadeEstoque;
    int minimoEstoque;
    float precoVenda;
} Produto;

void incluirProduto() {
    Produto p;
    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "ab"); // Abre o arquivo em modo de anexar
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Informe a descrição do produto: ");
    scanf(" %[^\n]", p.descricao);
    printf("Informe a quantidade em estoque: ");
    scanf("%d", &p.quantidadeEstoque);
    printf("Informe o nível mínimo de estoque: ");
    scanf("%d", &p.minimoEstoque);
    printf("Informe o preço de venda: ");
    scanf("%f", &p.precoVenda);

    fwrite(&p, sizeof(Produto), 1, arquivo);
    fclose(arquivo);
    printf("Produto incluído com sucesso!\n");
}

void registrarVenda() {
    char descricao[DESCRICAO_MAX];
    int quantidadeVendida;
    Produto p;
    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "r+b"); // Abre o arquivo em modo de leitura e escrita
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Informe a descrição do produto a ser vendido: ");
    scanf(" %[^\n]", descricao);
    printf("Informe a quantidade a ser vendida: ");
    scanf("%d", &quantidadeVendida);

    while (fread(&p, sizeof(Produto), 1, arquivo)) {
        if (strcmp(p.descricao, descricao) == 0) {
            if (p.quantidadeEstoque >= quantidadeVendida) {
                p.quantidadeEstoque -= quantidadeVendida;
                fseek(arquivo, -sizeof(Produto), SEEK_CUR);
                fwrite(&p, sizeof(Produto), 1, arquivo);
                printf("Venda registrada com sucesso!\n");
            } else {
                printf("Estoque insuficiente!\n");
            }
            fclose(arquivo);
            return;
        }
    }
    printf("Produto não encontrado!\n");
    fclose(arquivo);
}

void buscarProduto() {
    char descricao[DESCRICAO_MAX];
    Produto p;
    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "rb"); // Abre o arquivo em modo de leitura
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Informe a descrição do produto a ser buscado: ");
    scanf(" %[^\n]", descricao);

    while (fread(&p, sizeof(Produto), 1, arquivo)) {
        if (strcmp(p.descricao, descricao) == 0) {
            printf("Descrição: %s\n", p.descricao);
            printf("Quantidade em estoque: %d\n", p.quantidadeEstoque);
            printf("Nível mínimo de estoque: %d\n", p.minimoEstoque);
            printf("Preço de venda: %.2f\n", p.precoVenda);
            fclose(arquivo);
            return;
        }
    }
    printf("Produto não encontrado!\n");
    fclose(arquivo);
}

void relatorioEstoqueBaixo() {
    Produto p;
    FILE *arquivo = fopen(ARQUIVO_ESTOQUE, "rb"); // Abre o arquivo em modo de leitura
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Produtos com estoque abaixo do nível mínimo:\n");
    while (fread(&p, sizeof(Produto), 1, arquivo)) {
        if (p.quantidadeEstoque < p.minimoEstoque) {
            printf("Descrição: %s, Estoque: %d, Mínimo: %d, Preço: %.2f\n", 
                   p.descricao, p.quantidadeEstoque, p.minimoEstoque, p.precoVenda);
        }
    }
    fclose(arquivo);
}

int main() {
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Incluir Produto\n");
        printf("2. Registrar Venda\n");
        printf("3. Buscar Produto\n");
        printf("4. Relatório de Estoque Baixo\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluirProduto();
                break;
            case 2:
                registrarVenda();
                break;
            case 3:
                buscarProduto();
                break;
            case 4:
                relatorioEstoqueBaixo();
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);

    return 0;
}
