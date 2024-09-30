// File: A1_T1_20230335.cpp
// Purpose: .........
// Author: Mohamed Rashed Ali
// Section: .....................
// ID: 20230335
// TA: ...................
// Date: 8 Oct 2024
// Detailed explanation of the file and how program works

#include <iostream>
#include <vector>

using namespace std;

string findDelimiter(const string& target)
{
    for (char c : target)
    {
        // Check if the character is non-alphanumeric
        if (!isalnum(c))
            // Return the first non-alphanumeric character as a string
            return string(1, c);
    }
    return "";  // Return an empty string if no delimiter is found
}

// Function to split the string based on the found delimiter
vector<string> split(const string& target)
{
    // Automatically detect the delimiter
    string delimiter = findDelimiter(target);

    if (delimiter.empty())
        // If no delimiter is found, return the entire string as a single element
        return { target };

    vector<string> result;
    int start = 0;
    int end = target.find(delimiter);

    while (end != -1)
    {
        // Extract the substring and add to the result
        result.push_back(target.substr(start, end - start));

        // Move start position after the delimiter
        start = end + delimiter.length();

        // Find the next delimiter
        end = target.find(delimiter, start);
    }

    // Add the last part of the string
    result.push_back(target.substr(start));

    return result;
}

int main()
{
    string word;
    getline(cin,word);

    vector<string> result = split(word);

    bool first = true;

    // Directly clean and print each word in the main loop
    for (auto& part : result)
    {
        // This will hold the cleaned word
        string newWord = "";

        // Clean the current word by keeping only alphanumeric characters
        for (char c : part)
        {
            // Check if character is alphanumeric
            if (isalnum(c))
                // Add it to cleanedWord if valid
                newWord += c;
        }

        // Only print if the cleaned word is not empty
        if (!newWord.empty())
        {
            if (!first)
                // Add a comma between words, but not before the first one
                cout << ",";

            cout << "\"" << newWord << "\"";

            // Update flag to handle commas correctly
            first = false;
        }
    }

    cout << endl;
}
