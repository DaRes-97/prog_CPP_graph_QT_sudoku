# PROGETTO C++/QT

Resmini Daniele Andrea	MAT: 830446	

[d.resmini2@campus.unimib.it]: d.resmini2@campus.unimib.it	"mail di ateneo"

## PROGETTO C++ - GRAPH

il grafo è stato implementato tramite **array dinamici**:

​		`T* _name[]`	contenitore dei nomi dei nodi (identificativi esterni)

​		`bool* _node[]`	contenitore dello stato di attivazione dei nodi

​		`bool** _arch[]`	contenitore degli archi attivi (matrice di adiacenza)

​		`unsigned int len`	indicatore dimensione degli array

### COSTRUTTORI

`graph(T name)`:	il costruttore principale prende in ingresso un elemento di tipo *T* (nome del nodo) ed 								 inizializza gli array a dimensione singola, inserendo tale elemento

- la cella `_name[ID]` conterrà il dato T all'indice *ID*. L'indice *ID* funziona anche da identificatore interno, difatti la cella dell'array `_node[ID]` sarà settata a *true*

- i nodi vengono aggiunti tramite la funzione `add(T name)`, e rimossi tramite `remove(T name)`


### AGGIUNTA/RIMOZIONE DI NODI

inizialmente, l'array viene riempito in modo sequenziale, aumentando di volta la dimensione degli array di supporto e copiando i dati precedenti:

|    ID    |   0   |   1   |   2   |   3   |   4   |
| :------: | :---: | :---: | :---: | :---: | :---: |
| **name** | name1 | name2 | name3 | name4 | name5 |
| **node** | true  | true  | true  | true  | true  |

supponiamo ora che voglia rimuovere l'elemento *name3*, allora invocherò la funzione `remove(name3)`

- tramite la funzione interna `indexof(T name)`, il programma risale all'*ID* relativo alla variabile *name* e setta la cella relativa al valore *false*

|    ID    |   0   |   1   |     2     |   3   |   4   |
| :------: | :---: | :---: | :-------: | :---: | :---: |
| **name** | name1 | name2 |   name3   | name4 | name5 |
| **node** | true  | true  | **false** | true  | true  |

- nel momento in cui dovrò aggiungere un altro nodo, invece di aumentare di nuovo la dimensione dell'array, esso occuperà la prima cella disponibile, in questo caso *ID=2*, e il valore *name3* verrà sovrascritto

### AGGIUNTA/RIMOZIONE DI ARCHI

gli archi che connettono due nodi sono rappresentati tramite la matrice di adiacenza `_arch[][]`

inizialmente, la matrice si presenta in questo modo:

| 🠗ID1/ID2🠖 |   0   |   1   |   2   |   3   |   4   |
| :-------: | :---: | :---: | :---: | :---: | :---: |
|   **0**   | false | false | false | false | false |
|   **1**   | false | false | false | false | false |
|   **2**   | false | false | false | false | false |
|   **3**   | false | false | false | false | false |
|   **4**   | false | false | false | false | false |

tramite i metodi `add(T src, T dst)` e `remove(T src, T dst)`, vengono settati gli archi orientati tra i due nodi specificati, in cui *src* è il nome del nodo di partenza e *dst* è il nome del nodo di arrivo

anche qui la funzione `indexof(T name)` si occupa di ritornare l'*ID* dei due nodi dato il loro nome, previa verifica di esistenza degli stessi

per esempio, se volessi settare un arco tra *name2* e *name4*:


|    ID    |   0   |   1   |     2     |   3   |   4   |
| :------: | :---: | :---: | :-------: | :---: | :---: |
| **name** | name1 | name2 |   name3   | name4 | name5 |
| **node** | true  | true  | **false** | true  | true  |

`indexof(name2) == 1`, `indexof(name4) == 3`


| 🠗ID1/ID2🠖 |   0   |   1   |   2   |    3     |   4   |
| :-------: | :---: | :---: | :---: | :------: | :---: |
|   **0**   | false | false | false |  false   | false |
|   **1**   | false | false | false | **true** | false |
|   **2**   | false | false | false |  false   | false |
|   **3**   | false | false | false |  false   | false |
|   **4**   | false | false | false |  false   | false |

`arch[2][4] = true;`

stesso procedimento per la rimozione, settando la casella appropriata a *false*

- tutti gli array mantengono la stessa dimensione durante tutto il ciclo del programma
- la rimozione di un nodo comporta anche l'eliminazione di tutti gli archi entranti ed uscenti da esso
- nel momento in cui tutti i nodi dell'array sono settati *false*, gli array vengono **deinizializzati**

### EXISTS/HAS_EDGE

come da specifica:

​	`exists(T name)`: ritorna *true* se il nodo esiste (il nome è presente nell'array e il relativo *ID* è settato a 									*true*), *false* altrimenti

​	`has_edge(T src, T dst)`: ritorna *true* se esiste un arco che collega *src* con *dst*, previa verifica 													 dell'esistenza dei due nodi, altrimenti ritorna *false*

### NUM_NODI/NUM_ARCHI

i metodi `num_nodi()` e `num_archi()` ritornano rispettivamente il numero di nodi e di archi presenti nel grafo, andando a contare il numero di celle settate a *true* nei relativi array di supporto

### EQUALS

il metodo `equals(graph<T> other)`verifica l'uguaglianza del grafo con *other*, verificando che

- i due grafi contengano gli stessi nomi
- tali nomi siano collegati con gli stessi archi

Ai fini del controllo, non conta l'ordine dei nomi delle celle, ne l'*ID* a cui sono collegati

### STAMPA DEL GRAFO

è possibile visionare lo stato del grafo tramite il metodo `print()`, che stampa nell'ordine:

- coppia dei valori *<nome,ID>* dei soli nodi attivi
- matrice di adiacenza

un esempio di output:

![sample_graph_print](.\sample_graph_print.png)

### ITERATORI

come da specifica, è stato implementato un *const_iterator* di tipo *forward* che itera sull'insieme dei nomi dei nodi, utilizzando come puntatori

​	`const T *ptr_name`: puntatore all'array dei nomi dei nodi

​	`const bool *ptr_node`: puntatore all'array dello stato di attivazione dei nodi

a causa del tipo di implementazione, l'iteratore è in grado di fare un <u>trim</u> sul puntatore di partenza e di arrivo, saltando i nodi settati a *false* e puntando rispettivamente al primo e all'ultimo nodo settato a *true*

```c++
	const_iterator begin() const
	{
		T* ptr_name = _name;
		bool* ptr_node = _node;

		while(*ptr_node == false){
			ptr_name++;
			ptr_node++;
		}

		return const_iterator(ptr_name,ptr_node);
	}
```
```c++
	const_iterator end() const
	{
		T* ptr_name = _name+_len-1;
		bool* ptr_node = _node+_len-1;

		while(*ptr_node == false){
			ptr_node--;
			ptr_name--;
		}


		return const_iterator(ptr_name+1,ptr_node+1);
	}
```
non è però in grado di attuare una logica di incremento del puntatore che <u>salti i nodi settati a false</u> senza infrangere una di queste due condizioni:

1. <u>Non disponga di informazioni sulle variabili contenute nella classe contenitore</u>, tranne i puntatori con cui è inizializzato l'iteratore (non ha informazioni sulla lunghezza degli array)
2. <u>Non esegua accessi in memoria non consentiti</u> (superamento dei limiti di lunghezza dell'array per quanto riguarda la lettura delle celle)

pertanto viene attuata una politica di incremento <u>basilare</u>:

```c++
	void increment_ptr()
	{
		ptr_name++;
		ptr_node++;
	}
```
