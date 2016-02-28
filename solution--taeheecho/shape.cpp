/* ----------------------------------------------------------------------------
* Copyright &copy; 2016 Taehee Tim Cho <lotty02cho@gmail.com>
* Released under the [MIT License] (http://opensource.org/licenses/MIT)
* ------------------------------------------------------------------------- */

/**
 * Implements `shape.h`.
 */

// TODO: `#include`s for system headers, if necessary

#include "shape.h"
# include "constants.h"
# include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;

// TODO: `#include`s for other local headers, if necessary

// ----------------------------------------------------------------------------

// TODO: implementations for all functions in `class Buffer`

Shape::Shape(const std::string & type)
{
	type_ = type;
	setType(type);
}

Shape::~Shape() = default;
//{
//	type_ = '\0';
//	type_art_ = '\0';
//	Shape::~Shape() 
//}

std::string Shape::getType()
{
	return type_;
}

void Shape::setType(const std::string & type)
{
	if(type == "empty") {
		type_art_ = "     \n     \n     \n";
	}
	else if (type == "triangle") {
		type_art_ = "  ,  \n / \\ \n/___\\\n";
	}
	else if (type == "square") {
		type_art_ = ".---.\n|   |\n'---'\n";
	}
	else {
		cout << "ERROR: 'Shape::setType : invalid type\n" << endl;
		exit(1);
	}
}

void Shape::drawToBuffer(Buffer & b, unsigned int x, unsigned int y) const
{
	b.set(x, y, type_art_);
}

bool Shape::isHappy(const Neighborhood & n,
	unsigned int pos_x,
	unsigned int pos_y) const {

	if (n.get(pos_x, pos_y).getType() == "empty")
		return true;

	unsigned int x_min = (pos_x == 0) ? pos_x : pos_x - 1;
	unsigned int y_min = (pos_y == 0) ? pos_y : pos_y - 1;

	unsigned int x_max = (pos_x == n.size_x - 1) ? pos_x : pos_x + 1;
	unsigned int y_max = (pos_y == n.size_y - 1) ? pos_y : pos_y + 1;

	double alike = 0;
	double different = 0;

	for (int x = x_min; x <= x_max; x++) {
		for (int y = y_min; y <= y_max; y++) {
			if (x == pos_x && y == pos_y)
				continue;
			else if (n.get(x, y).getType() == "empty")
				continue;
			else if (n.get(x, y).getType() == n.get(pos_x, pos_y).getType())
				alike++;
			else
				different++;
		}
	}

	return    (different || alike)
		&& (different == 0 || alike / different >= RATIO_ALIKE_HAPPY)
		&& (alike == 0 || different / alike >= RATIO_DIFFERENT_HAPPY);
}

