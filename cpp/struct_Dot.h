#ifndef DOT_H
#define DOT_H

#include <iostream>

using std::cout;
using std::endl;

#include <ostream>

using std::ostream;

//#include "struct_Frame.h"

struct Dot {

	int x;
	int y;

	// new_x, new_y dung cho phep bien hinh cua piece
	int new_x;
	int new_y;

	Dot(int x = 0, int y = 0, int new_x = 0, int new_y = 0) {
		setX(x);
		setY(y);

		this->new_x = new_x;
		this->new_y = new_y;
	}

	Dot(Dot &dot) {

		x = dot.x;
		y = dot.y;
		new_x = dot.new_x;
		new_y = dot.new_y;
	}

	void setX(const int x) {
		this->x = x;
	}


	void setY(const int y) {
		this->y = y;
	}

	void print(const char delimiter) {
		std::cout << this->x << " " << this->y;
	}

	int get_square_edge(const Dot *dot1);
	bool operator==(const Dot *ob2);
	void print_new_coord();

	// tim toa do moi cua B (new_x, new_y) khi biet toa do ms cua dinh A va vec to chi phuong u
	// tra ve am neu toa do cua B khong la so nguyen
	// dot_a da biet toa do moi (new_x, new_y) - la toa do comfort cua piece
	static int fit_point_of_edge(Dot *dot_a, Dot *dot_b, Dot *dot_c, Dot *dot_d);

	friend ostream& operator<<(ostream &out, const Dot &ob);
};

void Dot::print_new_coord() {

	cout << "(" << new_x << ", " << new_y << ")" << endl;
}

bool Dot::operator==(const Dot *ob2) {

	if (ob2 == NULL) return false;
	return (this->x == ob2->x) && (this->y == ob2->y);
}

ostream& operator<<(ostream &out, const Dot &ob) {

	out << "(" << ob.x << ", " << ob.y << ")" << endl;
	return out;
}

int Dot::get_square_edge(const Dot *dot2) {

	return (this->x - dot2->x) * (this->x - dot2->x) + (this->y - dot2->y) * (this->y - dot2->y);
}


bool is_square_number(int number) {

	int tmp = int(sqrt(number));
	return tmp*tmp == number;
}

int Dot::fit_point_of_edge(Dot *dot_a, Dot *dot_b, Dot *dot_c, Dot *dot_d) {

	int square_edge_AB = dot_a->get_square_edge(dot_b);
	int x_u = dot_d->x - dot_c->x;
	int y_u = dot_d->y - dot_c->y;

	// He phuong trinh duong tron va duong thang
	if (square_edge_AB * x_u * x_u % (x_u * x_u + y_u * y_u) != 0) return -1;
	int tmp = square_edge_AB * x_u * x_u / (x_u * x_u + y_u * y_u);
	if (!is_square_number(tmp)) return -2;
	tmp = sqrt(tmp);
	// 2 truong hop
	// x_u == 0
	if (x_u == 0) {
		dot_b->new_x = dot_a->new_x;

		if (!is_square_number(square_edge_AB)) return -4;
		if (y_u < 0) dot_b->new_y = dot_a->new_y - sqrt(square_edge_AB);
		if (y_u > 0) dot_b->new_y = dot_a->new_y + sqrt(square_edge_AB);

		if (dot_b->new_x == dot_d->new_x && dot_b->new_y == dot_d->new_y) return 100;
		return 3;
	}

	if (tmp * y_u % x_u != 0) return -3;
	cout << "OKKKKKKKKKKKK" << endl;

	int x_B_1 = dot_a->new_x - tmp;
	int y_B_1 = dot_a->new_y - (tmp * y_u) / x_u;
	int x_B_2 = dot_a->new_x + tmp;
	int y_B_2 = dot_a->new_y + (tmp * y_u) / x_u;

	// Can loai 1 truong hop diem B nam ngoai doan DC
	// truong hop nay vector_AB nguoc chieu vs vector_CD : (x_d - x_c) / (x_b - x_a) < 0
	if (x_u * (x_B_1 - dot_a->new_x) < 0) {
		// Loai B_1
		dot_b->new_x = x_B_2;
		dot_b->new_y = y_B_2;

		if (x_B_2 == dot_d->x && y_B_2 == dot_d->y) return 100;
		return 1;
	}

	if (x_u * (x_B_2 - dot_a->new_x) < 0) {

		// Loai B_2
		dot_b->new_x = x_B_1;
		dot_b->new_y = y_B_1;
		if (x_B_1 == dot_d->x && y_B_1 == dot_d->y) return 100;
		return 2;
	}

	cout << "Vo ly";
	return 0;
}

#endif
