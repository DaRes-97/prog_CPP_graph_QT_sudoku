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

	@brief classe che implementa il grafo
*/
template<typename T>
class graph
{
private:

	typedef unsigned int idtype;

	idtype _len; ///< dimensione degli array
	T* _node; ///< array degli identificativi dei nodi
	bool** _arch; ///< matrice di adiacenza

	/**
		@brief inizializzatore delle variabili

		la funzione inizializza la matrice
		di adiacenza con valori false e crea
		l'array degli identificativi dei nodi

		@param len lunghezza array
	*/
	inline void init_vars(idtype len)
	{
		if(len == 0){
			_node = nullptr;
			_arch = nullptr;
			_len = 0;

			return;
		}

		_node = new T[len];
		_arch = new bool*[len];
		_len = len;

		for(idtype c = 0; c < len; c++){
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

		@param node array identificativi dei nodi
		@param arch matrice di adiacenza
		@param len lunghezza array e matrice
	*/
	inline void destr_vars(T* node, bool** arch, idtype len)
	{
		delete[] node;

		for(idtype c = 0; c < len; c++){
			delete[] arch[c];
		}
		delete[] arch;
	}

	/**
		@brief funzione di swap
	*/
	void swap(graph<T> &other)
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
	const idtype indexof(const T node) const
	{
		for(int c = 0; c < _len; c++){
			if(_node[c] == node)
				return c;
		}

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

		@param node nome del nodo

		@post _len == 1
	*/
	graph(T node) : _len(0), _node(nullptr), _arch(nullptr)
	{
		init_vars(1);
		_node[0] = node;

		#ifndef NDEBUG
		std::cout << "inizializzato grafo 1 elemento" << std::endl;
		#endif
	}

	/**
		@brief costruttore di copia

		costruttore di copia tra due graph

		@param other graph da copiare
	*/
	graph(const graph<T> &other) : _len(0), _node(nullptr), _arch(nullptr)
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
	const bool exists(const T node) const
	{
		int idx = indexof(node);

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
	const bool has_edge(T src, T dst) const
	{
		if(exists(src) && exists(dst)){
			idtype idx1 = indexof(src);
			idtype idx2 = indexof(dst);

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
	const bool equals(const graph<T> &other) const
	{

		if(num_nodes() != other.num_nodes() || //stesso num di nodi
			num_arches() != other.num_arches()) // stesso num di archi
		{
			return false;
		}

		for(idtype c = 0; c < _len; c++){
			if(!other.exists(_node[c])) //stessi nodi
				return false;

			for(idtype d = 0; d < _len; d++){
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
	*/
	void add(T node)
	{
		if(exists(node)) //nodo già inserito
			throw logicexception("nodo gia inserito!", 4);

		if(_len == 0){ //graph vuoto

			init_vars(1); // inizializzo la classe
			_node[0] = node;

		} else { //graph già inizializzato

			T* node_temp = _node;
			bool** arch_temp = _arch;
			idtype len_temp = _len;

			init_vars(len_temp+1); // reinizializzo la classe
			_node[_len-1] = node;

			//copio i vecchi dati sul nuovo grafo
			for(idtype c = 0; c < len_temp; c++){
				_node[c] = node_temp[c];
				for(idtype d = 0; d < len_temp; d++){
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
	*/
	void add(T src, T dst)
	{
		if(!exists(src) || !exists(dst))
			throw logicexception("uno dei nodi specificati non esiste!", 2);

		idtype idx1 = indexof(src);
		idtype idx2 = indexof(dst);

		if(_arch[idx1][idx2])
			throw logicexception("arco gia inserito!", 4);

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
	*/
	void remove(T node)
	{
		if(_len == 0) //grafo vuoto
			throw logicexception("grafo vuoto!", 1);
		if(!exists(node)) // nodo non presente
			throw logicexception("nodo non presente!", 3);

		//indice nodo da eliminare
		idtype idx = indexof(node);

		//puntatori ai vecchi dati
		T* node_temp = _node;
		bool** arch_temp = _arch;
		idtype len_temp = _len;


		//inizializzo nuovi array
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
	*/
	void remove(T src, T dst)
	{
		if(!exists(src) || !exists(dst))
			throw logicexception("uno dei nodi specificati non esiste!", 2);

		idtype idx1 = indexof(src);
		idtype idx2 = indexof(dst);

		if(!_arch[idx1][idx2])
			throw logicexception("arco non presente!", 3);

		_arch[idx1][idx2] = false;

		#ifndef NDEBUG
		std::cout << "arco eliminato correttamente" << std::endl;
		#endif
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
		std::cout << "<node,idx>: ";
		for(idtype c = 0; c < _len; c++){
			std::cout << "<" << _node[c] << "," << c << ">, ";
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
		@return reference a graph<T>
	*/
	graph& operator=(const graph<T> &other)
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

	class const_iterator {

		const T *ptr_node;

	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

	
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
		const_iterator(const T* nm) : ptr_node(nm) {}
		
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
