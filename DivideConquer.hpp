#ifndef DIVIDECONQUER_HPP
#define DIVIDECONQUER_HPP
#include "ListaPaises.hpp"
using namespace std;

class DivideConquer {
private: 
    ListaPaises*    aListaPaises;
    

public: 
DivideConquer (){
    aListaPaises = nullptr;
}

    ListaPaises* getListaPaises(){
        return aListaPaises;
    }

    Pais* buscarPaisConMasFronteras(ListaPaises* pListaPaises){
        int mayor=0;
        Pais* paisConMasFronteras=nullptr;
        for(Pais* actual=pListaPaises->getPrimerPais(); actual!=nullptr; actual=actual->getSiguientePais()){
            if(actual->getCantidadFronteras() >= mayor && actual->getVisitado()==false){
                paisConMasFronteras=actual;
                mayor=paisConMasFronteras->getCantidadFronteras();
            }
        }
        if(paisConMasFronteras!=nullptr){
            paisConMasFronteras->setVisitado();
            return paisConMasFronteras;
        }
        return nullptr;
    }



//elije un color para pintar las fronteras dependiendo del numero de entrada;
    string elegirColor(int pColor){
        string cafe="fill:#97480B;fill-rule:evenodd";
        string azul="fill:#0241FC;fill-rule:evenodd";
        string amarillo="fill:#F5FC02;fill-rule:evenodd";
        string naranja="fill:#FC6802;fill-rule:evenodd";
        string verde="fill:#16FC02;fill-rule:evenodd"; 
        string celeste="fill:#02EFFC;fill-rule:evenodd";
        string morado="fill:#7C02FC;fill-rule:evenodd";
        string rojo="fill:#F9073E;fill-rule:evenodd";
        string rosa="fill:#F907EE;fill-rule:evenodd";
        string negro="fill:#000000;fill-rule:evenodd";
        string turquesa="fill:#138BAF;fill-rule:evenodd";
        if(pColor ==0) return cafe;
        if(pColor ==1) return azul;
        if(pColor ==2) return amarillo;
        if(pColor ==3) return naranja;
        if(pColor ==4) return verde;
        if(pColor ==5) return celeste;
        if(pColor ==6) return morado;
        if(pColor ==7) return rojo;
        if(pColor ==8) return rosa;
        if(pColor ==9) return negro;
        if(pColor ==10) return turquesa;
        else return "-1";
    }

//Devuelve el número del ultimo colo que pintó
    int pintarFronteras(ListaPaises* pLista, Pais* pPais, int pColor, int cantidadColores){
        int colorFrontera=pColor;
        pPais->setColor(elegirColor(colorFrontera));
        colorFrontera++;
        Pais* paisPintado=nullptr;
        if(cantidadColores==colorFrontera){
            colorFrontera=0;
        }
        for(Frontera* actual=pPais->getPrimeraFrontera(); actual!=nullptr; actual=actual->getSiguienteFrontera()){
            //if()

            actual->setColor(elegirColor(colorFrontera));
            paisPintado = pLista->buscarPais(actual->getNombre());
            paisPintado->setCantidadPintadas();
            paisPintado->setColor(actual->getColor());
            colorFrontera++;
            //cout<<"PINTAR "<<actual->getNombre()<<" "<<actual->getColor() <<" / "<<paisPintado->getNombre()<<" "<<paisPintado->getColor()<<endl;
            if(cantidadColores==colorFrontera){
                colorFrontera=0;
            }
        }
        return colorFrontera;
    }

    /*void Divide(ListaPaises* pLista, int pCantidadColores){
        int contadorPaises=0;
        int cantidadPaises=210;
        int a=0;
        int colorPaises=0;
        Pais* paisActual=nullptr;
        while(contadorPaises!=cantidadPaises){
            paisActual=buscarPaisConMasFronteras(pLista);
            if(paisActual==nullptr){
                break;
            }
            a++;
            pintarFronteras(paisActual, colorPaises, pCantidadColores);
            colorPaises++;
            contadorPaises++;
            if(pCantidadColores==contadorPaises){
                contadorPaises=0;
            }
        }
        pintarPaisesBlanco(pLista, pCantidadColores);
    }*/

    int Divide(ListaPaises* pLista, int pCantidadColores, int pContadorPaises, int pColorActual){
        int cantidadPaises=211;
        Pais* paisActual=nullptr;
        if(pContadorPaises >= cantidadPaises){
            return 0;
        }else{
            paisActual=buscarPaisConMasFronteras(pLista);
            pColorActual = pintarFronteras(pLista, paisActual, pColorActual, pCantidadColores);
            pContadorPaises++;
            return Divide(pLista, pCantidadColores, pContadorPaises, pColorActual);
        }

    }

    void pintarPaisesBlanco(ListaPaises* pLista, int pCantidadColores){
        string blanco="fill:#f2f2f2;fill-rule:evenodd";
        for(Pais* actual=pLista->getPrimerPais(); actual!=nullptr; actual=actual->getSiguientePais()){

            if(actual->getCantidadPintadas() >= 3){
                actual->setColor(blanco);
            }
        }
    }










};
#endif
