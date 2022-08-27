#include <stdio.h>
#include <string.h>
#include <conio.h>

void interface_menu()
{
    system("cls");
    printf("\t\t\tSistema de Gerenciamento Compartilhado\n\n\n");
    printf("Menu de opcoes\n\n");
    printf("1) Cadastar Usina\n");
    printf("2) Cadastar Consumidor\n");
    printf("3) Cadastar Contrato entre Consumidor e Usina\n");
    printf("4) Consultar Usina Cadastrada\n");
    printf("5) Consultar Consumidor Cadastrado\n");
    printf("6) Excluir Usina\n");
    printf("7) Excluir Consumidor\n");
    printf("8) Encerrar Programa\n\n");
    printf("Digite uma opcao: ");
}

int valid_cpf(char id[])
{
    int i, valid, control;

    control = 0;

    for(i=0; i<14; i++){
        valid = id[i];
    }
    
    for(i=0; i<3; i++){
        if(id[i] >=48 && id[i] <=57){
            control++;
        }
    }
    if(id[3] == 46){ // Verifica o ponto
        control++;
    }
    for(i=4; i<7; i++){
        if(id[i] >=48 && id[i] <=57){
            control++;
        }
    }
    if(id[7] == 46){ // Verifica o ponto
        control++;
    }
    for(i=8; i<11; i++){
        if(id[i] >=48 && id[i] <=57){
            control++;
        }
    }
    if(id[11] == 45){ // Verifica o hifen
        control++;
    }
    for(i=12; i<14; i++){
        if(id[i] >=48 && id[i] <=57){
            control++;
        }
    }

//        printf("control = %d\n", control);

    if(control == 14){
        printf("\nCPF valido\n");
        return 0;
    }
    else{
        printf("\nCPF Invalido\n");
        return 1;
    }
}

int valid_cnpj(char id[])
{
    int i, valid, control;

    control = 0;

    for(i=0; i<18; i++){
        valid = id[i];
    }
    
    for(i=0; i<2; i++){
        if(id[i] >=48 && id[i] <=57){
            control++;
        }
    }
    if(id[2] == 46){
        control++;
    }
    for(i=3; i<6; i++){
        if(id[i] >=48 && id[i] <=57){
            control++;
        }
    }
    if(id[6] == 46){
        control++;
    }
    for(i=7; i<10; i++){
        if(id[i] >=48 && id[i] <=57){
            control++;
        }
    }
    if(id[10] == 47){
        control++;
    }
    for(i=11; i<15; i++){
        if(id[i] >=48 && id[i] <=57){
            control++;
        }
    }
    if(id[15] == 45){
        control++;
    }
    for(i=16; i<18; i++){
        if(id[i] >=48 && id[i] <=57){
            control++;
        }
    }

//        printf("control = %d\n", control);

    if(control == 18){
        printf("\nCNPJ Valido\n");
        return 0;
    }
    else{
        printf("\nCNPJ Invalido\n");
        return 1;
    }
}

int com_str(char str1[], char str2[])
{
    int tam_str1, tam_str2;
    int i, control, valid;

    tam_str1 = strlen(str1);
    tam_str2 = strlen(str2);

    if(tam_str1 != tam_str2){
        return 1;
    }
    else{

        control = 0;

        for(i=0; i<tam_str1; i++){
            if(str1[i] == str2[i]){
                control++;
            }
        }
//        printf("Control = %d\n", control);
        
        if(control == tam_str1){
            return 0;
        }
        else{return 1;}
    }
}

int valid_name(char name[]){
    int i, control=0, ascii, tam_name;

    tam_name = strlen(name);
    for(i=0; i<tam_name; i++){
        ascii = name[i];
        if(ascii == 124){
            control++;
        }
    }
    if(control == 0){
        printf("Nome Valido\n");
        return 0;
    }
    else{
        printf("Nome Invalido\nNao e permitido o uso do caracter '|'\n");
        return 1;
    }
}

int valid_data(int dia, int mes, int ano)
{
    if(mes<1 || mes>12 || ano<0){
        return 1;
    }
    else if(mes==2 && (dia>28 || dia<1) && ((ano%4 != 0) || ((ano%100==0 && (ano%400!=0))))){
        return 1;
    }
    else if((mes==4 || mes==6 || mes==9 || mes==11) && (dia<1 || dia>30)){
        return 1;
    }
    else if((mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12) && (dia<1 || dia>31)){
        return 1;
    }
    else if((mes==2) && (dia>29 || dia<1)){
        return 1;
    }
    else{
        return 0;
    }
}