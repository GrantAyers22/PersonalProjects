//Owner: Grant Ayers
#include "filekey.h"
#include <string>
#include <vector>

using namespace std;

FileKey::FileKey(){
fileName = vector<string>();
keyWord = "foo";
}
FileKey::FileKey(string kw, string fn){
    fileName = vector<string>();
    keyWord = kw;
    fileName.push_back(fn);
}
vector<string> FileKey :: getFiles(){
    return fileName;
}
string FileKey :: getKeyWord(){
    return keyWord;
}
bool FileKey :: fileContains(string fn){
    for (int i = 0; i<fileName.size(); i++){
        if (fileName.at(i) == fn){
            return true;
        }
    }
    return false;
}

FileKey& FileKey :: operator= (const FileKey& keyToEqual){
    keyWord = keyToEqual.keyWord;
    fileName = keyToEqual.fileName;
    return *this;
}

bool FileKey :: operator== (const FileKey& keyToCompare){
    if (keyToCompare.keyWord == keyWord && keyToCompare.fileName == fileName)
            return true;
    return false;
}

bool FileKey :: operator< (const FileKey& keyToCompare){
    return keyWord < keyToCompare.keyWord;
}

bool FileKey :: operator> (const FileKey& keyToCompare){
    return keyWord > keyToCompare.keyWord;
}

FileKey& FileKey :: operator= (FileKey& keyToEqual){
    keyWord = keyToEqual.keyWord;
    fileName = keyToEqual.fileName;
    return *this;
}

bool FileKey :: operator== (FileKey& keyToCompare){
    if (keyToCompare.keyWord == keyWord && keyToCompare.fileName == fileName)
            return true;
    return false;
}

bool FileKey :: operator< (FileKey& keyToCompare){
    return keyWord < keyToCompare.keyWord;
}

bool FileKey :: operator> (FileKey& keyToCompare){
    return keyWord > keyToCompare.keyWord;
}

void FileKey :: addFile(string fn){
    fileName.push_back(fn);
}
void FileKey :: addFile(vector<string> fns){
    for (unsigned long i = 0; i < fns.size(); i++){
        fileName.push_back(fns.at(i));
    }
}

ostream& operator<<(ostream &os, const FileKey fk){
    os << fk.keyWord << " ";
    for (unsigned long i = 0; i < fk.fileName.size(); i++){
        os << fk.fileName.at(i) << " ";
    }
    return os;
}
