#include "main.h"

void printf_bufferings(char buffering[], int *buffer_print);

/**
 * _printf - Printf function
 * @format: format.
 * Return: toprint chars.
 */
int _printf(const char *format, ...)
{
	int a, toprint = 0, toprint_chars = 0;
	int my_flags, my_width, my_precision, my_size, buffer_print = 0;
	va_list list;
	char buffering[BUFFER_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (a = 0; format && format[a] != '\0'; a++)
	{
		if (format[a] != '%')
		{
			buffering[buffer_print++] = format[a];
			if (buffer_print == BUFFER_SIZE)
				printf_bufferings(buffering, &buffer_print);

			toprint_chars++;
		}
		else
		{
			printf_bufferings(buffering, &buffer_print);
			my_width = get_my_width(format, &a, list);
			my_size = get_my_size(format, &a);
			my_precision = get_my_precision(format, &a, list);
			my_flags = get_my_flag(format, &a);		
			++a;
			toprint = handle_myprint(format, &a, list, buffering,
				my_flags, my_width, my_precision, my_size);
			if (toprint == -1)
				return (-1);
			toprint_chars = toprint_chars + toprint;
		}
	}

	printf_bufferings(buffering, &buffer_print);

	va_end(list);

	return (toprint_chars);
}

/**
 * printf_bufferings - Prints the contents of the buffering if it exist
 * @buffering: Array of characters
 * @buffer_print: Index at which to add next char, represents the length.
 */
void printf_bufferings(char buffering[], int *buffer_print)
{
	if (*buffer_print > 0)
		write(1, &buffering[0], *buffer_print);

	*buffer_print = 0;
}
