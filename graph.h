#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h> //iostream
#include <cassert> //assert
#include <iostream> // std::io
#include <algorithm> // std::swap
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

	void swap(graph &other)
	{
		std::swap(this->_node,other._node);
		std::swap(this->_arch,other._arch);
		std::swap(this->_len,other._len);
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
		@brief costruttore di copia

		costruttore di copia tra due graph

		@param other graph da copiare
	*/
	graph(const graph &other) : _len(0), _node(nullptr), _arch(nullptr)
	{
		init_vars(other._len);

		for(idtype c = 0; c < _len; c++){
			_node[c] = other._node[c];
			for(idtype d = 0; d < _len; d++){
				_arch[c][d] = other._arch[c][d];
			}
		}

		#ifndef NDEBUG
		std::cout << "inizializzato grafo tramite copia" << std::endl;
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

	/**
		@brief esistenza di un nodo nel grafo

		la funzione verifica l'esistenza di un
		determinato nodo all'interno del grafo

		@param id nodo da verificare
		@return res risultato della verifica
	*/
	const bool exists(const idtype id) const
	{
		if(id >= _len){
			return false;
		}
		else{
			bool res = _node[id];
			return res;
		}
	}

	/**
		@brief esistenza di un arco nel grafo

		la funzione verifica l'esistenza di un
		determinato arco all'interno del grafo

		@param id1 nodo di partenza
		@param id2 nodo di arrivo
		@return res risultato della verifica
	*/
	const bool has_edge(idtype id1, idtype id2) const
	{
		if(id1 < _len && id2 < _len){
			bool res = _arch[id1][id2];
			return res;
		} else{
			return false;
		}
	}

	/**
		@brief uguaglianza tra due graph

		la funzione controlla che i due graph
		siano della stessa dimensione ed abbiano
		gli stessi nodi e gli stessi archi attivi

		@param other graph da confrontare con this
	*/
	const bool equals(const graph &other) const {
		if(_len != other._len)
			return false;

		for(idtype c = 0; c < _len; c++){
			if(_node[c] != other._node[c])
				return false;

			for(idtype d = 0; d < _len; d++){
				if(_arch[c][d] != other._arch[c][d])
					return false;
			}
		}

		return true;
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

			if(_node[id]) //nodo già inserito
				throw logicexception("nodo gia inserito!", 4);

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
		@brief aggiunta di un arco

		la funzione crea un arco orientato tra i due
		nodi selezionati in ingresso

		@param id1 identificativo nodo 1
		@param id2 identificativo nodo 2
	*/
	void add(idtype id1, idtype id2)
	{
		if(!exists(id1) || !exists(id2))
			throw logicexception("uno dei nodi specificati non esiste!", 2);
		if(_arch[id1][id2])
			throw logicexception("arco gia inserito!", 4);

		_arch[id1][id2] = true;
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
			throw logicexception("grafo vuoto!", 1);
		if(id >= _len) // id non valido
			throw logicexception("id non valido!", 2);
		if(!_node[id]) // nodo non presente
			throw logicexception("nodo non presente!", 3);

		// elimino il nodo
		_node[id] = false;
		
		// elimino gli archi associati
		for(idtype c = 0; c < _len; c++){
			_arch[c][id] = false;
			_arch[id][c] = false;
		}

		//se non ci sono più nodi elimino il grafo
		if(num_nodes() == 0){
			destr_vars(_node,_arch,_len);
			_node = nullptr;
			_arch = nullptr;
			_len = 0;
		}
	}

	/**
		@brief rimozione di un arco

		la funzione rimuove l'arco orientato tra i due
		nodi selezionati in ingresso

		@param id1 identificativo nodo 1
		@param id2 identificativo nodo 2
	*/
	void remove(idtype id1, idtype id2)
	{
		if(!exists(id1) || !exists(id2))
			throw logicexception("uno dei nodi specificati non esiste!", 2);
		if(!_arch[id1][id2])
			throw logicexception("arco non presente!", 3);

		_arch[id1][id2] = false;
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
		@brief conteggio numero di nodi

		la funzione effettua il conteggio del
		numero di nodi presenti nel grafo

		@return count numero di nodi nel grafo
	*/
	const idtype num_nodes() const
	{
		idtype count = 0;
		for(idtype c = 0; c < _len; c++){
			if(_node[c])
				count++;
		}

		return count;
	}

	/**
		@brief conteggio numero di archi

		la funzione effettua il conteggio del
		numero di archi presenti nel grafo

		@return count numero di archi nel grafo
	*/
	const idtype num_arches() const
	{
		idtype count = 0;
		for(idtype c = 0; c < _len; c++){
			for(idtype d = 0; d < _len; d++){
				if(_arch[c][d])
					count++;
			}
		}

		return count;
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

	/**
		@brief operatore di assegnamento

		operatore di assegnamento che serve per copiare
		il contenuto di other in *this

		@param other graph da copiare
		@return reference a graph
	*/
	graph& operator=(const graph &other)
	{
		if(&other != this){ //controllo auto-assegnamento
			graph tmp(other);
			tmp.swap(*this);
		}

		#ifndef NDEBUG
		std::cout << "graph swapped" << std::endl;
		#endif

		return *this;
	}
};

#endif