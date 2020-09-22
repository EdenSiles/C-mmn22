

/*declare on complex struct*/

typedef struct complex {
	double r;
	double i;
}complex;

struct complex comp_arr[6];

void read_comp(complex* c, double r, double i);
void print_comp(complex* c);
void add_comp(complex* c1, complex* c2);
void sub_comp(complex* c1, complex* c2);
void mult_comp_real(complex* c, double real);
void mult_comp_img(complex* c, double img);
void mult_comp_comp(complex* c1, complex* c2);
void abs_comp(complex* c);
void stop();