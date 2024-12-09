// Sofia Tuomiranta
// Hotelli-harjoitustyö, 2 p

#include <iostream>  // Otetaan kirjain ja lukutoiminnot käyttöön
#include <string>  // Sisältää string-tietotyypin
#include <cstdlib> // Sisältä satunnaislukujen generaattorin
#include <ctime>  // Sisältää toiminnot ajan käsittelyyn

using namespace std;  // Otetaan käyttöön standardi nimiavaruus

// Määritellään huonetyypit enum-tietotyypillä
enum HuoneTyyppi { YHDEN_HENGEN, KAHDEN_HENGEN };

// Rakenne, joka tallentaa varauksen tiedot
struct Varaus {
    string nimi;  // Varaajan nimi
    int huoneNumero;  // Huoneen numero
    int oidenMaara;  // Öiden määrä
    HuoneTyyppi tyyppi;  // Huonetyyppi (yhden hengen tai kahden hengen)
    double hinta;  // Varauksen kokonaishinta
};

// Vakio, joka määrittää huoneiden kokonaismäärän
const int HUONEITA = 100;

// Vakio yhden hengen huoneen hinnalle per yö
const double HINTA_YHDEN_HENGEN = 100.0;

// Vakio kahden g¨hengen huoneelle per yö
const double HINTA_KAHDEN_HENGEN = 150.0;

// Funktio, joka tarkistaa onko huone jo varattu
bool onkoHuoneVarattu(Varaus varaukset[], int huoneNumero, HuoneTyyppi tyyppi, int varaustenMaara) 
{
    for (int i = 0; i < varaustenMaara; i++)  // Käydään läpi kaikki varaukset
    {
        if (varaukset[i].huoneNumero == huoneNumero && varaukset[i].tyyppi == tyyppi) 
        {
            return true;  // Palautetaan true, jos huone ja tyyppi täsmäävät
        }
    }
    return false;  // Palautetaan false, jos huonetta ei löytynyt varauksista
}

// Funktio joka laskee varauksen kokonaishinnan
double laskeHinta(HuoneTyyppi tyyppi, int oidenMaara)
{
    double hintaPerYo = (tyyppi == YHDEN_HENGEN) ? HINTA_YHDEN_HENGEN : HINTA_KAHDEN_HENGEN;  // Valitaan hinnasto tyypin mukaan
    return hintaPerYo * oidenMaara; // Lasketaan hinta kertomalla yöhinta öiden määrällä
}


// Funktio, joka tulostaa varauksen tiedot
void tulostaVaraus(Varaus varaus) 
{
    cout << "Nimi: " << varaus.nimi << endl;  // Tulostetaan varaajan nimi
    cout << "Huone: " << varaus.huoneNumero << endl; // Tulostetaan huoneen numero
    cout << "Öitä: " << varaus.oidenMaara << endl;  // Tulostetaan öiden määrä
    cout << "Tyyppi: " << (varaus.tyyppi == YHDEN_HENGEN ? "Yhden hengen" : "Kahden hengen") << endl;  // Tulostetaan huonetyyppi
    cout << "Hinta: " << varaus.hinta << " €" << endl;  // Tulostetaan kokonaishinta
}

int main()  // Tästä alkaa pääohjelma
{
    setlocale(LC_ALL, "fi-FI");  // Otetaan ääkköset käyttöön pääohjelmaan
    srand(time(0)); // Alustetaan satunnaislukugeneraattori ajan perusteella

    Varaus varaukset[HUONEITA]; // Luodaan taulukko, johon varaukset tallennetaan
    int varaustenMaara = 0; // Alustetaan varauksien lukumäärä nollaksi

    int valinta;  // Muuttuja käyttäjän valintaa varten
    do 
    {
        // Tulostetaan päävalikko
        cout << "\nPäävalikko:" << endl;  
        cout << "1. Varaa huone" << endl;  // Valinta 1: Uuden varauksen tekeminen
        cout << "2. Näytä varaukset" << endl;  // Valinta 2: Kaikkien varaustn tarkastelu
        cout << "0. Lopeta" << endl;  // Valinta 0; ohjelman lopettaminen
        cout << "Valitse: ";  // Pyydetään käyttäjää valitsemaan toiminto
        cin >> valinta;  // Tallennetaan käyttäjän syöte muuttujaan-valinta

        switch (valinta) {
        case 1: 
        {
            // Jos valittiin toiminto 1 
            if (varaustenMaara < HUONEITA) // tarkistetaan, onko huoneita vapaana
            {
                string nimi;  // Muuttuha varaajan nimelle
                int huoneNumero;  // Muuttuja huoneen numerolle
                int oidenMaara;  // Muuttuja öiden määrälle
                HuoneTyyppi tyyppi;  // Muuttuja huonetyypille

                cout << "Anna nimi: ";  // Pyydetään varaajan nimi
                cin.ignore(); // Tyhjennetään syötepuskuri edellisen rivin jäljiltä
                getline(cin, nimi);  // Luetaan varaajan nimi

                // Kysytään käyttäjältä huonetyyppi
                cout << "Valitse huonetyyppi (1 = yhden hengen, 2 = kahden hengen): ";
                int tyyppiValinta;  // Muuttuja käyttäjän huonetyyppivalintaa varten
                cin >> tyyppiValinta;  // Tallennetaan käyttäjän syöte muuttujaan-tyyppiValinta
                tyyppi = tyyppiValinta == 1 ? YHDEN_HENGEN : KAHDEN_HENGEN;  // Määritetään huonetyyyppi valinnan perusteella

                // Arvotaan vapaa huonenumero
                do 
                {
                    huoneNumero = rand() % HUONEITA + 1;  // Arvotaan numero väliltä 1-huoneita
                } while (onkoHuoneVarattu(varaukset, huoneNumero, tyyppi, varaustenMaara));  // Toistetaan, kunnes löytynyt huone ei ole varattu

                cout << "Anna öiden määrä: ";  // Pyydetään käyttäjältä öiden määrä
                cin >> oidenMaara;  // Tallennetaan käyttähän syöte muuttujaan-oidenMaara

                // Tallennetaan usi varaus taulukkoon
                varaukset[varaustenMaara].nimi = nimi;  // Tallennetaan nimi
                varaukset[varaustenMaara].huoneNumero = huoneNumero;  // Tallennetaan huoneen numero
                varaukset[varaustenMaara].oidenMaara = oidenMaara;  // Tallennetaan öiden määrä
                varaukset[varaustenMaara].tyyppi = tyyppi; // Tallennetaan huonetyyppi
                varaukset[varaustenMaara].hinta = laskeHinta(tyyppi, oidenMaara); // Tallennetaan laskettu hinta
                varaustenMaara++; // Kasvatetaan varausten lukumäärää

                cout << "Huone varattu!" << endl;  // Ilmoitetaan varauksen onnistuminen
            }
            else {
                cout << "Kaikki huoneet ovat varattuja." << endl; // Ilmoitetaan käyttäjälle ettei varaus ole mahdollinen
            }
            break;  // Lopetetaan case 1
        }
        case 2:
            // Jos valinta on 2
            for (int i = 0; i < varaustenMaara; i++) {  // Käydään läpi kaikki varaukset
                tulostaVaraus(varaukset[i]);  // Tulostetaan yksittäisen varauksen tiedot
                cout << endl;  // Tulostetaan tyhjä rivi
            }
            break;  // Lopetetaan case 2

        case 0:  // Jos valinta on 0
            cout << "Kiitos ja näkemiin!" << endl;  // Tulostetaan hyvästelyviesti
            break;  // Lopetetaan case 0
        default:  // Jos valinta ei vastaa mitään yllä olevista
            cout << "Virheellinen valinta." << endl;  // Ilmoitetaan virheellisestä syötteestä
        }
    } while (valinta != 0);  // Toistetaan kunnes käyttäjä valistee lopetuksen (case 0)

    return 0; // Ohjelma on onnistunut (palautetaan 0)
}
