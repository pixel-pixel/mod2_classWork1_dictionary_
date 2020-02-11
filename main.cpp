#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Word{
    char eng[20];
    char ua[20];
};
const int LENGHT = 20;
char PATH_UA[100] = "/home/andrew/CLionProjects/mod2_classWork1(dictionary)/Dictionary/UAeng/";
char PATH_ENG[100] = "/home/andrew/CLionProjects/mod2_classWork1(dictionary)/Dictionary/ENGua/";



void writeToUa(char ua[LENGHT], char eng[LENGHT]){
    Word word;
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
    Word word;
    strcpy(word.ua, ua);
    strcpy(word.eng, eng);

    char myPath[100];
    strcpy(myPath, PATH_ENG);
    strcat(strcat(myPath, eng), ".data");

    ofstream stream(myPath, ios::binary | ios::app);
    stream.write((char*)&word, sizeof(Word));
    stream.close();
}

void readFromUa(char ua[LENGHT]){
    Word word;
    char myPath[100];
    strcpy(myPath, PATH_UA);
    strcat(strcat(myPath, ua), ".data");

    ifstream stream(myPath, ios::binary | ios::in);

    while(true){
        stream.read((char*)&word, sizeof(Word));
        if(stream.eof()) break;
        cout << word.eng << endl;
    }
}

void readFromEng(char eng[LENGHT]){
    Word word;
    char myPath[100];
    strcpy(myPath, PATH_ENG);
    strcat(strcat(myPath, eng), ".data");

    ifstream stream(myPath, ios::binary | ios::in);

    while(true){
        stream.read((char*)&word, sizeof(Word));
        if(stream.eof()) break;
        cout << word.ua << endl;
    }
}

bool menu(){
    int c;
    char first[LENGHT];
    char second[LENGHT];
    cin >> c;

    if(c == 0){
        return 0;
    } else if(c == 1){
        cin.get();
        cin.getline(first, LENGHT);
        cin.getline(second, LENGHT);
        if((int)first[0] < 0) {
            writeToUa(first, second);
        }else {
            writeToEng(first, second);
        }

    } else if(c == 2){
        cin.getline(first, LENGHT);
        if(first[0] > 125) readFromUa(first);
        else readFromEng(first);
    }else{
        return 0;
    }

    return 1;
}

int main() {
    while (menu()) {}


}
