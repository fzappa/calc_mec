#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>


#include "FuncoesMec.h"
#include "GeraGrafico.h"
#include "ParserXML.h"

using namespace std;
using namespace Eigen;


int main()
{
	try{
			
			//Leitura dos dados
			conf lt;
			relat r;
			lt.load("dados.xml");

			cout << "\n#### CABO " << lt.modelo << " - " << lt.nome << " ####\n\n";
			
			// Definindo algumas constantes
			const double T0 {lt.trup*(lt.eds/100.0)};
			const double p {lt.massa};
			const double C1 {T0/p};
			
			printf("EDS = %.2f %%\n", lt.eds);
			printf("Divisões na catenária = %.2f m\n", lt.nl);
			
			// Chama a funcao catenaria e retorna o comprimento do cabo 
			// e a matriz posicao x altura
			Eigen::MatrixXd* ptrMxy {nullptr};  // Inicializa o ponteiro
			ptrMxy = catenaria_cabo(C1, lt.h0, lt.cvao, lt.nl, r.ccabo);
			
			// ######################### CATENARIA #########################
			// #Dados da catenaria
			printf("Comprimento do vão: %.2f m\n",lt.cvao);
			printf("Comprimento do cabo: %.2f m\n",r.ccabo);
			printf("H(max) = %.2f m\n", lt.h0);
			
			// ptrMxy.col(0) = distancias
			// ptrMxy.col(1) = flexas
			r.hmin = ptrMxy->col(1).minCoeff();
			printf("H(min) = %.2f m\n", r.hmin);
			
			// Retornar a quantidade de linhas/pedacos de cilindros
			r.qcil = ptrMxy->rows();
			printf("Quantidade de cilindros (TRICAMP) = %.2f \n\n", r.qcil);
			
			// Inicializa os ponteiros
			vector<double>* ptrPx = new vector<double>();
			vector<double>* ptrPy = new vector<double>();
			
			// Converte os pontos para um vetor (gnuplot)
			// Ao inves de fazer a copia dos dados, aponta 
			// o endereco da memoria em que estao armazenados
			for(int i=0; i < ptrMxy->rows(); i++){
				ptrPx->push_back((double)ptrMxy->coeffRef(i,0));
				ptrPy->push_back((double)ptrMxy->coeffRef(i,1));
			}
			
			
			// Gera o grafico usando o Gnuplot 
			gera_grafico(ptrPx, ptrPy, lt);


			//Salva os resultados em arquivo
			ofstream resultados;
			resultados.open ("catenaria.dat");
			for(int i = 0;i< ptrMxy->rows();i++){
				resultados << std::setprecision(4) << ptrMxy->coeffRef(i,0) << "\t" << ptrMxy->coeffRef(i,1) << endl;
			}
			resultados.close();
			
		
			//######################## FIM CATENARIA ########################


			// Calcula a flecha devido ao vento
			vector<double>* ptrSaida {nullptr};
			ptrSaida = flecha_cabo(lt.massa, lt.cvao, T0, lt.phi, lt.ventomed);
			
			// Salva o relatorio
			r.titulo = lt.modelo+" - "+lt.nome;
			r.eds = lt.eds;
			r.nl = lt.nl;
			r.cvao = lt.cvao;
			r.hmax = lt.h0;			
			r.hseg = altura_seg(lt.tensao,lt.h0);
			r.flecha = ptrSaida->at(0);
			r.balanco = ptrSaida->at(1);
			r.flechav = ptrSaida->at(2);
			r.flat = ptrSaida->at(3);
			r.save("relatorio.xml");
			
			printf ("Altura de segurança: %.2f [m]\n", r.hseg);
			printf ("Flecha: %.2f [m]\n", r.flecha );
			printf ("Balanço: %.2f [graus]\n", r.balanco);
			printf ("Flecha Vento: %.2f [m]\n", r.flechav);
			printf ("Esforço Lateral: %.2f [kgf]\n", r.flat);
			printf ("Comprimento do cabo: %.2f [m]\n", r.ccabo);	
			printf ("Disposição do feixe: (%.2f, %.2f, %.2f) [m]\n", 
			lt.gfeixe[0], lt.gfeixe[1], lt.gfeixe[2]);	
			
			
	}	catch (std::exception &e){
			cout << "Erro: " << e.what() << "\n";
	}	
	
	return 0;

}