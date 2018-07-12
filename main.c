#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contato{
    char nome1[20];
    char sobreNome[20];
    int numero;
};

typedef struct contato contato;

void troca(contato* a, contato* b){
    contato temp = *a;
    *a = *b;
    *b = temp;
}

int Mnome1(contato a, contato b){
    return a.nome1 < b.nome1;
}

int Mnome2(contato a, contato b){
    return a.sobreNome < b.sobreNome;
}

int Mnumero(contato a, contato b){
    return a.numero < b.numero;
}

void bb(contato* vet, int lin, int(*coisa)(contato,contato)) {
    int i, j;
    for (i = 0; i < lin - 1; i++) {
        for (j = 0; j < lin - 1; j++) {
            if (coisa(vet[j + 1], vet[j]) == 1) {
                troca(&vet[j + 1], &vet[j]);
            }
        }
    }
}

int Znome(contato a,char* nome){
    return strcmp(a.nome1,nome);
}

int ZsobreNome(contato a,char* nome){
    return strcmp(a.sobreNome,nome);
}

contato buscaBinariaCHAR(contato* vet, int lin, int (*regra)(contato,char*),char* nome) {
    int i;
    contato erro;
    erro.numero = -1;
    for (i = 0; i < lin; i++) {
        if (regra(vet[i], nome) == 0) {
            return vet[i];
        } else if ((i == (lin - 1) && (regra(vet[i], nome) != 0)) || (regra(vet[i], nome)) > 0) {
            return erro;
        }
    }
}

contato buscaBinariaINT(contato* vet, int lin, int num) {
    int i;
    contato erro;
    erro.numero = -1;
    for (i = 0; i < lin; i++) {
        if(vet[i].numero == num){
            return vet[i];
        }
        else if((i == (lin-1) && (vet[i].numero != num))|| (vet[i].numero > num)){
            return erro;
        }
    }
}

void salvaVetor(contato* pe,int lin){
    FILE* w = fopen("agenda.txt","w");
    int i;
    for (i = 0; i < lin; i++) {
        fprintf(w, "%s %s %i\n", pe[i].nome1, pe[i].sobreNome,pe[i].numero);
    }
}

void imprimeVetor(contato* pe,int lin){
    int i;
    for (i = 0; i < lin; i++) {
        printf("%s %s %i\n", pe[i].nome1, pe[i].sobreNome,pe[i].numero);
    }
}

void criaArquivoSTR(char* nome){
    FILE* p = fopen(nome, "w");
    fprintf(p,"");
    fclose(p);
}

void existe(char* arq, void(*faz)(char*)){
    FILE *oi = fopen(arq, "r" );
    if(!oi) {
        fclose(oi);
        faz(arq);
    }
    else{
        fclose(oi);
    }
}

void desalocaMemoria(contato* pe){
    free(pe);
}

contato* vetor(int lin){
    contato* mat;
    mat = malloc(sizeof(contato) * lin);
    return mat;
}

void insereContato(char* arq){
    contato pe;
    int S;
    puts("insira o primeiro nome");
    scanf("%s", pe.nome1);
    puts("insira o sobrenome nome");
    scanf("%s", pe.sobreNome);
    puts("insira o telefone");
    scanf("%i", &pe.numero);
    printf("Realmente deseja adicionar esse contato?\n"
                   "Nome: %s\n"
                   "Sobrenome: %s\n"
                   "Telefone: %i\n"
                   "1 - Sim\n"
                   "2 - Nao\n", pe.nome1, pe.sobreNome, pe.numero);
    scanf("%i", &S);
    if(S == 1){
        FILE* a = fopen(arq, "a");
        fprintf(a, "%s  %s  %i\n", pe.nome1, pe.sobreNome, pe.numero);
        fclose(a);
    } else{
        puts("Operacao cancelada");
    }
}

void popula(contato* vet,int lin) {
    FILE* ler = fopen("agenda.txt","r");
    int i;
    for (i = 0; i < lin; i++) {
        fscanf(ler,"%s", (vet[i].nome1));
        fscanf(ler,"%s", (vet[i].sobreNome));
        fscanf(ler,"%i", &(vet[i].numero));
    }
    fclose(ler);
}

void ordena(contato* vet, int lin){
    int op;
    puts("Deseja ordenar por qual item?\n"
                 "1 - Nome\n"
                 "2 - Sobrenome\n"
                 "3 - Telefone\n");
    scanf("%i", &op);
    if(op == 1){
        bb(vet,lin,Mnome1);
    }
    else if(op == 2){
        bb(vet,lin,Mnome2);
    }
    else{
        bb(vet,lin,Mnumero);
    }
}

contato busca(contato* vet, int lin){
    int op;
    contato pe;
    pe.numero = -1;
    printf("voce deseja buscar o contato a partir de qual item?\n"
                   "1 - Nome\n"
                   "2 - Sobrenome\n"
                   "3 - Telefone\n");
    scanf("%i", &op);
    if(op == 1){
        char nome[20];
        bb(vet,lin,Mnome1);
        puts("Insira o nome buscado\n");
        scanf("%s", nome);
        pe = buscaBinariaCHAR(vet,lin,Znome,nome);
        if(pe.numero == -1){
            puts("O contato desejado nao existe");
        }
        else{
            printf("%s %s %i\n", pe.nome1, pe.sobreNome,pe.numero);
        }
    }
    else if(op == 2){
        char nome[20];
        bb(vet,lin,Mnome2);
        puts("Insira o sobrenome buscado\n");
        scanf("%s", nome);
        pe = buscaBinariaCHAR(vet,lin,ZsobreNome,nome);
        if(pe.numero == -1){
            puts("contato desejado nao existe");
        }
        else{
            printf("%s %s %i\n", pe.nome1, pe.sobreNome,pe.numero);
        }
    }
    else if(op == 3){
        int num;
        bb(vet,lin,Mnumero);
        puts("Insira o telefone buscado\n");
        scanf("%i", &num);
        pe = buscaBinariaINT(vet,lin,num);
        if(pe.numero == -1){
            puts("telefone desejado nao existe");
        }
        else{
            printf("%s %s %i\n", pe.nome1, pe.sobreNome,pe.numero);
        }
    }
    return pe;
}

void apagaUM(contato pe, contato* vet, int lin) {
    int i;
    FILE *w = fopen("agenda.txt", "w");
    for (i = 0; i < lin; i++) {
        if((vet[i].numero == pe.numero)){
            contato a,b;
            a = vet[i];
            b = vet[lin - 1];
            vet[i] = b;
            vet[lin - 1] = a;
        }
    }
    salvaVetor(vet,lin-1);
    fclose(w);
}

void apaga(contato* vet, int lin){
    int op,cert;
    puts("voce deseja apagar um contato especifico ou todos?\n"
                 "1 - Contato especifico\n"
                 "2 - Todos");

    scanf("%i", &op);

    if(op == 2){
        puts("Voce tem certeza disso?\n"
                     "1 - Nao\n"
                     "2 - Sim");
        scanf("%i", &cert);
        if(cert == 2){
            criaArquivoSTR("agenda.txt");
            puts("Apagado");
        }
        else{
            puts("Operacao cancelada");
        }
    }
    else{
        contato pe;
        pe = busca(vet,lin);
        if(pe.numero == -1){
            return;
        }
        puts("Voce tem certeza disso?\n"
                     "1 - Nao\n"
                     "2 - Sim");
        scanf("%i", &cert);
        if(cert == 2){
            //pe = busca(vet,lin)
            apagaUM(pe,vet,lin);
            puts("Apagado");
        }
        else{
            puts("Operacao cancelada");
        }
    }
}

int contaLinhas(char* arquivo){
    FILE* f = fopen(arquivo, "r");
    char str[100];
    int l=0;

    while(fgets(str, 100, f) != NULL){
        l++;
    }
    fclose(f);
    return l;
}

int main(int argc, char *argv[]) {
    existe("agenda.txt", criaArquivoSTR);
    int res, lin, c = 1;
    while (c == 1) {
        puts("=============MENU==============");
        lin = contaLinhas("agenda.txt");
        contato *pe = vetor(lin);
        popula(pe, lin);
        printf("1 - Adicionar contato\n"
                       "2 - Mostrar agenda\n"
                       "3 - Ordenar agenda\n"
                       "4 - Mostrar contato especifico\n"
                       "5 - Remover da agenda\n");
        scanf("%i", &res);
        if (res == 1) {
            insereContato("agenda.txt");
        } else if (res == 2) {
            popula(pe, lin);
            imprimeVetor(pe, lin);
        } else if (res == 3) {
            ordena(pe, lin);
            imprimeVetor(pe, lin);
            int aux;
            puts("deseja ja salvar essa agenda?\n"
                         "1 - Sim\n"
                         "2 - Nao\n");
            scanf("%i", &aux);
            if (aux == 1) {
                salvaVetor(pe, lin);
            } else {
            }
        } else if (res == 4) {
            busca(pe, lin);
        } else if (res == 5) {
            apaga(pe, lin);
            popula(pe, lin - 1);
        }
        desalocaMemoria(pe);
        printf("\nDeseja mais alguma coisa?\n"
                       "1 - Sim\n"
                       "2 - Nao\n");
        scanf("%i", &c);
    }
    return 0;
}