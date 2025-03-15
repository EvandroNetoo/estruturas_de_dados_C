/*
Resultado do código após explicação do trabalho, usando como base o código do professor.
Link para o vídeo no canal de quem gravou a aula: https://youtu.be/7-SJELwtNxk
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef char string[20];


typedef struct tipoCelula {
	int valor;
	string nome;
	struct tipoCelula *abaixo;
	struct tipoCelula *dir;
} TCelula;


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void inicializaMatriz(TCelula **c){
	*c = NULL;
}


TCelula *alocaCelula(){
	TCelula *novo = (TCelula *)malloc(sizeof(TCelula));
	novo->dir = NULL;
	novo->abaixo = NULL;
	novo->valor = 0;
	strcpy(novo->nome, "");
	return novo;
}


void defineMatriz(TCelula **c, int linha, int coluna){
	if(*c == NULL){
		int lin,col;
		TCelula *linhaAtual = NULL, *colunaAtual = NULL;
		TCelula *colunaAux = NULL;
		
		*c = alocaCelula();
		linhaAtual = *c;

		
		for(lin=0; lin < linha; lin++){
			colunaAtual = linhaAtual;
			
			for(col=1; col < coluna; col++){
				colunaAtual->dir = alocaCelula();
				colunaAtual = colunaAtual->dir;
				
				if(colunaAux != NULL)	{
					colunaAux->abaixo = colunaAtual;
					colunaAux = colunaAux->dir;	
				}
				
			}
			
			colunaAux = linhaAtual->dir;
			
			if(lin < (linha - 1)) 
			   linhaAtual->abaixo = alocaCelula();
			
			linhaAtual = linhaAtual->abaixo;
		}
	}
}


void atualizaCelula(TCelula **c, int linha, int coluna, int valor){
	TCelula *atual = *c;
	int lin = 0;
	int col = 0;
	
	while(lin < linha){
		lin++;
		atual = atual->abaixo;
	}
	
	while(col < coluna){
		col++;
		atual = atual->dir;
	}
	
	atual->valor = valor;
}


TCelula *localizaCelula(TCelula *c, int linha, int coluna){
	TCelula *atual = c;
	int lin = 0, col = 0;
	
	while(lin < linha){
		atual = atual->abaixo;
		lin++;
	}
	
	while(col < coluna){
		atual = atual->dir;
		col++;
	}
	return atual;
}


int obterValor(TCelula *c){
	return c->valor;
}


void adicionarLinha(TCelula **c){
	TCelula *atual, *novo, *ultimo;
	
	if((*c) != NULL){

	   atual = (*c);
	   while(atual->abaixo != NULL){
	    	atual = atual->abaixo;
	   }
	   
	   ultimo = NULL;
	   
	   while(atual != NULL){
	   		novo = alocaCelula();
			
			if(ultimo != NULL){
				ultimo->dir = novo;
			}
			
			atual->abaixo = novo;
			
			ultimo = novo;
			
			atual = atual->dir;
					
	   }
	   
    }
	
	printf("\n\nLinha INSERIDA com SUCESSO!!!");
	
}


void adicionarColuna(TCelula **c){
	TCelula *atual, *novo, *ultimo;
	
	if((*c) != NULL){
		atual = (*c);
		
		while(atual->dir != NULL){
			atual = atual->dir;
		}
		
		ultimo = NULL;
		
		while(atual != NULL){
	   		novo = alocaCelula();
			
			if(ultimo != NULL){
				ultimo->abaixo = novo;
			}
			
			atual->dir = novo;
			
			ultimo = novo;
			
			atual = atual->abaixo;
			
		}
		
    }
    
    printf("\n\nColuna INSERIDA com SUCESSO!!!");
}


void exibeMatriz(TCelula *c){
	system("CLS");
	printf("=====| EXIBE MATRIZ |=====\n\n");
	
	TCelula *atual;
	TCelula *proxima = c;
	
	while(proxima != NULL){
		atual = proxima;
		while (atual != NULL)	{
			printf("%d ", atual->valor);
			atual = atual->dir;
		}
		printf("\n");
		proxima = proxima->abaixo;
	}
	
	printf("\n\n");
	system("PAUSE");
}


void exibeMatrizNome(TCelula *c){
	system("CLS");
	printf("=====| EXIBE MATRIZ |=====\n\n");
	
	TCelula *atual;
	TCelula *proxima = c;
	
	while(proxima != NULL){
		atual = proxima;
		while (atual != NULL)	{
			printf("%s ", atual->nome);
			atual = atual->dir;
		}
		printf("\n");
		proxima = proxima->abaixo;
	}
	
	printf("\n\n");
	system("PAUSE");
}


int menu(){
	int opcao;
	system("CLS");
	printf("=====| MENU |======\n\n");
	printf("0 - Sair (Encerrar Aplicacao).\n");
	printf("1 - Inserir NOVO usuario.\n");
	printf("2 - Registrar amizade entre usuarios.\n");
	printf("3 - Indicar novas amizades para usuarios.\n\n");
	printf("Informe OPCAO desejada: ");
	scanf("%d", &opcao);
	
	if((opcao > 3) || (opcao < 0)){
		printf("\n\nERRO:\nOPCAO invalida. Tente novamente.\n\n");
		system("PAUSE");
	}
	
	return opcao;
}


void adionarUsuario(TCelula *usuarios, TCelula *relacionamentos, int *qtdUsuarios) {
	string nome;

    limparBuffer();

	printf("Digite o nome do usuario: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

	adicionarLinha(&usuarios);

	strcpy(localizaCelula(usuarios, *qtdUsuarios, 0)->nome, nome);

	adicionarLinha(&relacionamentos);
	adicionarColuna(&relacionamentos);

	(*qtdUsuarios)++;
}


void defineAmizade(TCelula *relacionamentos, int iUsuario1, int iUsuario2) {
	localizaCelula(relacionamentos, iUsuario1, iUsuario2)->valor = 1;
	localizaCelula(relacionamentos, iUsuario2, iUsuario1)->valor = 1;
}


void registrarAmizade(TCelula *usuarios, TCelula *relacionamentos) {
	TCelula *usuarioAtual = usuarios;
	int iUsuario = 0, iUsuario1, iUsuario2;

	while (usuarioAtual != NULL) {
		printf("%d - %s\n", iUsuario, usuarioAtual->nome);
		iUsuario++;
		usuarioAtual = usuarioAtual->abaixo;
	}

	printf("Digite o index do primeiro usuario: ");
	scanf("%d", &iUsuario1);
	printf("Digite o index do segundo usuario: ");
	scanf("%d", &iUsuario2);

	defineAmizade(relacionamentos, iUsuario1, iUsuario2);

	printf("Amizade adiciondaa!");

	system("pause");
}


void indicarAmizades(TCelula *usuarios, TCelula *relacionamentos, int qtdUsuarios) { 
	TCelula *recomendacoes = NULL;
	TCelula *linhaAtual, *colunaAtual, *colunaAtualAux, *usuarioAtual;

	int i, j, k;

	defineMatriz(&recomendacoes, qtdUsuarios, qtdUsuarios);

	linhaAtual = relacionamentos;
	for (i = 0; i < qtdUsuarios; i++) {
		colunaAtual = linhaAtual;
		for (j = 0; j < qtdUsuarios; j++) {
			colunaAtualAux = linhaAtual;
			if (colunaAtual->valor == 1) {
				for (k = 0; k < qtdUsuarios; k++) {
					if (j != k && colunaAtualAux->valor == 1) {
						localizaCelula(recomendacoes, k, j)->valor++;
					}
					colunaAtualAux = colunaAtualAux->dir;
				}
			}
			colunaAtual = colunaAtual->dir;
		}
		linhaAtual = linhaAtual->abaixo;
	}

	usuarioAtual = usuarios;
	linhaAtual = recomendacoes;

	printf("Recomendações:\n\n");
	for (i = 0; i < qtdUsuarios; i++) {
		printf("%s:\n", usuarioAtual->nome);
		colunaAtual = linhaAtual;
		for (j = 0; j < qtdUsuarios; j++) {
			if (colunaAtual->valor >= 2) {
				if (localizaCelula(relacionamentos, i, j)->valor == 0) {
					printf("   %s\n", localizaCelula(usuarios, j, 0)->nome);
				}
			} 

			colunaAtual = colunaAtual->dir;
		}
		linhaAtual = linhaAtual->abaixo;
		usuarioAtual = usuarioAtual->abaixo;
	}

	system("pause");
}


int main(){
	int opcao, qtdUsuarios = 4;
	TCelula *relacionamentos, *usuarios;

	inicializaMatriz(&relacionamentos);
	inicializaMatriz(&usuarios);
	
	defineMatriz(&relacionamentos, qtdUsuarios, qtdUsuarios);
	defineMatriz(&usuarios, qtdUsuarios, 1);

	strcpy(localizaCelula(usuarios, 0, 0)->nome, "A");
	strcpy(localizaCelula(usuarios, 1, 0)->nome, "B");
	strcpy(localizaCelula(usuarios, 2, 0)->nome, "C");
	strcpy(localizaCelula(usuarios, 3, 0)->nome, "D");


	defineAmizade(relacionamentos, 0, 1);
	defineAmizade(relacionamentos, 0, 2);
	defineAmizade(relacionamentos, 1, 3);
	defineAmizade(relacionamentos, 2, 3);

	
	do{
		opcao = menu();
		switch(opcao){
			case 1:
				adionarUsuario(usuarios, relacionamentos, &qtdUsuarios);
				exibeMatrizNome(usuarios);
				break;
			case 2:
				registrarAmizade(usuarios, relacionamentos);
				break;
			case 3:
				indicarAmizades(usuarios, relacionamentos, qtdUsuarios);
				break;
			default:
				break;
		}
	} while(opcao != 0);

}
