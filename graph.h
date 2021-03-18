#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h> //iostream
#include <cassert> //assert
#include <iostream> // std::io
#include "graphexception.h" //gestore eccezioni

/**
	@file graph.h

	@brief dichiarazione della classe graph
*/

/**
	@class graph

	@brief classe che implementa il grafico
*/
class graph{
private:

	typedef unsigned int idtype;

	idtype _len; ///< dimensione degli array
	bool* _node; ///< array identificativi nodi
	bool** _arch; ///< matrice di adiacenza

	/**
		@brief inizializzatore delle variabili

		la funzione inizializza gli array di
		identificazione dei nodi e la matrice
		di adiacenza con valori false

		@param len lunghezza array
	*/
	inline void init_vars(idtype len){
		_node = new bool[len];
		_arch = new bool*[len];
		_len = len;

		for(idtype c = 0; c < len; c++){
			_node[c] = false;
			_arch[c] = new bool[len];

			for(idtype d = 0; d < len; d++){
				_arch[c][d] = false;
			}
		}
	}

	/**
		@brief funzione distruzione variabili

		la funzione si occupa di distruggere
		effettivamente le variabili inserite
		in ingresso

		@param node array identificativi nodi
		@param arch matrice di adiacenza
		@param len lunghezza array e matrice
	*/
	inline void destr_vars(bool* node, bool** arch, idtype len){
		delete[] node;

		for(idtype c = 0; c < len; c++)
			delete[] arch[c];

		delete[] arch;
	}

public:

	/**
		@brief costruttore nullo

		costruttore che inizializza la classe
		graph ad un valore nullo

		@post _len == 0
		@post _node == nullptr
		@post _arch == nullptr
	*/
	graph() : _len(0), _node(nullptr), _arch(nullptr)
	{
		#ifndef NDEBUG
		std::cout << "inizializzato grafo vuoto" << std::endl;
		#endif
	}

	/**
		@brief costruttore singolo

		costruttore che inizializza la classe
		graph con un solo nodo

		@param id identificativo nodo

		@post _len == id+1
		@post _node[id] == true
	*/
	graph(idtype id) : _len(0), _node(nullptr), _arch(nullptr)
	{
		init_vars(id+1);
		_node[id] = true;

		#ifndef NDEBUG
		std::cout << "inizializzato grafo 1 elemento" << std::endl;
		#endif
	}

	/**
		@brief distruttore classe grafo
	*/
	~graph()
	{
		destr_vars(_node,_arch,_len);
		_node = nullptr;
		_arch = nullptr;
		_len = 0;

		#ifndef NDEBUG
		std::cout << "grafo distrutto correttamente" << std::endl;
		#endif
	}

	const bool exists(const idtype id) const {
		if(id >= _len)
			return false;
		else
			return _node[id];
	}

	/**
		@brief aggiunta di un nodo

		la funzione si occupa di aggiungere un nodo
		al grafo. se il grafo non è ancora stato 
		inizializzato lo inizializza ed aggiunge il
		nodo, se il nodo è già stato inizializzato
		lo setta a true, altrimenti crea un grafo
		ex novo della dimensione corretta e copia
		i dati del vecchio grafo

		@param id identificativo nodo
	*/
	void add(idtype id)
	{
		if(_node == nullptr){ //graph vuoto

			init_vars(id+1); // inizializzo la classe
			_node[id] = true;

		} else if (id < _len) { //id già inizializzato

			if(_node[id] == true) //nodo già inserito
				throw logicexception("nodo gia inserito!", 999);

			_node[id] = true;

		} else { //id non ancora inizializzato

			bool* node_temp = _node;
			bool** arch_temp = _arch;
			idtype len_temp = _len;

			init_vars(id+1); // reinizializzo la classe
			_node[id] = true;

			//copio i vecchi dati sul nuovo grafo
			for(idtype c = 0; c < len_temp; c++){
				_node[c] = node_temp[c];
				for(idtype d = 0; d < len_temp; d++){
					_arch[c][d] = arch_temp[c][d];
				}
			}

			//distruggo i vecchi dati
			destr_vars(node_temp,arch_temp,len_temp);

			#ifndef NDEBUG
			std::cout << "copiati dati in nuovo grafo" << std::endl;
			#endif
		}
	}

	/**
		@brief rimozione di un nodo

		la funzione si occupa della rimozione di un
		nodo e degli archi associati, previo controllo
		della validità del nodo inserito come parametro

		@param id identificativo nodo
	*/
	void remove(idtype id)
	{
		if(_node == nullptr) //grafo vuoto
			throw logicexception("grafo vuoto!", 999);
		if(id >= _len) // id non valido
			throw logicexception("id non valido!", 999);
		if(!_node[id]) // nodo non presente
			throw logicexception("nodo non presente!", 999);

		// elimino il nodo
		_node[id] = false;
		
		// elimino gli archi associati
		for(idtype c = 0; c < _len; c++){
			_arch[c][id] = false;
			_arch[id][c] = false;
		}

		//se non ci sono più nodi elimino il grafo
		idtype count = 0;
		for(idtype c = 0; c < _len; c++){
			if(_node[c])
				count++;
		}
		if(count == 0){
			destr_vars(_node,_arch,_len);
			_node = nullptr;
			_arch = nullptr;
			_len = 0;
		}
	}

	/**
		@brief dimensione grafo

		ritorna la lunghezza degli
		array di supporto

		@return _len lunghezza array
	*/
	const idtype len() const
	{
		return _len;
	}

	/**
		@brief stampa del grafo

		la funzione si occupa di stampare la
		composizione de grafo su std::out,
		mostrando i nodi e gli archi attivi
	*/
	void print()
	{
		std::cout << "ids: ";
		for(idtype c = 0; c < _len; c++){
			if(_node[c])
				std::cout << c << ", ";
		}
		std::cout << std::endl;

		std::cout << "adjacency matrix: " << std::endl;
		std::cout << "   ";
		for(idtype c = 0; c < _len; c++)
				std::cout << c << "  ";
		std::cout << std::endl;
		for(idtype c = 0; c < _len; c++){
			std::cout << c << "  ";
			for(idtype d = 0; d < _len; d++){
				std::cout << _arch[c][d] << "  ";
			}
			std::cout << std::endl;
		}
	}
};

#endif