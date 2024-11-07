#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;
typedef struct _IndiceCep IndiceCep;

struct _IndiceCep
{
    int posicao;
    char cep[8];
};

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int main(int argc, char**argv)
{
    Endereco endereco;
    IndiceCep *indiceCep;
    FILE *arquivoCep, *arquivoIndice;
    int fim, qtd;
    
    arquivoCep = fopen("cep.dat","rb");
    arquivoIndice = fopen("cep_indice.dat","wb");
    
    fseek(arquivoCep, 0, SEEK_END);
    fim = ftell(arquivoCep);
    rewind(arquivoCep);
    
    qtd =  fim/sizeof(Endereco);
    
	indiceCep = (IndiceCep*) malloc(sizeof(IndiceCep)*qtd);
	
	for (int i = 0; i < qtd; i++) 
	{
	    fread(&endereco, sizeof(Endereco), 1, arquivoCep);
	    
	    indiceCep[i].posicao = i;
	    strncpy(indiceCep[i].cep, endereco.cep, 8);
	}
	
	qsort(indiceCep, sizeof(IndiceCep), qtd, compara);
	
	fwrite(indiceCep, sizeof(IndiceCep), qtd, arquivoIndice);
	
	free(indiceCep);
	
	return 0;
}
