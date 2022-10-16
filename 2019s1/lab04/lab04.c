#include <stdio.h>
#include <stdlib.h>
#include "retangulo.h"
#include "vetor.h"

#define MAX 1000

/*
 * reads from keyboard input the coordinates of n rectangles
 * and n vectors of movement
 * @param size number of rectangles to read
 * @return array with n rectangles moved
 */
retangulo ** read_retangulos(int size) {
	retangulo ** arr;
	vetor * v;
	double px, py, qx, qy;
	
	if ( !( arr = malloc( size * sizeof(retangulo *) ) ) )
		exit(1);
	for (int i = 0; i < size; i++) {
		scanf("%lf %lf %lf %lf", &px, &py, &qx, &qy);
		arr[i] = retangulo_criar(px, py, qx, qy);
		scanf("%lf %lf", &px, &py);
		v = vetor_criar(px, py);
		retangulo_transladar(arr[i], v);
		vetor_destruir(v);
	}

	return arr;
}

/*
 * frees alocated memory for arrays of rectangles
 * @param arr array of rectangles
 * @param size number of rectangles to read
 */
void free_retangulos(retangulo ** arr, int size) {
	for (int i = 0; i < size; i++)
		retangulo_destruir(arr[i]);
	free(arr);	
}

/*
 * frees alocated memory for arrays of rectangles
 * @param arr1 array of rectangles
 * @param size1 size of arr1
 * @param arr2 array of rectangles
 * @param size2 size of arr2
 * @param screen rectangle of screen
 * @return biggest area of intersection
 */
double max_intersection(retangulo ** arr1, int size1, retangulo ** arr2, int size2, retangulo * screen) {
	double cur, max = 0;
	retangulo * in;

	for (int i = 0; i < size1; i++)
		for (int j = 0; j < size2; j++) {
			if ( !( in = retangulo_interseccao(arr1[i], arr2[j]) ) )
				continue;
			if (retangulo_intersectam(in, screen)) {
				cur = retangulo_area(in);
				if (cur > max)
					max = cur;
			}
			retangulo_destruir(in);	
		}
	
	return max;	
}


int main(void) {
	double px, py, qx, qy, area; // read input square
	int n_att, n_def;
	retangulo * screen, ** att_arr, ** def_arr;

	// input reading
	scanf("%lf %lf %lf %lf", &px, &py, &qx, &qy);
	screen = retangulo_criar(px, py, qx, qy);

	scanf("%d", &n_att);
	att_arr = read_retangulos(n_att);

	scanf("%d", &n_def);
	def_arr = read_retangulos(n_def);

	// area calculation
	area = max_intersection(att_arr, n_att, def_arr, n_def, screen);
	if (area)
		printf("%.2f\n", area);
	else
		printf("%s\n", "null");

	// memory allocation freeing
	free_retangulos(att_arr, n_att);
	free_retangulos(def_arr, n_def);
	retangulo_destruir(screen);
}