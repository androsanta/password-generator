/*
il programma crea password di lunghezza PSW_LEN, utilizzando CARAT caratteri, presenti
nel file caratteri.txt. nella password ogni carattere viene ripetuto RIPET volte, e sono
presenti al massimo NUM_ALPHA caratteri e NUM_DIG numeri. complessita esponenziale
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define CARAT 62 /* 26 minuscoli + 26 maiuscoli + 10 numeri */
#define PSW_LEN 8 /* lunghezza password */
#define RIPET 1 /* massime ripetizioni dei caratteri nella password */
#define NUM_DIG 5 /* numero massimo di numeri e/o caratteri nella password */
#define NUM_ALPHA 5
#define MAXWRDFILE 50000000

void inizializza(char *val, int *vett){
    FILE *fp;
    int i;
    if((fp=fopen("caratteri.txt", "r"))==NULL){
        printf("Errore apertura file2\n");
        exit(EXIT_FAILURE);
    }
    fscanf(fp, "%s", val);
    for(i=0; i<CARAT; i++) vett[i]=0;
    fclose(fp);
}

int calcola(char c){
    int num;
    if(isdigit(c)) num=c-'0';
    else if(isupper(c)) num=(c-'A')+10;
    else if(islower(c)) num=(c-'a')+10;
    return num;
}

FILE* apri_nuovo_file(char *nomefile){
    FILE *fp;
    char c=nomefile[0]++;
    if((fp=fopen(nomefile, "w"))==NULL){
        printf("Errore apertura file secondari\n");
        exit(EXIT_FAILURE);
    }
    printf("Generato file %c\n", c);
    return fp;
}

void disp_ripet(int pos, char *val, char *sol, int n, int k, FILE *fp, int *vett, int *num_car, int *num_dig, int *npsw, char *nomefile){
    int i, num;
    if(pos>=k){
        if((*npsw)>MAXWRDFILE){
            fclose(fp);
            fp=apri_nuovo_file(nomefile);
            (*npsw)=0;
        }
        fprintf(fp, "%s\n", sol);
        (*npsw)++;
        return;
    }
    for(i=0; i<n; i++){
        sol[pos]=val[i];
        if(isdigit(sol[pos]))
            (*num_dig)++;
        else
            (*num_car)++;
        num=calcola(sol[pos]);
        vett[num]++;
        if(vett[num]<=RIPET && (*num_car)<=NUM_ALPHA && (*num_dig)<=NUM_DIG)
            disp_ripet(pos+1, val, sol, n, k, fp, vett, num_car, num_dig, npsw, nomefile);
        vett[num]--;
        if(isdigit(sol[pos]))
            (*num_dig)--;
        else
            (*num_car)--;
    }
}

int main()
{
FILE *fp;
char val[CARAT+1], sol[PSW_LEN+1], nomefile[7]="a.txt\0"; /* perche la fscanf mette il tappo */
int vett[CARAT], num_car=0, num_dig=0, npsw=0;

if((fp=fopen("a.txt", "w"))==NULL){
    printf("Errore apertura file1\n");
    exit(EXIT_FAILURE);
}

sol[PSW_LEN]='\0';
inizializza(val, vett);
printf("Inizio generazione password\n");
disp_ripet(0, val, sol, CARAT, PSW_LEN, fp, vett, &num_car, &num_dig, &npsw, nomefile);
printf("Password generata\n\a");
fclose(fp);
return 0;
}
