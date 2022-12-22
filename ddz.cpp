#include <iostream>
#include <random>
using namespace std;
constexpr auto N = 10000;

int main() {
    bool stavka;
    int n, q, jedan = 0, nula = 0; //n, duzina niza u, broj kvantizacionih nivoa, verovatnoca pojave 0 i 1
    double U = 4, delta, Ps = 0, Pnq = 0; //duzina intervala, korak kvantizacije, srednja snaga odbiraka, srednja snaga greske

    cout << "Tacka a ili b (0 ili 1): ";
    cin >> stavka;

    cout << "Unesite stepen broja kvantizacionih nivoa n:" << endl;
    cin >> n;
    q = 1 << n;

    delta = U / q; // racunanje delta

    float u[N];
    float u2[N];
    float uZbir[N];//niz N odbiraka
    float outKvantizer[N]; // niz na izlazu iz kvantizera
    float e[N]; //niz gresaka
    int binaryCode[10 * N]; // binarni niz na izlazu kodera
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distrib(-U / 2, U / 2);
    for (int i = 0; i < N; i++) u[i] = e[i] = distrib(gen);// Generisanje uniformno rasporedjenih random brojeva
        
    
    for (int i = 0; i < N; i++) u2[i] = distrib(gen);
        

    for (int i = 0; i < N; i++) {
        uZbir[i] = u[i] + u2[i];
        if (uZbir[i] > U / 2) uZbir[i] -= U;
        else if (uZbir[i] < -U / 2) uZbir[i] += U;
    }
    
    if (stavka) {
        for (size_t i = 0; i < N; i++)
        {
            u[i] = e[i] = uZbir[i];
        }
    }

    double d[1024 + 1];
    d[0] = -U / 2;
    for (int i = 1; i <= q; i++) //Generisanje granica intervala kvantizacije
        d[i] = d[i - 1] + delta;

    for (int i = 0; i < N; i++)
    {
        int j = 1;
        while (u[i] > d[j]) j++; //Nalazenje u kom intervalu je svaki od N odbiraka

        outKvantizer[i] = (d[j] + d[j - 1]) / 2; // izlaz iz kvantizera
        e[i] -= outKvantizer[i]; // racunanje greske kvantizacije

        for (int k = n - 1; k >= 0; k--)
        {
            int pom = (j - 1) >> k;
            binaryCode[(i + 1) * n - k - 1] = pom & 1; //Pretvaranje kvantizacionog nivoa u n bitova binarnog koda
        }

        Ps += u[i] * u[i]; //Uvecavanje Srednje snage suma kvantizacije i srednje snage odbiraka signala
        Pnq += e[i] * e[i];
    }

    
    //Ukoliko zelite da vam se ispisuje niz vrednosti signala i greske, odkomentarisite linije 74-92
    //a)
    /*
    cout << endl << "a)  Niz kvantiziranih vrednosti signala na izlazu iz kvantizera je:" << endl << "\t";
    for (int i = 0; i < N; i++)
        cout << outKvantizer[i] << " ";
    cout << endl << "Niz koji predstavlja signal greske je:" << endl;
    for (int i = 0; i < N; i++)
        cout << e[i] << " ";

    //b)
    cout << endl << endl << "b)  Binarni niz na izlazu kodera:" << endl << "\t";
    for (int i = 0; i < N * n; i++)
    {
        cout << binaryCode[i];
        jedan += binaryCode[i]; //Brojanje koliko puta se pojavljuju 1 i 0, respektivno
        nula += !binaryCode[i];
    }
    cout << endl << "Verovatnoca pojave jedinice je " << (double)jedan / n / N << endl;
    cout << "Verovatnoca pojave nule je " << (double)nula / n / N << endl; //Racunanje verovatnoce pojave svakog od simbola
    */

    //c) Ps
    cout << endl << "c)  Srednja snaga signala na ulazu u kvantizer Ps = " << Ps / N << endl;

    //d) Pnq
    cout << endl << "d)  Srednja snaga suma kvantizacije Pnq = " << Pnq / N << endl;


    //analiza
    cout << endl << "Odnos signal-sum SNRq = " << Ps / Pnq << endl;
    cout << "Ocekivana vrednost je " << q * q << endl;
    cout << "Procenat greske je " << abs((1-((Ps / Pnq) / (q * q))) * 100) << "%";
    return 0;
}