#include "main.h"

/**
 * print_unsignednum - Prints unsigned numbers.
 * @types: Lists of arguments.
 * @bufferings: bufferings array to handle prints.
 * @my_flags:  Calculates active flag.
 * @my_width: get my_width.
 * @my_pr: my_precision specifications.
 * @my_size: my_size specifiers.
 * Return: Numbers of chars printed.
 */
int print_unsignednum(va_list types, char bufferings[],
	int my_flags, int my_width, int my_pr, int my_size)
{
	int a = BUFFER_SIZE - 2;
	unsigned long int digit = va_arg(types, unsigned long int);

	digit = convert_myunsigned(digit, my_size);

	if (digit == 0)
		bufferings[a--] = '0';

	bufferings[BUFFER_SIZE - 1] = '\0';

	while (digit > 0)
	{
		bufferings[a--] = (digit % 10) + '0';
		digit /= 10;
	}

	a++;

	return (write_unsigned(0, a, bufferings, my_flags, my_width, my_pr, my_size));
}

/**
 * print_octate - Prints unsigned numbers in octal notation.
 * @types: Lists of arguments.
 * @bufferings: bufferings array to handle print.
 * @my_flags:  Calculates active flag.
 * @my_width: get my_width.
 * @my_pr: my_precision specifications
 * @my_size: my_size specifiers.
 * Return: Number of chars printed.
 */
int print_octate(va_list types, char bufferings[],
	int my_flags, int my_width, int my_pr, int my_size)
{
	int a = BUFFER_SIZE - 2;
	unsigned long int digit = va_arg(types, unsigned long int);
	unsigned long int init_digit = digit;

	ALPHA(my_width);

	digit = convert_myunsigned(digit, my_size);

	if (digit == 0)
		bufferings[a--] = '0';

	bufferings[BUFFER_SIZE - 1] = '\0';

	while (digit > 0)
	{
		bufferings[a--] = (digit % 8) + '0';
		digit /= 8;
	}

	if (my_flags & F_APPREND && init_digit != 0)
		bufferings[a--] = '0';

	a++;

	return (write_unsigned(0, a, bufferings, my_flags, my_width, my_pr, my_size));
}

/**
 * print_hexadeci - Prints unsigned number in hexadecimal notation.
 * @types: Lists of arguments.
 * @bufferings: bufferings array to handle print.
 * @my_flags:  Calculates active flag.
 * @my_width: get my_width.
 * @my_precision: my_precision specifications.
 * @my_size: my_size specifiers.
 * Return: Number of chars printed.
 */
int print_hexadeci(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size)
{
	return (print_hex(types, "0123456789abcdef", bufferings,
		my_flags, 'x', my_width, my_precision, my_size));
}

/**
 * print_hex_upperdec - Prints unsigned numbers in upper hexadecimal.
 * @types: Lists of arguments.
 * @bufferings: bufferings array to handle print.
 * @my_flags:  Calculates active flag.
 * @my_width: get my_width.
 * @my_precision: my_precision specifications.
 * @my_size: my_size specifiers.
 * Return: Number of chars printeds.
 */
int print_hex_upperdec(va_list types, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size)
{
	return (print_hex(types, "0123456789ABCDEF", bufferings,
		my_flags, 'X', my_width, my_precision, my_size));
}

/**
 * print_hex - Prints a hexadecimal number in lower or upper.
 * @types: Lists of arguments.
 * @Assign: Array of values to map the numbers.
 * @bufferings: bufferings array to handle print.
 * @my_flags:  Calculates active my_flags.
 * @flagx: Calculates active my_flags.
 * @my_width: get my_width.
 * @my_pr: my_precision specification.
 * @my_size: my_size specifiers.
 * @my_size: my_size specifications.
 * Return: Number of chars printed.
 */
int print_hex(va_list types, char assign[], char bufferings[],
	int my_flags, char flagx, int my_width, int my_pr, int my_size)
{
	int a = BUFFER_SIZE - 2;
	unsigned long int digit = va_arg(types, unsigned long int);

	ALPHA(my_width);

	digit = convert_myunsigned(digit, my_size);

	if (digit == 0)
		bufferings[a--] = '0';

	bufferings[BUFFER_SIZE - 1] = '\0';

	while (digit > 0)
	{
		bufferings[a--] = assign[digit % 16];
		digit /= 16;
	}

	if (my_flags & F_APPREND && digit != 0)
	{
		bufferings[a--] = flagx;
		bufferings[a--] = '0';
	}

	a++;

	return (write_unsigned(0, a, bufferings, my_flags, my_width, my_pr, my_size));
}
