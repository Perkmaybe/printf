#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list args, char buffer[], int *buff_ind,
		int flags, int width, int precision, int size)
{
	int num = va_arg(args, int);

	char num_str[100];
	int digit;
	int i;
	int j;
	int num_ind = 0;
	int neg = 0;

	if (num < 0)
	{
		neg = 1;
		num = -num;
	}
	while (num != 0)
	{
		digit = num % 10;
		num_str[num_ind++] = '0' + digit;
		num /= 10;
	}
	while (num_ind < precision)
	{
		num_str[num_ind++] = '0';
	}
	if (neg)
		num_str[num_ind++] = '-';

	while (num_ind < width)
		num_str[num_ind++] = flags & 2 ? '0' : ' ';

	for (i = 0, j = num_ind - 1; i < j; i++, j--)
	{
		char temp = num_str[i];

		num_str[i] = num_str[j];
		num_str[j] = temp;
	}
	for (i = 0; i < num_ind; i++)
		buffer[(*buff_ind)++] = num_str[i];
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
