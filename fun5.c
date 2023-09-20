#include "main.h"

/**
 * write_mychar - Prints a string
 * @c: char types.
 * @bufferings: bufferings array to handle print
 * @my_flags:  Calculates active my_flags.
 * @my_width: get my_width.
 * @my_precision: my_precision specifier
 * @my_size: my_size specifier
 *
 * Return: Number of chars printed.
 */
int write_mychar(char b, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size)
{
	int a = 0;
	char my_pile = ' ';

	ALPHA(my_precision);
	ALPHA(my_size);

	if (my_flags & F_NULL)
		my_pile = '0';

	bufferings[a++] = b;
	bufferings[a] = '\0';

	if (my_width > 1)
	{
		bufferings[BUFFER_SIZE - 1] = '\0';
		for (a = 0; a < my_width - 1; a++)
			bufferings[BUFFER_SIZE - a - 2] = my_pile;

		if (my_flags & F_SUBTRACT)
			return (write(1, &bufferings[0], 1) +
					write(1, &bufferings[BUFFER_SIZE - a - 1], my_width - 1));
		else
			return (write(1, &bufferings[BUFFER_SIZE - a - 1], my_width - 1) +
					write(1, &bufferings[0], 1));
	}

	return (write(1, &bufferings[0], 1));
}

/**
 * write_mynumber - Prints a string
 * @just_negative: Lista of arguments
 * @find: char types.
 * @bufferings: bufferings array to handle print
 * @my_flags:  Calculates active my_flags
 * @my_width: get my_width.
 * @my_precision: my_precision specifier
 * @my_size: my_size specifier
 *
 * Return: Number of chars printed.
 */
int write_mynumber(int just_negative, int find, char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size)
{
	int measure = BUFFER_SIZE - find - 1;
	char my_pile = ' ', delight = 0;

	ALPHA(my_size);

	if ((my_flags & F_NULL) && !(my_flags & F_SUBTRACT))
		my_pile = '0';
	if (just_negative)
		delight = '-';
	else if (my_flags & F_ADD)
		delight = '+';
	else if (my_flags & F_EXTRA)
		delight = ' ';

	return (write_mynum(find, bufferings, my_flags, my_width, my_precision,
		measure, my_pile, delight));
}

/**
 * write_mynum - Write a number using a buffer
 * @find: Index at which the number starts on the bufferings
 * @bufferings: bufferings
 * @my_flags: my_flags
 * @my_width: my_width
 * @prec: my_precision specifier
 * @measure: Number measure
 * @my_pile: Pading char
 * @my_extra: Extra char
 *
 * Return: Number of printed chars.
 */
int write_mynum(int find, char bufferings[],
	int my_flags, int my_width, int my_precision,
	int measure, char my_pile, char my_extra)
{
	int a, my_pile_start = 1;

	if (my_precision == 0 && find == BUFFER_SIZE - 2 && bufferings[find] == '0' && my_width == 0)
		return (0);
	if (my_precision == 0 && find == BUFFER_SIZE - 2 && bufferings[find] == '0')
		bufferings[find] = my_pile = ' ';
	if (my_precision > 0 && my_precision < measure)
		my_pile = ' ';
	while (my_precision > measure)
		bufferings[--find] = '0', measure++;
	if (my_extra != 0)
		measure++;
	if (my_width > measure)
	{
		for (a = 1; a < my_width - measure + 1; a++)
			bufferings[a] = my_pile;
		bufferings[a] = '\0';
		if (my_flags & F_SUBTRACT && my_pile == ' ')
		{
			if (my_extra)
				bufferings[--find] = my_extra;
			return (write(1, &bufferings[find], measure) + write(1, &bufferings[1], a - 1));
		}
		else if (!(my_flags & F_SUBTRACT) && my_pile == ' ')
		{
			if (my_extra)
				bufferings[--find] = my_extra;
			return (write(1, &bufferings[1], a - 1) + write(1, &bufferings[find], measure));
		}
		else if (!(my_flags & F_SUBTRACT) && my_pile == '0')
		{
			if (my_extra)
				bufferings[--my_pile_start] = my_extra;
			return (write(1, &bufferings[my_pile_start], a - my_pile_start) +
				write(1, &bufferings[find], measure - (1 - my_pile_start)));
		}
	}
	if (my_extra)
		bufferings[--find] = my_extra;
	return (write(1, &bufferings[find], measure));
}
/**
 * write_unsigned - Writes an unsigned number
 * @just_negative: Number indicating if the num is negative
 * @find: Index at which the number starts in the bufferings
 * @bufferings: Array of chars
 * @my_flags: my_flags specifiers
 * @my_width: my_width specifier
 * @my_precision: my_precision specifier
 * @my_size: my_size specifier
 *
 * Return: Number of written chars.
 */
int write_unsigned(int just_negative, int find,
	char bufferings[],
	int my_flags, int my_width, int my_precision, int my_size)
{
	int measure = BUFFER_SIZE - find - 1, a = 0;
	char my_pile = ' ';

	ALPHA(just_negative);
	ALPHA(my_size);

	if (my_precision == 0 && find == BUFFER_SIZE - 2 && bufferings[find] == '0')
		return (0);

	if (my_precision > 0 && my_precision < measure)
		my_pile = ' ';

	while (my_precision > measure)
	{
		bufferings[--find] = '0';
		measure++;
	}

	if ((my_flags & F_NULL) && !(my_flags & F_SUBTRACT))
		my_pile = '0';

	if (my_width > measure)
	{
		for (a = 0; a < my_width - measure; a++)
			bufferings[a] = my_pile;

		bufferings[a] = '\0';

		if (my_flags & F_SUBTRACT)
		{
			return (write(1, &bufferings[find], measure) + write(1, &bufferings[0], a));
		}
		else
		{
			return (write(1, &bufferings[0], a) + write(1, &bufferings[find], measure));
		}
	}

	return (write(1, &bufferings[find], measure));
}

/**
 * write_mypointers - Write a memory address
 * @bufferings: Arrays of chars
 * @find: Index at which the number starts in the bufferings
 * @measure: measure of number
 * @my_width: my_width specifier
 * @my_flags: my_flags specifier
 * @my_pile: Char representing the my_pileing
 * @my_extra: Char representing extra char
 * @my_pile_start: Index at which my_pileing should start
 *
 * Return: Number of written chars.
 */
int write_mypointers(char bufferings[], int find, int measure,
	int my_width, int my_flags, char my_pile, char my_extra, int my_pile_start)
{
	int a;

	if (my_width > measure)
	{
		for (a = 3; a < my_width - measure + 3; a++)
			bufferings[a] = my_pile;
		bufferings[a] = '\0';
		if (my_flags & F_SUBTRACT && my_pile == ' ')
		{
			bufferings[--find] = 'x';
			bufferings[--find] = '0';
			if (my_extra)
				bufferings[--find] = my_extra;
			return (write(1, &bufferings[find], measure) + write(1, &bufferings[3], a - 3));
		}
		else if (!(my_flags & F_SUBTRACT) && my_pile == ' ')
		{
			bufferings[--find] = 'x';
			bufferings[--find] = '0';
			if (my_extra)
				bufferings[--find] = my_extra;
			return (write(1, &bufferings[3], a - 3) + write(1, &bufferings[find], measure));
		}
		else if (!(my_flags & F_SUBTRACT) && my_pile == '0')
		{
			if (my_extra)
				bufferings[--my_pile_start] = my_extra;
			bufferings[1] = '0';
			bufferings[2] = 'x';
			return (write(1, &bufferings[my_pile_start], a - my_pile_start) +
				write(1, &bufferings[find], measure - (1 - my_pile_start) - 2));
		}
	}
	bufferings[--find] = 'x';
	bufferings[--find] = '0';
	if (my_extra)
		bufferings[--find] = my_extra;
	return (write(1, &bufferings[find], BUFFER_SIZE - find - 1));
}
