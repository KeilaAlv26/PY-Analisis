#ifndef BACKTRACKING_HPP
#define BACKTRACKING_HPP
#include "ListaPaises.hpp"
#include "Pais.hpp"
#include "Frontera.hpp"
#include "XMLParser.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

class Backtracking {
private: 
    

public: 
Backtracking (){
    
}

int algoritmoBacktracking(ListaPaises* pLista, int pCantidadColores, XMLParser *pXML)
{
    Pais* paisActual=nullptr;
    int colorPintado=0;
    paisActual=elegirPais(pLista);
    
    if(paisActual==nullptr){
        cout<<"Paises en blanco "<< pLista->getPaisesEnBlanco()<<endl;
        pintarColindantesDeBlanco(pLista, pXML);
        pXML->editarTexto("cantidadPintados", 211-pLista->getPaisesEnBlanco());
        pXML->editarTexto("cantidadBlancos", pLista->getPaisesEnBlanco());
        pXML->guardarArchivo("world-Backtracking.svg");
        return 0;
    }
    colorPintado=buscarColor(pLista, paisActual, pCantidadColores);

    paisActual->setColor(elegirColor(colorPintado));
    paisActual->setNumeroColor(colorPintado);
    paisActual->setPintado();
    pXML->modificarSVG(paisActual, "world-Backtracking.svg");
    pXML->guardarArchivo("world-Backtracking.svg");
    return algoritmoBacktracking(pLista, pCantidadColores, pXML);
    
}

Pais* elegirPais(ListaPaises* pLista){
    for(Pais* actual=pLista->getPrimerPais(); actual!=nullptr; actual=actual->getSiguientePais()){
        if(actual->getVisitado()==false){
            actual->setVisitado();
            return actual;
        }
    }
    return nullptr;
}

bool verificarSiHayColindantesPintadas(ListaPaises* pLista, Pais* pPais){
    for(Frontera* actual=pPais->getPrimeraFrontera(); actual!=nullptr; actual=actual->getSiguienteFrontera()){
        if(pLista->buscarPais(actual->getNombre())->getPintado()==true){ //si la frontera ya fue pintada
            return true;
        }
    }return false;
}

int buscarColor(ListaPaises* pLista, Pais* pPais, int pCantidadColores){
    for(int color=1; color<=pCantidadColores; color++){
        pPais->setColor(elegirColor(color));
        pPais->setNumeroColor(color);
        if(verificarSiHayColindantesPintadas(pLista, pPais)==true){
            if(verificarColorDeColindantes(pLista, pPais, pPais->getNumeroColor())==false){//si el color ya lo tiene una de sus fronteras
                return color;
                break;
            }
        }else{
            return rand()%pCantidadColores+1;
        }
            
    }pLista->setPaisesEnBlanco();
    return 0; //si no hay color solucion entonces se retorna 0 que es igual al color blanco
}

bool verificarColorDeColindantes(ListaPaises* pLista, Pais* pPais, int pNumColor){
    for(Frontera* actual=pPais->getPrimeraFrontera(); actual!=nullptr; actual=actual->getSiguienteFrontera()){
        if(pLista->buscarPais(actual->getNombre())->getVisitado()){
            if(pNumColor==pLista->buscarPais(actual->getNombre())->getNumeroColor()){
                return true;
            }
        }
    }return false;
}

string elegirColor(int pColor){
    string blanco="fill:#f2f2f2;fill-rule:evenodd";
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
    string cafe="fill:#97480B;fill-rule:evenodd";
    if(pColor ==0) return blanco;
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

void pintarColindantesDeBlanco(ListaPaises* pLista, XMLParser *pXML){
    for(Pais* indPais=pLista->getPrimerPais(); indPais!=nullptr; indPais=indPais->getSiguientePais()){
        for(Frontera* indFrontera=indPais->getPrimeraFrontera(); indFrontera!=nullptr; indFrontera=indFrontera->getSiguienteFrontera()){
            if(indPais->getColor()==indFrontera->getColor()){
                indFrontera->setColor(elegirColor(0));
            }
        }
    }
    pXML->modificarSVG(pLista, "world-Backtracking.svg");
}

};
#endif
