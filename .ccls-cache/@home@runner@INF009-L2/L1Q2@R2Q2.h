#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

typedef struct no {
    char name[256];
    int tam;
    struct no *proximo;
} No;

// Protótipo das Funções:

void moveString(No** topoPrinc, No** topoAux);
void pushPrinc(No** topoPrinc, char string[256]);
void pushAux(No** topoPrinc, No** topoAux, char string[256]);
void pop(No** topo);


// Funções:

void moveString(No** topoPrinc, No** topoAux) {
  if (*topoPrinc == NULL) {
    printf("Erro: pilha principal vazia\n");
    return;
  }

  No* noRemovido = *topoPrinc;
  *topoPrinc = (*topoPrinc)->proximo;

  noRemovido->proximo = *topoAux;
  *topoAux = noRemovido;
}

void pushPrinc(No** topoPrinc, char string[256]) {
  No* newstruct = (No*)malloc(sizeof(No));
  strcpy(newstruct->name, string);
  newstruct->proximo = *topoPrinc;
  *topoPrinc = newstruct;
}

void pushAux(No** topoPrinc, No** topoAux, char string[256]) {
    if (*topoPrinc == NULL) {
      printf("Erro: pilha principal vazia\n");
      return;
    }

    No* noRemovido = *topoPrinc;
    *topoPrinc = (*topoPrinc)->proximo;

    No* newstruct = (No*)malloc(sizeof(No));
    strcpy(newstruct->name, string);
    newstruct->proximo = *topoAux;
    *topoAux = newstruct;
}

void pop(No** topo) {
    if (*topo == NULL) {
      printf("Erro: pilha vazia\n");
    }
   int tamanho	= strlen ((*topo)->name);
    *topo = (*topo)->proximo;
}