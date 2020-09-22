#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"

#define MAX_SIZE 256
int break_str_to_substr(char* line);
char* substr(char *src, int len, int start);
int count_comma(char* s);
void do_op(struct complex *comp_arr);
struct complex* find_complex(char* str, struct complex *comp_arr);
void do_read_comp(struct complex *comp_arr);
void do_print_abs_comp(struct complex *comp_arr);
void do_add_sub_mult_comp(struct complex *comp_arr);
void do_mult_r_i_comp(struct complex *comp_arr);
void do_stop(struct complex *comp_arr);
int count_space_tab(char* s);
void  remove_spaces(char* s);
void  remove_tabs(char* s);

char* cmd_parts[4];

int main() {
	char line[MAX_SIZE];
	int i, idx;
	const char comma[] = ",";
	int sucsess = 1;
	
	/*init the complex objects*/
	for (idx = 0; idx < 6; idx++) {
		comp_arr[idx].r = 0;
		comp_arr[idx].i = 0;
	}
	
	/*allocate memory for the command. We save each part in array's cell*/
	for (i = 0; i < 4; i++) {
		cmd_parts[i] = (char*)malloc(MAX_SIZE * sizeof(char));
		cmd_parts[i] = NULL;
	}
	printf("Please enter command\n");
	/*scanning lines of inputs-each line find which operation to do an do it*/
	while (fgets(line, MAX_SIZE, stdin)) {/*scan line*/
		printf("%s",line);
		if (strcspn(line,"\r\n\0")==0)
			continue;
		if (count_comma(line) == -1) { /*check if ther is 2 commas sequentially*/
			printf("Multiple consecutive commas\n");
			continue;
		}
		for (i = 0; i < 4; i++) {
			cmd_parts[i] = NULL;
		}
		/*split the command to parts*/
		sucsess=break_str_to_substr(line);
		if((sucsess==0)&&(strncmp(cmd_parts[0], "stop", 4) !=0)){
			printf("Missing parameter\n");
			continue;
		}
	
		if ((strpbrk(cmd_parts[0], comma) != NULL)||((cmd_parts[1]!=NULL)&&(strncmp(cmd_parts[1],",",1)==0))){
			printf("Illegal comma\n");
			continue;
		}
			   		 
		do_op(comp_arr);
		printf("Please enter command\n");
	}
	printf("End of file\n");
	
	return 0;
}

int break_str_to_substr(char* line) {
	int i = 0;
	int j = 0;
	int count = 0;
	int start = 0;
	int flag = 0;
	
	while (i<strlen(line)) {
		if (flag == 2) break; /*we split the command to 2 parts*/
		while ((strncmp(line+i," ",1)!=0) && (strncmp(line + i, "	", 1) != 0) && (i < strlen(line))) { /*pass the string while the char isn't tab or space*/
				if (count == 0)
				start = i;
				count++;
				i++;	

		}
		
		if (count != 0) {
			flag++; /*move to next parts*/
			/*split the command to 2 parts- opeartion and arguments*/
			if (flag < 2) { 
				cmd_parts[j] = substr(line, count, start);
				
			}
			else if (flag == 2) {
				cmd_parts[j] = substr(line, strlen(line)-start, start);
				break;
			}
			
			count = 0;
			j++;
			}
		
		i++;
	}
	if (flag < 2)
		return 0;
	return 1;
}

char* substr(char *src, int len,int start)
{
	/*get length of the destination string*/
	int i;
	
	/*allocate (len + 1) chars for destination (+1 for extra null character)*/
	char *dest = (char*)malloc(sizeof(char) * (len + 1));

	/* extracts characters between m'th and n'th index from source string
	 and copy them into the destination string*/
	for (i = start; (i < start+len) && (*(src + i) != '\0'); i++)
	{
		*dest = *(src + i);
		dest++;
	}

	/* null-terminate the destination string*/
	*dest = '\0';

	/* return the destination string*/
	return dest - len;
}

/*this function count commas in the command*/
int count_comma(char* s) {
	int count = 0;
	int i;
	for (i = 0; i < strlen(s); i++) {
		if (count >= 2) /*there is too many commas*/
			return -1;
		if ((s[i] == ' ') || (s[i] == '	'))
			continue;
		if (s[i] == ',')
			count++;
		else
			count = 0;
	}
	return 0;
}

/*this function checks if there is tabs to spaces between chars*/
int count_space_tab(char* s) {
	int flag = 0;
	int i;
	int count = 0;

	if (s == NULL)
		return -2;
	for (i = 0; i < strlen(s); i++) {

		if ((s[i] != ' ') && (s[i] != '	') && ((s[i + 1] == ' ') || s[i + 1] == '	')) {
			flag = 1; /*we pass on a char*/
			i++;
			count++;
		}
		if ((flag == 1) && (s[i] != ' ') && (s[i] != '	')) /*we allready pass on a char and this is the second time*/
			return -1;


	}
	return count;
}

void do_op(struct complex *comp_arr) {
	
	cmd_parts[0] = strtok(cmd_parts[0], "\0"); /*split the operation string from the command*/
	
	/*find the relevent operation and call for the operation's function*/
	if (strcmp(cmd_parts[0], "read_comp") == 0) {
		do_read_comp(comp_arr);
	}
	else if ((strcmp(cmd_parts[0], "print_comp") == 0) || (strcmp(cmd_parts[0], "abs_comp\0") == 0) || (strcmp(cmd_parts[0], "abs_comp\r") == 0) || (strcmp(cmd_parts[0], "abs_comp\n") == 0)) {
		do_print_abs_comp(comp_arr);
	}
	else if ((strcmp(cmd_parts[0], "add_comp") == 0) || (strcmp(cmd_parts[0], "sub_comp") == 0) || (strcmp(cmd_parts[0], "mult_comp_comp") == 0)) {
		do_add_sub_mult_comp(comp_arr);
	}
	else if ((strcmp(cmd_parts[0], "mult_comp_real") == 0) || (strcmp(cmd_parts[0], "mult_comp_img") == 0)) {
		do_mult_r_i_comp(comp_arr);
	}
	else if ((strncmp(cmd_parts[0], "stop",4) == 0) && (cmd_parts[0][5] == '\0')){
		do_stop(comp_arr);
	}
	else {
		if ((strncmp(cmd_parts[0],"\n",1)==0) || (strncmp(cmd_parts[0], "\r", 1) == 0))
			return;
		printf("Undefined command name\n");
		return;
	}
}

struct complex* find_complex(char* str, struct complex *comp_arr) {
	/*remove tabs and spaces from the string*/
	if ((str[0] == ' ') || (str[0] == '	')) {
		remove_spaces(str);
		remove_tabs(str);
	}
	
	/*compare between the string and the complex objects of the program*/
	if (((strncmp(str, "A", 1) == 0) && (((str[1] == '\n')|| (str[1] == '\r')) || (str[1] == '\0'))) || (strncmp(str, "A ", 2) == 0) || (strncmp(str, "A	", 2) == 0)) {
		return &comp_arr[0];
	}
	if (((strncmp(str, "B", 1) == 0) && (((str[1] == '\n') || (str[1] == '\r')) || (str[1] == '\0'))) || (strncmp(str, "B ", 2) == 0) || (strncmp(str, "B	", 2) == 0)) {
		return &comp_arr[1];
	}
	if (((strncmp(str, "C", 1) == 0) && (((str[1] == '\n')|| (str[1] == '\r')) || (str[1] == '\0'))) || (strncmp(str, "C ", 2) == 0) || (strncmp(str, "C	", 2) == 0)) {
		return &comp_arr[2];
	}
	if (((strncmp(str, "D", 1) == 0) && (((str[1] == '\n') || (str[1] == '\r')) || (str[1] == '\0'))) || (strncmp(str, "D ", 2) == 0) || (strncmp(str, "D	", 2) == 0)) {
		return &comp_arr[3];
	}
	if (((strncmp(str, "E", 1) == 0) && (((str[1] == '\n') || (str[1] == '\r')) || (str[1] == '\0'))) || (strncmp(str, "E ", 2) == 0) || (strncmp(str, "E	", 2) == 0)) {
		return &comp_arr[4];
	}
	if (((strncmp(str, "F", 1) == 0) && (((str[1] == '\n') || (str[1] == '\r')) || (str[1] == '\0'))) || (strncmp(str, "F ", 2) == 0) || (strncmp(str, "F	", 2) == 0)) {
		return &comp_arr[5];
	}
	else {
		return NULL;
	}

}

void do_read_comp(struct complex *comp_arr) { 
	
	double i = 0, r = 0;
	
	struct complex* x;
	char* tmp1 = NULL;
	char* tmp2 = NULL;

	/*split the command to parts*/
	cmd_parts[1] = strtok(cmd_parts[1], ",");
	cmd_parts[2] = strtok(NULL, ",");
	cmd_parts[3] = strtok(NULL, "\0");
	
	/*check if there is tabs/spaces between 2 chars*/
	if ((count_space_tab(cmd_parts[1]) == -1) || (count_space_tab(cmd_parts[2]) == -1)) {
		printf("Missing comma\n");
		return;
	}
	

	if ((cmd_parts[1] == NULL) || ((cmd_parts[2] == NULL) || (cmd_parts[3] == NULL) || (strcspn(cmd_parts[3], "\r\n\0") == 0))) {
		printf("Missing parameter\n");
		return;
	}
	/*check the complex variable*/
	x = find_complex(cmd_parts[1],comp_arr);
	if (x == NULL) {
		printf("Undefined complex variable\n");
		return;
	}
	
	if ((strchr(cmd_parts[3], ',') != NULL) || (count_space_tab(cmd_parts[3]) == -1)) {
		printf("Extraneous text after end of command\n");
		return;
	}
	/*cast strings to double*/
	r = strtod(cmd_parts[2],&tmp1);
	i = strtod(cmd_parts[3],&tmp2);
	/*check if the cast success*/
	if ((cmd_parts[2] == tmp1)  || (cmd_parts[3] == tmp2)) {
		printf("Invalid parameter-not a number\n");
		return;
	}
	/*call read_comp operation*/
	read_comp(x, r, i);
}

void do_print_abs_comp(struct complex *comp_arr) { 
	struct complex* x;
	
	cmd_parts[1] = strtok(cmd_parts[1], "\0"); /*split the command*/
	if ((cmd_parts[1] == NULL) || (strcspn(cmd_parts[1], "\r\n\0") == 0)) {
		printf("Missing parameter\n");
		return;
	}
	if ((strchr(cmd_parts[1], ',') != NULL)||(cmd_parts[2] != NULL) || (count_space_tab(cmd_parts[2]) == -1)){
		printf("Extraneous text after end of command\n");
		return;
	}	
	/*check the complex variable*/
	x = find_complex(cmd_parts[1], comp_arr);	
	if (x == NULL) {
		printf("Undefined complex variable\n");
		return;
	}
	/*call the relevent operation*/
	if (strncmp(cmd_parts[0], "print_comp", 10) == 0) {
		print_comp(x);
	}
	else {
		abs_comp(x);
	}
}

/*this function checks errors in mult_comp_comp and sub/add_comp commands and calls for the relevent struct's operation*/
void do_add_sub_mult_comp(struct complex *comp_arr) {

	complex* x;
	complex* y;
	
	cmd_parts[1] = strtok(cmd_parts[1], ","); /*split the command to parts*/
	cmd_parts[2] = strtok(NULL, "\0");

	if ((count_space_tab(cmd_parts[1]) == -1)) { /*check if there is tabs/spaces between 2 chars*/
		printf("Missing comma\n");
		return;
	}
	if ((cmd_parts[1] == NULL) || (cmd_parts[2] == NULL) || (strcspn(cmd_parts[2], "\r\n\0") == 0)) {
		printf("Missing parameter\n");
		return;
	}
	if ((strchr(cmd_parts[2], ',') != NULL) || (count_space_tab(cmd_parts[2]) == -1)) {
		printf("Extraneous text after end of command\n");
		return;
	}	
	x = find_complex(cmd_parts[1], comp_arr); /*check the complex variable*/
	y = find_complex(cmd_parts[2], comp_arr);	
	if ((x == NULL) || (y == NULL)) {
		printf("Undefined complex variable\n");
		return;
	}

	/*call the relevent operation*/
	if (strncmp(cmd_parts[0], "add_comp", 8) == 0) {
		
		add_comp(x, y);
	}
	else if (strncmp(cmd_parts[0], "sub_comp", 8) == 0) {
		sub_comp(x, y);
	}
	else {
		mult_comp_comp(x, y);
	}
}

/*this function checks errors in mult_comp_real/img commands and calls for the relevent struct's operation*/
void do_mult_r_i_comp(struct complex *comp_arr) {

	complex* c;
	double num;
	char* tmp;

	cmd_parts[1] = strtok(cmd_parts[1], ","); /*split the command to parts*/
	cmd_parts[2] = strtok(NULL, "\0");

	if ((count_space_tab(cmd_parts[1]) == -1)) { /*there is a tab or space between 2 chars*/
		printf("Missing comma\n");
		return;
	}
	
	if ((cmd_parts[1] == NULL) || (cmd_parts[2] == NULL) || (strcspn(cmd_parts[2], "\r\n\0") == 0)) {
		printf("Missing parameter\n");
		return;
	}
	
	c = find_complex(cmd_parts[1], comp_arr); /*check the complex variable*/
	if (c == NULL) {
		printf("Undefined complex variable\n");
		return;
	}

	if ((strchr(cmd_parts[2], ',') != NULL) || (count_space_tab(cmd_parts[2]) == -1) ){
		printf("Extraneous text after end of command\n");
		return;
	}
	num = strtod(cmd_parts[2], &tmp); /*cast string to double*/
	
	if (cmd_parts[2] == tmp) {
		
		printf("Invalid parameter-not a number\n");
		return;
	}

	/*call the relevent operation*/
	if (strncmp(cmd_parts[0], "mult_comp_real", 14) == 0) {
		mult_comp_real(c, num);
	}
	else {
		mult_comp_img(c, num);
	}
}

/*this function called to the struct's stop operation and check for errors*/
void do_stop(struct complex *comp_arr) {

	if (cmd_parts[1] != NULL) {
		printf("Extraneous text after end of command\n");
		return;
	}
	stop();
}

/*remove tabs from given string*/
void  remove_tabs(char* s) {
	int count = 0;
	int i = 0;
	while (s[i]) {
		while (s[i] == '	') { /*go over the string until we get to a char that is not tab*/
			i++;
		}
		s[count++] = s[i++]; /*replace chars in the string*/
		if (s[i] == '	') {
			s[count] = ' ';
			break;
		}	
	}
}

/*remove spaces from given string*/
void  remove_spaces(char* s) {
	int count = 0;
	int i = 0;
	while (s[i]) {
		while (s[i] == ' ') { /*go over the string until we get to a char that is not space*/
			i++;
		}
		s[count++] = s[i++]; /*replace chars in the string*/
		if (s[i] == '	') {
			s[count] = ' ';
			break;
		}
	}
}