#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char string[40];


typedef struct tipoAtor {
    string nome;
    struct tipoAtor* prox;
} TAtor;


typedef struct tipoElenco {
    TAtor* ator;
    struct tipoElenco* prox;
} TElenco;


typedef struct tipoFilme {
    string titulo;
    int ano_producao;
    TElenco* elenco;
    struct tipoFilme* ante;
    struct tipoFilme* prox;
} TFilme;


typedef struct tipoListas {
    TFilme* filmes;
    TAtor* atores;
} TListas;


void inicializa(TListas* L) {
    L->atores = NULL;
    L->filmes = NULL;
}


int menu() {
    int opcao;
    printf("\n\n\n=====| MENU |======\n\n");
    printf("0 - Sair (Encerrar Aplicacao).\n\n");
    printf("1 - Cadastro de ATORES.\n");
    printf("2 - Cadastro de FILMES.\n");
    printf("3 - Cadastro de ELENCOS.\n\n");
    printf("4 - Listagem de ATORES.\n");
    printf("5 - Listagem de FILMES.\n\n");
    printf("6 - Exclusão de FILMES.\n");
    printf("7 - Exclusão de ATORES.\n");
    printf("8 - Exclusão de ELENCO.\n\n");
    printf("informe OPCAO desejada: ");
    scanf("%d", &opcao);

    if (opcao < 0 || opcao > 8) {
        printf("\n\n\nERRO:\nOPCAO invalida.\n\n");
        system("PAUSE");
    }

    return opcao;
}


void cadastro_ator(TListas* L) {
    TAtor* novo, * aux;

    novo = (TAtor*)malloc(sizeof(TAtor));

    printf("\n\n\n=====| CADASTRO DE ATOR |======\n\n");
    printf("Nome do Ator: ");
    fflush(stdin);
    gets(novo->nome);
    novo->prox = NULL;

    if (L->atores == NULL) {
        L->atores = novo;
    }
    else {
        aux = L->atores;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    printf("\n\n\nAtor Cadastrado com Sucesso.\n\n");
    system("PAUSE");
}


void cadastro_filme(TListas* L) {
    TFilme* novo, * aux;

    novo = (TFilme*)malloc(sizeof(TFilme));

    printf("\n\n\n=====| CADASTRO DE FILME |======\n\n");
    printf("Titulo do Filme: ");
    fflush(stdin);
    gets(novo->titulo);
    printf("Ano de Producao: ");
    scanf("%d", &novo->ano_producao);
    novo->elenco = NULL;
    novo->ante = NULL;
    novo->prox = NULL;

    if (L->filmes == NULL) {
        L->filmes = novo;
    }
    else {
        aux = L->filmes;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->ante = aux;
    }

    printf("\n\n\nFilme Cadastrado com Sucesso.\n\n");
    system("PAUSE");
}


void cadastro_elenco(TListas* L) {
    TElenco* novo, * aux;
    TFilme* filme;
    TAtor* ator;
    string nome;

    novo = (TElenco*)malloc(sizeof(TElenco));

    printf("\n\n\n=====| CADASTRO DE ELENCO |======\n\n");
    printf("Titulo do Filme: ");
    fflush(stdin);
    gets(nome);

    filme = L->filmes;
    while (filme != NULL && strcmp(filme->titulo, nome) != 0) {
        filme = filme->prox;
    }

    if (filme == NULL) {
        printf("\n\n\nERRO:\nFilme nao encontrado.\n\n");
        system("PAUSE");
        return;
    }

    printf("Nome do Ator: ");
    fflush(stdin);
    gets(nome);

    ator = L->atores;
    while (ator != NULL && strcmp(ator->nome, nome) != 0) {
        ator = ator->prox;
    }

    if (ator == NULL) {
        printf("\n\n\nERRO:\nAtor nao encontrado.\n\n");
        system("PAUSE");
        return;
    }

    novo->ator = ator;
    novo->prox = NULL;

    if (filme->elenco == NULL) {
        filme->elenco = novo;
    }
    else {
        aux = filme->elenco;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    printf("\n\n\nElenco Cadastrado com Sucesso.\n\n");
    system("PAUSE");
}


void listagem_atores(TListas* L) {
    TAtor* aux;

    printf("\n\n\n=====| LISTAGEM DE ATORES |======\n\n");

    if (L->atores == NULL) {
        printf("Nenhum Ator Cadastrado.\n\n");
    }
    else {
        aux = L->atores;
        while (aux != NULL) {
            printf("Nome do Ator: %s\n", aux->nome);
            aux = aux->prox;
        }
    }

    system("PAUSE");
}


void listagem_filmes(TListas* L) {
    TFilme* aux;
    TElenco* elenco;

    printf("\n\n\n=====| LISTAGEM DE FILMES |======\n\n");

    if (L->filmes == NULL) {
        printf("Nenhum Filme Cadastrado.\n\n");
    }
    else {
        aux = L->filmes;
        while (aux != NULL) {
            printf("Titulo do Filme: %s\n", aux->titulo);
            printf("Ano de Producao: %d\n", aux->ano_producao);
            printf("Elenco:\n");
            elenco = aux->elenco;
            while (elenco != NULL) {
                printf("Nome do Ator: %s\n", elenco->ator->nome);
                elenco = elenco->prox;
            }
            aux = aux->prox;
        }
    }

    system("PAUSE");
}


void exclusao_filme(TListas* L) {
    TFilme* filme;
    string nome;
    TElenco* elenco_atual, * elenco_prox;

    printf("\n\n\n=====| EXCLUSAO DE FILME |======\n\n");
    printf("Titulo do Filme: ");
    fflush(stdin);
    gets(nome);

    filme = L->filmes;
    while (filme != NULL && strcmp(filme->titulo, nome) != 0) {
        filme = filme->prox;
    }

    if (filme == NULL) {
        printf("\n\n\nERRO:\nFilme nao encontrado.\n\n");
        system("PAUSE");
        return;
    }

    if (filme->ante == NULL) {
        L->filmes = filme->prox;
    }
    else {
        filme->ante->prox = filme->prox;
    }

    if (filme->prox != NULL) {
        filme->prox->ante = filme->ante;
    }

    elenco_atual = filme->elenco;
    while (elenco_atual != NULL) {
        elenco_prox = elenco_atual->prox;
        free(elenco_atual);
        elenco_atual = elenco_prox;
    }

    free(filme);

    printf("\n\n\nFilme Excluido com Sucesso.\n\n");
    system("PAUSE");
}

void excluir_ator(TListas* L) {
    TAtor* ator_atual, * ator_prox;
    TFilme* filme_atual, * filme_prox;
    TElenco* elenco_atual, * elenco_prox;
    string nome;

    printf("\n\n\n=====| EXCLUSAO DE ATOR |======\n\n");
    printf("Nome do Ator: ");
    fflush(stdin);
    gets(nome);

    ator_atual = L->atores;
    while (ator_atual != NULL && strcmp(ator_atual->nome, nome) != 0) {
        ator_atual = ator_atual->prox;
    }

    if (ator_atual == NULL) {
        printf("\n\n\nERRO:\nAtor nao encontrado.\n\n");
        system("PAUSE");
        return;
    }

    filme_atual = L->filmes;
    while (filme_atual != NULL) {
        elenco_atual = filme_atual->elenco;
        while (elenco_atual != NULL && elenco_atual->ator != ator_atual) {
            elenco_atual = elenco_atual->prox;
        }

        if (elenco_atual != NULL) {
            if (elenco_atual == filme_atual->elenco) {
                filme_atual->elenco = elenco_atual->prox;
            }
            else {
                elenco_atual->prox = elenco_atual->prox;
            }

            free(elenco_atual);
        }

        filme_atual = filme_atual->prox;
    }

    if (ator_atual == L->atores) {
        L->atores = ator_atual->prox;
    }
    else {
        ator_prox = L->atores;
        while (ator_prox->prox != ator_atual) {
            ator_prox = ator_prox->prox;
        }
        ator_prox->prox = ator_atual->prox;
    }

    free(ator_atual);

    printf("\n\n\nAtor Excluido com Sucesso.\n\n");
    system("PAUSE");
}


void excluir_elenco(TListas* L) {
    TElenco* elenco_atual, * elenco_prox;
    TFilme* filme_atual;
    string nome;

    printf("\n\n\n=====| EXCLUSAO DE ELENCO |======\n\n");
    printf("Titulo do Filme: ");
    fflush(stdin);
    gets(nome);

    filme_atual = L->filmes;
    while (filme_atual != NULL && strcmp(filme_atual->titulo, nome) != 0) {
        filme_atual = filme_atual->prox;
    }

    if (filme_atual == NULL) {
        printf("\n\n\nERRO:\nFilme nao encontrado.\n\n");
        system("PAUSE");
        return;
    }

    elenco_atual = filme_atual->elenco;
    while (elenco_atual != NULL) {
        elenco_prox = elenco_atual->prox;
        free(elenco_atual);
        elenco_atual = elenco_prox;
    }

    filme_atual->elenco = NULL;

    printf("\n\n\nElenco Excluido com Sucesso.\n\n");
    system("PAUSE");
}


int main() {
    int opcao;
    TListas lista;

    inicializa(&lista);

    do {
        opcao = menu();
        switch (opcao) {
        case 1:
            cadastro_ator(&lista);
            break;
        case 2:
            cadastro_filme(&lista);
            break;
        case 3:
            cadastro_elenco(&lista);
            break;
        case 4:
            listagem_atores(&lista);
            break;
        case 5:
            listagem_filmes(&lista);
            break;
        case 6:
            exclusao_filme(&lista);
            break;
        case 7:
            excluir_ator(&lista);
            break;
        case 8:
            excluir_elenco(&lista);
            break;
        }
    } while (opcao != 0);

    return 0;
}
