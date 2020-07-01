#ifndef _DATA_H_
#define _DATA_H_

#include <vector>
#include <stdio.h>

class Data
{
    private:

        int n_nos;
        int n_arcos;
        int no_origem;
        int no_destino;
        std::vector<int> fluxo_max;
        std::vector<std::vector<int>> arcos;

    public:

        Data(char* filePath);
        
        int getNNos();
        int getNArcos();
        int getNoOrigem();
        int getNoDestino();
        int getFluxoMaxArco(int arco);
        int getNoArco(int arco, int no);

};

#endif

