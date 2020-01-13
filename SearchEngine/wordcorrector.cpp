//owner: Grant Ayers
#include "wordcorrector.h"
#include <string>
#include <vector>
#include <iostream>
#include "porter2_stemmer.h"
#include <cstring>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

WordCorrector::WordCorrector(){
}

WordCorrector::WordCorrector(string p, vector<string> stopWords){
    keyWords = vector<string>();
    p = p.substr(p.find_first_not_of(" "), p.size());

    p = removeTags(p);
    p = removeN(p);
    p = removeSpecialCharacters(p);
    stemWords(p, stopWords);
}

vector<string> WordCorrector::getParagraph(){
    return keyWords;
}

void WordCorrector :: stemWords(string p, vector<string> stopWords){
    transform(p.begin(), p.end(), p.begin(), ::tolower);
    if (p.find_first_not_of(" ") == string :: npos){}
    else{
        string tempPG = p.substr(p.find_first_not_of(" "), p.size());
        while ((tempPG.find(' ') != string::npos) && tempPG.find_first_not_of(' ') != string :: npos){
               unsigned long indexOfSpace = tempPG.find_first_of(" ");
                string word = tempPG.substr(0, indexOfSpace);
                if((binary_search(stopWords.begin(), stopWords.end(), word))){}
                else{
                    keyWords.push_back(stemWord(word));
                }
                tempPG = tempPG.substr(indexOfSpace+1, tempPG.size());
                if (tempPG.find_first_not_of(" ") != string :: npos)
                    tempPG = tempPG.substr(tempPG.find_first_not_of(" "), tempPG.size());
        }
    }
}

string WordCorrector :: stemWord(string word){
    Porter2Stemmer :: stem(word);
    return word;
}

string WordCorrector :: removeTags(string p){
    while ((p.find("<") != string::npos) || (p.find(">") != string::npos)){
        unsigned long index1 = p.find_first_of('<');
        unsigned long index2 = p.find_first_of('>');
        p =  p.substr(0, index1) + " " + p.substr(index2+1, p.size());
    }
    return p;
}

string WordCorrector :: removeN(string p){
    while (p.find("\\n") != string :: npos){
        unsigned long index1 = p.find("\\n");
        string r1 = p.substr(0, index1);
        string r2 = p.substr(index1+2, p.size());
        p =  r1 + " " + r2;
    }
    return p;
}
string WordCorrector :: removeSpacing(string p){
    unsigned long start = p.find_first_not_of(" ");
    p = p.substr(start, p.size());
    return p;
}

string WordCorrector :: removeSpecialCharacters(string paragraph){
    unsigned long  j = 0;
    for (unsigned long i = 0; i < paragraph.size(); i++){
        if ( (paragraph[i] >= 'A' && paragraph[i] <= 'Z') || (paragraph[i] >= 'a' && paragraph[i] <= 'z') || (paragraph[i] == ' ') ){
            paragraph[j] = paragraph[i];
            j++;
        }
    }
    return paragraph.substr(0, j);
}
