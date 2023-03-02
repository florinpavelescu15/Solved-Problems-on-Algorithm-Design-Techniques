Pavelescu Florin, grupa 324CC

# Walsh
```
                1         N/2         N
            1   +----------+----------+
                |          |          |
                |    1     |     2    |
                |          |          |
            N/2 +----------+----------+
                |          |          |
                |    3     |     4    |
                |          |          |
            N   +----------+----------+
```

Am folosit metoda *Divide et Impera*. Practic, am redus problema la o subproblema mai mica.
Am impartit matricea de dimensiune `N` in 4 matrice de dimensiune `N/2`.
Am identificat in care dintre cele 4 cadrane se gaseste punctul si am aplicat 
functia recursiv doar pe acel cadran. Daca punctul se gaseste in cadranul 4 adaug 1 la rezultat. 
De fiecare data returnez rezultatul modulo 2 pentru a ramane in multimea `{0, 1}`.
Am considerat caz de baza `N = 1`, caz in care rezultatul e `0`.
Reguli de rescalare:
- Daca `(x, y)` de afla in cadranul 1, coordonatele raman neschimbate.
- Daca `(x, y)` de afla in cadranul 2, coordonatele devin `(x, y - N / 2)`.
- Daca `(x, y)` de afla in cadranul 3, coordonatele devin `(x - N / 2, y)`.
- Daca `(x, y)` de afla in cadranul 4, coordonatele devin `(x - N / 2, y - N / 2)`.

Complexitate temporala: `T(n) = T(n / 2) + O(1)`, conform *teoremei Master*, `T(n) = O(log n)`
Complexitate spatiala: `O(1)`

## Statistics
Daca din cele `N` cuvinte din vectorul words aleg `k` cuvinte, `words[i_1]`, `words[i_2], ..., words[i_k]`,
si daca notez cu `freq[j]` numarul de aparitii ale literei `ch` in cuvantul
`words[i_j]` si `len[j]` lungimea cuvantului `words[i_j]`, pentru `j = 1..k`, atunci conditia
ca litera `ch` sa fie dominanta se rescrie astfel 
```
total_freq > total_length/2 <=>
<=> freq[1] + freq[2] + ... + freq[k] > (len[1] + len[2] + ... + len[k])/2 <=>
<=> 2 * (freq[1] + freq[2] + ... + freq[k]) > len[1] + len[2] + ... + len[k] <=>
<=> 2 * freq[1] - len[1] + 2 * freq[2] - len[2] + ... + 2 * freq[k] - len[k] > 0 <=>
<=> weight[1] + weight[2] + ... + weight[k] > 0
```
unde `weight[j] = 2 * freq[j] - len[j]` este greutatea cuvantului `words[i_j]` in caracterul `ch`. 
Daca notez `S = weight[1] + weight[2] + ... + weight[k]`, greutatea globala a subsirului
de cuvinte in litera `ch`, conditia devine `S > 0`.
Deci, pentru fiecare litera din alfabet, mi-am propus sa determin `k` maxim pentru care
se respecta conditia de mai sus. Asadar, am parcurs fiecare litera, am sortat vectorul `words`
dupa greutatea in litera curenta (cuvintele cu greutate mare vor da o dominanta mai mare) si
am concatenat, pe rand, cuvinte pana cand `S < 0` sau se termina sirul de cuvinte (*metoda Greedy*).
Am ales maximul valrilor calculate pentru fiecare dintre literele alfabetului.
Complexitate temporala: `O(L) + O(N*logN) = O(L + N*logN)`
Complexitate spatiala: `O(L)`

3. Prinel
Pentru a calcula numarul minim de pasi necesari pentru a ajunge la un target am folosit 
programarea dinamica, cu dp[i] = numarul minim de pasi necesari pentru a obtine 
targetul i, pentru i = 1..target.
- Fie x un numar natural nenul si d un divizor al sau. Evident, d este si divizor al lui x + d. (1)
- Fie i un numar natural nenul si d un divizor al sau, d != i. Evident, d este si divizor al lui i - d. (2)
Consider ca am determinat toate valorile dp[1], dp[2], ..., dp[i - 1]. Daca x + d = i 
(d este divizor al lui x), rezulta ca mai este un pas de la x pana la i, deci dp[i] = dp[x] + 1, 
deci dp[i] = dp[i - d] + 1 si conform (1) si (2) d este orice divizor al lui i, d != i. 
Asadar, cum dp[i - 1], dp[i - 2], ..., dp[1] au fost calculate optim, aleg dp[i] = min(dp[i - d] + 1),
unde d este orice divizor al lui i, d != i. 
Evident, cazul de baza este dp[1] = 0 (nu am nevoie de niciun pas ca sa ajung de la 1 la 1).
Pentru problema din enunt calculez dp[i] pentru i = 1..target_maxim, astfel voi obtine 
numarul minim de pasi pentru toate targeturile.
Cu targeturile calculate, problema se reduce la problema rucsacului cu urmatoarele identificari:
K (numarul total de pasi)                                           <-> W (greutatea totala a rucsacului)
costs[i] (numarul minim de pasi necesari pentru a obtine target[i]) <-> w[i] (greutatea obiectului i)
p[i] (punctajul aferent targetului targets[i])                      <-> p[i] (pretul obiectului i)
Complexitate temporala: O(max_target * sqrt(max_target)) + O(n * k) = O(max_target * sqrt(max_target) + n * k)
Complexitate spatiala: O(max_target) + O(n * k)

4. Crypto
Am pornit de la o implementare recursiva a determinarii numarului de aparitii ale unui subsir S
intr-un sir K, fara a tine cont de eventualele '?' din K, pe care am adaptat-o ulterior.
```
n = K.len
m = S.len
┌aparitii (K, S, n, m)
|
|    // sirul vid apare 1 data ca subsir in orice sir
|    ┌daca m == 0 atunci
|    |    return 1
|    └■
|    // sirul vid nu are niciun subsir in afara de sirul vid
|    ┌daca n == 0 atunci
|    |    return 0
|    └■
|    //daca ultimele litere se potrivesc
|    ┌daca K[n] == S[m] atunci
|    |    // caut restul lui S in restul lui K si intregul K in restul lui S 
|    |    return aparitii(K, S, n - 1, m - 1) + aparritii(K, S, n - 1, m);
|    | altfel
|    |    // caut S in restul lui K
|    |    aparritii(K, S, n - 1, m)
|    └■
└■
```

Am flosit programare dinamica, dp[i][j] = numarul de aparitii ale subsirului format din primele 
j litere ale subsirului S in sirul format din primele i caractere ale lui K.
In plus fata de algoritmul de mai sus, tin cont ca
- pentru fiecare dintre sirurile formate din primele i - 1 elemente din K un semn de intrebare pe 
pozitia i genereaza r siruri cu i elemente, iar orice alt caracter nu schimba cu nimic numarul sirurilor
- daca K[i - 1] != '?', poate fi orice caracter din S, inclusiv S[j - 1]
    - deci un caz in care K[i - 1] = S[j - 1] => dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]
    - alte r - 1 cazuri in care K[i - 1] != S[j - 1] => dp[i][j] = dp[i - 1][j]
    - insumand obtin dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] + (r - 1) * dp[i - 1][j]
                               = dp[i - 1][j - 1] + r * dp[i - 1][j]
    unde r este numarul de caractere distincte din S
Complexitate temporala: O(N * L)
Complexitate spatiala: O(N * L)
