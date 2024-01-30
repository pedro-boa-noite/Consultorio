#include "tLesao.h"

struct tLesao{
    char* diagnostico;
    char* regiao;
    int tamanho;
    int cirurgia;
    int crioterapia;
};

void registroBinarioLesoes(tLesao* l, FILE* file){

    if (file == NULL) {
        perror("Erro: arquivo não aberto para leitura");
        exit(EXIT_FAILURE);
    }

    int tamDiagnostico = strlen(l->diagnostico)+1;
    int tamRegiao = strlen(l->regiao)+1;

    fwrite(&tamDiagnostico, sizeof(int), 1, file);
    fwrite(l->diagnostico, sizeof(char), strlen(l->diagnostico)+1, file);
    fwrite(&tamRegiao, sizeof(int), 1, file);
    fwrite(l->regiao, sizeof(char), strlen(l->regiao)+1, file);

    fwrite(&l->tamanho, sizeof(int), 1, file);
    fwrite(&l->cirurgia, sizeof(int), 1, file);
    fwrite(&l->crioterapia, sizeof(int), 1, file);

    printf("%s %s %d %d %d\n", l->diagnostico, l->regiao, l->tamanho, l->cirurgia, l->crioterapia);
}

tLesao* cadastrarLesao(FILE* file, char* diagnostico, char* regiao, int tamanho, int cirurgia, int crioterapia){

    tLesao* lesao = calloc(1, sizeof(tLesao));

    int tamDiagnostico, tamRegiao;

    if(file != NULL){
        fread(&tamDiagnostico, sizeof(int), 1, file);
        lesao->diagnostico = malloc((tamDiagnostico)*sizeof(char));
        fread(lesao->diagnostico, sizeof(char), tamDiagnostico, file);

        fread(&tamRegiao, sizeof(int), 1, file);
        lesao->regiao = malloc((tamRegiao)*sizeof(char));
        fread(lesao->regiao, sizeof(char), tamRegiao, file);

        fread(&lesao->tamanho, sizeof(int), 1, file);
        fread(&lesao->cirurgia, sizeof(int), 1, file);
        fread(&lesao->crioterapia, sizeof(int), 1, file);
    } else{
        lesao->tamanho = tamanho;
        lesao->cirurgia = cirurgia;
        lesao->crioterapia = crioterapia;
        lesao->diagnostico = malloc((strlen(diagnostico)+1)*sizeof(char));
        lesao->regiao = malloc((strlen(regiao)+1)*sizeof(char));

        strcpy(lesao->diagnostico, diagnostico);
        strcpy(lesao->regiao, regiao);    
    }

    printf("criei lesao: %d %d %d %s %s\n", lesao->tamanho, lesao->cirurgia, lesao->crioterapia, lesao->diagnostico, lesao->regiao);
    return lesao;
}

void desalocaLesao(tLesao* l){
    if(l != NULL){
        if(l->diagnostico != NULL) free(l->diagnostico);
        if(l->regiao != NULL) free(l->regiao);
        free(l);
    }
}

char* obtemDiagnosticoLesao(tLesao* l){
    return l->diagnostico;
}

char* obtemRegiaoLesao(tLesao* l){
    return l->regiao;
}

int obtemTamanhoLesao(tLesao* l){
    return l->tamanho;
}

int obtemCirurgiaLesao(tLesao* l){
    return l->cirurgia;
}

int obtemCrioterapiaLesao(tLesao* l){
    return l->crioterapia;
}