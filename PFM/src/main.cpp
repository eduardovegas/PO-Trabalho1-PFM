#include "../include/Data.hpp"
#include <stdio.h>
#include <iostream>
#include <ilcplex/ilocplex.h>

void solve(Data& data);

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        printf("Usage:\n./bin instance\n");
        return 0;
    }

    Data data(argv[1]);
    solve(data);


    return 0;
}

void solve(Data& data)
{
    IloEnv env;
    IloModel modelo(env);


    ///////////////////////////////////////////////////////
    //variavel Xj: Xj = 1, 1 unidade sendo transportada pelo arco j
    IloNumVarArray x(env, data.getNArcos(), 0, IloInfinity);

    //adiciona a variavel x ao modelo
    for(int j = 0; j < data.getNArcos(); j++)
    {
        x[j].setBounds(0, data.getFluxoMaxArco(j));
        char name[100];
        sprintf(name, "X(%d)", j);
        x[j].setName(name);
        modelo.add(x[j]);
    }
    //fim das variaveis
    ///////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////
    //Criando a Função Objetivo (FO) 
    IloExpr sumX(env);
    for(int j = 0; j < data.getNArcos(); j++)
    {
        if(data.getNoArco(j, 1) == data.getNoDestino()){
            sumX += x[j];
        }
    }

    // Adicionando a FO
    modelo.add(IloMaximize(env, sumX));
    //////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////
    //Restricoes

    //Restricoes (1): todo fluxo que entra em um no menos o que sai deve ser igual a 0
    for(int i = 0; i < data.getNNos(); i++) 
    {   
        
        if(i+1 == data.getNoOrigem() || i+1 == data.getNoDestino())
            continue;
            
        IloExpr sumEX(env);
        IloExpr sumSX(env);

        for(int j = 0; j < data.getNArcos(); j++)
        {
            for(int n = 0; n < 2; n++)
            {
                if(data.getNoArco(j, n) == i+1)
                {
                    if(n == 0)
                    {
                        sumSX += x[j];
                    }
                    else
                    {
                        sumEX += x[j];
                    }       
                }
            }
        }

        IloRange r = (sumEX - sumSX == 0);
        char name[100];
        sprintf(name, "FLUX(%d)", i);
        r.setName(name);
        modelo.add(r);
    }

    //fim das restricoes
    ////////////////////////////////////////////////////////

    //resolve o modelo
    IloCplex pfm(modelo);
    pfm.setParam(IloCplex::TiLim, 2*60*60);
    pfm.setParam(IloCplex::Threads, 1);
//    pfm.setParam(IloCplex::Param::MIP::Interval, 1);
//    pfm.setParam(IloCplex::Param::MIP::Display, 5);
    pfm.exportModel("modelo.lp");

    try
    {
        pfm.solve();
    }
    catch(IloException& e)
    {
        std::cout << e;
    }

    std::cout << "\nstatus:" << pfm.getStatus() << std::endl;
    std::cout << "fluxo maximo obtido:" << pfm.getObjValue() << std::endl;
    for(int j = 0; j < data.getNArcos(); j++) 
    {
        if(pfm.getValue(x[j]) > 0)
        {
            printf("Fluxo do no #%d para o no #%d: ", data.getNoArco(j,0), data.getNoArco(j,1));
            std::cout << pfm.getValue(x[j]) << std::endl;
        }
    }

}

