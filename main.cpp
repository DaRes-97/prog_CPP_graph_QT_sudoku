#include <iostream>
#include <cassert>
#include "graph.h"

int main()
{
	graph<char> m1;
	graph<char> m2('a');

	m2.add('b');
	m2.add('c');
	m2.add('d');
	m2.add('e');

	m2.add('c','e');
	m2.add('e','e');

	m2.print();

	m2.remove('b');
	m2.add('z');

	m2.print();
	return 0;
}