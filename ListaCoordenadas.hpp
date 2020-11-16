#ifndef LISTACOORDENADAS_HPP
#define LISTACOORDENADAS_HPP
#include "Coordenada.hpp"
using namespace std;


class ListaCoordenadas {
private: 
    Coordenada* aPrimeraCoordenada;
    Coordenada* aUltimaCoordenada;

public: 
ListaCoordenadas (){
    aPrimeraCoordenada  = nullptr;
    aUltimaCoordenad    = nullptr;
}

    Coordenada* getPrimeraCoordenada(){
        return aPrimeraCoordenada;
    }

    void setPrimeraCoordenada(Coordenada* pPrimeraCoordenada){
        aPrimeraCoordenada=pPrimeraCoordenada;
    }

    Coordenada* getUltimaCoordenada(){
        return aUltimaCoordenada;
    }

    void setUltimaCoordenada(Coordenada* pUltimaCoordenada){
        aUltimaCoordenada=pUltimaCoordenada;
    }

    void agregarCoordenadas(string pCoordenada){
		Coordenada* nuevaCoordenada = new Coordenada();
        if(aPrimeraCoordenada != nullptr){
            aUltimaCoordenada->setSiguienteCoordenada(nuevaCoordenada);
            aUltimoCoordenada=nuevaCoordenada;
            nuevaCoordenada->setSiguienteCoordenada(nullptr);
        }
        else {
            setPrimerCoordenada(nuevaCoordenada);
            setUltimoCoordenada(nuevaCoordenada);
        }
        nuevaCoordenada->setPosicionCoordenada();
        for()
    }

    void imprimirCoordenadas(){
        for(Coordenada* actual=aPrimerCoordenada; actual!= nullptr;actual=actual->getSiguienteCoordenada()){
            cout<<actual->getNombre()<<" "<<actual->getIdCoordenada()<<" "<<actual->getColor()<<" "<<actual->getPosicionSVG()<<endl;
        }    
    }


   



};

#endif