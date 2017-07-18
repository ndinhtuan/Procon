#include <iostream>
#include <fstream>

using namespace std;

#include "cpp/func_parse_input.h"

int main(int argc, char *argv[]) {

	Piece** pieces;
	Frame* frame;

	cout << "Parsing ..." << endl;
	int num_pieces;
	parse_input("input1.txt", pieces, frame, num_pieces);
	frame->calculateAngle();
	frame->set_num_of_pieces(num_pieces);

	for (int i = 0; i < num_pieces; i++) {
		pieces[i]->calculateAngle();
	}
	cout << *pieces[7];
	frame->fill_half_auto(pieces);
	return 0;
}
