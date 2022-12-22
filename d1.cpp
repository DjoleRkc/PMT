/*
ZADATAK 1
Napisati program koji generiše sve kodne reči za kod opisan generišućom matricom 1 1 0 1 1 1
                                                                                 1 1 1 1 1 1
										 0 1 1 0 0 1
a) Odrediti parametre koda (n,k).  
b) Odrediti težinu svake kodne reči (broj jedinica u njoj), i napisati koliko ima kodnih reči sa težinama d=0, 1, ..., n. Protumačiti dobijeni rezultat. 
c) Koliko grešaka može da ispravi takav kod? 

ZADATAK 2 
a)  Napisati  program  koji  uzastopno  generiše N=1000  slučajno  izabranih  informacionih  reči  dužine k=6, 
a zatim na osnovu generišuće matrice iz prethodnog zadatka od njih formira N kodnih reči dužine n=10. 
b) Korisnik unosi pozicije grešaka na četiri uzastopne pozicije, što odgovara paketskoj greški u kanalu. 
Neka se ovakva paketska greška ponavlja periodično na svakih 50 binarnih simbola koji prolaze kroz kanal. 
Za koje parametre interlivera i deinterlivera je moguće ispraviti sve greške, ako je interliving kombinuje sa kodom iz prethodnog dela zadatka?  
c) Napisati program koji obavlja deinterliving i dekodovanje primljene sekvence (sekvence na izlazu kanala, izmenjene  pod  uticajem  periodične  paketske  smetnje).
Uporediti  poslatu  i  primljenu  sekvencu  i  proceniti koliku verovatnoću greške vidi korisnik
*/
#include <iostream>
#include <ctime>
#define N 6
#define K 3
#define N2 1000


using namespace std;


int main() {
	cout << "Zadatak 1"<<endl;
	cout << "a) Parametri koda su n=6 i k=3." << endl;
	srand(time(nullptr));
	bool matrica[K][N] = { {true, true, false, true,  true, true},
						 {true,  true, true,  true,  true,  true},
						 {false, true, true,  false, false, true} };

	
	int w[8] = {0};
	int w2[8] = {0};
	bool bit;
	int i = 0;

	cout << endl<<"b) Kodne reci su:"<<endl;
	for (int one = 0; one < 2; one++) {
		for (int two = 0; two < 2; two++) {
			for (int three = 0; three < 2; three++) {
				for (int j = 0; j < N; j++) {
					if ((bit = one & matrica[0][j] ^ two & matrica[1][j] ^ three & matrica[2][j])) w[i]++;
					cout << bit;
				}
				cout << " - tezina je: " << w[i] << endl;
				w2[w[i++]]+=1;
			}
		}
	}

	int d = 0;
	cout << endl<<"Broj kodnih reci sa tezinom:"<<endl;
	for (int j = 0; j <= N; j++) {
		cout << j << " - " << w2[j] << endl;
		if (!d && j && w2[j]) d = j;
	}

	int g = -1;
	int c = -1;

	while (d >= 2 * (++c + 1) + 1);
	while (d >= c + (++g + 1) + 1);

	cout << endl<<"c) Kod moze da detektuje " << g << " gresaka, i moze da ispravi " << c << " gresaka."<<endl;

	cout << endl<<"Zadatak 2"<<endl;
	cout <<"Matrica iz zadatka 1 ne moze da ispravi gresku, pa moramo usvojiti novu matricu."<<endl;

	bool generatingMatrix[K][N] = { {false, false, false, true,  true,  true},
							 {false, true,  true,  false, false, true},
							 {true,  false, true,  false, true,  false} };

	bool controlMatrix[N][K] = { {true,  true,  false},
							{true,  false, true},
							{true,  false, false},
							{false, true,  true},
							{false, true,  false},
							{false, false, true} };

	bool generator[K * N2];

	int predajnikBrojac = 0;
	bool zasticenaPorukaPredajnik[N * N2];
	

	bool interliver[N2][N];
	int interliverParam;

	int kanalBrojac = 0;
	bool kanal[N * N2];
	int miss;

	bool deinterliver[N2][N];

	int prijemnikBrojac = 0;
	bool zasticenaPorukaPrijemnik[N * N2];
	
	int numOfMisses = 0, sindrom;

	

	cout << endl<<"Od kog bita unositi paketsku gresku velicine 4 na svakih 50 simbola? ";
	cin >> miss;
	cout << "Koje parametre interlivera koristiti (Faktor od 1000)? ";
	cin >> interliverParam;

	cout << endl << "Generator:" << endl;
	for (int j = 0; j < K * N2; j++) {
		generator[j] = rand() % 2;
		cout << generator[j];
		if (j % 3 == 2) cout << " \n"[(j + 3) % 54 == 2];
	}
	cout << endl;
	cout << endl << "Generisane kodne reci:" << endl;
	for (int p = 0; p < K * N2; p += 3) {
		for (int j = 0; j < N; j++) {
			zasticenaPorukaPredajnik[predajnikBrojac] =
				generator[p + 0] & generatingMatrix[0][j] ^
				generator[p + 1] & generatingMatrix[1][j] ^
				generator[p + 2] & generatingMatrix[2][j];
			cout << zasticenaPorukaPredajnik[predajnikBrojac++];
		}
		cout << " \n"[(p + 3) % 24 == 0];
	}

	for (int p = 0; p < predajnikBrojac;) {
		for (int j = 0; j < interliverParam; j++) {
			for (int k = 0; k < 6; k++) {
				interliver[j][k] = zasticenaPorukaPredajnik[p++];
			}
		}

		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < interliverParam; k++) {
				kanal[kanalBrojac++] = interliver[k][j];
			}
		}
	}

	for (int o = miss - 50; o < kanalBrojac; o += 50) {
		kanal[o - 1] ^= true;
		kanal[o + 0] ^= true;
		kanal[o + 1] ^= true;
		kanal[o + 2] ^= true;
	}

	for (int p = 0; p < kanalBrojac;) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < interliverParam; k++) {
				deinterliver[k][j] = kanal[p++];
			}
		}

		for (int j = 0; j < interliverParam; j++) {
			for (int k = 0; k < 6; k++) {
				zasticenaPorukaPrijemnik[prijemnikBrojac++] = deinterliver[j][k];
			}
		}
	}

	for (int p = 0; p < 6 * N2; p += 6) {
		sindrom = 0;
		for (int j = 0; j < 3; j++) {
			sindrom += !(zasticenaPorukaPrijemnik[p + 0] & controlMatrix[0][j] ^
				zasticenaPorukaPrijemnik[p + 1] & controlMatrix[1][j] ^
				zasticenaPorukaPrijemnik[p + 2] & controlMatrix[2][j] ^
				zasticenaPorukaPrijemnik[p + 3] & controlMatrix[3][j] ^
				zasticenaPorukaPrijemnik[p + 4] & controlMatrix[4][j] ^
				zasticenaPorukaPrijemnik[p + 5] & controlMatrix[5][j]) * (int)pow(2, 2 - j);
		}
		if (sindrom != 0 && sindrom != 7) zasticenaPorukaPrijemnik[p + sindrom - 1] ^= true;
	}

	cout << endl << "DekodovanaPoruka(OriginalnaPoruka):" << endl;
	for (int p = 0; p < N * N2; p += 6) {
		if (zasticenaPorukaPrijemnik[p + 3] != generator[p / 2] || zasticenaPorukaPrijemnik[p + 1] != generator[p / 2 + 1] ||
			zasticenaPorukaPrijemnik[p] != generator[p / 2 + 2])
			numOfMisses++;
		cout << zasticenaPorukaPrijemnik[p + 3] << zasticenaPorukaPrijemnik[p + 1] << zasticenaPorukaPrijemnik[p]
			<< "(" << generator[p / 2] << generator[p / 2 + 1] << generator[p / 2 + 2] << ")" << " \n"[(p + 6) % 16 == 0];
	}

	cout << endl<<"Lose je preneto " << numOfMisses * 100/ N2 << "% bitova!";
}
