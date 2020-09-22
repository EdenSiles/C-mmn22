#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"


/*save the given values in the wanted object*/
void read_comp(complex*	c, double r, double i) {
	c->r = r;
	c->i = i;
}
/*print the object*/
void print_comp(complex* c) {
	printf("%.2f+(%.2f)i\n", c->r, c->i);
}
/*add objects by their real and img field*/
void add_comp(complex* c1, complex* c2) {
	complex* temp;
	temp=(complex*)malloc(sizeof(complex));
	temp->r = (c1->r) + (c2->r);
	temp->i = (c1->i) + (c2->i);
	printf("%.2f+(%.2f)i\n", temp->r, temp->i);
}
/*sub objects by their real and img field*/
void sub_comp(complex* c1, complex* c2) {
	complex* temp;
	temp = (complex*)malloc(sizeof(complex));
	temp->r = (c1->r) - (c2->r);
	temp->i = (c1->i) - (c2->i);
	printf("%.2f+(%.2f)i\n", temp->r, temp->i);
}
/*mult object in real number*/
void mult_comp_real(complex* c,double real) {
	complex* temp;
	temp = (complex*)malloc(sizeof(complex));
	temp->r = (c->r)*real;
	temp->i = (c->i)*real;
	printf("%.2f+(%.2f)i\n", temp->r, temp->i);
}
/*mult object in img number*/
void mult_comp_img(complex* c, double img) {

	complex* temp;
	temp = (complex*)malloc(sizeof(complex));
	temp->r = (c->i)*img*(-1); /*mult i in i is -1*/
	temp->i = (c->r)*img;
	printf("%.2f+(%.2f)i\n", temp->r, temp->i);
}
/*mult object in another object*/
void mult_comp_comp(complex* c1, complex* c2) {
	complex* temp;
	double real, img;
	real = (c1->r)*(c2->r) - (c1->i)*(c2->i);
	img = (c1->i)*(c2->r) + (c1->r)*(c2->i);
	temp = (complex*)malloc(sizeof(complex));
	temp->r = real;
	temp->i = img;
	printf("%.2f+(%.2f)i\n", temp->r, temp->i);
}
/*calculate the abs of object*/
void abs_comp(complex* c) {
	
	double real_pow, img_pow,sum;
	real_pow = (c->r)*(c->r);
	img_pow = (c->i)*(c->i);
	sum = real_pow + img_pow;
	printf("%.2f\n", sqrt(sum));
}
/*exit the program*/
void stop() {
	exit(0);
}