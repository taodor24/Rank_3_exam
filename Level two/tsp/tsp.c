#include <stdio.h>
#include <math.h>

#define MAX 11

typedef struct { float x, y; } City;

City c[MAX];
int n, used[MAX];
float dist[MAX][MAX], best = 1e9;

float d(City a, City b) {
    return sqrtf((a.x-a.x)*(a.x-a.x)+(a.y-b.y)*(a.y-b.y));
}

// рекурсивный перебор
void dfs(int k, int last, float len) {
    if (k == n) {
        if (len + dist[last][0] < best)
            best = len + dist[last][0];
        return;
    }
    for (int i=1; i<n; i++) if (!used[i]) {
        used[i]=1;
        dfs(k+1, i, len+dist[last][i]);
        used[i]=0;
    }
}

int main(void) {
    while (n < MAX && fscanf(stdin, " %f , %f", &c[n].x, &c[n].y) == 2) n++;
    for (int i=0; i<n; i++) for (int j=0; j<n; j++)
        dist[i][j] = sqrtf((c[i].x-c[j].x)*(c[i].x-c[j].x)+(c[i].y-c[j].y)*(c[i].y-c[j].y));
    used[0]=1;
    dfs(1,0,0);
    fprintf(stdout,"%.2f\n",best);
}





/*
old version:

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 11

typedef struct {
    float x, y;
} City;

City cities[MAX];
int n;
float dist[MAX][MAX];
int used[MAX];
int path[MAX];
float best = 1e9; // inicializa com valor grande

// calcula distância euclidiana usando sqrtf
float distance(City a, City b) {
    return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

// busca recursiva por todas as rotas
void search(int k, float length) {
    if (k == n) {
        length += dist[path[n-1]][path[0]]; // fecha o ciclo
        if (length < best)
            best = length;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = 1;
            path[k] = i;
            float new_length = length;
            if (k > 0)
                new_length += dist[path[k-1]][i];
            search(k+1, new_length);
            used[i] = 0;
        }
    }
}

int main(void) {
    n = 0;
    // leitura de cidades usando fscanf(stdin)
    while (fscanf(stdin, " %f , %f", &cities[n].x, &cities[n].y) == 2)
        n++;

    // pré-calcula todas as distâncias
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = distance(cities[i], cities[j]);

    // inicia busca
    search(0, 0.0);

    // imprime resultado usando fprintf
    fprintf(stdout, "%.2f\n", best);

    return 0;
}
*/