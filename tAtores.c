#include "tAtores.h"

#define MAX_PATH_LENGTH 100

struct tAtores{
    tPaciente** pacientes;
    int qtdPacientes;
    tSecretario** secretarios;
    int qtdSecretarios;
    tMedico** medicos;
    int qtdMedicos;
};

int idadeMedia(tAtores *a) {
    int somaIdades = 0;

    // Obtendo a data atual (09/11/23)
    int anoAtual = 2023;
    int mesAtual = 11;
    int diaAtual = 9;

    for (int i = 0; i < a->qtdPacientes; i++) {
        // Obtendo a data de nascimento do paciente
        int dia, mes, ano;
        sscanf(obtemDataPaciente(a->pacientes[i]), "%d/%d/%d", &dia, &mes, &ano);

        // Calculando a idade e somando à soma total
        int idade = anoAtual - ano;

        if (mesAtual < mes || (mesAtual == mes && diaAtual < dia)) {
            idade--;
        }

        somaIdades += idade;
    }

    // Calculando a idade média
    return somaIdades / a->qtdPacientes;
}

int pacientesMasculinos(tAtores* a){
    int qtd = 0;
    for(int i=0; i<a->qtdPacientes; i++){
        if(strcmp(obtemGeneroPaciente(a->pacientes[i]), "MASCULINO") == 0) qtd++;
    }
    return qtd;
}

int pacientesFemininos(tAtores* a){
    int qtd = 0;
    for(int i=0; i<a->qtdPacientes; i++){
        if(strcmp(obtemGeneroPaciente(a->pacientes[i]), "FEMININO") == 0) qtd++;
    }
    return qtd;
}

int pacientesOutros(tAtores* a){
    int qtd = 0;
    for(int i=0; i<a->qtdPacientes; i++){
        if(strcmp(obtemGeneroPaciente(a->pacientes[i]), "OUTROS") == 0) qtd++;
    }
    return qtd;
}

int imprimirPacientes(tFila* fila, tAtores* atores){
    char nome[50];
    int j=0, k=0, opcao;

    scanf("%[^\n]", nome);
    scanf("%*c");
    
    for(int i=0; i<atores->qtdPacientes; i++){
        if(strcmp(nome, obtemNomePaciente(atores->pacientes[i])) == 0) j++;
    }
    if(j == 0) return 0;

    printf("#################### BUSCAR PACIENTES #######################\nPACIENTES ENCONTRADOS:\n");

    tLista* lista = criaLista();
    for(int i=0; i<atores->qtdPacientes; i++){
        if(strcmp(nome, obtemNomePaciente(atores->pacientes[i])) == 0){
            insereLista(lista, atores->pacientes[i]);
            k++;
            printf("%d - %s (%s)\n", k, obtemNomePaciente(atores->pacientes[i]), obtemCpfPaciente(atores->pacientes[i]));
        }
    }
    printf("\n");

    printf("SELECIONE UMA OPCAO:\n\t(1) ENVIAR LISTA PARA IMPRESSAO\n\t(2) RETORNAR AO MENU PRINCIPAL\n############################################################\n");

    scanf("%d", &opcao);
    scanf("%*c");

    if(opcao == 1){
        insereDocumentoFila(fila, lista, imprimeNaTelaLista, imprimeEmArquivoLista, desalocaLista);
        printf("#################### BUSCAR PACIENTES #######################\nLISTA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU PRINCIPAL\n############################################################\n");
        scanf("%*c%*c");
    }

    return 1;
}

tMedico* EncontraMedico(tAtores* atores, char* usuario, char* senha){
    for(int i=0; i<atores->qtdMedicos; i++){
        if(strcmp(usuario, obtemUsuarioMedico(atores->medicos[i])) == 0 && strcmp(senha, obtemSenhaMedico(atores->medicos[i])) == 0) return atores->medicos[i];
    }

    return NULL;
}

tPaciente* ehIgualCpfPacientes(char* CPF, tAtores* a){
    for(int i=0; i<a->qtdPacientes; i++){
        if(strcmp(CPF, obtemCpfPaciente(a->pacientes[i])) == 0) return a->pacientes[i];
    }

    return NULL;
}

int ehIgualCpf(tAtores* a, char* CPF, char* ator){

    if (a == NULL || CPF == NULL || ator == NULL) {
        printf("Erro: algum dos parametros de ehIgualCpf e nulo.\n");
        exit(1);
    }

    if(a->qtdMedicos > 0 && (strcmp(ator, "medico") == 0)){
        for(int i=0; i<(a->qtdMedicos); i++){
            if(strcmp(CPF, obtemCpfMedico(a->medicos[i])) == 0) return 1;
        }    
    } else if(a->qtdPacientes > 0 && (strcmp(ator, "paciente") == 0)){
        for(int i=0; i<(a->qtdPacientes); i++){
            if(strcmp(CPF, obtemCpfPaciente(a->pacientes[i])) == 0) return 1;
        }    
    } else if(a->qtdSecretarios > 0 && (strcmp(ator, "secretario") == 0)){
        for(int i=0; i<(a->qtdSecretarios); i++){
            if(strcmp(CPF, obtemCpfSecretario(a->secretarios[i])) == 0) return 1;
        }    
    }

    return 0;
}

int insereSecretario(tAtores* a, FILE* file, char* caminho){

    char nome[100], CPF[20], dataNascimento[20], telefone[20], genero[20], usuario[20], senha[20], nivelAcesso[20];

    if(file == NULL){
        scanf("%[^\n]", nome);
        scanf("%*c");
        scanf("%[^\n]", CPF);
        scanf("%*c");
        scanf("%[^\n]", dataNascimento);
        scanf("%*c");
        scanf("%[^\n]", telefone);
        scanf("%*c");
        scanf("%[^\n]", genero);
        scanf("%*c");
        scanf("%[^\n]", usuario);
        scanf("%*c");
        scanf("%[^\n]", senha);
        scanf("%*c");
        scanf("%[^\n]", nivelAcesso);
        scanf("%*c");
        //printf("consegui escanear\n");
        if(ehIgualCpf(a, CPF, "secretario")) return 0;
    }

    (a->qtdSecretarios)++;

    a->secretarios = realloc(a->secretarios, sizeof(tSecretario*)*a->qtdSecretarios);
    if(file == NULL){
        a->secretarios[(a->qtdSecretarios) - 1] = criaSecretario(NULL, nome, CPF, dataNascimento, telefone, genero, usuario, senha, nivelAcesso);
        registroBinarioSecretarios(a->secretarios[(a->qtdSecretarios) - 1], caminho);
    } else{
        a->secretarios[(a->qtdSecretarios) - 1] = criaSecretario(file, nome, CPF, dataNascimento, telefone, genero, usuario, senha, nivelAcesso);
    }

    return 1;
}

int insereMedico(tAtores* a, FILE* file, char* caminho){
    char nome[100], CPF[20], dataNascimento[20], telefone[20], genero[20], usuario[20], senha[20], CRM[12];

    if(file == NULL){
        scanf("%[^\n]", nome);
        scanf("%*c");
        scanf("%[^\n]", CPF);
        scanf("%*c");
        scanf("%[^\n]", dataNascimento);
        scanf("%*c");
        scanf("%[^\n]", telefone);
        scanf("%*c");
        scanf("%[^\n]", genero);
        scanf("%*c");
        scanf("%[^\n]", CRM);
        scanf("%*c");
        scanf("%[^\n]", usuario);
        scanf("%*c");
        scanf("%[^\n]", senha);
        scanf("%*c");
        if(ehIgualCpf(a, CPF, "medico")) return 0;  
    }
    
    (a->qtdMedicos)++;

    a->medicos = realloc(a->medicos, sizeof(tMedico*)*a->qtdMedicos);
    if(file == NULL){
        a->medicos[(a->qtdMedicos) - 1] = criaMedico(NULL, nome, CPF, dataNascimento, telefone, genero, usuario, senha, CRM);
        registroBinarioMedicos(a->medicos[(a->qtdMedicos) - 1], caminho);
    } else{
        a->medicos[(a->qtdMedicos) - 1] = criaMedico(file, nome, CPF, dataNascimento, telefone, genero, usuario, senha, CRM);
    }

    return 1;
}

int inserePaciente(tAtores* a, FILE* file, char* caminho){

    char nome[100], CPF[20], dataNascimento[20], telefone[20], genero[20];

    if(file == NULL){
        scanf("%[^\n]", nome);
        scanf("%*c");
        scanf("%[^\n]", CPF);
        scanf("%*c");
        scanf("%[^\n]", dataNascimento);
        scanf("%*c");
        scanf("%[^\n]", telefone);
        scanf("%*c");
        scanf("%[^\n]", genero);
        scanf("%*c");
        printf("\nescaneei o paciente\n");
        if(ehIgualCpf(a, CPF, "paciente")) return 0;    
    }

    (a->qtdPacientes)++;

    a->pacientes = realloc(a->pacientes, sizeof(tPaciente*)*a->qtdPacientes);
    if(file == NULL){
        a->pacientes[(a->qtdPacientes) - 1] = criaPaciente(NULL, nome, CPF, dataNascimento, telefone, genero);
        registroBinarioPacientes(a->pacientes[(a->qtdPacientes) - 1], caminho);
    } else{
        a->pacientes[(a->qtdPacientes) - 1] = criaPaciente(file, nome, CPF, dataNascimento, telefone, genero);
    }

    return 1;
}

tAtores* atualizaBancoDados(tAtores* atores, char* caminho){
    char secretariosPath[MAX_PATH_LENGTH+20];
    sprintf(secretariosPath, "%s/secretarios.bin", caminho);
    FILE *secretariosFile = fopen(secretariosPath, "a+b");
    int leitura = 0;

    char sinalSecretario = 0;
    leitura = fread(&sinalSecretario, sizeof(char), 1, secretariosFile);

    while(sinalSecretario == 's' && leitura == 1){
        insereSecretario(atores, secretariosFile, caminho);
        leitura = fread(&sinalSecretario, sizeof(char), 1, secretariosFile);
    }

    char medicosPath[MAX_PATH_LENGTH+20];
    sprintf(medicosPath, "%s/medicos.bin", caminho);
    FILE *medicosFile = fopen(medicosPath, "a+b");

    char sinalMedico = 0;
    leitura = fread(&sinalMedico, sizeof(char), 1, medicosFile);

    while(sinalMedico == 's' && leitura == 1){
        insereMedico(atores, medicosFile, caminho);
        leitura = fread(&sinalMedico, sizeof(char), 1, medicosFile);
    }

    char pacientesPath[MAX_PATH_LENGTH+20];
    sprintf(pacientesPath, "%s/pacientes.bin", caminho);
    FILE *pacientesFile = fopen(pacientesPath, "a+b");
 
    char sinalPaciente = 0;
    leitura = fread(&sinalPaciente, sizeof(char), 1, pacientesFile);

    while(sinalPaciente == 's' && leitura == 1){
        inserePaciente(atores, pacientesFile, caminho);
        leitura = fread(&sinalPaciente, sizeof(char), 1, pacientesFile);
    }

    fclose(secretariosFile);
    fclose(medicosFile);
    fclose(pacientesFile);

    return atores;
}

/**
 * Função que cria um banco de atores vazia e retorna um ponteiro para ele.
 */
tAtores* criaAtores(char* caminho){
    tAtores* atores = calloc(1, sizeof(tAtores));

    if(strcmp(caminho, "null") == 0){
        atores->medicos = NULL;
        atores->pacientes = NULL;
        atores->secretarios = NULL;
    } else{
        atores = atualizaBancoDados(atores, caminho);
    }

    return atores;
}

/**
 * Função que recebe um ponteiro para um banco de atores e desaloca toda a memória
 * associada a ele. Essa função também desaloca todos os documentos associados a ele.
 * Essa função sempre verifica se o ponteiro é NULL antes de desalocar.
 */
void desalocaAtores(tAtores *a){
    if(a != NULL){
        if(a->medicos != NULL){
            for(int i=0; i<a->qtdMedicos; i++){
                desalocaMedico(a->medicos[i]);
            }
            free(a->medicos);
        }
        if(a->pacientes != NULL){
            for(int i=0; i<a->qtdPacientes; i++){
                desalocaPaciente(a->pacientes[i]);
            }
            free(a->pacientes);
        }
        if(a->secretarios != NULL){
            for(int i=0; i<a->qtdSecretarios; i++){
                desalocaSecretario(a->secretarios[i]);
            }
            free(a->secretarios);
        }
        free(a);
    }
}

int qtdMedicos(tAtores* a){
    return a->qtdMedicos;
}

int qtdPacientes(tAtores* a){
    return a->qtdPacientes;
}

int qtdSecretarios(tAtores* a){
    return a->qtdSecretarios;
}


char* VerificaAtor(tAtores* a, char* user, char* senha){
    for(int i = 0; i < a->qtdSecretarios; i++){
        if(strcmp(obtemSenhaSecretario(a->secretarios[i]), senha) == 0 && strcmp(obtemUsuarioSecretario(a->secretarios[i]), user) == 0){
            if(strcmp(obtemNivelAcesso(a->secretarios[i]), "ADMIN") == 0) return "user_admin";
            return "user_normal";
        }
    }
    for(int i = 0; i < a->qtdMedicos; i++){
        if(strcmp(obtemSenhaMedico(a->medicos[i]), senha) == 0 && strcmp(obtemUsuarioMedico(a->medicos[i]), user) == 0){
            return "medico";
        }
    }
    
    return NULL; // Retorna NULL se não encontrar nenhum ator correspondente
}

tPaciente* obtemPaciente(tAtores* a, int i){
    return a->pacientes[i];
}