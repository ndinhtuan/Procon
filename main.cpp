#include <iostream>
#include <fstream>

using namespace std;

#include "cpp/func_parse_input.h"

int main(int argc, char *argv[]) {

	int x, y;
	cout << Piece::find_integer_solution_of_equations(7, 2, 6, 1, 1, 4, x, y) << " : ";
	cout << x << ", " << y << endl;

	Piece** pieces;
	Frame* frame;

	cout << "Parsing ..." << endl;
	int num_pieces;
	parse_input("input.txt", pieces, frame, num_pieces);
	frame->calculateAngle();
	frame->set_num_of_pieces(num_pieces);

	for (int i = 0; i < num_pieces; i++) {
		pieces[i]->calculateAngle();
	}

	frame->fill(pieces);
	return 0;
}
