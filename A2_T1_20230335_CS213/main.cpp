#include <iostream>
#include "StringSet.h"
using namespace std;

void displayMenu() {
    cout << "\nMenu Options:" << endl;
    cout << "1. Load documents from files" << endl;
    cout << "2. Load documents from strings" << endl;
    cout << "3. Display similarity between two documents" << endl;
    cout << "4. Add a word to a document" << endl;
    cout << "5. Remove a word from a document" << endl;
    cout << "6. Display union of two documents" << endl;
    cout << "7. Display intersection of two documents" << endl;
    cout << "8. Exit" << endl;
    cout << "Please choose an option: ";
}

void loadDocumentFromFile(StringSet& doc1, StringSet& doc2, const string& filename1, const string& filename2) {
    try {
        doc1 = StringSet(filename1); // Load the first document from a file
        cout << "Document 1 loaded from file: " << filename1 << endl;
        cout << "Document 1 words: ";
        doc1.display(); // Display loaded words for doc1

        doc2 = StringSet(filename2); // Load the second document from a file
        cout << "Document 2 loaded from file: " << filename2 << endl;
        cout << "Document 2 words: ";
        doc2.display(); // Display loaded words for doc2
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void loadDocumentFromString(StringSet& doc1, StringSet& doc2, const string& str1, const string& str2) {
    try {
        doc1 = StringSet(str1, true); // Load the first string into doc1
        cout << "Document 1 loaded from string." << endl;
        cout << "Document 1 words: ";
        doc1.display(); // Display loaded words for doc1

        doc2 = StringSet(str2, true); // Load the second string into doc2
        cout << "Document 2 loaded from string." << endl;
        cout << "Document 2 words: ";
        doc2.display(); // Display loaded words for doc2
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void showSimilarity(const StringSet& doc1, const StringSet& doc2) {
    try {
        double similarityScore = doc1.similarity(doc2);
        cout << "Similarity Score: " << similarityScore << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void showUnion(const StringSet& doc1, const StringSet& doc2) {
    StringSet unionSet = doc1 + doc2; // Get the union using the overloaded "+" operator
    cout << "Union of Document 1 and Document 2: ";
    unionSet.display();
}

void showIntersection(const StringSet& doc1, const StringSet& doc2) {
    StringSet intersectionSet = doc1 * doc2; // Get the intersection using the overloaded "*" operator
    cout << "Intersection of Document 1 and Document 2: ";
    intersectionSet.display();
}

int main() {
    StringSet doc1, doc2;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string filename1, filename2;
                cout << "Enter the filename for Document 1: ";
                cin >> filename1;
                cout << "Enter the filename for Document 2: ";
                cin >> filename2;
                loadDocumentFromFile(doc1, doc2, filename1, filename2);
                break;
            }
            case 2: {
                string inputString1, inputString2;
                cin.ignore(); // To ignore the leftover newline from previous input
                cout << "Enter the text for Document 1: ";
                getline(cin, inputString1);
                cout << "Enter the text for Document 2: ";
                getline(cin, inputString2);
                loadDocumentFromString(doc1, doc2, inputString1, inputString2);
                break;
            }
            case 3: {
                showSimilarity(doc1, doc2);
                break;
            }
            case 4: {
                string word;
                cout << "Enter a word to add to Document 1: ";
                cin >> word;
                doc1.add(word);
                cout << "Word added to Document 1: ";
                doc1.display();
                break;
            }
            case 5: {
                string word;
                cout << "Enter a word to remove from Document 1: ";
                cin >> word;
                doc1.remove(word);
                cout << "Word removed from Document 1: ";
                doc1.display();
                break;
            }
            case 6: {
                showUnion(doc1, doc2);
                break;
            }
            case 7: {
                showIntersection(doc1, doc2);
                break;
            }
            case 8:
                cout << "Exiting the program..." << endl;
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }

    return 0;
}
