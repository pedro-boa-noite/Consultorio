#ifndef _TSECRETARIO_H_
#define _TSECRETARIO_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tSecretario tSecretario;

void registroBinarioSecretarios(tSecretario* s, char* caminho);

/**
 * Função que cria um secretario e retorna um ponteiro para ele.
 */
tSecretario* criaSecretario(FILE* file, char* nome, char* CPF, char* dataNascimento, char* telefone, char* genero, char* usuario, char* senha, char* nivelAcesso);

/**
 * Função que recebe um ponteiro para um secretario e desaloca toda a memória
 * associada a ele.
 * Essa função sempre verifica se o ponteiro é NULL antes de desalocar.
 */
void desalocaSecretario(tSecretario *s);

char* obtemSenhaSecretario(tSecretario *s);

char* obtemUsuarioSecretario(tSecretario *s);

char* obtemNivelAcesso(tSecretario *s);

char* obtemCpfSecretario(tSecretario *s);

#endif
