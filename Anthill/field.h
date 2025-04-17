#pragma once
#include <vector>
#include <string>
#include "ant.h"
#include "anthill.h"

class Box {
private:
	char c;
	Ant* ant;
	Anthill* anthill;
public:
	Box();

	void create_anthill();
	Anthill* get_anthill()const;

	void set_char(char c_);
	char get_char()const;
};

class Field {
private:
	int n;
	int m;
	std::vector<std::vector<Box*>>field;

public:
	Field(int n_, int m_);

	void generation_resources();
	void print_field()const;
};