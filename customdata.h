/*
	Resmini Daniele Andrea - MAT: 830446
	Progetto C++ - GRAPH
*/

#ifndef CUSTOMDATA_H
#define CUSTOMDATA_H

#include<string>

//tipo di dato custom
typedef struct an{
	std::string nome;
	std::string cognome;
} custom;

//overload operatore stream output
std::ostream& operator<<(std::ostream &os, const custom &cus) {
	os << "{";
	os << cus.nome << ",";
	os << cus.cognome;
	os << "}";

	return os;
}

//overload operatore uguaglianza
bool operator==(const custom& sx, const custom& dx){
	bool cond1 = sx.nome.compare(dx.nome) == 0;
	bool cond2 = sx.cognome.compare(dx.cognome) == 0;

	return cond1 && cond2;
}

//overload operatore disuguaglianza
bool operator!=(const custom& sx, const custom& dx){
	bool cond1 = sx.nome.compare(dx.nome) == 0;
	bool cond2 = sx.cognome.compare(dx.cognome) == 0;

	return !cond1 || !cond2;
}
#endif // CUSTOMDATA_H
