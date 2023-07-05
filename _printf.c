#include "main.h"
#include <stdio.h>
#include <stdarg.h>

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */

int _printf(const char *format, ...)
{
	va_list args;

	va_start(args, format);

	char buffer[100];
	int buff_ind = 0;
	int length = 0;

	for (int i = 0; format[i] != '\0'; i++)
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '%')
			{
				buffer[buff_ind++] = '%';
				i++;
			}
			else if (format[i + 1] == 'c')
			{
				char c = (char)va_arg(args, int);

				buffer[buff_ind++] = c;
				i++;
			}
			else if (format[i + 1] == 's')
			{
				const char *s = va_arg(args, const char*);

				for (int j = 0; s[j] != '\0'; j++)
				{
					buffer[buff_ind++] = s[j];
				}
				i++;
			}
			else
			{
				buffer[buff_ind++] = '%';
			}
		}
		else
		{
			buffer[buff_ind++] = format[i];
		}
		if (buff_ind >= 100 || format[i + 1] == '\0')
		{
			print_buffer(buffer, &buff_ind);
			length += buff_ind;
		}
	}
	va_end(args);
	return (length);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	for (int i = 0; i < *buff_ind; i++)
	{
		putchar(buffer[i]);
	}
	*buff_ind = 0;
}
