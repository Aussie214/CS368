////////////////////////////////////////////////////////////////////////////////
// File Name:      a2.cpp
//
// Author:         Gerald, Austin Wilson
// CS email:       gerald@cs.wisc.edu, awilson34@wisc.edu
//
// Description:    The source file for a2.
//
// IMPORTANT NOTE: THIS IS THE ONLY FILE THAT YOU SHOULD MODIFY FOR A2.
//                 You SHOULD NOT MODIFY any of the following:
//                   1. Name of the functions/methods.
//                   2. The number and type of parameters of the functions.
//                   3. Return type of the functions.
////////////////////////////////////////////////////////////////////////////////

#include "a2.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <regex>



using namespace std;

//Clean the input file by calling helper methods and store the result in outFile
void cleanData(std::ifstream &inFile, std::ofstream &outFile,
               std::unordered_set<std::string> &stopwords) {
    // TODO: Implement this method.
    // # of lines of code in Gerald's implementation: 13
    // Do the following operations on each review before
    // storing it to the output file:
    //   1. Replace hyphens with spaces.
    //   2. Split the line of text into individual words.
    //   3. Remove the punctuation marks from the words.
    //   5. Remove the short (1 or 0 letter) words. You should NOT remove
    //      numbers in this step because if you do so, you'll lose the ratings.
    //   7. Remove stopwords.
    
    string line;
    vector<string> inTokens;
    vector<string> outTokens;
    while (getline(inFile, line)) {
      inTokens.clear();
      outTokens.clear();
      //Replace hyphens with spaces
      //Appears to be working
      replaceHyphensWithSpaces(line);
      //Split line into words
      splitLine(line, inTokens);
      //Remove punctuation
      removePunctuation(inTokens, outTokens);
      //Remove short words
      removeShortWords(outTokens);
      //Remove stop words
      removeStopWords(outTokens, stopwords);
      //print outTokens to file
      for (auto& r : outTokens) {
        if ( !r.empty() && r[r.size() - 1] == '\r' ) {
          r.erase(r.size() - 1);
        }
      }
      //Remove empty strings or spaces
      for (vector<string>::iterator it = outTokens.begin(); it != outTokens.end(); it++) {
        string temp = *it;
        if ( !(temp.empty() || temp == " ") ) {
          outFile << *it << ' ';
        }
      }     
      outFile << endl;
    }
    outFile.close();
}

//Take input file and store in dictionary
void fillDictionary(std::ifstream &newInFile,
                    std::unordered_map<std::string, std::pair<long, long>> &dict) {
    string line;
    while (getline(newInFile, line)) {
      //Edit each incoming line
      vector<string> tokens;
      string temp;
      stringstream stream1(line);
      while (getline(stream1, temp, ' ')) {
        tokens.push_back(temp);  
      }
      string s_rating;
      string::size_type size;
      long rating;
      if (!tokens.empty()) {
        s_rating = tokens.front();
        rating = stol(s_rating, &size);
      }
      //Map
      for (vector<string>::iterator it = tokens.begin()++; it != tokens.end(); ++it) {
        //string is not in map
        string dig = *it;
        if (!dig.empty() && dig != "\n" && dig != "\r" && !isdigit(dig[0]) && dict.find(*it) == dict.end()) {
          //insert string into map
          pair<string, pair<long, long>> data;
          data.first = *it;
          data.second.first = rating;
          data.second.second = 1L;
          dict.insert( data );
        }
        //string is in map
        else {
          if ( !isdigit(dig[0]) && dig != "\n" && dig != "\r" && !dig.empty()) {
            unordered_map<string, pair<long, long>>::iterator index = dict.find(*it);
            long total_rating = index->second.first;
            total_rating = total_rating + rating;
            long total_num = index->second.second;
            total_num++;
            index->second.first = total_rating;
            index->second.second = total_num;
          }
        }
      }
    }
}

//put line from inFile into stop words set
void fillStopWords(std::ifstream &inFile,
                   std::unordered_set<std::string> &stopwords) {
    string line;
    while (getline(inFile, line)) {
      if ( !line.empty() && line[line.size() - 1] == '\r' ) {
        line.erase(line.size() - 1);
      }
      stopwords.insert(line);
    }
}

//Given dictionary map and input file of raw reviews, predict a score for the review
void scoreReviews(std::ifstream &testFile,
                 std::unordered_map<std::string, std::pair<long, long>> &dict,
                 std::ofstream &ratingsFile) {

    string line;
    vector<string> tokens;
    while (getline(testFile, line)) {
      tokens.clear();
      splitLine(line, tokens);
      for (auto& e : tokens) {
      }
      //works above this line
      long total_rating = 0;
      long num_vists = 0;
      double final;
      int no_words = 1;
      for ( auto it = tokens.begin(); it != tokens.end(); it++ ) {
        no_words = 0;
        num_vists++;
        //Found in dictionary
        if ( dict.find(*it) != dict.end() ) {
          unordered_map<string, pair<long, long>>::iterator index = dict.find(*it);
          long local_total = index->second.first;
          long local_vists = index->second.second;
          double local_avg = (local_total + 0.0) / (local_vists + 0.0);
          total_rating += local_avg;
        }
        //Not found in dictionary
        else {
          total_rating += 2;
        }
      }
      if (no_words) {
        final = 2;
      }
      else {
        final = (total_rating + 0.0) / (num_vists + 0.0);
      }
      //print to file
      ratingsFile << final << ' ';
      for ( auto itr = tokens.begin(); itr != tokens.end(); itr++ ) {
        ratingsFile << *itr << ' ';
      }
      ratingsFile << endl;
    }
      ratingsFile.close();
}

//Keep only digits and alphabetic characters
void removePunctuation(std::vector<std::string> &inTokens,
                       std::vector<std::string> &outTokens) {

    for (auto& s : inTokens) {
      string str = "";
      for (char c : s) {
        if (!ispunct(c, locale("en_US.UTF-8"))) {
          str = str + c;
        }
      }
      outTokens.push_back(str);
    }
}

//Remove short words, under 2 in length that are not numbers
void removeShortWords(std::vector<std::string> &tokens) {
    for (int i = 0; i < tokens.size(); i++) {
      string str = tokens.at(i);
      if ( str.length() <= 1 && !all_of(str.begin(), str.end(), ::isdigit) ) {
        tokens.erase(tokens.begin() + i);
      }
    }
}

//Remove words that match a string from the stopwords set
void removeStopWords(std::vector<std::string> &tokens,
                     std::unordered_set<std::string> &stopwords) {
                     
    for (int i = 0; i < tokens.size(); i++) {
      string str = tokens.at(i);
      if (stopwords.find(str) != stopwords.end()) {
        tokens.erase(tokens.begin() + i);
        i--;
      }
    }
}

//Replace all hypens with a space char
void replaceHyphensWithSpaces(std::string &line) {    
     for (int i = 0; i < line.length(); i++) {
       if (line[i] == '-') {
         line[i] = ' ';
       }
     }
}

//Given an input line as a string, splits the string into tokens 
//storing them in words
void splitLine(std::string &line, std::vector<std::string> &words) {
    stringstream s1(line);
    string token;
    while (getline(s1, token, ' ')) {
      words.push_back(token);
    }
}
