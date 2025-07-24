#include <stdarg.h>
#include <ctype.h>
#include <stdio.h>

int ft_scanf(const char *fmt, ...)
{
    va_list args;
    int count = 0, ch;

    va_start(args, fmt);

    while (*fmt)
    {
        if (*fmt == '%' && *(fmt + 1))
        {
            fmt++;
            if (*fmt == 'd') {
                int *n = va_arg(args, int *);
                int sign = 1, val = 0;

                while (isspace(ch = fgetc(stdin)));

                if (ch == '-') {
                    sign = -1;
                    ch = fgetc(stdin);
                }

                while (isdigit(ch)) {
                    val = val * 10 + (ch - '0');
                    ch = fgetc(stdin);
                }

                ungetc(ch, stdin);
                *n = val * sign;
                count++;
            }
            else if (*fmt == 's') {
                char *s = va_arg(args, char *);

                while (isspace(ch = fgetc(stdin)));

                do {
                    *s++ = ch;
                    ch = fgetc(stdin);
                } while (!isspace(ch) && ch != EOF);

                *s = '\0';
                if (ch != EOF)
                    ungetc(ch, stdin);
                count++;
            }
            else if (*fmt == 'c') {
                char *c = va_arg(args, char *);
                while (isspace(ch = fgetc(stdin))); // <--- добавлено
                *c = ch;
                count++;
            }
        }
        fmt++;
    }

    va_end(args);
    return count;
}




#include <stdio.h>
int main(void)
{
    int num;
    char c;
    char str[100];

    ft_scanf("%d %c %s", &num, &c, str);

    printf("num = %d\n", num);
    printf("char = %c\n", c);
    printf("str = %s\n", str);
    return 0;
}
