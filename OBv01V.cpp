#include "Vektoriaus.h"

struct studentas{
    string vardas, pavarde;
    vector <int> paz;
    int egz;
};

void pild (studentas &temp){
    cout<<"Iveskite varda ir pavarde: "; cin>>temp.vardas>>temp.pavarde;
    int x, a;
    cout<<"Iveskite 1, jeigu norite kad pazymiai butu generuojami atsitiktinai, jeigu nenorite paspauskite bet kuri klavisa: "; cin>>a;
    if (a != 1){
        cout<<"Iveskite paz.";
        while (cin>>x) {
            if (x<0 || x>10) {
                cout<<"Ivedete bloga skaiciu, iveskite is naujo ";
            } else temp.paz.push_back(x);
        }
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout<<"Iveskite egzamino paz."; cin>>temp.egz;
        while (temp.egz<0 || temp.egz>10) {
            if (temp.egz<0 || temp.egz>10) {
                cout<<"Ivedete bloga skaiciu, iveskite is naujo ";
                cin>>temp.egz;
         }
        }
    } else {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist (0, 10);

        int n;
        cout<<"Kiek pazymiu sugeneruoti? "; cin>>n;
        for (int i=0 ; i<n ; i++) temp.paz.push_back(dist(mt));
        temp.egz=dist((mt));
    }
}

double mediana (studentas& temp) {
    double mediana;
    int size = temp.paz.size();
    int vid=size/2;
    sort(temp.paz.begin(), temp.paz.end());
    mediana = size % 2 == 0 ? double((temp.paz[vid-1]+temp.paz[vid]))/2: temp.paz[vid];
    return mediana;
}

double galutinis(studentas& temp, int a) {
  double v=0;
  if (temp.paz.size() > 0) {
    if (a == 1) {
      v = std::accumulate(temp.paz.begin(), temp.paz.end(), v) * 1.0 / temp.paz.size();
    }
    else v = mediana(temp);
  }
  
  return v*0.4 + 0.6*temp.egz;
}

void spausd(studentas &temp, int x) {
    cout<<setw(10)<<left<<temp.vardas<<setw(15)<<left<<temp.pavarde;
    cout<<fixed<<setprecision(2)<<galutinis(temp, x)<<endl;
}

int main (){
    

    vector <studentas> mas;
    studentas tempas;
    char uzkl='n';
    do {
        pild(tempas);
        mas.push_back(tempas);
        tempas.paz.clear();
        cout<<"Baigti darba spausk n, testi - bet koks klavisas: ";
        cin>>uzkl;
    } while (uzkl != 'n' && uzkl!= 'N');

    string galutinis;
    int x;
    cout<<"Jeigu norite matyti vidurki spauskite 1, jeigu norite matyti mediana spauskite 0: "; cin>>x;
    galutinis = x == 1 ? galutinis="(Vid.)" : galutinis="(Med.)";
    cout<<setw(10)<<left<<"Vardas"<<setw(15)<<left<<"Pavarde"<<"Galutinis "<<galutinis<<endl;
    for (int i=0 ; i<41 ; i++) cout<<"-";
    cout<<endl;
    for (auto &i : mas) spausd(i, x);
    for (auto &i : mas) i.paz.clear();
    mas.clear();
}