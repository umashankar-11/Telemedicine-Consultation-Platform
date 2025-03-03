#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class MedicalDocument {
private:
    string patientName;
    string documentType;
    string documentContent;

public:
    MedicalDocument(string patient, string type, string content) {
        patientName = patient;
        documentType = type;
        documentContent = content;
    }

    void saveToFile() {
        ofstream file;
        file.open(patientName + "_" + documentType + ".txt", ios::out);
        if (file.is_open()) {
            file << "Patient: " << patientName << endl;
            file << "Document Type: " << documentType << endl;
            file << "Document Content: " << endl;
            file << documentContent << endl;
            file.close();
            cout << "Document saved for " << patientName << endl;
        } else {
            cout << "Error opening file to save document." << endl;
        }
    }

    void loadFromFile() {
        ifstream file;
        file.open(patientName + "_" + documentType + ".txt", ios::in);
        if (file.is_open()) {
            string line;
            cout << "Loading document for " << patientName << "..." << endl;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        } else {
            cout << "Error opening file to load document." << endl;
        }
    }

    void deleteFile() {
        if (remove((patientName + "_" + documentType + ".txt").c_str()) != 0) {
            cout << "Error deleting the document file." << endl;
        } else {
            cout << "Document deleted for " << patientName << endl;
        }
    }

    void updateDocument(string newContent) {
        ofstream file;
        file.open(patientName + "_" + documentType + ".txt", ios::out | ios::trunc);
        if (file.is_open()) {
            file << "Patient: " << patientName << endl;
            file << "Document Type: " << documentType << endl;
            file << "Updated Document Content: " << endl;
            file << newContent << endl;
            file.close();
            cout << "Document updated for " << patientName << endl;
        } else {
            cout << "Error opening file to update document." << endl;
        }
    }

    void appendDocument(string additionalContent) {
        ofstream file;
        file.open(patientName + "_" + documentType + ".txt", ios::out | ios::app);
        if (file.is_open()) {
            file << "\nAdditional Content: " << endl;
            file << additionalContent << endl;
            file.close();
            cout << "Additional content appended for " << patientName << endl;
        } else {
            cout << "Error opening file to append content." << endl;
        }
    }
};

int main() {
    MedicalDocument* doc1 = new MedicalDocument("John Doe", "Prescription", "Take one pill daily for 14 days.");
    MedicalDocument* doc2 = new MedicalDocument("Jane Smith", "X-ray Report", "No fractures detected. Clear chest X-ray.");
    MedicalDocument* doc3 = new MedicalDocument("Alice Brown", "Blood Test", "Blood sugar levels within normal range.");

    doc1->saveToFile();
    doc2->saveToFile();
    doc3->saveToFile();

    cout << "\nViewing Document for John Doe: " << endl;
    doc1->loadFromFile();

    cout << "\nUpdating Prescription for John Doe: " << endl;
    doc1->updateDocument("Take two pills daily for 10 days.");

    cout << "\nAppending Content to Prescription for John Doe: " << endl;
    doc1->appendDocument("Take the medication after meals.");

    cout << "\nViewing Updated Document for John Doe: " << endl;
    doc1->loadFromFile();

    cout << "\nDeleting Blood Test Document for Alice Brown: " << endl;
    doc3->deleteFile();

    delete doc1;
    delete doc2;
    delete doc3;

    return 0;
}
