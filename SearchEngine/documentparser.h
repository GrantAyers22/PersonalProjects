//owner Grant Ayers
//Many updates by Tim
#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H
#include "wordcorrector.h"
#include <vector>
#include <string>
#include <fstream>
#include <dirent.h>
#include <iostream>
#include "avltree.h"
#include "filekey.h"
#include "index.h"

using namespace std;

class DocumentParser
{
public:
    DocumentParser();
    DocumentParser(string fp);
    void run();
    void readThroughFolder(string folderPath);
    void readFile(string file, string folderPath);
    void addElement(vector<string> keyWords, string file);
    int getNodes();
    int totalOccurances(string wordToFind);
    int numberOfDocumentsWith(string wordToFind);
    void printTree();
    void fillStopWords();
    FileKey find(string wordToFind);
    long long getNumFilesParsed();
    long long getNumWordsParsed();
    vector<string> getKeyWords();
    vector<int> getKeyWordFrequencies();
    void clear();

private:
    Index* reversedIndex;
    vector<string> stopWords;
    vector<string> keyWords;
    vector<int>    keyWordFrequencies;
    string filePath;
    long long numFilesParsed;
    long long numWordsParsed;
};

#endif // DOCUMENTPARSER_H
