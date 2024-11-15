#include "StringSet.h"

// Helper function to tokenize input and remove punctuation
vector<string> StringSet::tokenize(const string& str)
{
    vector<string> tokens;
    stringstream ss(str);
    string word;

    // a loop to remove punctuation and make lowercase
    while (ss >> word)
    {

        string cleanWord;
        for (char ch : word)
        {
            if (!ispunct(ch))
                cleanWord += tolower(ch);
        }
        if (!cleanWord.empty() && !contains(cleanWord))
            tokens.push_back(cleanWord);
    }
    return tokens;
}

// Helper function to check if the vector contains a word
bool StringSet::contains(const string& word) const
{
    return find(words.begin(), words.end(), word) != words.end();
}

// Constructor to load words from a file
StringSet::StringSet(const string& filename)
{
    ifstream file(filename);
    string line;

    // And if else statement to check if the file opened
    if (file.is_open())
    {
        cout << "File opened successfully!" << endl;
        while (getline(file, line))
        {
            auto tokens = tokenize(line);
            for (const auto& token : tokens)
                add(token);
        }
        file.close();
    }
    else
        cout << "Error opening file!" << endl;
}

// Constructor to load words from a string
StringSet::StringSet(const string& inputString, bool fromString) {
    words = tokenize(inputString);
}

// Add a word to the set
void StringSet::add(const string& word)
{
    if (!contains(word))
        words.push_back(word);
}

// Remove a word from the set
void StringSet::remove(const string& word)
{
    auto it = find(words.begin(), words.end(), word);
    if (it != words.end())
        words.erase(it);
}

// Clear all words in the set
void StringSet::clear() {
    words.clear();
}

// Return the number of words in the set
int StringSet::size() const {
    return words.size();
}

// Display all words in the set
void StringSet::display() const
{
    for (const auto& word : words)
        cout << word << " ";

    cout << endl;
}

// Overload + operator for union of two sets
StringSet StringSet::operator+(const StringSet& other) const {
    StringSet result;
    result.words = words; // Start with a copy of the first set

    for (const auto& word : other.words)
    {
        if (!result.contains(word))
            result.words.push_back(word);
    }
    return result;
}

// Overload * operator for intersection of two sets
StringSet StringSet::operator*(const StringSet& other) const
{
    StringSet result;

    for (const auto& word : words)
    {
        if (other.contains(word))
            result.words.push_back(word);
    }
    return result;
}

// Similarity calculation using binary cosine coefficient
double StringSet::similarity(const StringSet& other) const
{
    int intersectionSize = (*this * other).size();
    int thisSize = size();
    int otherSize = other.size();

    // Check if either size is zero to prevent division by zero
    if (thisSize == 0 || otherSize == 0)
        return 0.0; // If one of the sets is empty, similarity is 0

    double sim = static_cast<double>(intersectionSize) / (sqrt(thisSize) * sqrt(otherSize));
    return sim;
}
