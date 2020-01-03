#include "dsstring.h"
#include <ostream>
#include <cstring>

DSSTRING::DSSTRING(){
    data = nullptr;
}

DSSTRING::DSSTRING(const char* sentData){
    unsigned long leng = strlen(sentData)+1;
    data = new char[leng];
    strcpy(data, sentData);
}

DSSTRING::DSSTRING(const DSSTRING& tempString){
    data = new char[strlen(tempString.data) +1];
    strcpy(data, tempString.data);
}

DSSTRING::~DSSTRING(){
//    if (data != nullptr){
//      delete[] data;
//        data = nullptr;
//    }
}

DSSTRING DSSTRING:: operator= (const char* stringToEqual){
    if (data != nullptr){
        delete[] data;
        data = nullptr;
    }
    data = new char[strlen(stringToEqual)+1];
    strcpy(data, stringToEqual);
    return *this;
}

DSSTRING DSSTRING:: operator= (const DSSTRING& ObjectToEqual){
    if (data != nullptr)
        delete[] data;
    int leng = strlen(ObjectToEqual.data) +1;
    data = new char[leng];
    strcpy(data, ObjectToEqual.data);
    return *this;
}

DSSTRING DSSTRING:: operator+ (const DSSTRING& objectToAdd){
    int len = strlen(data) + strlen(objectToAdd.data) +1;
    char * temp = new char[len];
    strcpy(temp, data);
    strcat(temp, objectToAdd.data);
    DSSTRING ds =  DSSTRING(temp);
    delete[] temp;
    return ds;
}

DSSTRING& DSSTRING:: operator+= (const DSSTRING& objectToAdd){
    char * temp = this ->data;
    this -> data = new char[strlen(temp) + strlen(objectToAdd.data)];
    strcpy(this->data, temp);
    strcat(this->data, objectToAdd.data);
    delete[] temp;
    return *this;
}

bool DSSTRING::operator==(const char * stringToCompare){
    int comp = strcmp(data, stringToCompare);
    if (comp == 0)
        return true;
    return false;
}

bool DSSTRING::operator==(const DSSTRING& objectToCompare){
    int comp = strcmp(data, objectToCompare.data);
    if (comp == 0)
        return true;
    return false;
}
bool DSSTRING::operator!=(const char * stringToCompare){
    int comp = strcmp(data, stringToCompare);
    if (comp == 0)
        return false;
    return true;
}

bool DSSTRING::operator!=(const DSSTRING& objectToCompare){
    int comp = strcmp(data, objectToCompare.data);
    if (comp == 0)
        return false;
    return true;
}
bool DSSTRING::operator<(const char * objectToCompare){
    //finding first non-same character
    int counter = 0;
    while (objectToCompare[counter] == data[counter]){
        counter++;
    }
    if (data[counter] < objectToCompare[counter]){
        return true;
    }
    else{
        return false;
    }
}

bool DSSTRING::operator<(const DSSTRING& objectToCompare){
    char * temp = objectToCompare.data;
    int counter = 0;
    while (temp[counter] == data[counter]){
        counter++;
    }
    if (data[counter] < temp[counter]){
        return true;
    }
    else {
        return false;
    }
}

char& DSSTRING::operator[](const int charPosition){
    if (charPosition > strlen(data)){ throw; }
    return data[charPosition];
}

int DSSTRING::size(){
    return strlen(data);
}

DSSTRING DSSTRING::substring(int startPosition, int numOfChars){
    char * temp;
    int counter = 0;
    int endPosition = startPosition + numOfChars;
    if (numOfChars < 0){
        temp = new char[(numOfChars*-1)+1];
        for (int i = startPosition; i >= endPosition; i--){
            temp[counter] = data[i];
            counter++;
        }
    }
    else {
        temp = new char[numOfChars+1];
        for (int i = startPosition; i < endPosition; i++){
            temp[counter] = data[i];
            counter++;
        }
    }
    return DSSTRING(temp);

}
bool DSSTRING :: isEmpty(){
    return (data == nullptr);
}
char* DSSTRING :: c_str(){
    return data;
}

