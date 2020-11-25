#ifndef XMLPARSER_HPP
#define XMLPARSER_HPP

#include "tinyxml2.cpp"
#include "tinyxml2.h"
#include "Pais.hpp"
#include "ListaPaises.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace tinyxml2;

class XMLParser
{
private:
	string Atributo;
	string Coordenadas;
	string Estilo;
	string ID;
	string Nombre;
	string Continente;
	XMLDocument doc;
	XMLElement *pPath;

public:
    XMLParser(){
	}

	XMLElement *buscarPath(string pNombre){
		modificarPath();
		int i = 0;
		int gCantidadPaises = 211;
		string actual;
		while(i < gCantidadPaises){
			cambiarPath();
			actual = (string)pPath->Attribute("data-name");
			if(actual == pNombre){
				return pPath;
			}
			i++;
		}return nullptr;
	}

	void modificarSVG(Pais *pais, const char *pFilename){
        string nombre;
		const char *color;
        XMLElement* buscado = nullptr;
		nombre = pais->getNombre();
		color = pais->getColor().c_str();
		buscado = buscarPath(nombre);
		editarAtributo("style", color);
    }

	void modificarSVG(ListaPaises *paises, const char *pFilename){
        string nombre;
		const char *color;
        XMLElement* buscado = nullptr;
        for(Pais *actual = paises->getPrimerPais(); actual!=nullptr; actual = actual->getSiguientePais()){
            nombre = actual->getNombre();
            buscado = buscarPath(nombre);
			color = actual->getColor().c_str();
			editarAtributo("style", color);
            //cambiarPath();
        }
    }

	void guardarArchivo(const char *pFilename){
		doc.SaveFile(pFilename);
	}	

	void cargarArchivo(const char* pFilename){
		doc.LoadFile(pFilename);
	}

	void editarAtributo(const char *pNombreAtributo, const char *pValor){
		pPath->SetAttribute(pNombreAtributo, pValor);
	}

	string getContinente(){
		Continente = (string)pPath->Attribute("continent");
		return Continente;
	}

	string getCoordenada(){
		Coordenadas = (string)pPath->Attribute("d");
		return Coordenadas;
	}

	string getID(){
		ID = (string)pPath->Attribute("data-id");
		return ID;
	}

	string getEstilo(){
		Estilo = (string)pPath->Attribute("style");
		return Estilo;
	}

	string getDataName(){
		Nombre = (string)pPath->Attribute("data-name");
		return Nombre;
	}

	void cambiarPath(){
		pPath = pPath->NextSiblingElement();
	}

	void modificarTexto(){
		pPath = doc.RootElement()->FirstChildElement()->NextSiblingElement()->NextSiblingElement();
	}

	void modificarPath(){
		pPath = doc.RootElement()->FirstChildElement()->NextSiblingElement()->NextSiblingElement()->NextSiblingElement()->NextSiblingElement()->NextSiblingElement()->NextSiblingElement();
	}

	void editarTexto(string atributo, int valor){
		buscarID(atributo);
		pPath->SetText(valor);
	}

	XMLElement *buscarID(string pNombre){
		modificarTexto();
		int i = 0;
		int gCantidadPaises = 211;
		string actual;
		while(i < gCantidadPaises){
			cambiarPath();
			actual = (string)pPath->Attribute("id");
			if(actual == pNombre){
				return pPath;
			}
			i++;
		}return nullptr;
	}

	void setPaisesBlanco(){
		modificarPath();
		for(int indice=0; indice<211; indice++){
			cambiarPath();
			editarAtributo("style", "fill:#f2f2f2;fill-rule:evenodd");
		}
	}

};

#endif