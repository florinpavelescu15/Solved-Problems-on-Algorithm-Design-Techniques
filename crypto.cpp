#include <fstream>
#include <string>
#include <vector>
#define MOD ((int)1e9 + 7)

using namespace std;

// numara caracterele dintr-un string, nu ia in considerare duplicatele
int different_chars(string s) {
    std::string aux;

    for (int i = 0; i < s.length(); i++)
        if (aux.find(s[i]) == std::string::npos)
            aux += s[i];

    return aux.length();
}

int occurrences(string K, string S) {
    int N = K.length();
    int L = S.length();
    // numarul de caractere distincte din S
    int r = different_chars(S);

    // programare dinamica dp[i][j] = numarul de aparitii ale
    // subsirului format din primele j caractere
    // in sirul format din primele i caractere
    vector<vector<unsigned long long>>
            dp(N + 1, vector<unsigned long long>(L + 1));

    // sirul vid apare ca subsir in sirul vid o data
    dp[0][0] = 1;

    // sirul vid nu are niciun subsir nevid
    for (int i = 1; i <= L; i++)
        dp[0][i] = 0;

    // orice semn de intrebare poate fi inlocuit cu orice caracter din S
    for (int i = 1; i <= N; i++)
        // pentru fiecare dintre sirurile
        // formate din primele i - 1 caractere din K
        // un semn de intrebare pe pozitia i genereaza r siruri cu i caractere
        // orice alt caracter nu schimba cu nimic numarul sirurilor
        if (K[i - 1] == '?')
            dp[i][0] = (r * dp[i - 1][0]) % MOD;
        else
            dp[i][0] = dp[i - 1][0];

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= L; j++)
            // daca K[i - 1] != '?'
            // '?' poate fi orice caracter din S, inclusiv S[j - 1]
            // deci un caz in care dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]
            // si alte r - 1 cazuri in care dp[i][j] = dp[i - 1][j]
            if (K[i - 1] == S[j - 1])
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
            else if (K[i - 1] == '?')
                dp[i][j] = (dp[i - 1][j - 1] + r * dp[i - 1][j]) % MOD;
            else
                dp[i][j] = dp[i - 1][j] % MOD;

    return dp[N][L];
}

int main() {
    string K, S;
    int N, L;
    ifstream fin("crypto.in");
    ofstream fout("crypto.out");
    fin >> N >> L;
    fin >> K >> S;
    fout << occurrences(K, S);
    return 0;
}
