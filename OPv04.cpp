#include "Funkcijos.cpp"

int main (){
    vector <studentas> mas;
    studentas tempas;
    vector <studentas> vargsas;
    vector <studentas> kietas;
    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// Generavimas /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    char a;
    bool pasirinkimas; // naudojamas su char a pasirinkimui while cikle
    do
    {
        if((a!='1' && a!='0')){ // 1 arba 0
            cout << "Iveskite 1, jeigu norite sugeneruoti, jeigu norite naudoti esamus - iveskite 0: ";
            cin>>a;
            pasirinkimas = false; // nustamas default
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
        else pasirinkimas = true;
    }while(!pasirinkimas);

    double generav = 0, skaitym, rusiavim, isved, bendras;

    string failodydis;

    if(a=='1'){
        failodydis="1000.txt";
        generavimas(failodydis, 15, generav);
    }
    else failodydis = "Studentai1000.txt";
    
    skaitymas (tempas, mas, skaitym, failodydis);
    rusiavimas(mas, vargsas, kietas, failodydis, rusiavim);
    isvedimas2(vargsas, failodydis, "vargsai.txt", isved);
    bendras=skaitym+rusiavim+isved+generav;
    isvedimas2(kietas, failodydis, "kietas.txt", isved);
    bendras+=isved;
    cout << failodydis << " Elementu failo visas laikas: " << bendras << endl;
    for (int i=0 ; i<41 ; i++) cout<<"-";

    for (auto &i : mas) i.paz.clear();
    mas.clear();
    for (auto &i : vargsas) i.paz.clear();
    vargsas.clear();
    for (auto &i : kietas) i.paz.clear();
    kietas.clear();

    remove("vargsai.txt");  
    remove("kietas.txt"); 
    cout << endl << endl;

    if(a=='1'){
        failodydis="10000.txt";
        generavimas(failodydis, 15, generav);
    }
    else failodydis = "Studentai10000.txt";

    generavimas(failodydis, 15, generav);
    skaitymas (tempas, mas, skaitym, failodydis);
    rusiavimas(mas, vargsas, kietas, failodydis, rusiavim);
    isvedimas2(vargsas, failodydis, "vargsai.txt", isved);
    bendras=skaitym+rusiavim+isved;
    isvedimas2(kietas, failodydis, "kietas.txt", isved);
    bendras+=isved;
    cout << failodydis << " Elementu failo visas laikas: " << bendras << endl;
    for (int i=0 ; i<41 ; i++) cout<<"-";

    for (auto &i : mas) i.paz.clear();
    mas.clear();
    for (auto &i : vargsas) i.paz.clear();
    vargsas.clear();
    for (auto &i : kietas) i.paz.clear();
    kietas.clear();  

    remove("vargsai.txt");  
    remove("kietas.txt");  
    cout << endl << endl;

    if(a=='1'){
        failodydis="100000.txt";
        generavimas(failodydis, 15, generav);
    }
    else failodydis = "Studentai100000.txt";

    generavimas(failodydis, 15, generav);
    skaitymas (tempas, mas, skaitym, failodydis);
    rusiavimas(mas, vargsas, kietas, failodydis, rusiavim);
    isvedimas2(vargsas, failodydis, "vargsai.txt", isved);
    bendras=skaitym+rusiavim+isved;
    isvedimas2(kietas, failodydis, "kietas.txt", isved);
    bendras+=isved;
    cout << failodydis << " Elementu failo visas laikas: " << bendras << endl;
    for (int i=0 ; i<41 ; i++) cout<<"-";

    for (auto &i : mas) i.paz.clear();
    mas.clear();
    for (auto &i : vargsas) i.paz.clear();
    vargsas.clear();
    for (auto &i : kietas) i.paz.clear();
    kietas.clear();

    remove("vargsai.txt");  
    remove("kietas.txt");
    cout << endl << endl;

    if(a=='1'){
        failodydis="1000000.txt";
        generavimas(failodydis, 15, generav);
    }
    else failodydis = "Studentai1000000.txt";

    generavimas(failodydis, 15, generav);
    skaitymas (tempas, mas, skaitym, failodydis);
    rusiavimas(mas, vargsas, kietas, failodydis, rusiavim);
    isvedimas2(vargsas, failodydis, "vargsai.txt", isved);
    bendras=skaitym+rusiavim+isved;
    isvedimas2(kietas, failodydis, "kietas.txt", isved);
    bendras+=isved;
    cout << failodydis << " Elementu failo visas laikas: " << bendras << endl;
    for (int i=0 ; i<41 ; i++) cout<<"-";

    for (auto &i : mas) i.paz.clear();
    mas.clear();
    for (auto &i : vargsas) i.paz.clear();
    vargsas.clear();
    for (auto &i : kietas) i.paz.clear();
    kietas.clear();

    remove("vargsai.txt");  
    remove("kietas.txt"); 
    cout << endl << endl;

    if(a=='1'){
        failodydis="10000000.txt";
        generavimas(failodydis, 15, generav);
    }
    else failodydis = "Studentai10000000.txt";

    generavimas(failodydis, 15, generav);
    skaitymas (tempas, mas, skaitym, failodydis);
    rusiavimas(mas, vargsas, kietas, failodydis, rusiavim);
    isvedimas2(vargsas, failodydis, "vargsai.txt", isved);
    bendras=skaitym+rusiavim+isved;
    isvedimas2(kietas, failodydis, "kietas.txt", isved);
    bendras+=isved;
    cout << failodydis << " Elementu failo visas laikas: " << bendras << endl;
    for (int i=0 ; i<41 ; i++) cout<<"-";

    for (auto &i : mas) i.paz.clear();
    mas.clear();
    for (auto &i : vargsas) i.paz.clear();
    vargsas.clear();
    for (auto &i : kietas) i.paz.clear();
    kietas.clear();

    remove("vargsai.txt");  
    remove("kietas.txt");

    if(a=='1'){
        remove("1000.txt");
        remove("10000.txt");
        remove("100000.txt");
        remove("1000000.txt");
        remove("10000000.txt");
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// Skaitymas arba Vedimas //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    char a; // naudojamas paimti duomenis apie vartotojo pasirinkima del nuskaitymo
    bool pasirinkimas; // naudojamas su char a pasirinkimui while cikle
    do
    {
        if((a!='1' && a!='0')){ // 1 arba 0
            cout << "Spauskite 1 jeigu norite, kad nuskaitytu is failo arba 0 jeigu norite vesti/generuoti duomenis: ";
            cin>>a;
            pasirinkimas = false; // nustatomas default
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
        else pasirinkimas = true;
    }while(!pasirinkimas);

    if(a==((int)'1')) skaitymas(tempas, mas);
    else{
        char uzkl='n';
        do {
            pild(tempas);
            mas.push_back(tempas);
            tempas.paz.clear();
            cout<<"Baigti darba spausk n, testi - bet koks klavisas: ";
            cin>>uzkl;
        } while (uzkl != 'n' && uzkl!= 'N');
    }
    
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// Lenteles formavimas ir valymas //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    isvedimas (mas); */    
    for (auto &i : mas) i.paz.clear();
    mas.clear();
}
