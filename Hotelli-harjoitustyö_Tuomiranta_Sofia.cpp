// Sofia Tuomiranta
// Hotelli-harjoitusty�, 2 p

#include <iostream>  // Otetaan kirjain ja lukutoiminnot k�ytt��n
#include <string>  // Sis�lt�� string-tietotyypin
#include <cstdlib> // Sis�lt� satunnaislukujen generaattorin
#include <ctime>  // Sis�lt�� toiminnot ajan k�sittelyyn

using namespace std;  // Otetaan k�ytt��n standardi nimiavaruus

// M��ritell��n huonetyypit enum-tietotyypill�
enum HuoneTyyppi { YHDEN_HENGEN, KAHDEN_HENGEN };

// Rakenne, joka tallentaa varauksen tiedot
struct Varaus {
    string nimi;  // Varaajan nimi
    int huoneNumero;  // Huoneen numero
    int oidenMaara;  // �iden m��r�
    HuoneTyyppi tyyppi;  // Huonetyyppi (yhden hengen tai kahden hengen)
    double hinta;  // Varauksen kokonaishinta
};

// Vakio, joka m��ritt�� huoneiden kokonaism��r�n
const int HUONEITA = 100;

// Vakio yhden hengen huoneen hinnalle per y�
const double HINTA_YHDEN_HENGEN = 100.0;

// Vakio kahden g�hengen huoneelle per y�
const double HINTA_KAHDEN_HENGEN = 150.0;

// Funktio, joka tarkistaa onko huone jo varattu
bool onkoHuoneVarattu(Varaus varaukset[], int huoneNumero, HuoneTyyppi tyyppi, int varaustenMaara) 
{
    for (int i = 0; i < varaustenMaara; i++)  // K�yd��n l�pi kaikki varaukset
    {
        if (varaukset[i].huoneNumero == huoneNumero && varaukset[i].tyyppi == tyyppi) 
        {
            return true;  // Palautetaan true, jos huone ja tyyppi t�sm��v�t
        }
    }
    return false;  // Palautetaan false, jos huonetta ei l�ytynyt varauksista
}

// Funktio joka laskee varauksen kokonaishinnan
double laskeHinta(HuoneTyyppi tyyppi, int oidenMaara)
{
    double hintaPerYo = (tyyppi == YHDEN_HENGEN) ? HINTA_YHDEN_HENGEN : HINTA_KAHDEN_HENGEN;  // Valitaan hinnasto tyypin mukaan
    return hintaPerYo * oidenMaara; // Lasketaan hinta kertomalla y�hinta �iden m��r�ll�
}


// Funktio, joka tulostaa varauksen tiedot
void tulostaVaraus(Varaus varaus) 
{
    cout << "Nimi: " << varaus.nimi << endl;  // Tulostetaan varaajan nimi
    cout << "Huone: " << varaus.huoneNumero << endl; // Tulostetaan huoneen numero
    cout << "�it�: " << varaus.oidenMaara << endl;  // Tulostetaan �iden m��r�
    cout << "Tyyppi: " << (varaus.tyyppi == YHDEN_HENGEN ? "Yhden hengen" : "Kahden hengen") << endl;  // Tulostetaan huonetyyppi
    cout << "Hinta: " << varaus.hinta << " �" << endl;  // Tulostetaan kokonaishinta
}

int main()  // T�st� alkaa p��ohjelma
{
    setlocale(LC_ALL, "fi-FI");  // Otetaan ��kk�set k�ytt��n p��ohjelmaan
    srand(time(0)); // Alustetaan satunnaislukugeneraattori ajan perusteella

    Varaus varaukset[HUONEITA]; // Luodaan taulukko, johon varaukset tallennetaan
    int varaustenMaara = 0; // Alustetaan varauksien lukum��r� nollaksi

    int valinta;  // Muuttuja k�ytt�j�n valintaa varten
    do 
    {
        // Tulostetaan p��valikko
        cout << "\nP��valikko:" << endl;  
        cout << "1. Varaa huone" << endl;  // Valinta 1: Uuden varauksen tekeminen
        cout << "2. N�yt� varaukset" << endl;  // Valinta 2: Kaikkien varaustn tarkastelu
        cout << "0. Lopeta" << endl;  // Valinta 0; ohjelman lopettaminen
        cout << "Valitse: ";  // Pyydet��n k�ytt�j�� valitsemaan toiminto
        cin >> valinta;  // Tallennetaan k�ytt�j�n sy�te muuttujaan-valinta

        switch (valinta) {
        case 1: 
        {
            // Jos valittiin toiminto 1 
            if (varaustenMaara < HUONEITA) // tarkistetaan, onko huoneita vapaana
            {
                string nimi;  // Muuttuha varaajan nimelle
                int huoneNumero;  // Muuttuja huoneen numerolle
                int oidenMaara;  // Muuttuja �iden m��r�lle
                HuoneTyyppi tyyppi;  // Muuttuja huonetyypille

                cout << "Anna nimi: ";  // Pyydet��n varaajan nimi
                cin.ignore(); // Tyhjennet��n sy�tepuskuri edellisen rivin j�ljilt�
                getline(cin, nimi);  // Luetaan varaajan nimi

                // Kysyt��n k�ytt�j�lt� huonetyyppi
                cout << "Valitse huonetyyppi (1 = yhden hengen, 2 = kahden hengen): ";
                int tyyppiValinta;  // Muuttuja k�ytt�j�n huonetyyppivalintaa varten
                cin >> tyyppiValinta;  // Tallennetaan k�ytt�j�n sy�te muuttujaan-tyyppiValinta
                tyyppi = tyyppiValinta == 1 ? YHDEN_HENGEN : KAHDEN_HENGEN;  // M��ritet��n huonetyyyppi valinnan perusteella

                // Arvotaan vapaa huonenumero
                do 
                {
                    huoneNumero = rand() % HUONEITA + 1;  // Arvotaan numero v�lilt� 1-huoneita
                } while (onkoHuoneVarattu(varaukset, huoneNumero, tyyppi, varaustenMaara));  // Toistetaan, kunnes l�ytynyt huone ei ole varattu

                cout << "Anna �iden m��r�: ";  // Pyydet��n k�ytt�j�lt� �iden m��r�
                cin >> oidenMaara;  // Tallennetaan k�ytt�h�n sy�te muuttujaan-oidenMaara

                // Tallennetaan usi varaus taulukkoon
                varaukset[varaustenMaara].nimi = nimi;  // Tallennetaan nimi
                varaukset[varaustenMaara].huoneNumero = huoneNumero;  // Tallennetaan huoneen numero
                varaukset[varaustenMaara].oidenMaara = oidenMaara;  // Tallennetaan �iden m��r�
                varaukset[varaustenMaara].tyyppi = tyyppi; // Tallennetaan huonetyyppi
                varaukset[varaustenMaara].hinta = laskeHinta(tyyppi, oidenMaara); // Tallennetaan laskettu hinta
                varaustenMaara++; // Kasvatetaan varausten lukum��r��

                cout << "Huone varattu!" << endl;  // Ilmoitetaan varauksen onnistuminen
            }
            else {
                cout << "Kaikki huoneet ovat varattuja." << endl; // Ilmoitetaan k�ytt�j�lle ettei varaus ole mahdollinen
            }
            break;  // Lopetetaan case 1
        }
        case 2:
            // Jos valinta on 2
            for (int i = 0; i < varaustenMaara; i++) {  // K�yd��n l�pi kaikki varaukset
                tulostaVaraus(varaukset[i]);  // Tulostetaan yksitt�isen varauksen tiedot
                cout << endl;  // Tulostetaan tyhj� rivi
            }
            break;  // Lopetetaan case 2

        case 0:  // Jos valinta on 0
            cout << "Kiitos ja n�kemiin!" << endl;  // Tulostetaan hyv�stelyviesti
            break;  // Lopetetaan case 0
        default:  // Jos valinta ei vastaa mit��n yll� olevista
            cout << "Virheellinen valinta." << endl;  // Ilmoitetaan virheellisest� sy�tteest�
        }
    } while (valinta != 0);  // Toistetaan kunnes k�ytt�j� valistee lopetuksen (case 0)

    return 0; // Ohjelma on onnistunut (palautetaan 0)
}
