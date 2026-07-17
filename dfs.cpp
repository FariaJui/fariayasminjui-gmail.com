// Standard header files for input/output, file handling, containers, and string stream
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;


// Evidence Class
// Stores information about a digital evidence file

class Evidence {
private:
    // Private data members (Encapsulation)
    string fileName;
    string filePath;
    string hashValue;
    long fileSize;

public:
    // Constructor: Initializes evidence information
    Evidence(string name, string path) {
        fileName = name;
        filePath = path;

        // Calculate file size automatically
        fileSize = getFileSize();

        // Generate hash value automatically
        hashValue = generateHash();
    }

    // Returns the size of the file in bytes
    long getFileSize() {
        // Open the file in binary mode and move to the end
        ifstream file(filePath, ios::binary | ios::ate);

        // Return 0 if the file cannot be opened
        if (!file)
            return 0;

        // Return the file size
        return file.tellg();
    }

    // Generates a simple hash value for file integrity checking
    string generateHash() {

        // Open the file in binary mode
        ifstream file(filePath, ios::binary);

        // Return an error if the file cannot be opened
        if (!file)
            return "FILE_ERROR";

        unsigned long hash = 0;
        char ch;

        // Read the file character by character
        while (file.get(ch)) {

            // Simple hash calculation
            hash = ((hash << 5) + hash) + ch;
        }

        // Convert hash value into hexadecimal format
        stringstream ss;
        ss << hex << hash;

        return ss.str();
    }

    // Displays all information about the evidence
    void displayEvidence() const {
        cout << "\nFile Name : " << fileName;
        cout << "\nFile Path : " << filePath;
        cout << "\nFile Size : " << fileSize << " bytes";
        cout << "\nHash      : " << hashValue << endl;
    }

    // Returns the evidence file name
    string getName() const {
        return fileName;
    }

    // Returns the generated hash value
    string getHash() const {
        return hashValue;
    }
};


// Digital Forensic System Class
// Manages evidence collection and forensic operations

class DigitalForensicSystem {
private:

    // Stores all collected evidence
    vector<Evidence> evidenceList;

    // Stores the chain of custody status
    map<string, string> custodyLog;

public:

    // Adds a new evidence file
    void addEvidence() {

        string name, path;

        // Get evidence information from the user
        cout << "Enter Evidence Name: ";
        getline(cin, name);

        cout << "Enter File Path: ";
        getline(cin, path);

        // Create a new evidence object
        Evidence ev(name, path);

        // Store the evidence in the vector
        evidenceList.push_back(ev);

        // Set the initial custody status
        custodyLog[name] = "Collected";

        cout << "\nEvidence Added Successfully.\n";
    }

    // Displays all stored evidence
    void viewEvidence() {

        // Check if the evidence list is empty
        if (evidenceList.empty()) {
            cout << "\nNo evidence available.\n";
            return;
        }

        // Display each evidence record
        for (size_t i = 0; i < evidenceList.size(); i++) {

            cout << "\n Evidence " << i + 1 << " ";

            evidenceList[i].displayEvidence();

            cout << "Status    : "
                 << custodyLog[evidenceList[i].getName()]
                 << endl;
        }
    }

    // Searches for an evidence file by name
    void searchEvidence() {

        string name;

        cout << "Enter Evidence Name: ";
        getline(cin, name);

        bool found = false;

        // Search through all stored evidence
        for (size_t i = 0; i < evidenceList.size(); i++) {

            if (evidenceList[i].getName() == name) {

                evidenceList[i].displayEvidence();

                cout << "Status    : "
                     << custodyLog[evidenceList[i].getName()]
                     << endl;

                found = true;
                break;
            }
        }

        // Display a message if the evidence is not found
        if (!found)
            cout << "\nEvidence not found.\n";
    }

    // Generates a forensic report
    void generateReport() {

        // Create the report file
        ofstream report("forensic_report.txt");

        // Check whether the report file is created successfully
        if (!report) {
            cout << "\nError creating report file.\n";
            return;
        }

        // Write the report header
        report << "DIGITAL FORENSIC REPORT\n";
        report << "\n\n";

        // Write all evidence information into the report
        for (size_t i = 0; i < evidenceList.size(); i++) {

            report << "Evidence Name : "
                   << evidenceList[i].getName() << endl;

            report << "Hash Value    : "
                   << evidenceList[i].getHash() << endl;

            report << "Status        : "
                   << custodyLog[evidenceList[i].getName()]
                   << endl;

            report << "\n";
        }

        // Close the report file
        report.close();

        cout << "\nReport Generated Successfully.\n";

        // Open the generated report for display
        ifstream showReport("forensic_report.txt");

        string line;

        cout << "\n FORENSIC REPORT \n\n";

        // Display the report on the console
        while (getline(showReport, line)) {
            cout << line << endl;
        }

        // Close the report file
        showReport.close();
    }

    // Displays the main menu and controls the program flow
    void menu() {

        string inputChoice;
        int choice = 0;

        do {

            cout << "\n DIGITAL FORENSIC SYSTEM \n";
            cout << "1. Add Evidence\n";
            cout << "2. View Evidence\n";
            cout << "3. Search Evidence\n";
            cout << "4. Generate Report\n";
            cout << "5. Exit\n";
            cout << "Enter choice: ";

            // Read the entire input as a string
            getline(cin, inputChoice);

            // Skip the iteration if the input is empty
            if (inputChoice.empty())
                continue;

            // Convert the string input into an integer
            stringstream ss(inputChoice);

            // Validate numeric input
            if (!(ss >> choice)) {

                cout << "\nInvalid choice! Please enter a number between 1 and 5.\n";

                // Reset the choice value
                choice = 0;

                continue;
            }

            // Execute the selected menu option
            switch (choice) {

                case 1:
                    addEvidence();
                    break;

                case 2:
                    viewEvidence();
                    break;

                case 3:
                    searchEvidence();
                    break;

                case 4:
                    generateReport();
                    break;

                case 5:
                    cout << "\nExiting...\n";
                    break;

                default:
                    cout << "\nInvalid choice. Try again.\n";
            }

        } while (choice != 5);
    }
};


// Program execution starts here

int main() {

    // Create an object of the Digital Forensic System
    DigitalForensicSystem dfs;

    // Start the menu-driven application
    dfs.menu();

    return 0;
}
