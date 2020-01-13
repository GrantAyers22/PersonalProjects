//owner Grant Ayers
#ifndef WORDCORRECTOR_H
#define WORDCORRECTOR_H
#include <string>
#include "porter2_stemmer.h"
#include <cstring>
#include <vector>

using namespace std;

class WordCorrector{
public:
    WordCorrector();
    WordCorrector(string p, vector<string> stopWords);
    vector<string> getParagraph();

    void stemWords(string paragraph, vector<string> stopWords);
    string stemWord(string word);
    string removeHTML(string paragraph);
    string removeTags(string paragraph);
    string removeN(string paragraph);
    string removeSpacing(string paragraph);
    string removeSpecialCharacters(string paragraph);
    string fixWords(string paragraph);
private:
    string paragraph;
    vector<string> keyWords;

};

#endif // WORDCORRECTOR_H
