#ifndef LISTASVG_HPP
#define LISTASVG_HPP

class ListaSVG {
private: 
		String aNombre;

public: 
	ListaSVG (){
		aNombre="";
	}

    String getNombreSVG(){
        return aNombre;
    }

    void setNombreSVG(string pNombre){
        aNombre=pNombre;
    }

};

#endif
