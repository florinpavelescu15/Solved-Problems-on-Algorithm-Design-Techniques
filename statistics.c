#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// compara doua numere intregi
int cmpfunc(const void *a, const void *b) {
    int A = *(int *)a;
    int B = *(int *)b;
    return B - A;
}

// calculeaza greutatea fiecarui cuvant din words in litera ch
// dupa formula: weight(word) = 2 * freq - word.len
// returneaza un vector de greutati
int *calculate_weights(char ch, int N, char **words) {
    int *weights = malloc((N + 1) * sizeof(int));
    for (int i = 0; i < N; i++) {
        int freq = 0;
        for (int j = 0; j < strlen(words[i]); j++)
            if (words[i][j] == ch)
                freq++;
        weights[i] = 2 * freq - strlen(words[i]);
    }
    return weights;
}

// calculeaza numarul maxim de cuvinte din words
// care pot fi concatenate pentru a obtine litera ch dominanta
int max_len(char ch, int N, char **words) {
    int nr_words = 0, S;
    // calculez greutatea fiecarui cuvant in litera ch
    int *weights = calculate_weights(ch, N, words);

    // sortez vectorul de greutati descrescator
    // cuvintele cu greutate mare dau o dominanta mai mare
    // astfel, ele au prioritate la adaugarea in sirul final
    qsort(weights, N, sizeof(int), cmpfunc);

    // S = 2 * freq - strlen, greutatea globala
    // conditia de dominanta a literei ch este ecivalenta
    // cu greutatea globala dtrict pozitiva
    // freq > strlen / 2 <=> 2 * freq - strlen > 0
    S = weights[nr_words];

    // adaug cuvinte in sir cat timp
    // mai am cuvinte
    // conditia de greutate globala pozitiva este satisfacuta
    while (S > 0 && nr_words < N) {
        nr_words++;
        S = S + weights[nr_words];
    }

    return nr_words;
}

int main() {
    char **words, word[10000];
    int N;
    FILE *in_file, *out_file;
    in_file = fopen("statistics.in", "r");
    out_file = fopen("statistics.out", "w");

    fscanf(in_file, "%d", &N);
    words = malloc((N + 1) * sizeof(char *));

    for (int i = 0; i < N; i++) {
        fscanf(in_file, "%s", word);
        words[i] = malloc((strlen(word) + 2) * sizeof(char));
        strcpy(words[i], word);
    }

    int max_words = -1;

    // pentru fiecare litera din alfabet
    // calculez numarul maxim de cuvinte care se pot concatena
    // pentru a obtine litera respectiva dominanta
    // maximul acestor valori este rezultatul problemei
    for (int i = 0; i < 26; i++) {
        int k = max_len('a' + i, N, words);
        if (k > max_words)
            max_words = k;
    }

    fprintf(out_file, "%d\n", max_words);
    fclose(in_file);
    fclose(out_file);

    return 0;
}
