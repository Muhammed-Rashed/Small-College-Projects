#ifndef STRINGSET_H
#define STRINGSET_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace std;

class StringSet {
private:
    vector<string> words;

    // Helper function to clean and tokenize input string
    vector<string> tokenize(const string& str);

    // Helper function to check if a word exists in the vector
    bool contains(const string& word) const;

public:
    // Default constructor for creating an empty set
    StringSet() = default;

    // Constructor to load words from a file
    StringSet(const string& filename);

    // Constructor to load words from a string
    StringSet(const string& inputString, bool fromString);

    // Add a word to the set (only if it's not already present)
    void add(const string& word);

    // Remove a word from the set
    void remove(const string& word);

    // Clear all words in the set
    void clear();

    // Return the number of words in the set
    int size() const;

    // Display all words in the set
    void display() const;

    // Overload + operator for union
    StringSet operator+(const StringSet& other) const;

    // Overload * operator for intersection
    StringSet operator*(const StringSet& other) const;

    // Similarity calculation
    double similarity(const StringSet& other) const;
};

#endif
