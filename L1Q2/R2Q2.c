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



void moveString(No** topoPrinc, No** topoAux);
void pushPrinc(No** topoPrinc, char string[256]);
void pushAux(No** topoPrinc, No** topoAux, char string[256]);
void pop(No** topo);




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


int main() {
  char linha[257];
  int cont = 0;
  FILE *fp_in = fopen("L1Q2/L1Q2.in", "r");
  FILE *fp_out = fopen("L1Q2.out", "w");
  if (fp_in == NULL || fp_out == NULL) {
    printf("Arquivos não podem ser abertos.");
    return EXIT_FAILURE;
  }

  while (fgets(linha, 257, fp_in) != NULL) { 
    int tamlinha = strlen(linha); 
    int contQuebralinha	=	0;
    int equaleLinha=0;
    for(int i =	0	; i	<	tamlinha	;	i++){
      if ( linha[i]	==	'\n')
        contQuebralinha++;
      }
    char *token = strtok(linha, " ");
    int k = 0;
    No  *topoPrinc	= NULL ; 
    No *topoAux = NULL; 

    while (token != NULL) {

    int tamanho =	strlen(token);
    if(token[tamanho-1]	==	'\n'){
      token[tamanho-1]='\0'; 
    }

      if(topoPrinc	==	NULL){
        pushPrinc	(	&topoPrinc	, token	);
        if(cont != 0)
          fprintf(fp_out," push-%s",topoPrinc->name);
        else
          fprintf(fp_out,"push-%s",topoPrinc->name);
      }	else	{
        if	(token[0] >= topoPrinc->name[0])	{ 
          pushPrinc	(	&topoPrinc	, token	);
          if(cont != 0)
            fprintf(fp_out," push-%s",topoPrinc->name);
          else
            fprintf(fp_out,"push-%s",topoPrinc->name);
        }else{
          int contmovestring =	0;
          while	(	topoPrinc != NULL &&	token[0]	< topoPrinc->name[0]	){
            moveString(&topoPrinc , &topoAux); 
            contmovestring++;
          }
          if(cont != 0)
            fprintf(fp_out	,	" %dx-pop"	,	contmovestring);
          else
            fprintf(fp_out	,	"%dx-pop"	,	contmovestring);

          pushPrinc(&topoPrinc,token); 
          if(cont != 0)
            fprintf(fp_out," push-%s",topoPrinc->name);
          else
            fprintf(fp_out,"push-%s",topoPrinc->name);

          while(	topoAux	!=	NULL	){
            moveString(&topoAux, &topoPrinc); 
            if(cont != 0)
              fprintf(fp_out	,	" push-%s"	,		topoPrinc->name);
            else
              fprintf(fp_out	,	"push-%s"	,		topoPrinc->name);
          }
        }
      }
      token = strtok(NULL, " ");
      k++;
      cont++;
    }
    cont = 0;
    if(equaleLinha	<	contQuebralinha){
      fprintf(fp_out,"\n");
      contQuebralinha++;
    }
  }
  fclose(fp_out);
  fclose(fp_in);
  return 0;
}