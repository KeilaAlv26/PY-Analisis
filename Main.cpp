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
int gCantidadColores=11;
int gCantidadPaises=211;


	ListaPaises* extraerDatosArchivo(XMLParser *pXML, ListaPaises* pListaPaises)
	{
		string nombrePais, id, color, coordenada, continente;
		ListaPaises* listaContinente=new ListaPaises();
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

	void algoritmoDinamico(const char *pFilename, ListaPaises* pListaPaises)
	{
		pParser->cargarArchivo("world-Dinamico.svg");
		pParser->setPaisesBlanco();
		pParser->guardarArchivo("world-Dinamico.svg");
		pListaPaises=extraerDatosArchivo(pParser, pListaPaises);
		pListaPaises->buscarFronteras();
		gDinamico->Dinamic(pListaPaises, gCantidadColores, pParser, 211);
	}

	void algoritmoDivideConquer(const char *pFilename, ListaPaises* pListaPaises)
	{
		pParser->cargarArchivo("world-DivideConquer.svg");
		pParser->setPaisesBlanco();
		pListaPaises=extraerDatosArchivo(pParser, pListaPaises);
		pListaPaises->buscarFronteras();
		ListaPaises* list=new ListaPaises();
		gDivideConquer->Divide(pListaPaises, gCantidadColores+1, gCantidadPaises, list, pParser);
	}

	void algoritmoBacktracking(const char *pFilename, ListaPaises* pListaPaises)
	{
		pParser->cargarArchivo("world-Backtracking.svg");
		pParser->setPaisesBlanco();
		pListaPaises=extraerDatosArchivo(pParser, pListaPaises);
		pListaPaises->buscarFronteras();
		gBacktracking->algoritmoBacktracking(pListaPaises, gCantidadColores, pParser);
	}


int main()
{
	algoritmoDivideConquer("world-DivideConquer.svg", gListaPaises);
	algoritmoBacktracking("world-Backtracking.svg", gListaPaises3);
	algoritmoDinamico("world-Dinamico.svg", gListaPaises2);

    return 0;
}