#ifndef _TRELATORIO_H_
#define _TRELATORIO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tPaciente.h"
#include "tMedico.h"
#include "tConsulta.h"

typedef struct tRelatorio tRelatorio;

tRelatorio *criaRelatorio(int pacientesAtendidos, int idadeMedia, int pacientesFemininos, int pacientesMasculinos, int pacientesOutros, int tamanhoLesoesConsultas, int numTotalLesoes, int cirugiasTotais, int crioterapiasTotais);

void desalocaRelatorio(void *dado);

void imprimeNaTelaRelatorio(void *dado);

void imprimeEmArquivoRelatorio(void *dado, char *path);

#endif