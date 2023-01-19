#include <iostream>
#include <random>
using namespace std;

int main() {
    cout.precision(8);
    int n, q, j = 1;
    double Umin, Umax, Uk, delta, d[1024 + 1], e, out, binary[8];

    cout << "Unesite opseg u kom se nalazi ulazni signal Umin i Umax:" << endl;
    cin >> Umin >> Umax;

    cout << "Unesite stepen broja kvantizacionih nivoa n:" << endl;
    cin >> n;
    q = 1 << n;

    cout << "Unesite vrednost amplitude odabirka Uk:" << endl;
    cin >> Uk;

    delta = (Umax - Umin) / q;

    d[0] = Umin;
    cout << "Prvih 10 kvantizacionih nivoa:" << endl << d[0] << " ";
    for (int i = 1; i <= q; i++)
    {
        d[i] = d[i - 1] + delta;
        if (i < 10) cout << (d[i] + d[i - 1]) / 2 << " ";
    }
    cout << endl << endl;

    while (Uk > d[j]) j++;
    out = (d[j] + d[j - 1]) / 2;
    e = abs(Uk - out);

    for (int k = n - 1; k >= 0; k--)
    {
        int pom = (j - 1) >> k;
        binary[n - k - 1] = pom & 1;
    }

    cout << "Vrednost kvantiziranog signala je: " << out << endl;
    cout << "Vrednost greske je: " << e << endl;
    cout << "Kodna rec na izlazu iz kvantizera je: ";
    for (int i = 0; i < n; i++)
        cout << binary[i];

    return 0;
}