//Owner: Tim Desmond
#include <iostream>
#include <istream>
#include <string>
#include <sstream>
#include <cstring>
#include <chrono>
#include <vector>
#include <algorithm>
#include "wordcorrector.h"
#include "documentparser.h"
#include "avltree.h"
#include "filekey.h"
#include "porter2_stemmer.h"

using namespace std;

void remove(std::vector<string> &v){
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = std::remove(it + 1, end, *it);
    }
    v.erase(end, v.end());
}

vector<string> separateIntoWords(string searchQuery)
{
    string word;
    vector<string> queryWords;
    stringstream queryStream(searchQuery);

    while (queryStream >> word)
        queryWords.push_back(word);
    return queryWords;
}

bool doesNotContain(vector<string> fileList, string str)
{
    for (int i = 0; i < fileList.size(); i++)
    {
        if (fileList[i] == str)
        {
            return false;
        }
    }
    return true;
}

vector<string> removeDuplicates(vector<string> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec.size(); j++)
        {
            if (j != i && vec[i] == vec[j])
            {
                vec.erase(vec.begin() + j);
                j--;
            }
        }
    }
    return vec;
}


// AND tom sue bar
// tom = A B C D
// sue = B D E
// bar = A C D E F

vector<string> findAnyMatchingFiles(vector<vector<string> > orFileList)
{
    vector<string> allFilesList;
    // Iterate over all the files
    for (int i = 0; i < orFileList.size(); i++)
    {
        // Iterate over all the lists of files containing the other ANDed terms
        for (int j = 0; j < orFileList[i].size(); j++)
        {
            allFilesList.push_back(orFileList[i][j]);
        }
    }
    allFilesList = removeDuplicates(allFilesList);
    return allFilesList;
}


vector<string> findCommonFiles(vector<vector<string> > andFileList)
{
    // Get all files containing the first ANDed term
    vector<string> filesWithFirstWord = andFileList[0];
    // Iterate over all the files
    for (int i = 0; i < filesWithFirstWord.size(); i++)
    {
        // Iterate over all the lists of files containing the other ANDed terms
        for (int j = 0; j < andFileList.size() && i != -1; j++)
        {
            //cout << " BEGIN NESTED FOR" << endl;
            //cout << "filesWithFirstWord.size() = " << filesWithFirstWord.size() << endl;
            //cout << "i = " << i << endl;


            // If the other ANDed term's file list does not contain the current file
            // being examinined from the first ANDed term's list, we will remove it
            if(filesWithFirstWord.size() != 0 && doesNotContain(andFileList[j], filesWithFirstWord[i]))
            {
                //cout << "BEGIN IF" << endl;
                //cout << "i = " << i << endl;
                //cout << "filesWithFirstWord.size() = " << filesWithFirstWord.size() << endl;
                filesWithFirstWord.erase(filesWithFirstWord.begin() + i);
                i--;
                //cout << "END_OF_IF" << endl;
            }
            //cout << " END NESTED FOR" << endl;
        }
    }
    return filesWithFirstWord;
}

vector<string> removeMatchingFiles(vector<string> filesWithAllSearchTerms, vector<string> filesWithAnyNotTerms)
{
    vector<string> filesWithAllSearchTermsAndNoNotTerms;
    for (int i = 0; i < filesWithAllSearchTerms.size(); i++)
    {
        if(doesNotContain(filesWithAnyNotTerms, filesWithAllSearchTerms[i]))
        {
            filesWithAllSearchTermsAndNoNotTerms.push_back(filesWithAllSearchTerms[i]);
        }
    }
    return filesWithAllSearchTermsAndNoNotTerms;
}

vector<string> getSortedTop15(vector<string> filenameList)
{
    vector<string> uniqueFiles = removeDuplicates(filenameList);
    vector<int> uniqueFileCounts;
    for (int i = 0; i < uniqueFiles.size(); i++)
    {
        uniqueFileCounts.push_back(0);
    }
    for (int i = 0; i < filenameList.size(); i++)
    {
        for (int j = 0; j < uniqueFiles.size(); j++)
        {
            if (filenameList[i] == uniqueFiles[j])
            {
                uniqueFileCounts[j]++;
            }
        }
    }
    for (int i = 0; i < uniqueFileCounts.size(); i++)
    {
        for (int j = 0; j < uniqueFileCounts.size() - 1; j++)
        {
            if(uniqueFileCounts[j] < uniqueFileCounts[j+1])
            {
                int temp = uniqueFileCounts[j];
                string tempStr = uniqueFiles[j];
                uniqueFileCounts[j] = uniqueFileCounts[j+1];
                uniqueFileCounts[j+1] = temp;
                uniqueFiles[j] = uniqueFiles[j+1];
                uniqueFiles[j+1] = tempStr;
            }
        }
    }
    vector<string> top15;
    for (int i = 0; i < uniqueFiles.size() && i < 15; i++)
    {
        top15.push_back(uniqueFiles[i]);
    }
    return top15;
}

void sortByFrequency(vector<string> & keyWords, vector<int> & keyWordFrequencies)
{
    for (int i = 0; i < keyWordFrequencies.size(); i++)
    {
        for (int j = 0; j < keyWordFrequencies.size() - 1; j++)
        {
            if(keyWordFrequencies[j] < keyWordFrequencies[j+1])
            {
                int temp = keyWordFrequencies[j];
                string tempStr = keyWords[j];
                keyWordFrequencies[j] = keyWordFrequencies[j+1];
                keyWordFrequencies[j+1] = temp;
                keyWords[j] = keyWords[j+1];
                keyWords[j+1] = tempStr;
            }
        }
    }
}
string importantInfo(string id, string fp){
    fp += '/';
    fp += id;
    fp += ".json";
    ifstream inFile;
    string opinion;
    WordCorrector wc = WordCorrector();
    vector<string> words = vector<string>();
    string returnme = "";
    inFile.open(fp);
    if(inFile.is_open()){
        while (getline(inFile, opinion)){
            if (opinion.substr(0, 24) == "  \"html_with_citations\":"){
                opinion = wc.removeTags(opinion);
                opinion = opinion.substr(25, opinion.size());
                opinion = wc.removeTags(opinion);
                opinion = wc.removeN(opinion);
                unsigned long  j = 0;
                for (unsigned long i = 0; i < opinion.size(); i++){
                    if ( (opinion[i] >= 'A' && opinion[i] <= 'Z') || (opinion[i] >= 'a' && opinion[i] <= 'z') || (opinion[i] == ' ') || (opinion[i] >= '0' && opinion[i] <= '9')){
                        opinion[j] = opinion[i];
                        j++;
                    }
                }
                opinion = opinion.substr(0, j);
                string tempPG = opinion.substr(opinion.find_first_not_of(" "), opinion.size());
                while ((tempPG.find(' ') != string::npos) && tempPG.find_first_not_of(' ') != string :: npos){
                       unsigned long indexOfSpace = tempPG.find_first_of(" ");
                        string word = tempPG.substr(0, indexOfSpace);
                        words.push_back((word));
                        tempPG = tempPG.substr(indexOfSpace+1, tempPG.size());
                        if (tempPG.find_first_not_of(" ") != string :: npos)
                            tempPG = tempPG.substr(tempPG.find_first_not_of(" "), tempPG.size());
                }
                for (int i = 0; i < words.size(); i++){
                    if (words[i] == "Justice"){
                        returnme += words[i] + " " + words[i+1] + " ";
                    }
                    if (words[i] == "Decided" ){
                        returnme += words[i] + " " + words[i+1] + " " + words[i+2] + " " + words[i+3] + " ";
                    }
                }
            }
        }
    }
    return returnme;
}


vector<string> executeAndQuery(vector<string> searchWords, vector<string> notWords, DocumentParser& dp, string filePath)
{
    vector<vector<string> > searchTermFileLists;
    vector<vector<string> > searchTermFileListsWithDuplicates;
    for (int i = 1; i < searchWords.size(); i++)
    {
        cout << "searchWords[i] = " << searchWords[i] << endl;
        Porter2Stemmer :: stem(searchWords[i]);
        FileKey name = dp.find(searchWords[i]);
        vector<string> files = name.getFiles();
        searchTermFileListsWithDuplicates.push_back(files);
        files = removeDuplicates(files);
        searchTermFileLists.push_back(files);
        //remove(files);
    }
    /*
    for (int i = 0; i < searchTermFileLists.size(); i++)
    {
        cout << "SearchTerm: " << searchWords[i+1] << "   " << endl;
        for (int j = 0; j < searchTermFileLists[i].size(); j++)
        {
            cout << searchTermFileLists[i][j] << endl;
        }
    }
    */
    vector<string> filesWithAllSearchTerms = findCommonFiles(searchTermFileLists);
    vector<string> filesWithAllSearchTermsWithDuplicates = findCommonFiles(searchTermFileListsWithDuplicates);

    vector<vector<string> > notTermFileLists;
    for (int i = 0; i < notWords.size(); i++)
    {
        //cout << "notWords[i] = " << notWords[i] << endl;
        Porter2Stemmer :: stem(notWords[i]);
        FileKey name = dp.find(notWords[i]);
        vector<string> files = name.getFiles();
        //for (int j = 0; j < files.size(); j++)
        //{
        //    cout << "NOT files[j] = " << files[j] << endl;
        //}
        files = removeDuplicates(files);
        notTermFileLists.push_back(files);
    }
    vector<string> filesWithAnyNotTerms = findAnyMatchingFiles(notTermFileLists);
    //for (int j = 0; j < filesWithAnyNotTerms.size(); j++)
    //{
    //    cout << "filesWithAnyNotTerms[j] = " << filesWithAnyNotTerms[j] << endl;
    //}
    vector<string> filesWithAllSearchTermsAndNoNotTerms = removeMatchingFiles(filesWithAllSearchTerms, filesWithAnyNotTerms);
    vector<string> filesWithAllSearchTermsAndNoNotTermsWithDuplicates = removeMatchingFiles(filesWithAllSearchTermsWithDuplicates, filesWithAnyNotTerms);
    //remove(files);
    int uniqueOccurances = filesWithAllSearchTermsAndNoNotTerms.size();
    cout << "Number of files containing all search terms: " << uniqueOccurances << endl;
    vector<string> sortedTop15 = getSortedTop15(filesWithAllSearchTermsAndNoNotTermsWithDuplicates);
    for (int i = 0; i < sortedTop15.size(); i++)
    {
        cout << "Search Results (Ranked " << i+1 << ") : "<<sortedTop15[i] << " " << importantInfo(sortedTop15[i], filePath) <<endl;
    }
    return sortedTop15;
    /*
    for (int i = 0; i < filesWithAllSearchTermsAndNoNotTerms.size(); i++)
    {
        cout << "filesWithAllSearchTerms[i]: "<<filesWithAllSearchTermsAndNoNotTerms[i]<<endl;
    }
    return filesWithAllSearchTermsAndNoNotTerms;
    */
}

vector<string> executeOrQuery(vector<string> searchWords, vector<string> notWords, DocumentParser& dp, string filePath)
{
    vector<vector<string> > searchTermFileLists;
    vector<vector<string> > searchTermFileListsWithDuplicates;
    for (int i = 1; i < searchWords.size(); i++)
    {
        Porter2Stemmer :: stem(searchWords[i]);
        FileKey name = dp.find(searchWords[i]);
        vector<string> files = name.getFiles();
        searchTermFileListsWithDuplicates.push_back(files);
        files = removeDuplicates(files);
        searchTermFileLists.push_back(files);
        // remove(files);
    }
    /*
    for (int i = 0; i < searchTermFileLists.size(); i++)
    {
        cout << "SearchTerm: " << searchWords[i+1] << "   " << endl;
        for (int j = 0; j < searchTermFileLists[i].size(); j++)
        {
            cout << searchTermFileLists[i][j] << endl;
        }
    }
    */
    vector<vector<string> > notTermFileLists;
    for (int i = 0; i < notWords.size(); i++)
    {
        //cout << "notWords[i] = " << notWords[i] << endl;
        Porter2Stemmer :: stem(notWords[i]);
        FileKey name = dp.find(notWords[i]);
        vector<string> files = name.getFiles();
        //for (int j = 0; j < files.size(); j++)
        //{
        //    cout << "NOT files[j] = " << files[j] << endl;
        //}
        files = removeDuplicates(files);
        notTermFileLists.push_back(files);
    }
    vector<string> filesWithAnyNotTerms = findAnyMatchingFiles(notTermFileLists);
    //for (int j = 0; j < filesWithAnyNotTerms.size(); j++)
    //{
    //    cout << "filesWithAnyNotTerms[j] = " << filesWithAnyNotTerms[j] << endl;
    //}

    vector<string> filesWithAnySearchTerms = findAnyMatchingFiles(searchTermFileLists);
    vector<string> filesWithAnySearchTermsWithDuplicates = findAnyMatchingFiles(searchTermFileListsWithDuplicates);
    vector<string> filesWithAnySearchTermsAndNoNotTerms = removeMatchingFiles(filesWithAnySearchTerms, filesWithAnyNotTerms);
    vector<string> filesWithAnySearchTermsAndNoNotTermsWithDuplicates = removeMatchingFiles(filesWithAnySearchTermsWithDuplicates, filesWithAnyNotTerms);

    //remove(files);
    int uniqueOccurances = filesWithAnySearchTermsAndNoNotTerms.size();
    cout << "Number of files containing any search terms: " << uniqueOccurances << endl;
    vector<string> sortedTop15 = getSortedTop15(filesWithAnySearchTermsAndNoNotTermsWithDuplicates);
    for (int i = 0; i < sortedTop15.size(); i++)
    {
        cout << "Search Results (Ranked " << i+1 << ") : "<<sortedTop15[i] << " " << importantInfo(sortedTop15[i], filePath) <<endl;
    }
    return sortedTop15;
    /*
    for (int i = 0; i < filesWithAnySearchTermsAndNoNotTerms.size(); i++)
    {
        cout << "filesWithAnySearchTerms[i]: "<<filesWithAnySearchTermsAndNoNotTerms[i]<<endl;
    }
    return filesWithAnySearchTermsAndNoNotTerms;
    */
}

vector<string> executeQuery(vector<string> searchWords, vector<string> notWords, DocumentParser& dp, string folderPath)
{
    if (searchWords.size() > 1)
    {
        cout << "Please do not provide multiple search terms without a condition such as AND/OR" << endl;
    }
    string wordToSearch = searchWords[0];
    Porter2Stemmer :: stem(wordToSearch);


    FileKey name = dp.find(wordToSearch);
    vector<string> files = name.getFiles();

    vector<vector<string> > notTermFileLists;
    for (int i = 0; i < notWords.size(); i++)
    {
        //cout << "notWords[i] = " << notWords[i] << endl;
        Porter2Stemmer :: stem(notWords[i]);
        FileKey n = dp.find(notWords[i]);
        vector<string> files = n.getFiles();
        //for (int j = 0; j < files.size(); j++)
        //{
        //    cout << "NOT files[j] = " << files[j] << endl;
        //}
        files = removeDuplicates(files);
        notTermFileLists.push_back(files);
    }
    vector<string> filesWithAnyNotTerms = findAnyMatchingFiles(notTermFileLists);
    //for (int j = 0; j < filesWithAnyNotTerms.size(); j++)
    //{
    //    cout << "filesWithAnyNotTerms[j] = " << filesWithAnyNotTerms[j] << endl;
    //}
    vector<string> filesWithSearchTermAndNoNotTerms = removeMatchingFiles(files, filesWithAnyNotTerms);

    //for (int i = 0; i < files.size(); i++)
    //{
    //    cout << "files[i] =" << files[i] << endl;
    //}
    int totalOccurances = filesWithSearchTermAndNoNotTerms.size();
    //remove(files);

    cout << "Number of Nodes: " << dp.getNodes() << endl;
    cout << "Number of total occurances of search term: " << totalOccurances << endl;
    vector<string> sortedTop15 = getSortedTop15(filesWithSearchTermAndNoNotTerms);
    filesWithSearchTermAndNoNotTerms = removeDuplicates(filesWithSearchTermAndNoNotTerms);
    int uniqueOccurances = filesWithSearchTermAndNoNotTerms.size();
    cout << "Number of unique occurances of search term: " << uniqueOccurances << endl;
    for (int i = 0; i < sortedTop15.size(); i++)
    {
        cout << "Search Results (Ranked " << i+1 << ") : "<< sortedTop15[i]<< " " << importantInfo(sortedTop15[i], folderPath) << endl;
    }
    return sortedTop15;
    /*
    filesWithSearchTermAndNoNotTerms = removeDuplicates(filesWithSearchTermAndNoNotTerms);
    int uniqueOccurances = filesWithSearchTermAndNoNotTerms.size();
    cout << "Number of unique occurances of search term: " << uniqueOccurances << endl;
    for (int i = 0; i < filesWithSearchTermAndNoNotTerms.size(); i++)
    {
        cout << "filesWithSearchTermAndNoNotTerms[i]: "<<filesWithSearchTermAndNoNotTerms[i]<<endl;
    }
    return filesWithSearchTermAndNoNotTerms;
    */
}

void print300WordsFromSelected(vector<string> filenameList, string datapath)
{
    cout << "Would you like to print a 300-word intro to one of the found files(y/n)?>";
    string answer = "";
    cin >> answer;
    cin.ignore (numeric_limits<streamsize>::max(), '\n');
    if (answer == "y")
    {
        cout << "Files Displayed Below: " << endl;
        for (int i = 0; i < filenameList.size(); i++)
        {
            cout << "File " << (i+1) << " : " << filenameList[i] << endl;
        }
        cout << "Please enter filename to print>";
        string filename = "";
        cin >> filename;
        cin.ignore (numeric_limits<streamsize>::max(), '\n');
        for (int i = 0; i < filenameList.size(); i++)
        {
            if (filename == filenameList[i])
            {
                string fullpath = datapath;
                fullpath = fullpath + "/" +filename + ".json";
                fstream file;
                string word;
                fstream deniedFile;
                string deniedWord;
                deniedFile.open(fullpath.c_str());
                bool denied = false;
                string previousWord = "";
                while (deniedFile >> word)
                {
                    if (previousWord == "Certiorari" && word == "denied.")
                    {
                        denied = true;
                    }
                    previousWord = word;
                }

                if (denied)
                {
                    cout << "File " << filename << " found to be 'Certiorari denied'." << endl;
                }
                else
                {
                    ifstream infile;
                    string opinion = "";
                    cout << "File " << filename << " found, printing 300-word excerpt below." << endl;
                    cout << " . . . ";
                    infile.open(fullpath.c_str());
                    if(infile.is_open()){
                        WordCorrector wc;
                        vector<string> stopWords;
                        vector<string> words;
                        int size;
                        while (getline(infile, opinion)){
                            if (opinion.substr(0, 24) == "  \"html_with_citations\":"){
                                wc = WordCorrector();
                                opinion = opinion.substr(25, opinion.size());
                                opinion = wc.removeTags(opinion);
                                opinion = wc.removeN(opinion);
                                opinion = wc.removeSpecialCharacters(opinion);

                                string tempPG = opinion.substr(opinion.find_first_not_of(" "), opinion.size());
                                while ((tempPG.find(' ') != string::npos) && tempPG.find_first_not_of(' ') != string :: npos){
                                       unsigned long indexOfSpace = tempPG.find_first_of(" ");
                                        string word = tempPG.substr(0, indexOfSpace);
                                        if((binary_search(stopWords.begin(), stopWords.end(), word))){}
                                        else{
                                            words.push_back((word));
                                        }
                                        tempPG = tempPG.substr(indexOfSpace+1, tempPG.size());
                                        if (tempPG.find_first_not_of(" ") != string :: npos)
                                            tempPG = tempPG.substr(tempPG.find_first_not_of(" "), tempPG.size());
                                }

                                if (words.size() > 300){
                                    size = 300;
                                }
                                else{
                                    size = words.size();
                                }
                                for (int i = 0; i < size; i++){
                                    cout << words.at(i) + " ";
                                }
                            }
                        }
                    }
                    cout << " . . . ";
                    cout << endl;
                }
            }
        }
    }
}


int main(int argc, char** argv){

    cout << "Please enter a directory containing court decision info: ";
    string filePath = "";
    cin >> filePath;
    cin.ignore (numeric_limits<streamsize>::max(), '\n');
    cout << "filePath = " << filePath << endl;
    DocumentParser dp = DocumentParser(filePath);
    dp.run();


    //string wordToSearch = argv[2];
    vector<string> searchWords;
    string databaseMode = "";

    while (databaseMode != "quit")
    {
        cout << "Please enter database mode(QUERY/MAINTENANCE/STATS)>";
        cin >> databaseMode;
        cin.ignore (numeric_limits<streamsize>::max(), '\n');

        if (databaseMode == "QUERY")
        {
            string query = "";
            cout << "Please enter a search query into the database>";
            getline(cin, query);
            cin.ignore (numeric_limits<streamsize>::max(), '\n');
            cout << "query = " << query << endl;
            searchWords = separateIntoWords(query);
            for (int i = 0; i < searchWords.size(); i++)
            {
                if ( searchWords[i] != "AND" && searchWords[i] != "OR" && searchWords[i] != "NOT")
                {
                    for (int j = 0; j < searchWords[i].length(); j++)
                    {
                        searchWords[i][j] = tolower(searchWords[i][j]);
                    }
                }
            }
            //for (int i = 2; i < argc; i++)
            //{
            //    searchWords.push_back(argv[i]);
            //}
            // All words preceded by a NOT
            vector<string> notWords;
            for (int i = 0; i < searchWords.size(); i++)
            {
                if (searchWords[i] == "NOT")
                {
                    notWords.push_back(searchWords[i+1]);
                    searchWords.erase(searchWords.begin() + i+1);
                    searchWords.erase(searchWords.begin() + i);
                    i--;
                    i--;
                }
            }
            for (int i = 0; i < searchWords.size(); i++)
            {
                cout << "searchWords[i] = " << searchWords[i] << endl;
            }
            for (int i = 0; i < notWords.size(); i++)
            {
                cout << "notWords[i] = " << notWords[i] << endl;
            }


            //start timer
            auto start = chrono::steady_clock::now();
            //run
            //end timer

            if (searchWords[0] == "AND")
            {
                vector<string> foundFiles = executeAndQuery(searchWords, notWords, dp, filePath);
                auto end = chrono::steady_clock::now();
                cout << "Total time to perform query: " << chrono::duration_cast<chrono::seconds>(end-start).count() << " seconds" << endl;
                print300WordsFromSelected(foundFiles, filePath);
            }
            else if (searchWords[0] == "OR")
            {
                vector<string> foundFiles = executeOrQuery(searchWords, notWords, dp, filePath);
                auto end = chrono::steady_clock::now();
                cout << "Total time to perform query: " << chrono::duration_cast<chrono::seconds>(end-start).count() << " seconds" << endl;
                print300WordsFromSelected(foundFiles, filePath);

            }
            else // No condition provided case
            {
                vector<string> foundFiles = executeQuery(searchWords, notWords, dp, filePath);
                auto end = chrono::steady_clock::now();
                cout << "Total time to perform query: " << chrono::duration_cast<chrono::seconds>(end-start).count() << " seconds" << endl;
                print300WordsFromSelected(foundFiles, filePath);
            }
        }
        else if (databaseMode == "MAINTENANCE")
        {
            string choice;
            cout << "Choose from the following:" << endl;
            cout << "ADD/CLEAR/POPULATE: ";
            cin >> choice;
            if (choice == "ADD"){
                string fileName = "";
                cout << "Enter the full folder: ";
                cin >> fileName;
                cin.ignore (numeric_limits<streamsize>::max(), '\n');
                filePath = fileName;
                cout << "FILENAME: " << fileName;
                dp.readThroughFolder(fileName);
            }
            if (choice == "CLEAR"){
                dp.clear();
                cout << "All files cleared" << endl;
            }
            if (choice == "POPULATE"){
                auto beginBoi = chrono::steady_clock::now();
                dp.readThroughFolder("/home/student/Desktop/scotus-small");
                filePath = "/home/student/Desktop/scotus-small";
                auto doneBoi = chrono::steady_clock::now();
                cout << "TIME: " << chrono::duration_cast<chrono::seconds>(doneBoi-beginBoi).count() << endl;
            }
        }
        else if (databaseMode == "STATS")
        {
            long long numOpinions = dp.getNumFilesParsed();
            long long numWordsIndexed = dp.getNumWordsParsed();
            double numWordsPerOpinion = (double) numWordsIndexed / (double) numOpinions;
            cout << "This database has indexed " << numOpinions << " opinions. " << endl;
            cout << "There are an average of " << numWordsPerOpinion << " words indexed in each opinion. " << endl;
            vector<string> keyWords = dp.getKeyWords();
            vector<int> keyWordFrequencies = dp.getKeyWordFrequencies();
            sortByFrequency(keyWords, keyWordFrequencies);
            for (int i = 0; i < keyWords.size() && i < 50; i++)
            {
                cout << "#" << i+1  << " most frequent word was '" << keyWords[i] << "' and appeared " << keyWordFrequencies[i] <<  " times. " << endl;
            }
        }
        if (databaseMode != "STATS" && databaseMode != "QUERY" && databaseMode != "MAINTENANCE")
        {
            cout << "Database mode invalid, please try again." << endl;
        }
        databaseMode = "";
    }

    //dp.printTree();

}
