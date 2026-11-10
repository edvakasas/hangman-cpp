#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <stdexcept>
using namespace std;

class Zaidejas {
protected:
    string vardas;
public:
    Zaidejas(const string& v) : vardas(v) {}
    virtual void veiksmas() = 0;
    string getVardas() const { return vardas; }
    virtual ~Zaidejas() {}
};

class ZodzioNustatytojas : public Zaidejas {
private:
    string zodis;
    string uzuomina;
public:
    ZodzioNustatytojas(const string& v) : Zaidejas(v) {}
    void veiksmas() override {
        cout << vardas << ", iveskite zodi, kuri reikes atspeti: ";
        cin >> zodis;
        transform(zodis.begin(), zodis.end(), zodis.begin(), ::tolower);
        cout << "Iveskite uzuomina: ";
        cin.ignore();
        getline(cin, uzuomina);
    }
    string getZodis() const { return zodis; }
    string getUzuomina() const { return uzuomina; }
};

class Spejikas : public Zaidejas {
private:
    int spejimuSkaicius = 0;
public:
    Spejikas(const string& v) : Zaidejas(v) {}
    void veiksmas() override {
        cout << vardas << ", spekite raides!" << endl;
    }
    void operator++(int) { spejimuSkaicius++; }
    int getSpejimuSkaicius() const { return spejimuSkaicius; }
};

class Zaidimas {
private:
    ZodzioNustatytojas nustatytojas;
    Spejikas spejikas;
    string zodis;
    string uzuomina;
    set<char> atspetos;
    set<char> neteisingos;
    map<char, bool> klaviatura;
    int gyvybes;
    bool panaudotaUzuomina = false;

    void atnaujinkKlaviatura(char raide, bool teisinga) {
        klaviatura[raide] = teisinga;
    }

    void piesk() {
        system("cls");
        cout << "+---+" << endl;
        cout << "|   |" << endl;
        cout << "|   " << (gyvybes <= 5 ? "O" : "") << endl;
        cout << "|  " << (gyvybes <= 4 ? "/" : " ");
        cout << (gyvybes <= 3 ? "|" : " ");
        cout << (gyvybes <= 2 ? "\\" : " ") << endl;
        cout << "|  " << (gyvybes <= 1 ? "/" : " ");
        cout << (gyvybes <= 0 ? " \\" : "  ") << endl;
        cout << "|____" << endl;
    }

    void rodykZodi() {
        for (char c : zodis) {
            if (atspetos.count(c)) cout << c << ' ';
            else cout << "_ ";
        }
        cout << endl;
    }

    void rodykKlaviatura() {
        cout << "\nKlaviatura:\n";
        for (char c = 'a'; c <= 'z'; ++c) {
            if (klaviatura.count(c)) {
                if (klaviatura[c]) cout << "[" << c << "] ";
                else cout << "(" << c << ") ";
            }
            else {
                cout << c << ' ';
            }
            if ((c - 'a' + 1) % 13 == 0) cout << endl;
        }
        cout << endl;
    }

    void rodykUzuomina() {
        if (panaudotaUzuomina)
            cout << "Uzuomina: " << uzuomina << endl;
    }

public:
    Zaidimas(const string& v1, const string& v2)
        : nustatytojas(v1), spejikas(v2), gyvybes(6) {
    }

    void vykdyti() {
        nustatytojas.veiksmas();
        zodis = nustatytojas.getZodis();
        uzuomina = nustatytojas.getUzuomina();
        spejikas.veiksmas();

        while (gyvybes > 0) {
            piesk();
            rodykUzuomina();
            rodykZodi();
            rodykKlaviatura();

            cout << "Liko gyvybiu: " << gyvybes << ". Spekite raide arba rasykite !clue: ";
            string ivestis;
            cin >> ivestis;
            transform(ivestis.begin(), ivestis.end(), ivestis.begin(), ::tolower);

            if (ivestis == "!clue") {
                if (!panaudotaUzuomina && gyvybes > 1) {
                    gyvybes--;
                    panaudotaUzuomina = true;
                }
                else {
                    cout << "Negalima naudoti uzuominos!\n";
                }
                continue;
            }

            if (ivestis.length() != 1 || !isalpha(ivestis[0])) {
                cout << "Netinkama ivestis.\n";
                continue;
            }

            char spejimas = ivestis[0];
            spejikas++;
            if (atspetos.count(spejimas) || neteisingos.count(spejimas)) {
                cout << "Jau spejote sia raide.\n";
                continue;
            }

            if (zodis.find(spejimas) != string::npos) {
                atspetos.insert(spejimas);
                atnaujinkKlaviatura(spejimas, true);
            }
            else {
                neteisingos.insert(spejimas);
                atnaujinkKlaviatura(spejimas, false);
                gyvybes--;
            }

            if (all_of(zodis.begin(), zodis.end(), [&](char c) { return atspetos.count(c); })) {
                piesk();
                cout << "Sveikiname, " << spejikas.getVardas() << "! Zodis buvo: " << zodis << endl;
                return;
            }
        }

        piesk();
        cout << "Zaidimas baigtas. Zodis buvo: " << zodis << endl;
    }
};

int main() {
    string v1, v2;
    char pasirinkimas;
    do {
        cout << "Zodzio nustatytojo vardas: ";
        cin >> v1;
        cout << "Spejiko vardas: ";
        cin >> v2;
        Zaidimas zaidimas(v1, v2);
        zaidimas.vykdyti();
        cout << "Ar norite zaisti dar karta? (t/n): ";
        cin >> pasirinkimas;
    } while (pasirinkimas == 't' || pasirinkimas == 'T');

    return 0;
}
