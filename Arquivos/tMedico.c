#include "tMedico.h"

struct tMedico{
    char* nome;
    char* CPF;
    char* dataNascimento;
    char* telefone;
    char* genero;
    char* CRM;
    char* usuario;
    char* senha;
};

void registroBinarioMedicos(tMedico* m, char* caminho){

    char caminhoCompleto[120];
    sprintf(caminhoCompleto, "%s/medicos.bin", caminho);
    FILE *medicosFile = fopen(caminhoCompleto, "ab");

    if(medicosFile == NULL) {
        perror("Erro ao abrir o arquivo de medicos");
        exit(EXIT_FAILURE);
    }

    int tamNome = strlen(m->nome)+1;
    int tamCPF = strlen(m->CPF)+1;
    int tamDataNascimento = strlen(m->dataNascimento)+1;
    int tamTelefone = strlen(m->telefone)+1;
    int tamGenero = strlen(m->genero)+1;
    int tamCRM = strlen(m->CRM)+1;
    int tamUsuario = strlen(m->usuario)+1;
    int tamSenha = strlen(m->senha)+1;
    char sinal = 's';

    fwrite(&sinal, sizeof(char), 1, medicosFile);
    fwrite(&tamNome, sizeof(int), 1, medicosFile);
    fwrite(m->nome, sizeof(char), strlen(m->nome)+1, medicosFile);
    fwrite(&tamCPF, sizeof(int), 1, medicosFile);
    fwrite(m->CPF, sizeof(char), strlen(m->CPF)+1, medicosFile);
    fwrite(&tamDataNascimento, sizeof(int), 1, medicosFile);
    fwrite(m->dataNascimento, sizeof(char), strlen(m->dataNascimento)+1, medicosFile);
    fwrite(&tamTelefone, sizeof(int), 1, medicosFile);
    fwrite(m->telefone, sizeof(char), strlen(m->telefone)+1, medicosFile);
    fwrite(&tamGenero, sizeof(int), 1, medicosFile);
    fwrite(m->genero, sizeof(char), strlen(m->genero)+1, medicosFile);
    fwrite(&tamCRM, sizeof(int), 1, medicosFile);
    fwrite(m->CRM, sizeof(char), strlen(m->CRM)+1, medicosFile);
    fwrite(&tamUsuario, sizeof(int), 1, medicosFile);
    fwrite(m->usuario, sizeof(char), strlen(m->usuario)+1, medicosFile);
    fwrite(&tamSenha, sizeof(int), 1, medicosFile);
    fwrite(m->senha, sizeof(char), strlen(m->senha)+1, medicosFile);

    fclose(medicosFile);
}

/**
 * Função que cria um medico e retorna um ponteiro para ele.
 */
tMedico* criaMedico(FILE* file, char* nome, char* CPF, char* dataNascimento, char* telefone, char* genero, char* usuario, char* senha, char* CRM){
    tMedico* medico = calloc(1, sizeof(tMedico));

    int tamNome, tamCPF, tamDataNascimento, tamTelefone, tamGenero, tamUsuario, tamSenha, tamCRM;

    if(file != NULL){
        fread(&tamNome, sizeof(int), 1, file);
        medico->nome = malloc((tamNome)*sizeof(char));
        fread(medico->nome, sizeof(char), tamNome, file);

        fread(&tamCPF, sizeof(int), 1, file);
        medico->CPF = malloc((tamCPF)*sizeof(char));
        fread(medico->CPF, sizeof(char), tamCPF, file);

        fread(&tamDataNascimento, sizeof(int), 1, file);
        medico->dataNascimento = malloc((tamDataNascimento)*sizeof(char));
        fread(medico->dataNascimento, sizeof(char), tamDataNascimento, file);

        fread(&tamTelefone, sizeof(int), 1, file);
        medico->telefone = malloc((tamTelefone)*sizeof(char));
        fread(medico->telefone, sizeof(char), tamTelefone, file);

        fread(&tamGenero, sizeof(int), 1, file);
        medico->genero = malloc((tamGenero)*sizeof(char));
        fread(medico->genero, sizeof(char), tamGenero, file);

        fread(&tamCRM, sizeof(int), 1, file);
        medico->CRM = malloc((tamCRM)*sizeof(char));
        fread(medico->CRM, sizeof(char), tamCRM, file);

        fread(&tamUsuario, sizeof(int), 1, file);
        medico->usuario = malloc((tamUsuario)*sizeof(char));
        fread(medico->usuario, sizeof(char), tamUsuario, file);

        fread(&tamSenha, sizeof(int), 1, file);
        medico->senha = malloc((tamSenha)*sizeof(char));
        fread(medico->senha, sizeof(char), tamSenha, file);
    } else{

        //printf("criaMedico antes da alocacao: %s %s %s %s %s %s %s %s\n", nome, CPF, dataNascimento, telefone, genero, CRM, usuario, senha);

        medico->nome = malloc((strlen(nome)+1)*sizeof(char));
        medico->CPF = malloc((strlen(CPF)+1)*sizeof(char));
        medico->dataNascimento = malloc((strlen(dataNascimento)+1)*sizeof(char));
        medico->telefone = malloc((strlen(telefone)+1)*sizeof(char));
        medico->genero = malloc((strlen(genero)+1)*sizeof(char));
        medico->CRM = malloc((strlen(CRM)+1)*sizeof(char));
        medico->usuario = malloc((strlen(usuario)+1)*sizeof(char));
        medico->senha = malloc((strlen(senha)+1)*sizeof(char));

        strcpy(medico->nome, nome);
        strcpy(medico->CPF, CPF);
        strcpy(medico->dataNascimento, dataNascimento);
        strcpy(medico->telefone, telefone);
        strcpy(medico->genero, genero);
        strcpy(medico->CRM, CRM);
        strcpy(medico->usuario, usuario);
        strcpy(medico->senha, senha);  
    }

    printf("criaMedico depois da alocacao: %s %s %s %s %s %s %s %s\n", medico->nome, medico->CPF, medico->dataNascimento, medico->telefone, medico->genero, medico->CRM, medico->usuario, medico->senha);

    return medico;
}

/**
 * Função que recebe um ponteiro para um medico e desaloca toda a memória
 * associada a ele.
 * Essa função sempre verifica se o ponteiro é NULL antes de desalocar.
 */
void desalocaMedico(tMedico *m){
    if(m != NULL){ 
        if(m->nome != NULL) free(m->nome);
        if(m->CPF != NULL) free(m->CPF);
        if(m->dataNascimento != NULL) free(m->dataNascimento);
        if(m->telefone != NULL) free(m->telefone);
        if(m->genero != NULL) free(m->genero);
        if(m->CRM != NULL) free(m->CRM);
        if(m->usuario != NULL) free(m->usuario);
        if(m->senha != NULL) free(m->senha);
        free(m);
    }
}

char* obtemSenhaMedico(tMedico *m){
    return m->senha;
}

char* obtemUsuarioMedico(tMedico *m){
    return m->usuario;
}

char* obtemCpfMedico(tMedico *m){
    return m->CPF;
}

char* obtemNomeMedico(tMedico *m){
    return m->nome;
}

char* obtemCrmMedico(tMedico *m){
    return m->CRM;
}
