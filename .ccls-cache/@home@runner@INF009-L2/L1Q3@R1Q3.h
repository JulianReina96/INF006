#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <locale.h>

enum	{ INTEIRO	=	-3 , FLOAT , E_CARACTERE};

typedef struct eleLista{
  float chaveDecimal;
  struct eleLista* prox;
  int index;
}noSublista;

typedef struct inicioSublista{
  int qtdElementos;
  noSublista* primeiroElemento;
}inicioSublista;

typedef struct elemento{
  int chaveInteira;
  struct elemento* anterior;
  struct elemento* prox;
  int index;
  inicioSublista* subLista;
}no;

typedef struct inicio{
  int qtdElementos;
  no* primeiroElemento;
}inicio;

// protótipo das funções:

void verifica_caracter(char *token, int* cont);
int intOrFloat(double numero);
void inserirElementoFinal(inicio* lista, int chave, inicioSublista* sublista);
void inserirElemento(inicioSublista* lista, float chave);
void impressao(inicio* lista, FILE* fp_out);
void imprimir(inicio* lista, inicioSublista* subLista, FILE* fp_out);
void insertionSort(int* vetor, int tam);
void insertionSortFloat(float* vetor, int tam);
int contarCasasDecimais(float numero);
void liberaMemoria2(inicio* lista);


void verifica_caracter(char *token, int* cont){
  if((token[0] > 64 &&	token[0] < 91 ) || (token[0] > 96 &&	token[0] < 123  ))
    *cont = E_CARACTERE;
}


int intOrFloat(double numero){
    double fracao;
    fracao = modf	(numero, &numero); 
    if (fracao == 0.0) {
      return INTEIRO;
    }else{
      return FLOAT;
    }
}


void inserirElementoFinal(inicio* lista, int chave, inicioSublista* sublista) {
  no* novoElemento = (no*)malloc(sizeof(no));
  if (novoElemento == NULL) {
    perror("Erro ao alocar memória");
    return;
  }
  novoElemento->chaveInteira = chave;
  novoElemento->anterior = NULL;
  novoElemento->prox = NULL;
  novoElemento->index = lista->qtdElementos;
  novoElemento->subLista = sublista;
  if (lista->primeiroElemento == NULL) {
      lista->primeiroElemento = novoElemento;
  } else {
      no* atual = lista->primeiroElemento;
      while (atual->prox != NULL) {
        atual = atual->prox;
      }
      atual->prox = novoElemento;
      novoElemento->anterior = atual;
  }
  lista->qtdElementos++;
}


void inserirElemento(inicioSublista* lista, float chave){
  noSublista* novoElemento = (noSublista*)malloc(sizeof(noSublista));
  if (novoElemento == NULL) {
      perror("Erro ao alocar memória");
      return;
  }
  novoElemento->chaveDecimal = chave;
  novoElemento->prox = NULL;
  novoElemento->index = lista->qtdElementos;
  if (lista->primeiroElemento == NULL) {
    lista->primeiroElemento = novoElemento;
  } else {
    noSublista* atual = lista->primeiroElemento;
    while (atual->prox != NULL) {
      atual = atual->prox;
    }
    atual->prox = novoElemento;
  }
  lista->qtdElementos++;
}


void impressao(inicio* lista, FILE* fp_out){
  no* novo = (no*)malloc(sizeof(no));
  novo = lista->primeiroElemento;
  fprintf(fp_out, "[");
  int cont = 0;
  while(novo != NULL){
    if(cont != 0)
      fprintf(fp_out, "->%d(", novo->chaveInteira);
    else
      fprintf(fp_out, "%d(", novo->chaveInteira);
    inicioSublista* inicioSub = (inicioSublista*)malloc(sizeof(inicioSublista));
    noSublista* novoSublista = (noSublista*)malloc(sizeof(noSublista));
    inicioSub = novo->subLista;
    novoSublista = inicioSub->primeiroElemento;
    int contSub = 0;
    int casasDecimais = 0;
    char formato[20];
    while(novoSublista != NULL){
      if(contSub != 0){
        casasDecimais = contarCasasDecimais(novoSublista->chaveDecimal);
        if(casasDecimais > 2)
          fprintf(fp_out, "->%.2f", novoSublista->chaveDecimal);
        else{
        sprintf(formato, "%%.%df", casasDecimais);
        fprintf(fp_out, "->");
        fprintf(fp_out, formato, novoSublista->chaveDecimal);
        }
      }else{
        casasDecimais = contarCasasDecimais(novoSublista->chaveDecimal);
        if(casasDecimais > 2)
          fprintf(fp_out, "%.2f", novoSublista->chaveDecimal);
        else{
        sprintf(formato, "%%.%df", casasDecimais);
        fprintf(fp_out, formato, novoSublista->chaveDecimal);
        }
      }
      novoSublista = novoSublista->prox;
      contSub++;
    }
    fprintf(fp_out, ")");
    novo = novo->prox;
    cont++;
  }
  fprintf(fp_out, "]");
}


void insertionSort(int* vetor, int tam) {
  int j;
  for (j = 1; j < tam; j++) {
    int key = vetor[j];
    int i = j - 1;
    while ((i >= 0) && (vetor[i] > key)) {
      vetor[i + 1] = vetor[i];
      i = i - 1;
    }
    vetor[i + 1] = key;
  }
}


void insertionSortFloat(float* vetor, int tam) {
  int j;
  for (j = 1; j < tam; j++) {
    float key = vetor[j];
    int i = j - 1;
    while ((i >= 0) && (vetor[i] > key)) {
      vetor[i + 1] = vetor[i];
      i = i - 1;
    }
    vetor[i + 1] = key;
  }
}


int contarCasasDecimais(float numero) {
  int casasDecimais = 0;
  while (fabs(numero - round(numero)) > 0) {
    numero *= 10;
    casasDecimais++;
  }
  return casasDecimais;
}


void liberaMemoria(inicio* lista){
  no* novo = lista->primeiroElemento;
  while(novo->prox != NULL){
    inicioSublista* inicioSub = novo->subLista;
    noSublista* subLista = inicioSub->primeiroElemento;
    while(subLista != NULL){
      noSublista* proxSub = subLista->prox;
      free(subLista);
      subLista = proxSub;
    }
    inicioSub->primeiroElemento = NULL;
    no* prox = novo->prox;
    free(novo);
    novo = prox;
  }
  lista->primeiroElemento = NULL;
}