#ifndef PUZZLE_H

#define PUZZLE_H

#include <cmath>
#include <cstdio>
#include "struct_Dot.h"
#include <iostream>

using std::endl;
using std::cout;

#include <iomanip>

using std::setw;

#include <ostream>

using std::ostream;

struct Puzzle {

	// Puzzle id
	int id;

	// Number of vertices
	int num_of_vertices;

	// List of vertices
	Dot** vertices;

	// Angles

	double* angles;

	/* Class constructor */

	Puzzle(const int num_of_vertices) {
		// Create a puzzle with a provided num of vertices
		this->num_of_vertices = num_of_vertices;
		this->vertices = new Dot*[num_of_vertices];
		this->angles = new double[num_of_vertices];

		//this->calculateAngle();
	}

	Puzzle() {

		this->num_of_vertices = 0;
		this->vertices = NULL;
		this->angles = NULL;
	}

	/* Class destructor */

	~Puzzle() {
		// Delete all vertices
		for (int i = 0; i < this->num_of_vertices; i++) {
			delete this->vertices[i];
		}
		// Delete list of vertices
		delete [] this->vertices;
		delete [] this->angles;
	}

	void calculateAngle() {
		Dot *A, *B, *C; // Triangle abc
		int ai, bi, ci; // Vertice's index
		double a, b, c; // Triangle sides
		double cosCi;
		// for (int i = 0; i < this->num_of_vertices; i++) {
		// 	this->angles[i] = calculate_angle(i);
		// }
		for (int i = 0; i < this->num_of_vertices; i++) {
			// Law of cosines

			ai = (i - 1 + this->num_of_vertices) % this->num_of_vertices;
			bi = (i + 1) % this->num_of_vertices;
			ci = i;
			A = this->vertices[ai];
			B = this->vertices[bi];
			C = this->vertices[ci];

			a = sqrt(
				(double) pow(B->x - C->x, 2) + pow(B->y - C->y, 2)
			);

			b = sqrt(
				(double) pow(A->x - C->x, 2) + pow(A->y - C->y, 2)
			);

			c = sqrt(
				(double) pow(B->x - A->x, 2) + pow(B->y - A->y, 2)
			);
			//cout << a << " " << b << " " << c << endl;
			cosCi = (pow(a, 2) + pow(b, 2) - pow(c, 2)) / 2.0 / (double) a / (double) b;
			angles[i] = acos(cosCi) * 180 / M_PI;
			//cout << cosCi << endl;
			//cout << setprecision(10) << M_PI << endl;
			//printf("%.4f\n", angles[i]*180 / M_PI);
		}
	}

	// Set a dot as a vertice of the puzzle
	void set_vertice(const int index, Dot* dot) {
		this->vertices[index] = dot;
	}

	friend ostream& operator<<(ostream &out, const Puzzle &ob);

	double calculate_angle(const int v);
	double calculate_angle(const int v, const int v1, const int v2);
};

double Puzzle::calculate_angle(const int v, const int v1, const int v2) {
	Dot *A, *B, *C;
	// Get the vertices
	A = vertices[v  % num_of_vertices];
	B = vertices[v1 % num_of_vertices];
	C = vertices[v2 % num_of_vertices];
	Dot *AB, *AC;
	AB = new Dot(B->x - A->x, B->y - A->y);
	AC = new Dot(C->x - A->x, C->y - A->y);
	double cosA;
	// Tich vo huong cua vector AB va AC
	int AB_AC = AB->x * AC->x + AB->y * AC->y;
	double ab, ac; // Do dai cua AB, AC
	ab = sqrt(AB->x * AB->x + AB->y * AB->y);
	ac = sqrt(AC->x * AC->x + AC->y * AC->y);
	cosA = (double) AB_AC / ab / ac;
	return acos(cosA) * 180 / M_PI;
}

double Puzzle::calculate_angle(const int v) {
	int v_next, v_prev;
	v_next = (v+1) % num_of_vertices;
	v_prev = (v-1+num_of_vertices) % num_of_vertices;
//	std::cout << "DEBUG " << v << " " << v_next << " " << v_prev << std::endl;
	double angle = calculate_angle(v, v_next, v_prev);
	{
		// So luot duyet cac goc con
		int iterations = num_of_vertices - 2;
		// Lay vi tri dau tien, duyet theo chieu tang dan

		double check_angle = 0;
		for (int i = 0; i < iterations; i++) {
			int v1 = (v_next + i) % num_of_vertices;
			int v2 = (v1 + 1) % num_of_vertices;
//			std::cout << "DEBUG " << v << " " << v1 << " " << v2 << std::endl;
			check_angle += calculate_angle(v, v1, v2);
		}
//	std::cout << "DEBUG " << check_angle << std::endl;
		if (check_angle <= 180) {
//			if (angle == check_angle) {
				return angle;
//			}

		} else {
			// Neu check_angle > 180 thi co 2 truong hop
			if (abs(check_angle + angle - 360.000) < 0.05) {
				return check_angle;
			} else {
				if (check_angle + angle > 360) {
					return check_angle;
				} else {
					return angle;
				}
			}

		}
}
}

ostream& operator<<(ostream &out, const Puzzle &ob) {

	out << ob.num_of_vertices << " vertices : " << endl;
	for (int i = 0; i < ob.num_of_vertices; i++) {

			out << *(ob.vertices[i]) << endl;
	}

	return out;
}

#endif
