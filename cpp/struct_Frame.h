#ifndef FRAME_H

#define FRAME_H

#include "struct_Puzzle.h"
#include "struct_Piece.h"
#include "struct_Dot.h"
#include <iostream>

using std::cout;
using std::endl;

#include <vector>

using std::vector;

#define EPSILON 1e-8

struct Frame : Puzzle {

	/* Class constructor */

	Frame(const int num_of_vertices) : Puzzle(num_of_vertices) {

	}

	void fill(Piece **all_pieces);
	// return comfortable index of piece for index_frame of Frame
	int find_piece_at_index(Piece **all_pieces, Piece*& comfort_piece, int index_frame);
	// chon prev_index, index_piece, next_piece fix dung vao prev_index, index_frame, next_index_frame theo is_comfort_edges()
	// Sau ham nay 3 toa do dinh cua piece tai index se thay doi
	// Tra ve false neu khong chon dc
	bool choose_position_for_piece(Piece *piece, int index_piece, int index_frame); // <- can thay doi cho tim dc goc phu hop tra ve luon, ta tim nhieu goc roi thu
	// Dua vao su thay doi cua 3 dinh ta tim dc su thay doi cua tat ca cac dinh con lai cua piece
	// index, index -1, index + 1 la 3 dinh da co su tinh tien, thay doi taij (new_x, new_y)
	void fix_coord_piece(Piece *piece, int index);
	void get_new_frame();
	void set_num_of_pieces(int _num_of_pieces) {

		num_of_pieces = _num_of_pieces;
	}
	static bool is_square_number(int number);
	static bool is_comfort_edges(int edge_sqr_1, int edge_sqr_2);
	static int UCLN(int a, int b);
	// kiem tra xem cac canh (iP, iP_n); (iP, iP_p) co comfort voi (iF, iF_n) vaf (iF, iF_p) hay khong
	// dung ham is_comfort_edges
	static bool is_comfort_3_dot(Dot *iP, Dot *iP_n, Dot *iP_p, Dot *iF, Dot *iF_n, Dot *iF_p);
	// Ham fit 3 dot cua piece theo 3 dot cua frame
	static int fit_3_dot(Dot *iP, Dot *iP_n, Dot *iP_p, Dot *iF, Dot *iF_n, Dot *iF_p);

	vector<Piece*> result_pieces;
	int num_of_pieces;
};

void Frame::fill(Piece **all_pieces){

	int index = 0;

	while (index < num_of_vertices) {
		cout << "Vertice " << index << " with angle " << angles[index] * 180 / M_PI << " : " << endl;
		Piece *comfort_piece = NULL;

		if (abs(angles[index] - M_PI/2) <= EPSILON) {
			index ++;
			continue;
		}

		// Find comfortable piece for index th of frame
		int index_piece = find_piece_at_index(all_pieces, comfort_piece, index);

		if (index_piece == -1) {

			cout << "Not found comfortable piece." << endl;
		}
		else {
			// Found comfortable piece
			bool h = choose_position_for_piece(comfort_piece, index_piece, index);
			if (!h) {
				cout << "Not choose position." << endl;
			}
			else {
				int tmp = comfort_piece->fix_coord_piece(index_piece);
				if (tmp < 0) cout << " Cannot fix coord piece " << endl;
				comfort_piece->print_new_coord();
			}

		}

		// --------------------------------------------



		index++;
		cin.ignore().get();
	}
}

int Frame::find_piece_at_index(Piece **all_pieces, Piece*& comfort_piece, int index_frame) {

	for (int i = 0; i < num_of_pieces; i++) {

		for (int j = 0; j < all_pieces[i]->num_of_vertices; j++) {

			if (abs(angles[index_frame] - all_pieces[i]->angles[j]) <= EPSILON) {

				comfort_piece = all_pieces[i];
				return j;
			}

		}
	}

	return -1; // NOT FOUND COMFORTABLE PIECE
}

bool Frame::is_square_number(int number) {

	int tmp = int(sqrt(number));
	return tmp*tmp == number;
}

int Frame::UCLN(int a, int b) {

	while (b != 0) {

		int tmp = b;
		b = a % b;
		a = tmp;
	}
	return a;
}

bool Frame::is_comfort_edges(int edge_sqr_1, int edge_sqr_2) {

	int ucln = UCLN(edge_sqr_1, edge_sqr_2);

	for (int i = 1; i <= ucln; i++) {

		if (edge_sqr_1 % i == 0 && edge_sqr_2 % i == 0) {

				int tmp1 = edge_sqr_1 / i;
				int tmp2 = edge_sqr_2 / i;
				if (is_square_number(tmp1) && is_square_number(tmp2)) return true;
		}
	}

	return false;
}

bool Frame::is_comfort_3_dot(Dot *vertice_piece, Dot *vertice_piece_next, Dot *vertice_piece_prev,
															Dot *vertice_frame, Dot *vertice_frame_next, Dot *vertice_frame_prev) {

	int square_edge_piece_next = vertice_piece->get_square_edge(vertice_piece_next);
	int square_edge_piece_prev = vertice_piece->get_square_edge(vertice_piece_prev);

	int square_edge_frame_next = vertice_frame->get_square_edge(vertice_frame_next);
	int square_edge_frame_prev = vertice_frame->get_square_edge(vertice_frame_prev);

	return is_comfort_edges(square_edge_piece_next, square_edge_frame_next) &&
				 is_comfort_edges(square_edge_piece_prev, square_edge_frame_prev);
}

// ham nay set cac gia tri (new_x, new_y) cho 3 dot cua piece
// tra ve duong neu fit ok, so duong lon neu co mot dinh trung luon vs frame
int Frame::fit_3_dot(Dot *vertice_piece, Dot *vertice_piece_next, Dot *vertice_piece_prev,
															Dot *vertice_frame, Dot *vertice_frame_next, Dot *vertice_frame_prev) {

	//vertice_piece->new_x = vertice_frame->x;
	//vertice_piece->new_y = vertice_frame->y;
	int a = Dot::fit_point_of_edge(vertice_piece, vertice_piece_next, vertice_frame, vertice_frame_next);
	int b = Dot::fit_point_of_edge(vertice_piece, vertice_piece_prev, vertice_frame, vertice_frame_prev);

	cout << "Value of fit : " << a << " and " << b << endl;
	if (a > 0 && b > 0) {
		return a + b;
	}
	else return -1;
}

bool Frame::choose_position_for_piece(Piece *piece, int index_piece, int index_frame) {

	int index_piece_next = (index_piece + 1) % piece->num_of_vertices;
	int index_piece_prev = (index_piece - 1 + piece->num_of_vertices) % piece->num_of_vertices;

	int index_frame_next = (index_frame + 1) % this->num_of_vertices;
	int index_frame_prev = (index_frame - 1 + this->num_of_vertices) % this->num_of_vertices;

	Dot *vertice_piece = piece->vertices[index_piece];
	Dot *vertice_piece_next = piece->vertices[index_piece_next];
	Dot *vertice_piece_prev = piece->vertices[index_piece_prev];

	Dot *vertice_frame = this->vertices[index_frame];
	Dot *vertice_frame_next = this->vertices[index_frame_next];
	Dot *vertice_frame_prev = this->vertices[index_frame_prev];

	int val1, val2;
	Dot *dot_n1 = new Dot(*vertice_piece_next);
	Dot *dot_p1 = new Dot(*vertice_piece_prev);
  Dot *dot_n2 = new Dot(*vertice_piece_next);
	Dot *dot_p2 = new Dot(*vertice_piece_prev);

	if (is_comfort_3_dot(vertice_piece, vertice_piece_next, vertice_piece_prev,
												vertice_frame, vertice_frame_next, vertice_frame_prev)) {
		vertice_piece->new_x = vertice_frame->x;
		vertice_piece->new_y = vertice_frame->y;
		val1 = fit_3_dot(vertice_piece, dot_n1, dot_p1, vertice_frame, vertice_frame_next, vertice_frame_prev);
  }

	if (is_comfort_3_dot(vertice_piece, vertice_piece_prev, vertice_piece_next,
												vertice_frame, vertice_frame_next, vertice_frame_prev)) {
		vertice_piece->new_x = vertice_frame->x;
		vertice_piece->new_y = vertice_frame->y;
		val2 = fit_3_dot(vertice_piece, dot_p2, dot_n2, vertice_frame, vertice_frame_next, vertice_frame_prev);
  }

	cout << "val1 : " << val1 << endl;
	cout << "val2 : " << val2 << endl;
	if (val1 > 100 || val2 < 0) {

		vertice_piece_next->new_x = dot_n1->new_x;
		vertice_piece_next->new_y = dot_n1->new_y;

		vertice_piece_prev->new_x = dot_p1->new_x;
		vertice_piece_prev->new_y = dot_p1->new_y;
		return true;
	}

	if (val2 > 100 || val1 < 0) {

		vertice_piece_next->new_x = dot_n2->new_x;
		vertice_piece_next->new_y = dot_n2->new_y;

		vertice_piece_prev->new_x = dot_p2->new_x;
		vertice_piece_prev->new_y = dot_p2->new_y;
		return true;
	}

	return false;
}

#endif
