#include <iostream>
#include <cassert>
#include "graph.h"
#include "customdata.h"

template<typename U>
void test_constructors(const U arr[], unsigned int length)
{
	//costruttore vuoto
	graph<U> m1;
	assert(m1.len() == 0);

	//costruttore 1 elemento
	graph<U> m2(arr[0]);
	assert(m2.len() == 1);

	//costruttore copia
	graph<U> m3(m2);
	assert(m3.equals(m2));
}

template<typename U>
void test_add_remove(const U arr[], unsigned int length)
{
	graph<U> m1;
	unsigned int len;

	//primo inserimento
	m1.add(arr[0]);

	//nodo già inserito
	try{
		m1.add(arr[0]);
		assert(false);
	} catch(logicexception e){
		std::cout << e.what() << std::endl;
	}

	//altri inserimenti
	m1.add(arr[1]);
	m1.add(arr[2]);
	m1.add(arr[4]);
	m1.add(arr[5]);
	m1.add(arr[6]);
	m1.add(arr[8]);

	//eliminazione corretta
	m1.remove(arr[4]);
	len = m1.len(); //salvo lunghezza array

	//nodo già rimosso
	try{
		m1.remove(arr[4]);
		assert(false);
	} catch(logicexception e){
		std::cout << e.what() << std::endl;
	}

	//rimpiazzo nodo
	m1.add(arr[9]);
	assert(m1.len() == len);	//il nuovo nodo va al posto di quello
								//rimosso precedentemente (len non
								//aumenta)

	//aggiungo arco correttamente
	m1.add(arr[2],arr[9]);

	//arco già attivato
	try{
		m1.add(arr[2],arr[9]);
		assert(false);
	} catch(logicexception e){
		std::cout << e.what() << std::endl;
	}

	//nodo non presente
	try{
		m1.add(arr[2],arr[4]);
		assert(false);
	} catch(logicexception e){
		std::cout << e.what() << std::endl;
	}

	//rimuovo l'arco correttamente
	m1.remove(arr[2],arr[9]);

	//arco già rimosso
	try{
		m1.remove(arr[2],arr[9]);
		assert(false);
	} catch(logicexception e){
		std::cout << e.what() << std::endl;
	}

	//nodo non presente
	try{
		m1.remove(arr[2],arr[4]);
		assert(false);
	} catch(logicexception e){
		std::cout << e.what() << std::endl;
	}

	//svuoto il graph
	m1.remove(arr[9]);
	m1.remove(arr[8]);
	m1.remove(arr[6]);
	m1.remove(arr[5]);
	m1.remove(arr[2]);
	m1.remove(arr[1]);
	m1.remove(arr[0]);
	assert(m1.len() == 0);
}

template<typename U>
void test_equals(const U arr[], unsigned int length)
{
	graph<U> g1;
	g1.add(arr[0]);
	g1.add(arr[1]);
	g1.add(arr[2]);
	g1.add(arr[4]);
	g1.add(arr[5]);
	g1.add(arr[1],arr[4]);
	g1.add(arr[2],arr[2]);

	graph<U> g2;
	g2.add(arr[4]);
	g2.add(arr[5]);
	g2.add(arr[2]);
	g2.add(arr[0]);
	g2.add(arr[1]);
	g2.add(arr[1],arr[4]);
	g2.add(arr[2],arr[2]);

	// test equals con ID diversi ma 
	// archi e nodi uguali
	assert(g1.equals(g2));

	g2.remove(arr[0]);
	g2.add(arr[9]);

	// test equals con len uguale ma
	// nodi diversi
	assert(!g1.equals(g2));

	g2.add(arr[6]);

	// test equals con len e nodi diversi
	assert(!g1.equals(g2));
}

template<typename U>
void test_utils(const U arr[], unsigned int length)
{
	//grafo vuoto
	graph<U> g1;

	assert(!g1.exists(arr[0]));
	assert(!g1.has_edge(arr[0],arr[1]));
	assert(g1.len() == 0);
	assert(g1.num_nodes() == 0);
	assert(g1.num_arches() == 0);

	//grafo 1 elemento
	graph<U> g2(arr[0]);

	assert(g2.exists(arr[0]));
	assert(!g2.exists(arr[1]));
	assert(!g2.has_edge(arr[0],arr[0]));
	assert(g2.len() == 1);
	assert(g2.num_nodes() == 1);
	assert(g2.num_arches() == 0);

	g2.add(arr[0],arr[0]);

	assert(g2.has_edge(arr[0],arr[0]));
	assert(g2.num_arches() == 1);

	//grafo con diversi elementi
	g2.add(arr[1]);
	g2.add(arr[2]);
	g2.add(arr[4]);
	g2.add(arr[2],arr[4]);

	assert(g2.exists(arr[0]));
	assert(g2.exists(arr[1]));
	assert(g2.len() == 4);
	assert(g2.num_nodes() == 4);
	assert(g2.num_arches() == 2);
}

template<typename U>
void test_operators(const U arr[], unsigned int length)
{
	//grafo vuoto
	graph<U> g1;
	graph<U> g2 = g1;

	assert(g1.equals(g2));

	//grafo 1 elemento
	graph<U> g3(arr[0]);
	graph<U> g4 = g3;

	assert(g3.equals(g4));

	//grafo con diversi elementi
	graph<U> g5(arr[0]);
	graph<U> g6(arr[5]);
	g5.add(arr[1]);
	g5.add(arr[2]);
	g5.add(arr[4]);
	g5.add(arr[2],arr[4]);
	g5.add(arr[0],arr[0]);
	g6 = g5;

	assert(g5.equals(g6));
}

int main()
{
	unsigned int length = 10;

	//ripetuti elementi in index 2-3 e 0-7
	char arr_char[length] = {'a', 'b', 'c', 'c', 'd', 'e', 'f', 'a', 'g', 'o', 'z'};
	custom arr_custom[length] = {{"mario", "lezzi"}, {"mauro","garli"}, {"giacomo","lundini"}, {"giacomo", "lundini"},
								{"luigi","garli"}, {"luigi","vincenzi"}, {"filippo", "gurlomi"}, {"mario","lezzi"},
								{"mario","gastelletti"},{"pedro","hernandez"}};

	std::cout << "----->TEST COSTRUTTORI<-----" << std::endl;
	test_constructors<char>(arr_char,length);
	test_constructors<custom>(arr_custom,length);

	std::cout << "----->TEST ADD/REMOVE<-----" << std::endl;
	test_add_remove<char>(arr_char,length);
	test_add_remove<custom>(arr_custom,length);

	std::cout << "----->TEST EQUALS<-----" << std::endl;
	test_equals<char>(arr_char,length);
	test_equals<custom>(arr_custom,length);

	std::cout << "----->TEST UTILS<-----" << std::endl;
	test_utils<char>(arr_char,length);
	test_utils<custom>(arr_custom,length);

	std::cout << "----->TEST OPERATORS<-----" << std::endl;
	test_operators<char>(arr_char,length);
	test_operators<custom>(arr_custom,length);

	std::cout << ">>>>>>TEST COMPLETATI<<<<<<" << std::endl;
	return 0;
}
