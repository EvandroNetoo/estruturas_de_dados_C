#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define RUBRO true
#define NEGRA false


typedef struct No {
    int valor;
    int bal;
    bool cor;
    struct No* esq;
    struct No* dir;
} No;

int menu() {
    int opcao;
    printf("Menu:\n");
    printf("1. Inserir elemento\n");
    printf("2. Excluir elemento\n");
    printf("3. Listar elementos em ordem\n");
    printf("4. Listar elementos em pré-ordem\n");
    printf("5. Listar elementos em pós-ordem\n");
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


int altura(No* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    int altura_esquerda = altura(raiz->esq);
    int altura_direita = altura(raiz->dir);
    return (altura_esquerda > altura_direita ? altura_esquerda : altura_direita) + 1;
}

int fator_balanceamento(No* raiz) {
    return altura(raiz->esq) - altura(raiz->dir);
}

No* balanceamento_LL(No* a, bool* h) {
    printf("LL\n");
    No* b = a->esq;
    a->esq = b->dir;
    b->dir = a;

    if (b->bal == 0) {
        a->bal = 1;
        b->bal = -1;
        *h = false;
    }
    else {
        a->bal = 0;
        b->bal = 0;
        *h = false;
    }

    return b;
}

No* balanceamento_RR(No* a, bool* h) {
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

No* balanceamento_LR(No* a, bool* h) {
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

No* balanceamento_RL(No* a, bool* h) {
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

No* balancear_avl(No* a, int balanceamento_a, int balanceamento_b, bool* h) {
    if (balanceamento_a == 2 && balanceamento_b >= 0) return balanceamento_LL(a, h);
    if (balanceamento_a == -2 && balanceamento_b <= 0) return balanceamento_RR(a, h);
    if (balanceamento_a == 2 && balanceamento_b == -1) return balanceamento_LR(a, h);
    if (balanceamento_a == -2 && balanceamento_b == 1) return balanceamento_RL(a, h);
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
        (*raiz) = balancear_avl(*raiz, (*raiz)->bal, (*raiz)->esq->bal, cresceu);
        *cresceu = false;
    }
    else if (valor >= (*raiz)->valor) {
        inserir_avl(&(*raiz)->dir, valor, cresceu);
        if (*cresceu) (*raiz)->bal--;
        if ((*raiz)->bal == 0) *cresceu = false;
        if ((*raiz)->bal != -2 && (*raiz)->bal != 2) return;
        (*raiz) = balancear_avl(*raiz, (*raiz)->bal, (*raiz)->dir->bal, cresceu);
        *cresceu = false;
    }
}



No* remover_avl(No* raiz, int valor, bool* diminuiu) {
    if (raiz == NULL) {
        *diminuiu = false;
        return NULL;
    }

    if (valor < raiz->valor) {
        raiz->esq = remover_avl(raiz->esq, valor, diminuiu);
        if (*diminuiu) {
            raiz->bal++;
            if (raiz->bal == 1) {
                *diminuiu = false;
            } else if (raiz->bal == 2) {
                int bal_esq = (raiz->esq != NULL) ? raiz->esq->bal : 0;
                No* nova_raiz = balancear_avl(raiz, raiz->bal, bal_esq, diminuiu);
                if (nova_raiz->bal == 0) {
                    *diminuiu = true;
                } else {
                    *diminuiu = false;
                }
                return nova_raiz;
            }
        }
    } else if (valor > raiz->valor) {
        raiz->dir = remover_avl(raiz->dir, valor, diminuiu);
        if (*diminuiu) {
            raiz->bal--;
            if (raiz->bal == -1) {
                *diminuiu = false;
            } else if (raiz->bal == -2) {
                int bal_dir = (raiz->dir != NULL) ? raiz->dir->bal : 0;
                No* nova_raiz = balancear_avl(raiz, raiz->bal, bal_dir, diminuiu);
                if (nova_raiz->bal == 0) {
                    *diminuiu = true;
                } else {
                    *diminuiu = false;
                }
                return nova_raiz;
            }
        }
    } else {
        if (raiz->esq == NULL || raiz->dir == NULL) {
            No* temp = raiz->esq ? raiz->esq : raiz->dir;
            if (temp == NULL) {
                free(raiz);
                *diminuiu = true;
                return NULL;
            } else {
                *raiz = *temp;
                free(temp);
                *diminuiu = true;
            }
        } else {
            No* temp = maior_no(raiz->esq);
            raiz->valor = temp->valor;
            bool diminuiu_temp = false;
            raiz->esq = remover_avl(raiz->esq, temp->valor, &diminuiu_temp);
            if (diminuiu_temp) {
                raiz->bal++;
                if (raiz->bal == 1) {
                    *diminuiu = false;
                } else if (raiz->bal == 2) {
                    int bal_esq = (raiz->esq != NULL) ? raiz->esq->bal : 0;
                    No* nova_raiz = balancear_avl(raiz, raiz->bal, bal_esq, diminuiu);
                    if (nova_raiz->bal == 0) {
                        *diminuiu = true;
                    } else {
                        *diminuiu = false;
                    }
                    return nova_raiz;
                }
            } else {
                *diminuiu = false;
            }
        }
    }
    return raiz;
}

int main() {
    No* raiz = NULL;
    bool h;

    inserir_avl(&raiz, 5, &h);
    inserir_avl(&raiz, 3, &h);
    inserir_avl(&raiz, 8, &h);
    inserir_avl(&raiz, 2, &h);
    inserir_avl(&raiz, 4, &h);
    inserir_avl(&raiz, 7, &h);
    inserir_avl(&raiz, 10, &h);
    inserir_avl(&raiz, 1, &h);
    inserir_avl(&raiz, 6, &h);
    inserir_avl(&raiz, 9, &h);
    inserir_avl(&raiz, 11, &h);
    
    
    remover_avl(raiz, 4, &h);
    imprime_arvore(raiz);
    remover_avl(raiz, 8, &h);
    remover_avl(raiz, 6, &h);
    remover_avl(raiz, 5, &h);
    remover_avl(raiz, 2, &h);
    imprime_arvore(raiz);

    return 0;
}