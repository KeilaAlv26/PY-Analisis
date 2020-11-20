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
int gCantidadColores=7;
int gCantidadPaises=211;


	ListaPaises* extraerDatosArchivo(const char *pFilename, ListaPaises* pListaPaises)
	{
		string nombrePais, id, color, coordenada, continente;
		ListaPaises* listaContinente=new ListaPaises();
		Pais* paisConMasFronteras=nullptr;
		XMLDocument doc;
		doc.LoadFile(pFilename);
		XMLElement *paths = doc.RootElement()->FirstChildElement()->NextSiblingElement()->NextSiblingElement(); //Primer path

		for(int indice=0; indice<gCantidadPaises; indice++){
			paths = paths->NextSiblingElement();
			id = (string) paths->Attribute("data-id");	
			color = (string) paths->Attribute("style");
			coordenada = (string) paths->Attribute("d");
			nombrePais = (string) paths->Attribute("data-name");
			pListaPaises->agregarPais(nombrePais, id, color, indice+1, coordenada);
			
		}
		return pListaPaises;
	}

    void modificarSVG(ListaPaises *paises, const char* pFileName){
        XMLDocument doc;
        doc.LoadFile(pFileName);
        XMLElement *paths = doc.RootElement()->FirstChildElement()->NextSiblingElement()->NextSiblingElement()->NextSiblingElement();
        string nombre;
        Pais* buscado = nullptr;
        int gCantidadPaises = 211;
        for(int indice=0; indice<gCantidadPaises; indice++){
            nombre = (string) paths->Attribute("data-name");
            buscado = paises->buscarPais(nombre);
			paths->SetAttribute("style", buscado->getColor().c_str());
            paths = paths->NextSiblingElement();
        }
        doc.SaveFile(pFileName);
    }

	void algoritmoDinamico(const char *pFilename, ListaPaises* pListaPaises)
	{
		pListaPaises=extraerDatosArchivo(pFilename, pListaPaises);
		pListaPaises->buscarFronteras();
		gDinamico->Dinamic(pListaPaises, gCantidadColores);
		//pListaPaises->imprimirPaises();
		modificarSVG(pListaPaises, pFilename);
	}

	void algoritmoDivideConquer(const char *pFilename, ListaPaises* pListaPaises)
	{
		pListaPaises=extraerDatosArchivo(pFilename, pListaPaises);
		pListaPaises->buscarFronteras();
		ListaPaises* list=new ListaPaises();
		gDivideConquer->Divide(pListaPaises, gCantidadColores, gCantidadPaises, list);
		modificarSVG(pListaPaises, pFilename);
	}


int main()
{
	algoritmoDivideConquer("world-DivideConquer.svg", gListaPaises);
	algoritmoDinamico("world-Dinamico.svg", gListaPaises2);
    return 0;
}