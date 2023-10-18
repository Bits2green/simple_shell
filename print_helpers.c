#include "shell.h"

int my_snprintf(char *str, size_t size, const char *format, ...)
{
int i;
int written;
va_list args;
int temp;

if (size == 0)
return -1; /*Invalid size*/

va_start(args, format);

written = 0; /*Number of characters written*/

while (*format && size > 1)
{
if (*format == '%')
{
format++; /*Move past '%'*/
if (*format == '\0')
break; /*Incomplete format specifier*/

if (*format == 'c')
{
char c = va_arg(args, int);
*str = c;
str++;
size--;
written++;
}
else if (*format == 's')
{
const char *source = va_arg(args, const char *);
while (*source && size > 1)
{
*str = *source;
str++;
source++;
size--;
written++;
}
}
else if (*format == 'd')
{
int num = va_arg(args, int);
char num_str[12]; /*Sufficient for INT_MIN*/
int len = 0;
if (num == 0)
{
num_str[len++] = '0';
}
else if (num < 0)
{
num_str[len++] = '-';
num = -num;
}
temp = num;
while (temp != 0)
{
num_str[len++] = '0' + (temp % 10);
temp /= 10;
}
for (i = len - 1; i >= 0 && size > 1; i--)
{
*str = num_str[i];
str++;
size--;
written++;
}
}
else
{
/*Unsupported format specifier*/
*str = '%';
str++;
size--;
written++;
if (size == 1)
break;
*str = *format;
str++;
size--;
written++;
}
}
else
{
*str = *format;
str++;
format++;
size--;
written++;
}
format++;
}

/*Null-terminate the string if there's space*/
if (size > 0) *str = '\0';

va_end(args);
return written;
}

void my_putint(int num)
{
char buffer[32];
int len = my_snprintf(buffer, sizeof(buffer), "%d", num);
write(STDOUT_FILENO, buffer, len);
}

void my_putchar(char c)
{
write(STDOUT_FILENO, &c, 1);
}

void my_puts(const char *str)
{
write(STDOUT_FILENO, str, my_strlen(str));
}
