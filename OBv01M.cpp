#include "Masyvo.h"

#define arr_size 10000
const string P[11] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

struct studentas{
    string vardas, pavarde;
    int* paz;
    int egz, k=0;
};

int* papildymas (int *mas, int n){
    int* naujas;
  naujas = new int[n+1];

  for(int i=0; i<n; i++)
    naujas[i] = mas[i];

  delete[] mas;
  return naujas;
}

void pild (studentas &temp){
    string p="0";
    bool paz=false;
    int x=1, v;
    cout << "Iveskite varda: "; cin >> temp.vardas;
    cout << "Iveskite pavarde: "; cin >> temp.pavarde;
    cout << setfill('-') << setw(50) << '-' << setfill(' ') << endl;
    cout<<"Iveskite 1 jeigu norite ranka irasyti pazymius, jeigu norite kad sugeneruotu spauskite betka: "; cin>>v;
    cout << setfill('-') << setw(50) << '-' << setfill(' ') << endl;
    if (v == 1) {  
        while(p != "q") {
            cout << "Iveskite " << temp.k+1 << "-a(-i) pazymi arba q, jei norite baigti: ";
            cin >> p;
            if ( p=="q") break;
            for (int i=0; i<11; i++)
            if (p == P[i]) paz=true;
            if (paz==false) cout<<"Ivestis bloga."<<endl;
            if (p != "q" && paz) {
                temp.paz = papildymas(temp.paz, temp.k);
                temp.paz[temp.k] = stoi(p);
                temp.k++;
            }
        paz=false;
        }

         while(!paz) {
            cout << setfill('-') << setw(50) << '-' << setfill(' ') << endl;
            cout << "Iveskite egzamino iverti: ";
            cin >> p;
            for (int i=0; i<11; i++)
                if (p == P[i]) paz=true;
            if (paz==false) cout<<"Ivestis bloga."<<endl;
            if (paz) temp.egz = stoi(p);
        }
    } else {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist (0, 10);

        int m;
        cout<<"Kiek pazymiu sugeneruoti? "; cin>>m;
        for (int i=0 ; i<m ; i++) {
            temp.paz = papildymas(temp.paz, temp.k);
            temp.paz[temp.k]=dist(mt);
            temp.k++;           
         }
        temp.egz=dist((mt));
    }
}

double mediana (studentas &temp){
    double mediana;
    bool rikiuoti=true;
    while (rikiuoti){
        rikiuoti=false;
        for (int i=0;i<temp.k-1;i++){
            if (temp.paz[i]<temp.paz[i+1]){
                swap(temp.paz[i], temp.paz[i+1]);
                rikiuoti=true;
            }
        }
    }
    //std::sort(temp.paz[0], temp.paz[temp.k-1]);
    int vid=temp.k/2;
    return temp.k % 2 == 0 ? double((temp.paz[vid-1]+temp.paz[vid]))/2: temp.paz[vid];
}

double galutinis(studentas& temp, int a) {
    double v=0;
    if (a == 0) {
      v = accumulate(temp.paz, temp.paz + temp.k, v) * 1.0 / temp.k;
    }
    else v = mediana(temp);
  
  return v*0.4 + 0.6*temp.egz;
}

void spausd(studentas &temp, int a){
    cout << setw(15) << temp.vardas << setw(15) << temp.pavarde << setw(19) << fixed << setprecision(2) << galutinis(temp, a) << endl;
    delete temp.paz;
}

int main () {
    studentas *mas;
    mas=new studentas[arr_size];
    int n=0, a;

    char uzkl = 'n';
    do
    {
        pild(mas[n]);
        cout << setfill('-') << setw(50) << '-' << setfill(' ') << endl;
        cout << "Baigti darba spausk n, testi - bet koks klavisas: " << endl;
        cout << setfill('-') << setw(50) << '-' << setfill(' ') << endl;
        n++;
        cin >> uzkl;
    } while (uzkl!='n' && uzkl!='N');

    cout << setfill('-') << setw(50) << '-' << setfill(' ') << endl;
    cout<<"Jeigu norite matyti galutini vidurki iveskite 0, Jeigu norite matyti galutine mediana iveskite 1 "; cin>>a;
    cout << setfill('-') << setw(50) << '-' << setfill(' ') << endl;

    cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas";

    if (a == 1) cout << setw(20) << "Galutinis (Med.)" << endl;
    else cout << setw(20) << "Galutinis (Vid.)" << endl;

    cout << setfill('-') << setw(50) << '-' << setfill(' ') << endl;

    for (int i = 0; i < n; i++) spausd(mas[i], a);
    delete [] mas;
}