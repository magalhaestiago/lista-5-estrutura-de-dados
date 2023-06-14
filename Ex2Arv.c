#include <stdio.h>
#include <stdlib.h>

int main(){
    char* nome = "Tiago Magalh";
    printf("%s", nome);
}



typedef struct No{
    struct Livro liv;
    struct No *esquerda, *direita;
}ArvBin;

typedef struct Livro{
    char* tituloLivro;
    char* nomeAutor;
    int anoPublicacao;  
    int registro;
};



ArvBin *inserirLivro(ArvBin *raiz, struct Livro livro){
    if(raiz == NULL){
        ArvBin *novo = malloc(sizeof(ArvBin));
        novo->liv = livro;
        novo->esquerda = NULL;
        novo->direita = NULL;

        return novo;
    } else {
        if(livro.registro < raiz->liv.registro){
            raiz->esquerda = inserirLivro(raiz->esquerda, livro);
        } else {
            raiz->direita = inserirLivro(raiz->direita, livro);
        }
        return raiz;
    }
}

void imprimirDadosLivros(struct Livro livro){
    printf("%s\n", livro.tituloLivro);
    printf("%s\n", livro.nomeAutor);
    printf("%d\n", livro.anoPublicacao);
    printf("%d\n", livro.registro);
    printf("=============================\n");
}

int maior(int x, int y){
    if(x > y){
        return x;
    } else {
        return y;
    }
}

int menor(int x, int y){
    if(x < y){
        return x;
    } else {
        return y;
    }
}



int oLivroEstaEntreEssesAnos(int valor, int ano1, int ano2){
    if(valor >= maior(ano1, ano2) && valor <= menor(ano1, ano2)){
        return 1;
    } else {
        return 0;
    }
}

void imprimeLivros(ArvBin *raiz, char *nomeAutor, int ano1, int ano2){
    
    if(raiz != NULL && nomeAutor == raiz->liv.nomeAutor && oLivroEstaEntreEssesAnos(raiz->liv.anoPublicacao, ano1, ano2)){
        imprimirDadosLivros(raiz->liv);
    }
    imprimeLivros(raiz->esquerda, nomeAutor, ano1, ano2);
    imprimeLivros(raiz->direita, nomeAutor, ano1, ano2);

}

