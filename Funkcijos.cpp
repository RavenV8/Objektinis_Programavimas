#include "Vektoriaus.h"

struct studentas{
    string vardas, pavarde;
    vector <int> paz;
    int egz;
};

void pild (studentas &temp){
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// Vardas ir Pavarde ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    cout<<"Iveskite varda ir pavarde: "; cin>>temp.vardas>>temp.pavarde;
    char a; // naudojamas pasirinkti tarp generavimo ir vedimo (1 arba 0)
    int x;  // naudojamas surasyti pazymius (0-10)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// Sugeneruoti arba Suvesti ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool pasirinkimas; // naudojamas su char a pasirinkimui while cikle
    do
    {
        if((a!='1' && a!='0')){ // 1 arba 0
            cout << "Iveskite 1, jeigu norite kad pazymiai butu generuojami, jeigu norite suvesti patys - iveskite 0: ";
            cin>>a;
            pasirinkimas = false; // nustamas default
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
        else pasirinkimas = true;
    }while(!pasirinkimas);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// Pazymiu vedimas /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (a == '0'){
        cout<<"Iveskite paz. (0-10). Jei norite uzbaigti vedima parasykite raide: ";
        while (cin>>x) { // duoda vesti pazymius. sustabdyti - irasyti raide
            if (x<0 || x>10) {
                cout<<"Ivedete netinkama skaiciu (galima ivesti 0-10). Siuo metu esate ivede "<<temp.paz.size()<<" skaicius. "<<"Jei norite uzbaigti parasykite raide: ";
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            } else temp.paz.push_back(x);
        }
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// Egzamino vedimas ////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        pasirinkimas = false; //nu defaultinamas pasirinkimas
        cout<<"Iveskite egzamino paz. (0-10): ";
        do{
            if(cin>>temp.egz){
                if(temp.egz<0 || temp.egz>10) cout<<"Ivedete netinkama skaiciu (iveskite 0-10): ";
                else pasirinkimas = true;
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            }
            else{ // jei ivedama raide tai pafailinama
                cout<<"Ivedete netinkama simboli (iveskite 0-10): ";
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            } 
        }while(!pasirinkimas);
    }
        
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// Pazymiu generavimas /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////   
    else {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist (0, 10);

        int n;
        pasirinkimas = false;
        cout<<"Kiek pazymiu sugeneruoti?: ";
        do{
            if(cin>>n){
                if(n<0) cout<<"Ivedete neigiama/netinkama skaiciu. Bandykite dar karta: "; // nebutina cia, nes nefiksuoja neigiamu ir taip
                else pasirinkimas = true;
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            }
            else{
                cout<<"Ivedete netinkama skaiciu. Bandykite dar karta: ";
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            } 
        }while(!pasirinkimas);
        for (int i=0 ; i<n ; i++) temp.paz.push_back(dist(mt));
        temp.egz=dist((mt));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// Skaitymas ///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////  

void skaitymas (studentas &temp, vector <studentas> &mas) {
    vector<string> splited;
    string eil, df;

    cout<<"Iveskite failo pavadinima: "; cin>>df;

    try {
        std::ifstream open_f(df);
        if(open_f.fail())
        throw df;
    } 
    catch(string klaida) {
        cout << "Dokumento pavadinimu "<< klaida << " nera." << endl;
        cout << "Bandykite ijungti programa is naujo ir patikrinti ar nepadarete klaidu." << endl;
        exit (0);
  }

    std::ifstream open_f(df);
    while (open_f){ 
      if (!open_f.eof()) { // skaito iki kol baigiasi failas
          std::getline(open_f, eil);
          splited.push_back(eil);}
      else break;
    }
    open_f.close();

    stringstream ss(splited[0]); // pirmoji perskelta eilute yra pradine ivestis
    string word;
    int count = 0; // suskaiciuoti kiek yra zodziu
    while (ss >> word) // 
        count++;

    int pazymys;
    for (int i=1;i<splited.size();i++){
        stringstream ss(splited[i]);
        ss >> temp.vardas >> temp.pavarde;
        for (int i=0;i<count-3;i++){ // du - vardas ir pavarde ir dar vienas egzaminas
            ss >> pazymys;
            temp.paz.push_back(pazymys);
        }
        ss >> temp.egz;
        mas.push_back(temp);
        temp.paz.clear();
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// Mediana /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////   
double mediana (studentas& temp) {
    double mediana;
    int size = temp.paz.size();
    int vid=size/2;
    sort(temp.paz.begin(), temp.paz.end());
    mediana = size % 2 == 0 ? double((temp.paz[vid-1]+temp.paz[vid]))/2 : temp.paz[vid];
    return mediana;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// Vidurkis //////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////   
double vidurkis(studentas& temp, int a) {
  double v=0;
  if (temp.paz.size() > 0) {   
    if (a == 1) {
      double suma = 0.0;
      for (int pazymys : temp.paz) suma += pazymys;
      v = suma / temp.paz.size();
    }
    else v = mediana(temp);
  }
  
  return v*0.4 + 0.6*temp.egz;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// Išvedimas ir Sort ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool palyginimas (studentas &a, studentas &b) {
    return a.vardas < b.vardas;
}

void isvedimas(vector<studentas> &temp){
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// Vidurkis arba Mediana ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string galutinis;
    char a, x;
    bool pasirinkimas; // naudojamas su char a pasirinkimui while cikle
    do
    {
        if((x!='1' && x!='0')){ // 1 arba 0
            cout << "Jeigu norite matyti vidurki iveskite 1, jeigu norite matyti mediana iveskite 0: ";
            cin>>x;
            pasirinkimas = false;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
        else pasirinkimas = true;
    }while(!pasirinkimas);
    galutinis = x == '1'? galutinis="(Vid.)" : galutinis="(Med.)";

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// TXT arba Terminal ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    pasirinkimas = false; // naudojamas su char a pasirinkimui while cikle
    do
    {
        if((a!='1' && a!='0')){ // 1 arba 0
            cout << "Jeigu norite isvesti i TXT iveskite 1, jeigu norite isvesti i terminal iveskite 0: ";
            cin>>a;
            pasirinkimas = false;
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
        else pasirinkimas = true;
    }while(!pasirinkimas);
    galutinis = a == '1'? galutinis="(Vid.)" : galutinis="(Med.)";
    
       sort(temp.begin(), temp.end(), palyginimas);

       if(a==0){ // i terminal isvesti
        cout<<setw(10)<<left<<"Vardas"<<setw(15)<<left<<"Pavarde"<<"Galutinis "<<galutinis<<endl;
        for (int i=0 ; i<41 ; i++) cout<<"-";
        cout<<endl;
        for(int i = 0; i < temp.size(); i ++) {
            cout << setw(15) << temp[i].vardas << setw(15) << temp[i].pavarde << setw(19) << fixed << setprecision(2) << vidurkis(temp[i], x) << endl;
        }
       }
       else{ // i txt isvesti
        string txt_pavadinimas; // failo pavadinimas
        cout<<"Iveskite rezultatu failo pavadinima: ";cin>>txt_pavadinimas;
        std::ofstream out(txt_pavadinimas);

        out<<setw(10)<<left<<"Vardas"<<setw(15)<<left<<"Pavarde"<<"Galutinis "<<galutinis<<endl;
        for (int i=0 ; i<41 ; i++) out<<"-";
        out<<endl;
        for(int i = 0; i < temp.size(); i ++) {
            out << setw(15) << temp[i].vardas << setw(15) << temp[i].pavarde << setw(19) << fixed << setprecision(2) << vidurkis(temp[i], x) << endl;
        }
        out.close();
       }
}
