#ifndef LIN_EQ_SOLVER_H
#define LIN_EQ_SOLVER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Defines the maximum dimension that you can use
// Can change the number if larger than 20x20 matrix is needed
#define MAX_DIM 20

// Defines a structure, with four variables (two vectors, one matrix, and an integer)
typedef struct
{
  long double matrix[MAX_DIM][MAX_DIM];
  long double vector[MAX_DIM];
  long double solution[MAX_DIM];
  int    dim;
}lin_eq_type;

// Defines the functions to actually do the math
int solve_lin_eq(lin_eq_type *lin_eq);
long double  det(int m, lin_eq_type *lin_eq);

#endif
