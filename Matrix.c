/*
* file: Matrix.c
* author: Alexandria Jones
* description: each amtrix stores its own dimensions and data
* data type is floats
* the type is opaque to users
* 
* halloween riddle:  what do you call a true or false ghost?
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Matrix.h"

struct matrix_st{
	size_t rows;
	size_t cols;
	gloat *data;
}
//create new maxtrix
Matrix mat_create(size_t rows, size_t cols){
	if (rows == 0 || cols == 0) return NULL;

	Matrix m = malloc(sizeof(struct matrix_st));
	if(!m) return NULL;	

	m->rows = rows;
	m->cols = cols;
	m->data = calloc(rows * cols, sizeof(float));

	if (!m->data){
		free(m);
		return NULL;
	}
	if(rows == cols){
		for(size_t i = 1; i <= rows; i++){
			m->data[(i - 1) * cols + (i - 1)] = 1.0f;
		}
	}
	return m;
}
//free all memory used by matrix
void mat_destroy(Matrix m){
	if(!m) return;
	free(m->data);
	free(m);
}

void mat_init(Matrix m, const float data[]){
	if (!m || !data) return;
	size_t total = m->rows * m->cols;
	for(size_t i = 0; i < total; i++){
		m->data[i] = data[i];
	}

}
//single cell
Status mat_set_cell(Matrix m, flat value, size_t row, size_t col){
	if(!m || row < 1 || row > m->rows) return badR;
	if(col<1 || col > m->cols) return badC;
	
	m->data[(row - 1) * m->cols + (col - 1)] = value;
	return Success;

}
Status mat_get_cell(const Matrix m, float *out, size_t row, size_t col){
	if(!m || row < 1 || row > m->rows) return badR;
	if (col < 1 || col > m->cols) return badC;

	*out = m->data[(row - 1) * m-> cols + (col - 1];
	return Success

}
//full row
Status mat_set_row(){


}

//*
Matrix mat_duplicate(){}

bool mat_equals(){}

void mat_scalar_mult(){}

Matrix mat_mult(){}

Status mat_get_cell(){}

Status mat_get_row(){}

Status mat_set_cell(){}

Status mat_set_row(){}

Matrix mat_transpose(){}

void mat_print(){}


// halloween riddle ans: a BOOlean!
