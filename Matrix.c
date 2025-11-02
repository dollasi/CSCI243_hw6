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
	float *data;
};
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
Status mat_set_cell(Matrix m, float value, size_t row, size_t col){
	if(!m || row < 1 || row > m->rows) return BadRowNumber;
	if(col<1 || col > m->cols) return BadColNumber;
	
	m->data[(row - 1) * m->cols + (col - 1)] = value;
	return Success;

}
Status mat_get_cell(const Matrix m, float *out, size_t row, size_t col){
	if(!m || row < 1 || row > m->rows) return BadRowNumber;
	if (col< 1 || col > m->cols) return BadColNumber;

	*out = m->data[(row - 1) * m-> cols + (col - 1)];
	return Success;

}
//full row
Status mat_set_row(Matrix m, const float arr[], size_t row) {
	if (!m || row < 1 || row > m->rows)
	return BadRowNumber;
	size_t start = (row - 1) * m->cols;
	for (size_t j = 0; j < m->cols; j++) {
		m->data[start + j] = arr[j];
	}
	return Success;
}

// get a full row
Status mat_get_row(const Matrix m, float arr[], size_t row) {
	if (!m || row < 1 || row > m->rows) return BadRowNumber;
	size_t start = (row - 1) * m->cols;
	for (size_t j = 0; j < m->cols; j++) {
		arr[j] = m->data[start + j];
	}
	return Success;
}
// multiply all elements by a scalar
void mat_scalar_mult(Matrix m, float value) {
	if (!m) return;
	size_t total = m->rows * m->cols;
	for (size_t i = 0; i < total; i++) {
		m->data[i] *= value;
	}
}

//duplicate a matrix
Matrix mat_duplicate(const Matrix src) {
	if(!src) return NULL;
	Matrix copy = mat_create(src->rows, src->cols);
    
	if (!copy)return NULL;

	size_t total = src->rows * src->cols;
	for(size_t i = 0; i < total; i++) {
		copy->data[i] = src->data[i];
	}
	return copy;
}

//check equality
bool mat_equals(const Matrix m1, const Matrix m2) {
	if (!m1 || !m2)
	return false;
	if (m1->rows != m2->rows || m1->cols != m2->cols) return false;
	
	size_t total = m1->rows * m1->cols;
	for (size_t i = 0; i < total; i++) {
		if (m1->data[i] != m2->data[i]) return false;
	}
	return true;
}

// multiply two matrices
Matrix mat_mult(const Matrix a, const Matrix b) {
	if (!a || !b) return NULL;
	if (a->cols != b->rows)return NULL;

	Matrix result = mat_create(a->rows, b->cols);
	if(!result)return NULL;
		for (size_t i = 1; i <= a->rows; i++) {
			for (size_t j = 1; j <= b->cols; j++) {
				float sum = 0.0f;
				for (size_t k = 1; k <= a->cols; k++){
					sum += a->data[(i - 1) * a->cols + (k - 1)] * b->data[(k - 1) * b->cols + (j - 1)];
				}
				result->data[(i - 1) * result->cols + (j - 1)] = sum;
			}
		}
		return result;
}

//transpose a matrix
Matrix mat_transpose(const Matrix m) {
	if (!m)return NULL;
	Matrix t = mat_create(m->cols, m->rows);
	if (!t) return NULL;

	for (size_t i = 1; i <= m->rows; i++) {
		for (size_t j = 1; j <= m->cols; j++) {
			t->data[(j - 1) * t->cols + (i - 1)] =
			m->data[(i - 1) * m->cols + (j - 1)];
		}
	}
	return t;
}

//print the matrix
void mat_print(const Matrix m, FILE *stream) {
	if (!m || !stream) return;

	fprintf(stream, "%zu rows, %zu columns:\n", m->rows, m->cols);
	for (size_t i = 1; i <= m->rows; i++) {
		for (size_t j = 1; j <= m->cols; j++) {
			fprintf(stream, "%8.3f", m->data[(i - 1) * m->cols + (j - 1)]);
		}
	fputc('\n', stream);
	}
}
