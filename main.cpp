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
}

int main()
{
	unsigned int length = 10;

	//ripetuti elementi in index 2-3 e 0-7
	char arr_char[length] = {'a', 'b', 'c', 'c', 'd', 'e', 'f', 'a', 'g', 'o', 'z'};
	custom arr_custom[length] = {{"mario", "lezzi"}, {"mauro","garli"}, {"giacomo","lundini"}, {"giacomo", "lundini"},
								{"luigi","garli"}, {"luigi","vincenzi"}, {"filippo", "gurlomi"}, {"mario","lezzi"},
								{"mario","gastelletti"},{"pedro","hernandez"}};

	test_constructors<char>(arr_char,length);
	test_constructors<custom>(arr_custom,length);

	test_add_remove<char>(arr_char,length);
	test_add_remove<custom>(arr_custom,length);

	return 0;
}
