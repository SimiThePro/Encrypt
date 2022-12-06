#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <algorithm>


using namespace std;

const char* command = "dir .\\Dateien /b";
string path = "Dateien/";

#define SHOWDIR cout << "{\n"; system(command);  cout << '}'
#define CLEAR system("cls")

struct Encrypt {
public:
    int key = 0;
    string DateinameZuVer = "";
    string DateinameVer = "";

};
struct Decrypt
{
public:
    int key = 0;
    string DateinameZuEnt = "";
    string DateinameEnt = "";
};

void Menu();
void Verschluesseln(struct Encrypt& encrypt);
void Entschluesseln(struct Decrypt& decrypt);
void Bruteforce();

int main()
{
    struct Encrypt encrypt2;
    struct Decrypt decrypt;
    string Eingabe, FileInput;
    int iEingabe = 0;


    while (iEingabe != 4)
    {
        CLEAR;
        Menu();
        cout << "\n>>";
        getline(cin, Eingabe);
        stringstream(Eingabe) >> iEingabe;
        switch (iEingabe) {
        case 1:
            Verschluesseln(encrypt2);
            break;
        case 2:
            Entschluesseln(decrypt);
            break;
        case 3: {
            Bruteforce();
        }
        case 4:
            break;

        }
    }
}



void Menu() {
    cout <<
        "1.	Verschluesseln"
        "\na) Wahl des Schluessels"
        "\nb) Wahl der zu verschluesselnden Datei"
        "\nc) Wahl der verschluesselten Datei"
        "\n2.	Entschluesseln"
        "\na) Eingabe des Schluessels"
        "\nb) Wahl der verschluesselten Datei"
        "\nc) Wahl der entschluesselten Datei"
        "\n3.	Ende";
}

void Verschluesseln(struct Encrypt& encrypt) {
    //Deklaration

    ifstream DateiZuVer;
    ofstream DateiVer;

    string strschluessel;
    string sWahl; int Wahl = 0;
    string line, FileText, LowerText = "", Eingabe;

    while (Wahl != 5) {
        Wahl = 0;
        CLEAR;
        cout <<
            "\n 1) Wahl des Schluessels \t\t\t(Momentan: " << encrypt.key << ")" <<
            "\n 2) Wahl der zu verschluesselnden Datei \t" << (encrypt.DateinameZuVer == "" ? "KEINE AUSGEWAEHLT" : encrypt.DateinameZuVer + ".txt") <<
            "\n 3) Wahl der verschluesselten Datei \t\t" << (encrypt.DateinameVer == "" ? "KEINE AUSGEWAEHLT" : encrypt.DateinameVer + ".txt") <<
            "\n 4) AUSFUEHREN" <<
            "\n 5 Ende";


        while (Wahl < 1 || Wahl > 5)
        {
            cout << "\n>>";
            getline(cin, sWahl);
            stringstream(sWahl) >> Wahl;
            if (Wahl < 1 || Wahl > 5) cout << "Please enter a valid Number";
        }

        switch (Wahl)
        {
        case 1: {
            int tempkey = 0;
            cout << "Geben Sie den Schluessel ein: ";
            while (tempkey == 0) {
                getline(cin, strschluessel);
                stringstream(strschluessel) >> tempkey;
                if (tempkey == 0) {
                    cout << "Geben Sie einen gueltigen Schluessel ein" << endl;
                }
            }
            encrypt.key = tempkey;

            break;

        }
        case 2: {
            cout << "Welche der Folgenden Dateien moechten sie verschluesseln\n";
            SHOWDIR;
            for (DateiZuVer; !DateiZuVer.is_open();)
            {
                getline(cin, encrypt.DateinameZuVer);
                DateiZuVer.open(path + encrypt.DateinameZuVer + ".txt");
                if (!DateiZuVer.is_open())
                    cout << "unable to open file" << endl;
            }
            while (getline(DateiZuVer, line)) {
                FileText += line + "\n";
            }
            cout << "Möchten Sie die Datei auslesen?   (j=ja|n=nein)  " << endl;
            getline(cin, Eingabe);
            if (Eingabe == "j") {
                cout << FileText;
                system("pause");
            }
            DateiZuVer.close();
            break;
        }
        case 3: {
            cout << "In Welcher Datei möchten Sie die verschlüsselung speichern\n";
            SHOWDIR;
            for (DateiVer; !DateiVer.is_open();)
            {
                getline(cin, encrypt.DateinameVer);
                DateiVer.open(path + encrypt.DateinameVer + ".txt");
                if (!DateiVer.is_open())
                    cout << "unable to open file" << endl;
            }
            DateiVer.close();
            break;
        }
        case 4: {
            DateiZuVer.open(path + encrypt.DateinameZuVer + ".txt");
            cout << "Um Fortzufahren drücken Sie ENTER";
            getline(cin, Eingabe);
            if (Eingabe == "") {
                while (getline(DateiZuVer, line)) {
                    LowerText += line + "\n";
                }
                DateiZuVer.close();
                cout << endl << LowerText;


                string encryptedtext(LowerText.length(), ' ');

                for (int i = 0, endlines = 0; i < LowerText.length() - endlines; i++) {
                    if ((LowerText[i] >= 'A' && LowerText[i] <= 'Z') || (LowerText[i] >= 'a' && LowerText[i] <= 'z'))
                    {
                        if (LowerText[i] >= 'A' && LowerText[i] <= 'Z')
                        {
                            if (LowerText[i] <= ('Z') - encrypt.key)
                                encryptedtext[i] = (LowerText[i] + encrypt.key);
                            else encryptedtext[i] = ((LowerText[i] % ('Z' - encrypt.key)) + 'A' - 1);
                        }
                        else
                        {
                            if (LowerText[i] <= ('z') - encrypt.key)
                                encryptedtext[i] = (LowerText[i] + encrypt.key);
                            else encryptedtext[i] = ((LowerText[i] % ('z' - encrypt.key)) + 'a' - 1);
                        }

                    }
                    else if (LowerText[i] == '\n' || LowerText[i] == ' ')
                    {
                        endlines++;
                        encryptedtext[i] = LowerText[i];
                    }
                    else encryptedtext[i] = LowerText[i] + encrypt.key;

                }
                DateiVer.open(path + encrypt.DateinameVer + ".txt");

                DateiVer << encryptedtext;

                DateiVer.close();

                cout << "\nDie Datei wurde von der Datei \"" + encrypt.DateinameZuVer + "\".txt mit den " <<
                    "Schluessel " << encrypt.key << " in die Datei \"" << encrypt.DateinameVer << ".txt verschluesselt." << endl;
                system("pause");

            }

        }
        case 5: {

            break;
        }
        }
    }
}

void Entschluesseln(struct Decrypt& decrypt) {

    ifstream DateiZuEnt;
    ofstream DateiEnt;
    string strschluessel;
    string sWahl; int Wahl = 0;
    string line, FileText, LowerText = "", Eingabe;

    while (Wahl != 5) {
        Wahl = 0;

        CLEAR;
        cout <<
            "\n 1) Wahl des Schluessels \t\t\t(Momentan: " << decrypt.key << ")" <<
            "\n 2) Wahl der verschluesselten Datei \t" << (decrypt.DateinameZuEnt == "" ? "KEINE AUSGEWAEHLT" : decrypt.DateinameZuEnt + ".txt") <<
            "\n 3) Wahl der entschluesselten Datei \t" << (decrypt.DateinameEnt == "" ? "KEINE AUSGEWAEHLT" : decrypt.DateinameEnt + ".txt") <<
            "\n 4) AUSFUEHREN"
            "\n 5) ENDE";


        while (Wahl < 1 || Wahl > 5)
        {
            cout << "\n>>";
            getline(cin, sWahl);
            stringstream(sWahl) >> Wahl;
            if (Wahl < 1 || Wahl > 4) cout << "Please enter a valid Number";
        }

        switch (Wahl)
        {
        case 1: {
            int tempkey = 0;
            cout << "Geben Sie den Schluessel ein: ";
            while (tempkey == 0) {
                getline(cin, strschluessel);
                stringstream(strschluessel) >> tempkey;
                if (tempkey == 0) {
                    cout << "Geben Sie einen gueltigen Schluessel ein" << endl;
                }
            }
            decrypt.key = tempkey;
            break;
        }
        case 2: {
            cout << "Welche der Folgenden Dateien moechten sie entschluesseln\n";
            SHOWDIR;
            for (DateiZuEnt; !DateiZuEnt.is_open();)
            {
                getline(cin, decrypt.DateinameZuEnt);
                DateiZuEnt.open(path + decrypt.DateinameZuEnt + ".txt");
                if (!DateiZuEnt.is_open())
                    cout << "unable to open file" << endl;
            }
            while (getline(DateiZuEnt, line)) {
                FileText += line + "\n";
            }
            cout << "Möchten Sie die Datei auslesen?   (j=ja|n=nein)  " << endl;
            getline(cin, Eingabe);
            if (Eingabe == "j") {
                cout << FileText;
                system("pause");
            }
            DateiZuEnt.close();
            break;
        }
        case 3: {
            cout << "In Welcher Datei möchten Sie die entschlüsselung speichern\n";
            SHOWDIR;
            for (DateiEnt; !DateiEnt.is_open();)
            {
                getline(cin, decrypt.DateinameEnt);
                DateiEnt.open(path + decrypt.DateinameEnt + ".txt");
                if (!DateiEnt.is_open())
                    cout << "unable to open file" << endl;
            }
            DateiEnt.close();
            break;
        }
        case 4: {
            DateiZuEnt.open(path + decrypt.DateinameZuEnt + ".txt");
            cout << "Um Fortzufahren drücken Sie ENTER";
            getline(cin, Eingabe);
            if (Eingabe == "") {
                Wahl = 4;
                string encryptedtext = "", line;
                while (getline(DateiZuEnt, line))
                    encryptedtext += line + '\n';

                string decryptedtext(encryptedtext.length(), ' ');

                for (int i = 0, endlines = 0; i < encryptedtext.length() - endlines; i++) {

                    if ((encryptedtext[i] >= 'a' && encryptedtext[i] <= 'z') || (encryptedtext[i] >= 'A' && encryptedtext[i] <= 'Z')) {

                        if (encryptedtext[i] >= 'a' && encryptedtext[i] <= 'z')
                        {
                            if (encryptedtext[i] >= ('a') + decrypt.key)
                                decryptedtext[i] = (encryptedtext[i] - decrypt.key);
                            else decryptedtext[i] = 'z' - (decrypt.key - (encryptedtext[i] % ('a')) - 1);
                        }
                        else {
                            if (encryptedtext[i] >= ('A') + decrypt.key)
                                decryptedtext[i] = (encryptedtext[i] - decrypt.key);
                            else decryptedtext[i] = 'Z' - (decrypt.key - (encryptedtext[i] % ('A')) - 1);
                        }

                    }
                    else
                        decryptedtext[i] = encryptedtext[i] - decrypt.key;

                    if (encryptedtext[i] == '\n' || encryptedtext[i] == ' ')
                    {
                        endlines++;
                        decryptedtext[i] = encryptedtext[i];
                    }

                }
                DateiEnt.open(path + decrypt.DateinameEnt + ".txt");

                DateiEnt << decryptedtext;

                DateiEnt.close();

            }
            else {
                break;
            }
        }
        case 5: {

            break;
        }
        }

    }
}


void Bruteforce() {
    ifstream DateiLesen;
    ifstream DateiVerschlossen; string TextVerschluesselt;
    ofstream DateiSpeicher;

    string Eingabe;
    string TextDatei = "", TextDateiLower, line;
    vector<string> Texts;
    vector<int> AnzahlE;
    vector<int> posAlphabet;
    vector<char> charAlphabet;

    cout << "Welche der Folgenden Dateien moechten Sie entschluesseln?\n";
    SHOWDIR;

    while (!DateiVerschlossen.is_open()) {
        getline(cin, Eingabe);
        DateiVerschlossen.open(path + Eingabe + ".txt");
        if (!DateiVerschlossen.is_open())
            cout << "Diese Datei ist nicht vorhanden!\n";
    }
    while (getline(DateiVerschlossen, line)) {
        TextVerschluesselt += line + '\n';
    }

    for (int key = 1; key < 11; key++)
    {
        string TextEntschluesselt(TextVerschluesselt.length(),' ');
        for (int i = 0, endlines = 0; i < TextVerschluesselt.length() - endlines; i++) {

            if ((TextVerschluesselt[i] >= 'a' && TextVerschluesselt[i] <= 'z') || (TextVerschluesselt[i] >= 'A' && TextVerschluesselt[i] <= 'Z')) {

                if (TextVerschluesselt[i] >= 'a' && TextVerschluesselt[i] <= 'z')
                {
                    if (TextVerschluesselt[i] >= ('a') + key)
                        TextEntschluesselt[i] = (TextVerschluesselt[i] - key);
                    else TextEntschluesselt[i] = 'z' - (key - (TextVerschluesselt[i] % ('a')) - 1);
                }
                else {
                    if (TextVerschluesselt[i] >= ('A') + key)
                        TextEntschluesselt[i] = (TextVerschluesselt[i] - key);
                    else TextEntschluesselt[i] = 'Z' - (key - (TextVerschluesselt[i] % ('A')) - 1);
                }

            }
            else
                TextEntschluesselt[i] = TextVerschluesselt[i] - key;

            if (TextVerschluesselt[i] == '\n' || TextVerschluesselt[i] == ' ')
            {
                endlines++;
                TextEntschluesselt[i] = TextVerschluesselt[i];
            }

        }
        Texts.push_back(TextEntschluesselt);

        
        for (int i = 0; i < TextEntschluesselt.length(); i++) {
            if (TextEntschluesselt[i] <= 'Z' || TextEntschluesselt[i] >= 'A')
                TextEntschluesselt[i] = tolower(TextEntschluesselt[i]);
            if (find(charAlphabet.begin(), charAlphabet.end(), TextEntschluesselt[i]) != charAlphabet.end()) {

                auto pos = distance(charAlphabet.begin(), find(charAlphabet.begin(), charAlphabet.end(), TextEntschluesselt[i]));
                posAlphabet.at(pos)++;

            }
            else {
                charAlphabet.push_back(TextEntschluesselt[i]);
                posAlphabet.push_back(1);
            }
        }

        AnzahlE.push_back(posAlphabet.at(distance(charAlphabet.begin(), find(charAlphabet.begin(), charAlphabet.end(), 'e'))));
        
        TextDateiLower += line + '\n';
        charAlphabet.clear();
        posAlphabet.clear();

    }

    
    cout <<endl << TextDateiLower << endl << TextDatei ;
    system("pause");




}
