#include <stdio.h>
#include <math.h>

// reduc problema la o subproblema de dimensiune N/2
int walsh(int N, int x, int y) {
    // caz de baza
    if (N == 1)
        return 0;

    // verific in ce cadran se afla (x, y)
    // aplic recursiv functia walsh doar pe cadranul respectiv
    // apoi scalez coordonatele la noua dimensiune
    if (x <= N / 2 && y <= N / 2)
        return walsh(N / 2, x, y) % 2;

    if (x <= N / 2 && y > N / 2)
        return walsh(N / 2, x, y - N / 2) % 2;

    if (x > N / 2 && y <= N / 2)
        return walsh(N / 2, x - N / 2, y) % 2;

    if (x > N / 2 && y > N / 2)
        return (1 + walsh(N / 2, x - N / 2, y - N / 2)) % 2;
}

int main() {
    FILE *in_file, *out_file;
    in_file = fopen("walsh.in", "r");
    out_file = fopen("walsh.out", "w");
    int N, K, x, y;

    fscanf(in_file, "%d %d", &N, &K);

    for (int i = 1; i <= K; i++) {
        fscanf(in_file, "%d %d", &x, &y);
        fprintf(out_file, "%d\n", walsh(N, x, y));
    }

    fclose(in_file);
    fclose(out_file);

    return 0;
}
