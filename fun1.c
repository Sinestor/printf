#include "main.h"

/**
 * print_characters - Prints a character
 * @types: List of arguments
 * @bufferings: bufferings array to handle prints
 * @myf:  Calculate active my_flags
 * @myw: Calc my_width
 * @myp: my_precision specifications
 * @mys: my_size specifier
 * Return: Number of chars printed
 */
int print_characters(va_list types, char bufferings[],
	int myf, int myw, int myp, int mys)
{
	char b = va_arg(types, int);

	return (write_mychar(b, bufferings, myf, myw, myp, mys));
}

/**
 * strings_print - Prints a string
 * @types: List of arguments
 * @bufferings: bufferings array to handle print
 * @my_flags:  Cal active my_flags’
 * @my_width: get my_width..
 * @my_precision: my_precision specifications.
 * @my_size: my_size specifiers.
 * Return: Num of chars printed.
 */
int strings_print(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size)
{
	int measure = 0, a;
	char *my_struct = va_arg(types, char *);

	ALPHA(bufferings);
	ALPHA(my_flags);
	ALPHA(my_width);
	ALPHA(my_precision);
	ALPHA(my_size);
	if (my_struct == NULL)
	{
		my_struct = "(null)";
		if (my_precision >= 6)
			my_struct = "      ";
	}

	while (my_struct[measure] != '\0')
		measure++;

	if (my_precision >= 0 && my_precision < measure)
		measure = my_precision;

	if (my_width > measure)
	{
		if (my_flags & F_SUBTRACT)
		{
			write(1, &my_struct[0], measure);
			for (a = my_width - measure; a > 0; a--)
				write(1, " ", 1);
			return (my_width);
		}
		else
		{
			for (a = my_width - measure; a > 0; a--)
				write(1, " ", 1);
			write(1, &my_struct[0], measure);
			return (my_width);
		}
	}

	return (write(1, my_struct, measure));
}

/**
 * percent_prints - Prints a percent sign.
 * @types: Lista of arguments.
 * @bufferings: bufferings array to handle print.
 * @my_flags:  Calculate active my_flags.
 * @my_width: get my_width.
 * @my_precision: my_precision specifications.
 * @my_size: my_size specifiers.
 * Return: Number of chars printed
 */
int percent_prints(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size)
{
	ALPHA(types);
	ALPHA(bufferings);
	ALPHA(my_flags);
	ALPHA(my_width);
	ALPHA(my_precision);
	ALPHA(my_size);
	return (write(1, "%%", 1));
}

/**
 * print_integer - Print int
 * @types: List of arguments.
 * @bufferings: bufferings array to handle print.
 * @myf:  Calculates active my_flags
 * @myw: get my_width..
 * @myp: my_precision specifications.
 * @mys: my_size specifiers.
 * Return: Numbers of chars printed.
 */
int print_integer(va_list types, char bufferings[],
	int myf, int myw, int myp, int mys)
{
	int a = BUFFER_SIZE - 2;
	int just_negative = 0;
	long int j = va_arg(types, long int);
	unsigned long int digit;

	j = convert_mynumber(j, mys);

	if (j == 0)
		bufferings[a--] = '0';

	bufferings[BUFFER_SIZE - 1] = '\0';
	digit = (unsigned long int)j;
	if (j < 0)
	{
		digit = (unsigned long int)((-1) * j);
		just_negative = 1;
	}
	while (digit > 0)
	{
		bufferings[a--] = (digit % 10) + '0';
		digit /= 10;
	}
a++;

return (write_mynumber(just_negative, a, bufferings, myf, myw, myp, mys));
}

/**
 * binary_prints - Prints unsigned numbers
 * @types: Lists of arguments
 * @bufferings: bufferings array to handle prints
 * @my_flags:  Calculates active flag
 * @my_width: get my_width
 * @my_precision: my_precision specifications
 * @my_size: my_size specifiers
 * Return: Numbers of char printed
 */
int binary_prints(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size)
{
	int read;
unsigned int j, a, p, add;
	unsigned int x[32];

	ALPHA(bufferings);
	ALPHA(my_flags);
	ALPHA(my_width);
	ALPHA(my_precision);
	ALPHA(my_size);

	j = va_arg(types, unsigned int);
	p = 2147483648; /* (2 ^ 31) */
	x[0] = j / p;
	for (a = 1; a < 32; a++)
	{
		p /= 2;
		x[a] = (j / p) % 2;
	}
	for (add = 0, a = 0, read = 0; a < 32; a++)
	{
		add = add + x[a];
		if (add || a == 31)
		{
			char k = '0' + x[a];

			write(1, &k, 1);
			read++;
		}
	}
	return (read);
}
