#include <iostream>
#include <cstdlib>
#include <ctime>
#include "field.h"

Box::Box() :c(' '), ant(nullptr), anthill(nullptr)
{
}

void Box::create_anthill()
{
	anthill = new Anthill();
}

Anthill* Box::get_anthill() const
{
	return anthill;
}

void Box::set_char(char c_)
{
	c = c_;
}

char Box::get_char() const
{
	return c;
}

Field::Field(int n_, int m_):n(n_+2), m(m_+2),
field(std::vector<std::vector<Box*>>(n, std::vector<Box*>(m)))
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			field[i][j] = new Box();

	field[n / 2][m / 2]->set_char('H');
	field[n / 2][m / 2]->create_anthill();

	for (int i = 0; i < m; i++) {
		field[0][i]->set_char('_');
		field[n - 1][i]->set_char('_');
	}

	for (int i = 1; i < n; i++) {
		field[i][0]->set_char('|');
		field[i][m - 1]->set_char('|');
	}
}

void Field::generation_resources()
{
	std::srand(std::time(nullptr));
	int food_resources = m / 2 + std::rand() % 3 - 1;
	int branch_resources = n / 2 + std::rand() % 3 - 1;

	for (int i = 0; i < food_resources; i++) {
		int i_food, j_food;
		do {
			i_food = std::rand() % n;
			j_food = std::rand() % m;
		} while (field[i_food][j_food]->get_char() != ' ');
		field[i_food][j_food]->set_char('F');
	}

	for (int i = 0; i < branch_resources; i++) {
		int i_branch, j_branch;
		do {
			i_branch = std::rand() % n;
			j_branch = std::rand() % m;
		} while (field[i_branch][j_branch]->get_char() != ' ');
		field[i_branch][j_branch]->set_char('B');
	}
}

void Field::print_field() const
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			std::cout << field[i][j]->get_char();
		std::cout << std::endl;
	}
}
