#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>
#include <cstring>

class DSSTRING{

private:
    char* data;
    int length;
public:
    DSSTRING();
    DSSTRING(const char* sentData);
    DSSTRING(const DSSTRING&);
    ~DSSTRING();

    DSSTRING operator= (const char*);
    DSSTRING operator= (const DSSTRING&);
    DSSTRING operator+ (const DSSTRING&);
    DSSTRING& operator+= (const DSSTRING&);

    bool operator== (const char*);
    bool operator== (const DSSTRING&);
    bool operator!= (const char*);
    bool operator!= (const DSSTRING&);
    bool operator< (const char*);
    bool operator< (const DSSTRING&);
    bool isEmpty();
    char& operator[] (const int);

    int size();

    DSSTRING substring(int a, int b);

    char* c_str();

    friend std :: ostream& operator<< (std :: ostream& output, const DSSTRING& DS){
        output << DS.data;
        return output;
    }

};

#endif // DSSTRING_H
