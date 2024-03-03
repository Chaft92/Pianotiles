#include <stdlib.h>
#include <time.h>
#include <stdio.h>

struct test{
    int premier;
    char deuxieme;
    int troisieme;
};


struct test tab[5];

int rempli(){
    srand(time(NULL));
    int i;
    int n;
    for(i=0;i<5;i++){
        tab[i].premier=rand()%40;
        printf(tab[i].premier);
    }
    return 0;
};

int main(){
    rempli();
    return 0;
}
