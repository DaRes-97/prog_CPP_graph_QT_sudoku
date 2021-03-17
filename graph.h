#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <cassert>

class graph{
private:

	typedef unsigned int idtype;

	idtype _len;
	bool* _node;
	bool** _arch;

	inline void init_vars(idtype len){
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

	inline void destr_vars(){
		delete[] _node;

		for(idtype c = 0; c < _len; c++)
			delete[] _arch[c];

		delete[] _arch;

		_len = 0;
		_node = nullptr;
		_arch = nullptr;
	}

public:

	graph() : _len(0), _node(nullptr), _arch(nullptr)
	{

	}

	graph(idtype id) : _len(0), _node(nullptr), _arch(nullptr)
	{
		init_vars(id+1);
		_node[id] = true;
	}

	~graph()
	{
		destr_vars();
	}
};

#endif