#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int ft_scanf(const char *format, ...)
{
    va_list ap;
    int count = 0, c;

    va_start(ap, format);
    while (*format)
    {
        if (*format == '%')
        {
            format++;
            if (*format == 'd')
            {
                int *n = va_arg(ap, int*);
                int sign = 1, val = 0;

                while (isspace(c = fgetc(stdin)));
                if (c == '-' || c == '+') { if (c == '-') sign = -1; c = fgetc(stdin); }
                if (!isdigit(c)) return count; 
                do { val = val * 10 + (c - '0'); } while (isdigit(c = fgetc(stdin)));
                if (c != EOF) ungetc(c, stdin);
                *n = val * sign;
                count++;
            }
            else if (*format == 's')
            {
                char *s = va_arg(ap, char*);
                while (isspace(c = fgetc(stdin)));
                if (c == EOF) return count;
                do { *s++ = c; } while ((c = fgetc(stdin)) != EOF && !isspace(c));
                if (c != EOF) ungetc(c, stdin);
                *s = '\0';
                count++;
            }
            else if (*format == 'c')
            {
                char *ch = va_arg(ap, char*);
                if ((c = fgetc(stdin)) == EOF) return count;
                *ch = c;
                count++;
            }
        }
        format++;
    }
    va_end(ap);
    return count;
}




//     MAIN:

#include <stdio.h>

int main() {
    int num;
    char c;
    char str[100];

    printf("Enter a NUMBER, SYMBOL and a WORD: ");
    int res = ft_scanf("%d %c %s", &num, &c, str);

    printf("\nft_scanf returned: %d\n", res);
    printf("Read NUMBER: %d\n", num);
    printf("Read SYMBOL: %c\n", c);
    printf("Read WORD: %s\n", str);

    return 0;
}


