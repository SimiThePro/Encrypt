#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <conio.h>


using namespace std;

const char* command = "dir .\\Dateien /b";
string path = "Dateien/";

#define SHOWDIR system(command)
#define CLEAR system("cls")

void Menu();
void Verschluesseln();
void Entschluesseln();


struct Encrypt {
public:
    int key = 0;
    string DateinameZuVer = "";
    string DateinameVer = "";
    ifstream DateiZuVer;
    ofstream DateiVer;
};
struct Decrypt
{
public:
    int key = 0;
    string DateinameZuEnt = "";
    string DateinameEnt = "";
    ifstream DateiZuEnt;
    ofstream DateiEnt;
};


int main()
{
    Menu();
    string Eingabe, FileInput;
    int iEingabe;
    cout << "\n>>";
    getline(cin, Eingabe);
    stringstream(Eingabe) >> iEingabe;
    
    while (iEingabe != 3)
    switch (iEingabe) {
    case 1:
        Verschluesseln();
        break;
    case 2:
        Entschluesseln();
        break;
    }
    

    ofstream MyFile(path + "Informationen.txt");
    MyFile << Eingabe;
    MyFile.close();

    /*ifstream MyReadFile(path +"Informationen.txt");
    if (MyReadFile.is_open()) {
        while (getline(MyReadFile, FileInput)) {

        }
    }*/
    Eingabe = FileInput;
    string lowerEingabe = FileInput;

    for (int i = 0, deleted = 0; i < Eingabe.length(); i++) {
        if (isupper(Eingabe[i]) && isalpha(Eingabe[i])) {
            lowerEingabe[i] = Eingabe[i] + 32;
        }
        else if (islower(Eingabe[i]))lowerEingabe[i] = Eingabe[i];
    }

    int schluessel;
    cin >> schluessel;
    //Encrypt//
    for (int i = 0; i < lowerEingabe.length(); i++) {
        if (lowerEingabe[i] < 'z' - schluessel)
            lowerEingabe[i] += schluessel;
        else lowerEingabe[i] = (lowerEingabe[i] % ('z' - schluessel)) + 'a' - 1;
    }
    cout << lowerEingabe << endl;

    //Decrypt//
    for (int i = 0; i < lowerEingabe.length(); i++) {
        if (lowerEingabe[i] > 'a' + schluessel - 1)
        {
            lowerEingabe[i] -= schluessel;
        }
        else lowerEingabe[i] = 'z' - (schluessel - (lowerEingabe[i] % ('a')) - 1);
    }

    cout << lowerEingabe << endl;



    //Show Directory//
    system(command);
    

}



void Menu() {
    cout <<
        "1.	Verschluesseln"
        "\na) Wahl des Schluessels"
        "\nb) Wahl der zu verschluesselnden Datei"
        "\nc) Wahl der verschluesselten Datei"
        "\n2.	Entschlüsseln"
        "\na) Eingabe des Schluessels"
        "\nb) Wahl der verschluesselten Datei"
        "\nc) Wahl der entschluesselten Datei"
        "\n3.	Ende";
}

void Verschluesseln() {
    //Deklaration
    Encrypt encrypt;
    string strschluessel;
    string sWahl; int Wahl = 0;
    string line, FileText, LowerText = "", Eingabe;

    while (Wahl != 4) {
        Wahl = 0;
        int tempkey = 0;
        CLEAR;
        cout <<
            "\n 1) Wahl des Schluessels \t\t\t(Momentan: " << encrypt.key << ")" <<
            "\n 2) Wahl der zu verschluesselnden Datei \t" << (encrypt.DateinameZuVer == "" ? "KEINE AUSGEWAEHLT" : encrypt.DateinameZuVer + ".txt") <<
            "\n 3) Wahl der verschluesselten Datei \t\t" << (encrypt.DateinameVer == "" ? "KEINE AUSGEWAEHLT" : encrypt.DateinameVer + ".txt")  <<
            "\n 4) AUSFUEHREN";

                
        while (Wahl < 1 || Wahl > 4)
        {
            cout << "\n>>";
            getline(cin, sWahl);
            stringstream(sWahl) >> Wahl;
            if (Wahl < 1 || Wahl > 4) cout << "Please enter a valid Number";
        }

        switch (Wahl)
        {
        case 1: {
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
            for (encrypt.DateiZuVer; !encrypt.DateiZuVer.is_open();)
            {
                getline(cin, encrypt.DateinameZuVer);
                encrypt.DateiZuVer.open(path + encrypt.DateinameZuVer+ ".txt");
                if (!encrypt.DateiZuVer.is_open())
                    cout << "unable to open file" << endl;
            }
            while (getline(encrypt.DateiZuVer, line)) {
                FileText += line + "\n";
            }
            cout << "Möchten Sie die Datei auslesen?   (j=ja|n=nein)  " << endl;
            getline(cin, Eingabe);
            if (Eingabe == "j") {
                cout << FileText;
                system("pause");
            }
            encrypt.DateiZuVer.close();
            break;
        }
        case 3: {
            cout << "In Welcher Datei möchten Sie die verschlüsselung speichern\n";
            SHOWDIR;
            for (encrypt.DateiVer; !encrypt.DateiVer.is_open();)
            {
                getline(cin, encrypt.DateinameVer);
                encrypt.DateiVer.open(path + encrypt.DateinameVer + ".txt");
                if (!encrypt.DateiVer.is_open())
                    cout << "unable to open file" << endl;
            }
            encrypt.DateiVer.close();
            break;
        }
        case 4: {
            encrypt.DateiZuVer.open(path + encrypt.DateinameZuVer + ".txt");
            cout << "Um Fortzufahren drücken Sie ENTER";
            getline(cin, Eingabe);
            if (Eingabe == "") {
                while (getline(encrypt.DateiZuVer,line)){
                    /*for (int i = 0; i < line.length(); i++) {
                        if (line [i] >= 'A' && line[i] <='Z') {
                            line[i] = line[i] + 32;
                        }
                        else if (islower(line[i]))line[i] = line[i];
                    }*/
                    LowerText += line + "\n";
                }
                encrypt.DateiZuVer.close();
                cout << endl << LowerText;


                string encryptedtext(LowerText.length(), ' ');

                for (int i = 0, endlines = 0; i < LowerText.length()-endlines; i++) {
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
                        
                    }else if (LowerText[i] == '\n')
                    {
                        endlines++;
                        encryptedtext[i] = LowerText[i];
                    }
                    else encryptedtext[i] = LowerText[i] + encrypt.key;
                    
                }
                encrypt.DateiVer.open(path + encrypt.DateinameVer + ".txt");

                encrypt.DateiVer << encryptedtext;

                encrypt.DateiVer.close();

            }
            
        }
        }
    }
}

void Entschluesseln() {
    Decrypt decrypt;
    string strschluessel;
    string sWahl; int Wahl = 0;
    string line, FileText, LowerText = "", Eingabe;

    while (Wahl != 4) {
        Wahl = 0;
        int tempkey = 0;
        CLEAR;
        cout <<
            "\n 1) Wahl des Schluessels \t\t\t(Momentan: " << decrypt.key << ")" <<
            "\n 2) Wahl der verschlüsselten Datei \t" << (decrypt.DateinameZuEnt == "" ? "KEINE AUSGEWAEHLT" : decrypt.DateinameZuEnt + ".txt") <<
            "\n 3) Wahl der entschlüsselten Datei \t" << (decrypt.DateinameEnt == "" ? "KEINE AUSGEWAEHLT" : decrypt.DateinameEnt + ".txt") <<
            "\n 4) AUSFUEHREN";


        while (Wahl < 1 || Wahl > 4)
        {
            cout << "\n>>";
            getline(cin, sWahl);
            stringstream(sWahl) >> Wahl;
            if (Wahl < 1 || Wahl > 4) cout << "Please enter a valid Number";
        }

        switch (Wahl)
        {
        case 1: {
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
            for (decrypt.DateiZuEnt; !decrypt.DateiZuEnt.is_open();)
            {
                getline(cin, decrypt.DateinameZuEnt);
                decrypt.DateiZuEnt.open(path + decrypt.DateinameZuEnt + ".txt");
                if (!decrypt.DateiZuEnt.is_open())
                    cout << "unable to open file" << endl;
            }
            while (getline(decrypt.DateiZuEnt, line)) {
                FileText += line + "\n";
            }
            cout << "Möchten Sie die Datei auslesen?   (j=ja|n=nein)  " << endl;
            getline(cin, Eingabe);
            if (Eingabe == "j") {
                cout << FileText;
                system("pause");
            }
            decrypt.DateiZuEnt.close();
            break;
        }
        case 3: {
            cout << "In Welcher Datei möchten Sie die entschlüsselung speichern\n";
            SHOWDIR;
            for (decrypt.DateiEnt; !decrypt.DateiEnt.is_open();)
            {
                getline(cin, decrypt.DateinameEnt);
                decrypt.DateiEnt.open(path + decrypt.DateinameEnt + ".txt");
                if (!decrypt.DateiEnt.is_open())
                    cout << "unable to open file" << endl;
            }
            decrypt.DateiEnt.close();
            break;
        }
        case 4: {
            decrypt.DateiZuEnt.open(path + decrypt.DateinameZuEnt + ".txt");
            cout << "Um Fortzufahren drücken Sie ENTER";
            getline(cin, Eingabe);
            if (Eingabe == "") {
                string encryptedtext = "", line;
                while (getline(decrypt.DateiZuEnt, line))
                    encryptedtext += line + '\n';

                string decryptedtext(encryptedtext.length(), ' ');

                for (int i = 0, endlines = 0; i < encryptedtext.length() - endlines; i++) {
                    
                    if ((encryptedtext[i] >= 'a' && encryptedtext[i] <= 'z')||(encryptedtext[i] >= 'A' && encryptedtext[i] <= 'Z')) {
                        
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

                    if (encryptedtext[i] == '\n')
                    {
                        endlines++;
                        decryptedtext[i] = encryptedtext[i];
                    }
                    
                }
                
                /*for (int i = 0; i < lowerEingabe.length(); i++) {
                    if (lowerEingabe[i] > 'a' + schluessel - 1)
                    {
                        lowerEingabe[i] -= schluessel;
                    }
                    else lowerEingabe[i] = 'z' - (schluessel - (lowerEingabe[i] % ('a')) - 1);
                }*/

                decrypt.DateiEnt.open(path + decrypt.DateinameEnt + ".txt");

                decrypt.DateiEnt << decryptedtext;

                decrypt.DateiEnt.close();

            }
            else {
                Wahl = 0;
                break;
            }
            break;
        }
        }
    }
}
