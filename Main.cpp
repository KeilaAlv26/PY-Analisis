#include "tinyxml2.cpp"
#include "tinyxml2.h"
#include <iostream>
#include <vector>
#include "ListaPaises.hpp"
#include "DivideConquer.hpp"
#include "Dinamico.hpp"

using namespace tinyxml2;
using namespace std;

ListaPaises* gListaPaises = new ListaPaises();
ListaPaises* gListaPaises2 = new ListaPaises();
DivideConquer* gDivideConquer = new DivideConquer();
Dinamico* gDinamico = new Dinamico();



    void modificarSVG(ListaPaises *paises, const char* pFileName){
        XMLDocument doc;
        doc.LoadFile(pFileName);
        XMLElement *paths = doc.RootElement()->FirstChildElement()->NextSiblingElement()->NextSiblingElement()->NextSiblingElement();
        string nombre;
        Pais* buscado = nullptr;
        int cantidadPaises = 211;
        for(int indice=0; indice<cantidadPaises; indice++){
            nombre = (string) paths->Attribute("data-name");
            buscado = paises->buscarPais(nombre);
			paths->SetAttribute("style", buscado->getColor().c_str());
            paths = paths->NextSiblingElement();
        }
        doc.SaveFile(pFileName);
    }

	void algoritmoDinamico(const char *pFilename)
	{
		string lista;
		int cantidadPaises=211;
		int cantidadColores=11;
		string nombrePais;
		string id;
		string color;
		string coordenada;
		string continente;
		ListaPaises* listaContinente=new ListaPaises();
		Pais* paisConMasFronteras=nullptr;
		XMLDocument doc;
		doc.LoadFile(pFilename);
		XMLElement *paths = doc.RootElement()->FirstChildElement()->NextSiblingElement()->NextSiblingElement(); //Primer path

		for(int indice=0; indice<cantidadPaises; indice++){
			paths = paths->NextSiblingElement();
			nombrePais = (string) paths->Attribute("data-name");
			id = (string) paths->Attribute("data-id");	
			color = (string) paths->Attribute("style");
			coordenada = (string) paths->Attribute("d");
			gListaPaises2->agregarPais(nombrePais, id, color, indice+1, coordenada);
			
		}
		gListaPaises2->buscarFronteras();
		//gListaPaises2->imprimirFronteras();
		gDinamico->Dinamic(gListaPaises2, cantidadColores);
		gListaPaises2->imprimirPaises();
		modificarSVG(gListaPaises2, pFilename);
	}

	void algoritmoDivideConquer(const char *pFilename)
	{
		string lista;
		int cantidadPaises=211;
		int cantidadColores=7;
		string nombrePais;
		string id;
		string color;
		string coordenada;
		string continente;
		ListaPaises* listaContinente=new ListaPaises();
		Pais* paisConMasFronteras=nullptr;
		XMLDocument doc;
		doc.LoadFile(pFilename);
		XMLElement *paths = doc.RootElement()->FirstChildElement()->NextSiblingElement()->NextSiblingElement(); //Primer path

		for(int indice=0; indice<cantidadPaises; indice++){
			paths = paths->NextSiblingElement();
			nombrePais = (string) paths->Attribute("data-name");
			id = (string) paths->Attribute("data-id");	
			color = (string) paths->Attribute("style");
			coordenada = (string) paths->Attribute("d");
			gListaPaises->agregarPais(nombrePais, id, color, indice+1, coordenada);
			
		}
		gListaPaises->buscarFronteras();
		ListaPaises* list=new ListaPaises();
		gDivideConquer->Divide(gListaPaises, cantidadColores, cantidadPaises, list);
		modificarSVG(gListaPaises, pFilename);
	}


int main()
{
	algoritmoDivideConquer("world-DivideConquer.svg");
	algoritmoDinamico("world-Dinamico.svg");
    return 0;
}