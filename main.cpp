#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Word{
    char eng[20];
    char ua[20];
}word;
const int LENGHT = 20;
char PATH_UA[100] = "/home/andrew/CLionProjects/mod2_classWork1(dictionary)/Dictionary/UAeng/";
char PATH_ENG[100] = "/home/andrew/CLionProjects/mod2_classWork1(dictionary)/Dictionary/ENGua/";



void writeToUa(char ua[LENGHT], char eng[LENGHT]){
    strcpy(word.ua, ua);
    strcpy(word.eng, eng);

    char myPath[100];
    strcpy(myPath, PATH_UA);
    strcat(strcat(myPath, ua), ".data");

    ofstream stream(myPath, ios::binary | ios::app);
    stream.write((char*)&word, sizeof(Word));
    stream.close();
}
void writeToEng(char eng[LENGHT], char ua[LENGHT]){
    strcpy(word.ua, ua);
    strcpy(word.eng, eng);

    char myPath[100];
    strcpy(myPath, PATH_ENG);
    strcat(strcat(myPath, eng), ".data");

    ofstream stream(myPath, ios::binary | ios::app);
    stream.write((char*)&word, sizeof(Word));
    stream.close();
}
void terminalWrite(){
    const char* msg1 = "ENTER THE WORD:";
    const char* msg2 = "ENTER THE TRANSLATION:";
    char first[LENGHT];
    char second[LENGHT];

    cout << msg1 << endl;
    cin.get();
    cin.getline(first, LENGHT);
    cout << msg2 << endl;
    cin.getline(second, LENGHT);

    if((int)first[0] < 0) {
        writeToUa(first, second);
        writeToEng(second, first);
    }else {
        writeToEng(first, second);
        writeToUa(second, first);
    }
}

bool readFromUa(char ua[LENGHT]){
    char myPath[100];
    strcpy(myPath, PATH_UA);
    strcat(strcat(myPath, ua), ".data");

    ifstream stream(myPath, ios::binary | ios::in);

    if(stream.good()){
        while(true){
            stream.read((char*)&word, sizeof(Word));
            if(stream.eof()) break;
            cout << word.eng << endl;
        }
    }else{
        return false;
    }
    return true;
}
bool readFromEng(char eng[LENGHT]){
    char myPath[100];

    strcpy(myPath, PATH_ENG);
    strcat(strcat(myPath, eng), ".data");

    ifstream stream(myPath, ios::binary | ios::in);

    if(stream.good()){
        while(true){
            stream.read((char*)&word, sizeof(Word));
            if(stream.eof()) break;
            cout << word.ua << endl;
        }
    }else{
        return false;
    }
    return true;
}
void terminalRead(){
    const char* msg = "ENTER THE WORD WHOSE TRANSLATIONS YOU WANT TO WATCH:";
    char first[LENGHT];

    cout << msg << endl;
    cin.get();
    cin.getline(first, LENGHT);

    if ((int) first[0] > 0) {
        cout << (readFromEng(first) ? "" : "Перекладу не знайдено") << endl;
    } else {
        cout << (readFromUa(first) ? "" : "Перекладу не знайдено") << endl;
    }
}

bool removeUaTranslate(char ua[LENGHT]){
    char myPath[100];
    strcpy(myPath, PATH_UA);
    strcat(strcat(myPath, ua), ".data");
    return remove(myPath);
}
bool removeEngTranslate(char eng[LENGHT]){
    char myPath[100];
    strcpy(myPath, PATH_ENG);
    strcat(strcat(myPath, eng), ".data");
    return remove(myPath);
}
void terminalRemove(){
    const char* msg = "ENTER THE WORD WHOSE TRANSLATIONS YOU WANT TO REMOVE:";
    char first[LENGHT];

    cout << msg << endl;
    cin.get();
    cin.getline(first, LENGHT);

    if((int)first[0] > 0) {
        if(!removeEngTranslate(first)) cout << "SUCCESS" << endl;
        else cout << "ERROR!" << endl;
    }else {
        if(!removeUaTranslate(first)) cout << "SUCCESS" << endl;
        else cout << "ERROR!" << endl;
    }
}

bool menu(){
    const char* msg = "0 - exit\n"
                      "1 - add translate\n"
                      "2 - get translate\n"
                      "3 - delete word\n"
                      "4 - delete translate";
    int c;

    cout << msg << endl;
    cin >> c;

    switch (c){
        case 1:
            terminalWrite();
            break;
        case 2:
            terminalRead();
            break;
        case 3:
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
