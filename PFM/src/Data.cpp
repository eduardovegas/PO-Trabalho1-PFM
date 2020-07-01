#include "../include/Data.hpp"
#include <stdlib.h>

Data::Data(char* filePath)
{
    FILE* f = fopen(filePath, "r");

    if(!f)
    {
        printf("Problem while reading instance %s.\n", filePath);
        exit(1);
    }

    if(fscanf(f, "%d", &n_nos) != 1)
    {
        printf("Problem while reading instance %s.\n", filePath);
        exit(1);
    }

    if(fscanf(f, "%d", &n_arcos) != 1)
    {
        printf("Problem while reading instance %s.\n", filePath);
        exit(1);
    }

    if(fscanf(f, "%d", &no_origem) != 1)
    {
        printf("Problem while reading instance %s.\n", filePath);
        exit(1);
    }

    if(fscanf(f, "%d", &no_destino) != 1)
    {
        printf("Problem while reading instance %s.\n", filePath);
        exit(1);
    }

    //lendo arcos
    fluxo_max = std::vector<int>(n_arcos, 0);

    for(int i = 0; i < n_arcos; i++)
    {
        std::vector<int> vecAux(2);

        for(int j = 0; j < 2; j++)
        {
            if(fscanf(f, "%d", &vecAux[j]) != 1)
            {
                printf("Problem while reading instance.\n");
                exit(1);
            }
        }

        arcos.push_back(vecAux);

        //lendo fluxo maximo
        if(fscanf(f, "%d", &fluxo_max[i]) != 1)
        {
            printf("Problem while reading instance.\n");
            exit(1);
        }

    }
    

    /*printf("leu\n");

    for(int i = 0; i < n_arcos; i++)
    {
        printf("%d\n", fluxo_max[i]);
    }

    for(int i = 0; i < n_arcos; i++)
    {

        for(int j = 0; j < arcos[i].size(); j++){

            printf("%d ", arcos[i][j]);
        }

        puts("");
    }*/


    fclose(f);
}

int Data::getNNos()
{
    return n_nos;
}

int Data::getNArcos()
{
    return n_arcos;
}

int Data::getNoOrigem()
{
    return no_origem;
}

int Data::getNoDestino()
{
    return no_destino;
}

int Data::getFluxoMaxArco(int arco)
{
    return fluxo_max[arco];
}

int Data::getNoArco(int arco, int no)
{
    return arcos[arco][no];
}