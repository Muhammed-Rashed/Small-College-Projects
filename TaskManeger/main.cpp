// Name: Mohamed Rashed Ali
// ID: 20230335
// File: main.cpp
// Subject: OOP
// Purpose: Task Manager Implementation

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <fstream>

using namespace std;

// Colors because why not?
#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define BLUE        "\033[34m"
#define CYAN        "\033[36m"

// Represents a single process
class Process {
public:
    string imageName;       // Name of the executable image
    int pid;                // Process ID
    string sessionName;     // Name of the session running the process
    int sessionNumber;      // Session number
    string memoryUsageStr;

    // Constructor to initialize process details
    Process(string imageName, int pid, string sessionName, int sessionNumber, string memoryUsageStr)
            : imageName(move(imageName)), pid(pid), sessionName(move(sessionName)), sessionNumber(sessionNumber), memoryUsageStr(move(memoryUsageStr)) {}

    // Function to clean the memory string, remove commas, and convert it to an integer
    int getMemoryUsageKB() {
        string cleanMemory = memoryUsageStr;
        cleanMemory.erase(remove(cleanMemory.begin(), cleanMemory.end(), ','), cleanMemory.end());
        if (cleanMemory.empty() || !all_of(cleanMemory.begin(), cleanMemory.end(), ::isdigit)) {
            return 0;
        }
        return stoi(cleanMemory);
    }



    // Function to display process details
    void display() {
        cout << setw(35) << left << imageName
             << setw(20) << pid
             << setw(25) << sessionName
             << setw(15) << sessionNumber
             << setw(20) << getMemoryUsageKB() << " K" << endl; // Display memory usage as integer
    }

};

// Manages a list of processes and provides operations on them
class ProcessList {
private:
    vector<Process> processes; // Stores the list of processes

public:
    void fillProcesses() {
        // Run tasklist and redirect output to a temporary file
        system("tasklist /fo csv /nh > tasklist.txt");

        ifstream file("tasklist.txt");
        if (!file.is_open()) {
            cerr << RED << "Failed to open tasklist.txt." << RESET << endl;
            return;
        }

        string line;

        while (getline(file, line)) {
            try {
                // Remove quotes and parse the CSV line
                line.erase(remove(line.begin(), line.end(), '\"'), line.end()); // Remove quotes
                stringstream ss(line);
                string imageName, pidStr, sessionName, sessionNumStr, memoryUsageStr;

                // Read each comma-separated value
                getline(ss, imageName, ',');
                getline(ss, pidStr, ',');
                getline(ss, sessionName, ',');
                getline(ss, sessionNumStr, ',');
                getline(ss, memoryUsageStr, ',');

                // Parse the numeric values
                int pid = stoi(pidStr);
                int sessionNumber = stoi(sessionNumStr);

                // Add the process to the list
                processes.emplace_back(imageName, pid, sessionName, sessionNumber, memoryUsageStr);
            } catch (const exception& e) {
                cerr << RED << "Error parsing line: " << line << RESET << endl;
                cerr << RED << "Reason: " << e.what() << RESET << endl;
                continue; // Skip invalid lines
            }
        }

        file.close();

        // Optional: Clean up the temporary file
        remove("tasklist.txt");
    }


    // Displays the list of processes in a tabular format
    void displayProcesses() {
        cout << BLUE;
        cout << setw(35) << left << "Image Name"
             << setw(20) << "PID"
             << setw(25) << "Session Name"
             << setw(15) << "Session#"
             << setw(20) << "Mem Usage" << endl;
        cout << string(115, '=') << endl;
        cout << RESET;
        for (auto& process : processes) { // Removed `const` from auto&
            process.display();
        }
    }


    // Sorting functions
    void sortByName() {
        sort(processes.begin(), processes.end(),
             [](Process& a, Process& b) { // Removed `const`
                 string nameA = a.imageName;
                 string nameB = b.imageName;
                 transform(nameA.begin(), nameA.end(), nameA.begin(), ::tolower);
                 transform(nameB.begin(), nameB.end(), nameB.begin(), ::tolower);
                 return nameA < nameB;
             });
    }

    void sortByPID() {
        sort(processes.begin(), processes.end(),
             [](Process& a, Process& b) { return a.pid < b.pid; }); // Removed `const`
    }

    void sortByMemoryUsage() {
        sort(processes.begin(), processes.end(),
             [](Process& a, Process& b) { return a.getMemoryUsageKB() > b.getMemoryUsageKB(); }); // Removed `const`
    }

    void sortBySessionName() {
        sort(processes.begin(), processes.end(),
             [](Process& a, Process& b) { return a.sessionName < b.sessionName; }); // Removed `const`
    }

    void sortBySessionNumber() {
        sort(processes.begin(), processes.end(),
             [](Process& a, Process& b) { return a.sessionNumber < b.sessionNumber; }); // Removed `const`
    }

};

// Displays the menu of sorting options
void showMenu() {
    cout << CYAN;
    cout << "\nChoose an option to sort the processes:\n";
    cout << "1. Sort by Image Name\n";
    cout << "2. Sort by PID\n";
    cout << "3. Sort by Memory Usage\n";
    cout << "4. Sort by Session Name\n";
    cout << "5. Sort by Session Number\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
    cout << RESET;
}

int main() {
    ProcessList processList;

    try {
        processList.fillProcesses();

        int choice;
        do {
            showMenu(); // Display the menu
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << RED << "Invalid input. Please enter a number.\n" << RESET;
                continue;
            }

            switch (choice) {
                case 1:
                    processList.sortByName();
                    cout << GREEN << "\nProcesses sorted by Image Name:\n" << RESET;
                    processList.displayProcesses();
                    break;
                case 2:
                    processList.sortByPID();
                    cout << GREEN << "\nProcesses sorted by PID:\n" << RESET;
                    processList.displayProcesses();
                    break;
                case 3:
                    processList.sortByMemoryUsage();
                    cout << GREEN << "\nProcesses sorted by Memory Usage:\n" << RESET;
                    processList.displayProcesses();
                    break;
                case 4:
                    processList.sortBySessionName();
                    cout << GREEN << "\nProcesses sorted by Session Name:\n" << RESET;
                    processList.displayProcesses();
                    break;
                case 5:
                    processList.sortBySessionNumber();
                    cout << GREEN << "\nProcesses sorted by Session Number:\n" << RESET;
                    processList.displayProcesses();
                    break;
                case 6:
                    cout << GREEN << "Exiting program.\n" << RESET;
                    break;
                default:
                    cout << RED << "Invalid choice. Please try again.\n" << RESET;
            }

        } while (choice != 6);

    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}
