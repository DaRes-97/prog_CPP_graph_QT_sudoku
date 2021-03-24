#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h> //iostream
#include <cassert> //assert
#include <iostream> // std::io
#include <algorithm> // std::swap
#include "graphexception.h" //gestore eccezioni

#define TRIM_ENABLED 1 ///< abilito o meno il trim

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
	T* _name; ///< array nomi dei nodi
	bool* _node; ///< array identificativi nodi
	bool** _arch; ///< matrice di adiacenza

	/**
		@brief inizializzatore delle variabili

		la funzione inizializza gli array di
		identificazione dei nodi e la matrice
		di adiacenza con valori false e crea
		l'array dei nomi dei nodi

		@param len lunghezza array
	*/
	inline void init_vars(idtype len)
	{
		_name = new T[len];
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

		@param name array nomi dei nodi
		@param node array identificativi nodi
		@param arch matrice di adiacenza
		@param len lunghezza array e matrice
	*/
	inline void destr_vars(T* name, bool* node, bool** arch, idtype len)
	{
		delete[] node;
		delete[] name;

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
		std::swap(this->_name,other._name);
		std::swap(this->_node,other._node);
		std::swap(this->_arch,other._arch);
		std::swap(this->_len,other._len);
	}

	/**
		@brief primo elemento libero

		la funzione ritorna il primo index libero
		all'interno dell'array dei nodi. Questa 
		funzione automatizza la gestione degli
		array per quanto riguarda l'aggiunta
		dei nodi

		@return idx primo indice disponibile
	*/
	idtype first_free()
	{
		idtype idx = 0;

		while(idx < _len){
			if(!_node[idx])
				break;
			idx++;
		}

		return idx;
	}

	/**
		@brief indice del nodo

		dato il nome del nodo ritorna il suo
		id

		@param name nome del nodo
		@return c indice (ID) del nodo
	*/
	const idtype indexof(const T name) const
	{
		for(int c = 0; c < _len; c++){
			if(_node[c] && _name[c] == name)
				return c;
		}

		return _len;
	}

	/**
		@brief trim degli array di supporto

		metodo di supporto al const_iterator.
		si occupa di eliminare fisicamente i
		nodi non attivi ricostruendo gli array
		di supporto
	*/
	void trim()
	{
		//controllu sull'operazione da fare
		if(TRIM_ENABLED == 0 || num_nodes() == 0 || _len == 0)
			return;

		bool trimmable = false;
		for(int c = 0; c < _len; c++){
			if(!_node[c])
				trimmable = true;
		}

		if(!trimmable){
			#ifndef NDEBUG
			std::cout << "graph non trimmabile" << std::endl;
			#endif

			return;
		}

		//nuova dimensione
		int new_len = num_nodes();

		//puntatori ai vecchi dati
		bool* node_temp = _node;
		T* name_temp = _name;
		bool** arch_temp = _arch;
		idtype len_temp = _len;

		//inizializzo nuovi array
		init_vars(new_len);

		//copio i vecchi dati
		int row = 0;
		int col = 0;
		for(int c = 0; c < len_temp; c++){
			col = 0;
			if(node_temp[c]){
				_node[row] = node_temp[c];
				_name[row] = name_temp[c];

				for(int d = 0; d < len_temp; d++){
					if(node_temp[d]){
						_arch[row][col] = arch_temp[c][d];
						col++;
					}
				}

				row++;
			}
		}

		//distruggo i vecchi dati
		destr_vars(name_temp,node_temp,arch_temp,len_temp);

		#ifndef NDEBUG
		std::cout << "eseguito trim array di supporto" << std::endl;
		#endif
	}

public:

	/**
		@brief costruttore nullo

		costruttore che inizializza la classe
		graph ad un valore nullo

		@post _len == 0
		@post _name == nullptr
		@post _node == nullptr
		@post _arch == nullptr
	*/
	graph() : _len(0), _name(nullptr), _node(nullptr), _arch(nullptr)
	{
		#ifndef NDEBUG
		std::cout << "inizializzato grafo vuoto" << std::endl;
		#endif
	}

	/**
		@brief costruttore singolo

		costruttore che inizializza la classe
		graph con un solo nodo

		@param name nome del nodo

		@post _len == id+1
	*/
	graph(T name) : _len(0), _name(nullptr), _node(nullptr), _arch(nullptr)
	{
		idtype id = first_free();
		init_vars(id+1);
		_name[id] = name;
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
	graph(const graph<T> &other) : _len(0), _name(nullptr), _node(nullptr), _arch(nullptr)
	{
		init_vars(other._len);

		for(idtype c = 0; c < _len; c++){
			_node[c] = other._node[c];
			_name[c] = other._name[c];
			for(idtype d = 0; d < _len; d++){
				_arch[c][d] = other._arch[c][d];
			}
		}

		trim();

		#ifndef NDEBUG
		std::cout << "inizializzato grafo tramite copia" << std::endl;
		#endif
	}

	/**
		@brief distruttore classe grafo
	*/
	~graph()
	{
		destr_vars(_name,_node,_arch,_len);
		_name = nullptr;
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

		@param name nome del nodo
		@return res risultato della verifica
	*/
	const bool exists(const T name) const
	{
		int id = indexof(name);

		if(id == _len){
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

		@param name1 nome nodo di partenza
		@param name2 nome nodo di arrivo
		@return res risultato della verifica
	*/
	const bool has_edge(T name1, T name2) const
	{
		if(exists(name1) && exists(name2)){
			idtype id1 = indexof(name1);
			idtype id2 = indexof(name2);

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
	const bool equals(const graph<T> &other) const
	{

		if(num_nodes() != other.num_nodes() || //stesso num di nodi
			num_arches() != other.num_arches()) // stesso num di archi
		{
			return false;
		}

		for(idtype c = 0; c < _len; c++){
			if(_node[c]){
				if(!other.exists(_name[c])) //stessi nodi
					return false;
			}

			for(idtype d = 0; d < _len; d++){
				if(_arch[c][d]){
					if(!other.has_edge(_name[c],_name[d])) // stessi archi
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
		nodo, se il nodo è già stato inizializzato
		lo setta a true, altrimenti crea un grafo
		ex novo della dimensione corretta e copia
		i dati del vecchio grafo

		@param name nome del nuovo nodo
	*/
	void add(T name)
	{
		if(exists(name)) //nodo già inserito
			throw logicexception("nodo gia inserito!", 4);

		idtype id = first_free();
		#ifndef NDEBUG
		std::cout << "ID LIBERO:" << id << std::endl;
		#endif

		if(_node == nullptr){ //graph vuoto

			init_vars(id+1); // inizializzo la classe
			_node[id] = true;
			_name[id] = name;

		} else if (id < _len) { //id già inizializzato

			_node[id] = true;
			_name[id] = name;

		} else { //id non ancora inizializzato

			bool* node_temp = _node;
			T* name_temp = _name;
			bool** arch_temp = _arch;
			idtype len_temp = _len;

			init_vars(id+1); // reinizializzo la classe
			_node[id] = true;
			_name[id] = name;

			//copio i vecchi dati sul nuovo grafo
			for(idtype c = 0; c < len_temp; c++){
				_node[c] = node_temp[c];
				_name[c] = name_temp[c];
				for(idtype d = 0; d < len_temp; d++){
					_arch[c][d] = arch_temp[c][d];
				}
			}

			//distruggo i vecchi dati
			destr_vars(name_temp,node_temp,arch_temp,len_temp);

			#ifndef NDEBUG
			std::cout << "copiati dati in nuovo grafo" << std::endl;
			#endif
		}

		#ifndef NDEBUG
		std::cout << "nodo aggiunto correttamente" << std::endl;
		#endif
	}

	/**
		@brief aggiunta di un arco

		la funzione crea un arco orientato tra i due
		nodi selezionati in ingresso

		@param name1 nome nodo di partenza
		@param name2 nome nodo di arrivo
	*/
	void add(T name1, T name2)
	{
		if(!exists(name1) || !exists(name2))
			throw logicexception("uno dei nodi specificati non esiste!", 2);

		idtype id1 = indexof(name1);
		idtype id2 = indexof(name2);

		if(_arch[id1][id2])
			throw logicexception("arco gia inserito!", 4);

		_arch[id1][id2] = true;

		#ifndef NDEBUG
		std::cout << "arco aggiunto correttamente" << std::endl;
		#endif
	}

	/**
		@brief rimozione di un nodo

		la funzione si occupa della rimozione di un
		nodo e degli archi associati, previo controllo
		della validità del nodo inserito come parametro

		@param name nome del nodo da rimuovere
	*/
	void remove(T name)
	{
		if(_node == nullptr) //grafo vuoto
			throw logicexception("grafo vuoto!", 1);
		if(!exists(name)) // nodo non presente
			throw logicexception("nodo non presente!", 3);

		idtype id = indexof(name);
		// elimino il nodo
		_node[id] = false;
		
		// elimino gli archi associati
		for(idtype c = 0; c < _len; c++){
			_arch[c][id] = false;
			_arch[id][c] = false;
		}

		trim();

		//se non ci sono più nodi elimino il grafo
		if(num_nodes() == 0){
			destr_vars(_name,_node,_arch,_len);
			_name = nullptr;
			_node = nullptr;
			_arch = nullptr;
			_len = 0;
		}

		#ifndef NDEBUG
		std::cout << "nodo eliminato correttamente" << std::endl;
		#endif
	}

	/**
		@brief rimozione di un arco

		la funzione rimuove l'arco orientato tra i due
		nodi selezionati in ingresso

		@param name1 nome nodo di partenza
		@param name2 nome nodo di arrivo
	*/
	void remove(T name1, T name2)
	{
		if(!exists(name1) || !exists(name2))
			throw logicexception("uno dei nodi specificati non esiste!", 2);

		idtype id1 = indexof(name1);
		idtype id2 = indexof(name2);

		if(!_arch[id1][id2])
			throw logicexception("arco non presente!", 3);

		_arch[id1][id2] = false;

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
		std::cout << "<name,id>: ";
		for(idtype c = 0; c < _len; c++){
			if(_node[c])
				std::cout << "<" << _name[c] << "," << c << ">, ";
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

		trim();

		#ifndef NDEBUG
		std::cout << "graph swapped" << std::endl;
		#endif

		return *this;
	}

	class const_iterator {

		const T *ptr_name;

	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

	
		const_iterator() : ptr_name(nullptr) {}
		
		const_iterator(const const_iterator &other) : ptr_name(other.ptr_name) {}

		const_iterator& operator=(const const_iterator &other)
		{
			ptr_name = other.ptr_name;
			return *this;
		}

		~const_iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const
		{
			return *ptr_name;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const
		{
			return ptr_name;
		}
		
		// Operatore di iterazione post-incremento
		const_iterator operator++(int)
		{
			const_iterator tmp(this);
			ptr_name++;
			return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++()
		{
			ptr_name++;
			return *this;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const
		{
			return (ptr_name == other.ptr_name);
		}
		
		// Diversita'
		bool operator!=(const const_iterator &other) const
		{
			return (ptr_name != other.ptr_name);
		}

	private:
		//Dati membro
		friend class graph;

		// Costruttore privato di inizializzazione usato dalla classe container
		const_iterator(const T* nm) : ptr_name(nm) {}
		
	}; // classe const_iterator

	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const
	{
		return const_iterator(_name);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const
	{
		return const_iterator(_name+_len);
	}
};

#endif
