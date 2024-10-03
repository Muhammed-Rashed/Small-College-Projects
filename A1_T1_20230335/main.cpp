#include <iostream>
#include <vector>

using namespace std;

// Problem 3
string findDelimiter(const string& target)
{
    for (char c : target)
    {
        if (!isalnum(c))
            return string(1, c);
    }
    return "";
}

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

int problem_3()
{
    cout<<"Please Enter anything: "<<endl;
    string word;
    getline(cin, word);

    vector<string> result = split(word);

    bool first = true;

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



// Problem 6a
static void binaryPrint(int n)
{
    if (n == 0)
    {
        cout << 0;
        return;
    }

    if (n > 1)
        binaryPrint(n / 2);

    cout << (n % 2);
}

int problem_6a()
{
    cout<<"Please enter the number you want"<<endl;
    int num; cin>>num;
    binaryPrint(num);
    return 0;
}

// problem 6b
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

int problem_6b()
{
    int k;
    string prefix;

    cout << "Please enter the binary number prefix: ";
    cin >> prefix;

    cout << "Please enter the number of digits for the suffix: ";
    cin >> k;

    numbers(prefix, k);
    return 0;
}


// Problem 9
static bool bears(int n)
{
    if (n == 42)
        return true;

    if (n < 42)
        return false;

    if (n % 2 == 0 && bears(n / 2))
        return true;


    if (n % 3 == 0 || n % 4 == 0)
    {
        int lastDigit = n % 10;
        int secondLastDigit = (n % 100) / 10;
        int product = lastDigit * secondLastDigit;

        if (product > 0 && bears(n - product))
            return true;
    }

    if (n % 5 == 0 && bears(n - 42))
        return true;

    return false;

}

int problem_9()
{
    int n;
    cout<<"Please enter the number of bears: ";
    cin>>n;

    if (bears(n))
        cout<<"Bears("<<n<<") is true"<<endl;
    else
        cout<<"Bears("<<n<<") is false"<<endl;
    return 0;
}


int main()
{
    cout << "Welcome User to my Assignment" << endl;
    cout << "A)Separate by delimiter\nB)One Binary Number\nC)Many Binary Numbers\nD)Teddy Bear Picnic\nE)Phishing Scanner\nChoice: ";
    char choice;
    cin>>choice;

    cin.ignore();
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


    return 0;
}
