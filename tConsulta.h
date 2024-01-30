#ifndef _TCONSULTA_H_
#define _TCONSULTA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tLesao.h"
#include "tFila.h"
#include "tDocumento.h"
#include "tReceita.h"
#include "tBiopsia.h"
#include "tEncaminhamento.h"
#include "tMedico.h"
#include "tPaciente.h"
#include "tDocumento.h"

typedef struct tConsulta tConsulta;

int numCirurgias(tConsulta* consulta);

int numCrioterapias(tConsulta* consulta);

int tamanhoLesoesConsulta(tConsulta* consulta, int j);

void colocaEncaminhamentoFila(tFila* fila, tConsulta* consulta, tMedico* medico, tPaciente* paciente);

int colocaBiopsiaFila(tFila* fila, tConsulta* consulta, tMedico* medico, tPaciente* paciente);

void colocaReceitaFila(tFila* fila, tConsulta* consulta, tMedico* medico, tPaciente* paciente);

void insereLesao(tConsulta* consulta, FILE* file, int i);

int escolheOpcao(int opcao, tConsulta* consulta, tFila* fila, tMedico* medico, tPaciente* paciente, char* caminho);

void registroBinarioConsultas(tConsulta* consulta, char* caminho);

tConsulta* criaConsulta(FILE* file, tFila* fila, char* caminho, tMedico* medico, tPaciente* paciente, char* data, int possuiDiabetes, int ehFumante, int possuiAlergia, int possuiHistoricoCancer, char* tipoPele);

void desalocaConsulta(tConsulta* c);

int obtemQtdLesoesConsulta(tConsulta* c);

char* obtemCpfPacienteConsulta(tConsulta* c);

#endif