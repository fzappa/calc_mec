#ifndef FUNCOESMEC_H
#define FUNCOESMEC_H

#include <cmath>
#include <vector>
#include <eigen3/Eigen/Dense>

double altura_seg(const double&, 
									const double&);
									
std::vector<double>* flecha_cabo(const double&, 
																 const double&,
																 const double&, 
																 const double&, 
																 const double&);
								 
Eigen::MatrixXd* catenaria_cabo(const double&, 
																const double&, 
																const double&, 
																const double&, 
																double&);

#endif
