#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define TRUE  0
#define FALSE 1

int available[4]={1,5,2,0},i;
int p0[]={0,0,1,2, 0,0,1,2};
int p1[]={1,0,0,0, 1,7,5,0};
int p2[]={1,3,5,4, 2,3,5,6};
int p3[]={0,6,3,2, 0,6,5,2};
int p4[]={0,0,1,4, 0,6,5,6};

struct process{
    int alloc[4],maxm[4],need[4],finished_flag;
};
void initialize(struct process *P,int *p){
    for(i=0; i<8; i++)
        i<4?(P->alloc[i] = p[i]):(P->maxm[i-4]= p[i]);
    P->finished_flag=FALSE;
}
void calcNeed(struct process *P){
    for(i=0; i<4; i++)
        P->need[i] = P->maxm[i] - P->alloc[i];
}
void printMatrix(int name,struct process P){
    printf("P%d",name);
    for(i=0; i<4; i++)
        printf("%4d",P.alloc[i]);
    printf("\t");
    for(i=0; i<4; i++)
        printf("%4d",P.need[i]);
    printf("\t");
    for(i=0; i<4; i++)
        printf("%4d",available[i]);
    printf(" => ");
}
int reqNeed(struct process P){
    for(i=0; i<4; i++)
        if(P.need[i]>available[i])
            return 0;
    return 1;
}
void work(struct process *P){
    for(i=0; i<4; i++)
        available[i]+=P->alloc[i];

    P->finished_flag=TRUE;
}
int allDone(struct process P[]){
    for(i=0; i<5; i++)
        if(P[i].finished_flag == FALSE)
            return FALSE;
    return TRUE;
}
int main(){
    struct process P0,P1,P2,P3,P4;
    initialize(&P0,p0);
    initialize(&P1,p1);
    initialize(&P2,p2);
    initialize(&P3,p3);
    initialize(&P4,p4);

    calcNeed(&P0);
    calcNeed(&P1);
    calcNeed(&P2);
    calcNeed(&P3);
    calcNeed(&P4);

    printf("     ALLOCATED\t\t   NEED MATRIX\t\t   AVAILABLE MATRIX\n");
    struct process Pr[5]={P0,P1,P2,P3,P4};
    int m;
    char buf[3],safe_seq[50]="\nSafe Sequence : <";
    do{
        for(m=0; m<5; m++){
            if(Pr[m].finished_flag==FALSE){
                printMatrix(m,Pr[m]);
                if(reqNeed(Pr[m])){
                    work(&Pr[m]);
                    sprintf(buf,"P%d,",m);
                    strcat(safe_seq,buf);
                }
            for(i=0; i<4; i++)
                printf("%4d",available[i]);
            printf("\n");
            }

        }
    }while(allDone(Pr));

    safe_seq[strlen(safe_seq)-1]='>';
    puts(safe_seq);
    return 0;
}
