#include <iostream>
#include <cassert>
#include "graph.h"

void test_constructors()
{
	graph g1; //test costrut. vuoto
	graph g2(7); //test costrut. 1 elem.
	assert(g2.len() == 8);
	graph g3(g2); //test costrut. copia
	assert(g3.len() == 8);

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

void test_add_arch()
{
	//aggiungo arco da grafo vuoto
	graph g1;
	try{
		g1.add(7,5);
		assert(false);
	} catch(logicexception e){
		std::cout << e.what() << std::endl;
	}

	//aggiungo arco correttamente
	graph g2(1);
	g2.add(9);
	g2.add(5);
	g2.add(9,5);
	assert(g2.has_edge(9,5));
	assert(!g2.has_edge(5,9));
	assert(!g2.has_edge(1,2));

	//aggiungo arco già inserito
	try{
		g2.add(9,5);
		assert(false);
	} catch (logicexception &e){
		std::cout << e.what() << std::endl;
	}
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

void test_remove_arch()
{
	//rimozione da grafo vuoto
	graph g1;
	try{
		g1.remove(5,4);
		assert(false);
	} catch (logicexception e){
		std::cout << e.what() << std::endl;
	}

	//rimozione eseguita correttamente
	graph g2(1);
	g2.add(9);
	g2.add(5);
	g2.add(9,5);
	assert(g2.has_edge(9,5));
	g2.remove(9,5);
	assert(!g2.has_edge(9,5));
	assert(!g2.has_edge(5,9));
	assert(!g2.has_edge(1,2));

	//rimozione arco già rimosso
	try{
		g2.remove(9,5);
		assert(false);
	} catch (logicexception e){
		std::cout << e.what() << std::endl;
	}
}

void test_count_nodes_arches()
{
	//conteggio nodi e archi
	graph g1;
	assert(g1.num_nodes() == 0);
	assert(g1.num_arches() == 0);

	g1.add(9);
	assert(g1.num_nodes() == 1);
	assert(g1.num_arches() == 0);

	g1.add(4);
	assert(g1.num_nodes() == 2);
	assert(g1.num_arches() == 0);

	g1.add(9,4);
	assert(g1.num_nodes() == 2);
	assert(g1.num_arches() == 1);

	g1.add(4,9);
	assert(g1.num_nodes() == 2);
	assert(g1.num_arches() == 2);

	g1.add(4,4);
	assert(g1.num_nodes() == 2);
	assert(g1.num_arches() == 3);

	g1.print();
}

void test_operators()
{
	//operator=
	graph g1;
	graph g2(5);
	graph g3(7);
	g1 = g3;
	//DA IMPLEMENTARE VERIFICA UGUAGLIANZA/DISEGUAGLIANZA TRA DUE GRAFI
}

int main()
{

	test_constructors();
	test_add_node();
	test_remove_node();
	test_add_arch();
	test_remove_arch();
	test_count_nodes_arches();

	return 0;
}