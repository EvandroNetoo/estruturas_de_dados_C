#include <stdio.h>
#include <stdlib.h>


typedef struct tipoCelula {
    int valor;
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
    celula->valor = 0;
    return celula;
}

void definir_matriz(TCelula **celula, int linha, int coluna) {
    int i, j;
    TCelula *linha_atual = NULL, *coluna_atual = NULL;

    if (*celula == NULL) {
        *celula = alocar_celula();
    }

    linha_atual = *celula;

    for (i = 0; i < linha; i++) {
        coluna_atual = linha_atual;
        for (j = 0; j < coluna - 1; j++) {
            
            if (coluna_atual->direita == NULL) {
                coluna_atual->direita = alocar_celula();
            }
            coluna_atual = coluna_atual->direita;
        
        }

        if (i < (linha - 1)) {
            if (linha_atual->abaixo == NULL) {
                linha_atual->abaixo = alocar_celula();
            }
        }

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

void set_celula(TCelula *celula, int linha, int coluna, int valor) {
    TCelula *celula_atual = get_celula(celula, linha, coluna);
    celula_atual->valor = valor; 
}

void print_matriz(TCelula *celula) {
    TCelula *linha_atual = celula, *coluna_atual = celula;
    while (linha_atual != NULL) {
        coluna_atual = linha_atual;
        while (coluna_atual != NULL) {
            printf("%d ", coluna_atual->valor);
            coluna_atual = coluna_atual->direita;
        }
        printf("\n");
        linha_atual = linha_atual->abaixo;
    }
}

int main() {
    TCelula *matriz;

    set_matriz(&matriz);
    definir_matriz(&matriz, 3, 3);
    set_celula(matriz, 0, 0, 1);
    set_celula(matriz, 0, 1, 2);
    set_celula(matriz, 1, 0, 3);
    print_matriz(matriz);

    printf("\n");

    definir_matriz(&matriz, 4, 4);
    set_celula(matriz, 3, 3, 4);
    print_matriz(matriz);
    return 0;
}

