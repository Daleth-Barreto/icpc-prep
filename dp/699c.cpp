#include <bits/stdc++.h>

using namespace std;

int main() {
    // Optimizar la entrada/salida
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // dp[i][j] almacenará el máximo de días de actividad hasta el día i,
    // donde j representa la actividad realizada en el día i:
    // 0 = Descanso
    // 1 = Concurso
    // 2 = Gimnasio
    vector<vector<int>> dp(n + 1, vector<int>(3, -1));

    // Casos base
    dp[0][0] = 0;
    dp[0][1] = 0;
    dp[0][2] = 0;

    for (int i = 1; i <= n; i++) {
        // 1. Siempre podemos descansar en el día i
        dp[i][0] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]});

        // 2. Si hay un concurso en el día i (a[i] == 1 o a[i] == 3)
        if (a[i] == 1 || a[i] == 3) {
            // Podemos hacer el concurso si el día anterior descansamos o fuimos al gimnasio
            int prev_max = max(dp[i - 1][0], dp[i - 1][2]);
            if (prev_max != -1) {
                dp[i][1] = prev_max + 1;
            }
        }

        // 3. Si el gimnasio está abierto en el día i (a[i] == 2 o a[i] == 3)
        if (a[i] == 2 || a[i] == 3) {
            // Podemos ir al gimnasio si el día anterior descansamos o hicimos el concurso
            int prev_max = max(dp[i - 1][0], dp[i - 1][1]);
            if (prev_max != -1) {
                dp[i][2] = prev_max + 1;
            }
        }
    }

    // Buscamos el máximo número de días en los que Vasya NO descansó
    int max_actividad = max({dp[n][0], dp[n][1], dp[n][2]});

    // La respuesta es el total de días menos el máximo de días activos
    cout << n - max_actividad << "\n";

    return 0;
}