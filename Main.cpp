#include <iostream>
#include <vector>
#include "ListaPaises.hpp"
#include "DivideConquer.hpp"
#include "Backtracking.hpp"
#include "Dinamico.hpp"
#include "XMLParser.hpp"

using namespace tinyxml2;
using namespace std;

ListaPaises* gListaPaises = new ListaPaises();
ListaPaises* gListaPaises2 = new ListaPaises();
ListaPaises* gListaPaises3 = new ListaPaises();
DivideConquer* gDivideConquer = new DivideConquer();
Backtracking* gBacktracking = new Backtracking();
Dinamico* gDinamico = new Dinamico();
XMLParser *pParser = new XMLParser();
int gCantidadColores=7;
int gCantidadPaises=211;


	ListaPaises* extraerDatosArchivo(XMLParser *pXML, ListaPaises* pListaPaises)
	{
		string nombrePais, id, color, coordenada, continente;
		ListaPaises* listaContinente=new ListaPaises();
		//Pais* paisConMasFronteras=nullptr;
		pXML->modificarPath();
		for(int indice=0; indice<gCantidadPaises; indice++){
			pXML->cambiarPath();
			id = pXML->getID();	
			color = pXML->getEstilo();
			coordenada = pXML->getCoordenada();
			nombrePais = pXML->getDataName();
			continente = pXML->getContinente();
			pListaPaises->agregarPais(nombrePais, id, color, indice+1, coordenada, continente);
			
		}
		return pListaPaises;
	}

    /*void modificarSVG(ListaPaises *paises, const char* pFileName){
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
    }*/

	void algoritmoDinamico(const char *pFilename, ListaPaises* pListaPaises)
	{
		pParser->cargarArchivo("world-Dinamico.svg");
		pParser->setPaisesBlanco();
		pParser->guardarArchivo("world-Dinamico.svg");
		pListaPaises=extraerDatosArchivo(pParser, pListaPaises);
		pListaPaises->buscarFronteras();
		gDinamico->Dinamic(pListaPaises, gCantidadColores, pParser, 211);
		//pListaPaises->imprimirPaises();
		//pXML->modificarSVG(pListaPaises, pFilename);
	}

	void algoritmoDivideConquer(const char *pFilename, ListaPaises* pListaPaises)
	{
		pParser->cargarArchivo("world-DivideConquer.svg");
		pParser->setPaisesBlanco();
		pListaPaises=extraerDatosArchivo(pParser, pListaPaises);
		pListaPaises->buscarFronteras();
		//pListaPaises->imprimirFronteras();
		ListaPaises* list=new ListaPaises();
		gDivideConquer->Divide(pListaPaises, gCantidadColores+1, gCantidadPaises, list, pParser);
		//modificarSVG(pListaPaises, pFilename);
	}

	void algoritmoBacktracking(const char *pFilename, ListaPaises* pListaPaises)
	{
		pParser->cargarArchivo("world-Backtracking.svg");
		pParser->setPaisesBlanco();
		pListaPaises=extraerDatosArchivo(pParser, pListaPaises);
		pListaPaises->buscarFronteras();
		//ListaPaises* list=new ListaPaises();
		gBacktracking->algoritmoBacktracking(pListaPaises, gCantidadColores, pParser);
		//modificarSVG(pListaPaises, pFilename);
	}


int main()
{
	algoritmoDivideConquer("world-DivideConquer.svg", gListaPaises);
	algoritmoBacktracking("world-Backtracking.svg", gListaPaises3);
	algoritmoDinamico("world-Dinamico.svg", gListaPaises2);

    return 0;
}