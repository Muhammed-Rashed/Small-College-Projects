// File: A1_T1_20230335.cpp
// Purpose: Split words, find binary numbers, find all possible binary numbers, find if numbers of bears equals 42, find if file is a phishing email
// Author: Mohamed Rashed Ali
// Section: Yet to be determined
// ID: 20230335
// TA: Yet to be determined
// Date: 8 Oct 2024



#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

// Colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"

using namespace std;

// This function will act as my main way of entering and exiting after and doing a task
int Pause()
{
    cout << "Do You wish to Continue, Return to the menu or Exit?" << endl;
    cout << BLUE << "A) Continue\n" << RESET;
    cout << MAGENTA << "B) Return to the menu\n" << RESET;
    cout << RED << "C) Exit\n" << RESET;
    cout << YELLOW << "Choice: " << RESET;

    string choice;
    cin >> choice;
    cin.ignore();

    // Input validation loop
    while (choice.length() != 1 ||
           (choice[0] != 'a' && choice[0] != 'A' &&
            choice[0] != 'b' && choice[0] != 'B' &&
            choice[0] != 'c' && choice[0] != 'C')) {
        cout << endl << RED << "Please choose from one of the options available" << RESET << endl;

        cout << BLUE << "A) Continue\n" << RESET;
        cout << MAGENTA << "B) Return to the menu\n" << RESET;
        cout << RED << "C) Exit\n" << RESET;
        cout << YELLOW << "Choice: " << RESET;

        cin >> choice;
        cin.ignore();
    }

    if (choice[0] == 'a' || choice[0] == 'A')
        return 0;
    else if (choice[0] == 'b' || choice[0] == 'B')
        return 2;
    else
        return 3;
}

// These are all the functions used for validating and error handling

// Used in problem 6a and 9
// This small function will be used in error handling by checking if what we entered is an int (It was a nice trick I learned)
        int validINT()
        {
            int num;
            while (true)
            {
                cin >> num;
                if (cin.fail())
                {
                    cout << RED << "Invalid input. Please enter a valid integer: " << RESET;
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


// Used for problem 6b
// To check if the string we entered is binary or not
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

// Used for problem 3
// Function to help split the words
vector<string> split(const string& target, const string& delimiter)
{
    vector<string> result;
    size_t start = 0;
    size_t end = target.find(delimiter);

    while (end != string::npos)
    {
        result.push_back(target.substr(start, end - start));
        start = end + delimiter.length();
        end = target.find(delimiter, start);
    }

    // Add the last substring after the last delimiter
    result.push_back(target.substr(start));

    return result;
}


// Used for problem 6a
// Function to find binary (IDK why you made us do this it was super easy, but I guess good practice)
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


// Used for problem 6b
// Function for getting the all the different binary cases
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


// Used for problem 9
// It's nice that the Professor made us use dynamic programing although this is a very simple one
// The function used for calculating the bears and checking
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
                cout << RED << "Could not open the file: "<< RESET << GREEN << fileName << RESET << endl;
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
    string input, delimiter;

    cout << GREEN <<"Enter a string: " << RESET;
    getline(cin, input);

    cout << GREEN <<"Enter a delimiter: " << RESET;
    getline(cin, delimiter);
    while (delimiter.length()>1)
    {
        cout << RED << "Please enter one character: "<< RESET;
        getline(cin, delimiter);
        cin.ignore();
    }

    vector<string> result = split(input, delimiter);

    cout << "Resulting split strings: ";
    for (size_t i = 0; i < result.size(); ++i)
    {
        cout << "\"" << result[i] << "\"";
        if (i < result.size() - 1)
            cout << ", ";
    }
    cout << endl;

    return 0;
}

int problem_6a()
{
    cout<< GREEN <<"Please enter the number you want: " << RESET << endl;
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
        cout << GREEN << "Please enter the binary number prefix: " << RESET;
        cin >> prefix;

        isValid = isBinary(prefix);

        if (!isValid)
            cout << RED << "Invalid input. Only 0 and 1 are allowed." << RESET << endl;

    } while (!isValid);

    cout << GREEN << "Please enter the number of digits for the suffix: " << RESET;
    cin >> k;

    numbers(prefix, k);
    cout<<endl;
    return 0;
}

int problem_9()
{
    cout << GREEN << "Please enter the number of bears: " << RESET;
    int n = validINT();

    if (bears(n))
        cout<<GREEN<<"Bears("<<n<<") is true"<<RESET<<endl;
    else
        cout<<GREEN<<"Bears("<<n<<") is false"<<RESET<<endl;
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
    cout << GREEN <<"Enter the name of the file to scan: " << RESET;
    cin >> fileName;

    scanFile(fileName, phishingTerms);

    return 0;
}


// The main menu
int main()
{
    cout << GREEN << "Welcome User to my Assignment" << RESET << endl;

    bool running = true;
    int lastChoice = -1;

    while (running) {
        if (lastChoice == -1)
        {
            // If it's the first run, show the menu
            cout << BLUE << "A) Separate by delimiter\n" << RESET;
            cout << BLUE << "B) One Binary Number\n" << RESET;
            cout << BLUE << "C) Many Binary Numbers\n" << RESET;
            cout << BLUE << "D) Teddy Bear Picnic\n" << RESET;
            cout << BLUE << "E) Phishing Scanner\n" << RESET;
            cout << YELLOW << "Choice: " << RESET;

            string choice;
            cin >> choice;
            cin.ignore();

            // For Error handling
            while (choice.length() != 1 ||
                   (choice[0] != 'a' && choice[0] != 'A' &&
                    choice[0] != 'b' && choice[0] != 'B' &&
                    choice[0] != 'c' && choice[0] != 'C' &&
                    choice[0] != 'd' && choice[0] != 'D' &&
                    choice[0] != 'e' && choice[0] != 'E')) {
                cout << endl << RED << "Please choose from one of the options available" << RESET << endl;

                cout << BLUE << "A) Separate by delimiter\n" << RESET;
                cout << BLUE << "B) One Binary Number\n" << RESET;
                cout << BLUE << "C) Many Binary Numbers\n" << RESET;
                cout << BLUE << "D) Teddy Bear Picnic\n" << RESET;
                cout << BLUE << "E) Phishing Scanner\n" << RESET;
                cout << YELLOW << "Choice: " << RESET;

                cin >> choice;
                cin.ignore();
            }

            // Store the last operation based on user choice
            if (choice[0] == 'a' || choice[0] == 'A')
            {
                lastChoice = 1;
                problem_3();
            }
            else if (choice[0] == 'b' || choice[0] == 'B')
            {
                lastChoice = 2;
                problem_6a();
            }
            else if (choice[0] == 'c' || choice[0] == 'C')
            {
                lastChoice = 3;
                problem_6b();
            }
            else if (choice[0] == 'd' || choice[0] == 'D')
            {
                lastChoice = 4;
                problem_9();
            }
            else if (choice[0] == 'e' || choice[0] == 'E')
            {
                lastChoice = 5;
                problem_12();
            }
        }
        else
        {
            // If a last choice exists, pause and retry the operation
            int action = Pause();
            if (action == 0)
            {
                switch (lastChoice)
                {
                    case 1: problem_3(); break;
                    case 2: problem_6a(); break;
                    case 3: problem_6b(); break;
                    case 4: problem_9(); break;
                    case 5: problem_12(); break;
                }
            }
            else if (action == 2)
            {
                lastChoice = -1;
                continue;
            }
            else if (action == 3)
                running = false;
        }
    }

    return 0;
}