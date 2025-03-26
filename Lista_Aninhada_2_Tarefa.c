/* Lista Aninhada 2 
   26-03-2025
   Tarefa Avaliativa
   
   Trabalho em Dupla:
   
   (1) Evandro
   (2).....................................................
   
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef char string[40];

typedef struct Disciplina {
	string nome;
	int carga_horaria;
	struct Disciplina *ante;
	struct Disciplina *prox;
	struct aPreRequisito *preRequisitos;	
} Disciplina;

typedef struct PreRequisito {
	Disciplina disciplina;
	struct PreRequisito *ante;
	struct PreRequisito *prox;
} PreRequisito;

typedef struct Grade {
	Disciplina *disciplina;
	int periodo;
	struct Grade *ante;
	struct Grade *prox;	
} Grade;

typedef struct Curso {
	string nome;
	struct Curso *ante;
	struct Curso *prox;
	Grade *gradeCurricular;
} Curso;

typedef struct Lista {
	Curso *cursos;
	Disciplina *disciplinas;
} Lista;



int menu(){
	int opcao;
	system("CLS");
	printf("=======| MENU |=======\n\n");
	printf("0 - SAIR (Encerrar Aplicacao).\n\n");
	printf("1 - Inserir DISCIPLINA.\n");
	printf("2 - Excluir DISCIPLINA.\n\n");
	printf("3 - Inserir CURSO.\n");
	printf("4 - Excluir CURSO.\n\n");
	printf("5 - Registrar PRE-REQUISITO para DISCIPLINA.\n");
	printf("6 - Excluir PRE-REQUISITO de DISCIPLINA.\n\n");
	printf("7 - Registrar GRADE CURRICULAR para CURSO.\n");
	printf("8 - Excluir item da GRADE CURRICULAR de CURSO.\n\n");
	
	printf("Informe a OPCAO desejada: ");
	scanf("%d", &opcao);
	
	if((opcao < 0) || (opcao > 8)){
		printf("\n\n\nERRO: OPCAO invalida!\nTente Novamente\n\n");
		system("PAUSE");
	}
	return opcao;
}


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


#define inserir(lista, novo) do { \
    if ((lista) == NULL) { \
        (lista) = (novo); \
    } else { \
        typeof(lista) aux = (lista); \
        while (aux->prox != NULL) { \
            aux = aux->prox; \
        } \
        aux->prox = (novo); \
        (novo)->ante = aux; \
    } \
} while(0)




void inserir_disciplina(Lista *lista) {
	Disciplina *disciplina = (Disciplina *) malloc(sizeof(Disciplina));
	disciplina->ante = NULL;
	disciplina->prox = NULL;

	printf("Inserir Disciplina\n\n");

	printf("Informe o nome da Disciplina: ");
	limparBuffer();
	fgets(disciplina->nome, sizeof(disciplina->nome), stdin);
    disciplina->nome[strcspn(disciplina->nome, "\n")] = 0;

	printf("Informe a Carga Horaria da Disciplina: ");
	scanf("%d", &disciplina->carga_horaria);

	inserir(lista->disciplinas, disciplina);
}


void listar_disciplinas(Disciplina *disciplina) {
	int i = 1;
	if (disciplina == NULL) {
		printf("Nenhuma Disciplina Cadastrada.\n\n");
	} else {
		while(disciplina != NULL) {
			printf("%d - %s - %dh\n", i++, disciplina->nome, disciplina->carga_horaria);
			disciplina = disciplina->prox;
		}
	}
}

void excluir_dicisplina(Lista *lista) {
	printf("Excluir Disciplina\n\n");

	listar_disciplinas(lista->disciplinas);

	system("PAUSE");
}


int main() {
	int opcao;
	Lista lista;

	if (lista.disciplinas == NULL) {
		printf("Nenhuma Disciplina Cadastrada.\n\n");
	}
	if (lista.cursos == NULL) {
		printf("Nenhum Curso Cadastrado.\n\n");
	}

	do {
		opcao = menu();
		system("CLS");
		switch (opcao) {
			case 1:
				inserir_disciplina(&lista);
				break;
			case 2:
				excluir_dicisplina(&lista);
				break;
			case 3:
				printf("Inserir Cursos\n");
				break;
			case 4:
				printf("Excluir Cursos\n");
				break;
			case 5:
				printf("Registrar Pre-Requisitos para Disciplinas\n");
				break;
			case 6:
				printf("Excluir Pre-Requisitos de Disciplinas\n");
				break;
			case 7:
				printf("Registrar Grade Curricular para Cursos\n");
				break;
			case 8:
				printf("Excluir item da Grade Curricular de Cursos\n");
				break;
		}
	} while (opcao != 0);
	

	return 0;
}
