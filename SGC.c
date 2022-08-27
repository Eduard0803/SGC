#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "221008580.h"

#define TAM_CPF 14
#define TAM_CNPJ 18
#define TAM_NAME 150
#define ARQ_CONS "consumidores.txt"
#define ARQ_CONS1 "consumidores 1.txt"
#define ARQ_US "usinas.txt"
#define ARQ_US1 "usinas 1.txt"
#define ARQ_CONT "contratos.txt"
#define ARQ_CONT1 "contratos 1.txt"

char f_cnpj[TAM_CNPJ], f_name[TAM_NAME], f_id[TAM_CNPJ], f_rest[TAM_NAME];
int f_day, f_month, f_year;
float f_potencia;

typedef struct{
    char cnpj[TAM_CNPJ], name[TAM_NAME];
    int day, month, year;
    float potencia;
}USINA;

typedef struct{
    char id[TAM_CNPJ], name[TAM_NAME];
}CONSUMIDOR;

typedef struct{
    char cnpj[TAM_CNPJ], id[TAM_CNPJ];
    int day, month, year;
    float potencia;
}CONTRATO;

USINA u;
CONSUMIDOR c;
CONTRATO t;

void op1();     //  Procedimento para cadastrar Usinas
void op2();     //  Procedimento para cadastrar Consumidores
void op3();     //  Procedimento para cadastrar contratos entre Consumidores e Usinas
void op4();     //  Procediemto para consultar Usinas Cadastradas
void op5();     //  Procedimento para consultar Consumidores Cadastrados
void op6();     //  Procedimento para Excluir Usinas
void op7();     //  Procedimento para Excluir Consumidores
void op8();     //  Procedimento para Encerrar o Programa

int main()
{
    int op=0;

    while(op != 8){
        interface_menu();
        scanf("%d", &op);
        if(op == 1){
            op1();}
        else if(op == 2){
            op2();}
        else if(op == 3){
            op3();}
        else if(op == 4){
            op4();}
        else if(op == 5){
            op5();}
        else if(op == 6){
            op6();}
        else if(op == 7){
            op7();}
        else if(op == 8){
            op8();}
        else{printf("\nOpcao nao disponivel\n\nClique para Continuar");getch();}
    }
}

void op1()
{
    FILE *arq;
    int ret_valid_data=1, ret_valid_cnpj=1, ret_valid_name=1, cont=0, ret_strncmp, i;

    system("cls");
    printf("\t\tCadastro de Usinas\n\n");
    printf("Digite os dados a seguir:\n\n");
    while(ret_valid_cnpj == 1){             // Validação e Verificação para ver se o cnpj já foi cadastrado 
        printf("Siga o formato XX.XXX.XXX/XXXX-XX\n");
        printf("CNPJ: ");
        scanf(" %[^\n]", u.cnpj);
        system("cls");
        ret_valid_cnpj = valid_cnpj(u.cnpj);

        arq = fopen(ARQ_US, "r");
        while(fscanf(arq, " %[^|]|%[^|]|%d|%d|%d|%f", f_cnpj, f_name, &f_day, &f_month, &f_year, &f_potencia) !=EOF){
            ret_strncmp = strncmp(f_cnpj, u.cnpj, TAM_CNPJ);
            if(ret_strncmp == 0){ret_valid_cnpj = 1; printf("CNPJ ja cadastrado!\n");getch(); break;}
        }
        fclose(arq);
    }

    while(ret_valid_name == 1){
    printf("Nome: ");
    scanf(" %[^\n]", u.name);
    ret_valid_name = valid_name(u.name);
    }
    system("cls");

    while(ret_valid_data == 1){             //Validação da data digitada
        if(cont>0){printf("Data Incorreta!\n");}
        printf("Siga o formato DD/MM/YYYY\n");
        printf("Data de inicio do contrato: ");
        scanf("%d/%d/%d", &u.day, &u.month, &u.year);
        ret_valid_data = valid_data(u.day, u.month, u.year);
        system("cls");
        cont++;
    }

    u.potencia=0;
    cont=0;
    while(u.potencia <=0){                // Validação da potencia digitada
        if(cont>0){printf("Digite um Valor Acima de 0\n\n");}
        printf("Potencia estimada em MW: ");
        scanf("%f", &u.potencia);
        cont++;
    }
    system("cls");
    
    arq = fopen(ARQ_US, "a");       // Gravação dos dados no arquivo
    for(i=0; i<TAM_CNPJ; i++){
        fprintf(arq, "%c", u.cnpj[i]);        // Repetição para escrever um caracter por vez da string ent_cnpj
    }
    fprintf(arq, "|%s|%d|%d|%d|%.2f\n", u.name, u.day, u.month, u.year, u.potencia);
    fclose(arq);

    printf("Dados Gravados com sucesso!\n\n");
    printf("\nClique para Continuar");getch();
}

void op2()
{
    FILE *arq;
    int tam_id, ret_valid_id=1, ret_strncmp, ret_valid_name=1;

    system("cls");
    printf("\t\tCadastro de Consumidor\n\n");
    printf("Digite os dados a seguir: \n\n");

    while(ret_valid_id==1 || tam_id != 14 || tam_id != 18 || ret_strncmp == 0){
        printf("Siga o formato XX.XXX.XXX/XXXX-XX para CNPJ e XXX.XXX.XXX-XX para CPF\n");
        printf("Identificacao: ");
        scanf(" %[^\n]", c.id);

        arq = fopen(ARQ_CONS, "r");
        while(fscanf(arq, " %[^|]|%[^\n]", f_id, f_name) !=EOF){       // Verificação da id do consumidor
            ret_strncmp = strncmp(c.id, f_id, tam_id);
            if(ret_strncmp == 0){ret_valid_id = 1; printf("\nIdentificacao ja cadastrada!\n\n"); break;}
        }
        fclose(arq);

        if(ret_strncmp !=0){     // Validação da identificação do consumidor
            tam_id = strlen(c.id);

            if(tam_id == TAM_CPF){
                ret_valid_id = valid_cpf(c.id);
                if(ret_valid_id == 0){break;}
            }
            else if(tam_id == TAM_CNPJ){
                ret_valid_id = valid_cnpj(c.id);
                if(ret_valid_id == 0){break;}
            }
            else{printf("Dados Incorretos!\n\n");}
            printf("\nClique para Continuar");getch();}
    }
    while(ret_valid_name == 1){
    printf("\nNome: ");
    scanf(" %[^\n]", c.name);
    ret_valid_name = valid_name(c.name);
    }

    arq = fopen(ARQ_CONS, "a");     // Gravação dos dados no arquivo
    fprintf(arq, "%s|%s\n", c.id, c.name);
    fclose(arq);

    printf("\nDados Gravados com Sucesso!\n");
    printf("\nClique para Continuar");getch();
}

void op3()
{
    FILE *arq;
    int ret_strncmp, ret_valid_cnpj=1, ret_valid_id=1, ret_valid_data=1, tam_id, com_cnpj_id, i, cont=0;
    float s_potencia=0, d_potencia;

    system("cls");
    printf("\t\tCadastro de Contrato\n\n");
    printf("Digite os dados a seguir\n\n");
    while(ret_valid_cnpj == 1 || ret_strncmp != 0){     // Verificação e Validação do CNPJ da Usina
        printf("CNPJ da Usina: ");
        scanf(" %[^\n]", t.cnpj);
        ret_valid_cnpj = valid_cnpj(t.cnpj);
        if(ret_valid_cnpj == 0){
            arq = fopen(ARQ_US, "r");
            
            if(arq == NULL){
                printf("Erro na Abertura do Arquivo!\n");
            }
            while(fscanf(arq, " %[^|]|%[^|]|%d|%d|%d|%f", u.cnpj, u.name, &u.day, &u.month, &u.year, &u.potencia) !=EOF){
                ret_strncmp = strncmp(u.cnpj, t.cnpj, TAM_CNPJ);
                if(ret_strncmp == 0){
                    break;
                }
            }
            fclose(arq);
            if(ret_strncmp == 0){printf("\nCNPJ Encontrado com Sucesso!\n");}
            else{printf("\nErro na Busca do CNPJ!\n");}
            printf("\nClique para Continuar");getch();system("cls");
        }
    }

    while(ret_valid_id == 1 || ret_strncmp != 0){
        printf("\nSiga o formato XX.XXX.XXX/XXXX-XX para CNPJ e XXX.XXX.XXX-XX para CPF\n");    // Validação da id do Consumidor
        printf("Id do Consumidor: ");
        scanf(" %[^\n]", t.id);
        tam_id = strlen(t.id);
        com_cnpj_id = strncmp(t.cnpj, t.id, 18);
        if(tam_id == 14){
            ret_valid_id = valid_cpf(t.id);
        }
        else if(tam_id == 18 && com_cnpj_id != 0){
            ret_valid_id = valid_cnpj(t.id);
        }
        else if(com_cnpj_id == 0){
            ret_valid_id = 1;
            printf("\nUma usina nao pode ser sua propria consumidora!\n");
        }
        else{printf("Identificacao Invalida!\n");}
        
        if(ret_valid_id == 0){
            arq = fopen(ARQ_CONS, "r");
            while(fscanf(arq, " %[^|]|%[^\n]", c.id, c.name) !=EOF){        // Verificação do Consumidor
                ret_strncmp = strncmp(c.id, t.id, tam_id);
                if(ret_strncmp == 0){
                    break;
                }
            }
            fclose(arq);
            if(tam_id == 14 && ret_strncmp == 0){printf("CPF Encontrado com Sucesso!\n");}
            else if(tam_id == 18 && ret_strncmp == 0){printf("CNPJ Encontrado com Sucesso!\n");}
            else{printf("Erro ao Buscar Identificacao\n");}
            printf("\nClique para Continuar");getch();system("cls");
        }
    }

    while(ret_valid_data == 1){         // Validação da Data de inicio do contrato
        printf("Siga o formato DD/MM/YYYY\n");
        printf("Data de Inicio do Contrato: ");
        scanf("%d/%d/%d", &t.day, &t.month, &t.year);
        ret_valid_data = valid_data(t.day, t.month, t.year);
        if(ret_valid_data == 0){printf("Data Valida\n");}
        else{printf("Data Invalida\n");}
        printf("\nClique para Continuar");getch();system("cls");
    }

    t.potencia = 0;
    while(t.potencia <=0){
        if(cont>0){printf("Potencia Invalida\n");}      // Validação da potencia contratada
        printf("Potencia Contratada: ");
        scanf("%f", &t.potencia);
        cont++;
        FILE *arq1 = fopen(ARQ_CONT, "r");      // Não permite que o usuario contrate uma potencia maior que a potencia restante da usina
        while(fscanf(arq1, " %[^|]|%[^|]|%d|%d|%d|%f", f_cnpj, f_id, &f_day, &f_month, &f_year, &f_potencia) !=EOF){
            ret_strncmp = strncmp(f_cnpj, t.cnpj, 18);
            if(ret_strncmp == 0){
                s_potencia += f_potencia;
            }
        }
        fclose(arq1);
        d_potencia = u.potencia - s_potencia;
//        printf("d_potencia = %.2f\nu.potencia = %.2f\ns_potencia = %.2f\n", d_potencia, u.potencia, s_potencia);getch();
        if(t.potencia > d_potencia){t.potencia = 0;}
        s_potencia=0;
    }
    system("cls");
    printf("Dados Cadastrados:\n\n");
    printf("CNPJ: ");
    for(i=0; i<TAM_CNPJ; i++){
        printf("%c", t.cnpj[i]);
    }
    printf("\nId: %s\n", t.id);
    printf("Data: %d/%d/%d\n", t.day, t.month, t.year);
    printf("Potencia Contratada: %.2f\n", t.potencia);

    arq = fopen(ARQ_CONT, "a");
    for(i=0; i<TAM_CNPJ; i++){
        fprintf(arq, "%c", t.cnpj[i]);
    }
    fprintf(arq, "|%s|%d|%d|%d|%f\n", t.id, t.day, t.month, t.year, t.potencia);
    fclose(arq);
    
    printf("\nDados Gravados com Sucesso!\n");
    printf("Clique para Continuar");getch();
}

void op4()
{
    FILE *arq, *arq1;
    int ret_strncmp, ret1_strncmp, ret_valid_cnpj=1, cont_valid_cnpj=0, cont=0;
    char f_id1[TAM_CNPJ];
    float f_potencia1, s_potencia = 0.0, potencia1, p_potencia;

    while(ret_valid_cnpj == 1){
        system("cls");
        printf("\t\tConsulta a Usinas\n\n");
        if(cont_valid_cnpj>0){printf("Digite Novamente!\n");}
        printf("Digite o CNPJ da usina\n");
        printf("Seguindo o formato XX.XXX.XXX/XXXX-XX\n");
        scanf("%s", u.cnpj);
        ret_valid_cnpj = valid_cnpj(u.cnpj);
        cont_valid_cnpj++;
    }
    arq = fopen(ARQ_US, "r");

    while(fscanf(arq, " %[^|]|%[^|]|%d|%d|%d|%f", f_cnpj, f_name, &f_day, &f_month, &f_year, &f_potencia) !=EOF){
        ret_strncmp = strncmp(f_cnpj, u.cnpj, 18);
        if(ret_strncmp == 0){
            break;
        }
    }
    fclose(arq);
    system("cls");

    if(ret_strncmp == 0){
        printf("CNPJ: %s\n", f_cnpj);
        printf("Nome: %s\n", f_name);
        printf("Data de inicio das operacoes: %d/%d/%d\n", f_day, f_month, f_year);
        printf("Potencia estimada: %.2f\n\n", f_potencia);
    }
    else{printf("Falha ao procurar dados!\n\n");}

    printf("Consumidores Cadastrados\n\n");

    arq = fopen(ARQ_CONT, "r");
    while(fscanf(arq, " %[^|]|%[^|]|%d|%d|%d|%f", f_cnpj, f_id, &f_day, &f_month, &f_year, &f_potencia1) !=EOF){
        ret_strncmp = strncmp(u.cnpj, f_cnpj, 18);
        if(ret_strncmp == 0){
            s_potencia += f_potencia1;
            arq1 = fopen(ARQ_CONS, "r");
            while(fscanf(arq1, " %[^|]|%[^\n]", f_id1, f_name) !=EOF){
                ret1_strncmp = strcmp(f_id, f_id1);
                if(ret1_strncmp == 0){
                    printf("Identificacao: %s\nNome: %s\n", f_id1, f_name);
                    cont++;
                }
            }
            fclose(arq1);
        }
    }
    if(cont==0){
        printf("Nenhum Consumidor Cadastrado\n\n");
    }
    fclose(arq);
    p_potencia = 100.0-(s_potencia/f_potencia*100);
    printf("\nPercentual De Potencia Disponivel: %.2f%%\n", p_potencia);
    printf("Potencia Ainda Disponivel: %.2f\n\n", f_potencia-s_potencia);
    printf("\nClique para Continuar");getch();
}

void op5()
{
    FILE *arq, *arq1;
    int ret_com_str, ret_valid_id=1, ret_strncmp, tam_id, cont=0, cont1=0;
    char f_cnpj1[TAM_CNPJ], f_name1[TAM_NAME], f_rest[TAM_NAME];

    system("cls");
    printf("\t\tConsulta a Consumidores\n\n");
    printf("Digite a Identificacao do Consumidor\n");

    while(ret_valid_id == 1){
        if(cont>0){printf("\nDigite Novamente!\n");}
        printf("\nSiga o formato XX.XXX.XXX/XXXX-XX para CNPJ e XXX.XXX.XXX-XX para CPF\n");
        scanf("%s", c.id);
        tam_id = strlen(c.id);
        if(tam_id == 14){
            ret_valid_id = valid_cpf(c.id);
        }
        else if(tam_id == 18){
            ret_valid_id = valid_cnpj(c.id);
        }
        else{printf("Dados Incorretos!\n");}
        cont++;
    }
    system("pause");

    arq = fopen(ARQ_CONS, "r");
    while(fscanf(arq, " %[^|]|%[^\n]", f_id, f_name) !=EOF){
        ret_com_str = strncmp(f_id, c.id, tam_id);
//        printf("%s\n", id);getch();
        if(ret_com_str == 0){
            break;
        }
    }
    fclose(arq);
    system("cls");

    if(ret_com_str == 0){
        printf("Identificacao: %s\n", f_id);
        printf("Nome: %s\n\n", f_name);
    }
    else{printf("Falha ao procurar dados!\n\n");}

    printf("\t\tUsinas contratadas\n\n");
    arq = fopen(ARQ_CONT, "r");
    while(fscanf(arq, " %[^|]|%[^|]|%d|%d|%d|%f", f_cnpj, f_id, &f_day, &f_month, &f_year, &f_potencia) !=EOF){
        ret_strncmp = strncmp(f_id, c.id, tam_id);
        if(ret_strncmp == 0){
            arq1 = fopen(ARQ_US, "r");
            while(fscanf(arq1, " %[^|]|%[^|]|%[^\n]", f_cnpj1, f_name1, f_rest) != EOF){
                ret_strncmp = strncmp(f_cnpj, f_cnpj1, TAM_CNPJ);
                if(ret_strncmp == 0){
                    printf("CNPJ: %s\nNome: %s\n\n", f_cnpj1, f_name1);
                    cont1++;
                }
            }
        }
    }
    if(cont1==0){
        printf("Nenhuma Usina Contratada\n\n");
    }
    fclose(arq);
    fclose(arq1);
    printf("\n");
    system("pause");
}

void op6()
{
    FILE *arq, *arq1;
    int ret_strncmp, ret_valid_cnpj;

    system("cls");
    printf("\t\tExcluir Usina Cadastrada\n\n");
    printf("Digite o CNPJ: ");
    scanf(" %[^\n]", u.cnpj);
    if(valid_cnpj(u.cnpj)==0){

        arq = fopen(ARQ_US, "r");
        while(fscanf(arq, " %[^|]|%[^|]|%d|%d|%d|%f", f_cnpj, f_name, &f_day, &f_month, &f_year, &f_potencia) != EOF){
            ret_strncmp = strncmp(u.cnpj, f_cnpj, TAM_CNPJ);
            if(ret_strncmp == 0){break;}
        }
        rewind(arq);
        if(ret_strncmp != 0){
            printf("\nErro ao buscar usina\n");
        }
        else{
            arq1 = fopen(ARQ_US1, "a");

            while(fscanf(arq, " %[^|]|%[^|]|%d|%d|%d|%f", f_cnpj, f_name, &f_day, &f_month, &f_year, &f_potencia) != EOF){
            ret_strncmp = strncmp(u.cnpj, f_cnpj, TAM_CNPJ);
            if(ret_strncmp != 0){
                fprintf(arq1, "%s|%s|%d|%d|%d|%f\n", f_cnpj, f_name, f_day, f_month, f_year, f_potencia);
            }
        }
        fclose(arq);
        fclose(arq1);

        remove(ARQ_US);
        rename(ARQ_US1, ARQ_US);

        arq = fopen(ARQ_CONT, "r");
        arq1 = fopen(ARQ_CONT1, "a");
        while(fscanf(arq, " %[^|]|%[^|]|%d|%d|%d|%f", f_cnpj, f_id, &f_day, &f_month, &f_year, &f_potencia) !=EOF){
            ret_strncmp = strncmp(u.cnpj, f_cnpj, TAM_CNPJ);
            if(ret_strncmp != 0){
                fprintf(arq1, "%s|%s|%d|%d|%d|%.2f\n", f_cnpj, f_id, f_day, f_month, f_year, f_potencia);
            }
        }
        fclose(arq);
        fclose(arq1);

        remove(ARQ_CONT);
        rename(ARQ_CONT1, ARQ_CONT);

        printf("Usina Excluida com Sucesso!\n");
        }
        printf("\nClique para Continuar");getch();
    }
}

void op7()
{
    FILE *arq, *arq1;
    int ret_strncmp, ret_valid_id=1, tam_id;

    system("cls");
    printf("\t\tExcluir Consumidor Cadastrado\n\n");
    printf("Identificacao: ");
    scanf(" %[^\n]", c.id);

    tam_id = strlen(c.id);
    while(ret_valid_id !=0){        // Validação da id do usuario
        if(tam_id == TAM_CPF){
            ret_valid_id = valid_cpf(c.id);
        }
        else if(tam_id == TAM_CNPJ){
            ret_valid_id = valid_cnpj(c.id);
        }
        else{printf("Identificacao Invalida!\n");}
    }

    arq = fopen(ARQ_CONS, "r");
    while(fscanf(arq, " %[^|]|%[^\n]", f_id, f_name) !=EOF){        // Verificação da id do usuario
        ret_strncmp = strncmp(f_id, c.id, tam_id);
        if(ret_strncmp == 0){break;}
    }
    rewind(arq);
    if(ret_strncmp != 0){printf("Erro ao buscar consumidor\n");}
    else{
        arq1 = fopen(ARQ_CONS1, "a");
        while(fscanf(arq, " %[^|]|%[^\n]", f_id, f_name) !=EOF){        // Copia todos os outros consumidores em um arquivo auxiliar
            ret_strncmp = strncmp(f_id, c.id, tam_id);
            if(ret_strncmp != 0){
                fprintf(arq1, "%s|%s\n", f_id, f_name);
            }
        }
        fclose(arq);
        fclose(arq1);

        remove(ARQ_CONS);       // Apaga o arquivo principal
        rename(ARQ_CONS1, ARQ_CONS);        //Renomei o arquivo auxiliar com o nome do arquivo principal

        arq = fopen(ARQ_CONT, "r");
        arq1 = fopen(ARQ_CONT1, "a");
        while(fscanf(arq, " %[^|]|%[^|]|%[^\n]", f_cnpj, f_id, f_rest) !=EOF){     // Verificação dos contratos com o consumidor
            ret_strncmp = strncmp(f_id, c.id, tam_id);
            if(ret_strncmp != 0){
                fprintf(arq1, "%s|%s|%s\n", f_cnpj, f_id, f_rest);     // Copia todos os outros contratos em um arquivo auxiliar
            }
        }
        fclose(arq);
        fclose(arq1);

        remove(ARQ_CONT);       // Apaga o arquivo principal
        rename(ARQ_CONT1, ARQ_CONT);        // Renomeia o arquivo auxiliar com o nome do arquivo principal
        
        printf("Consumidor Excluido com Sucesso!\n");
    }
    printf("\nClique para Continuar");getch();
}

void op8(){
    system("cls");
    printf("\n\n\t\tObrigado por usar o SGC\n\n\n\nClique para Sair");  // Exibe uma mensagem ao usuario e chama a função exit()
    getch();
    system("cls");
    exit(0);
}