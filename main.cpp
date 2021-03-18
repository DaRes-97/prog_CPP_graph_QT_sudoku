#include <iostream>
#include <cassert>
#include "graph.h"

void test_constructors()
{
	graph g1; //test costrut. vuoto
	graph g2(7); //test costrut. 1 elem.
}

void test_add_node()
{
	//aggiungo nodo da grafo vuoto
	graph g1;
	g1.add(7);
	assert(g1.exists(7));
	assert(g1.len() == 8);

	// aggiungo nodo già presente
	graph g2(5);
	try{
		g2.add(5);
		assert(false);
	} catch(logicexception &e){
		std::cout << e.what() << std::endl;
	}

	// aggiungo nodo con ricostruzione grafo
	graph g3(3);
	g3.add(10);
	assert(g3.len() == 11);
	assert(g3.exists(3));
	assert(g3.exists(10));
}

void test_remove_node()
{
	graph g1;
	graph g2(7);
	graph g3(5);
	graph g4(5);

	// rimozione nodo da grafo vuoto
	try{
		g1.remove(7);
		assert(false);
	} catch(logicexception e){
		std::cout << e.what() << std::endl;
	}

	// rimozione nodo non esistente
	try{
		g2.remove(5);
		assert(false);
	} catch(logicexception e){
		std::cout << e.what() << std::endl;
	}

	// rimozione eseguita correttamente ed elim grafo
	g3.remove(5);
	assert(g3.len() == 0);

	//rimozione eseguita correttamente
	g4.add(3);
	g4.remove(5);
	assert(g4.len() == 6);
	assert(!g4.exists(5));
}

int main()
{

	test_constructors();
	test_add_node();
	test_remove_node();

	return 0;
}