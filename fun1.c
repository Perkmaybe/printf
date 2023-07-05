#include "main.h"
/*
 * This function is a recursive helper function for printing unsigned integers.
 * It takes an unsigned long integer 'num',
 * a character buffer 'buffer', and a pointer to an integer 'i'.
 * The function recursively divides 'num' by 10 until it reaches zero.
 * During each recursive call, it appends the last digit
 * (obtained using modulo division by 10) to the buffer
 * and increments the buffer index 'i' by one.
 * This process effectively stores the digits of the
 * number in reverse order in the buffer.
 */
void print_unsigned_recursive(unsigned long int num, char buffer[], int *i)
{
	if (num == 0)
		return;

	else
	{
		print_unsigned_recursive(num / 10, buffer, i);
		buffer[(*i)++] = (num % 10) + '0';
	}
}

/*
 * This function prints an unsigned integer using the %u conversion specifier.
 * It takes a 'va_list' argument 'types', a character buffer 'buffer',
 * and the flags, width, precision, and size parameters.
 * Inside the function, the unsigned long integer argument
 * is extracted from 'types' using 'va_arg' and stored in 'num'.
 * The 'convert_size_unsgnd' function is used to handle the length
 * modifier ('size') for the number.
 *
 * The function initializes the buffer index 'i' to 'BUFF_SIZE - 2',
 * where 'BUFF_SIZE' is the size of the buffer array.
 * It sets the last element of the buffer to a
 * null character to ensure proper termination.
 *
 * Next, it checks if the number is zero. If so, it directly stores the
 * character '0' in the buffer and decrements the buffer index 'i' by one.
 * Otherwise, it calls the 'print_unsigned_recursive' function to
 * store the digits of the number in the buffer using recursion.
 *
 * Finally, it increments the buffer index 'i' to the correct position
 * and returns the result of the 'write_unsgnd' function,
 * which is responsible for writing the formatted output based on
 * the provided flags, width, precision, and size.
 */
int print_unsigned(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	int i = BUFF_SIZE - 2;

	buffer[BUFF_SIZE - 1] = '\0';

	if (num == 0)
		buffer[i--] = '0';

	else
		print_unsigned_recursive(num, buffer, &i);

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_octal(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
				flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
				flags, 'X', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * Prints a hexadecimal number based on the provided arguments.
 *
 * @param types    The variadic argument list
 * @param map_to    The array mapping hexadecimal digits (0-15) to characters
 * @param buffer    The output buffer to store the printed characters
 * @param flags     The formatting flags
 * @param flag_ch   The flag character for prefixing the hexadecimal number
 * @param width     The width of the output field
 * @param precision The precision for formatting the output
 * @param size      The length modifier for the number
 * @return The number of characters printed
 */
int print_hexa(va_list types, char map_to[], char buffer[], int flags,
		char flag_ch, int width, int precision, int size)
{
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	int i = BUFF_SIZE - 2;

	int digit;

	buffer[BUFF_SIZE - 1] = '\0';

	if (num == 0)
		buffer[i--] = '0';

	else
	{
		while (num > 0)
		{
			digit = num % 16;

			buffer[i--] = map_to[digit];

			num /= 16;
		}
	}
	if (flags & F_HASH && num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
