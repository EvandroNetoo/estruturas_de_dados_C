#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct No {
    int valor;
    int bal;
    struct No* esq;
    struct No* dir;
} No;

int menu() {
    int opcao;
    printf("Menu:\n");
    printf("1. Inserir elemento\n");
    printf("2. Excluir elemento\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

void listar_pre_ordem(No* raiz) {
    if (raiz != NULL) {
        printf("%d\n", raiz->valor);
        listar_pre_ordem(raiz->esq);
        listar_pre_ordem(raiz->dir);
    }
}

void listar_em_ordem(No* raiz) {
    if (raiz != NULL) {
        listar_em_ordem(raiz->esq);
        printf("%d\n", raiz->valor);
        listar_em_ordem(raiz->dir);
    }
}

void listar_pos_ordem(No* raiz) {
    if (raiz != NULL) {
        listar_pos_ordem(raiz->esq);
        listar_pos_ordem(raiz->dir);
        printf("%d\n", raiz->valor);
    }
}

void imprime_arvore(No* raiz, int nivel = 0) {
    if (raiz == NULL)
        return;

    imprime_arvore(raiz->dir, nivel + 1);

    for (int i = 0; i < nivel; i++)
        printf("        ");
    printf("%d (%d)\n", raiz->valor, raiz->bal);

    imprime_arvore(raiz->esq, nivel + 1);
}

struct No* criar_no(int valor) {
    struct No* novo_no = (No*)malloc(sizeof(No));
    novo_no->valor = valor;
    novo_no->bal = 0;
    novo_no->esq = NULL;
    novo_no->dir = NULL;
    return novo_no;
}

void inserir(No** raiz, int valor) {
    if (*raiz == NULL) {
        (*raiz) = criar_no(valor);
    }
    else if (valor < (*raiz)->valor) {
        inserir(&(*raiz)->esq, valor);
    }
    else if (valor >= (*raiz)->valor) {
        inserir(&(*raiz)->dir, valor);
    }
}

No* menor_no(No* raiz) {
    if (raiz->esq == NULL) {
        return raiz;
    }
    return menor_no(raiz->esq);
}

No* maior_no(No* raiz) {
    if (raiz->dir == NULL) {
        return raiz;
    }
    return maior_no(raiz->dir);
}

No* remover(No* raiz, int valor) {
    No* temp;
    if (raiz == NULL) return NULL;

    if (raiz->valor > valor) {
        raiz->esq = remover(raiz->esq, valor);
    }
    else if (raiz->valor < valor) {
        raiz->dir = remover(raiz->dir, valor);
    }
    else {
        if (raiz->dir == NULL) {
            temp = raiz->esq;
            free(raiz);
            return temp;
        }
        if (raiz->esq == NULL) {
            temp = raiz->dir;
            free(raiz);
            return temp;
        }

        temp = maior_no(raiz->esq);
        raiz->valor = temp->valor;
        raiz->esq = remover(raiz->esq, temp->valor);
    }
    return raiz;
}