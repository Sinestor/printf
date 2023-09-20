#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define ALPHA(x) (void)(x)
#define BUFFER_SIZE 1024
#define F_SUBTRACT 1
#define F_ADD 2
#define F_NULL 4
#define F_APPREND 8
#define F_EXTRA 16

#define S_BIG 2
#define S_SMALL 1

struct fume
{
	char fume;
	int (*fn)(va_list, char[], int, int, int, int);
};

typedef struct fume fume_t;

int _printf(const char *format, ...);
int print_characters(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size);
int strings_print(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size);
int percent_prints(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size);
int print_integer(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size);
int binary_prints(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size);
int print_unsignednum(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size);
int print_octate(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size);
int print_hexadeci(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size);
int print_hex_upperdec(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size);
int print_hex(va_list types, char assign[], char bufferings[],
	int my_flags, char flagx, int my_width, int my_precision, int my_size);
int print_nonprint(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size);
int myprint_pointer(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size);
int my_rot13string(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size);
int print_myreverse(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size);
int get_my_flag(const char *format, int *a);
int get_my_width(const char *format, int *a, va_list list);
int get_my_precision(const char *format, int *a, va_list list);
int get_my_size(const char *format, int *a);
int handle_myprint(const char *fume, int *find, va_list list,char bufferings[],int my_flags, int my_width, int my_precision, int my_size);
int write_mychar(char b, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size);
int write_mynumber(int just_negative, int find, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size);
int write_mynum(int find, char bufferings[], int my_flags, int my_width, 
int my_precision, int measure, char my_pile, char my_extra);
int write_mypointers(char bufferings[], int find, int measure,
	int my_width, int my_flags, char my_pile, char my_extra, int my_pile_start);
int write_unsigned(int just_negative, int find, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size);
int my_printable(char b);
int append_hex_buff(char ascii_mycode, char bufferings[], int a);
int my_digit(char b);
long int convert_mynumber(long int digit, int my_size);
long int convert_myunsigned(unsigned long int digit, int my_size);

#endif
