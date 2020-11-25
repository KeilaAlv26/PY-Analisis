#ifndef DINAMICO_HPP
#define DINAMICO_HPP
#include "ListaPaises.hpp"
#include "Pais.hpp"
#include "Frontera.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class Dinamico {
private: 
    
    
public: 
Dinamico (){
    
}



    int Dinamic(ListaPaises* pLista, int pCantidadColores, XMLParser *pXML, int pCantidadPaises){
        Pais* paisActual=nullptr;
        paisActual=seleccionarPais(pLista, pCantidadColores);
        pCantidadPaises--;
        if(pCantidadPaises==0){
            cout<<"Paises en blanco dinamico "<<pLista->getPaisesEnBlanco()<<endl;
            pXML->editarTexto("cantidadPintados", 211-pLista->getPaisesEnBlanco());
            pXML->editarTexto("cantidadBlancos", pLista->getPaisesEnBlanco());
            pXML->modificarSVG(pLista, "world-Dinamico.svg");
            pXML->guardarArchivo("world-Dinamico.svg");
            return 0;
        }else{
            return Dinamic(pLista, pCantidadColores, pXML, pCantidadPaises);
        }
    }


    Pais* seleccionarPais(ListaPaises* pLista, int pCantidadColores){
        int colorPais=0;
        for(Pais* actual=pLista->getPrimerPais(); actual!=nullptr; actual=actual->getSiguientePais()){
            if(actual->getVisitado()==false){
                if(actual->getCantidadFronteras()==0 || verificarFronterasSinPintar(pLista, actual)){
                    colorPais = rand()%pCantidadColores+1;
                    actual->setColor(elegirColor(colorPais));
                    actual->setNumeroColor(colorPais);
                    actual->setVisitado();
                    actual->setPintado();
                    return actual;
                }
                colorPais=verificarColorFronteras(pLista, actual, pCantidadColores);
                if(colorPais==0){
                    actual->setColor("fill:#f2f2f2;fill-rule:evenodd");
                    pLista->setPaisesEnBlanco();
                    actual->setVisitado();
                    actual->setPintado();
                    actual->setNumeroColor(0);
                    return actual;
                }else{
                    actual->setColor(elegirColor(colorPais));
                    actual->setNumeroColor(colorPais);
                    actual->setVisitado();
                    actual->setPintado();
                    return actual;
                }
            }
        }return nullptr;
    }

    bool verificarFronterasSinPintar(ListaPaises* pLista, Pais* pPais){
        for(Frontera* actual=pPais->getPrimeraFrontera(); actual!=nullptr; actual=actual->getSiguienteFrontera()){
            if(pLista->buscarPais(actual->getNombre())->getPintado()){
                return false;
            }
        }return true;
    }

    int seleccionarColorDePais(vector<int> pColoresFronteras, int pCantidadColores){
        bool colorUsado=false;
        for(int numColor=1; numColor<=pCantidadColores; numColor++){
            colorUsado=false;
            for(int indice=0; indice<pColoresFronteras.size(); indice++){
                if(pColoresFronteras[indice]==numColor){
                    colorUsado=true;
                }
            } if(colorUsado==false){
                return numColor;
            }
        }return 0;
    }

    int verificarColorFronteras(ListaPaises* pLista, Pais* pPais, int pCantidadColores){
        vector<int> coloresElegidos;
        int colorFront=0;
        int colorPais=0;
        for(Frontera* actual=pPais->getPrimeraFrontera(); actual!=nullptr; actual=actual->getSiguienteFrontera()){
            if(pLista->buscarPais(actual->getNombre())->getPintado()){//verifica si el pais frontera ya fue pintado
                colorFront=pLista->buscarPais(actual->getNombre())->getNumeroColor();
                coloresElegidos.push_back(colorFront);
            }
        }
        colorPais=seleccionarColorDePais(coloresElegidos, pCantidadColores);
        return colorPais;
    }
 
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
        if(pColor ==11) return cafe;
        else return "-1";
    }


};

#endif
