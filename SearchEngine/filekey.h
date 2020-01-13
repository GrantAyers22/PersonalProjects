//owner Grant Ayers
#ifndef FILEKEY_H
#define FILEKEY_H
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class FileKey
{
public:
    FileKey();
    FileKey(string kw, string fn);
    vector<string> getFiles();
    string getKeyWord();

    void addFile(string fn);
    void addFile(vector<string> fns);
    bool fileContains(string fn);


    FileKey& operator= (const FileKey& keyToEqual);
    bool operator== (const FileKey& keyToCompare);
    bool operator< (const FileKey& keyToCompare);
    bool operator> (const FileKey& keyToCompare);

    FileKey& operator= (FileKey& keyToEqual);
    bool operator== (FileKey& keyToCompare);
    bool operator< (FileKey& keyToCompare);
    bool operator> (FileKey& keyToCompare);

    friend ostream& operator<<(ostream& os, const FileKey fk);


private:
    string keyWord;
    vector<string> fileName;
};

#endif // FILEKEY_H
