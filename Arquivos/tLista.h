#ifndef _TLISTA_H_
#define _TLISTA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tPaciente.h"

typedef struct tLista tLista;

void insereLista(tLista* lista, tPaciente* paciente);

tLista *criaLista();

void desalocaLista(void *dado);

void imprimeNaTelaLista(void *dado);

void imprimeEmArquivoLista(void *dado, char *path);

int listaNula(tLista *lista);

#endif
