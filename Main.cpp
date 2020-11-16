#include "tinyxml2.cpp"
#include "tinyxml2.h"
#include <iostream>
/*#include <cstring>
#include <string>
#include <stdio.h>
#include <sstream>*/
#include "ListaPaises.hpp"
#include "DivideConquer.hpp"

using namespace tinyxml2;
using namespace std;

ListaPaises* gListaPaises = new ListaPaises();
DivideConquer* gDivideConquer = new DivideConquer();


//Variables Globales
/*string gSumaCoordenadas = "";

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

string leerSVG(const char *pFilename, string pPaisBuscado)
{
	int cantidadPaises=211;
	bool entro = false;
	string paisActual;
	string coordenadas;
	XMLDocument doc;
	doc.LoadFile(pFilename);
	XMLElement *paths = doc.RootElement()->FirstChildElement()->NextSiblingElement()->NextSiblingElement()->NextSiblingElement(); //Primer path
	for(int indice=0; indice<cantidadPaises-1; indice++){
		paths = paths->NextSiblingElement();
		paisActual = (string) paths->Attribute("data-name");
		if(pPaisBuscado == paisActual){
			entro=true;
			coordenadas = (string) paths->Attribute("d");
			return coordenadas;
		}	
	}
	if(!entro){
		std::cout <<"El pais buscado no fue encontrado";
		return 0;
	}else return 0;
	//doc.SaveFile(pFilename);
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
		if(ascii != 109 && ascii != 122){
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
	while(pCoordenadas != "/"){
		posicionDelimitador = strTok (pCoordenadas, (char)',');
		if(contador%2 == 0){ //si es una coordenada X
			suma = stof(pCoordenadas.substr(0, posicionDelimitador)) + sumaAnteriorX;
			sumaAnteriorX=suma;
			gSumaCoordenadas= gSumaCoordenadas + floatToString(suma) + ',';
		}else{
			suma = stof(pCoordenadas.substr(0, posicionDelimitador)) + sumaAnteriorY;
			sumaAnteriorY=suma;
			gSumaCoordenadas= gSumaCoordenadas + floatToString(suma) + ',';
		}
		contador++;
		pCoordenadas = pCoordenadas.substr(posicionDelimitador+1, largoPCoordenadas);
	}
	return gSumaCoordenadas;
}*/

/*bool compararCoordenadas(string pCoordenadasPais, string pCoordenadasfrontera){
	int delimitadorPais=0;
	int delimitadorFrontera=0;
	float puntoPais=0;
	float puntoFrontera=0;
	for(){
		delimitadorPais=strTok(pCoordenadasPais, (char)',');
		delimitadorFrontera=strTok(pCoordenadasFrontera, (char)',');
		puntoPais=stof(pCoordenadasPais.substr(0, posicionDelimitador)) + sumaAnteriorX;
		
		for(){
			
		}
	}
}*/

    void modificarSVG(ListaPaises *paises){
        XMLDocument doc;
        doc.LoadFile("world.svg");
        XMLElement *paths = doc.RootElement()->FirstChildElement()->NextSiblingElement()->NextSiblingElement()->NextSiblingElement();
        string nombre;
		//const char* atributo;
        Pais* buscado = nullptr;
        int cantidadPaises = 211;
        for(int indice=0; indice<cantidadPaises; indice++){
            nombre = (string) paths->Attribute("data-name");
            buscado = paises->buscarPais(nombre);
			//char *cptr = new char[buscado->getColor().size()+1];
			paths->SetAttribute("style", buscado->getColor().c_str());
			//cout<<buscado->getNombre()<<" "<<buscado->getColor().c_str()<<endl;
            paths = paths->NextSiblingElement();
        }
        doc.SaveFile("world.svg");
    }

void addCountry(const char *pFilename){
	string lista;
	int cantidadPaises=211;
	int cantidadColores =8;
	string nombrePais;
	string id;
	string color;
    string coordenada;
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
	gDivideConquer->Divide(gListaPaises, cantidadColores, 0, 0);
	gDivideConquer->pintarPaisesBlanco(gListaPaises, cantidadColores);
	//Divide(ListaPaises* pLista, int pCantidadColores, int pContadorPaises, int pColorActual)
	//gListaPaises->imprimirFronteras();
	//gListaPaises->imprimirPaises();
	modificarSVG(gListaPaises);
	/*paisConMasFronteras= gDivideConquer->buscarPaisConMasFronteras(gListaPaises);
	cout<<"\n\n"<<paisConMasFronteras->getNombre()<<endl;
	cout<<paisConMasFronteras->getCantidadFronteras()<<endl;
	cout<<paisConMasFronteras->getVisitado()<<endl;*/

}


int main()
{

	addCountry("world.svg");
	/*string coordenadas;
	float prueba;
	string retorno;
	int posicion;
	string sumaCoordenadas;
	coordenadas = leerSVG("world.svg", "Nicaragua");
	posicion=strTok(coordenadas, (char)',');
	retorno = getCoordenadas(coordenadas);
	cout<<retorno<<endl;
	sumaCoordenadas = getSumaCoordenadas(retorno);
	cout<<"\n\n"<<sumaCoordenadas<<endl;*/
	/*posicion = strTok (retorno, (char)',');
	prueba = stof(retorno.substr(0, posicion));
	cout<<"\n\n"<<prueba;*/


    return 0;
}