#include <stdio.h>
#include <stdlib.h>

typedef struct timeEsports{
    int pontuacao;
    char *nome;
};

typedef struct No{
    struct timeEsports time;

    struct No *esquerda, *direita;
}ArvBin;


ArvBin* inserir(ArvBin *raiz, struct timeEsports timeNovo){
    if(raiz == NULL){
        raiz->time = timeNovo;
        raiz->esquerda = NULL;
        raiz->direita = NULL;
    } else {
        if (timeNovo.pontuacao < raiz->time.pontuacao){
            raiz->esquerda = inserir(raiz->esquerda, timeNovo);
        } else {
            raiz->direita = inserir(raiz->direita, timeNovo);
        }
        return raiz;
    }
}

void imprimirDadosEmOrdem(ArvBin *raiz){
    if(raiz != NULL){
        imprimirDadosEmOrdem(raiz->esquerda);
        printf("%d ", raiz->time.pontuacao);
        imprimirDadosEmOrdem(raiz->direita);
    }
}