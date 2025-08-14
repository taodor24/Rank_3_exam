#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int ft_scanf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    int count = 0;
    int c;

    while (*format)
    {
        if (*format == '%')
        {
            format++;
            if (*format == 'd')
            {
                int *p = va_arg(args, int*);
                int num = 0, sign = 1;
                
                while (isspace(c = fgetc(stdin)));
                if (c == '-') { sign = -1; c = fgetc(stdin); }
                if (!isdigit(c)) return count;
                
                do { num = num * 10 + (c - '0'); } while (isdigit(c = fgetc(stdin)));
                if (c != EOF) ungetc(c, stdin);
                
                *p = num * sign;
                count++;
            }
            else if (*format == 's')
            {
                char *p = va_arg(args, char*);
                while (isspace(c = fgetc(stdin)));
                if (c == EOF) return count;
                
                do { *p++ = c; } while ((c = fgetc(stdin)) != EOF && !isspace(c));
                if (c != EOF) ungetc(c, stdin);
                *p = '\0';
                count++;
            }
            else if (*format == 'c')
            {
                char *p = va_arg(args, char*);
                c = fgetc(stdin);
                if (c == EOF) return count;
                *p = c;
                count++;
            }
            else return count; // unsupported format
        }
        else
        {
            // pass spaces and number match CHECK
            c = fgetc(stdin);
            if (c != *format) return count;
        }
        format++;
    }

    va_end(args);
    return count;
}


/////////////////////////////////////////////////////////////////////////////////////
//     MAIN:
#include <stdio.h>

int ft_scanf(const char *format, ...);

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
