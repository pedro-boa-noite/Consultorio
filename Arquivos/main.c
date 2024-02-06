#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tDocumento.h"
#include "tLista.h"
#include "tFila.h"
#include "tAtores.h"
#include "tMedico.h"
#include "tPaciente.h"
#include "tSecretario.h"
#include "tConsulta.h"
#include "tRelatorio.h"

#define MAX_PATH_LENGTH 100

typedef struct{
    tConsulta** consultas;
    int qtdConsultas;
} tConsultas;

int executarFila(tFila* fila, char* caminho){
    int opcao;
    while(1){
        scanf("%d", &opcao);
        scanf("%*c");

        if(opcao == 2) return 1;
        
        printf("################### FILA DE IMPRESSAO MEDICA #####################\nEXECUTANDO FILA DE IMPRESSÃO:\n");
        imprimeFila(fila, caminho);
        printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU ANTERIOR\n###########################################################\n");
        
        scanf("%*c%*c");    
    }
    
    return 1;
}

int pacientesAtendidos(tAtores* atores, tConsultas* consultas){
    int qtd = 0, k = 0;
    for(int i=0; i<qtdPacientes(atores); i++){
        k=0;
        for(int j=0; j<consultas->qtdConsultas; j++){
            if(strcmp(obtemCpfPaciente(obtemPaciente(atores, i)), obtemCpfPacienteConsulta(consultas->consultas[j])) == 0) k++;
        }
        if(k!=0) qtd++;
    }
    return qtd;
}

int cirugiasTotais(tConsultas* consultas){
    int num=0;

    for(int i=0; i<consultas->qtdConsultas; i++){
        num += numCirurgias(consultas->consultas[i]);
    }

    return num;
}

int crioterapiasTotais(tConsultas* consultas){
    int num=0;

    for(int i=0; i<consultas->qtdConsultas; i++){
        num += numCrioterapias(consultas->consultas[i]);
    }

    return num;
}

int tamanhoLesoesConsultas(tConsultas* consultas){
    int num=0, qtd=0;

    for(int i=0; i<consultas->qtdConsultas; i++){

        for(int j=0; j<obtemQtdLesoesConsulta(consultas->consultas[i]); j++){
            num += tamanhoLesoesConsulta(consultas->consultas[i], j);
            qtd++;
        }
    }

    if(qtd != 0) return num/qtd;
    return 0;
}

int numTotalLesoes(tConsultas* consultas){
    int num=0;

    for(int i=0; i<consultas->qtdConsultas; i++){
        num += obtemQtdLesoesConsulta(consultas->consultas[i]);
    }

    return num;
}

void imprimirRelatorio(tFila* fila, tAtores* atores, tConsultas* consultas){
    int opcao;

    printf("NUMERO TOTAL DE PACIENTES ATENDIDOS: ");
    printf("%d\n", pacientesAtendidos(atores, consultas));
    printf("IDADE MEDIA: ");
    printf("%d\n", idadeMedia(atores));
    printf("DISTRIBUICAO POR GENERO:\n");
    printf("- FEMININO: ");
    printf("%d\n", pacientesFemininos(atores));
    printf("- MASCULINO: ");
    printf("%d\n", pacientesMasculinos(atores));
    printf("- OUTROS: ");
    printf("%d\n", pacientesOutros(atores));
    printf("TAMANHO MEDIO DAS LESOES: ");
    printf("%d\n", tamanhoLesoesConsultas(consultas));
    printf("NUMERO TOTAL DE LESOES: ");
    printf("%d\n", numTotalLesoes(consultas));
    printf("NUMERO TOTAL DE CIRURGIAS: ");
    printf("%d\n", cirugiasTotais(consultas));
    printf("NUMERO TOTAL DE CRIOTERAPIA: ");
    printf("%d\n", crioterapiasTotais(consultas));

    tRelatorio* relatorio = criaRelatorio(pacientesAtendidos(atores, consultas), idadeMedia(atores), pacientesFemininos(atores), pacientesMasculinos(atores), pacientesOutros(atores), tamanhoLesoesConsultas(consultas), numTotalLesoes(consultas), cirugiasTotais(consultas), crioterapiasTotais(consultas));

    printf("SELECIONE UMA OPCAO:\n\t(1) ENVIAR LISTA PARA IMPRESSAO\n\t(2) RETORNAR AO MENU PRINCIPAL\n############################################################\n");

    scanf("%d", &opcao);
    scanf("%*c");

    if(opcao == 1){
        insereDocumentoFila(fila, relatorio, imprimeNaTelaRelatorio, imprimeEmArquivoRelatorio, desalocaRelatorio);
        printf("#################### RELATORIO GERAL #######################\nRELATORIO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n############################################################\n");
        scanf("%*c%*c");
    } else{
        desalocaRelatorio(relatorio);
    }
}

int existeBancoDados(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

int insereConsulta(tConsultas* c, tAtores* a, tFila* fila, FILE* file, tMedico* medico, char* caminho){
    char CPF[20], data[20], tipoPele[5];
    int possuiDiabetes, ehFumante, possuiAlergia, possuiHistoricoCancer;

    if(file == NULL){
        scanf("%[^\n]", CPF);
        scanf("%*c");
        tPaciente* paciente = ehIgualCpfPacientes(CPF, a);
        if(paciente == NULL){
            return 0; 
        }
        printf("---\n-NOME: %s\n-DATA DE NASCIMENTO: %s\n---\n", obtemNomePaciente(paciente), obtemDataPaciente(paciente));
        printf("DATA DA CONSULTA: \nPOSSUI DIABETES: \nFUMANTE: \nALERGIA A MEDICAMENTO: \nHISTORICO DE CANCER: \nTIPO DE PELE: \n############################################################\n");
        scanf("%[^\n]", data);
        scanf("%*c");
        scanf("%d", &possuiDiabetes);
        scanf("%*c");
        scanf("%d", &ehFumante);
        scanf("%*c");
        scanf("%d", &possuiAlergia);
        scanf("%*c");
        scanf("%d", &possuiHistoricoCancer);
        scanf("%*c");
        scanf("%[^\n]", tipoPele);
        scanf("%*c");
    } 

    (c->qtdConsultas)++;

    c->consultas = realloc(c->consultas, sizeof(tConsulta**)*c->qtdConsultas);
    if(file == NULL){
        tPaciente* paciente = ehIgualCpfPacientes(CPF, a);
        c->consultas[(c->qtdConsultas) - 1] = criaConsulta(NULL, fila, caminho, medico, paciente, data, possuiDiabetes, ehFumante, possuiAlergia, possuiHistoricoCancer, tipoPele);
        registroBinarioConsultas(c->consultas[(c->qtdConsultas) - 1], caminho);
    } else{
        c->consultas[(c->qtdConsultas) - 1] = criaConsulta(file, fila, caminho, NULL, NULL, data, possuiDiabetes, ehFumante, possuiAlergia, possuiHistoricoCancer, tipoPele);
    }

    return 1;
}

tConsultas* atualizaBancoDadosConsultas(tConsultas* consultas, tAtores* atores, char* caminho){

    char consultasPath[MAX_PATH_LENGTH+20];
    sprintf(consultasPath, "%s/consultas.bin", caminho);
    FILE *consultasFile = fopen(consultasPath, "a+b");
    int leitura = 0;

    char sinalConsulta = 0;
    leitura = fread(&sinalConsulta, sizeof(char), 1, consultasFile);

    while(sinalConsulta == 's' && leitura == 1){
        insereConsulta(consultas, atores, NULL, consultasFile, NULL, caminho);
        leitura = fread(&sinalConsulta, sizeof(char), 1, consultasFile);
    }

    fclose(consultasFile);

    return consultas;
}

tConsultas* criaConsultas(char* caminho, tAtores* atores){
    tConsultas* consultas = calloc(1, sizeof(tConsultas));

    char consultasPath[MAX_PATH_LENGTH+20];
    sprintf(consultasPath, "%s/consultas.bin", caminho); //CONFERE SE EXISTEM ARQUIVOS .bin

    if(strcmp(caminho, "null") == 0 || !existeBancoDados(consultasPath)){
        consultas->consultas = NULL;
    } else{
        consultas = atualizaBancoDadosConsultas(consultas, atores, caminho);
    }

    return consultas;
}

void desalocaConsultas(tConsultas* c){
    if(c != NULL){
        if(c->consultas != NULL){
            for(int i=0; i<c->qtdConsultas; i++){
                desalocaConsulta(c->consultas[i]);
            }   
            free(c->consultas); 
        }
        free(c);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void exibeMenuMedico(){
    printf("####################### MENU PRINCIPAL #########################\nESCOLHA UMA OPCAO:\n(4) REALIZAR CONSULTA\n(5) BUSCAR PACIENTES\n(6) RELATORIO GERAL\n(7) FILA DE IMPRESSAO\n(8) FINALIZAR O PROGRAMA\n###############################################################\n");
}

void exibeMenuUser(){
    printf("####################### MENU PRINCIPAL #########################\nESCOLHA UMA OPCAO:\n(2) CADASTRAR MEDICO\n(3) CADASTRAR PACIENTE\n(5) BUSCAR PACIENTES\n(6) RELATORIO GERAL\n(7) FILA DE IMPRESSAO\n(8) FINALIZAR O PROGRAMA\n###############################################################\n");
}

void exibeMenuSupremo(){
    printf("####################### MENU PRINCIPAL #########################\nESCOLHA UMA OPCAO:\n(1) CADASTRAR SECRETARIO\n(2) CADASTRAR MEDICO\n(3) CADASTRAR PACIENTE\n(4) REALIZAR CONSULTA\n(5) BUSCAR PACIENTES\n(6) RELATORIO GERAL\n(7) FILA DE IMPRESSAO\n(8) FINALIZAR O PROGRAMA\n###############################################################\n");
}

void printaDadosComuns(){
    printf("NOME COMPLETO: \nCPF: \nDATA DE NASCIMENTO: \nTELEFONE: \nGENERO: \n");
}

void printaTerminacao(){
    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n############################################################\n");
}

void printaCpfRepetido(){
    printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");
}

void printaCadastroSecretario(){
    printf("#################### CADASTRO SECRETARIO #######################\n");
    printaDadosComuns();
    printf("NOME DE USUARIO: \nSENHA: \nNIVEL DE ACESSO: \n\n");
}

void printaCadastroMedico(){
    printf("#################### CADASTRO MEDICO #######################\n");
    printaDadosComuns();
    printf("CRM: \nNOME DE USUARIO: \nSENHA: \n\n");
}

void printaCadastroPaciente(){
    printf("#################### CADASTRO PACIENTE #######################\n");
    printaDadosComuns();
}

void escolheOperacao(tConsultas* consultas, tAtores* atores, tFila* fila, tMedico* medico, char* ator, int opcao, char* caminho, char* caminhoFila){
    switch (opcao){

        case 1: //"insere" retorna um inteiro que indica oq deve imprimir
        if(strcmp(ator, "medico") == 0 || strcmp(ator, "user_normal") == 0) break;
        printaCadastroSecretario();
        if(insereSecretario(atores, NULL, caminho)){
            printaTerminacao();  
            scanf("%*c%*c");
        } else printaCpfRepetido(); 
        break;

        case 2:
        if(strcmp(ator, "medico") == 0) break;
        printaCadastroMedico();
        if(insereMedico(atores, NULL, caminho)){
            printaTerminacao(); 
            scanf("%*c%*c");
        } 
        else printaCpfRepetido();
        break;

        case 3: 
        if(strcmp(ator, "medico") == 0) break;
        printaCadastroPaciente();
        if(inserePaciente(atores, NULL, caminho)){
            printaTerminacao();
            scanf("%*c%*c");
        }
        else printaCpfRepetido();
        break;

        case 4:
        if(strcmp(ator, "user_normal") == 0) break;
        printf("#################### CONSULTA MEDICA #######################\nCPF DO PACIENTE: \n");
        if(!insereConsulta(consultas, atores, fila, NULL, medico, caminho)){
            printf("PACIENTE SEM CADASTRO\n\nPRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU INICIAL\n############################################################\n");
            scanf("%*c%*c");
        }
        break;

        case 5:
        printf("#################### BUSCAR PACIENTES #######################\nNOME DO PACIENTE:\n############################################################\n");
        if(!imprimirPacientes(fila, atores)){
            printf("#################### BUSCAR PACIENTES #######################\nNENHUM PACIENTE FOI ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR \n############################################################\n");
            scanf("%*c%*c");
        } 
        break;

        case 6:
        printf("#################### RELATORIO GERAL #######################\n");
        imprimirRelatorio(fila, atores, consultas);
        break;

        case 7:
        printf("################### FILA DE IMPRESSAO MEDICA #####################\nESCOLHA UMA OPCAO:\n\t (1) EXECUTAR FILA DE IMPRESSAO\n\t (2) RETORNAR AO MENU ANTERIOR\n############################################################\n");
        executarFila(fila, caminhoFila);
        break;

        case 8:
        desalocaAtores(atores);
        desalocaConsultas(consultas);
        desalocaFila(fila);
        exit(0);

        default:
        break;
    }
}

void rodarSistema(tConsultas* consultas, tAtores* atores, tFila* fila, char* ator, tMedico* medico, char* caminho, char* caminhoFila){
    int opcao;

    while(1){
        if(strcmp(ator, "medico") == 0) exibeMenuMedico(); 
        else if(strcmp(ator, "user_normal") == 0) exibeMenuUser();
        else if(strcmp(ator, "user_admin") == 0) exibeMenuSupremo();
        scanf("%d", &opcao);
        scanf("%*c");
        escolheOperacao(consultas, atores, fila, medico, ator, opcao, caminho, caminhoFila);
    }
}

void solicitacaoLogin(tConsultas* consultas, tAtores* atores, tFila* fila, char* caminho, char* caminhoFila){

    printf("######################## ACESSO MINI-SADE ######################\nDIGITE SEU LOGIN:\nDIGITE SUA SENHA:\n###############################################################\n");
    
    char usuario[20], senha[20];
    scanf("%[^\n]", usuario);
    scanf("%*c");
    scanf("%[^\n]", senha);
    scanf("%*c");

    char *ator = VerificaAtor(atores, usuario, senha);

    tMedico* medico = EncontraMedico(atores, usuario, senha); 

    if(ator == NULL){
        printf("SENHA INCORRETA OU USUARIO INEXISTENTE\n");
        solicitacaoLogin(consultas, atores, fila, caminho, caminhoFila);
    } else{
        rodarSistema(consultas, atores, fila, ator, medico, caminho, caminhoFila);
    }
}

int main(int argc, char const* argv[]){

    const char* caminhoConfig = argv[1];

    printf("################################################\nDIGITE O CAMINHO DO BANCO DE DADOS:\n################################################\n");
    char path[MAX_PATH_LENGTH], pathBanco[MAX_PATH_LENGTH+50], pathFila[MAX_PATH_LENGTH+50];
    scanf("%[^\n]", path);
    scanf("%*c");

    sprintf(pathBanco, "%s/%s", caminhoConfig, path);
    sprintf(pathFila, "%s/saida", caminhoConfig);

    char secretariosPath[MAX_PATH_LENGTH+70];
    sprintf(secretariosPath, "%s/secretarios.bin", pathBanco); //CONFERE SE EXISTEM ARQUIVOS .bin

    tFila* fila = criaFila();

    if(!existeBancoDados(secretariosPath)){ //caso de ser o primeiro acesso
        tAtores* atores = criaAtores("null");
        tConsultas* consultas = criaConsultas("null", atores);
        printaCadastroSecretario();
        insereSecretario(atores, NULL, pathBanco);
        solicitacaoLogin(consultas, atores, fila, pathBanco, pathFila);
    } else{ //caso de ja haver banco de dados
        tAtores* atores = criaAtores(pathBanco);
        tConsultas* consultas = criaConsultas(pathBanco, atores);
        solicitacaoLogin(consultas, atores, fila, pathBanco, pathFila);
    }

    return 0;
}
