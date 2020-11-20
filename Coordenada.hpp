#ifndef COORDENADA_HPP
#define COORDENADA_HPP
using namespace std;

class Coordenada {
private: 
    int                     aPosicionCoordenada;
    Coordenada*             aSiguienteCoordenadaX;
    Coordenada*             aSiguienteCoordenadaY;
    float                   aCoordenadaX;
    float                   aCoordenadaY;

public: 
Coordenada (){
    aPosicionCoordenada     =0;
    aSiguienteCoordenadaX   =nullptr;
    aSiguienteCoordenadaY   =nullptr;
    aCoordenadaX            =0;
    aCoordenadaY            =0;

}

    int getPosicionCoordenada(){
        return aPosicionCoordenada;
    }

    void setPosicionCoordenada(){
        aPosicionCoordenada++;
    }

    Coordenada* getSiguienteCoordenadaX(){
        return aSiguienteCoordenadaX;
    }

    void setSiguienteCoordenadaX(Coordenada* pSiguienteCoordenada){
        aSiguienteCoordenadaX=pSiguienteCoordenada;
    }

    Coordenada* getSiguienteCoordenadaY(){
        return aSiguienteCoordenadaY;
    }

    void setSiguienteCoordenadaY(Coordenada* pSiguienteCoordenada){
        aSiguienteCoordenadaY=pSiguienteCoordenada;
    }

    float getCoordenadaEjeX(){
        return aCoordenadaX;
    }

    void setCoordenadaEjeX(float pCoordenadaX){
        aCoordenadaX=pCoordenadaX;
    }

    float getCoordenadaEjeY(){//DEBE SELECCIONAR EN EL PARAMETRO SOLO LOS X O SOLO LOS Y
        return aCoordenadaY;
    }

    void setCoordenadaEjeY(float pCoordenadaY){
        aCoordenadaY=pCoordenadaY;
    }

};
#endif
