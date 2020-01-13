//owner Grant Ayers
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "avltree.h"
#include "index.h"
#include <functional>
template<class T>
class HashTableDS //: public Index<T>
{
    template <typename K, typename V>
    class HashNode {
    public:
        HashNode(){
            keys = new K[5];
            values = new V[5];
            numIn = 0;
        }
        HashNode(const K &key, const V &value){
            keys = new K[5];
            keys[0] = key;
            values = new V[5];
            values[0] = value;
            numIn = 1;
        }
        ~HashNode(){
            delete[] keys;
            delete[] values;
        }

        V& getValue(K key){
            for(int i = 0; i < numIn; i++){
                if(keys[i] == key){
                    return values[i];
                }
            }
            throw std::underflow_error("not in here");
        }

        V*& getValues(){
            return values;
        }

        K*& getKeys(){
            return keys;
        }

        int getNum(){
            return numIn;
        }

        bool addValue(K key, V value){
            if(numIn>=4)
                return false;
            keys[numIn] = key;
            values[numIn] = value;
            numIn++;
            return true;
        }

        bool room(){
            return numIn<4;
        }
        bool contains(K key){
            for(int i = 0; i < numIn; i++){
                if(keys[i] == key){
                    return true;
                }
            }
            return false;
        }


    private:
        // key-value pair
        K* keys;
        V* values;
        int numIn;
    };
private:
    HashNode<std::string,T>* data;
    int currSize;
    int capacity;
public:
    HashTableDS(){
        data = new HashNode<std::string,T>[10000];
        capacity = 10000;
        currSize = 0;
        for(int i = 0; i<capacity; i++){
            data[i] = HashNode<std::string,T>();
        }
    }
    HashTableDS(const HashTableDS<T>& rhs);
    HashTableDS(int numElements){
        data = new HashNode<std::string,T>[numElements];
        capacity = numElements;
        currSize = 0;
        for(int i = 0; i<capacity; i++){
            data[i] = HashNode<std::string,T>();
        }
    }
    ~HashTableDS(){
        delete[] data;
    }
    void add(std::string key, T thing){
        int hash = std::hash<std::string>().operator()(key);
        int spot = hash%capacity;
        if(!data[spot].room())
            resize();
        data[spot].addValue(key,thing);
        currSize++;
    }
    T& get(std::string key){
        int hash = std::hash<std::string>().operator()(key);
        int spot = hash%capacity;
        if(data[spot].contains(key)){
            return data[spot].getValue(key);
        }
        throw std::underflow_error("not in table");
    }
    T& operator[](std::string key){
        return get(key);
    }

    bool contains(std::string key){
        int hash = std::hash<std::string>().operator()(key);
        int spot = hash%capacity;
        return(data[spot].contains(key));
    }

    void resize(){
        int newCap = capacity*4;
        HashNode<std::string,T>* newDat = new HashNode<std::string,T>[newCap];
        for(int i = 0; i < newCap; i++){
            newDat[i] = HashNode<std::string,T>();
        }
        for(int i = 0; i < capacity; i++){
            T* vals = data[i].getValues();
            std::string* keys = data[i].getKeys();
            for(int j = 0; j < data[i].getNum(); j++){
                int hash = std::hash<std::string>().operator()(keys[j]);
                int spot = hash%newCap;
                if(!newDat[spot].room())
                    resize();
                data[spot].addValue(keys[i],vals[i]);
            }
        }
        delete[] data;
        data = newDat;
        capacity = newCap;
    }
};

#endif // HASHTABLE_H
