#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == 's') {
                const char *str = va_arg(args, const char *);
                fputs(str, stdout);
            } else if (*format == 'd') {
                int num = va_arg(args, int);
                printf("%d", num);
            }
            /* Add more format specifiers as needed */
        } else {
            putchar(*format);
        }
        format++;
    }
    
    va_end(args);
}
