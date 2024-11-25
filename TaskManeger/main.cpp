#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <stdexcept>

using namespace std;

class Process {
public:
    string imageName;
    int pid;
    string sessionName;
    int sessionNumber;
    int memoryUsageKB; // Memory in KB

    Process(string imageName, int pid, string sessionName, int sessionNumber, int memoryUsageKB)
            : imageName(move(imageName)), pid(pid), sessionName(move(sessionName)), sessionNumber(sessionNumber), memoryUsageKB(memoryUsageKB) {}

    void display() const {
        cout << setw(35) << left << imageName   // Increased from 30 to 35
             << setw(20) << pid                // Increased from 15 to 20
             << setw(25) << sessionName        // Increased from 20 to 25
             << setw(15) << sessionNumber      // Increased from 10 to 15
             << setw(20) << memoryUsageKB << " K" << endl; // Increased from 15 to 20
    }
};

class ProcessList {
private:
    vector<Process> processes;

    string executeTasklist() {
        string result;
        char buffer[128];
        FILE* pipe = _popen("tasklist /fo csv /nh", "r"); // Run "tasklist" in CSV format
        if (!pipe) {
            throw runtime_error("Failed to execute tasklist command.");
        }
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }
        _pclose(pipe);
        return result;
    }

    void parseTasklistOutput(const string& output) {
        istringstream stream(output);
        string line;

        while (getline(stream, line)) {
            // Parse CSV line: "Image Name","PID","Session Name","Session#","Memory Usage"
            line.erase(remove(line.begin(), line.end(), '\"'), line.end()); // Remove quotes
            istringstream lineStream(line);

            string imageName, pidStr, sessionName, sessionNumStr, memoryStr;
            getline(lineStream, imageName, ',');
            getline(lineStream, pidStr, ',');
            getline(lineStream, sessionName, ',');
            getline(lineStream, sessionNumStr, ',');
            getline(lineStream, memoryStr, ',');

            try {
                int pid = stoi(pidStr);
                int sessionNumber = stoi(sessionNumStr);
                memoryStr.erase(remove(memoryStr.begin(), memoryStr.end(), ','), memoryStr.end()); // Remove commas in memory
                int memoryUsageKB = stoi(memoryStr);

                processes.emplace_back(imageName, pid, sessionName, sessionNumber, memoryUsageKB);
            } catch (...) {
                // Skip invalid or corrupt lines
                continue;
            }
        }
    }

public:
    void loadProcesses() {
        processes.clear();
        string output = executeTasklist();
        parseTasklistOutput(output);
    }

    void displayProcesses() const {
        cout << setw(35) << left << "Image Name"          // Increased from 30 to 35
             << setw(20) << "PID"                       // Increased from 15 to 20
             << setw(25) << "Session Name"             // Increased from 20 to 25
             << setw(15) << "Session#"                 // Increased from 10 to 15
             << setw(20) << "Mem Usage" << endl;       // Increased from 15 to 20
        cout << string(115, '=') << endl;               // Increased separator width to match column size
        for (const auto& process : processes) {
            process.display();
        }
    }

    void sortByName() {
        sort(processes.begin(), processes.end(),
             [](const Process& a, const Process& b) { return a.imageName < b.imageName; });
    }

    void sortByPID() {
        sort(processes.begin(), processes.end(),
             [](const Process& a, const Process& b) { return a.pid < b.pid; });
    }

    void sortByMemoryUsage() {
        sort(processes.begin(), processes.end(),
             [](const Process& a, const Process& b) { return a.memoryUsageKB > b.memoryUsageKB; });
    }
};

void showMenu() {
    cout << "\nChoose an option to sort the processes:\n";
    cout << "1. Sort by Image Name\n";
    cout << "2. Sort by PID\n";
    cout << "3. Sort by Memory Usage\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    ProcessList processList;

    try {
        processList.loadProcesses();

        int choice;
        do {
            showMenu();
            cin >> choice;

            switch (choice) {
                case 1:
                    processList.sortByName();
                    cout << "\nProcesses sorted by Image Name:\n";
                    processList.displayProcesses();
                    break;
                case 2:
                    processList.sortByPID();
                    cout << "\nProcesses sorted by PID:\n";
                    processList.displayProcesses();
                    break;
                case 3:
                    processList.sortByMemoryUsage();
                    cout << "\nProcesses sorted by Memory Usage:\n";
                    processList.displayProcesses();
                    break;
                case 4:
                    cout << "Exiting program.\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }

        } while (choice != 4);

    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}
