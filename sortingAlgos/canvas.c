#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "canvas.h"
#include "libs/utils.h"
#include "libs/fileManager.h"
#include "libs/bubbles.h"
#include "libs/selection.h"
#include "libs/insertion.h"
#include "libs/merge.h"
#include "libs/quicksort.h"
#include "libs/profile.h"

#define null NULL
#define true 1
#define false 0

int start()
{
    navigation();
    return body();
}

int choseSorts()
{

    int choice;
    printf("\t_");
    scanf("%d", &choice);

    return choice < 1 || choice > 9 ? false: choice;

}

int body()
{
    int choice = choseSorts();

    while(!choice){
        printf("\n\tOPCAO INVALIDA! DIGITE NOVAMENTE: ");
        choice = choseSorts();
    }

    char mobs[9][50] = {
        "BUBBLE SORT", "SMART BUBBLE", "SELECTION SORT", 
        "INSERTION SORT", "MERGE SORT", "QUICK SORT", 
        "QUICK SORT DOIS PIVOS", "TESTE QSORT 2 PIVOS VETOR ALEATORIO",
        "TESTE QSORT DOIS PIVOS VETOR ORDENADO"
    };

    printf("\tVOCE ESCOLHEU %s.\n\n", mobs[choice-1]);

    int size;
    char filename[40];

    if(choice < 8){
        printf("\n Digite o nome do arquivo (default data.txt): ");
        scanf(" %s", filename);
    }else{
        strcpy(filename, "data.txt");
    }
    // createRandomValuesFile(filename);



    size = count(filename);
    
    if(!size){
        printf("ARQUIVO INVÁLIDO.");
        return false;
    }
    /**
     * Aloca o vetor com o tamanho necessário
     */ 
    int *v = (int*)malloc(size * sizeof(int));
    
    read(v, filename);
    
    
    if(sort(choice, v, size)){
        if(choice < 8)
            printf("\n\nARQUIVO ORDENADO A PARTIR DO ALGORITMO %s\n\n", mobs[choice-1]);
        return true;
    }
    return false;

}

int sort(int choice, int * v, int size)
{
        Data cmp;
        cmp.changes=0;
        cmp.cmp=0;
        cmp.start = clock();
        int diff = 0;

        if(choice < 8) printv(v, size);       
        
        switch(choice){
            
            case 1:
                bubbleSort(v, size, &cmp);
                break;
            case 2:
                smartBubble(v, size, &cmp);
                break;
            case 3:
                selectionSort(v, size, &cmp);
                break;
            case 4:
                insertionSort(v, size, &cmp);
                break;
            case 5:
                mergeSort(v, 0, size, &cmp);
                break;
            case 6:
                quickSort(v, 0, size, &cmp);
                break;
            case 7:
                dualPivotQuickSort(v, 0, size, &cmp);
                break;
            case 8:
                profile();
                break;
            case 9:
                worstCaseProfile();
                break;
        }
        
        cmp.end = clock();
        diff = (double)(cmp.end - cmp.start);


    if(choice < 8){
        printv(v, size);

        printf("Comparações: %lld\tTrocas: %lld\tTamanho do Vetor: %d\n", cmp.cmp, cmp.changes, size);
        printf("Tempo decorrido: %d ticks", diff);
    }

    return true;
}

void navigation()
{    
    printf("\n\n");
    printf("\t|------------------------------------------------------------|\n");
    printf("\t|                  ALGORITMOS DE ORDENACAO                   |\n");
    printf("\t|-------------------------------|----------------------------|\n");
    printf("\t|          ITERATIVOS           |");
    printf(   "          RECURSIVOS        |\n");

    printf("\t|-------------------------------|----------------------------|\n");
    
    printf("\t|     1 - BUBBLE SORT\t ");
    printf("\t|     5 - MERGE SORT\t     |\n");
    printf("\t|     2 - SMART BUBBLE\t ");
    printf("\t|     6 - QUICK SORT\t     |\n");
    printf("\t|     3 - SELECTION SORT ");
    printf("\t|     7 - QUICK SORT 2 PIVOS |\n");
    printf("\t|     4 - INSERTION SORT");
    printf("\t|\t                     |\n");
    printf("\t|\t\t\t\t\t                     |\n");
    printf("\t|     8 - TESTE QSORT 2 PIVO VETOR ALEATORIO\t\t     |\n");
    printf("\t|     9 - TESTE QSORT 2 PIVO ORDENADO \t\t\t     |\n");
    printf("\t--------------------------------------------------------------\n");
    printf("\n\n\t ESCOLHA UMA OPCAO: ");
}
