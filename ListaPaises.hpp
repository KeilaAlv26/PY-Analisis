#ifndef LISTAPAISES_HPP
#define LISTAPAISES_HPP
#include "Pais.hpp"
#include <string.h>
#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <sstream>


using namespace std;

class ListaPaises {
private: 
    int             aCantidadPaises;
    int             aPaisesEnBlanco;
    Pais*           aPrimerPais;
    Pais*           aUltimoPais;

public: 
ListaPaises (){
    aCantidadPaises =0;
    aPaisesEnBlanco =0;
    aPrimerPais     =nullptr;
    aUltimoPais     =nullptr;
}

    int getCantidadPaises(){
        return aCantidadPaises;
    }

    void setCantidadPaises(){
        aCantidadPaises++;
    }

    
    int getPaisesEnBlanco(){
        return aPaisesEnBlanco;
    }

    void setPaisesEnBlanco(){
        aPaisesEnBlanco++;
    }

    Pais* getPrimerPais(){
        return aPrimerPais;
    }

    void setPrimerPais(Pais* pPrimerPais){
        aPrimerPais=pPrimerPais;
    }

    Pais* getUltimoPais(){
        return aUltimoPais;
    }

    void setUltimoPais(Pais* pUltimoPais){
        aUltimoPais=pUltimoPais;
    }

   

    void agregarPais(string pNombre, string pIdPais, string pColor, int pPosicionSVG, string pCoordenadas)
    {
		Pais* nuevoPais = new Pais();
        if(aPrimerPais != nullptr){
            aUltimoPais->setSiguientePais(nuevoPais);
            aUltimoPais=nuevoPais;
            nuevoPais->setSiguientePais(nullptr);
        }
        else {
            setPrimerPais(nuevoPais);
            setUltimoPais(nuevoPais);
            nuevoPais->setSiguientePais(nullptr);
        }
        setCantidadPaises();
        nuevoPais->setColor(pColor);
        nuevoPais->setIdPais(pIdPais);
        nuevoPais->setNombre(pNombre);
        nuevoPais->setPosicionSVG(pPosicionSVG);
        nuevoPais->setStringCoordenada(pCoordenadas);
        saveCoordenadas(nuevoPais, pCoordenadas);
    }

    bool eliminarPais(string pNombre)
    {
        Pais* anterior=nullptr;
        for(Pais* actual=aPrimerPais; actual!=nullptr; actual=actual->getSiguientePais()){
            if(actual->getNombre() == pNombre){
                if(anterior==nullptr){
                    setPrimerPais(actual->getSiguientePais());
                    actual->setSiguientePais(nullptr);
                    return true;
                }
                else{
                    anterior->setSiguientePais(actual->getSiguientePais());
                    return true;
                }
                
            } 
            anterior=actual;
        }
        return false;
    }

    void imprimirPaises()
    {
        for(Pais* actual=aPrimerPais; actual!= nullptr;actual=actual->getSiguientePais()){
            cout<<actual->getNombre()<<" "<<actual->getNumeroColor()<<" "<<actual->getCantidadFronteras()<<endl;
            //imprimirCoordenadasX(actual);
            //imprimirCoordenadasY(actual);
        }    
    }

    void imprimirCoordenadasX(Pais* pPais){
        cout<<"X ";
        for(Coordenada* temporal=pPais->getPrimeraCoordenadaX(); temporal!= nullptr; temporal=temporal->getSiguienteCoordenadaX()){
            cout<<temporal->getCoordenadaEjeX()<<", ";
        }
        cout<<"\n\n";
    }

    void imprimirCoordenadasY(Pais* pPais){
        cout<<"Y ";
        for(Coordenada* temporal=pPais->getPrimeraCoordenadaY(); temporal!= nullptr; temporal=temporal->getSiguienteCoordenadaY()){
            cout<<temporal->getCoordenadaEjeY()<<", ";
        }
        cout<<"\n\n";
    }

    int strTok (string pCadena, char delimitador)
    {
        string nueva;
        int largo = pCadena.length();
        for (int i = 0; i < largo; i++){
            if (pCadena[i] == delimitador){
                nueva = pCadena.substr(i);
                return i;
            } 		
        }return -1;
    }

    string getCoordenadas(string pCoordenadas)
    {
        string retornoCoordenadas;
        int posicionDelimitador=0;
        int ascii=0;
        int cont=0;
        int largoPCoordenadas=pCoordenadas.length();
        while(posicionDelimitador != -1){
            posicionDelimitador = strTok (pCoordenadas, (char)' ');
            ascii=pCoordenadas[0];
            if(ascii != 109 && ascii != 122 && ascii != 108 && ascii!= 77){
                retornoCoordenadas = retornoCoordenadas +  pCoordenadas.substr(0,posicionDelimitador) + ",";
            }
            pCoordenadas = pCoordenadas.substr(posicionDelimitador+1, largoPCoordenadas);
            cont++;
        } 
        retornoCoordenadas= retornoCoordenadas + "/";
        return retornoCoordenadas;
    }

    string floatToString (float number){
        std::ostringstream buff;
        buff<<number;
        return buff.str();
    }

    string getSumaCoordenadas(string pCoordenadas)
    {
        int largoPCoordenadas=pCoordenadas.length();
        int posicionDelimitador=0;
        int contador=0;
        float sumaAnteriorX=0;
        float sumaAnteriorY=0;
        float suma=0;
        string sumaCoordenadas;
        while(pCoordenadas != "/"){
            posicionDelimitador = strTok (pCoordenadas, (char)',');
            if(contador%2 == 0){ //si es una coordenada X
                suma = stof(pCoordenadas.substr(0, posicionDelimitador)) + sumaAnteriorX;
                sumaAnteriorX=suma;
                sumaCoordenadas= sumaCoordenadas + floatToString(suma) + ',';
            }else{
                suma = stof(pCoordenadas.substr(0, posicionDelimitador)) + sumaAnteriorY;
                sumaAnteriorY=suma;
                sumaCoordenadas= sumaCoordenadas + floatToString(suma) + ',';
            }
            contador++;
            pCoordenadas = pCoordenadas.substr(posicionDelimitador+1, largoPCoordenadas);
        }
        sumaCoordenadas=sumaCoordenadas + "/";

        return sumaCoordenadas;
    }

    void saveCoordenadas(Pais* pPais, string pCoordenadas)
    {
        pCoordenadas=getCoordenadas(pCoordenadas);
        pCoordenadas=getSumaCoordenadas(pCoordenadas);
        float puntoCoordenada=0;
        int posicionDelimitador=0;
        int verificaXoY=0;
        while(pCoordenadas != "/"){
            posicionDelimitador=strTok(pCoordenadas, (char)',');
            puntoCoordenada=stof(pCoordenadas.substr(0,posicionDelimitador));
            pCoordenadas=pCoordenadas.substr(posicionDelimitador+1, pCoordenadas.length());
            addCoordenadas(pPais, puntoCoordenada, verificaXoY);
            verificaXoY++;
        }   
    }

    void addCoordenadas(Pais* pPais, float pCoordenada, int pPuntoXY){
        Coordenada* nuevaCoordenada=new Coordenada();
        if(pPuntoXY%2 == 0){//si es x
            if(pPais->getPrimeraCoordenadaX() != nullptr){
                pPais->getUltimaCoordenadaX()->setSiguienteCoordenadaX(nuevaCoordenada);
                pPais->setUltimaCoordenadaX(nuevaCoordenada);
                nuevaCoordenada->setSiguienteCoordenadaX(nullptr);
            }
            else {
                pPais->setPrimeraCoordenadaX(nuevaCoordenada);
                pPais->setUltimaCoordenadaX(nuevaCoordenada);
                nuevaCoordenada->setSiguienteCoordenadaX(nullptr);
            }
            nuevaCoordenada->setCoordenadaEjeX(pCoordenada);
        } else {
            if(pPais->getPrimeraCoordenadaY() != nullptr){
                pPais->getUltimaCoordenadaY()->setSiguienteCoordenadaY(nuevaCoordenada);
                pPais->setUltimaCoordenadaY(nuevaCoordenada);
                pPais->getUltimaCoordenadaY()->setSiguienteCoordenadaY(nullptr);

            }
            else{
                pPais->setPrimeraCoordenadaY(nuevaCoordenada);
                pPais->setUltimaCoordenadaY(nuevaCoordenada);
                nuevaCoordenada->setSiguienteCoordenadaY(nullptr);
            }
            nuevaCoordenada->setCoordenadaEjeY(pCoordenada);
        }
    }

void buscarFronteras(){
    for(Pais* actual=aPrimerPais; actual!= nullptr; actual=actual->getSiguientePais()){
        for(Pais* fronteraTemp=aPrimerPais; fronteraTemp!=nullptr; fronteraTemp=fronteraTemp->getSiguientePais()){
            if(actual->getPosicionSVG() != fronteraTemp->getPosicionSVG()){
                comparacionDeCoordenadas(actual, fronteraTemp);
            }
        }
    }
}

void comparacionDeCoordenadas(Pais* pPais, Pais* pFrontera){
    Coordenada* coordPaisY=pPais->getPrimeraCoordenadaY();
    bool esFrontera=false;
    for(Coordenada* coordPaisX=pPais->getPrimeraCoordenadaX(); coordPaisX!=nullptr; coordPaisX=coordPaisX->getSiguienteCoordenadaX()){
        esFrontera=comparacion2(coordPaisX, coordPaisY, pPais, pFrontera);
        if(esFrontera){
            break;
        }
        coordPaisY=coordPaisY->getSiguienteCoordenadaY();
    }
}

bool comparacion2(Coordenada* coordPaisX, Coordenada* coordPaisY, Pais* pPais, Pais* pFrontera){
    Coordenada* coordFronteraY=pFrontera->getPrimeraCoordenadaY();
    for(Coordenada* coordFronteraX=pFrontera->getPrimeraCoordenadaX(); coordFronteraX!= nullptr; coordFronteraX=coordFronteraX->getSiguienteCoordenadaX()){
        if((coordPaisX->getCoordenadaEjeX() - coordFronteraX->getCoordenadaEjeX()) >=-3 && (coordPaisX->getCoordenadaEjeX() - coordFronteraX->getCoordenadaEjeX()) <=20){
            //cout<<"IF1 "<<pPais->getNombre()<< " - "<<pFrontera->getNombre()<<endl;
            if((coordPaisY->getCoordenadaEjeY() - coordFronteraY->getCoordenadaEjeY()) >=-3 && (coordPaisY->getCoordenadaEjeY() - coordFronteraY->getCoordenadaEjeY()) <=20){
                //cout<<"IF1 "<<pPais->getNombre()<< " - "<<pFrontera->getNombre()<<endl;
                //cout<<"SI SON" <<coordPaisY->getCoordenadaEjeY() <<" - "<< coordFronteraY->getCoordenadaEjeY()<<endl;
                agregarFrontera(pPais, pFrontera);
                return true;
            }
            coordFronteraY=coordFronteraY->getSiguienteCoordenadaY();
        }
    }return false;
}




void agregarFrontera(Pais* pPais, Pais* pFrontera){
    Frontera* nuevaFrontera = new Frontera();
    if(pPais->getPrimeraFrontera() != nullptr){
        pPais->getUltimaFrontera()->setSiguienteFrontera(nuevaFrontera);
        pPais->setUltimaFrontera(nuevaFrontera );
        nuevaFrontera->setSiguienteFrontera(nullptr);
    }
    else {
        pPais->setPrimeraFrontera(nuevaFrontera);
        pPais->setUltimaFrontera(nuevaFrontera);
        nuevaFrontera->setSiguienteFrontera(nullptr);
    }
    nuevaFrontera->setColor(pFrontera->getColor());
    nuevaFrontera->setIdPais(pFrontera->getIdPais());
    nuevaFrontera->setNombre(pFrontera->getNombre());
    pPais->setCantidadFronteras();
}

void imprimirFronteras(){
    for(Pais* actual=aPrimerPais; actual!= nullptr; actual=actual->getSiguientePais()){
        for(Frontera* temporal=actual->getPrimeraFrontera(); temporal!=nullptr; temporal=temporal->getSiguienteFrontera()){
            cout<<actual->getNombre()<<" - "<<temporal->getNombre()<<" -> "<<temporal->getColor()<<endl;
        }
    }
}

Pais* buscarPais(string pNombre){
    for(Pais* actual=aPrimerPais; actual!=nullptr; actual= actual->getSiguientePais()){
        if(pNombre == actual->getNombre()){
            return actual;
        }
    }return nullptr;
}



};

#endif