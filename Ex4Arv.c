#include <stdio.h>
#include <stdlib.h>

/*
Você está trabalhando em um projeto de pesquisa arqueológica e precisa
desenvolver um sistema para gerenciar as descobertas de artefatos encontrados
em diferentes camadas do solo. Cada artefato possui um ID único e uma data de
descoberta. Você decide utilizar uma árvore AVL para armazenar as informações
dos artefatos, ordenados pela data de descoberta. Além disso, você precisa
implementar dois métodos adicionais no sistema: getLatestArtifact e
getOldestArtifact.
Implemente a classe AVLTree em uma linguagem de programação de sua escolha,
com os seguintes requisitos:
A classe deve ter um método insert, que recebe como parâmetros o ID e a data de
descoberta de um novo artefato a ser inserido na árvore.

O método insert deve adicionar o novo artefato à árvore AVL e garantir que a
propriedade de balanceamento seja mantida em todos os momentos.
Além disso, a classe deve conter os seguintes métodos:
– "getLatestArtifact", que deve retornar o ID do artefato mais recente
descoberto;
– "getOldestArtifact", que deve retornar o ID do artefato mais antigo descoberto.
*/

typedef struct artefato{
    int idArtefato;
    int diaData, mesData, anoData;
};

typedef struct No{
    struct artefato;
    struct No *direita, *esquerda;
    int altura;
}AvlTree;

AvlTree* novoNo(struct artefato a){
    AvlTree *aux = malloc(sizeof(AvlTree));
    if(aux != NULL){
        aux->altura = 0;
        aux->direita = NULL;
        aux->esquerda = NULL;

        aux->anoData = a.anoData;
        aux->mesData = a.mesData;
        aux->diaData = a.diaData;
        aux->idArtefato = a.idArtefato;
    } else {
        return;
    }
    return aux;
}

AvlTree *insert(AvlTree *raiz, struct artefato a){
    if(raiz == NULL){
        return novoNo(a);
    } else {
        if(a.idArtefato < raiz->idArtefato){
            raiz->esquerda = insert(raiz->esquerda, a);
        } else {
            raiz->direita = insert(raiz->direita, a);
        }
    }

    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;

    raiz = balancear(raiz);
}

int alturaNo(AvlTree *no){ 
    if(no == NULL){
        return -1;
    } else {
        return no->altura;
    }
}

int fatorBalanceamento(AvlTree *no){
    if(no != NULL){
        return alturaNo(no->esquerda) - alturaNo(no->direita);
    } else {
        return 0;
    }
}

AvlTree *rotacaoEsquerda(AvlTree *raiz){
    AvlTree *filho, *proximaRaiz;

    proximaRaiz = raiz->direita;
    filho = proximaRaiz->esquerda;

    proximaRaiz->esquerda = raiz;
    raiz->direita = filho;

    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    proximaRaiz->altura = maior(alturaNo(proximaRaiz->esquerda), alturaNo(proximaRaiz->direita)) + 1;

    return proximaRaiz;

}


AvlTree *rotacaoDireita(AvlTree *raiz){
    AvlTree *filho, *proximaRaiz;

    proximaRaiz = raiz->esquerda;
    filho = proximaRaiz->direita;

    proximaRaiz->direita = raiz;
    raiz->esquerda = filho;

    raiz->altura = maior(alturaNo(raiz->esquerda), alturaNo(raiz->direita)) + 1;
    proximaRaiz->altura = maior(alturaNo(proximaRaiz->direita), alturaNo(proximaRaiz->esquerda)) + 1;

    return proximaRaiz;
}

AvlTree *rotacaoDireitaEsquerda(AvlTree *raiz){
    raiz->direita = rotacaoDireita(raiz->direita);
    return rotacaoEsquerda(raiz);
}

AvlTree *rotacaoEsquerdaDireita(AvlTree *raiz){
    raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
    return rotacaoDireita(raiz);
}

int maior(int a, int b){
    return (a > b) ? a: b; // Se a > b, retorna a, senão retorna b;    
}

AvlTree *artefatomaisRecente(AvlTree *raiz){
    if(raiz == NULL){
        return raiz;
    } else if(raiz->direita != NULL){
        raiz->direita = artefatomaisRecente(raiz->direita);
    }
}

int artefatoMaisAntigo(AvlTree *raiz){
    if(raiz == NULL){
        return raiz->idArtefato;
    } else if(raiz->esquerda !=NULL) {
        raiz->esquerda = artefatoMaisAntigo(raiz->esquerda);
    }

    return raiz->idArtefato;
}

AvlTree *balancear(AvlTree *raiz){
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
