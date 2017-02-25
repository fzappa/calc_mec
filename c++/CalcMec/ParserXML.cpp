
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <iostream>

#include "ParserXML.h"

//Referencias
//http://www.boost.org/doc/libs/1_42_0/doc/html/boost_propertytree/tutorial.html
//http://www.technical-recipes.com/2014/using-boostproperty_tree/

//TODO Implementar leitura de vetores do XML

void conf::load(const std::string &filename)
{

    // Create empty property tree object
    using boost::property_tree::ptree;
    ptree pt;

    read_xml(filename, pt);

    // Leitura dos dados do vao
    nome = pt.get<std::string>("projeto.nome");
		grafico = pt.get<int>("projeto.grafico");
    ncfeixe = pt.get<double>("projeto.vao.ncfeixe");
    dfeixe = pt.get<double>("projeto.vao.dfeixe");
    cvao = pt.get<double>("projeto.vao.comprimento");
    h0 = pt.get<double>("projeto.vao.h0");
    eds = pt.get<double>("projeto.vao.eds");
    nl = pt.get<double>("projeto.vao.nl");
    tensao = pt.get<double>("projeto.vao.tensao");
		gfeixe[0] = pt.get<double>("projeto.vao.gfeixe.e");
		gfeixe[1] = pt.get<double>("projeto.vao.gfeixe.c");
		gfeixe[2] = pt.get<double>("projeto.vao.gfeixe.d");

    // Leitura das caracteristicas do cabo
    modelo = pt.get<std::string>("projeto.cabo.modelo");
    secao = pt.get<double>("projeto.cabo.secao");
    phi = pt.get<double>("projeto.cabo.phi");
    massa = pt.get<double>("projeto.cabo.massa");
    trup = pt.get<double>("projeto.cabo.trup");
    alphafinal = pt.get<double>("projeto.cabo.alphafinal");
    elastfinal = pt.get<double>("projeto.cabo.elastfinal");
    pminimo = pt.get<double>("projeto.cabo.pminimo");
    pmaximo = pt.get<double>("projeto.cabo.pmaximo");
    tcop = pt.get<double>("projeto.cabo.tcop");
    tamb = pt.get<double>("projeto.cabo.tamb");
    tmax = pt.get<double>("projeto.cabo.tmax");
    tmin = pt.get<double>("projeto.cabo.tmin");
    ventomed = pt.get<double>("projeto.cabo.ventomed");

}

void conf::save(const std::string &filename)
{

    // Create empty property tree object
    using boost::property_tree::ptree;
    ptree pt;

    // Put log filename in property tree
    pt.put("projeto.nome", nome);

    // Put debug level in property tree
    pt.put("projeto.vao.tensao", tensao);
    pt.put("projeto.cabo.modelo", modelo);
  
    // Write property tree to XML file
    write_xml(filename, pt, std::locale(), 
        boost::property_tree::xml_writer_make_settings<ptree::key_type>(' ', 1u));

}


void relat::save(const std::string &filename)
{

    // Create empty property tree object
    using boost::property_tree::ptree;
    ptree pt;

    // Put log filename in property tree
    pt.put("projeto.titulo", titulo);
    pt.put("projeto.relatorio.eds", eds);
    pt.put("projeto.relatorio.nl", nl);
		pt.put("projeto.relatorio.cvao", cvao);
		pt.put("projeto.relatorio.ccabo", ccabo);
		pt.put("projeto.relatorio.hmax", hmax);
		pt.put("projeto.relatorio.hmin", hmin);
		pt.put("projeto.relatorio.qcil", qcil);
		pt.put("projeto.relatorio.hseg", hseg);
		pt.put("projeto.relatorio.flecha", flecha);
		pt.put("projeto.relatorio.balanco", balanco);	
		pt.put("projeto.relatorio.flechav", flechav);
		pt.put("projeto.relatorio.cvao", cvao);
  
    // Write property tree to XML file
    write_xml(filename, pt, std::locale(), 
        boost::property_tree::xml_writer_make_settings<ptree::key_type>(' ', 1u));

}
