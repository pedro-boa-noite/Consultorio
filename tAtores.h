#ifndef _TATORES_H_
#define _TATORES_H_

#include "tMedico.h"
#include "tPaciente.h"
#include "tSecretario.h"
#include "tFila.h"
#include "tLista.h"
//#include "tConsulta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tAtores tAtores;

int idadeMedia(tAtores *a);

int pacientesMasculinos(tAtores* a);

int pacientesFemininos(tAtores* a);

int pacientesOutros(tAtores* a);

int imprimirPacientes(tFila* fila, tAtores* atores);

tMedico* EncontraMedico(tAtores* atores, char* usuario, char* senha);

tPaciente* ehIgualCpfPacientes(char* CPF, tAtores* a);

int ehIgualCpf(tAtores* a, char* CPF, char* ator);

int insereSecretario(tAtores* a, FILE* file, char* caminho);

int insereMedico(tAtores* a, FILE* file, char* caminho);

int inserePaciente(tAtores* a, FILE* file, char* caminho);

tAtores* atualizaBancoDados(tAtores* atores, char* caminho);

/**
 * Função que cria um banco de atores vazia e retorna um ponteiro para ele.
 */
tAtores *criaAtores(char* caminho);

/**
 * Função que recebe um ponteiro para um banco de atores e desaloca toda a memória
 * associada a ele. Essa função também desaloca todos os documentos associados a ele.
 * Essa função sempre verifica se o ponteiro é NULL antes de desalocar.
 */
void desalocaAtores(tAtores *a);

int qtdMedicos(tAtores* a);

int qtdPacientes(tAtores* a);

int qtdSecretarios(tAtores* a);

char* VerificaAtor(tAtores* a, char* user, char* senha);

tPaciente* obtemPaciente(tAtores* a, int i);


#endif