#include <fstream>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

// problema rucsacului discontinuu
int rucsac(int N, int W, vector<int> &w, vector<int> &p) {
    // inainte de a incepe, verific daca nu cumva
    // toate obiectele pot fi introduse in rucsac
    // in acest caz, returnez suma tuturor preturilor
    int total_weight = 0, total_price = 0;

    for (int i = 1; i <= N; i++) {
        total_weight = total_weight + w[i];
        total_price = total_price + p[i];
    }

    if (total_weight <= W)
        return total_price;

    // daca nu pot fi introduse tote obiectele
    // clasica problema a rucsacului
    // dp[i][cap] = pretul maxim obtinut avand la dispozitie
    // primele i obiecte si un rucsac de greutate maxima cap
    // clar, rezultatul problemei se gaseste in dp[N][W]
    vector<vector<int>> dp(N + 1, vector<int>(W + 1));

    // caz de baza, 0 obiecte => pret total 0
    for (int cap = 0; cap <= W; cap++)
        dp[0][cap] = 0;

    // decid, pentru fiecare obiect
    // daca e convenabil sau nu sa-l pun in rucsac
    // aleg varianta care maximizeaza dp[i][cap]
    // neadaugarea unui obiect nu modifica nimic, dp[i][cap] = dp[i - 1][cap]
    // adaugarea lui inseamna -> scaderea greutatii disponibile
    //                        -> cresterea pretului total
    // dp[i][cap] = dp[i - 1][cap - w[i]] + p[i]

    for (int i = 1; i <= N; i++) {
        for (int cap = 0; cap <= W; cap++) {
            dp[i][cap] = dp[i - 1][cap];
            // se pune problema adaugarii in rucsac
            // doar daca obiectul curent are loc
            if (w[i] <= cap)
                dp[i][cap] = max(dp[i][cap], dp[i - 1][cap - w[i]] + p[i]);
        }
    }

    return dp[N][W];
}

int main() {
    ifstream fin("prinel.in");
    ofstream fout("prinel.out");
    int max_target = 0, N, K;
    fin >> N >> K;
    vector<int> p(N + 1), target(N + 1), costs(N + 1);

    for (int i = 1; i <= N; i++) {
        fin >> target[i];
        max_target = max(target[i], max_target);
    }

    for (int i = 1; i <= N; i++)
        fin >> p[i];

    fin.close();

    // calculez numarul minim de pasi necesari
    // pentru a ajunge de la 1 la targetul maxim
    // programare dinamica dp[i] = numarul de pasi de la 1 la i
    vector<int> dp(max_target + 1);
    // caz de baza, 0 pasi de la 1 la 1
    dp[1] = 0;

    for (int i = 2; i <= max_target; i++) {
        dp[i] = INT_MAX;
        // parcurg toti divizorii lui i
        for (int d = 1; d * d <= i; d++) {
            if (i % d == 0) {
                // aleg acel divizor care minimizeaza numarul de pasi
                dp[i] = min(dp[i], dp[i - d] + 1);
                if (d != 1 && d != i / d)
                    dp[i] = min(dp[i], dp[i - i / d] + 1);
            }
        }
    }

    // pentru fiecare target, costul este numarul minim de pasi de la 1 la el
    for (int i = 1; i <= N; i++)
        costs[i] = dp[target[i]];

    int score = rucsac(N, K, costs, p);
    fout << score;
    fout.close();

    return 0;
}
