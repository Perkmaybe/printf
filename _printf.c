#include "main.h"
#include <stdio.h>
#include <stdarg.h>

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */

int _printf(const char *format, ...)
{
	va_list args;

	va_start(args, format);

	int length = vprintf(format, args);

	va_end(args);
	return (length);
}
