#include <unistd.h>
#include <stdio.h>

int check(char *s)
{
    int n = 0;
    for (int i=0; s[i]; i++)
    {
        if (s[i]=='(') n++;
        if (s[i]==')')
        {
            if (n) n--;
            else return 0;
        }
    }
    return n==0;
}

int need(char *s)
{
    int o = 0, c = 0;
    for (int i=0; s[i]; i++)
    {
        if (s[i]=='(') o++;
        if (s[i]==')')
        {
            if (o) o--;
            else c++;
        }
    }
    return o + c;
}


void solve(char *s, int fix, int pos, int need) {
    if (fix == need) { if (check(s)) puts(s); return; }
    for (int i = pos; s[i]; i++) {
        char t = s[i];
        if (t == '(' || t == ')') {
            s[i] = ' ';
            solve(s, fix + 1, i + 1, need);
            s[i] = t;
        }
    } // перебираем все возможные варианты удаления минимального числа скобок.
}

int main(int ac, char **av) {
    if (ac == 2)
        solve(av[1], 0, 0, need(av[1]));
}