#include<iostream>
#include<string>
#include<time.h>

using namespace std;

//cheia formata din 2 numere
struct cheie {
	int a;
	int b;
};

//functie pentru modulo
int modulo(int a, int b)
{
	int r = a % b;
	return r < 0 ? r + b : r;
}

//functie care face cmmdc dintre un numar si 26 si returneaza 1 daca cmmdc este 1, iar altfel returneaza 0
int cmmdc(int a) {
	int b = 26;
	while (a != b) {
		if (a > b) {
			a = a - b;
		}
		else
		{
			b = b - a;
		}
	}
	if (a == 1) {
		return 1;
	}
	else
	{
		return 0;
	}
}

//functie care returneaza simetricul unui numar in raport cu 26
int simetric(int a) {
	int x = 1;
	while ((a * x) % 26 != 1) {
		x++;
	}
	return x;
}

//functie de criptare care primeste ca parametrii mesajul in clar si cheia; functia returneaza mesajul criptat
string criptare(string mesaj_clar, int a, int b) {
	int cuv;
	string mesaj_criptat = mesaj_clar;
	for (int i = 0; i < mesaj_clar.size(); i++) {
		if (mesaj_clar[i] == ' ') {
			mesaj_criptat[i] = ' ';
		}
		else {
			mesaj_criptat[i] = ((a * (mesaj_clar[i] - 97) + b) % 26) + 97;
		}
	}
	return mesaj_criptat;
}

//functie de decriptare care primeste ca parametrii mesajul criptat si cheia; functia returneaza mesajul decriptat
string decriptare(string mesaj_criptat, int a, int b) {
	int cuv;
	string mesaj_decriptat = mesaj_criptat;
	for (int i = 0; i < mesaj_criptat.size(); i++) {
		if (mesaj_criptat[i] == ' ') {
			mesaj_decriptat[i] = ' ';
		}
		else {
			mesaj_decriptat[i] = modulo(simetric(a) * (mesaj_criptat[i] - 97 - b), 26) + 97;
		}
	}
	return mesaj_decriptat;
}

//functie care simuleaza un atac cu forta bruta asupra cifrului afin in conditiile in care afla primele doua caractere ale mesajului in clar
void brute_force_attack(string hint, string interceptat, string test) {
	int ok = 1, cheie1, cheie2;
	for (int i = 1; i < 26; i++) {
		if (cmmdc(i) == 1) {
			for (int j = 0; j < 26; j++) {
				test = criptare(hint, i, j);
				if (test == interceptat) {
					ok = 0;
					cheie1 = i;
					cheie2 = j;
					break;
				}
			}
		}
		if (ok == 0) {
			break;
		}
	}

	cout << endl << "Rezultate brute force attack:" << endl;
	cout << "Prima cheie= " << cheie1 << "; A doua cheie= " << cheie2 << endl;
}

int main() {
	string mesaj_clar;
	cout << "Mesajul in clar: ";
	getline(cin, mesaj_clar);

	//cheia este generata aleator
	cheie key;
	srand(time(NULL));

	//1<= a <=25 si cmmdc-ul dintre a si 26 trebuie sa fie 1
	key.a = (rand() % 25) + 1;
	while (cmmdc(key.a) != 1) {
		key.a = (rand() % 25) + 1;
	}

	//0<= b <=25
	key.b = rand() % 26;

	cout << "a= " << key.a << endl << "b= " << key.b << endl;

	string mesaj_criptat = mesaj_clar;
	mesaj_criptat = criptare(mesaj_clar, key.a, key.b);
	cout << "Mesajul criptat: " << mesaj_criptat << endl;

	string mesaj_decriptat = mesaj_clar;
	mesaj_decriptat = decriptare(mesaj_criptat, key.a, key.b);
	cout << "Mesajul decriptat: " << mesaj_decriptat << endl;


	string hint = mesaj_clar;
	hint.resize(2);
	string interceptat = mesaj_criptat;
	interceptat.resize(hint.size());
	string test = hint;

	brute_force_attack(hint, interceptat, test);

	return 0;
}