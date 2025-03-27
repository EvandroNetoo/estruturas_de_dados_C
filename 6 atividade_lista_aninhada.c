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

typedef struct Disciplina
{
	string nome;
	int carga_horaria;
	struct PreRequisito *pre_requisitos;
	struct Disciplina *ante;
	struct Disciplina *prox;
} Disciplina;

typedef struct PreRequisito
{
	Disciplina *disciplina;
	struct PreRequisito *ante;
	struct PreRequisito *prox;
} PreRequisito;

typedef struct Grade
{
	Disciplina *disciplina;
	int periodo;
	struct Grade *ante;
	struct Grade *prox;
} Grade;

typedef struct Curso
{
	string nome;
	struct Curso *ante;
	struct Curso *prox;
	Grade *grade_curricular;
} Curso;

typedef struct Lista
{
	Curso *cursos;
	Disciplina *disciplinas;
} Lista;

int menu()
{
	int opcao;
	system("CLS");
	printf("=======| MENU |=======\n\n");
	printf("0 - SAIR (Encerrar Aplicacao).\n\n");

	printf("1 - Listar DISCIPLINAS.\n");
	printf("2 - Registrar DISCIPLINA.\n");
	printf("3 - Excluir DISCIPLINA.\n\n");

	printf("4 - Listar CURSOS.\n");
	printf("5 - Registrar CURSO.\n");
	printf("6 - Excluir CURSO.\n\n");

	printf("7 - Listar PRE-REQUISITOS para DISCIPLINA.\n");
	printf("8 - Registrar PRE-REQUISITO para DISCIPLINA.\n");
	printf("9 - Excluir PRE-REQUISITOS de DISCIPLINA.\n\n");

	printf("10 - Listar GRADES CURRICULARES para CURSO.\n");
	printf("11 - Registrar GRADE CURRICULAR para CURSO.\n");
	printf("12 - Excluir item da GRADE CURRICULAR de CURSO.\n\n");

	printf("Informe a OPCAO desejada: ");
	scanf("%d", &opcao);

	if ((opcao < 0) || (opcao > 12))
	{
		printf("\n\n\nERRO: OPCAO invalida!\nTente Novamente\n\n");
		system("PAUSE");
	}
	return opcao;
}

void limparBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
}

#define obter(lista, index, variavel)          \
	do                                         \
	{                                          \
		variavel = lista;                      \
		int i = 1;                             \
		while (variavel != NULL && i != index) \
		{                                      \
			variavel = variavel->prox;         \
			i++;                               \
		}                                      \
	} while (0)

#define listar(lista, tipo, formato, ...)          \
	do                                             \
	{                                              \
		tipo *aux = (lista);                       \
		int i = 1;                                 \
		if (aux == NULL)                           \
		{                                          \
			printf("Nenhum item cadastrado.\n");   \
		}                                          \
		else                                       \
		{                                          \
			while (aux != NULL)                    \
			{                                      \
				printf(formato, i++, __VA_ARGS__); \
				aux = aux->prox;                   \
			}                                      \
		}                                          \
	} while (0)

#define inserir(lista, novo, tipo)    \
	do                                \
	{                                 \
		if ((lista) == NULL)          \
		{                             \
			(lista) = (novo);         \
		}                             \
		else                          \
		{                             \
			tipo *aux = (lista);      \
			while (aux->prox != NULL) \
			{                         \
				aux = aux->prox;      \
			}                         \
			aux->prox = (novo);       \
			(novo)->ante = aux;       \
		}                             \
	} while (0)

#define excluir_por_referencia(lista, referencia)      \
	do                                                 \
	{                                                  \
		if (referencia->ante == NULL)                  \
		{                                              \
			lista = referencia->prox;                  \
		}                                              \
		else if (referencia->prox == NULL)             \
		{                                              \
			referencia->ante->prox = NULL;             \
		}                                              \
		else                                           \
		{                                              \
			referencia->ante->prox = referencia->prox; \
			referencia->prox->ante = referencia->ante; \
		}                                              \
		free(referencia);                              \
	} while (0)

#define excluir_por_index(lista, index, tipo)   \
	do                                          \
	{                                           \
		tipo *aux = lista;                      \
		int i = 1;                              \
		while (aux != NULL && i != index)       \
		{                                       \
			aux = aux->prox;                    \
			i++;                                \
		}                                       \
		if (referencia != NULL && i == index)   \
		{                                       \
			excluir_por_referencia(lista, aux); \
		}                                       \
	} while (0)

#define excluir_lista(lista, tipo) \
	do                             \
	{                              \
		tipo *aux = lista;         \
		tipo *temp = aux;          \
		while (aux != NULL)        \
		{                          \
			temp = aux;            \
			aux = aux->prox;       \
			free(temp);            \
		}                          \
		lista = NULL;              \
	} while (0)

void listar_disciplinas(Lista *lista)
{
	printf("Listar disciplinas\n\n");
	listar(lista->disciplinas, Disciplina, "%d - %s (%d horas)\n", aux->nome, aux->carga_horaria);
	printf("\n");
	system("PAUSE");
}

void inserir_disciplina(Lista *lista)
{
	Disciplina *disciplina = (Disciplina *)malloc(sizeof(Disciplina));
	disciplina->ante = NULL;
	disciplina->prox = NULL;
	disciplina->pre_requisitos = NULL;

	printf("Registrar Disciplina\n\n");

	printf("Informe o nome da Disciplina: ");
	limparBuffer();
	fgets(disciplina->nome, sizeof(disciplina->nome), stdin);
	disciplina->nome[strcspn(disciplina->nome, "\n")] = 0;

	printf("Informe a Carga Horaria da Disciplina: ");
	scanf("%d", &disciplina->carga_horaria);

	inserir(lista->disciplinas, disciplina, Disciplina);

	printf("\nDisicplina registrada com sucesso!\n\n");
	system("PAUSE");
}

void excluir_disciplina(Lista *lista)
{
	int index;

	printf("Excluir Disciplina\n\n");
	listar(lista->disciplinas, Disciplina, "%d - %s (%d horas)\n", aux->nome, aux->carga_horaria);

	if (lista->disciplinas == NULL)
	{
		system("PAUSE");
		return;
	}

	printf("Informe o numero da Disciplina que deseja excluir: ");
	scanf("%d", &index);

	if (index < 1)
	{
		printf("Índice inválido!\n");
		system("PAUSE");
		return;
	}

	Disciplina *disciplina;
	obter(lista->disciplinas, index, disciplina);

	excluir_lista(disciplina->pre_requisitos, PreRequisito);

	excluir_por_referencia(lista->disciplinas, disciplina);

	printf("\nDisciplina excluída com sucesso!\n\n");
	system("PAUSE");
}

void listar_cursos(Lista *lista)
{
	printf("Listar Cursos\n\n");
	listar(lista->cursos, Curso, "%d - %s\n", aux->nome);
	printf("\n");
	system("PAUSE");
}

void inserir_curso(Lista *lista)
{
	Curso *curso = (Curso *)malloc(sizeof(Curso));
	curso->ante = NULL;
	curso->prox = NULL;
	curso->grade_curricular = NULL;

	printf("Registrar Curso\n\n");

	printf("Informe o nome do Curso: ");
	limparBuffer();
	fgets(curso->nome, sizeof(curso->nome), stdin);
	curso->nome[strcspn(curso->nome, "\n")] = 0;

	inserir(lista->cursos, curso, Curso);

	printf("\nCurso registrado com sucesso!\n\n");
	system("PAUSE");
}

void excluir_curso(Lista *lista)
{
	int index;

	printf("Excluir Curso\n\n");
	listar(lista->cursos, Curso, "%d - %s\n", aux->nome);

	printf("Informe o numero do Curso que deseja excluir: ");
	scanf("%d", &index);

	if (index < 1)
	{
		printf("Índice inválido!\n");
		system("PAUSE");
		return;
	}

	Curso *curso;
	obter(lista->cursos, index, curso);

	excluir_lista(curso->grade_curricular, Grade);

	excluir_por_referencia(lista->cursos, curso);

	printf("\nCurso excluído com sucesso!\n\n");
	system("PAUSE");
}


void listar_pre_requisitos(Lista *lista) {
	int index;
	printf("Listar Pre-Requisitos para Disciplina\n\n");

	listar(lista->disciplinas, Disciplina, "%d - %s (%d horas)\n", aux->nome, aux->carga_horaria);
	printf("Informe o número da Disciplina: ");
	scanf("%d", &index);
	
	Disciplina *disciplina;
	obter(lista->disciplinas, index, disciplina);

	printf("Pre-Requisitos para %s (%d horas)\n", disciplina->nome, disciplina->carga_horaria);
	listar(disciplina->pre_requisitos, PreRequisito, "%d - %s (%d horas)\n", aux->disciplina->nome, aux->disciplina->carga_horaria);

	printf("\n");
	system("PAUSE");
}


int main()
{
	int opcao;
	Lista *lista = (Lista *)malloc(sizeof(Lista));
	lista->cursos = NULL;
	lista->disciplinas = NULL;

	Disciplina calc1 = {"Calculo I", 60, NULL, NULL, NULL};

	Disciplina calc2 = {"Calculo II", 60, NULL, NULL, NULL};
	PreRequisito pre_calc2 = {&calc1, NULL, NULL};
	calc2.pre_requisitos = &pre_calc2;

	inserir(lista->disciplinas, &calc1, Disciplina);
	inserir(lista->disciplinas, &calc2, Disciplina);

	do
	{
		opcao = menu();
		system("CLS");
		switch (opcao)
		{
		case 1:
			listar_disciplinas(lista);
			break;
		case 2:
			inserir_disciplina(lista);
			break;
		case 3:
			excluir_disciplina(lista);
			break;
		case 4:
			listar_cursos(lista);
			break;
		case 5:
			inserir_curso(lista);
			break;
		case 6:
			excluir_curso(lista);
			break;
		case 7:
			printf("Listar Pre-Requisitos para Disciplina\n");
			break;
		case 8:
			printf("Registrar Pre-Requisitos para Disciplina\n");
			break;
		case 9:
			printf("Excluir Pre-Requisitos de Disciplina\n");
			break;
		case 10:
			printf("Listar Grades Curriculares para Curso\n");
			break;
		case 11:
			printf("Registrar Grade Curricular para Curso\n");
			break;
		case 12:
			printf("Excluir item da Grade Curricular de Cursos\n");
			break;
		}
	} while (opcao != 0);

	return 0;
}
