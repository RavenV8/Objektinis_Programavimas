#include "Funkcijos.cpp"

int main (){
    vector <studentas> mas;
    studentas tempas;
    string failas;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// Skaitymas arba Vedimas //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    
    isvedimas (mas);
    for (auto &i : mas) i.paz.clear();
    mas.clear();
}