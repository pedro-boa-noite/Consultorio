#include "tPaciente.h"

struct tPaciente{
    char* nome;
    char* CPF;
    char* dataNascimento;
    char* telefone;
    char* genero;
};

// void registroBinarioPacientesNaConsulta(tPaciente* p, FILE* file){
//     if(file == NULL) {
//         perror("Erro ao abrir o arquivo de pacientes na consulta");
//         exit(EXIT_FAILURE);
//     }

//     int tamNome = strlen(p->nome)+1;
//     int tamCPF = strlen(p->CPF)+1;
//     int tamDataNascimento = strlen(p->dataNascimento)+1;
//     int tamTelefone = strlen(p->telefone)+1;
//     int tamGenero = strlen(p->genero)+1;

//     fwrite(&tamNome, sizeof(int), 1, file);
//     fwrite(p->nome, sizeof(char), strlen(p->nome)+1, file);
//     fwrite(&tamCPF, sizeof(int), 1, file);
//     fwrite(p->CPF, sizeof(char), strlen(p->CPF)+1, file);
//     fwrite(&tamDataNascimento, sizeof(int), 1, file);
//     fwrite(p->dataNascimento, sizeof(char), strlen(p->dataNascimento)+1, file);
//     fwrite(&tamTelefone, sizeof(int), 1, file);
//     fwrite(p->telefone, sizeof(char), strlen(p->telefone)+1, file);
//     fwrite(&tamGenero, sizeof(int), 1, file);
//     fwrite(p->genero, sizeof(char), strlen(p->genero)+1, file);
// }

void registroBinarioPacientes(tPaciente* p, char* caminho){

    char caminhoCompleto[120];
    sprintf(caminhoCompleto, "%s/pacientes.bin", caminho);
    FILE *pacientesFile = fopen(caminhoCompleto, "ab");

    if(pacientesFile == NULL) {
        perror("Erro ao abrir o arquivo de pacientes");
        exit(EXIT_FAILURE);
    }

    int tamNome = strlen(p->nome)+1;
    int tamCPF = strlen(p->CPF)+1;
    int tamDataNascimento = strlen(p->dataNascimento)+1;
    int tamTelefone = strlen(p->telefone)+1;
    int tamGenero = strlen(p->genero)+1;
    char sinal = 's';

    fwrite(&sinal, sizeof(char), 1, pacientesFile);
    fwrite(&tamNome, sizeof(int), 1, pacientesFile);
    fwrite(p->nome, sizeof(char), strlen(p->nome)+1, pacientesFile);
    fwrite(&tamCPF, sizeof(int), 1, pacientesFile);
    fwrite(p->CPF, sizeof(char), strlen(p->CPF)+1, pacientesFile);
    fwrite(&tamDataNascimento, sizeof(int), 1, pacientesFile);
    fwrite(p->dataNascimento, sizeof(char), strlen(p->dataNascimento)+1, pacientesFile);
    fwrite(&tamTelefone, sizeof(int), 1, pacientesFile);
    fwrite(p->telefone, sizeof(char), strlen(p->telefone)+1, pacientesFile);
    fwrite(&tamGenero, sizeof(int), 1, pacientesFile);
    fwrite(p->genero, sizeof(char), strlen(p->genero)+1, pacientesFile);

    fclose(pacientesFile);
}

tPaciente* criaPaciente(FILE* file, char* nome, char* CPF, char* dataNascimento, char* telefone, char* genero){
    tPaciente* paciente = calloc(1, sizeof(tPaciente));

    int tamNome, tamCPF, tamDataNascimento, tamTelefone, tamGenero;

    if(file != NULL){
        fread(&tamNome, sizeof(int), 1, file);
        paciente->nome = malloc((tamNome)*sizeof(char));
        fread(paciente->nome, sizeof(char), tamNome, file);

        fread(&tamCPF, sizeof(int), 1, file);
        paciente->CPF = malloc((tamCPF)*sizeof(char));
        fread(paciente->CPF, sizeof(char), tamCPF, file);

        fread(&tamDataNascimento, sizeof(int), 1, file);
        paciente->dataNascimento = malloc((tamDataNascimento)*sizeof(char));
        fread(paciente->dataNascimento, sizeof(char), tamDataNascimento, file);

        fread(&tamTelefone, sizeof(int), 1, file);
        paciente->telefone = malloc((tamTelefone)*sizeof(char));
        fread(paciente->telefone, sizeof(char), tamTelefone, file);

        fread(&tamGenero, sizeof(int), 1, file);
        paciente->genero = malloc((tamGenero)*sizeof(char));
        fread(paciente->genero, sizeof(char), tamGenero, file);
    } else{
        paciente->nome = malloc((strlen(nome)+1)*sizeof(char));
        paciente->CPF = malloc((strlen(CPF)+1)*sizeof(char));
        paciente->dataNascimento = malloc((strlen(dataNascimento)+1)*sizeof(char));
        paciente->telefone = malloc((strlen(telefone)+1)*sizeof(char));
        paciente->genero = malloc((strlen(genero)+1)*sizeof(char));

        strcpy(paciente->nome, nome);
        strcpy(paciente->CPF, CPF);
        strcpy(paciente->dataNascimento, dataNascimento);
        strcpy(paciente->telefone, telefone);
        strcpy(paciente->genero, genero); 
    }

    printf("%s %s %s %s %s\n", paciente->nome, paciente->CPF, paciente->dataNascimento, paciente->telefone, paciente->genero);

    return paciente;
}

void desalocaPaciente(tPaciente *p){

    if(p != NULL){
        if(p->nome != NULL) free(p->nome);
        if(p->CPF != NULL) free(p->CPF);
        if(p->dataNascimento != NULL) free(p->dataNascimento);
        if(p->telefone != NULL) free(p->telefone);
        if(p->genero != NULL) free(p->genero);
        free(p);
    }
}


char* obtemCpfPaciente(tPaciente *p){
    return p->CPF;
}

char* obtemNomePaciente(tPaciente *p){
    return p->nome;
}

char* obtemDataPaciente(tPaciente *p){
    return p->dataNascimento;
}

char* obtemGeneroPaciente(tPaciente *p){
    return p->genero;
}

char* obtemTelefonePaciente(tPaciente *p){
    return p->telefone;
}