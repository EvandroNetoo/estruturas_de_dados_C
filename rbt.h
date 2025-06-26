typedef struct No {
    int chave;
    int cor;
    struct No *pai;
    struct No *esq;
    struct No *dir;
} No;

void insereNo(No **arvore, No *pPai, No **pMain, int k);

No *avo(No *arvore);

No *tio(No *arvore);

void rotacaoDireita(No **no);

void rotacaoEsquerda(No **no);

void consertaRB(No **arvore, No **pMain);

void inOrder(No *raiz);

void dRotacaoDireita(No **no);

void dRotacaoEsquerda(No **no);

void removeNo(No **arvore, int k);

void nBlackIBlackFRed(No *aRemover, No **arvore);

void nBlackIBlackFBlack(No *aRemover, No **arvore);

void nBlackIRed(No *aRemover, No **arvore);

No *buscaNo(No *arvore, int k);

No *irmao(No *pai, No *noAtual);

int filhoEsquerdo(No *arvore);

No **maiorEsq(No **pMaiorEsq);
