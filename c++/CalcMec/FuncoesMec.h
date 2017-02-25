#ifndef FUNCOESMEC_H
#define FUNCOESMEC_H

#include <cmath>
#include <vector>
#include <eigen3/Eigen/Dense>

double altura_seg(const double& V, 
									const double& H0);
									
void flecha_cabo(const double& MASSA, 
								 const double& VAO, 
								 const double& T0, 
								 const double& PHI, 
								 const double& VENTO_MED,
								 std::vector<double>& saida);
								 
void catenaria_cabo(const double& C1, 
										const double& H, 
										const double& L, 
										const double& NX, 
										double& LCABO,
										Eigen::MatrixXd& mxy);

#endif
