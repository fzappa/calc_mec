#ifndef GERAGRAFICO_H
#define GERAGRAFICO_H

#include "ParserXML.h"

void gera_grafico(const std::vector<double>* px,
									const std::vector<double>* py,
									const conf& dados);

#endif