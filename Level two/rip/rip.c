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







/*
old version:

#include <unistd.h>
#include <stdio.h>

int calcul(char *s)
{
	int o = 0;
	int c = 0;
	for(int i = 0; s[i]; i++)
	{
		if (s[i] == '(')
			o++;
		else if( s[i] == ')')
		{
			if( o > 0)
				o--;
			else
				c++;
		}
	}
	return o + c;
}
int solve(char *s, int must_fix, int fix, int pos)
{
	if(must_fix == fix && !calcul(s)) { puts(s); return;}
	for (int x = pos; s[x]; x++)
	{
		char t = s[x];
		s[x] = ' '; 
		solve(s, must_fix, fix + 1, x + 1);
	       	s[x] = t;
	}
}
int main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	int must_fix = calcul(av[1]);
	solve(av[1], must_fix, 0, 0);
       return 0;
}       
*/