#ifndef _TMEDICO_H_
#define _TMEDICO_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tMedico tMedico;

void registroBinarioMedicos(tMedico* m, char* caminho);

/**
 * Função que cria um medico e retorna um ponteiro para ele.
 */
tMedico* criaMedico(FILE* file, char* nome, char* CPF, char* dataNascimento, char* telefone, char* genero, char* usuario, char* senha, char* CRM);

/**
 * Função que recebe um ponteiro para um medico e desaloca toda a memória
 * associada a ele.
 * Essa função sempre verifica se o ponteiro é NULL antes de desalocar.
 */
void desalocaMedico(tMedico *m);

char* obtemSenhaMedico(tMedico *m);

char* obtemUsuarioMedico(tMedico *m);

char* obtemCpfMedico(tMedico *m);

char* obtemNomeMedico(tMedico *m);

char* obtemCrmMedico(tMedico *m);

#endif
