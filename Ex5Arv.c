#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    struct candidato cand;
    int altura;
    struct No *esquerda, *direita;

}ArvAvlPartido;

typedef struct candidato{
    int numIdentificacao;
    int numVotos;
};

ArvAvlPartido *novoNo(struct candidato novoCandidato){
    ArvAvlPartido *novo = malloc(sizeof(ArvAvlPartido));

    if(novo != NULL){
        novo->cand = novoCandidato;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 0;
    } else {
        return;
    }
    return novo;
}
/*
    3
        4
    x        5


        4
    3       5
       x    
*/

ArvAvlPartido *insert(ArvAvlPartido *raiz, struct candidato novoCandidato){
    if(raiz == NULL){
        return novoNo(novoCandidato);
    } else if (novoCandidato.numVotos < raiz->cand.numVotos){
        return insert(raiz->esquerda, novoCandidato);
    } else {
        return insert(raiz->direita, novoCandidato);
    }

    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;

    raiz = balancear(raiz);   
}


int fatorBalanceamento(ArvAvlPartido *no){
    if(no != NULL){
        return alturaNo(no->esquerda) - alturaNo(no->direita);
    } else {
        return 0;
    }
}



ArvAvlPartido *balancear(ArvAvlPartido *raiz){
    int fb = fatorBalanceamento(raiz);

    if(fb < -1 && fatorBalanceamento(raiz->direita) <= 0){
        raiz = rotacaoEsquerda(raiz);
    } else if(fb < 0 && fatorBalanceamento(raiz->esquerda)  < 0){
        raiz = rotacaoDireita(raiz);
    } else if(fb > 1 && fatorBalanceamento(raiz->esquerda < 0)){
        raiz = rotacaoEsquerdaDireita(raiz);
    } else {
        raiz = rotacaoDireitaEsquerda(raiz);
    }

    return raiz;
}


ArvAvlPartido *rotacaoEsquerda(ArvAvlPartido *raiz){
    ArvAvlPartido *proximaRaiz, *filho;

    proximaRaiz = raiz->direita;
    filho = proximaRaiz->esquerda;

    proximaRaiz->esquerda = raiz;
    raiz->direita = filho;

    raiz->altura = maior(alturaNo(raiz->direita), alturaNo(raiz->esquerda)) + 1;
    proximaRaiz = maior(alturaNo(proximaRaiz->direita), alturaNo(proximaRaiz->esquerda)) + 1;

    return proximaRaiz;
}

ArvAvlPartido *rotacaoDireita(ArvAvlPartido *raiz){
    ArvAvlPartido *proximaRaiz, *filho;

    proximaRaiz = raiz->esquerda;
    filho = proximaRaiz->direita;

    proximaRaiz->direita = raiz;
    raiz->esquerda = filho;

    raiz->altura = maior(alturaNo(raiz->direita), alturaNo(raiz->esquerda)) + 1;
    proximaRaiz->altura = maior(alturaNo(proximaRaiz->esquerda),alturaNo(proximaRaiz->direita)) + 1;
    
    return proximaRaiz;
}

int alturaNo(ArvAvlPartido *raiz){
    if(raiz != NULL){
        return raiz->altura;
    } else {
        return -1;
    }
}

int maior(int a, int b){
    return (a > b) ? a: b;
}

ArvAvlPartido *getCandidate(ArvAvlPartido *raiz, int numIdentificacaoNew){
    ArvAvlPartido *aux = raiz;

    while(aux->cand.numIdentificacao != numIdentificacaoNew || aux == NULL){
        aux = getCandidate(aux->esquerda, numIdentificacaoNew);
        aux = getCandidate(aux->direita, numIdentificacaoNew);
    }
    return aux;

}

ArvAvlPartido *remover(ArvAvlPartido *raiz, int numIdentificacaoRemove){
    if(raiz == NULL){
        return NULL;
    } else {
        if(raiz->cand.numVotos == getCandidate(raiz, numIdentificacaoRemove)->cand.numVotos){
            if(raiz->esquerda == NULL && raiz->direita == NULL){
                free(raiz);
                return NULL;
            } else {
                if(raiz->esquerda != NULL && raiz->direita != NULL){
                    ArvAvlPartido *aux = raiz->esquerda;
                    while(aux->direita != NULL){
                        aux = aux->direita;
                    }
                    raiz->cand.numVotos = aux->cand.numVotos;
                    aux->cand.numVotos = getCandidate(raiz, numIdentificacaoRemove)->cand.numVotos;
                    raiz->esquerda = remover(raiz->esquerda, numIdentificacaoRemove);
                    return raiz;
                }
                else {
                    ArvAvlPartido *aux;
                    if(raiz->esquerda != NULL){
                        aux = raiz->esquerda;
                    } else {
                        aux = raiz->direita;
                    }
                    free(raiz);
                    return aux;

                }
            }
        } else {
            if(getCandidate(raiz, numIdentificacaoRemove)->cand.numVotos < raiz->cand.numVotos){
                raiz->esquerda = remover(raiz->esquerda, numIdentificacaoRemove);
            } else {
                raiz->direita = remover(raiz->direita, numIdentificacaoRemove);
            }
        }
        raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;

        raiz = balancear(raiz);

        return raiz;
    }

    
}