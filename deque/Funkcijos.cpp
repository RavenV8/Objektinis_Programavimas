#include "Vektoriaus.h"

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

void skaitymas (studentas &temp, deque <studentas> &mas, double &skaitym, string failodydis) {
    deque<string> splited;
    string eil, df=failodydis;

    skaitym=0;

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
    auto start = std::chrono::high_resolution_clock::now(); auto st=start;
    while (open_f){ 
      if (!open_f.eof()) { // skaito iki kol baigiasi failas
          std::getline(open_f, eil);
          splited.push_back(eil);}
      else break;
    }
    open_f.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    failodydis.erase(std::remove(failodydis.begin(), failodydis.end(), '.'), failodydis.end());
    failodydis.erase(std::remove(failodydis.begin(), failodydis.end(), 't'), failodydis.end()); /// is pavadinimo pasidaryti dydi
    failodydis.erase(std::remove(failodydis.begin(), failodydis.end(), 'x'), failodydis.end());

    std::cout << failodydis << " elementu failo nuskaitymas uztruko: "<< diff.count() << " s\n";

    skaitym=diff.count(); // grazina laiko skirtuma

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
bool palyginimas2 (studentas &a, studentas &b) {
    return a.bendr < b.bendr;
}


void isvedimas(deque<studentas> &temp){
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

        auto start = std::chrono::high_resolution_clock::now();

        out<<setw(10)<<left<<"Vardas"<<setw(15)<<left<<"Pavarde"<<"Galutinis "<<galutinis<<endl;
        for (int i=0 ; i<41 ; i++) out<<"-";
        out<<endl;
        for(int i = 0; i < temp.size(); i ++) {
            out << setw(15) << temp[i].vardas << setw(15) << temp[i].pavarde << setw(19) << fixed << setprecision(2) << vidurkis(temp[i], x) << endl;
        }
        out.close();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << "Failo isvedimas truko:  "<< diff.count() << " s\n";
       }
}
void generavimas(string filename, int kiek, double &generav){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist (0, 10);

    generav = 0;

    std::ofstream rf (filename); // kokiu pavadinimu issaugojima

    filename.erase(std::remove(filename.begin(), filename.end(), '.'), filename.end());
    filename.erase(std::remove(filename.begin(), filename.end(), 't'), filename.end());
    filename.erase(std::remove(filename.begin(), filename.end(), 'x'), filename.end());
    int studKiek = stoi(filename);

    auto start = std::chrono::high_resolution_clock::now();

    rf << setw(25) << left << "Vardas" << setw(25) << left << "Pavarde";
    for (int i=0 ; i<kiek ; i++){
        rf << setw(5) << left << "ND"+to_string(i+1); // pazymiams taskai
    }
    rf << "Egz." << endl;

    for (int i=0; i<studKiek ; i++) {
        rf << setw(25) << left << "Vardas"+to_string(i+1) << setw(25) << left << "Pavarde"+to_string(i+1);
        for (int j=0 ; j<kiek ; j++) {
            rf << setw(5) << left << dist(mt);
        }
        rf << dist(mt) << endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << filename << " elementu sugeneruoti uztruko: "<< diff.count() << " s\n";

    generav=diff.count();

}
void rusiavimas (deque <studentas> &temp, deque <studentas> &vargsas, deque <studentas> &kietas, string failodydis, double &rusiavim) {

    rusiavim=0;

    failodydis.erase(std::remove(failodydis.begin(), failodydis.end(), '.'), failodydis.end());
    failodydis.erase(std::remove(failodydis.begin(), failodydis.end(), 't'), failodydis.end());
    failodydis.erase(std::remove(failodydis.begin(), failodydis.end(), 'x'), failodydis.end());

    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i=0 ; i<temp.size() ; i++) { // tikrinamas vidurkis kad paskui priskirti prie vienos ar kitos grupes
        temp[i].bendr=vidurkis(temp[i], 1);
        if (temp[i].bendr < 5) {
            vargsas.push_back(temp[i]);
        } else kietas.push_back(temp[i]);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << failodydis << " elementu suskirstymas i vargsus ir kietus uztruko: "<< diff.count() << " s\n";

    rusiavim=diff.count();

    start = std::chrono::high_resolution_clock::now();

    sort(vargsas.begin(), vargsas.end(), palyginimas2);
    sort(kietas.begin(), kietas.end(), palyginimas2);


    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << failodydis << " vargsu ir kietu elementu rusiavimas uztruko: "<< diff.count() << " s\n";

    rusiavim+=diff.count();

}
void isvedimas2 (deque <studentas> &temp, string failodydis, string tipas, double &isved) {
    
    std::ofstream out(tipas);

    isved=0;

    auto start = std::chrono::high_resolution_clock::now();

    out<<setw(10)<<left<<"Vardas"<<setw(15)<<left<<"Pavarde"<<"Galutinis (Vid.)" <<endl;
    for (int i=0 ; i<41 ; i++) out<<"-";
    cout << endl;
    for(int i = 0; i < temp.size(); i ++) {
        out << setw(15) << temp[i].vardas << setw(15) << temp[i].pavarde << setw(19) << fixed << setprecision(2) << temp[i].bendr << endl;
        }
    out.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    failodydis.erase(std::remove(failodydis.begin(), failodydis.end(), '.'), failodydis.end());
    failodydis.erase(std::remove(failodydis.begin(), failodydis.end(), 't'), failodydis.end());
    failodydis.erase(std::remove(failodydis.begin(), failodydis.end(), 'x'), failodydis.end());

    std::cout << failodydis << " failu elemento " << tipas << " isvedimas uztruko: " << diff.count() << " s\n";

    isved=diff.count();
}