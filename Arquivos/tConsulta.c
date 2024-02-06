#include "tConsulta.h"

struct tConsulta{
    char* data;
    int possuiDiabetes;
    int ehFumante;
    int possuiAlergia;
    int possuiHistoricoCancer;
    char* tipoPele;
    tLesao** lesoes;
    int qtdLesoes;
    char* CPFPaciente;
};

int numCirurgias(tConsulta* consulta){
    int num = 0;

    for(int i=0; i<consulta->qtdLesoes; i++){
        num += obtemCirurgiaLesao(consulta->lesoes[i]);
    }

    return num;
}

int numCrioterapias(tConsulta* consulta){
    int num = 0;

    for(int i=0; i<consulta->qtdLesoes; i++){
        num += obtemCrioterapiaLesao(consulta->lesoes[i]);
    }

    return num;
}

int tamanhoLesoesConsulta(tConsulta* consulta, int j){
    return obtemTamanhoLesao(consulta->lesoes[j]);
}

void colocaEncaminhamentoFila(tFila* fila, tConsulta* consulta, tMedico* medico, tPaciente* paciente){
    char especialidade[50], motivo[300];

    scanf("%[^\n]", especialidade);
    scanf("%*c");
    scanf("%[^\n]", motivo);
    scanf("%*c");

    tEncaminhamento* encaminhamento;
    if(medico == NULL){
        encaminhamento = criaEncaminhamento(obtemNomePaciente(paciente), obtemCpfPaciente(paciente), especialidade, motivo, "", "", consulta->data);
    }
    else{
        encaminhamento = criaEncaminhamento(obtemNomePaciente(paciente), obtemCpfPaciente(paciente), especialidade, motivo, obtemNomeMedico(medico), obtemCrmMedico(medico), consulta->data);
    }
    insereDocumentoFila(fila, encaminhamento, imprimeNaTelaEncaminhamento, imprimeEmArquivoEncaminhamento, desalocaEncaminhamento);
    //desalocaEncaminhamento(encaminhamento);
}

int colocaBiopsiaFila(tFila* fila, tConsulta* consulta, tMedico* medico, tPaciente* paciente){

    if(consulta->qtdLesoes == 0) return 0;

    tBiopsia* biopsia;
    if(medico == NULL){
        biopsia = criaBiopsia(obtemNomePaciente(paciente), obtemCpfPaciente(paciente), consulta->lesoes, consulta->qtdLesoes, "", "", consulta->data);
    }
    else{
        biopsia = criaBiopsia(obtemNomePaciente(paciente), obtemCpfPaciente(paciente), consulta->lesoes, consulta->qtdLesoes, obtemNomeMedico(medico), obtemCrmMedico(medico), consulta->data);
    }
    insereDocumentoFila(fila, biopsia, imprimeNaTelaBiopsia, imprimeEmArquivoBiopsia, desalocaBiopsia);
    //desalocaBiopsia(biopsia);

    return 1;
} 

void colocaReceitaFila(tFila* fila, tConsulta* consulta, tMedico* medico, tPaciente* paciente){
    char nomeMedicamento[50], tipoMedicamento[50], instrucoes[300], tipoUso[20];
    eTipoUso numero;
    int qntd;

    scanf("%[^\n]", tipoUso);
    scanf("%*c");
    scanf("%[^\n]", nomeMedicamento);
    scanf("%*c");
    scanf("%[^\n]", tipoMedicamento);
    scanf("%*c");
    scanf("%d", &qntd);
    scanf("%*c");
    scanf("%[^\n]", instrucoes);
    scanf("%*c");

    if(strcmp(tipoUso, "ORAL") == 0){
        numero = 0;   
    } 
    else{
        numero = 1;
    } 

    int dia, mes, ano;
    sscanf(consulta->data, "%d/%d/%d", &dia, &mes, &ano);
    char data[11];
    sprintf(data, "%d/%d/%d", dia, mes, ano);

    tReceita* receita;
    if(medico == NULL){
        receita = criaReceita(obtemNomePaciente(paciente), numero, nomeMedicamento, tipoMedicamento, instrucoes, qntd, "", "", data);    
    } 
    else{
        printf("entrei onde tem medico\n");
        receita = criaReceita(obtemNomePaciente(paciente), numero, nomeMedicamento, tipoMedicamento, instrucoes, qntd, obtemNomeMedico(medico), obtemCrmMedico(medico), data);
    }
    insereDocumentoFila(fila, receita, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
    //desalocaReceita(receita);
} 

void insereLesao(tConsulta* consulta, FILE* file, int i){

    char diagnostico[30], regiao[20];
    int tamanho, cirurgia, crioterapia;

    if(file == NULL){
        scanf("%[^\n]", diagnostico);
        scanf("%*c");
        scanf("%[^\n]", regiao);
        scanf("%*c");
        scanf("%d", &tamanho);
        scanf("%*c");
        scanf("%d", &cirurgia);
        scanf("%*c");
        scanf("%d", &crioterapia);
        scanf("%*c");    
        
        (consulta->qtdLesoes)++;
    }

    consulta->lesoes = realloc(consulta->lesoes, sizeof(tLesao*)*consulta->qtdLesoes);
    if(file == NULL){
        consulta->lesoes[(consulta->qtdLesoes) - 1] = cadastrarLesao(NULL, diagnostico, regiao, tamanho, cirurgia, crioterapia);
    } else{
        consulta->lesoes[i] = cadastrarLesao(file, diagnostico, regiao, tamanho, cirurgia, crioterapia);
    }
}

int escolheOpcao(int opcao, tConsulta* consulta, tFila* fila, tMedico* medico, tPaciente* paciente, char* caminho){
    switch(opcao){
        case 1:
        printf("#################### CONSULTA MEDICA #######################\nCADASTRO DE LESAO:\nDIAGNOSTICO CLINICO: \nREGIAO DO CORPO: \nTAMANHO: \nENVIAR PARA CIRURGIA: \nENVIAR PARA CRIOTERAPIA: \n");
        insereLesao(consulta, NULL, 0);
        printf("LESAO REGISTRADA COM SUCESSO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n############################################################\n");
        scanf("%*c%*c");
        return 1;
        case 2:
        printf("#################### CONSULTA MEDICA #######################\nRECEITA MEDICA:\nTIPO DE USO:\nNOME DO MEDICAMENTO:\nTIPO DE MEDICAMENTO:\nQUANTIDADE:\nINSTRUÇÕES DE USO:\n\n");
        colocaReceitaFila(fila, consulta, medico, paciente);
        printf("RECEITA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n############################################################\n");
        scanf("%*c%*c");
        return 1;
        case 3:
        if(!colocaBiopsiaFila(fila, consulta, medico, paciente)) printf("#################### CONSULTA MEDICA #######################\nNAO E POSSIVEL SOLICITAR BIOPSIA SEM LESAO CIRURGICA. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n############################################################\n");
        else printf("#################### CONSULTA MEDICA #######################\nSOLICITACAO DE BIOPSIA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n############################################################\n");
        scanf("%*c%*c");
        return 1;
        case 4:
        printf("#################### CONSULTA MEDICA #######################\nENCAMINHAMENTO:\nESPECIALIDADE ENCAMINHADA: \nMOTIVO:\n\n");
        colocaEncaminhamentoFila(fila, consulta, medico, paciente);
        printf("ENCAMINHAMENTO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n############################################################\n");
        scanf("%*c%*c");
        return 1;
        case 5:
        return 0;
        default:
        return 1;
    }
}

void registroBinarioConsultas(tConsulta* consulta, char* caminho){
    char caminhoCompleto[120];
    sprintf(caminhoCompleto, "%s/consultas.bin", caminho);
    FILE *consultasFile = fopen(caminhoCompleto, "ab");

    if(consultasFile == NULL) {
        perror("Erro ao abrir o arquivo de consultas");
        exit(EXIT_FAILURE);
    }

    int tamData = strlen(consulta->data)+1;
    int tamTipoPele = strlen(consulta->tipoPele)+1;
    int tamCPF = strlen(consulta->CPFPaciente)+1;
    char sinal = 's';

    fwrite(&sinal, sizeof(char), 1, consultasFile);

    fwrite(&tamData, sizeof(int), 1, consultasFile);
    fwrite(consulta->data, sizeof(char), strlen(consulta->data)+1, consultasFile);

    fwrite(&consulta->possuiDiabetes, sizeof(int), 1, consultasFile);
    fwrite(&consulta->ehFumante, sizeof(int), 1, consultasFile);
    fwrite(&consulta->possuiAlergia, sizeof(int), 1, consultasFile);
    fwrite(&consulta->possuiHistoricoCancer, sizeof(int), 1, consultasFile);

    fwrite(&tamTipoPele, sizeof(int), 1, consultasFile);
    fwrite(consulta->tipoPele, sizeof(char), strlen(consulta->tipoPele)+1, consultasFile);

    fwrite(&consulta->qtdLesoes, sizeof(int), 1, consultasFile);

    for(int i=0; i<consulta->qtdLesoes; i++){
        registroBinarioLesoes(consulta->lesoes[i], consultasFile);
    }

    fwrite(&tamCPF, sizeof(int), 1, consultasFile);
    fwrite(consulta->CPFPaciente, sizeof(char), strlen(consulta->CPFPaciente)+1, consultasFile);

    fclose(consultasFile);
}

tConsulta* criaConsulta(FILE* file, tFila* fila, char* caminho, tMedico* medico, tPaciente* paciente, char* data, int possuiDiabetes, int ehFumante, int possuiAlergia, int possuiHistoricoCancer, char* tipoPele){
    tConsulta* consulta = calloc(1, sizeof(tConsulta));

    int tamData, tamTipoPele, tamCPF;

    if(file != NULL){
        fread(&tamData, sizeof(int), 1, file);
        consulta->data = malloc((tamData)*sizeof(char));
        fread(consulta->data, sizeof(char), tamData, file);

        fread(&consulta->possuiDiabetes, sizeof(int), 1, file);
        fread(&consulta->ehFumante, sizeof(int), 1, file);
        fread(&consulta->possuiAlergia, sizeof(int), 1, file);
        fread(&consulta->possuiHistoricoCancer, sizeof(int), 1, file);

        fread(&tamTipoPele, sizeof(int), 1, file);
        consulta->tipoPele = malloc((tamTipoPele)*sizeof(char));
        fread(consulta->tipoPele, sizeof(char), tamTipoPele, file);

        fread(&consulta->qtdLesoes, sizeof(int), 1, file);

        for(int i=0; i<consulta->qtdLesoes; i++){
            insereLesao(consulta, file, i);
        }

        fread(&tamCPF, sizeof(int), 1, file);
        consulta->CPFPaciente = malloc((tamCPF)*sizeof(char));
        fread(consulta->CPFPaciente, sizeof(char), tamCPF, file);

    } else{
        consulta->data = malloc((strlen(data)+1)*sizeof(char));
        consulta->tipoPele = malloc((strlen(tipoPele)+1)*sizeof(char));
        consulta->CPFPaciente = malloc((strlen(obtemCpfPaciente(paciente))+1)*sizeof(char));

        consulta->lesoes = NULL;

        consulta->possuiDiabetes = possuiDiabetes;
        consulta->ehFumante = ehFumante;
        consulta->possuiAlergia = possuiAlergia;
        consulta->possuiHistoricoCancer = possuiHistoricoCancer;

        strcpy(consulta->data, data);
        strcpy(consulta->tipoPele, tipoPele);
        strcpy(consulta->CPFPaciente, obtemCpfPaciente(paciente));

        int opcao;
        while(1){
            printf("#################### CONSULTA MEDICA #######################\nESCOLHA UMA OPCAO:\n(1) CADASTRAR LESAO\n(2) GERAR RECEITA MEDICA\n(3) SOLICITACAO DE BIOPSIA\n(4) ENCAMINHAMENTO\n(5) ENCERRAR CONSULTA\n############################################################\n");
            scanf("%d", &opcao);
            scanf("%*c");
            if(!escolheOpcao(opcao, consulta, fila, medico, paciente, caminho)) break;
        }
    }

    return consulta;
}

void desalocaConsulta(tConsulta* c){
    
    if(c != NULL){
        if(c->data != NULL) free(c->data);
        if(c->tipoPele != NULL) free(c->tipoPele);
        if(c->lesoes != NULL){
            for(int i=0; i<c->qtdLesoes; i++){
                desalocaLesao(c->lesoes[i]);
            }
            free(c->lesoes);  
        }
        // if(c->nomePaciente != NULL) free(c->nomePaciente);
        if(c->CPFPaciente != NULL) free(c->CPFPaciente);
        // if(c->dataNascimentoPaciente != NULL) free(c->dataNascimentoPaciente);
        // if(c->telefonePaciente != NULL) free(c->telefonePaciente);
        // if(c->generoPaciente != NULL) free(c->generoPaciente);
        free(c);
    }
}

int obtemQtdLesoesConsulta(tConsulta* c){
    return c->qtdLesoes;
}

char* obtemCpfPacienteConsulta(tConsulta* c){
    return c->CPFPaciente;
}
