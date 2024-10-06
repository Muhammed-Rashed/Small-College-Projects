// File: A1_T1_20230335.cpp
// Purpose: ………
// Author: Mohamed Rashed Ali
// Section: Yet to be determined
// ID: 20230335
// TA: Yet to be determined
// Date: 8 Oct 2024



#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;
// These are all the functions used for validating and error handling

// This small function will be used in error handling by checking if what we entered is an int (It was a nice trick I learned)
    // Used in problem 6a and 9
        int validINT()
        {
            int num;
            while (true)
            {
                cin >> num;
                if (cin.fail())
                {
                    cout << "Invalid input. Please enter a valid integer: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else
                {
                    cin.ignore(1000, '\n');
                    return num;
                }
            }
        }

// To check if the string we entered is binary or not
    // Used for problem 6b
        bool isBinary(const string& prefix)
        {
            for (char c : prefix)
            {
                if (c != '0' && c != '1')
                    return false;
            }
            return true;
        }

// This will have all the functions used for each problem

// Function to help find the delimiter by checking if it's not a number nor a word
    // Used for problem 3
        string findDelimiter(const string& target)
        {
            for (char c : target)
            {
                if (!isalnum(c))
                    return string(1, c);
            }
            return "";
        }

// Function to help split the words
        vector<string> split(const string& target)
        {
            string delimiter = findDelimiter(target);

            if (delimiter.empty())
                return { target };

            vector<string> result;
            int start = 0;
            int end = target.find(delimiter);

            while (end != -1)
            {
                result.push_back(target.substr(start, end - start));

                start = end + delimiter.length();

                end = target.find(delimiter, start);
            }

            result.push_back(target.substr(start));

            return result;
        }


// Function to find binary (IDK why you made us do this it was super easy, but I guess good practice)
    // Used for problem 6a
        static void binaryPrint(int n)
        {
            // The test case as told in the pdf
            if (n == 0)
            {
                cout << 0;
                return;
            }

            // The recursion part
            if (n > 1)
                binaryPrint(n / 2);

            cout << (n % 2);
        }



// Function for getting the all the different binary cases
    // Used for problem 6b
        void numbers(string prefix, int k)
        {
            if (k == 0)
                cout << prefix << endl;

            else
            {
                numbers(prefix + "0", k - 1);
                numbers(prefix + "1", k - 1);
            }
        }


// It's nice that the Professor made us use dynamic programing although this is a very simple one
// The function used for calculating the bears and checking
    // Used for problem 9
        static bool bears(int n)
        {
            // Check if its 42
            if (n == 42)
                return true;

            // Check if it's less than 42
            if (n < 42)
                return false;

            // Checking while at the same time using the first rule
            if (n % 2 == 0 && bears(n / 2))
                return true;

            // Checking while at the same time using the 2nd rule
            if (n % 3 == 0 || n % 4 == 0)
            {
                int lastDigit = n % 10;
                int secondLastDigit = (n % 100) / 10;
                int product = lastDigit * secondLastDigit;

                if (product > 0 && bears(n - product))
                    return true;
            }

            // Same like the above if conditions
            if (n % 5 == 0 && bears(n - 42))
                return true;


            // If none of these work then simply false
            return false;
        }


// Function to convert a string to lowercase
// (Because some files will have capital letters that the code wouldn't be able to read)
    // Used for problem 12 (He just had to make us suffer now did he?)
        string toLowerCase(const string& str)
        {
            string result = str;
            transform(result.begin(), result.end(), result.begin(), ::tolower);
            return result;
        }

        // Structure to hold the term and its associated point value
        struct PhishingTerm {
            string term;
            int pointValue;
        };

// Function to scan the file for phishing terms and calculate the phishing score (Most of the work)
        void scanFile(const string& fileName, const vector<PhishingTerm>& terms)
        {
            ifstream file(fileName);

            // Simple error message
            if (!file.is_open())
            {
                cerr << "Could not open the file: " << fileName << endl;
                return;
            }

            // Array to hold the occurrence count of each phishing term
            vector<int> occurrences(terms.size(), 0);
            int totalScore = 0;

            string line;
            while (getline(file, line))
            {
                // Convert the line to lowercase
                string lowerLine = toLowerCase(line);

                for (size_t i = 0; i < terms.size(); ++i)
                {
                    size_t pos = lowerLine.find(terms[i].term);
                    while (pos != string::npos) {
                        occurrences[i]++;
                        totalScore += terms[i].pointValue;
                        pos = lowerLine.find(terms[i].term, pos + terms[i].term.size());
                    }
                }
            }

            file.close();

            // Output the results
            cout << "Phishing Scan Results:\n";
            for (size_t i = 0; i < terms.size(); ++i)
            {
                if (occurrences[i] > 0)
                {
                    cout << "Term: " << terms[i].term << ", Occurrences: " << occurrences[i]
                         << ", Points: " << occurrences[i] * terms[i].pointValue << endl;
                }
            }
            cout << "Total Phishing Score: " << totalScore << endl;
        }


// These functions will be used for our inputs and outputs
int problem_3()
{
    cout<<"Please Enter anything: "<<endl;
    string word;
    getline(cin, word);

    vector<string> result = split(word);

    // This is here just to make sure that the comma used is printed correctly
    bool first = true;

    // The loop used to print the output
    for (auto& part : result)
    {
        string newWord = "";


        for (char c : part)
        {
            if (isalnum(c))
                newWord += c;
        }

        if (!newWord.empty())
        {
            if (!first)
                cout << ",";

            cout << "\"" << newWord << "\"";

            first = false;
        }
    }

    cout << endl;
    return 0;
}

int problem_6a()
{
    cout<<"Please enter the number you want"<<endl;
    int num = validINT();
    binaryPrint(num);
    return 0;
}

int problem_6b()
{
    int k;
    string prefix;
    bool isValid;

    do
    {
        cout << "Please enter the binary number prefix: ";
        cin >> prefix;

        isValid = isBinary(prefix);

        if (!isValid)
            cout << "Invalid input. Only 0 and 1 are allowed." << endl;

    } while (!isValid);

    cout << "Please enter the number of digits for the suffix: ";
    cin >> k;

    numbers(prefix, k);
    return 0;
}

int problem_9()
{
    cout<<"Please enter the number of bears: ";
    int n = validINT();

    if (bears(n))
        cout<<"Bears("<<n<<") is true"<<endl;
    else
        cout<<"Bears("<<n<<") is false"<<endl;
    return 0;
}

// This one is slightly different with the list inside since no need to put in a function of its own
int problem_12()
{
    // List of common phishing terms and their point values
    vector<PhishingTerm> phishingTerms = {

            // Words used a lot of the time

            {"password", 3},
            {"credit card", 3},
            {"social security", 3},
            {"account", 2},
            {"bank", 3},
            {"security", 2},
            {"virus", 2},

            // Action

            {"verify", 2},
            {"login", 2},
            {"urgent", 3},
            {"click here", 2},
            {"secure", 1},
            {"update", 2},

            // Urgency

            {"limited time", 2},
            {"offer", 1},
            {"action required", 2},
            {"immediately", 2},
            {"confidential", 3},
            {"billing", 3},
            {"alert", 2},
            {"dear customer", 1},
            {"congratulations", 1},

            // Company names

            {"paypal", 3},
            {"ebay", 2},
            {"amazon", 2},
            {"apple", 2},
            {"microsoft", 2},
            {"chase", 3},
            {"huawei", 3},
            {"citibank", 3},
    };

    string fileName;
    cout << "Enter the name of the file to scan: ";
    cin >> fileName;

    scanFile(fileName, phishingTerms);

    return 0;
}


// The main menu
int main()
{
    cout << "Welcome User to my Assignment" << endl;
    cout << "A)Separate by delimiter\nB)One Binary Number\nC)Many Binary Numbers\nD)Teddy Bear Picnic\nE)Phishing Scanner\nChoice: ";
    char choice;
    cin>>choice;

    cin.ignore();

    // Loop to make sure nothing wrong happens
    while (choice !='a' and choice != 'A' and choice != 'b' and choice != 'B' and choice != 'c' and choice != 'C' and choice != 'd' and choice != 'D' and choice != 'e' and choice != 'E')
    {
        cout<<"Please chose from one of the options available"<<endl;
        cout << "A)Separate by delimiter\nB)One Binary Number\nC)Many Binary Numbers\nD)Teddy Bear Picnic\nE)Phishing Scanner\nChoice: ";
        cin >> choice;
        cin.ignore();
    }
    if (choice == 'a' || choice == 'A')
        problem_3();
    else if(choice == 'b' || choice == 'B')
        problem_6a();
    else if(choice == 'c' || choice == 'C')
        problem_6b();
    else if (choice == 'd' || choice == 'D')
        problem_9();
    else if (choice == 'e' || choice == 'E')
        problem_12();

    return 0;
}
