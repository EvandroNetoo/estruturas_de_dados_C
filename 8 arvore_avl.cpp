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


No* balanceamento_LL(No* a) {
    printf("LL\n");
    No* b = a->esq;
    a->esq = b->dir;
    b->dir = a;

    if (b->bal == 0) {
        a->bal = 1;
        b->bal = -1;
    }
    else {
        a->bal = 0;
        b->bal = 0;
    }

    return b;
}

No* balanceamento_RR(No* a) {
    printf("RR\n");
    No* b = a->dir;
    a->dir = b->esq;
    b->esq = a;

    if (b->bal == 0) {
        a->bal = -1;
        b->bal = 1;
    }
    else {
        a->bal = 0;
        b->bal = 0;
    }

    return b;
}

No* balanceamento_LR(No* a) {
    printf("LR\n");
    No* b = a->esq;
    No* c = b->dir;
    b->dir = c->esq;
    c->esq = b;
    a->esq = c->dir;
    c->dir = a;
    if (c->bal == +1) a->bal = -1; else a->bal = 0;
    if (c->bal == -1) b->bal = +1; else b->bal = 0;
    c->bal = 0;
    return c;
}

No* balanceamento_RL(No* a) {
    printf("RL\n");
    No* b = a->dir;
    No* c = b->esq;
    b->esq = c->dir;
    c->dir = b;
    a->dir = c->esq;
    c->esq = a;
    if (c->bal == -1) a->bal = +1; else a->bal = 0;
    if (c->bal == +1) b->bal = -1; else b->bal = 0;
    c->bal = 0;
    return c;
}

No* balancear_avl(No* a, int balanceamento_a, int balanceamento_b) {
    if (balanceamento_a == 2 && balanceamento_b >= 0) return balanceamento_LL(a);
    if (balanceamento_a == -2 && balanceamento_b <= 0) return balanceamento_RR(a);
    if (balanceamento_a == 2 && balanceamento_b == -1) return balanceamento_LR(a);
    if (balanceamento_a == -2 && balanceamento_b == 1) return balanceamento_RL(a);
    return NULL;
}

void inserir_avl(No** raiz, int valor, bool* cresceu) {
    if (*raiz == NULL) {
        (*raiz) = criar_no(valor);
        *cresceu = true;
    }
    else if (valor < (*raiz)->valor) {
        inserir_avl(&(*raiz)->esq, valor, cresceu);
        if (*cresceu) (*raiz)->bal++;
        if ((*raiz)->bal == 0) *cresceu = false;
        if ((*raiz)->bal != -2 && (*raiz)->bal != 2) return;
        (*raiz) = balancear_avl(*raiz, (*raiz)->bal, (*raiz)->esq->bal);
        *cresceu = false;
    }
    else if (valor >= (*raiz)->valor) {
        inserir_avl(&(*raiz)->dir, valor, cresceu);
        if (*cresceu) (*raiz)->bal--;
        if ((*raiz)->bal == 0) *cresceu = false;
        if ((*raiz)->bal != -2 && (*raiz)->bal != 2) return;
        (*raiz) = balancear_avl(*raiz, (*raiz)->bal, (*raiz)->dir->bal);
        *cresceu = false;
    }
}

No* balanceL(No* p, bool* h) {
    switch (p->bal) {
        case +1:
            p->bal = 0; break;
        case 0:
            p->bal = -1; *h = false; break;
        case -1: {
            No* b = p->dir;
            if (b->bal <= 0) {
                // RR
                p->dir = b->esq;
                b->esq = p;
                if (b->bal == 0) {
                    p->bal = -1; b->bal = +1; *h = false;
                } else {
                    p->bal = b->bal = 0;
                }
                p = b;
            } else {
                // RL
                No* c = b->esq;
                b->esq = c->dir;
                c->dir = b;
                p->dir = c->esq;
                c->esq = p;
                if (c->bal == -1) p->bal = +1; else p->bal = 0;
                if (c->bal == +1) b->bal = -1; else b->bal = 0;
                p = c;
                p->bal = 0;
            }
            break;
        }
    }
    return p;
}

No* balanceR(No* p, bool* h) {
    switch (p->bal) {
        case -1:
            p->bal = 0; break;
        case 0:
            p->bal = +1; *h = false; break;
        case +1: {
            No* b = p->esq;
            if (b->bal >= 0) {
                // LL
                p->esq = b->dir;
                b->dir = p;
                if (b->bal == 0) {
                    p->bal = +1; b->bal = -1; *h = false;
                } else {
                    p->bal = b->bal = 0;
                }
                p = b;
            } else {
                // LR
                No* c = b->dir;
                b->dir = c->esq;
                c->esq = b;
                p->esq = c->dir;
                c->dir = p;
                if (c->bal == +1) p->bal = -1; else p->bal = 0;
                if (c->bal == -1) b->bal = +1; else b->bal = 0;
                p = c;
                p->bal = 0;
            }
            break;
        }
    }
    return p;
}

void DelMin(No** q, No** r, bool* h) {
    if ((*r)->esq != NULL) {
        DelMin(q, &(*r)->esq, h);
        if (*h) {
            *r = balanceL(*r, h);
        }
    }
    else {
        (*q)->valor = (*r)->valor;
        No* temp = *r;
        *r = (*r)->dir;
        *h = true;
        free(temp);
    }
}

No* remover_avl(No* raiz, int x, bool* h) {
    if (raiz == NULL) {
        return NULL;
    }

    if (x < raiz->valor) {
        raiz->esq = remover_avl(raiz->esq, x, h);
        if (*h) {
            raiz = balanceL(raiz, h);   // subárvore esquerda diminuiu
        }
    }
    else if (x > raiz->valor) {
        raiz->dir = remover_avl(raiz->dir, x, h);
        if (*h) {
            raiz = balanceR(raiz, h);   // subárvore direita diminuiu
        }
    }
    else {
        // achou p->valor == x
        No* q = raiz;
        if (raiz->dir == NULL) {
            raiz = raiz->esq;
            *h = true;
        }
        else if (raiz->esq == NULL) {
            raiz = raiz->dir;
            *h = true;
        }
        else {
            // dois filhos: troca com sucessor mínimo da direita
            DelMin(&q, &raiz->dir, h);
            if (*h) {
                raiz = balanceR(raiz, h);
            }
        }
    }
    return raiz;
}

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


int main() {
    No* raiz = NULL;
    bool h;

    int opcao, valor;
    do {
        h = false;
        opcao = menu();
        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                inserir_avl(&raiz, valor, &h);
                break;
            case 2:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                raiz = remover_avl(raiz, valor, &h);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
            }
        printf("\n");
        imprime_arvore(raiz);
        printf("\n");
    } while (opcao != 0);

    return 0;
}