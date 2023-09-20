
#include "main.h"

/**
 * my_printable - Evaluates if a char is printable
 * @c: Char to be evaluated.
 *
 * Return: 1 if c is printable, 0 otherwise
 */
int my_printable(char b)
{
	if (b >= 32 && b < 127)
		return (1);
	return (0);
}


#include "main.h"

/**
 * append_hex_buff - Append ascci in hex code to bufferings
 * @bufferings: Array of chars.
 * @i: Index at which to start appending.
 * @ascii_mycode: ASCII CODE.
 * Return: Always 3
 */
int append_hex_buff(char ascii_mycode, char bufferings[], int a)
{
	char assign[] = "0123456789ABCDEF";
	if (ascii_mycode < 0)
		ascii_mycode *= -1;

	bufferings[a++] = '\\';
	bufferings[a++] = 'x';

	bufferings[a++] = assign[ascii_mycode / 16];
	bufferings[a] = assign[ascii_mycode % 16];

	return (3);
}
/**
 * my_digit - Verifies if a char is a digit
 * @b: Char to be evaluated
 *
 * Return: 1 if b is a digit, 0 otherwise
 */
int my_digit(char b)
{
	if (b >= '0' && b <= '9')
		return (1);
	return (0);
}
/**
 * convert_mynumber - Casts a number to the specified my_size
 * @digit: Number to be casted.
 * @my_size: Number indicating the type to be casted.
 *
 * Return: Casted value of digit
 */
long int convert_mynumber(long int digit, int my_size)
{
	if (my_size == S_BIG)
		return (digit);
	else if (my_size == S_SMALL)
		return ((short)digit);

	return ((int)digit);
}


/**
 * convert_myunsigned - Casts a number to the specified my_size
 * @digit: Number to be casted
 * @my_size: Number indicating the type to be casted
 *
 * Return: Casted value of digit
 */
long int convert_myunsigned(unsigned long int digit, int my_size)
{
	if (my_size == S_BIG)
		return (digit);
	else if (my_size == S_SMALL)
		return ((unsigned short)digit);

	return ((unsigned int)digit);
}

/**
 * handle_print - Prints an argument based on its type
 * @fume: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @find: find.
 * @buffer: Buffer array to handle print.
 * @my_flags: Calculates active my_flags
 * @my_width: get my_width.
 * @precision: Precision specification
 * @my_size: my_size specifier
 * Return: 1 or 2;
 */

int handle_myprint(const char *fume, int *find, va_list list, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size)
{
	int a, myhandler = 0,myhead = -1;
	fume_t fume_types[] = {
		{'c', print_characters}, {'s', strings_print}, {'%', percent_prints},
		{'i', print_integer}, {'d', print_integer}, {'b', binary_prints},
		{'u', print_unsignednum}, {'o', print_octate}, {'x', print_hexadeci},
		{'X', print_hex_upperdec}, {'p', myprint_pointer}, {'S', print_nonprint},
		{'r', print_myreverse}, {'R', my_rot13string}, {'\0', NULL}
	};
	for (a = 0; fume_types[a].fume != '\0'; a++)
		if (fume[*find] == fume_types[a].fume)
			return (fume_types[a].fn(list, bufferings, my_flags, my_width, my_precision, my_size));

	if (fume_types[a].fume == '\0')
	{
		if (fume[*find] == '\0')
			return (-1);
		myhandler += write(1, "%%", 1);
		if (fume[*find - 1] == ' ')
			myhandler += write(1, " ", 1);
		else if (my_width)
		{
			--(*find);
			while (fume[*find] != ' ' && fume[*find] != '%')
				--(*find);
			if (fume[*find] == ' ')
				--(*find);
			return (1);
		}
		myhandler += write(1, &fume[*find], 1);
		return (myhandler);
	}
	return (myhead);
}
