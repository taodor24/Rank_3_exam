#include <unistd.h>
#include <stdlib.h>

int n;

void putnbr(int n)                    
{
    char c;
    if (n >= 10)
        putnbr(n / 10);
    c = n % 10 + '0';
    write(1, &c, 1);
}

void print(int *a)
{
    for (int i = 0; i < n; i++)
    {
        if (i > 0)
            write(1, " ", 1);
        putnbr(a[i]);
    }
    write(1, "\n", 1);
}
////////////////////////////////////////////////////////
int is_safe(int *board, int col, int row)
{
    for (int i = 0; i < col; i++)
        if (board[i] == row || abs(board[i] - row) == abs(i - col))
            return 0;
    return 1;
}

void solve(int *board, int col)
{
    if (col == n)
    {
        print(board);
        return;
    }
    for (int row = 0; row < n; row++)
        if (is_safe(board, col, row))
        {
            board[col] = row;
            solve(board, col + 1);
        }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    n = atoi(argv[1]);
    int board[n];
    solve(board, 0);
    return 0;
}







/*
ANOTHER VERSION:

#include <unistd.h>
#include <stdlib.h>

int n;

int is_safe(int *pos, int col, int row)
{
    for (int i = 0; i < col; i++)
        if (pos[i] == row || abs(pos[i] - row) == abs(i - col))
            return 0;
    return 1;
}

void print_solution(int *pos)
{
    char c;
    for (int i = 0; i < n; i++)
    {
        c = pos[i] + '0';
        write(1, &c, 1);
        if (i != n - 1)
            write(1, " ", 1);
    }
    write(1, "\n", 1);
}

void solve(int *pos, int col)
{
    if (col == n)
    {
        print_solution(pos);
        return;
    }
    for (int row = 0; row < n; row++)
        if (is_safe(pos, col, row))
        {
            pos[col] = row;
            solve(pos, col + 1);
        }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    n = atoi(argv[1]);
    int pos[n];
    solve(pos, 0);
    return 0;
}
*/
