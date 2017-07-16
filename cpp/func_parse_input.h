#ifndef PARSE_INPUT_H

#define PARSE_INPUT_H

#include "struct_Frame.h"
#include "struct_Piece.h"

// This function parses the input string in the input file
// into Pieces and Frame
// Pieces: array of the assignment pieces
// Frame: the assignment frame

void parse_input(const char* filename, Piece**& pieces, Frame*& frame, int &num_pieces) {

	fstream fp;

	fp.open(filename, ios::in);

	int num_of_pieces;
	fp >> num_of_pieces;
	num_pieces = num_of_pieces;
	cout << "Num of pieces = " << num_of_pieces << endl;

	pieces = new Piece*[num_of_pieces];

// Get pieces info
	for (int i = 0; i < num_of_pieces; i++) {

		int num_of_vertices;
		fp >> num_of_vertices;

		pieces[i] = new Piece(num_of_vertices);

		for (int j = 0; j < num_of_vertices; j++) {
			int x, y;
			fp >> x >> y;
			Dot *dot = new Dot(x, y);
			pieces[i]->set_vertice(j, dot);
		}
	}

// Get frame info
	{
		int num_of_vertices;
		fp >> num_of_vertices;
		frame = new Frame(num_of_vertices);
		int x, y;
		int i = 0;
		while (fp >> x >> y) {
			Dot *dot = new Dot(x, y);
			frame->set_vertice(i, dot);
			i++;
		}
	}

	fp.close();
}

#endif
