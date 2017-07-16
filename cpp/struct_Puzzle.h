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
			angles[i] = acos(cosCi);
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

};

ostream& operator<<(ostream &out, const Puzzle &ob) {

	out << ob.num_of_vertices << " vertices : " << endl;
	for (int i = 0; i < ob.num_of_vertices; i++) {

			out << *(ob.vertices[i]) << endl;
	}

	return out;
}

#endif
