/*
	Resmini Daniele Andrea - MAT: 830446
	Progetto C++ - GRAPH
*/

#include <iostream>
#include <cassert>
#include "graph.h"

#define LENGTH 10
#define LENGTH_2 5

//tipo di dato custom
typedef struct an{
	std::string nome;
	std::string cognome;
} custom;

//overload operatore stream output per custom
std::ostream& operator<<(std::ostream &os, const custom &cus) {
	os << "{";
	os << cus.nome << ",";
	os << cus.cognome;
	os << "}";

	return os;
}

//funtore comparazione tra double
struct compare_double{

    bool operator()(double sx, double dx) const {
        return sx == dx;
    }

};

//funtore comparazione tra char
struct compare_char{

    bool operator()(char sx, char dx) const {
        return sx == dx;
    }

};

//funtore comparazione tra tipi custom
struct compare_custom{

    bool operator()(custom sx, custom dx) const {
    bool cond1 = sx.nome.compare(dx.nome) == 0;
    bool cond2 = sx.cognome.compare(dx.cognome) == 0;

        return cond1 && cond2;
    }

};

template<typename U, typename Funct>
void test_constructors(const U arr[])
{
	//costruttore vuoto
	graph<U,Funct> m1;
	assert(m1.num_nodes() == 0);

	//costruttore 1 elemento
	graph<U,Funct> m2(arr[0]);
	assert(m2.num_nodes() == 1);

	//costruttore copia
	graph<U,Funct> m3(m2);
	assert(m3.equals(m2));
}

template<typename U, typename Funct>
void test_add_remove(const U arr[])
{
	graph<U,Funct> m1;
	unsigned int len;

	//primo inserimento
	m1.add(arr[0]);

	//nodo già inserito
	try{
		m1.add(arr[0]);
		assert(false);
	} catch(graphexception e){
		std::cout << e.what() << std::endl;
	}

	//altri inserimenti
	m1.add(arr[1]);
	m1.add(arr[2]);
	m1.add(arr[4]);
	m1.add(arr[5]);
	m1.add(arr[6]);
	m1.add(arr[8]);

	len = m1.num_nodes(); //salvo lunghezza array

	//eliminazione corretta
	m1.remove(arr[4]);

	//nodo già rimosso
	try{
		m1.remove(arr[4]);
		assert(false);
	} catch(graphexception e){
		std::cout << e.what() << std::endl;
	}

	m1.add(arr[9]);

	assert(m1.num_nodes() == len);

	//aggiungo arco correttamente
	m1.add(arr[2],arr[9]);

	//arco già attivato
	try{
		m1.add(arr[2],arr[9]);
		assert(false);
	} catch(graphexception e){
		std::cout << e.what() << std::endl;
	}

	//nodo non presente
	try{
		m1.add(arr[2],arr[4]);
		assert(false);
	} catch(graphexception e){
		std::cout << e.what() << std::endl;
	}

	//rimuovo l'arco correttamente
	m1.remove(arr[2],arr[9]);

	//arco già rimosso
	try{
		m1.remove(arr[2],arr[9]);
		assert(false);
	} catch(graphexception e){
		std::cout << e.what() << std::endl;
	}

	//arco non presente
	try{
		m1.remove(arr[2],arr[4]);
		assert(false);
	} catch(graphexception e){
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
	assert(m1.num_nodes() == 0);
}

template<typename U, typename Funct>
void test_equals(const U arr[])
{
	graph<U,Funct> g1;
	g1.add(arr[0]);
	g1.add(arr[1]);
	g1.add(arr[2]);
	g1.add(arr[4]);
	g1.add(arr[5]);
	g1.add(arr[1],arr[4]);
	g1.add(arr[2],arr[2]);

	graph<U,Funct> g2;
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

template<typename U, typename Funct>
void test_utils(const U arr[])
{
	//grafo vuoto
	graph<U,Funct> g1;

	assert(!g1.exists(arr[0]));
	assert(!g1.has_edge(arr[0],arr[1]));
	assert(g1.num_nodes() == 0);
	assert(g1.num_arches() == 0);

	//grafo 1 elemento
	graph<U,Funct> g2(arr[0]);

	assert(g2.exists(arr[0]));
	assert(!g2.exists(arr[1]));
	assert(!g2.has_edge(arr[0],arr[0]));
	assert(g2.num_nodes() == 1);
	assert(g2.num_arches() == 0);

	g2.add(arr[0],arr[0]);

	assert(g2.has_edge(arr[0],arr[0]));
	assert(g2.num_arches() == 1);

	//grafo con diversi elementi
    	g2.add(arr[1]);
	g2.add(arr[2]);
	g2.add(arr[4]);
	g2.add(arr[0],arr[4]);

	assert(g2.exists(arr[0]));
	assert(g2.exists(arr[1]));
	assert(g2.num_nodes() == 4);
	assert(g2.num_arches() == 2);

    g2.add(arr[1],arr[4]);
    g2.add(arr[2],arr[4]);
    g2.add(arr[4],arr[2]);
    g2.add(arr[2],arr[0]);

	//test print visuale
	g2.print();
}

template<typename U, typename Funct>
void test_operators(const U arr[])
{
	//grafo vuoto, not equals
	graph<U,Funct> g1;
	graph<U,Funct> g2(arr[1]);

	assert(!g1.equals(g2));

	//grafo 1 elemento, equals
	graph<U,Funct> g3(arr[0]);
	graph<U,Funct> g4 = g3;

	assert(g3.equals(g4));

	//grafo con diversi elementi, equals
	graph<U,Funct> g5(arr[0]);
	graph<U,Funct> g6(arr[5]);
	g5.add(arr[1]);
	g5.add(arr[2]);
	g5.add(arr[4]);
	g5.add(arr[2],arr[4]);
	g5.add(arr[0],arr[0]);
	g6 = g5;

	assert(g5.equals(g6));

	//operator<< test visuale
	std::cout << g6 << std::endl;
}

template<typename U, typename Funct>
void test_iterators(const U arr[], const U arr_final[])
{
	graph<U,Funct> g1;

	//riempio il grafo
	for(unsigned int c = 0; c < LENGTH; c++){
		try{
			g1.add(arr[c]);
		} catch (graphexception e) {}
	}

	//rimuovo alcuni nodi
	g1.remove(arr[0]);
	g1.remove(arr[4]);
	g1.remove(arr[9]);

	//test iteratore. gli elementi ritornati dall
	//iteratore devono essere gli stessi del secondo
	//array passato in ingresso
	typename graph<U,Funct>::const_iterator it1, ite1;
	unsigned int index = 0;
    	Funct comp;

	for(it1 = g1.begin(), ite1 = g1.end(); it1 != ite1; ++it1){
		std::cout << *it1 << " <--> " << arr_final[index] << std::endl;
		assert(comp(*it1, arr_final[index]));
		index++;
		assert(index <= LENGTH_2);
	}
	assert(index == g1.num_nodes());
	std::cout << std::endl;
}

int main()
{

	//ripetuti elementi in index 2-3 e 0-7
	double arr_double[LENGTH] = {1.2, 2.4, 5.1, 5.1, 3.2, 8.5, 4.4, 1.2, 9.6, 2.6};
	char arr_char[LENGTH] = {'a', 'b', 'c', 'c', 'd', 'e', 'f', 'a', 'g', 'o'};
	custom arr_custom[LENGTH] = {{"mario", "lezzi"}, {"mauro","garli"}, {"giacomo","lundini"}, {"giacomo", "lundini"},
				{"luigi","garli"}, {"luigi","vincenzi"}, {"filippo", "gurlomi"}, {"mario","lezzi"},
				{"mario","gastelletti"},{"pedro","hernandez"}};

	std::cout << "----->TEST COSTRUTTORI<-----" << std::endl;
	test_constructors<char,compare_char>(arr_char);
	test_constructors<custom,compare_custom>(arr_custom);
	test_constructors<double,compare_double>(arr_double);

	std::cout << "----->TEST ADD/REMOVE<-----" << std::endl;
	test_add_remove<char,compare_char>(arr_char);
	test_add_remove<custom,compare_custom>(arr_custom);
	test_add_remove<double,compare_double>(arr_double);

	std::cout << "----->TEST EQUALS<-----" << std::endl;
	test_equals<char,compare_char>(arr_char);
	test_equals<custom,compare_custom>(arr_custom);
	test_equals<double,compare_double>(arr_double);

	std::cout << "----->TEST UTILS<-----" << std::endl;
	test_utils<char,compare_char>(arr_char);
	test_utils<custom,compare_custom>(arr_custom);
	test_utils<double,compare_double>(arr_double);

	std::cout << "----->TEST OPERATORS<-----" << std::endl;
	test_operators<char,compare_char>(arr_char);
	test_operators<custom,compare_custom>(arr_custom);
	test_operators<double,compare_double>(arr_double);

	//array modificati per test iteratori
	double arr_double_final[LENGTH_2] = {2.4, 5.1, 8.5, 4.4, 9.6};
	char arr_char_final[LENGTH_2] = {'b', 'c', 'e', 'f', 'g'};
	custom arr_custom_final[LENGTH_2] = {{"mauro","garli"}, {"giacomo","lundini"},
					{"luigi","vincenzi"}, {"filippo", "gurlomi"},
					{"mario","gastelletti"}};

	std::cout << "----->TEST ITERATORS<-----" << std::endl;
	test_iterators<char,compare_char>(arr_char,arr_char_final);
	test_iterators<custom,compare_custom>(arr_custom,arr_custom_final);
	test_iterators<double,compare_double>(arr_double,arr_double_final);

	std::cout << ">>>>>>TEST COMPLETATI<<<<<<" << std::endl;
	return 0;
}
