#ifndef FRONTERA_HPP
#define FRONTERA_HPP
using namespace std;

class Frontera {
private: 
    Frontera* aSiguienteFrontera;
    string    aNombre;
    string    aIdPais;
    string    aColor;

public: 
Frontera (){
    aSiguienteFrontera  =nullptr;
    aNombre             ="";
    aIdPais             ="";
    aColor              ="";
}


    Frontera* getSiguienteFrontera(){
        return aSiguienteFrontera;
    }

    void setSiguienteFrontera(Frontera* pSiguienteFrontera){
        aSiguienteFrontera=pSiguienteFrontera;
    }

     string getNombre(){
        return aNombre;
    }

    void setNombre(string pNombre){
        aNombre=pNombre;
    }

    string getColor(){
        return aColor;
    }

    void setColor(string pColor){
        aColor=pColor;
    }

    string getIdPais(){
        return aIdPais;
    }

    void setIdPais(string pId){
        aIdPais=pId;
    }

};

#endif