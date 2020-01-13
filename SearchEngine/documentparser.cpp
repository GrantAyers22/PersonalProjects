//owner Tim Desmond
#include "documentparser.h"
#include "porter2_stemmer.h"
#include "wordcorrector.h"
#include <string>
#include <vector>
#include <fstream>
#include <dirent.h>
#include <iostream>
#include <cstring>
#include "avltree.h"
#include "filekey.h"
#include "index.h"



using namespace std;

DocumentParser::DocumentParser(){
    numFilesParsed = 0;
    numWordsParsed = 0;
    reversedIndex = new AVLTreeIndex;
}
DocumentParser :: DocumentParser(string fp){
    numFilesParsed = 0;
    numWordsParsed = 0;
    fillStopWords();
    reversedIndex = new AVLTreeIndex;
    filePath = fp;
}

void DocumentParser::run(){
    readThroughFolder(filePath);
}
void DocumentParser::readThroughFolder(string folderPath){
    DIR *pathDirectories;
    struct dirent *entry;
    string file;

    if ((pathDirectories = opendir(folderPath.c_str()))){
        cout << "directory opened" << endl;
        while ((entry = readdir(pathDirectories))){
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") !=0){
                file = entry->d_name;
                readFile(file, folderPath);
                numFilesParsed++;
            }
        }
    }
}

void DocumentParser::readFile(string file, string folderPath){
    ifstream inFile;
    string tempPath = folderPath;
    tempPath += '/';
    tempPath += file;
    string id = file.substr(0, file.size()-5);

    WordCorrector wc;
    string opinion;
    inFile.open(tempPath.c_str());
    if(inFile.is_open()){
        while (getline(inFile, opinion)){
            if (opinion.substr(0, 24) == "  \"html_with_citations\":"){
                wc = WordCorrector(opinion, stopWords);
                addElement(wc.getParagraph(), id);
            }
        }
        inFile.close();
    }
}

FileKey DocumentParser :: find(string wordToFind){
    FileKey toFind = FileKey(wordToFind, "foo.txt");
    return reversedIndex->find(toFind);
}

int findKeyWord(vector<string> keyWords, string keyWord)
{
    for(int i = 0; i < keyWords.size(); i++)
    {
        if (keyWords[i] == keyWord)
        {
            return i;
        }
    }
    return -1;
}

void DocumentParser::addElement(vector<string> keyWordList, string file){
    for (unsigned long i = 0; i < keyWordList.size(); i++){
        FileKey temp = FileKey(keyWordList.at(i), file);
        int index = findKeyWord(keyWords, temp.getKeyWord());
        if (index == -1)
        {
            keyWords.push_back(temp.getKeyWord());
            keyWordFrequencies.push_back(temp.getFiles().size());
        }
        else
        {
            keyWordFrequencies[index] += temp.getFiles().size();
        }
        reversedIndex->insert(temp);
        numWordsParsed++;
    }
}

int DocumentParser :: getNodes(){
    return reversedIndex->getNumOfNodes();
}

void DocumentParser :: printTree(){
    reversedIndex->printTree();
}


long long DocumentParser :: getNumFilesParsed()
{
    return numFilesParsed;
}
long long DocumentParser :: getNumWordsParsed()
{
    return numWordsParsed;
}

vector<string> DocumentParser :: getKeyWords()
{
    return keyWords;
}
vector<int> DocumentParser :: getKeyWordFrequencies()
{
    return keyWordFrequencies;
}
void DocumentParser :: clear(){
    reversedIndex->makeEmpty();
}

void DocumentParser :: fillStopWords(){
    stopWords = vector<string>();
    //a
    stopWords.push_back("a");
    stopWords.push_back("about");
    stopWords.push_back("above");
    stopWords.push_back("act");
    stopWords.push_back("after");
    stopWords.push_back("again");
    stopWords.push_back("against");
    stopWords.push_back("all");
    stopWords.push_back("am");
    stopWords.push_back("an");
    stopWords.push_back("and");
    stopWords.push_back("any");
    stopWords.push_back("are");
    stopWords.push_back("as");
    stopWords.push_back("at");

    //b
    stopWords.push_back("be");
    stopWords.push_back("because");
    stopWords.push_back("been");
    stopWords.push_back("before");
    stopWords.push_back("being");
    stopWords.push_back("below");
    stopWords.push_back("between");
    stopWords.push_back("both");
    stopWords.push_back("but");
    stopWords.push_back("by");

    //c
    stopWords.push_back("c");
    stopWords.push_back("co");

    //d
    stopWords.push_back("did");
    stopWords.push_back("do");
    stopWords.push_back("does");
    stopWords.push_back("doing");
    stopWords.push_back("down");
    stopWords.push_back("during");

    //e
    stopWords.push_back("each");

    //f
    stopWords.push_back("few");
    stopWords.push_back("for");
    stopWords.push_back("from");
    stopWords.push_back("further");

    //h
    stopWords.push_back("had");
    stopWords.push_back("has");
    stopWords.push_back("have");
    stopWords.push_back("having");
    stopWords.push_back("he");
    stopWords.push_back("her");
    stopWords.push_back("here");
    stopWords.push_back("hers");
    stopWords.push_back("herself");
    stopWords.push_back("him");
    stopWords.push_back("himself");
    stopWords.push_back("his");
    stopWords.push_back("how");

    //i
    stopWords.push_back("i");
    stopWords.push_back("if");
    stopWords.push_back("in");
    stopWords.push_back("into");
    stopWords.push_back("is");
    stopWords.push_back("it");
    stopWords.push_back("its");
    stopWords.push_back("itself");

    //l
    stopWords.push_back("law");

    //m
    stopWords.push_back("me");
    stopWords.push_back("more");
    stopWords.push_back("most");
    stopWords.push_back("my");
    stopWords.push_back("myself");

    //n
    stopWords.push_back("no");
    stopWords.push_back("nor");
    stopWords.push_back("not");

    //o
    stopWords.push_back("of");
    stopWords.push_back("off");
    stopWords.push_back("on");
    stopWords.push_back("once");
    stopWords.push_back("only");
    stopWords.push_back("or");
    stopWords.push_back("other");
    stopWords.push_back("our");
    stopWords.push_back("ours");
    stopWords.push_back("ourselves");
    stopWords.push_back("out");
    stopWords.push_back("over");
    stopWords.push_back("own");

    //s
    stopWords.push_back("same");
    stopWords.push_back("she");
    stopWords.push_back("so");
    stopWords.push_back("some");
    stopWords.push_back("state");
    stopWords.push_back("such");

    //t
    stopWords.push_back("than");
    stopWords.push_back("that");
    stopWords.push_back("the");
    stopWords.push_back("their");
    stopWords.push_back("theirs");
    stopWords.push_back("them");
    stopWords.push_back("themselves");
    stopWords.push_back("then");
    stopWords.push_back("there");
    stopWords.push_back("these");
    stopWords.push_back("they");
    stopWords.push_back("this");
    stopWords.push_back("those");
    stopWords.push_back("through");
    stopWords.push_back("to");
    stopWords.push_back("too");

    //u
    stopWords.push_back("up");
    stopWords.push_back("under");
    stopWords.push_back("until");
    stopWords.push_back("us");

    //v
    stopWords.push_back("v");
    stopWords.push_back("very");

    //w
    stopWords.push_back("was");
    stopWords.push_back("we");
    stopWords.push_back("were");
    stopWords.push_back("what");
    stopWords.push_back("when");
    stopWords.push_back("where");
    stopWords.push_back("which");
    stopWords.push_back("while");
    stopWords.push_back("who");
    stopWords.push_back("whom");
    stopWords.push_back("why");
    stopWords.push_back("with");

    //y
    stopWords.push_back("you");
    stopWords.push_back("your");
    stopWords.push_back("yours");
    stopWords.push_back("yourself");
    stopWords.push_back("yourselves");
}
