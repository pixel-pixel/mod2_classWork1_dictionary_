#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Word {
    char eng[20];
    char ua[20];
} word;
const int LENGHT = 20;
char PATH_UA[100] = "/home/andrew/CLionProjects/mod2_classWork1(dictionary)/Dictionary/UAeng/";
char PATH_ENG[100] = "/home/andrew/CLionProjects/mod2_classWork1(dictionary)/Dictionary/ENGua/";


void writeToUa(char ua[LENGHT], char eng[LENGHT]) {
    strcpy(word.ua, ua);
    strcpy(word.eng, eng);

    char myPath[100];
    strcpy(myPath, PATH_UA);
    strcat(strcat(myPath, ua), ".data");

    ofstream stream(myPath, ios::binary | ios::app);
    stream.write((char *) &word, sizeof(Word));
    stream.close();
}

void writeToEng(char eng[LENGHT], char ua[LENGHT]) {
    strcpy(word.ua, ua);
    strcpy(word.eng, eng);

    char myPath[100];
    strcpy(myPath, PATH_ENG);
    strcat(strcat(myPath, eng), ".data");

    ofstream stream(myPath, ios::binary | ios::app);
    stream.write((char *) &word, sizeof(Word));
    stream.close();
}

void terminalWrite() {
    const char *msg1 = "ENTER THE WORD:";
    const char *msg2 = "ENTER THE TRANSLATION:";
    char first[LENGHT];
    char second[LENGHT];

    cout << msg1 << endl;
    cin.get();
    cin.getline(first, LENGHT);
    cout << msg2 << endl;
    cin.getline(second, LENGHT);

    if ((int) first[0] < 0) {
        writeToUa(first, second);
        writeToEng(second, first);
    } else {
        writeToEng(first, second);
        writeToUa(second, first);
    }
}

bool readFromUa(char ua[LENGHT]) {
    char myPath[100];
    strcpy(myPath, PATH_UA);
    strcat(strcat(myPath, ua), ".data");

    ifstream stream(myPath, ios::binary | ios::in);

    if (stream.good()) {
        while (true) {
            stream.read((char *) &word, sizeof(Word));
            if (stream.eof()) break;
            cout << word.eng << endl;
        }
    } else {
        return false;
    }
    return true;
}

bool readFromEng(char eng[LENGHT]) {
    char myPath[100];

    strcpy(myPath, PATH_ENG);
    strcat(strcat(myPath, eng), ".data");

    ifstream stream(myPath, ios::binary | ios::in);

    if (stream.good()) {
        while (true) {
            stream.read((char *) &word, sizeof(Word));
            if (stream.eof()) break;
            cout << word.ua << endl;
        }
    } else {
        return false;
    }
    return true;
}

void terminalRead() {
    const char *msg = "ENTER THE WORD WHOSE TRANSLATIONS YOU WANT TO WATCH:";
    char first[LENGHT];

    cout << msg << endl;
    cin.get();
    cin.getline(first, LENGHT);

    if ((int) first[0] > 0) {
        cout << (readFromEng(first) ? "" : "TRANSLATION NOT EXISTS") << endl;
    } else {
        cout << (readFromUa(first) ? "" : "TRANSLATION NOT EXISTS") << endl;
    }
}

bool removeUaTranslation(char ua[LENGHT]) {
    char myPath[100];
    strcpy(myPath, PATH_UA);
    strcat(strcat(myPath, ua), ".data");
    return remove(myPath);
}

bool removeEngTranslation(char eng[LENGHT]) {
    char myPath[100];
    strcpy(myPath, PATH_ENG);
    strcat(strcat(myPath, eng), ".data");
    return remove(myPath);
}

void terminalRemove() {
    const char *msg = "ENTER THE WORD WHOSE TRANSLATIONS YOU WANT TO REMOVE:";
    char first[LENGHT];

    cout << msg << endl;
    cin.get();
    cin.getline(first, LENGHT);

    if ((int) first[0] > 0) {
        if (!removeEngTranslation(first)) cout << "SUCCESS" << endl;
        else cout << "ERROR!" << endl;
    } else {
        if (!removeUaTranslation(first)) cout << "SUCCESS" << endl;
        else cout << "ERROR!" << endl;
    }
}

bool editUaTranslation(char ua[LENGHT], char translation[LENGHT]) {
    char myPath1[100];
    char myPath2[100];

    strcpy(myPath1, PATH_UA);
    strcat(strcat(myPath1, ua), ".data");
    strcpy(myPath2, PATH_UA);
    strcat(strcat(myPath2, "1"), ".data");

    ifstream stream1(myPath1, ios::binary | ios::in);
    ofstream stream2(myPath2, ios::binary | ios::app);

    if (stream1.good()) {
        while (true) {
            stream1.read((char *) &word, sizeof(Word));
            if (stream1.eof()) break;
            if(strcmp(translation, word.eng) != 0) stream2.write((char *) &word, sizeof(Word));
        }
    } else {
        return false;
    }
    stream1.close();
    stream2.close();
    return !(remove(myPath1) != 0 || rename(myPath2, myPath1) != 0);
}

bool editEngTranslation(char eng[LENGHT], char translation[LENGHT]){
    char myPath1[100];
    char myPath2[100];

    strcpy(myPath1, PATH_ENG);
    strcat(strcat(myPath1, eng), ".data");
    strcpy(myPath2, PATH_ENG);
    strcat(strcat(myPath2, "1"), ".data");

    ifstream stream1(myPath1, ios::binary | ios::in);
    ofstream stream2(myPath2, ios::binary | ios::app);

    if (stream1.good()) {
        while (true) {
            stream1.read((char *) &word, sizeof(Word));
            if (stream1.eof()) break;
            if(strcmp(translation, word.ua) != 0) stream2.write((char *) &word, sizeof(Word));
        }
    } else {
        return false;
    }
    stream1.close();
    stream2.close();
    return !(remove(myPath1) != 0 || rename(myPath2, myPath1) != 0);
}

void terminalEdit() {
    const char *msg1 = "ENTER WORD WHOSE TRANSLATION YOU WANT TO EDIT:";
    const char *msg2 = "CHOSE AND WRITE THE WORD YOU WANT TO REMOVE:";
    char first[LENGHT];
    char second[LENGHT];

    cout << msg1 << endl;
    cin.get();
    cin.getline(first, LENGHT);

    if ((int) first[0] > 0) {
        cout << (readFromEng(first) ? "" : "WORD NOT EXISTS") << endl;
    } else {
        cout << (readFromUa(first) ? "" : "WORD NOT EXISTS") << endl;
    }

    cout << msg2 << endl;
    cin.getline(second, LENGHT);

    editEngTranslation(first, second);

    if ((int) first[0] > 0) editEngTranslation(first, second);
    else editUaTranslation(first, second);
}

bool menu() {
    const char *msg = "0 - exit\n"
                      "1 - add translate\n"
                      "2 - get translate\n"
                      "3 - delete word\n"
                      "4 - delete translate";
    int c;

    cout << msg << endl;
    cin >> c;

    switch (c) {
        case 1:
            terminalWrite();
            break;
        case 2:
            terminalRead();
            break;
        case 3:
            terminalEdit();
            break;
        case 4:
            terminalRemove();
            break;
        default:
            return false;
    }
    return true;
}

int main() {
    while (menu()) {}
}
