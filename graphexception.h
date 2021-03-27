/*
	Resmini Daniele Andrea - MAT: 830446
	Progetto C++ - GRAPH
*/

#ifndef GRAPHEXCEPTION_H
#define GRAPHEXCEPTION_H

#include <stdexcept>
#include <string>

class runtimeexception : public std::runtime_error
{
public:

	runtimeexception(const std::string &message) : std::runtime_error(message) {}
};

class logicexception : public std::logic_error
{
	int _value;
public:

	/*
		ERROR CODES:

			1 = grafo vuoto
			2 = uno dei nodi specificati non esiste
			3 = nodo/arco non esistente
			4 = nodo/arco già inserito
	*/
	logicexception(const std::string &message, int value) : std::logic_error(message), _value(value) {}

	int get_value(void) const
	{
		return _value;
	}
};

#endif