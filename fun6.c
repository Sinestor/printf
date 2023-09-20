
#include "main.h"

/**
 * get_my_flag - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @a: take a parameter.
 * Return: Flags:
 */
int get_my_flag(const char *format, int *a)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int e, curr_a;
	int my_flags = 0;
	const char F_TEXT[] = {'-', '+', '0', '#', ' ', '\0'};
	const int F_VALUE[] = {F_SUBTRACT, F_ADD, F_NULL, F_APPREND, F_EXTRA, 0};

	for (curr_a = *a + 1; format[curr_a] != '\0'; curr_a++)
	{
		for (e = 0; F_TEXT[e] != '\0'; e++)
			if (format[curr_a] == F_TEXT[e])
			{
				my_flags |= F_VALUE[e];
				break;
			}

		if (F_TEXT[e] == 0)
			break;
	}

	*a = curr_a - 1;

	return (my_flags);
}

/**
 * get_my_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @a: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int get_my_precision(const char *format, int *a, va_list list)
{
	int curr_a = *a + 1;
	int my_precision = -1;

	if (format[curr_a] != '.')
		return (my_precision);
	my_precision = 0;

	for (curr_a += 1; format[curr_a] != '\0'; curr_a++)
	{
		if (my_digit(format[curr_a]))
		{
			my_precision *= 10;
			my_precision += format[curr_a] - '0';
		}
		else if (format[curr_a] == '*')
		{
			curr_a++;
			my_precision = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*a = curr_a - 1;
	return (my_precision);
}

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_my_size(const char *format, int *a)
{
	int curr_a = *a + 1;
	int my_size = 0;

	if (format[curr_a] == 'l')
		my_size = S_BIG;
	else if (format[curr_a] == 'h')
		my_size = S_SMALL;

	if (my_size == 0)
		*a = curr_a - 1;
	else
		*a = curr_a;

	return (my_size);
}


/**
 * get_my_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @a: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_my_width(const char *format, int *a, va_list list)
{
	int curr_a;
	int my_width = 0;

	for (curr_a = *a + 1; format[curr_a] != '\0'; curr_a++)
	{
		if (my_digit(format[curr_a]))
		{
			my_width *= 10;
			my_width += format[curr_a] - '0';
		}
		else if (format[curr_a] == '*')
		{
			curr_a++;
			my_width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*a = curr_a - 1;

	return (my_width);
}
