#ifndef FUNCOESMEC_H
#define FUNCOESMEC_H

//#define EIGEN_USE_MKL_ALL

#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a > b) ? a : b)

#include <Eigen/Dense>  // ln -s /usr/include/eigen3/Eigen /usr/include (Arch Linux)
#include <functional>   // std::function
#include <memory>       // std::unique_ptr
#include <vector>

struct conf {

    // Dados do vao
    double ncfeixe{0.0};  // number of conductors in beam
    double dfeixe{0.0};   // beam diameter
    double cvao{0.0};     // length of the vessel
    double h0{0.0};       // height of departure (leveled distances)

    // uneven distances
    double hA{0.0};  // height of tower A
    double hB{0.0};  // height of tower B

    double eds{0.0};     // eds
    double nl{cvao};     // number of divisions in the catenary
    double tensao{0.0};  // voltage level [V]
    std::vector<double> gfeixe{0.0, 0.0, 0.0};

    // TODO -> Create a list with some cable types
    // Cables caracteristics
    double secao{0.0};
    double phi{0.0};
    double massa{0.0};
    double trup{0.0};
    double alphafinal{0.0};
    double elastfinal{0.0};
    double pminimo{0.0};
    double pmaximo{0.0};
    double tcop{0.0};
    double tamb{0.0};
    double tmax{0.0};
    double tmin{0.0};
    double ventomed{0.0};
};

// Maximum current supported by cable
double iEHS(const conf &, const double &);
double iAlumoweld(const conf &, const double &);
double iACRS(const conf &, const double &);

double alturaSeg(const conf &);
std::unique_ptr<std::vector<double>> forcasExternas(const conf &);
std::unique_ptr<Eigen::MatrixXd> catenaria(const conf &, double &, double &, double &, double &);
std::unique_ptr<Eigen::MatrixXd> eqEstadoTemperatura(const conf &);
double eqTermicaCabo(const conf &);

double NewtonRaphson(std::function<double(double)> const &, std::function<double(double)> const &,
                     const double &);

#endif
