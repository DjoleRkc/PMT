#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n = 1, opcija, niz[] = {1, 2, 3, 4, 5, 10, 15, 20};
    double U, t, T, fgr, f0, Pout = 0;

    cout << "odaberite koju opeciju zelite:\nopcija 1: zadatak  1 c)\nopcija 2: zadatak  1 d)" << endl;
    cin >> opcija;

    switch(opcija)
    {
        case 1:
            cout << "Unesite amplitudu U, trajanje t i periodu T impulsa periodicne povorke: " << endl;
            cin >> U >> t >> T;
            cout << "Unesite granicnu ucestalost fgr: " << endl;
            cin >> fgr;

            f0 = 1/T;
            Pout += pow(U*t/T, 2);

            while(f0*n < fgr)
            {
                Pout += 2 * pow((U*t/T * sin(n*f0*t* M_PI) / (n*f0*t* M_PI)), 2);
                n++;
            }
            cout << endl << "Snaga na izlazu filtra je: " << Pout;
            break;
        case 2:
            U = 1; T = 2.0/1000; t = 0.25/1000;
            cout << "Za U = 1, T = 2ms i t = 25ms" << endl;
            for(int i = 0; i < 8; i++, Pout = 0, n = 1)
            {
                fgr = (0.5 * niz[i] + 0.1) * 1000;
                cout << "Za fgr = " << fgr << " snaga na izlazu filtra je: ";
                f0 = 1/T;
                Pout += pow(U*t/T, 2);

                while(f0*n < fgr)
                {
                    Pout += 2 * pow((U*t/T * sin(n*f0*t* M_PI) / (n*f0*t* M_PI)), 2);
                    n++;
                }
                cout << Pout << endl ;
            }
            cout << endl << "Za fgr koje tezi beskonacnosti snaga na izlazu filtra je: " << 0.125 << endl;
            break;
        default:
            cout << "izabrali ste nepostojecu opciju" << endl;
    }

    return 0;
}
