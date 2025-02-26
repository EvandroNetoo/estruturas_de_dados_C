#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef char str[30];

typedef struct tipoCelula {
    bool boolean;
    str string;
    struct tipoCelula *abaixo;
    struct tipoCelula *direita;
} TCelula;

void set_matriz(TCelula **celula) {
    *celula = NULL;
}

TCelula *alocar_celula() {
    TCelula *celula = (TCelula *) malloc(sizeof(TCelula));
    celula->abaixo = NULL;
    celula->direita = NULL;
    celula->boolean = false;
    celula->string[0] = '\0';

    return celula;
}

void definir_matriz(TCelula **celula, int linha, int coluna) {
    int i, j;
    TCelula *linha_atual = NULL, *coluna_atual = NULL, *coluna_acima = NULL;

    if (*celula == NULL) {
        *celula = alocar_celula();
    }

    linha_atual = *celula;

    for (i = 0; i < linha; i++) {
        coluna_atual = linha_atual;
        for (j = 1; j < coluna ; j++) {
            
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


TCelula *get_celula(TCelula *celula, int linha, int coluna) {
    int i, j;
    for (i = 0; i < linha; i++) {
        celula = celula->abaixo;
    }
    for (j = 0; j < coluna; j++) {
        celula = celula->direita;
    }
    return celula;
}


void set_bool_celula(TCelula *celula, int linha, int coluna, bool valor) {
    TCelula *celula_atual = get_celula(celula, linha, coluna);
    if (celula_atual == NULL) {
        printf("i: %d, j: %d\n", linha, coluna);
        return;
    }
    celula_atual->boolean = valor; 
}

void set_str_celula(TCelula *celula, int linha, int coluna, str valor) {
    TCelula *celula_atual = get_celula(celula, linha, coluna);
    strcpy(celula_atual->string, valor);
}

void print_matriz(TCelula *celula) {
    TCelula *linha_atual = celula, *coluna_atual = celula;
    while (linha_atual != NULL) {
        coluna_atual = linha_atual;
        while (coluna_atual != NULL) {
            printf("%d ", coluna_atual->boolean);
            coluna_atual = coluna_atual->direita;
        }
        printf("\n");
        linha_atual = linha_atual->abaixo;
    }
}


void set_relacionamento(TCelula *celula, int indice_user1, int indice_user2, bool amigos) {
    set_bool_celula(celula, indice_user1, indice_user2, amigos);
    set_bool_celula(celula, indice_user2, indice_user1, amigos);
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
		printf("\n\n\tERRO:\n\tOPCAO invalida. Tente novamente.\n\n");
		system("PAUSE");
	}
	
	return opcao;
}


void inserir_usuario(int *qtd_usuarios, TCelula *usuarios, TCelula  *relacionamentos){
    char nome[30];
    printf("Digite o nome do usuario: ");
    scanf("%s", nome);

    (*qtd_usuarios)++;

    definir_matriz(&usuarios, *qtd_usuarios, 1);
    definir_matriz(&relacionamentos, *qtd_usuarios, *qtd_usuarios);

    set_str_celula(usuarios, *qtd_usuarios, 0, nome);

    printf("Usuario inserido com sucesso!\n");
}

int main() {
    int opcao, qtd_usuarios = 4;
    TCelula *usuarios = NULL, *relacionamentos = NULL;

    definir_matriz(&usuarios, qtd_usuarios, 1);
    set_str_celula(usuarios, 0, 0, "Ana");
    set_str_celula(usuarios, 1, 0, "Ze");
    set_str_celula(usuarios, 2, 0, "Cassandra");
    set_str_celula(usuarios, 3, 0, "Angelo");

    definir_matriz(&relacionamentos, qtd_usuarios, qtd_usuarios);

    set_relacionamento(relacionamentos, 0, 1, true);

    do {
		opcao = menu();
        switch (opcao) {
        case 1:
            inserir_usuario(&qtd_usuarios, usuarios, relacionamentos);
            break;
        
        case 2:
            break;

        case 3:
            break;
        
        default:
            break;
        }
			
        printf("gfdgsdfgsdfgdsf");
	} while(opcao != 0);

    return 0;
}

