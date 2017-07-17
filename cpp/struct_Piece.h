#ifndef PIECE_H

#define PIECE_H

#include "struct_Puzzle.h"
#include "struct_Dot.h"

struct Piece : public Puzzle {

	/* Class constructor */

	Piece(const int num_of_pieces) : Puzzle(num_of_pieces) {
		flipped = false;
		filled = false;
	}

	// Dua vao su thay doi (new_x, new_y) cua 3 dinh ta tim dc su thay doi cua tat ca cac dinh con lai cua piece
	int fix_coord_piece(int index);
	void print_new_coord();

	// find new D known new A, B, C
	static int find_new_coord_dot(Dot *dot_D, Dot *dot_A, Dot *dot_B, Dot *dot_C);
	// tim nghiem nguyen cua he phuong trinh tra ve nghiem x, y
	// tra ve so duong neu nghiem nguyen, so am neu khong co nghiem nguyen. Tra ve 0 he vo ly
	static int find_integer_solution_of_equations(int a, int b, int c, int a1, int b1, int c1,
																									int &x, int &y);

	bool flipped;
	bool filled;
};

void Piece::print_new_coord() {

	cout << "New coord - " << this->num_of_vertices << " vertices : " << endl;

	for (int i = 0; i < this->num_of_vertices; i++) {

		(this->vertices[i])->print_new_coord();
	}
}

int Piece::fix_coord_piece(int index) {

	int index_next = (index + 1) % this->num_of_vertices;
	int index_prev = (index - 1 + this->num_of_vertices) % this->num_of_vertices;

	Dot *dot_A = this->vertices[index];
	Dot *dot_B = this->vertices[index_next];
	Dot *dot_C = this->vertices[index_prev];
	// Dua vao (new_x, new_y) cua 3 dinh A, B, C de tim cac dinh con lai

	int i = (index_prev - 1 + this->num_of_vertices) % this->num_of_vertices;
	while (i != index_next) {

		int tmp = find_new_coord_dot(this->vertices[i], dot_A, dot_B, dot_C);

		if (tmp < 0) {

			cout << "Cannot find new coord of dot." << endl;
			return -1;
		}
		i = (i - 1 + this->num_of_vertices) % this->num_of_vertices;
	}

	return 1;
}

int Piece::find_integer_solution_of_equations(int a, int b, int c, int a1, int b1, int c1,
																							 int &x, int &y) {

	if (a != 0)	{

		if ((a * c1 - a1 * c) % (a * b1 - a1 * b) != 0) return -1;
		y = (a * c1 - a1 * c) / (a * b1 - a1 * b);
		if ((c - b * y) % a != 0) return -2;
		x = (c - b * y) / a;
		return 1;
	}

	if (b != 0) {

		if ((c * b1 - c1 * b) % (a * b1 - a1 * b) != 0) return -3;
		x = (c * b1 - c1 * b) / (a * b1 - a1 * b);
		if ((c - a * x) % b != 0) return -4;
		y = (c - a * x) / b;
		return 2;
	}

	return 0;
}

int Piece::find_new_coord_dot(Dot *dot_D, Dot *dot_A, Dot *dot_B, Dot *dot_C) {

	int square_AD = dot_D->get_square_edge(dot_A);
	int square_BD = dot_D->get_square_edge(dot_B);
	int square_CD = dot_D->get_square_edge(dot_C);

	int a = 2 * (dot_B->new_x - dot_A->new_x);
	int b = 2 * (dot_B->new_y - dot_A->new_y);
	int c = square_AD - square_BD - ((dot_A->new_y) * (dot_A->new_y) - (dot_B->new_y) * (dot_B->new_y)
																		+ (dot_A->new_x) * (dot_A->new_x) - (dot_B->new_x) * (dot_B->new_x));
	int a1 = 2 * (dot_C->new_x - dot_A->new_x);
	int b1 = 2 * (dot_C->new_y - dot_A->new_y);
	int c1 = square_AD - square_CD - ((dot_A->new_y) * (dot_A->new_y) - (dot_C->new_y) * (dot_C->new_y)
																		+ (dot_A->new_x) * (dot_A->new_x) - (dot_C->new_x) * (dot_C->new_x));

	int k = find_integer_solution_of_equations(a, b, c, a1, b1, c1, dot_D->new_x, dot_D->new_y);
	//cout << "k = " << k << endl;
	if (k <= 0) {

		cout << "Not found integer coord dot !" << endl;
		return -1;
	}
	return 1;
}
#endif
