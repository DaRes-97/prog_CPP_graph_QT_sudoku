# PROGETTO C++/QT

Resmini Daniele Andrea	MAT: 830446	

[d.resmini2@campus.unimib.it](mailto:d.resmini2@campus.unimib.it)

## PROGETTO C++ - GRAPH

il grafo è stato implementato tramite **array dinamici**:

​		`T* _name[]`	contenitore dei nomi dei nodi (identificativi)

​		`bool** _arch[]`	contenitore degli archi attivi (matrice di adiacenza)

​		`unsigned int len`	indicatore dimensione degli array

### COSTRUTTORI

`graph(T name)`:	il costruttore principale prende in ingresso un elemento di tipo *T* (nome del nodo) ed 								 inizializza gli array a dimensione singola, inserendo tale elemento

- la cella `_name[ID]` conterrà il dato T all'indice *ID*. L'indice *ID* funziona anche da identificatore interno, per quanto riguarda gli archi

- i nodi vengono aggiunti tramite la funzione `add(T name)`, e rimossi tramite `remove(T name)`


### AGGIUNTA/RIMOZIONE DI NODI

inizialmente, l'array viene riempito in modo sequenziale (`add(T name)`), aumentando di volta la dimensione degli array di supporto e copiando i dati precedenti:

|    ID    |   0   |   1   |   2   |   3   |   4   |
| :------: | :---: | :---: | :---: | :---: | :---: |
| **name** | name1 | name2 | name3 | name4 | name5 |

supponiamo ora che voglia rimuovere l'elemento *name3*, allora invocherò la funzione `remove(name3)`

- tramite la funzione interna `indexof(T name)`, il programma risale all'*ID* relativo alla variabile *name* ricrea gli array di supporto escludendo la cella relativa

|    ID    |   0   |   1   |     2     |   3   |
| :------: | :---: | :---: | :-------: | :---: |
| **name** | name1 | name2 |   name4   | name5 |

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

➔ `indexof(name2) == 1`, `indexof(name4) == 3`


| 🠗ID1/ID2🠖 |   0   |   1   |   2   |    3     |   4   |
| :-------: | :---: | :---: | :---: | :------: | :---: |
|   **0**   | false | false | false |  false   | false |
|   **1**   | false | false | false | **true** | false |
|   **2**   | false | false | false |  false   | false |
|   **3**   | false | false | false |  false   | false |
|   **4**   | false | false | false |  false   | false |

➔ `arch[1][3] = true;`

stesso procedimento per la rimozione, settando la casella appropriata a *false*

- gli array mantengono una dimensione coerente durante tutto il ciclo del programma
- la rimozione di un nodo comporta anche l'**eliminazione di tutti gli archi entranti ed uscenti da esso**

### EXISTS/HAS_EDGE

come da specifica:

​	`exists(T name)`: ritorna *true* se il nodo esiste (il nome è presente nell'array *_name[]*), *false* altrimenti

​	`has_edge(T src, T dst)`: ritorna *true* se esiste un arco che collega *src* con *dst*, previa verifica 													 dell'esistenza dei due nodi, altrimenti ritorna *false*

### NUM_NODI/NUM_ARCHI

i metodi `num_nodi()` e `num_archi()` ritornano rispettivamente il numero di nodi e di archi presenti nel grafo, andando a contare il numero di celle settate a *true* nei relativi array di supporto

### EQUALS

il metodo `equals(graph<T> other)`verifica l'uguaglianza del grafo con *other*, verificando che

- i due grafi contengano gli stessi nomi
- tali nomi siano collegati con gli stessi archi

Ai fini del controllo, non conta l'ordine dei nomi delle celle

### STAMPA DEL GRAFO

è possibile visionare lo stato del grafo tramite il metodo `print()`, che stampa nell'ordine:

- coppia dei valori *<nome,ID>* 
- matrice di adiacenza

un esempio di output:

![](https://drive.google.com/uc?id=12O8ewNtKoqiQG0Ahckv4f5ML-5syaEi-)

### ITERATORI

come da specifica, è stato implementato un *const_iterator* di tipo *forward* che itera sull'insieme dei nomi dei nodi, utilizzando come puntatore:

​	`const T *ptr_name`: puntatore all'array dei nomi dei nodi

## PROGETTO QT - SUDOKU

Il gioco è stato implementato mediante una griglia 9x9 di elementi `QLineEdit`, che costituiscono le caselle del Sudoku, e da una serie di pulsanti che consentono di interagire con le funzionalità del programma.

All'apertura dell'eseguibile viene settata la griglia di gioco e vengono generati *n* valori casuali in altrettante caselle random

La schermata iniziale si presenta in questo modo:

![](https://drive.google.com/uc?id=1ml0DOFokMlxbVDfNr6TeO7v2Q7opI_tb)



- **NOTA:** per variare il numero di celle riempite automaticamente, si deve modificare il valore della costante `LEVEL` nel file *sudoku.cpp*. Il valore è settato a <u>15</u> di default

------

A questo punto, l'utente può iniziare ad inserire i numeri nelle caselle attive, e una volta finito, cliccando sul tasto **SOLVE**, si attiva il sistema di risoluzione.

- se la griglia è già stata riempita, il sistema controlla la **correttezza dei valori immessi** ( non deve essere presente nessun duplicato)
- altrimenti, **inserisce i valori in maniera automatica** ove compatibile con il rispetto delle regole del gioco

Se la griglia finale risulta **corretta**, appare un messaggio della riuscita dell'operazione e si attivano le frecce **<** e **>** che consentono di ripercorrere i diversi stadi della risoluzione

![](https://drive.google.com/uc?id=1iPhUp_rd6dnk2Oq-mZsNmmVKitUT8uF8)



![](https://drive.google.com/uc?id=1gj3kUQ5cBmyTAdk145euWexsRBuy7RaA)



In caso di **errori** nella risoluzione, il sistema si blocca e vengono evidenziati i settori di gioco che presentano duplicati:

![](https://drive.google.com/uc?id=1p6BoEZhLEGVHVyPVxHOmwgs5kaDUTZ2v)



Premendo il tasto **RESET** il gioco ritorna allo stato inziale.

------

### IMPLEMENTAZIONE INTERNA

- gli stati di risoluzione intermedi sono stati implementati tramite due **QStack**, `prev` e `next`, che vengono riempite e svuotate alternativamente
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

- **NOTA:** per alcune configurazioni di gioco, tale metodo potrebbe portare a tempistiche di risoluzione eccessive. Per questioni di semplicità del codice, non sono stati implementati ulteriori controlli in grado di saltare la maggior parte dei rami di *backtrack* inutili, che portano all'aumento del tempo di risoluzione.