#include "StringSet.h"
#include <iostream>

using namespace std;

void displayMenu() {
    cout << "\n=== StringSet Demo Application ===\n";
    cout << "1. Load two files and calculate similarity\n";
    cout << "2. Enter two strings and calculate similarity\n";
    cout << "3. Demo: Preloaded files\n";
    cout << "4. Exit\n";
    cout << "===================================\n";
    cout << "Enter your choice: ";
}

void demoOption() {
    // Predefined sample documents
    string demo1 = "Chocolate ice cream, chocolate milk, and chocolate bars are delicious! "
                   "Everyone loves chocolate. Ice cream is also a favorite treat. "
                   "Milk and bars are essential ingredients in many desserts. "
                   "Bars, ice, and milk are often enjoyed with chocolate.";

    string demo2 = "Chocolate cake is a classic dessert enjoyed worldwide. "
                   "Ice cream and milkshakes pair wonderfully with chocolate bars. "
                   "Everyone has a favorite dessert, often including chocolate or ice cream.";

    // Create StringSet objects for the demo documents
    StringSet doc1(demo1, true);
    StringSet doc2(demo2, true);

    // Display documents
    cout << "Demo Document 1: " << endl;
    doc1.display();
    cout << "\nDemo Document 2: " << endl;
    doc2.display();

    // Calculate union, intersection, and similarity
    StringSet unionSet = doc1 + doc2;
    StringSet intersectionSet = doc1 * doc2;
    double similarityScore = doc1.similarity(doc2);

    // Display results
    cout << "\nUnion of words:" << endl;
    unionSet.display();

    cout << "\nIntersection of words:" << endl;
    intersectionSet.display();

    cout << "\nSimilarity score: " << similarityScore << endl;
}

void loadFiles() {
    string filename1, filename2;
    cout << "Enter the path to the first file: ";
    cin >> filename1;
    cout << "Enter the path to the second file: ";
    cin >> filename2;

    StringSet doc1(filename1);
    StringSet doc2(filename2);

    cout << "\nUnique words in the first document:\n";
    doc1.display();
    cout << "\nUnique words in the second document:\n";
    doc2.display();

    StringSet unionSet = doc1 + doc2;
    StringSet intersectionSet = doc1 * doc2;

    cout << "\nUnion of the two documents:\n";
    unionSet.display();

    cout << "Intersection of the two documents:\n";
    intersectionSet.display();

    double similarityScore = doc1.similarity(doc2);
    cout << "\nSimilarity Score: " << similarityScore << endl;
}

void enterStrings() {
    cin.ignore(); // Clear the input buffer
    string str1, str2;
    cout << "Enter the first string: ";
    getline(cin, str1);
    cout << "Enter the second string: ";
    getline(cin, str2);

    StringSet doc1(str1, true);
    StringSet doc2(str2, true);

    cout << "\nUnique words in the first string:\n";
    doc1.display();
    cout << "\nUnique words in the second string:\n";
    doc2.display();

    StringSet unionSet = doc1 + doc2;
    StringSet intersectionSet = doc1 * doc2;

    cout << "\nUnion of the two strings:\n";
    unionSet.display();

    cout << "Intersection of the two strings:\n";
    intersectionSet.display();

    double similarityScore = doc1.similarity(doc2);
    cout << "\nSimilarity Score: " << similarityScore << endl;
}

void demoMode() {
    cout << "\n--- Demo Mode ---\n";
    StringSet doc1("demo_file1.txt"); // Preloaded file paths
    StringSet doc2("demo_file2.txt");

    cout << "Unique words in the first demo document:\n";
    doc1.display();
    cout << "Unique words in the second demo document:\n";
    doc2.display();

    StringSet unionSet = doc1 + doc2;
    StringSet intersectionSet = doc1 * doc2;

    cout << "\nUnion of the two demo documents:\n";
    unionSet.display();

    cout << "Intersection of the two demo documents:\n";
    intersectionSet.display();

    double similarityScore = doc1.similarity(doc2);
    cout << "\nSimilarity Score: " << similarityScore << endl;
}

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                loadFiles();
                break;
            case 2:
                enterStrings();
                break;
            case 3:
                demoOption();
                break;
            case 4:
                cout << "Exiting application. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
