//exercício 2: contar a frequência de cada símbolo no arquivo. Também baseado no copia1. 
//Criar uma array com contadores para cada uma dos possíveis símbolos (256 ou de 0 a 255) e para cada símbolo lido acumular. Mostrar a tabela na saída padrão. 

// gcc -o ex2 ex2.c
// ./ex2 aula.txt

#include <stdio.h>

int main(int argc, char** argv) {
    FILE *entrada;
    int c; 
    int contadores[256] = {0}; 

    if (argc != 2) {
        fprintf(stderr, "Erro na chamada do comando.\n");
        fprintf(stderr, "Uso: %s [ARQUIVO ORIGEM].\n", argv[0]);
        return 1;
    }

    // Abre o arquivo de origem para leitura
    entrada = fopen(argv[1], "rb");
    if (entrada == NULL) {
        fprintf(stderr, "Arquivo %s não pode ser aberto para leitura\n", argv[1]);
        return 1;
    }

    // Lê os símbolos e conta a frequência
    while ((c = fgetc(entrada)) != EOF) {
        contadores[c]++; // Incrementa o contador do símbolo lido
    }

    fclose(entrada); // Fecha o arquivo de origem

    // Exibe a tabela de frequência
    printf("Frequência de cada símbolo no arquivo:\n");
    for (int i = 0; i < 256; i++) {
        if (contadores[i] > 0) {
            printf("Símbolo: %d (char: '%c') - Frequência: %d\n", i, (char)i, contadores[i]);
        }
    }

    return 0;
}
