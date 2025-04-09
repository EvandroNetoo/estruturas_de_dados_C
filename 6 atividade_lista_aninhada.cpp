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
#ifdef _WIN32
#include <windows.h>
#endif	


typedef char string[40];


typedef struct Disciplina {
	string nome;
	int carga_horaria;
	struct PreRequisito* pre_requisitos;
	struct Disciplina* ante;
	struct Disciplina* prox;
} Disciplina;


typedef struct PreRequisito {
	Disciplina* disciplina;
	struct PreRequisito* ante;
	struct PreRequisito* prox;
} PreRequisito;


typedef struct Grade {
	Disciplina* disciplinas;
	int periodo;
	struct Grade* ante;
	struct Grade* prox;
} Grade;


typedef struct Curso {
	string nome;
	struct Curso* ante;
	struct Curso* prox;
	Grade* grades_curriculares;
} Curso;


typedef struct Lista {
	Curso* cursos;
	Disciplina* disciplinas;
} Lista;


int menu() {
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

	if ((opcao < 0) || (opcao > 13)) {
		printf("\n\n\nERRO: OPCAO invalida!\nTente Novamente\n\n");
		system("PAUSE");
	}
	return opcao;
}


void limpar_buffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
}


#define obter(lista, index, variavel) do { \
	variavel = lista; \
	int i = 1; \
	while (variavel != NULL && i != index) \
	{ \
		variavel = variavel->prox; \
		i++; \
	} \
} while (0)


#define listar(lista, tipo, formato, ...) do { \
	printf("\n"); \
	tipo *aux = (lista); \
	int i = 1; \
	if (aux == NULL) { \
		printf("Nenhum item cadastrado.\n"); \
	} \
	else { \
		while (aux != NULL) { \
			printf(formato, __VA_ARGS__); \
			aux = aux->prox; \
			i++; \
		} \
	} \
	printf("\n"); \
} while (0)


#define inserir(lista, novo, tipo) do { \
	if ((lista) == NULL) \
	{ \
		(lista) = (novo); \
	} \
	else \
	{ \
		tipo *aux = (lista); \
		while (aux->prox != NULL) \
		{ \
			aux = aux->prox; \
		} \
		aux->prox = (novo); \
		(novo)->ante = aux; \
	} \
} while (0)


#define excluir_por_referencia(lista, referencia) do { \
	if (referencia->ante == NULL ) { \
		lista = referencia->prox; \
	} \
	else if (referencia->prox == NULL) { \
		referencia->ante->prox = NULL; \
	} \
	else { \
		referencia->ante->prox = referencia->prox; \
		referencia->prox->ante = referencia->ante; \
	} \
	free(referencia); \
} while (0)


#define excluir_por_index(lista, index, tipo) do { \
	tipo *aux = lista; \
	int i = 1; \
	while (aux != NULL && i != index) { \
		aux = aux->prox; \
		i++; \
	} \
	if (referencia != NULL && i == index) { \
		excluir_por_referencia(lista, aux) \
	} \
} while (0)


#define excluir_lista(lista, tipo) do { \
	tipo *aux = lista; \
	tipo *temp = aux; \
	while (aux != NULL) { \
		temp = aux; \
		aux = aux->prox; \
		free(temp); \
	} \
	lista = NULL; \
} while (0)


void listar_disciplinas(Lista* lista) {
	printf("Listar disciplinas\n");
	listar(lista->disciplinas, Disciplina, "%d - %s (%d horas)\n", i, aux->nome, aux->carga_horaria);
	system("PAUSE");
}


Disciplina* inserir_disciplina(Lista* lista) {
	Disciplina* disciplina = (Disciplina*)malloc(sizeof(Disciplina));
	disciplina->ante = NULL;
	disciplina->prox = NULL;
	disciplina->pre_requisitos = NULL;

	printf("Registrar Disciplina\n\n");

	printf("Informe o nome da Disciplina: ");
	limpar_buffer();
	fgets(disciplina->nome, sizeof(disciplina->nome), stdin);
	disciplina->nome[strcspn(disciplina->nome, "\n")] = 0;

	printf("Informe a Carga Horaria da Disciplina: ");
	scanf("%d", &disciplina->carga_horaria);

	inserir(lista->disciplinas, disciplina, Disciplina);

	printf("\nDisicplina registrada com sucesso!\n\n");
	system("PAUSE");

	return disciplina;
}


void excluir_disciplina(Lista* lista) {
	int index;

	printf("Excluir Disciplina\n");
	listar(lista->disciplinas, Disciplina, "%d - %s (%d horas)\n", i, aux->nome, aux->carga_horaria);

	if (lista->disciplinas == NULL) {
		system("PAUSE");
		return;
	}

	printf("Informe o numero da Disciplina que deseja excluir: ");
	scanf("%d", &index);

	Disciplina* disciplina;
	obter(lista->disciplinas, index, disciplina);
	if (disciplina == NULL) {
		printf("\nDisciplina não encontrada!\n\n");
		system("PAUSE");
		return;
	}

	excluir_lista(disciplina->pre_requisitos, PreRequisito);

	excluir_por_referencia(lista->disciplinas, disciplina);

	printf("\nDisciplina excluída com sucesso!\n\n");
	system("PAUSE");
}


void listar_cursos(Lista* lista) {
	printf("Listar Cursos\n");
	listar(lista->cursos, Curso, "%d - %s\n", i, aux->nome);
	system("PAUSE");
}


void inserir_curso(Lista* lista) {
	Curso* curso = (Curso*)malloc(sizeof(Curso));
	curso->ante = NULL;
	curso->prox = NULL;
	curso->grades_curriculares = NULL;

	printf("Registrar Curso\n\n");

	printf("Informe o nome do Curso: ");
	limpar_buffer();
	fgets(curso->nome, sizeof(curso->nome), stdin);
	curso->nome[strcspn(curso->nome, "\n")] = 0;

	inserir(lista->cursos, curso, Curso);

	printf("\nCurso registrado com sucesso!\n\n");
	system("PAUSE");
}


void excluir_curso(Lista* lista) {
	int index;

	printf("Excluir Curso\n");
	listar(lista->cursos, Curso, "%d - %s\n", i, aux->nome);

	printf("Informe o numero do Curso que deseja excluir: ");
	scanf("%d", &index);

	if (index < 1) {
		printf("Índice inválido!\n");
		system("PAUSE");
		return;
	}

	Curso* curso;
	obter(lista->cursos, index, curso);
	if (curso == NULL) {
		printf("Curso não encontrado!\n");
		system("PAUSE");
		return;
	}

	excluir_lista(curso->grades_curriculares, Grade);

	excluir_por_referencia(lista->cursos, curso);

	printf("\nCurso excluído com sucesso!\n\n");
	system("PAUSE");
}


void listar_pre_requisitos(Lista* lista) {
	int index;
	printf("Listar pre-Requisitos para disciplina\n");

	listar(lista->disciplinas, Disciplina, "%d - %s (%d horas)\n", i, aux->nome, aux->carga_horaria);
	printf("Informe o número da disciplina: ");
	scanf("%d", &index);

	Disciplina* disciplina;
	obter(lista->disciplinas, index, disciplina);
	if (disciplina == NULL) {
		printf("Disciplina não encontrada!\n");
		system("PAUSE");
		return;
	}

	printf("\nPre-Requisitos para %s (%d horas):\n", disciplina->nome, disciplina->carga_horaria);
	listar(disciplina->pre_requisitos, PreRequisito, "%s (%d horas)\n", aux->disciplina->nome, aux->disciplina->carga_horaria);

	system("PAUSE");
}


void inserir_pre_requisitos(Lista* lista) {
	int index;
	printf("Registrar pre-Requisitos para disciplina\n");

	listar(lista->disciplinas, Disciplina, "%d - %s (%d horas)\n", i, aux->nome, aux->carga_horaria);
	printf("Informe o número da disciplina que terá o pré requisito: ");
	scanf("%d", &index);

	Disciplina* disciplina;
	obter(lista->disciplinas, index, disciplina);
	if (disciplina == NULL) {
		printf("Disciplina não encontrada!\n");
		system("PAUSE");
		return;
	}

	int qtd_pre_requisitos, i;
	printf("Informe a quantidade de pre-Requisitos: ");
	scanf("%d", &qtd_pre_requisitos);
	for (i = 0; i < qtd_pre_requisitos; i++) {
		system("CLS");
		printf("Registrar Pre-Requisito para %s (%d horas)\n", disciplina->nome, disciplina->carga_horaria);

		PreRequisito* pre_requisito = (PreRequisito*)malloc(sizeof(PreRequisito));
		pre_requisito->ante = NULL;
		pre_requisito->prox = NULL;

		listar(lista->disciplinas, Disciplina, "%d - %s (%d horas)\n", i, aux->nome, aux->carga_horaria);
		printf("Informe o número da Disciplina: ");
		scanf("%d", &index);

		obter(lista->disciplinas, index, pre_requisito->disciplina);
		if (pre_requisito->disciplina == NULL) {
			printf("Disciplina não encontrada!\n");
			i--;
			system("PAUSE");
			return;
		}

		inserir(disciplina->pre_requisitos, pre_requisito, PreRequisito);

		printf("\nPre-Requisito registrado com sucesso!\n\n");
		system("PAUSE");
	}
}


void excluir_pre_requisito(Lista* lista) {
	int index;
	printf("Registrar pre-Requisitos para disciplina\n");

	listar(lista->disciplinas, Disciplina, "%d - %s (%d horas)\n", i, aux->nome, aux->carga_horaria);
	printf("Informe o número da disciplina que terá o pré requisito: ");
	scanf("%d", &index);

	Disciplina* disciplina;
	obter(lista->disciplinas, index, disciplina);
	if (disciplina == NULL) {
		printf("Disciplina não encontrada!\n");
		system("PAUSE");
		return;
	}

	listar(disciplina->pre_requisitos, PreRequisito, "%d - %s (%d horas)\n", i, aux->disciplina->nome, aux->disciplina->carga_horaria);
	printf("Informe o número do pré requisito: ");
	scanf("%d", &index);

	PreRequisito* pre_requisito;
	obter(disciplina->pre_requisitos, index, pre_requisito);
	if (pre_requisito == NULL) {
		printf("Pré requisito não encontrado!\n");
		system("PAUSE");
		return;
	}

	excluir_por_referencia(disciplina->pre_requisitos, pre_requisito);

	printf("\nPre-Requisito excluído com sucesso!\n\n");
	system("PAUSE");
}


void listar_grades_curriculares(Lista* lista) {
	printf("Listar grrades curriculares de curso\n");

	int index;
	listar(lista->cursos, Curso, "%d - %s\n", i, aux->nome);
	printf("Informe o número do curso: ");
	scanf("%d", &index);

	Curso* curso;
	obter(lista->cursos, index, curso);
	if (curso == NULL) {
		printf("Curso não encontrado!\n");
		system("PAUSE");
		return;
	}

	printf("\nGrade Curricular do Curso %s:\n", curso->nome);
	Grade* grade = curso->grades_curriculares;
	while (grade != NULL) {
		printf("Período: %d\n", grade->periodo);
		listar(grade->disciplinas, Disciplina, "    %d - %s (%d horas)\n", i, aux->nome, aux->carga_horaria);
		grade = grade->prox;
	}

	system("PAUSE");
}


void inserir_grade_curricular(Lista* lista) {
	printf("Registrar Grade Curricular de Curso\n");

	int index;
	listar(lista->cursos, Curso, "%d - %s\n", i, aux->nome);
	printf("Informe o número do curso: ");
	scanf("%d", &index);

	Curso* curso;
	obter(lista->cursos, index, curso);
	if (curso == NULL) {
		printf("Curso não encontrado!\n");
		system("PAUSE");
		return;
	}

	Grade* grade = (Grade*)malloc(sizeof(Grade));
	grade->ante = NULL;
	grade->prox = NULL;

	printf("Informe o período da grade curricular: ");
	scanf("%d", &grade->periodo);

	int qtd_disciplinas, i;
	printf("Informe a quantidade de disciplinas: ");
	scanf("%d", &qtd_disciplinas);
	for (i = 0; i < qtd_disciplinas; i++) {
		system("CLS");
		printf("Registrar Disciplina para o Período %d do curso %s\n", grade->periodo, curso->nome);

		Disciplina* disciplina;

		listar(lista->disciplinas, Disciplina, "%d - %s (%d horas)\n", i, aux->nome, aux->carga_horaria);
		printf("Informe o número da Disciplina: ");
		scanf("%d", &index);

		obter(lista->disciplinas, index, disciplina);
		if (disciplina == NULL) {
			printf("Disciplina não encontrada!\n");
			i--;
			system("PAUSE");
			return;
		}

		inserir(grade->disciplinas, disciplina, Disciplina);

		printf("\nDisciplina registrada com sucesso!\n\n");
		system("PAUSE");
	}
}


void excluir_grade_curricular(Lista* lista) {
	printf("Excluir grade curricular de curso\n");

	listar(lista->cursos, Curso, "%d - %s\n", i, aux->nome);

	int index;
	printf("Informe o número do curso: ");
	scanf("%d", &index);

	Curso* curso;
	obter(lista->cursos, index, curso);
	if (curso == NULL) {
		printf("Curso não encontrado!\n");
		system("PAUSE");
		return;
	}

	listar(curso->grades_curriculares, Grade, "%d - Período %d\n", i, aux->periodo);

	printf("Informe o número do período que deseja excluir: ");
	scanf("%d", &index);

	Grade* grade;
	obter(curso->grades_curriculares, index, grade);
	if (grade == NULL) {
		printf("Período não encontrado!\n");
		system("PAUSE");
		return;
	}

	excluir_por_referencia(curso->grades_curriculares, grade);

	printf("\nPeríodo excluído com sucesso!\n\n");
}


int main() {
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
#endif

	int opcao;
	Lista* lista = (Lista*)malloc(sizeof(Lista));
	lista->cursos = NULL;
	lista->disciplinas = NULL;
	
	do {
		opcao = menu();
		system("CLS");
		switch (opcao) {
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
				listar_pre_requisitos(lista);
				break;
			case 8:
				inserir_pre_requisitos(lista);
				break;
			case 9:
				excluir_pre_requisito(lista);
				break;
			case 10:
				listar_grades_curriculares(lista);
				break;
			case 11:
				inserir_grade_curricular(lista);
				break;
			case 12:
				excluir_grade_curricular(lista);
				break;
		}
	} while (opcao != 0);

	return 0;
}
