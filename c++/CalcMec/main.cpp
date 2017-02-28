#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <string>

#include "FuncoesMec.h"
#include "gnuplot_i.hpp"
#include "ParserXML.h"

using namespace std;
using namespace Eigen;

// Delay para o programa conseguir acessar o disco
//using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
//using std::chrono::system_clock;

int main()
{
	try{
			printf("\n#### CABO BLUEJAY - NEXANS - CIRCUITO DE 765KV ####\n\n");
			
			//Leitura dos dados
			conf lt;
			relat r;
			lt.load("dados.xml");
			
			// Definindo algumas constantes
			const double T0 {lt.trup*(lt.eds/100.0)};
			const double p {lt.massa};
			const double C1 {T0/p};
			
			printf("EDS = %.2f %%\n", lt.eds);
			printf("Divisões na catenária = %.2f m\n", lt.nl);
			
			// Chama a funcao catenaria e retorna o comprimento do cabo 
			// e a matriz posicao x altura
			Eigen::MatrixXd* mxy;
			mxy = catenaria_cabo(C1, lt.h0, lt.cvao, lt.nl, r.ccabo);
			
			cout << "SAIDA" << endl;

	//	######################### CATENARIA #########################
	//	#Dados da catenaria
			printf("Comprimento do vão: %.2f m\n",lt.cvao);
			printf("Comprimento do cabo: %.2f m\n",r.ccabo);
			printf("H(max) = %.2f m\n", lt.h0);
			
			r.hmin = mxy->col(1).minCoeff();
			printf("H(min) = %.2f m\n", r.hmin);
			
			r.qcil = mxy->rows();
			printf("Quantidade de cilindros (TRICAMP) = %.2f \n\n", r.qcil);
			
			vector<double> px, py;
			
			//converte os pontos para um vetor (gnuplot)
			for(int i=0;i<mxy->rows();i++){
				px.push_back((double)mxy->coeffRef(i,0));
				py.push_back((double)mxy->coeffRef(i,1));
			}
			
			// ------- Gera o grafico usando o Gnuplot ---------- //
			Gnuplot gp;
			std::ostringstream legenda;  // para compor a legenda

			gp.reset_all();
			
			switch (lt.grafico){
				case 1:
					gp.savetops(lt.modelo+" - "+lt.nome);
					break;
				case 2:
					gp.savetosvg(lt.modelo+" - "+lt.nome);
					break;
				case 3:
					gp.savetojpg(lt.modelo+" - "+lt.nome);
					break;
				case 4:
					gp.savetopng(lt.modelo+" - "+lt.nome);
					break;
				case 5:
					gp.savetopdf(lt.modelo+" - "+lt.nome);
					break;
				case 6:
					gp.savetoepslatex(lt.modelo+" - "+lt.nome);
					break;
				default:
					gp.savetopng(lt.modelo+" - "+lt.nome);
			}
			
			gp.set_grid().set_style("lines");
			gp.set_xrange((-lt.cvao/2),(lt.cvao/2)).set_yrange(0,lt.h0+10.0);
			gp.set_title(lt.modelo+" - "+lt.nome);
			gp.set_xlabel("Comprimento").set_ylabel("Altura");
			
			legenda << "Vão de " << lt.cvao << "m";
			gp.plot_xy(px,py,legenda.str());
			
			// Executa uma pausa
			this_thread::sleep_for(100ms);
		  //---------------------------------------------------//
		
			//Salva os resultados em arquivo
			ofstream resultados;
			resultados.open ("catenaria.dat");
			for(int i = 0;i< mxy->rows();i++){
				resultados << mxy->coeffRef(i,0) << "\t" << mxy->coeffRef(i,1) << endl;
			}
			resultados.close();
			
			// Salva o relatorio
			r.titulo = lt.modelo+" - "+lt.nome;
			r.eds = lt.eds;
			r.nl = lt.nl;
			r.cvao = lt.cvao;
			r.hmax = lt.h0;

		
		
	//	######################## FIM CATENARIA ########################


			vector<double> saida(4);
			flecha_cabo(lt.massa, lt.cvao, T0, lt.phi, lt.ventomed, saida);
			
			r.hseg = altura_seg(lt.tensao,lt.h0);
			r.flecha = saida[0];
			r.balanco = saida[1];
			r.flechav = saida[2];
			r.flat = saida[3];
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