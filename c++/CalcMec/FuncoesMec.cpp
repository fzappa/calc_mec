#include "FuncoesMec.h"

#define PI 3.14159265

using namespace std;
using namespace Eigen;

/**
  Função para calculo da altura de segurança
  @param V: Nível de tensão em V
  @param H0: Altura dos condutores em metros
  @return Altura de segurança em metros
*/
double altura_seg(const double& V, 
									const double& H0){
	
	return H0 + 0.01 * (((V/1000)/sqrt(3)) - 50);
}


/**
	Função que calcula a flecha de um cabo
	Autor: Alan Franco
	
	@param MASSA Massa do cabo [kg]
	@param VAO Comprimento do vao [m]
	@param T0 Tração inicial [N]      
	@param PHI Angulo de balanço [graus]
	@param VENTO_MED Vento medio [m/s]
	@return Retorna um vector na forma: (Flecha, Balanco, Flecha Vento, Esforco lateral)

	#%%%%%%%%%%%%%%%%%%%%%% Equações %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	#%%% (Livro: Projetos Mecânicos das Linhas Aéreas de Transmissão) 
	#%%% Labegalini, Fuchs, Almeida. Pg 21, 2ª edição  
	#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	*/
	void flecha_cabo(const double& MASSA, 
									 const double& VAO, 
									 const double& T0, 
									 const double& PHI, 
									 const double& VENTO_MED, 
									 std::vector<double>& saida){
		
		double flecha, forv, bal, foreq, flev, esfl;
			
		flecha = (MASSA*(VAO*VAO))/(8*T0);             // flecha [m]
		forv = (PHI/2)*(VENTO_MED*VENTO_MED);          // forca do vento [kgf]
		bal = atan(forv/MASSA)*(180/PI);               // angulo de balaco [graus]
		foreq	= pow(((MASSA*MASSA)+(forv*forv)),0.5);  // forca equivalente [kgf]
		flev = (foreq*(VAO*VAO))/(8*T0);               // flecha devido ao vento [m]
		esfl = ((foreq*VAO)/2);                        // esforco lateral [kgf]
		
		saida[0] = flecha;
		saida[1] = bal;
		saida[2] = flev;
		saida[3] = esfl;
	}
	

//#if 0

Eigen::MatrixXd *catenaria_cabo(const double& C1, 
																const double& H, 
																const double& VAO, 
																const double& NX,
																double& LCABO){
		
		//Inicializa o ponteiro
		Eigen::MatrixXd *mxy {new Eigen::MatrixXd};
		
		//inicializa o array
		unsigned short int i {0};
		for(double val=(-VAO/2);val<=(VAO/2);val+=(VAO/NX)){
			i++;
		}
		mxy->resize(i,2);
		
		//coloca os valores
		i=0;
		for(double val=(-VAO/2);val<=(VAO/2);val+=(VAO/NX)){
			(*mxy)(i,0) = val;
			// Outro modos de referenciar:
			// (*mxy).coeffRef(i,0)
			// mxy->coeffReff(i,0)
			i++;
		}
		
		//Calcula os pontos da catenaria
		mxy->col(1) = H - (C1*(((mxy->col(0)/C1).array().cosh())-1)); 
		
		// inverte a curva
		mxy->col(1) = H - (mxy->col(1).array() - mxy->col(1).minCoeff()); 
		
		LCABO = 2*C1*sinh(VAO/(2*C1));
		
		return mxy;
	}
