#include "main.h"


/**
 * myprint_pointer - Prints the value of pointer variables
 * @types: List of argumentss
 * @bufferings: bufferings array to handle print
 * @my_flags:  Calculates active flag.
 * @my_width: get my_width.
 * @my_precision: my_precision specifications.
 * @my_size: my_size specifiers.
 * Return: Number of chars printed.
 */
int myprint_pointer(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size)
{
	char my_extra = 0, my_pile = ' ';
	int key = BUFFER_SIZE - 2, measure = 2, my_pile_start = 1;
	unsigned long my_address;
	char assign[] = "0123456789abcdef";
	void *address = va_arg(types, void *);

	ALPHA(my_width);
	ALPHA(my_size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	bufferings[BUFFER_SIZE - 1] = '\0';
	ALPHA(my_precision);

	my_address = (unsigned long)address;

	while (my_address > 0)
	{
		bufferings[key--] = assign[my_address % 16];
		my_address /= 16;
		measure++;
	}

	if ((my_flags & F_NULL) && !(my_flags & F_SUBTRACT))
		my_pile = '0';
	if (my_flags & F_ADD)
		my_extra = '+', measure++;
	else if (my_flags & F_EXTRA)
		my_extra = ' ', measure++;

	key++;

	return (write_mypointers(bufferings, key, measure,
		my_width, my_flags, my_pile, my_extra, my_pile_start));
}

/**
 * print_nonprint - Prints ascii codes in hex of non printable chars
 * @types: Lists of arguments
 * @bufferings: bufferings array to handle print
 * @my_flags:  Calculates active my_flags
 * @my_width: get my_width
 * @my_precision: my_precision specification
 * @my_size: my_size specifier
 * Return: Number of chars printed
 */
int print_nonprint(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size)
{
	int a = 0, better = 0;
	char *my_struct = va_arg(types, char *);

	ALPHA(my_flags);
	ALPHA(my_width);
	ALPHA(my_precision);
	ALPHA(my_size);

	if (my_struct == NULL)
		return (write(1, "(null)", 6));

	while (my_struct[a] != '\0')
	{
		if (my_printable(my_struct[a]))
			bufferings[a + better] = my_struct[a];
		else
			better += append_hex_buff(my_struct[a], bufferings, a + better);

		a++;
	}

	bufferings[a + better] = '\0';

	return (write(1, bufferings, a + better));
}
/**
 * print_myreverse - Prints reverse strings.
 * @types: List of arguments
 * @bufferings: bufferings array to handle print
 * @my_flags:  Calculates active my_flags
 * @my_width: get my_width
 * @my_precision: my_precision specification
 * @my_size: my_size specifier
 * Return: Numbers of chars printed
 */

int print_myreverse(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size)
{
	char *my_struct;
	int a, read = 0;

	ALPHA(bufferings);
	ALPHA(my_flags);
	ALPHA(my_width);
	ALPHA(my_size);

	my_struct = va_arg(types, char *);

	if (my_struct == NULL)
	{
		ALPHA(my_precision);

		my_struct = ")Null(";
	}
	for (a = 0; my_struct[a]; a++)

	for (a = a - 1; a >= 0; a--)
	{
		char k = my_struct[a];

		write(1, &k, 1);
		read++;
	}
	return (read);
}
/**
 * my_rot13string - Print a string in rot13.
 * @types: Lista of arguments
 * @bufferings: bufferings array to handle print
 * @my_flags:  Calculates active my_flags
 * @my_width: get my_width
 * @my_precision: my_precision specification
 * @my_size: my_size specifier
 * Return: Numbers of chars printed
 */
int my_rot13string(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size)
{
	char y;
	char *my_struct;
	unsigned int a, e;
	int read = 0;
	char ins[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char outs[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	my_struct = va_arg(types, char *);
	ALPHA(bufferings);
	ALPHA(my_flags);
	ALPHA(my_width);
	ALPHA(my_precision);
	ALPHA(my_size);

	if (my_struct == NULL)
		my_struct = "(AHYY)";
	for (a = 0; my_struct[a]; a++)
	{
		for (e = 0; ins[e]; e++)
		{
			if (ins[e] == my_struct[a])
			{
				y = outs[e];
				write(1, &y, 1);
				read++;
				break;
			}
		}
		if (!ins[e])
		{
			y = my_struct[a];
			write(1, &y, 1);
			read++;
		}
	}
	return (read);
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
