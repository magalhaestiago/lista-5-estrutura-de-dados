#include <stdlib.h>
#include <stdio.h>

typedef struct no{
    int info;
    struct no *esquerda, *direita;
}ArvBin;


// A) Inserir elementos
ArvBin *inserirNo(ArvBin *raiz, int valor){
    if(raiz == NULL){
        ArvBin *novo = malloc(sizeof(ArvBin));

        novo->info = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
        
    } else {
        if(valor < raiz->info){
            raiz->esquerda = inserirNo(raiz->esquerda, valor);
        } else {
            raiz->direita = inserirNo(raiz->direita, valor);
        }
        return raiz;
    }
}


// B) Percorrer a Arvore usando pre-ordem, em ordem e pos ordem

// pre ordem
void printarPreOrdem(ArvBin *raiz){
    if(raiz != NULL){
        printf("%d ", raiz->info);
        printarPreOrdem(raiz->esquerda);
        printarPreOrdem(raiz->direita);
    }
}

// em ordem
void printarEmOrdem(ArvBin *raiz){
    if(raiz != NULL){
        printarPreOrdem(raiz->esquerda);
        printf("%d ", raiz->info);
        printarPreOrdem(raiz->direita);
    }
}

// pos ordem
void printarPosOrdem(ArvBin *raiz){
    if(raiz != NULL){
        printarPreOrdem(raiz->esquerda);
        printarPreOrdem(raiz->direita);
        printf("%d ", raiz->info);
    }
}

// C) Verificar se um certo valor n (chave) está presente na árvore;
int buscaElemento(ArvBin *raiz, int valor){
    if(raiz->info == valor){
        return 1;
    } else if (raiz->info > valor) {
        return buscaElemento(raiz->esquerda, valor);
    } else if (raiz->info < valor) {
        return buscaElemento(raiz->direita, valor);
    } 
    
}

// D) Retornar o menor e o maior valor presente na árvore;
int maiorValor(ArvBin *raiz){
   if(raiz->direita == NULL){
        return raiz->info;
    }else {
        return maiorValor(raiz->direita);
    }
}

int menorValor(ArvBin *raiz){
    if(raiz->esquerda == NULL){
        return raiz->info;
    } else {
        return menorValor(raiz->esquerda);
    }
}

// E) Retornar a média dos valores presentes na árvore;

// funcoes auxiliares
int somaNos(ArvBin *raiz){
    int aux = 0;
    if(raiz != NULL){
        aux = aux + raiz->info;
        aux += somaNos(raiz->esquerda);
        aux += somaNos(raiz->direita);
    }
    return aux;
}
int qtdNos(ArvBin *raiz){
    int cont = 0;
    if(raiz != NULL){
        cont++;
        cont += qtdNos(raiz->esquerda);
        cont+= qtdNos(raiz->direita); 
    }
    return cont;
}

double mediaNos(ArvBin *raiz){
    return somaNos(raiz)/qtdNos(raiz);
}

// F) Retornar o número de NULLs presentes na árvore;

int numNullsArvore(ArvBin *raiz){
    
}






int main(){
    ArvBin *raiz = NULL;

    raiz = inserirNo(raiz, 3);
    raiz = inserirNo(raiz, 5);
    raiz = inserirNo(raiz, 2);
    raiz = inserirNo(raiz, 6);
    raiz = inserirNo(raiz, 5);
    
    printarPreOrdem(raiz);
    
    printf("\n%.2f", mediaNos(raiz));

    
    
    
}