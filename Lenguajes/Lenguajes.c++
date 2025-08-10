#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <queue>
#include <set>
#include <cctype>

using namespace std;

struct DFA {
    int n; // número de estados
    vector<string> alphabet; // símbolos del alfabeto
    vector<bool> isFinal; // estados finales
    vector<vector<int>> trans; // tabla de transiciones [estado][símbolo] = estado destino
};

// Obtiene la siguiente línea no vacía (salta líneas en blanco). Devuelve false si EOF.
bool getNonEmptyLine(ifstream &in, string &out) {
    out.clear();
    while (std::getline(in, out)) {
        // quitar posibles espacios al principio y final
        size_t start = out.find_first_not_of(" \t\r\n");
        if (start == string::npos) continue; // línea vacía -> seguir
        size_t end = out.find_last_not_of(" \t\r\n");
        out = out.substr(start, end - start + 1);
        if (!out.empty()) return true;
    }
    return false;
}

// Trim (in-place)
void trim_inplace(string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) { s.clear(); return; }
    size_t end = s.find_last_not_of(" \t\r\n");
    s = s.substr(start, end - start + 1);
}

int main() {
    string ruta;
    cout << "Ingrese la ruta del archivo .txt con la entrada del AFD que decea minimizar: ";
    getline(cin, ruta);

    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo. Verifique la ruta e intente de nuevo." << endl;
        return 1;
    }

    // Leer cantidad de casos
    int casos;
    if (!(archivo >> casos)) {
        cerr << "Error: No se pudo leer el número de casos." << endl;
        return 1;
    }
    if (casos <= 0) {
        cerr << "Error: el número de casos debe ser mayor que 0." << endl;
        return 1;
    }
    // Consumir el resto de la línea
    archivo.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Pares de estados equivalentes en orden lexicografico: " << endl;

    for (int caso = 0; caso < casos; ++caso) {
        // Leer n (número de estados). saltar líneas en blanco hasta encontrar el número
        int n;
        string line;
        while (true) {
            if (!getNonEmptyLine(archivo, line)) {
                cerr << "Error: EOF inesperado al leer número de estados para el caso " << caso+1 << "." << endl;
                return 1;
            }
            stringstream st(line);
            if (st >> n) break;
            // sino seguir a la siguiente línea
        }

        if (n <= 0) {
            cerr << "Error: número de estados debe ser > 0 en el caso " << caso+1 << "." << endl;
            return 1;
        }

        DFA dfa;
        dfa.n = n;

        // Leer alfabeto (línea no vacía) y validar símbolos (a..z), sin duplicados
        if (!getNonEmptyLine(archivo, line)) {
            cerr << "Error: EOF inesperado al leer alfabeto para el caso " << caso+1 << "." << endl;
            return 1;
        }
        {
            stringstream ss(line);
            string sym;
            set<char> seen;
            while (ss >> sym) {
                // Validar que sea exactamente un carácter y que esté en 'a'..'z'
                if (sym.size() != 1) {
                    cerr << "Error: símbolo de alfabeto inválido \"" << sym << "\". Debe ser un solo carácter 'a'..'z' (caso " << caso+1 << ")." << endl;
                    return 1;
                }
                char c = sym[0];
                if (c < 'a' || c > 'z') {
                    cerr << "Error: símbolo de alfabeto inválido '" << sym << "'. Debe ser una letra minúscula 'a'..'z' (caso " << caso+1 << ")." << endl;
                    return 1;
                }
                if (seen.count(c)) {
                    cerr << "Error: símbolo de alfabeto duplicado '" << sym << "' en el caso " << caso+1 << "." << endl;
                    return 1;
                }
                seen.insert(c);
                dfa.alphabet.push_back(sym);
            }
            if (seen.empty()) {
                cerr << "Error: alfabeto vacío en el caso " << caso+1 << "." << endl;
                return 1;
            }
            if (seen.size() > 26) {
                cerr << "Error: alfabeto demasiado grande (más de 26 símbolos) en el caso " << caso+1 << "." << endl;
                return 1;
            }
        }
        int alphaSize = dfa.alphabet.size();

        // --- LECTURA DE ESTADOS FINALES ---
        // Aquí usamos getline normal para permitir una línea vacía (0 estados finales).
        if (!std::getline(archivo, line)) {
            cerr << "Error: EOF inesperado al leer estados finales para el caso " << caso+1 << "." << endl;
            return 1;
        }
        trim_inplace(line);
        dfa.isFinal.assign(dfa.n, false);
        if (!line.empty()) {
            stringstream sf(line);
            int f;
            while (sf >> f) {
                if (f < 0 || f >= dfa.n) {
                    cerr << "Error: índice de estado final fuera de rango (" << f << ") en el caso " << caso+1 << "." << endl;
                    return 1;
                }
                dfa.isFinal[f] = true;
            }
            // si hubiera tokens no numéricos esto fallaría en el while >> f; puedes validar más si se desea
        }

        // Leer tabla de transiciones: deben venir exactamente n líneas (cada una con índice + alphaSize enteros)
        dfa.trans.assign(dfa.n, vector<int>(alphaSize, -1));
        for (int i = 0; i < dfa.n; ++i) {
            if (!getNonEmptyLine(archivo, line)) {
                cerr << "Error: EOF inesperado al leer transiciones (estado " << i << ") en el caso " << caso+1 << "." << endl;
                return 1;
            }
            stringstream st(line);
            int idx;
            if (!(st >> idx)) {
                cerr << "Error: falta índice de estado en la línea de transiciones (caso " << caso+1 << ")." << endl;
                return 1;
            }
            if (idx < 0 || idx >= dfa.n) {
                cerr << "Error: índice de estado en la tabla fuera de rango (" << idx << ") en el caso " << caso+1 << "." << endl;
                return 1;
            }
            for (int j = 0; j < alphaSize; ++j) {
                int dest;
                if (!(st >> dest)) {
                    cerr << "Error: faltan transiciones para el estado " << idx << " (esperadas " << alphaSize << ") en el caso " << caso+1 << "." << endl;
                    return 1;
                }
                if (dest < 0 || dest >= dfa.n) {
                    cerr << "Error: destino de transición fuera de rango (" << dest << ") para estado " << idx << " en el caso " << caso+1 << "." << endl;
                    return 1;
                }
                dfa.trans[idx][j] = dest;
            }
            // Comprobar tokens extra en la misma línea (si hay, señalamos error)
            string extra;
            if (st >> extra) {
                cerr << "Error: tokens extra en la línea de transicion del estado " << idx << " (caso " << caso+1 << ")." << endl;
                return 1;
            }
        }

        // -------------------------
        // Optimización: construir lista de predecesores para cada (estado,símbolo)
        // pred[state][symbol] = vector de estados p tales que δ(p,symbol) = state
        // -------------------------
        vector<vector<vector<int>>> pred(dfa.n, vector<vector<int>>(alphaSize));
        for (int p = 0; p < dfa.n; ++p) {
            for (int a = 0; a < alphaSize; ++a) {
                int t = dfa.trans[p][a];
                pred[t][a].push_back(p);
            }
        }

        // Matriz de marcados (solo usaremos p<q)
        vector<vector<bool>> marcado(dfa.n, vector<bool>(dfa.n, false));
        queue<pair<int,int>> q;

        // Marcar pares cuyo estado final difiere y encolarlos
        for (int p = 0; p < dfa.n; ++p) {
            for (int r = p + 1; r < dfa.n; ++r) {
                if (dfa.isFinal[p] != dfa.isFinal[r]) {
                    marcado[p][r] = true;
                    q.push({p, r});
                }
            }
        }

        // Propagación eficiente: para cada par marcado (r,s) mirar sus predecesores
        while (!q.empty()) {
            auto pr = q.front(); q.pop();
            int r = pr.first;
            int s = pr.second;
            // recorrer cada símbolo
            for (int a = 0; a < alphaSize; ++a) {
                const auto &preR = pred[r][a];
                const auto &preS = pred[s][a];
                if (preR.empty() || preS.empty()) continue;
                // combinar preR x preS
                for (int p_state : preR) {
                    for (int q_state : preS) {
                        if (p_state == q_state) continue;
                        int x = min(p_state, q_state);
                        int y = max(p_state, q_state);
                        if (!marcado[x][y]) {
                            marcado[x][y] = true;
                            q.push({x,y});
                        }
                    }
                }
            }
        }

        // Recopilar pares no marcados -> equivalentes
        vector<pair<int,int>> equivalentes;
        for (int p = 0; p < dfa.n; ++p) {
            for (int r = p + 1; r < dfa.n; ++r) {
                if (!marcado[p][r]) equivalentes.push_back({p,r});
            }
        }

        // Orden lexicográfico (ya lo estarán por construcción, pero lo aseguramos)
        sort(equivalentes.begin(), equivalentes.end());

        // Imprimir pares (en una sola línea, separados por espacios)
        for (size_t i = 0; i < equivalentes.size(); ++i) {
            if (i > 0) cout << " ";
            cout << "(" << equivalentes[i].first << "," << equivalentes[i].second << ")";
        }
        cout << endl;
    }

    return 0;
}