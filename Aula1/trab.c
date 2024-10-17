#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ARQUIVO "estoque.bin"

typedef struct {
    char descricao[40];
    int quantidadeEstoque;
    int minimoEstoque;
    float precoVenda;
} Produto;


void incluirProduto(Produto produto){
    FILE* file;    
    file = fopen("estoque.bin", "r+b");
    fseek(file, sizeof(Produto), SEEK_END);
    fwrite(&produto, sizeof(Produto), 1, file);
    fclose(file);
};


void buscarProduto(int b, Produto produto){
    FILE* file;    
    file = fopen("estoque.bin", "r+b");
    fseek(file, (b * sizeof(Produto)), SEEK_SET);
    printf("%c %d %d %f", produto.descricao, produto.quantidadeEstoque, produto.minimoEstoque, produto.precoVenda);
    fclose(file);
};

void registrarVenda(Produto produto){
    FILE* file;    
    file = fopen("estoque.bin", "r+b");
    fclose(file);
};

void relatorioEstoqueMinimo(Produto produto){
    FILE* file;    
    file = fopen("estoque.bin", "r+b");
    fclose(file);
};

void limparBuffer(Produto produto){
    FILE* file;    
    file = fopen("estoque.bin", "r+b");
    fclose(file);
};


void exibirMenu(Produto produto){
    FILE* file;    
    file = fopen("estoque.bin", "r+b");
    fclose(file);
};


int main() {
    int opcao;

    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer(); 

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
