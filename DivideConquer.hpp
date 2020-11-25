#ifndef DIVIDECONQUER_HPP
#define DIVIDECONQUER_HPP
#include "ListaPaises.hpp"
#include "Pais.hpp"
#include "Frontera.hpp"
#include "XMLParser.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

class DivideConquer {
private: 
    

public: 
DivideConquer (){
    
}

    ListaPaises* getListaPaisesActual(ListaPaises* pListaPaises, int pCantidadColores, int pCantidadPaises){
        string nombre, id, color, coordenada, continente;
        ListaPaises* listaActual=new ListaPaises();
        Pais* temporal=nullptr;
        int paisesEnLista=0;
        int posicion=0;
        if(pCantidadPaises<pCantidadColores){//si quedan pocos paises en la lista de paises
            return pListaPaises;
        } 
        else {
            for(Pais* actual=pListaPaises->getPrimerPais(); actual!=nullptr; actual=actual->getSiguientePais()){

                if(actual->getVisitado()==false){
                    id          =actual->getIdPais();
                    color       =actual->getColor();
                    nombre      =actual->getNombre();
                    posicion    =actual->getPosicionSVG();
                    coordenada  =actual->getStringCoordenada();
                    continente  =actual->getContinente();
                    listaActual->agregarPais(nombre, id, color, posicion, coordenada, continente);
                    paisesEnLista++;
                    pCantidadPaises--;
                    for(Frontera* fronteraTemp=actual->getPrimeraFrontera(); fronteraTemp!=nullptr; fronteraTemp=fronteraTemp->getSiguienteFrontera()){
                        if(paisesEnLista>=pCantidadColores){
                            return listaActual;
                        }

                        temporal=pListaPaises->buscarPais(fronteraTemp->getNombre());
                        if(temporal==nullptr){
                            break;
                        }else{
                            id=temporal->getIdPais();
                            color=temporal->getColor();
                            nombre=temporal->getNombre();
                            posicion=temporal->getPosicionSVG();
                            coordenada=temporal->getStringCoordenada();
                            continente  =temporal->getContinente();
                            listaActual->agregarPais(nombre, id, color, posicion, coordenada, continente);
                            paisesEnLista++;
                            pCantidadPaises--;
                        }
                    } 
                    if (paisesEnLista >= pCantidadColores){
                        return listaActual;
                    }
                }
            }
        }
        return listaActual;
    }

    void imprimirListaPequena(ListaPaises* pLista){
        for(Pais* actual=pLista->getPrimerPais(); actual!=nullptr; actual=actual->getSiguientePais()){
            cout<<"lista  ->  " <<actual->getNombre()<<endl;
        }
    }

    ListaPaises* cambiarEstadoVisitado(ListaPaises* pListaPaises, ListaPaises* pListaActual){
        for(Pais* actual=pListaActual->getPrimerPais(); actual!=nullptr; actual=actual->getSiguientePais()){
            actual->setVisitado();
        }
        return pListaPaises;
    }

//elije un color para pintar las fronteras dependiendo del numero de entrada;
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
    
    void pintarPaises(ListaPaises* pLista, int pCantidadColores, XMLParser *pXML){
        int color=1;
        for(Pais* actual=pLista->getPrimerPais(); actual!=nullptr; actual=actual->getSiguientePais()){
            if(pCantidadColores==color){
                actual->setColor(elegirColor(1));
                actual->setNumeroColor(1);
                color=2;
            }
            else {
                actual->setColor(elegirColor(color));
                actual->setNumeroColor(color);
                color++;
            }   
        }
        pXML->modificarSVG(pLista, "world-DivideConquer.svg");
        pXML->guardarArchivo("world-DivideConquer.svg");
    }

    void pintarDeBlanco(ListaPaises* pLista, int pCantidadColores, XMLParser *pXML){
        for(Pais* pais=pLista->getPrimerPais(); pais!=nullptr; pais=pais->getSiguientePais()){
            while(cambiarColor(pLista, pais, pCantidadColores)){
                if(pais->getCantidadPintadas()>=pCantidadColores-1){
                    pais->setColor(elegirColor(0));
                    pais->setNumeroColor(0);
                    pLista->setPaisesEnBlanco();
                    break;
                }
            }
        }
        pXML->modificarSVG(pLista, "world-DivideConquer.svg");
        pXML->guardarArchivo("world-DivideConquer.svg");
    }

    bool cambiarColor(ListaPaises* pLista, Pais* pPais, int pCantidadColores){
        string colorPais=pPais->getColor();
        int color=0;
        for(Frontera* frontera=pPais->getPrimeraFrontera(); frontera!=nullptr; frontera=frontera->getSiguienteFrontera()){
            if(pLista->buscarPais(frontera->getNombre())->getColor() == colorPais){ //si tiene un color igual al de una de sus fronteras
                color=rand()%pCantidadColores+1;
                if(color!=pPais->getNumeroColor()){
                    pPais->setColor(elegirColor(color));
                    pPais->setNumeroColor(color);
                    pPais->setCantidadPintadas();
                    return true;
                }else{
                    //color=rand()%pCantidadColores+1;
                    pPais->setColor(elegirColor(color));
                    pPais->setNumeroColor(color);
                    pPais->setCantidadPintadas();
                    return true;
                }
            }
        }
        return false;
    }


    int Divide(ListaPaises* pListaPaises, int pCantidadColores, int pCantidadPaises, ListaPaises* pRetorno, XMLParser *pXML){
	    ListaPaises* listaPaisesActuales=new ListaPaises();
        listaPaisesActuales=getListaPaisesActual(pListaPaises, pCantidadColores, pCantidadPaises);
        pListaPaises = cambiarEstadoVisitado(pListaPaises, listaPaisesActuales);
        pintarPaises(listaPaisesActuales, pCantidadColores, pXML);
        pCantidadPaises-=pCantidadColores;
        //cout<<pCantidadPaises<<endl;
        if(pCantidadPaises<=0){

            pintarDeBlanco(pListaPaises, pCantidadColores, pXML);
            //pintarColindantesDeBlanco(pListaPaises);
            cout<< "Paises en blanco divide-conquer "<<pListaPaises->getPaisesEnBlanco()<<endl;
            pXML->editarTexto("cantidadPintados", 211-pListaPaises->getPaisesEnBlanco());
            pXML->editarTexto("cantidadBlancos", pListaPaises->getPaisesEnBlanco());
            pXML->guardarArchivo("world-DivideConquer.svg");
            return 0;
        } else {
            return Divide(pListaPaises, pCantidadColores, pCantidadPaises, pRetorno, pXML);
        }
    }

   /* void pintarColindantesDeBlanco(ListaPaises* pLista){
    int prueba=0;
    for(Pais* indPais=pLista->getPrimerPais(); indPais!=nullptr; indPais=indPais->getSiguientePais()){
        for(Frontera* indFrontera=indPais->getPrimeraFrontera(); indFrontera!=nullptr; indFrontera=indFrontera->getSiguienteFrontera()){
            if(indPais->getColor()==pLista->buscarPais(indFrontera->getNombre())->getColor()  && pLista->buscarPais(indFrontera->getNombre())->getNumeroColor()!=0){
                //cout<<indPais->getColor()<<" "<<indFrontera->getColor()<<endl;
                //cout<<pLista->buscarPais(indFrontera->getNombre())->getNumeroColor()<<" "<<indFrontera->getColor()<<" "<<prueba<<endl;
                indPais->setColor(elegirColor(0));
                indPais->setNumeroColor(0);
                //indPais->setNumeroColor(0);
                pLista->setPaisesEnBlanco();
                prueba++;
            }
        }
    }
}*/

};
#endif
