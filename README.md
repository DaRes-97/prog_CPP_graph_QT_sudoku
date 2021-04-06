# PROGETTO C++/QT

Resmini Daniele Andrea	-	MAT: 830446	

[d.resmini2@campus.unimib.it](mailto:d.resmini2@campus.unimib.it)

## PROGETTO C++ - GRAPH

Il grafo è stato implementato tramite **array dinamici**:

​		`T* _node[]`	contenitore degli identificativi dei nodi

​		`bool** _arch[]`	contenitore degli archi attivi (matrice di adiacenza)

​		`unsigned int _len`	indicatore dimensione degli array

→ con `T` dato generico

### COSTRUTTORI

`graph(T node)`:	il costruttore principale prende in ingresso un elemento di tipo `T`  ed inizializza gli array a dimensione unitaria, inserendo tale elemento.

- la cella `_node[IDX]` conterrà il nodo di tipo `T` all'indice *IDX*. L'indice *IDX* funziona anche da identificatore interno, per quanto riguarda gli archi

### AGGIUNTA/RIMOZIONE DI NODI

L'array viene riempito in modo sequenziale, creando di volta in volta degli array di supporto di dimensioni maggiori e copiando i dati dagli array precedenti

|   IDX    |   0   |   1   |   2   |   3   |   4   |
| :------: | :---: | :---: | :---: | :---: | :---: |
| **node** | name1 | name2 | name3 | name4 | name5 |

supponiamo ora che voglia rimuovere l'elemento *name3*, allora invocherò la funzione `remove(name3)`

- tramite la funzione interna `index_of(T node)`, il programma risale all'*IDX* relativo alla variabile *name3* e ricrea gli array di supporto escludendo la cella relativa

|   IDX    |   0   |   1   |   2   |   3   |
| :------: | :---: | :---: | :---: | :---: |
| **node** | name1 | name2 | name4 | name5 |

### AGGIUNTA/RIMOZIONE DI ARCHI

Gli archi che connettono due nodi sono rappresentati tramite la matrice di adiacenza `_arch[][]`

Inizialmente, la matrice si presenta in questo modo:

| 🠗IDX1/IDX2🠖 |   0   |   1   |   2   |   3   |
| :---------: | :---: | :---: | :---: | :---: |
|    **0**    | false | false | false | false |
|    **1**    | false | false | false | false |
|    **2**    | false | false | false | false |
|    **3**    | false | false | false | false |

tramite i metodi `add(T src, T dst)` e `remove(T src, T dst)`, vengono settati gli archi orientati tra i due nodi specificati, in cui *src* è il nodo di partenza e *dst* è il nodo di arrivo.

per esempio, se volessi settare un arco tra *name2* e *name4*:


|   IDX    |   0   |   1   |   2   |   3   |
| :------: | :---: | :---: | :---: | :---: |
| **node** | name1 | name2 | name4 | name5 |

➔ `index_of(name2) == 1`, `index_of(name4) == 2`


| 🠗IDX1/IDX2🠖 |   0   |   1   |    2     |   3   |
| :---------: | :---: | :---: | :------: | :---: |
|    **0**    | false | false |  false   | false |
|    **1**    | false | false | **true** | false |
|    **2**    | false | false |  false   | false |
|    **3**    | false | false |  false   | false |

➔ `_arch[1][2] = true;`

stesso procedimento per la rimozione, settando la casella appropriata a *false*

- gli array mantengono una dimensione coerente durante tutto il ciclo del programma
- la rimozione di un nodo comporta anche l'**eliminazione di tutti gli archi entranti ed uscenti da esso**

### ECCEZIONI

Durante l'aggiunta o la rimozione di nodi, vengono generate delle eccezioni nei seguenti casi:

- si vuole aggiungere un **nodo/arco già esistente** (CODICE 4)
- si vuole eliminare un **nodo/arco non presente** (CODICE 3)
- si vuole eliminare un nodo quando il **grafo è vuoto** (CODICE 1)
- si vuole aggiungere un arco tra **uno o due nodi non inizializzati** (CODICE 2)

In tal caso vengono generate delle *logicexception* della gerarchia standard delle eccezioni, con i codici sopra esposti

### EXISTS/HAS_EDGE

come da specifica:

​	`exists(T node)`: ritorna *true* se il nodo esiste (il nome è presente nell'array *_node[]*), *false* altrimenti

​	`has_edge(T src, T dst)`: ritorna *true* se esiste un arco che collega *src* con *dst*, previa verifica dell'esistenza dei due nodi, altrimenti ritorna *false*

### NUM_NODI/NUM_ARCHI

i metodi `num_nodi()` e `num_archi()` ritornano rispettivamente il numero di nodi e di archi presenti nel grafo, andando a contare rispettivamente il numero di celle dell'array e il numero di celle settate a *true* della matrice di adiacenza

### EQUALS

il metodo `equals(graph<T,F> other)`verifica l'uguaglianza del grafo con `other`, verificando che

- i due grafi contengano gli stessi nodi
- tali nodi siano collegati con gli stessi archi

Ai fini del controllo, **non conta l'ordine** dei nomi nelle celle degli array

### STAMPA DEL GRAFO

è possibile visionare lo stato del grafo tramite il metodo `print()`, che stampa nell'ordine:

- coppia dei valori *<node,IDX>* 
- matrice di adiacenza

un esempio di output:

![](https://drive.google.com/uc?id=1VQ8vwBJyTRUp3y2j0IhwNj9wKjxM6eMq)

corrispondente al grafo:

![](https://drive.google.com/uc?id=1DtdD6M4YK_C1kpGI7vdGF9v4_uNLDeqd)

### ITERATORI

come da specifica, è stato implementato un `const_iterator` di tipo *forward* che itera sull'insieme degli identificativi dei nodi, utilizzando come puntatore:

​	`const T *ptr_node`: puntatore all'array degli identificativi dei nodi

## PROGETTO QT - SUDOKU

Il gioco è stato implementato mediante una griglia 9x9 di elementi `QLineEdit`, che costituiscono le caselle del Sudoku, e da una serie di pulsanti che consentono di interagire con le funzionalità del programma.

La schermata iniziale si presenta in questo modo:

![](https://drive.google.com/uc?id=1ml0DOFokMlxbVDfNr6TeO7v2Q7opI_tb)



A questo punto, l'utente può iniziare ad inserire i numeri nelle caselle, e una volta finito, cliccando sul tasto **SOLVE**, si attiva il sistema di risoluzione.

- se la griglia è già stata riempita completamente, il sistema controlla la **correttezza dei valori immessi** (non deve essere presente nessun duplicato)
- altrimenti, **inserisce i valori in maniera automatica** ove compatibile con il rispetto delle regole del gioco

Se la griglia finale risulta **corretta**, appare un messaggio della riuscita dell'operazione e si attivano le frecce **<** e **>** che consentono di ripercorrere i diversi stadi della risoluzione

![](https://drive.google.com/uc?id=1QtORPy9LSHyTdLxZcvz0C627nnLm0HrL)

![](https://drive.google.com/uc?id=1scReskIuvC2AlikUQO0gsJZ6pfy1t3YV)



Nel caso in cui il Sudoku **non fosse risolvibile**, il sistema si blocca e vengono evidenziati, se presenti, i settori di gioco che presentano duplicati:

![](https://drive.google.com/uc?id=1w_aMP_1I1m5pDJp139rX8hTI7JnOCqsC)



Premendo il tasto **RESET** il gioco ritorna allo stato inziale.

------

### IMPLEMENTAZIONE INTERNA

- gli stati di risoluzione intermedi sono stati implementati tramite due *QStack*, `prev_state` e `next_state`, che vengono riempite e svuotate alternativamente
- l'algoritmo di risoluzione automatica utilizza la tecnica del **backtracking**, di cui sotto:

```java
bool solve(configuration conf){
	
	//base case
	if(!choices)
		return has_duplicates(conf);

	for(all choices) {
		try choice c;

		//correct choice
		if(solve(conf with choice c))
			return true;

		//wrong choice
		unmake choice c;
	}

    //backtrack trigger
	return false;
}
```

- **NOTA:** per alcune configurazioni di gioco, tale metodo potrebbe portare a tempistiche di risoluzione eccessive.

## NOTE FINALI

Il progetto **C++** è stato testato sulle seguenti piattaforme:

- **Microsoft Windows 10** 64 bit, build: 19042.746
  - Compiler → g++ (MinGW.org GCC-6.3.0-1) 6.3.0
- **Ubuntu 20.04.2**, tramite WSL2
  - Compiler → g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
  - Memory check → valgrind-3.15.0

Il progetto **QT** è stato testato sulle seguenti piattaforme:

- **Microsoft Windows 10** 64 bit, build: 19042.746
  - Compiler → QT 5.15.2, MinGW-based
- **Ubuntu 20.04.2** 64 bit, tramite HYPER-V
  - Compiler → QT 5.12.8, (GCC 9.3.0, 64 bit)
  - Memory check → valgrind-3.15.0
