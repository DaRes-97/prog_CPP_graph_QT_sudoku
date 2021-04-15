/*
	Resmini Daniele Andrea - MAT: 830446
	Progetto C++ - GRAPH
*/

/**
	@file graph.h
*/
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h> //iostream
#include <cassert> //assert
#include <iostream> // std::io
#include <algorithm> // std::swap

/**
	@class graphexception

	@brief classe che implementa il gestore eccezioni
*/
class graphexception : public std::runtime_error
{

public:

	/**
        @brief costruttore eccezione
	*/
	graphexception(const std::string &message) : std::runtime_error(message) {}

};

/**
	@class graph

	@brief classe che implementa il grafo
*/
template<typename T, typename F>
class graph
{
private:

	typedef T value_type; //tipo del nodo
    typedef F funct_type; //tipo funtore confronto
	typedef unsigned int idx_type; //tipo dimensione array

	idx_type _len; ///< dimensione degli array
	value_type* _node; ///< array degli identificativi dei nodi
	bool** _arch; ///< matrice di adiacenza

	/**
		@brief inizializzatore delle variabili

		la funzione inizializza la matrice
		di adiacenza con valori false e crea
		l'array degli identificativi dei nodi

		@param len lunghezza array
	*/
	inline void init_vars(idx_type len)
	{
		if(len == 0){
			_node = nullptr;
			_arch = nullptr;
			_len = 0;

			return;
		}

		try{
			_node = new value_type[len];
			_arch = new bool*[len];
			_len = len;

			for(idx_type c = 0; c < len; c++){
				_arch[c] = new bool[len];
				for(idx_type d = 0; d < len; d++){
					_arch[c][d] = false;
				}
			}
		} catch (...) {
			//errore in allocazione memoria
			destr_vars(_node, _arch, _len);
			_node = nullptr;
			_arch = nullptr;
			_len = 0;
			throw;
		}
	}

	/**
		@brief funzione distruzione variabili

		la funzione si occupa di distruggere
		effettivamente le variabili inserite
		in ingresso

		@param node array identificativi dei nodi
		@param arch matrice di adiacenza
		@param len lunghezza array e matrice
	*/
	inline void destr_vars(value_type* node, bool** arch, idx_type len)
	{
		delete[] node;

		for(idx_type c = 0; c < len; c++){
			delete[] arch[c];
		}
		delete[] arch;
	}

	/**
		@brief funzione di swap
	*/
	void swap(graph<value_type,funct_type> &other)
	{
		std::swap(this->_node,other._node);
		std::swap(this->_arch,other._arch);
		std::swap(this->_len,other._len);
	}

	/**
		@brief indice del nodo

		dato l'identificativo del nodo ritorna
		la sua posizione nell'array

		@param node identificativo del nodo
		@return c indice (IDX) del nodo
	*/
	idx_type index_of(const value_type &node) const
	{
        funct_type compare;
		for(int c = 0; c < _len; c++){
			if(compare(_node[c],node))
				return c;
		}

		//nodo non trovato
		return _len;
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

		@param node identificativo del nodo

		@post _len == 1
	*/
	explicit graph(value_type node) : _len(0), _node(nullptr), _arch(nullptr)
	{
		init_vars(1); //allocazione
		_node[0] = node; //assegnamento

		#ifndef NDEBUG
		std::cout << "inizializzato grafo 1 elemento" << std::endl;
		#endif
	}

	/**
		@brief costruttore di copia

		costruttore di copia tra due graph

		@param other graph da copiare
	*/
	graph(const graph<value_type,funct_type> &other) : _len(0), _node(nullptr), _arch(nullptr)
	{
		//allocazione
		init_vars(other._len);
		//assegnamento
		for(idx_type c = 0; c < _len; c++){
			_node[c] = other._node[c];
			for(idx_type d = 0; d < _len; d++){
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
		destr_vars(_node, _arch, _len);
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

		@param node identificativo del nodo
		@return res risultato della verifica
	*/
	bool exists(const value_type &node) const
	{
		int idx = index_of(node);

		if(idx == _len){
			return false;
		}

		return true;
	}

	/**
		@brief esistenza di un arco nel grafo

		la funzione verifica l'esistenza di un
		determinato arco all'interno del grafo

		@param src identificativo nodo di partenza
		@param dst identificativo nodo di arrivo
		@return res risultato della verifica
	*/
	bool has_edge(const value_type &src, const value_type &dst) const
	{
		if(exists(src) && exists(dst)){
			idx_type idx1 = index_of(src);
			idx_type idx2 = index_of(dst);

			bool res = _arch[idx1][idx2];
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
	bool equals(const graph<value_type,funct_type> &other) const
	{

		if(num_nodes() != other.num_nodes() || //stesso num di nodi
			num_arches() != other.num_arches()) // stesso num di archi
		{
			return false;
		}

		for(idx_type c = 0; c < _len; c++){
			if(!other.exists(_node[c])) //stessi nodi
				return false;

			for(idx_type d = 0; d < _len; d++){
				if(_arch[c][d]){
					if(!other.has_edge(_node[c],_node[d])) // stessi archi
						return false;
				}
			}
		}

		return true;
	}

	/**
		@brief aggiunta di un nodo

		la funzione si occupa di aggiungere un nodo
		al grafo. se il grafo non è ancora stato
		inizializzato lo inizializza ed aggiunge il
		nodo, se il grafo è già stato inizializzato
		crea un grafo ex novo della dimensione
 		corretta e copia i dati del vecchio grafo

		@param node nome del nuovo nodo
		@throws graphexception nodo già inserito
	*/
	void add(const value_type &node)
	{
		if(exists(node)) //nodo già inserito
			throw graphexception("nodo gia inserito!");

		if(_len == 0){ //graph vuoto

			init_vars(1); //allocazione
			_node[0] = node; //assegnamento

		} else { //graph già inizializzato

			value_type* node_temp = _node;
			bool** arch_temp = _arch;
			idx_type len_temp = _len;

			init_vars(len_temp+1); //allocazione
			_node[_len-1] = node; //assegnamento

			//copio i vecchi dati sul nuovo grafo
			for(idx_type c = 0; c < len_temp; c++){
				_node[c] = node_temp[c];
				for(idx_type d = 0; d < len_temp; d++){
					_arch[c][d] = arch_temp[c][d];
				}
			}

			//distruggo i vecchi dati
			destr_vars(node_temp,arch_temp,len_temp);
		}

		#ifndef NDEBUG
		std::cout << "nodo aggiunto correttamente" << std::endl;
		#endif
	}

	/**
		@brief aggiunta di un arco

		la funzione crea un arco orientato tra i due
		nodi selezionati in ingresso

		@param src identificativo nodo di partenza
		@param dst identificativo nodo di arrivo
		@throws graphexception uno dei nodi non esiste
		@throws graphexception arco già inserito
	*/
	void add(const value_type &src, const value_type &dst)
	{
		if(!exists(src) || !exists(dst))
			throw graphexception("uno dei nodi specificati non esiste!");

		idx_type idx1 = index_of(src);
		idx_type idx2 = index_of(dst);

		if(_arch[idx1][idx2])
			throw graphexception("arco gia inserito!");

		_arch[idx1][idx2] = true;

		#ifndef NDEBUG
		std::cout << "arco aggiunto correttamente" << std::endl;
		#endif
	}

	/**
		@brief rimozione di un nodo

		la funzione si occupa della rimozione di un
		nodo e degli archi associati, previo controllo
		della validità del nodo inserito come parametro

		@param node identificativo del nodo da rimuovere
		@throws graphexception grafo vuoto
		@throws graphexception nodo non presente
	*/
	void remove(value_type node)
	{
		if(_len == 0) //grafo vuoto
			throw graphexception("grafo vuoto!");
		if(!exists(node)) // nodo non presente
			throw graphexception("nodo non presente!");

		//indice nodo da eliminare
		idx_type idx = index_of(node);

		//puntatori ai vecchi dati
		value_type* node_temp = _node;
		bool** arch_temp = _arch;
		idx_type len_temp = _len;

		//allocazione nuovi array
		init_vars(len_temp-1);

		if(_len != 0){
			//copio i vecchi dati
			int row = 0;
			int col = 0;
			for(int c = 0; c < len_temp; c++){
				col = 0;
				if(c != idx){
					_node[row] = node_temp[c];

					for(int d = 0; d < len_temp; d++){
						if(d != idx){
							_arch[row][col] = arch_temp[c][d];
							col++;
						}
					}

					row++;
				}
			}
		}

		//distruggo i vecchi dati
		destr_vars(node_temp,arch_temp,len_temp);

		#ifndef NDEBUG
		std::cout << "nodo eliminato correttamente" << std::endl;
		#endif
	}

	/**
		@brief rimozione di un arco

		la funzione rimuove l'arco orientato tra i due
		nodi selezionati in ingresso

		@param src identificativo nodo di partenza
		@param dst identificativo nodo di arrivo
		@throws graphexception uno dei nodi non esiste
		@throws graphexception arco non presente
	*/
	void remove(value_type src, value_type dst)
	{
		if(!exists(src) || !exists(dst))
			throw graphexception("uno dei nodi specificati non esiste!");

		idx_type idx1 = index_of(src);
		idx_type idx2 = index_of(dst);

		if(!_arch[idx1][idx2])
			throw graphexception("arco non presente!");

		_arch[idx1][idx2] = false;

		#ifndef NDEBUG
		std::cout << "arco eliminato correttamente" << std::endl;
		#endif
	}

	/**
		@brief conteggio numero di nodi

		la funzione effettua il conteggio del
		numero di nodi presenti nel grafo

		@return _len numero di nodi nel grafo
	*/
	idx_type num_nodes() const
	{
		return _len;
	}

	/**
		@brief conteggio numero di archi

		la funzione effettua il conteggio del
		numero di archi presenti nel grafo

		@return count numero di archi nel grafo
	*/
	idx_type num_arches() const
	{
		idx_type count = 0;
		for(idx_type c = 0; c < _len; c++){
			for(idx_type d = 0; d < _len; d++){
				if(_arch[c][d])
					count++;
			}
		}

		return count;
	}

	/**
		@brief stampa del grafo

		la funzione si occupa di stampare la
		composizione del grafo su std::out,
		mostrando i nodi e gli archi attivi
	*/
	void print()
	{
		std::cout << *this << std::endl;
	}

	/**
		@brief operatore di assegnamento

		operatore di assegnamento che serve per copiare
		il contenuto di other in *this

		@param other graph da copiare
		@return reference a graph<value_type>
	*/
	graph& operator=(const graph<value_type,funct_type> &other)
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

	/**
		@brief ridefinizione operatore di stream

		ridefinizione dell'operatore di stream per scrivere
		un graph su uno stream di output

		@param os stream di output (operando di sx)
		@param db graph da scrivere (operando di dx)

		@return reference allo stream di output
	*/
	friend std::ostream& operator<<(std::ostream &os, const graph<value_type,funct_type> &g) {

		os << "<node,idx>: ";
		for(idx_type c = 0; c < g._len; c++){
			os << "<" << g._node[c] << "," << c << ">, ";
		}
		os << "\n";

		os << "adjacency matrix: " << "\n";
		os << "   ";
		for(idx_type c = 0; c < g._len; c++)
				os << c << "  ";
		os << "\n";
		for(idx_type c = 0; c < g._len; c++){
			os << c << "  ";
			for(idx_type d = 0; d < g._len; d++){
				os << g._arch[c][d] << "  ";
			}
			os << "\n";
		}

		return os;
	}

	class const_iterator {

		const T *ptr_node;

	public:
		typedef std::forward_iterator_tag	iterator_category;
		typedef T				value_type;
		typedef const value_type*			pointer;
		typedef const value_type&			reference;


		const_iterator() : ptr_node(nullptr) {}

		const_iterator(const const_iterator &other) : ptr_node(other.ptr_node) {}

		const_iterator& operator=(const const_iterator &other)
		{
			ptr_node = other.ptr_node;
			return *this;
		}

		~const_iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const
		{
			return *ptr_node;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const
		{
			return ptr_node;
		}

		// Operatore di iterazione post-incremento
		const_iterator operator++(int)
		{
			const_iterator tmp(this);
			ptr_node++;
			return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++()
		{
			ptr_node++;
			return *this;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const
		{
			return (ptr_node == other.ptr_node);
		}

		// Diversita'
		bool operator!=(const const_iterator &other) const
		{
			return (ptr_node != other.ptr_node);
		}

	private:
		//Dati membro
		friend class graph;

		// Costruttore privato di inizializzazione usato dalla classe container
		const_iterator(const value_type* nm) : ptr_node(nm) {}

	}; // classe const_iterator

	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const
	{
		return const_iterator(_node);
	}

	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const
	{
		return const_iterator(_node+_len);
	}
};

#endif
