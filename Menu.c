#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "estoque.bin"

typedef struct {
    char descricao[40];
    int quantidadeEstoque;
    int minimoEstoque;
    float precoVenda;
} Produto;

void incluirProduto();
void buscarProduto();
void registrarVenda();
void relatorioEstoqueMinimo();
void exibirMenu();
void limparBuffer();

int main() {
    int opcao;

    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o buffer do stdin

        switch(opcao) {
            case 1:
                incluirProduto();
                break;
            case 2:
                buscarProduto();
                break;
            case 3:
                registrarVenda();
                break;
            case 4:
                relatorioEstoqueMinimo();
                break;
            case 5:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 5);

    return 0;
}
