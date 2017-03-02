#ifndef PARSERXML_H
#define PARSERXML_H

#include <iostream>
#include <vector>

struct conf{

    // Dados do vao
    std::string nome {NULL};        // nome do caso
		int grafico {0};                // formato da saida
    double ncfeixe {0.0};       		// numero de condutores no feixe
    double dfeixe {0.0};        		// diametro do feixe
    double cvao {0.0};      				// comprimento do vao
    double h0 {0.0};								// altura de partida
    double eds {0.0};								// eds
    double nl {0.0};								// numero de divisoes na catenaria
    double tensao {0.0};						// nivel de tensao [V]
		std::vector<double> gfeixe {0.0, 0.0, 0.0};
    
    // Caracteristicas do cabo
    std::string modelo {NULL};
    double secao {0.0};
    double phi {0.0};
    double massa {0.0};
    double trup {0.0};
    double alphafinal {0.0};
    double elastfinal {0.0};
    double pminimo {0.0};
    double pmaximo {0.0};
    double tcop {0.0};
    double tamb {0.0};
    double tmax {0.0};
    double tmin {0.0};
    double ventomed {0.0};
		
		// Ler e salvar
    void load(const std::string&);
    void save(const std::string&);
};


struct relat{

    // Dados do vao
    std::string titulo {NULL};    		// nome do caso
    double eds {0.0};            		// nunero de condutores no feixe
    double nl {0.0};            		// diametro do feixe
    double cvao {0.0};				// comprimento do vao
    double ccabo {0.0};								// altura de partida
    double hmax {0.0};								// eds
    double hmin {0.0};								// numero de divisoes na catenaria
    double qcil {0.0};						// nivel de tensao [V]
		double hseg {0.0};
		double flecha {0.0};
		double balanco {0.0};
		double flechav {0.0};
		double flat {0.0};
		std::vector<double> gfeixe {0.0, 0.0, 0.0};
		
		//Salvar relatorio
    void save(const std::string&);
};




#endif