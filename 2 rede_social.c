#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef char str[30];

typedef struct tipoCelula {
    int integer;
    bool boolean;
    str string;
    struct tipoCelula* abaixo;
    struct tipoCelula* direita;
} TCelula;


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void set_matriz(TCelula** celula) {
    *celula = NULL;
}

TCelula* alocar_celula() {
    TCelula* celula = (TCelula*)malloc(sizeof(TCelula));
    celula->abaixo = NULL;
    celula->direita = NULL;
    celula->boolean = false;
    celula->string[0] = '\0';
    celula->integer = 0;

    return celula;
}

void definir_matriz(TCelula** celula, int linha, int coluna) {
    int i, j;
    TCelula* linha_atual = NULL, * coluna_atual = NULL, * coluna_acima = NULL;

    if (*celula == NULL) {
        *celula = alocar_celula();
    }

    linha_atual = *celula;

    for (i = 0; i < linha; i++) {
        coluna_atual = linha_atual;
        for (j = 1; j < coluna; j++) {

            if (coluna_atual->direita == NULL) {
                coluna_atual->direita = alocar_celula();
            }
            coluna_atual = coluna_atual->direita;

            if (coluna_acima != NULL) {
                coluna_acima->abaixo = coluna_atual;
                coluna_acima = coluna_acima->direita;
            }

        }
        if (i < (linha - 1)) {
            if (linha_atual->abaixo == NULL) {
                linha_atual->abaixo = alocar_celula();
            }
        }
        coluna_acima = linha_atual->direita;
        linha_atual = linha_atual->abaixo;
    }

}


TCelula* get_celula(TCelula* celula, int linha, int coluna) {
    int i, j;
    for (i = 0; i < linha; i++) {
        celula = celula->abaixo;
    }
    for (j = 0; j < coluna; j++) {
        celula = celula->direita;
    }
    return celula;
}


void set_int_celula(TCelula* celula, int linha, int coluna, int valor) {
    TCelula* celula_atual = get_celula(celula, linha, coluna);
    celula_atual->integer = valor;
}

void set_bool_celula(TCelula* celula, int linha, int coluna, bool valor) {
    TCelula* celula_atual = get_celula(celula, linha, coluna);
    celula_atual->boolean = valor;
}

void set_str_celula(TCelula* celula, int linha, int coluna, str valor) {
    TCelula* celula_atual = get_celula(celula, linha, coluna);
    strcpy(celula_atual->string, valor);
}

void print_matriz(TCelula* celula) {
    TCelula* linha_atual = celula, * coluna_atual = celula;
    while (linha_atual != NULL) {
        coluna_atual = linha_atual;
        while (coluna_atual != NULL) {
            printf("%d ", coluna_atual->integer);
            coluna_atual = coluna_atual->direita;
        }
        printf("\n");
        linha_atual = linha_atual->abaixo;
    }
}

int menu() {
    int opcao;
    system("CLS");
    printf("=====| MENU |======\n\n");
    printf("0 - Sair (Encerrar Aplicacao).\n");
    printf("1 - Inserir NOVO usuario.\n");
    printf("2 - Registrar amizade entre usuarios.\n");
    printf("3 - Indicar novas amizades para usuarios.\n");
    printf("\nInforme OPCAO desejada: ");
    scanf("%d", &opcao);

    if ((opcao > 4) || (opcao < 0)) {
        printf("\n\n\tERRO:\n\tOPCAO invalida. Tente novamente.\n\n");
        system("PAUSE");
    }

    return opcao;
}

void inserir_usuario(int* qtd_usuarios, TCelula* usuarios, TCelula* relacionamentos) {
    str nome;

    printf("Digite o nome do usuario: ");

    limparBuffer();
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    (*qtd_usuarios)++;

    definir_matriz(&usuarios, *qtd_usuarios, 1);
    definir_matriz(&relacionamentos, *qtd_usuarios, *qtd_usuarios);

    set_str_celula(usuarios, *qtd_usuarios - 1, 0, nome);

    printf("Usuario inserido com sucesso!\n");
    system("PAUSE");
}

void print_usuarios(TCelula* celula) {
    int i = 0;
    while (celula != NULL) {
        printf("%d - %s\n", i++, celula->string);
        celula = celula->abaixo;
    }
}

void set_relacionamento(TCelula* relacionametos, int indice_user1, int indice_user2, bool amigos) {
    set_bool_celula(relacionametos, indice_user1, indice_user2, amigos);
    set_bool_celula(relacionametos, indice_user2, indice_user1, amigos);
}

void add_relacionamento(TCelula* usuarios, TCelula* relacionametos) {
    int indice_user1, indice_user2;
    print_usuarios(usuarios);
    printf("Digite os indices dos usuários separados por espaço: ");
    scanf("%d %d", &indice_user1, &indice_user2);
    set_relacionamento(relacionametos, indice_user1, indice_user2, true);
}


void print_relacionamentos(TCelula* usuarios, TCelula* relacionamentos) {
    TCelula* linha_atual = relacionamentos, * coluna_atual, * usuario_atual = usuarios;
    int biggest_name = 0, name_len;

    while (usuario_atual != NULL) {
        name_len = (int)strlen(usuario_atual->string);
        if (name_len > biggest_name) {
            biggest_name = name_len;
        }
        usuario_atual = usuario_atual->abaixo;
    }

    usuario_atual = usuarios;

    while (linha_atual != NULL) {
        coluna_atual = linha_atual;

        printf("%*s ", biggest_name, usuario_atual->string);

        usuario_atual = usuario_atual->abaixo;
        while (coluna_atual != NULL) {
            printf("%d ", coluna_atual->boolean);
            coluna_atual = coluna_atual->direita;
        }
        printf("\n");
        linha_atual = linha_atual->abaixo;
    }
}

void recomendar_relacionamentos(int qtd_usuarios, TCelula* usuarios, TCelula* relacionamentos, int min_relacionamentos) {
    TCelula* recomendacoes = NULL, * linha_atual = relacionamentos, * coluna_atual, * coluna_atual_aux, * usuario_atual = usuarios;

    int i, j, k;

    definir_matriz(&recomendacoes, qtd_usuarios, qtd_usuarios);

    for (i = 0; i < qtd_usuarios; i++) {
        coluna_atual = linha_atual;
        for (j = 0; j < qtd_usuarios; j++) {
            if (coluna_atual->boolean) {
                coluna_atual_aux = linha_atual;
                for (k = 0; k < qtd_usuarios; k++) {
                    if (j != k && coluna_atual_aux->boolean) {
                        coluna_atual_aux->integer++;
                        get_celula(recomendacoes, k, j)->integer++;
                    }
                    coluna_atual_aux = coluna_atual_aux->direita;
                }
            }
            coluna_atual = coluna_atual->direita;
        }
        linha_atual = linha_atual->abaixo;
    }

    printf("Recomendacoes:\n");
    print_matriz(recomendacoes);
    system("PAUSE");

    linha_atual = recomendacoes;
    for (i = 0; i < qtd_usuarios; i++) {
        coluna_atual = linha_atual;

        printf("%s:\n", usuario_atual->string);

        usuario_atual = usuario_atual->abaixo;
        for (j = 0; j < qtd_usuarios; j++) {
            if (coluna_atual->integer >= min_relacionamentos) {
                if (!get_celula(relacionamentos, i, j)->boolean) {
                    printf("    %s\n", get_celula(usuarios, j, 0)->string);
                }
            }
            coluna_atual = coluna_atual->direita;
        }
        linha_atual = linha_atual->abaixo;
    }

    system("PAUSE");
}


int main() {
    int opcao, qtd_usuarios = 4;
    TCelula* usuarios = NULL, * relacionamentos = NULL;

    definir_matriz(&usuarios, qtd_usuarios, 1);
    set_str_celula(usuarios, 0, 0, "A");
    set_str_celula(usuarios, 1, 0, "B");
    set_str_celula(usuarios, 2, 0, "C");
    set_str_celula(usuarios, 3, 0, "D");

    definir_matriz(&relacionamentos, qtd_usuarios, qtd_usuarios);

    set_relacionamento(relacionamentos, 0, 1, true);
    set_relacionamento(relacionamentos, 0, 2, true);
    set_relacionamento(relacionamentos, 1, 3, true);
    set_relacionamento(relacionamentos, 2, 3, true);


    printf("Relacionamentos inciais:\n");
    printf("A -- B\n");
    printf("|    |\n");
    printf("C -- D\n");

    system("PAUSE");

    do {
        opcao = menu();
        switch (opcao) {
        case 1:
            inserir_usuario(&qtd_usuarios, usuarios, relacionamentos);
            break;

        case 2:
            add_relacionamento(usuarios, relacionamentos);
            break;

        case 3:
            recomendar_relacionamentos(qtd_usuarios, usuarios, relacionamentos, 2);
            break;

        case 4:
            print_relacionamentos(usuarios, relacionamentos);
            system("PAUSE");
            break;

        default:
            break;
        }
    } while (opcao != 0);

    return 0;
}

