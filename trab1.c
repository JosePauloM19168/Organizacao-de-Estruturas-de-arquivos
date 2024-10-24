/*
João Victor Vacari
José Paulo Macedo
Leonardo Picanço
Thiago de Castro Genasio Lessa
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define ARQUIVO "estoque.bin"

typedef struct {
    char descricao[40];
    int quantidadeEstoque;
    int minimoEstoque;
    float precoVenda;
} Produto;


void incluirProduto(){
    FILE* file;    
    Produto produto;
    
    getchar();
    printf("\nDescricao do produto: \n");
    scanf("%39s", produto.descricao);

    printf("\nQuantidade em Estoque: \n");
    scanf("%d", &produto.quantidadeEstoque);

    printf("\nQuantidade minima: \n");
    scanf("%d", &produto.minimoEstoque);

    printf("\nPreco de venda: \n");
    scanf("%f", &produto.precoVenda);
    
    file = fopen("estoque.bin", "r+b");
    fseek(file, 0, SEEK_END);
    fwrite(&produto, sizeof(Produto), 1, file);
    fclose(file);
};

void registrarVenda(int quantidade, int cd_produto){
    FILE* file;    
    Produto produtoLeitura;
    file = fopen("estoque.bin", "r+b");

    
    
    fseek(file, (cd_produto * sizeof(Produto)), SEEK_SET);
    fread(&produtoLeitura, sizeof(Produto), 1, file);

    if (quantidade > produtoLeitura.quantidadeEstoque) {
        printf("Quantidade em estoque insuficiente para a venda.\n");
        return;
    }

    produtoLeitura.quantidadeEstoque -= quantidade;

    fseek(file, (cd_produto * sizeof(Produto)), SEEK_SET);
    fwrite(&produtoLeitura, sizeof(Produto), 1, file);

    fclose(file);
};

void buscarProduto(int b, Produto produto){
    FILE* file;    
    Produto produtoLeitura;

    file = fopen("estoque.bin", "r+b");
    fseek(file, (b * sizeof(Produto)), SEEK_SET);
    fread(&produtoLeitura, sizeof(Produto), 1, file);

    printf("%s %d %d %f \n", produtoLeitura.descricao, produtoLeitura.quantidadeEstoque, produtoLeitura.minimoEstoque, produtoLeitura.precoVenda);

    fclose(file);
};

//buscar produto por descrição ad
void buscarProdutoPorDescricao(char *descricao){
    FILE* file;
    Produto produtoLeitura;
    bool naoEncontrou = 1;
    
    file = fopen("estoque.bin", "r+b");
    int result = fread(&produtoLeitura, sizeof(Produto), 1, file);
    
    while(result>0){
        if (strstr(produtoLeitura.descricao, descricao)){
            printf("%s %d %d %f \n", produtoLeitura.descricao, produtoLeitura.quantidadeEstoque, produtoLeitura.minimoEstoque, produtoLeitura.precoVenda);
            naoEncontrou = 0;
        }
        result = fread(&produtoLeitura, sizeof(Produto), 1, file);
    }
    if(naoEncontrou==1){
        printf("Descrição não encontrada");
    }
        
    fclose(file);
}

void relatorioEstoqueMinimo(){
    FILE* file;    
    file = fopen("estoque.bin", "r+b");
    Produto produtoLeitura;
    
    int result = fread(&produtoLeitura, sizeof(Produto), 1, file);
    
    while(result>0){
        if (produtoLeitura.quantidadeEstoque <= produtoLeitura.minimoEstoque){
            printf("O produto : %s está com estoque abaixo do mínimo, atualmente possui %d em estoque \n",produtoLeitura.descricao, produtoLeitura.quantidadeEstoque);
        }
        
        result = fread(&produtoLeitura, sizeof(Produto), 1, file);
    }
    
    fclose(file);
};


int main() {
    int opcao, i,j,k;

    do {
        printf(" 1: incluir Produto \n 2: registrar Venda \n 3: buscar Produto \n 4: buscar Produto por descrição \n 5: relatorio Estoque Minimo \n 6: Sair \n Escolha uma opcao: \n");
        i = scanf("%d", &opcao);
        char text[40];

        Produto produto;
        strcpy(produto.descricao, "descricao");
        produto.quantidadeEstoque = 1;
        produto.minimoEstoque = 2;
        produto.precoVenda = 3;

        exibirMenu(produto);

        switch(opcao) {
            case 1:
                incluirProduto();
                break;
            case 2:
                printf("insira a quantidade a ser vendida: \n");
                scanf("%d",&k);
                printf("insira o código do produto: \n");
                scanf("%d",&j);
                registrarVenda(k, j);
                break;
            case 3:
                printf("insira o código do produto: \n");
                scanf("%d", &i);
                buscarProduto(i, produto);
                break;
            case 4:
                printf("digite o que deseja pesquisar: \n");
                scanf("%39s", &text);
                buscarProdutoPorDescricao(text);
                break;
            case 5:
                relatorioEstoqueMinimo();
                break;
            case 6:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 6);

    return 0;
}
