#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct WordCount{
    string word;
    int count;
    void OneMoreOwrd(){ count++; }
    WordCount(string s){ word = s; count = 1;}
};

struct {
    bool operator()(const WordCount& x, const WordCount& y)
    {
        if (x.count < y.count)
            return false;
        else if (x.count > y.count)
            return true;
        else{
            if (x.word < y.word)
                return true;
            else
                return false;
        }
    }
} CompareWordCount;

// Function prototypes
string InputText();
string Normalize(string);
vector<WordCount> DistinctWords(string);
bool findWord(string, vector<WordCount>&);
void DisplayResults(vector<WordCount>);
void OneMoreOwrd();


int main(int argc, char** argv) {
    cout << "Lab 9 - Text File Word Counter" << endl;
    cout << "-------------------------------" << endl;
    while (true){
        string buffer = InputText();
        if (buffer == ""){break;}
        cout <<"\nThis is the text string read from the file" << endl;
        cout <<  "------------------------------------------" << endl;
        cout << buffer << endl << endl;
        vector<WordCount> words = DistinctWords(buffer);
        cout << "There are " << words.size() << " unique words in the above text." << endl;
        cout << "---------------------------------------------" << endl << endl;
        DisplayResults(words);
    }
    return 0;
}

string InputText(){
    string file;
    ifstream inputFile;
    string str;
    string text;

    do{ cout << "\nFile name? ";
        getline(cin, file);
        inputFile.open(file.c_str());
        if(inputFile){
            while (!inputFile.eof()){
            getline(inputFile, str);
            text += str;
            }
            inputFile.close(); return text;
        }
        else{
            if(file!= ""){cout << "This file does not exist. Please, try again." << endl;}
            continue;
        }
    }while(!inputFile && file!="");
    return text;
}

string Normalize(string s){
    string toLowString;
    char ch;

    for (int i = 0; i < s.length(); i++){
        ch = s[i];
        ch = tolower(ch);
        if (isalpha(ch) || isblank(ch))
            toLowString += ch;
    }
    return toLowString;
}

vector<WordCount> DistinctWords(string s){
    vector<WordCount> words;
    string toLowString = Normalize(s);

    istringstream ss(toLowString);

    string str;
    while(ss >> str){
        if (findWord(str, words) == true){ continue; }
        else{
            WordCount temp(str);
            words.push_back(temp);}
    }
    return words;
}

bool findWord(string str, vector<WordCount>& words){
    for (auto& her : words){
        if (her.word.compare(str) == 0){
            her.OneMoreOwrd(); return true;}
    }
}

void DisplayResults(vector<WordCount> words){
    vector<WordCount> FirstColumn;
    vector<WordCount> SecondColumn;
    vector<WordCount> ThirdColumn;
    vector<WordCount> FourthColumn;

    sort(words.begin(), words.end(),CompareWordCount);
    if(words.size()< 15){
        cout << setw(12) << left << "Word"  << setw(15) << right << "Count" << endl;
        cout << setw(12) << left << "----"  << setw(15) << right << "----" << endl;
        for (auto &r : words){
        cout << setw(12) << left << r.word;
        cout << setw(15) << right << r.count << endl;
        }
    }
    else if (words.size()> 15 && words.size()<60){
    for (int i = 0; i < words.size(); i++){
        if(i<14){
            FirstColumn.push_back(words[i]);
        }
       if(i> 14 && i<28){
            SecondColumn.push_back(words[i]);
        }
        if(i> 28 && i<42){
            ThirdColumn.push_back(words[i]);
        }
        if(i> 42 && i<60){
            FourthColumn.push_back(words[i]);
        }
    }

    for (int i = 0; i < FirstColumn.size(); i++){
            if(i==0){
            cout << setw(12) << left << "Word"  << setw(15) << right << " Count ";
            cout << setw(13) << left << "Word"  << setw(16) << right << "Count ";
            cout << setw(12) << left << "Word"  << setw(16) << right << "Count ";
            cout << setw(12) << left << "Word"  << setw(15) << right << "Count" << endl;
            cout << setw(13) << left << "----"  << setw(15) << right << " ---- " ;
            cout << setw(12) << left << "----"  << setw(16) << right << "---- " ;
            cout << setw(12) << left << "----"  << setw(16) << right << "---- " ;
            cout << setw(12) << left << "----"  << setw(15) << right << "----" << endl;}
            cout<< endl;

            cout << setw(12) << left << FirstColumn[i].word;
            cout << setw(15) << right << FirstColumn[i].count << " ";
        if(i<SecondColumn.size()){cout << setw(12) << left << SecondColumn[i].word;
        cout << setw(15) << right << SecondColumn[i].count << " ";}
        if(i<ThirdColumn.size()){ cout << setw(12) << left << ThirdColumn[i].word;
        cout << setw(15) << right << ThirdColumn[i].count << " ";}
        if(i<FourthColumn.size()){cout << setw(12) << left << FourthColumn[i].word;
                    cout << setw(15) << right << FourthColumn[i].count;}
        }
    }
        else{
        for (int i = 0; i < words.size(); i++){
        if(i<30){
            FirstColumn.push_back(words[i]);
        }
        if(i> 30 && i<60){
            SecondColumn.push_back(words[i]);
        }
        if(i> 60 && i<90){
            ThirdColumn.push_back(words[i]);
        }
        if(i> 90 && i<140){
            FourthColumn.push_back(words[i]);
        }
    }

    for (int i = 0; i < FirstColumn.size(); i++){
        if(i==0){
            cout << setw(12) << left << "Word"  << setw(15) << right << " Count ";
            cout << setw(13) << left << "Word"  << setw(16) << right << "Count ";
            cout << setw(12) << left << "Word"  << setw(16) << right << "Count ";
            cout << setw(12) << left << "Word"  << setw(15) << right << "Count" << endl;
            cout << setw(13) << left << "----"  << setw(15) << right << " ---- " ;
            cout << setw(12) << left << "----"  << setw(16) << right << "---- " ;
            cout << setw(12) << left << "----"  << setw(16) << right << "---- " ;
            cout << setw(12) << left << "----"  << setw(15) << right << "----" << endl;}
        cout<< endl;
        cout << setw(12) << left << FirstColumn[i].word;
        cout << setw(15) << right << FirstColumn[i].count << " ";
        if(i<SecondColumn.size()){cout << setw(12) << left << SecondColumn[i].word;
        cout << setw(15) << right << SecondColumn[i].count << " ";}
        if(i<ThirdColumn.size()){ cout << setw(12) << left << ThirdColumn[i].word;
        cout << setw(15) << right << ThirdColumn[i].count << " ";}
        if(i<FourthColumn.size())cout << setw(12) << left << FourthColumn[i].word;
        cout << setw(15) << right << FourthColumn[i].count;}
        }

    }





