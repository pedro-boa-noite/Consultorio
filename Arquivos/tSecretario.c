#include "tSecretario.h"

struct tSecretario{
    char* nome;
    char* CPF;
    char* dataNascimento;
    char* telefone;
    char* genero;
    char* usuario;
    char* senha;
    char* nivelAcesso;
};

void registroBinarioSecretarios(tSecretario* s, char* caminho){

    char caminhoCompleto[120];
    sprintf(caminhoCompleto, "%s/secretarios.bin", caminho);
    FILE *secretariosFile = fopen(caminhoCompleto, "ab");

    if(secretariosFile == NULL) {
        perror("Erro ao abrir o arquivo de secretários");
        exit(EXIT_FAILURE);
    }

    int tamNome = strlen(s->nome)+1;
    int tamCPF = strlen(s->CPF)+1;
    int tamDataNascimento = strlen(s->dataNascimento)+1;
    int tamTelefone = strlen(s->telefone)+1;
    int tamGenero = strlen(s->genero)+1;
    int tamUsuario = strlen(s->usuario)+1;
    int tamSenha = strlen(s->senha)+1;
    int tamNivelAcesso = strlen(s->nivelAcesso)+1;
    char sinal = 's';

    fwrite(&sinal, sizeof(char), 1, secretariosFile);
    fwrite(&tamNome, sizeof(int), 1, secretariosFile);
    fwrite(s->nome, sizeof(char), strlen(s->nome)+1, secretariosFile);
    fwrite(&tamCPF, sizeof(int), 1, secretariosFile);
    fwrite(s->CPF, sizeof(char), strlen(s->CPF)+1, secretariosFile);
    fwrite(&tamDataNascimento, sizeof(int), 1, secretariosFile);
    fwrite(s->dataNascimento, sizeof(char), strlen(s->dataNascimento)+1, secretariosFile);
    fwrite(&tamTelefone, sizeof(int), 1, secretariosFile);
    fwrite(s->telefone, sizeof(char), strlen(s->telefone)+1, secretariosFile);
    fwrite(&tamGenero, sizeof(int), 1, secretariosFile);
    fwrite(s->genero, sizeof(char), strlen(s->genero)+1, secretariosFile);
    fwrite(&tamUsuario, sizeof(int), 1, secretariosFile);
    fwrite(s->usuario, sizeof(char), strlen(s->usuario)+1, secretariosFile);
    fwrite(&tamSenha, sizeof(int), 1, secretariosFile);
    fwrite(s->senha, sizeof(char), strlen(s->senha)+1, secretariosFile);
    fwrite(&tamNivelAcesso, sizeof(int), 1, secretariosFile);
    fwrite(s->nivelAcesso, sizeof(char), strlen(s->nivelAcesso)+1, secretariosFile);

    fclose(secretariosFile);
}

tSecretario* criaSecretario(FILE* file, char* nome, char* CPF, char* dataNascimento, char* telefone, char* genero, char* usuario, char* senha, char* nivelAcesso){
    tSecretario* secretario = calloc(1, sizeof(tSecretario));

    int tamNome, tamCPF, tamDataNascimento, tamTelefone, tamGenero, tamUsuario, tamSenha, tamNivelAcesso;

    if(file != NULL){
        fread(&tamNome, sizeof(int), 1, file);
        secretario->nome = malloc((tamNome)*sizeof(char));
        fread(secretario->nome, sizeof(char), tamNome, file);

        fread(&tamCPF, sizeof(int), 1, file);
        secretario->CPF = malloc((tamCPF)*sizeof(char));
        fread(secretario->CPF, sizeof(char), tamCPF, file);

        fread(&tamDataNascimento, sizeof(int), 1, file);
        secretario->dataNascimento = malloc((tamDataNascimento)*sizeof(char));
        fread(secretario->dataNascimento, sizeof(char), tamDataNascimento, file);

        fread(&tamTelefone, sizeof(int), 1, file);
        secretario->telefone = malloc((tamTelefone)*sizeof(char));
        fread(secretario->telefone, sizeof(char), tamTelefone, file);

        fread(&tamGenero, sizeof(int), 1, file);
        secretario->genero = malloc((tamGenero)*sizeof(char));
        fread(secretario->genero, sizeof(char), tamGenero, file);

        fread(&tamUsuario, sizeof(int), 1, file);
        secretario->usuario = malloc((tamUsuario)*sizeof(char));
        fread(secretario->usuario, sizeof(char), tamUsuario, file);

        fread(&tamSenha, sizeof(int), 1, file);
        secretario->senha = malloc((tamSenha)*sizeof(char));
        fread(secretario->senha, sizeof(char), tamSenha, file);

        fread(&tamNivelAcesso, sizeof(int), 1, file);
        secretario->nivelAcesso = malloc((tamNivelAcesso)*sizeof(char));
        fread(secretario->nivelAcesso, sizeof(char), tamNivelAcesso, file);
    } else{
        secretario->nome = malloc((strlen(nome)+1)*sizeof(char));
        secretario->CPF = malloc((strlen(CPF)+1)*sizeof(char));
        secretario->dataNascimento = malloc((strlen(dataNascimento)+1)*sizeof(char));
        secretario->telefone = malloc((strlen(telefone)+1)*sizeof(char));
        secretario->genero = malloc((strlen(genero)+1)*sizeof(char));
        secretario->usuario = malloc((strlen(usuario)+1)*sizeof(char));
        secretario->senha = malloc((strlen(senha)+1)*sizeof(char));
        secretario->nivelAcesso = malloc((strlen(nivelAcesso)+1)*sizeof(char));

        strcpy(secretario->nome, nome);
        strcpy(secretario->CPF, CPF);
        strcpy(secretario->dataNascimento, dataNascimento);
        strcpy(secretario->telefone, telefone);
        strcpy(secretario->genero, genero);
        strcpy(secretario->usuario, usuario);
        strcpy(secretario->senha, senha);
        strcpy(secretario->nivelAcesso, nivelAcesso);
    }

    printf("%s %s %s %s %s %s %s %s\n", secretario->nome, secretario->CPF, secretario->dataNascimento, secretario->telefone, secretario->genero, secretario->usuario, secretario->senha, secretario->nivelAcesso);

    return secretario;
}

void desalocaSecretario(tSecretario *s){
    if(s != NULL){
        if(s->nome != NULL) free(s->nome);
        if(s->CPF != NULL) free(s->CPF);
        if(s->dataNascimento != NULL) free(s->dataNascimento);
        if(s->telefone != NULL) free(s->telefone);
        if(s->genero != NULL) free(s->genero);
        if(s->usuario != NULL) free(s->usuario);
        if(s->senha != NULL) free(s->senha);
        if(s->nivelAcesso != NULL) free(s->nivelAcesso);
        free(s);
    }
}

char* obtemSenhaSecretario(tSecretario *s){
    return s->senha;
}

char* obtemUsuarioSecretario(tSecretario *s){
    return s->usuario;
}

char* obtemNivelAcesso(tSecretario *s){
    return s->nivelAcesso;
}

char* obtemCpfSecretario(tSecretario *s){
    return s->CPF;
}
