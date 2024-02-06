#ifndef _TPACIENTE_H_
#define _TPACIENTE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tPaciente tPaciente;

void registroBinarioPacientesNaConsulta(tPaciente* p, FILE* file);

tPaciente* LeBinarioPacienteNaConsulta(FILE* file);

void registroBinarioPacientes(tPaciente* p, char* caminho);

/**
 * Função que cria um paciente e retorna um ponteiro para ele.
 */
tPaciente* criaPaciente(FILE* file, char* nome, char* CPF, char* dataNascimento, char* telefone, char* genero);

/**
 * Função que recebe um ponteiro para um paciente e desaloca toda a memória
 * associada a ele.
 * Essa função sempre verifica se o ponteiro é NULL antes de desalocar.
 */
void desalocaPaciente(tPaciente *p);

char* obtemCpfPaciente(tPaciente *p);

char* obtemNomePaciente(tPaciente *p);

char* obtemDataPaciente(tPaciente *p);

char* obtemGeneroPaciente(tPaciente *p);

char* obtemTelefonePaciente(tPaciente *p);

#endif
