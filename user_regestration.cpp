#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Patient {
private:
    string name;
    int age;
    string medicalHistory;

public:
    Patient() : name(""), age(0), medicalHistory("") {}
    Patient(string n, int a, string m) : name(n), age(a), medicalHistory(m) {}

    Patient& operator=(const Patient& other) {
        if (this != &other) {
            name = other.name;
            age = other.age;
            medicalHistory = other.medicalHistory;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Patient& p) {
        os << "Patient Name: " << p.name << endl;
        os << "Age: " << p.age << endl;
        os << "Medical History: " << p.medicalHistory << endl;
        return os;
    }

    friend istream& operator>>(istream& is, Patient& p) {
        cout << "Enter Patient Name: ";
        getline(is, p.name);
        cout << "Enter Age: ";
        is >> p.age;
        is.ignore();
        cout << "Enter Medical History: ";
        getline(is, p.medicalHistory);
        return is;
    }

    void updateMedicalHistory(const string& newHistory) {
        medicalHistory = newHistory;
    }

    void display() const {
        cout << *this;
    }
};

class PatientManagement {
private:
    vector<Patient> patients;

public:
    void addPatient(const Patient& p) {
        patients.push_back(p);
    }

    void displayAllPatients() const {
        for (size_t i = 0; i < patients.size(); i++) {
            cout << "\nPatient " << (i + 1) << " Details:" << endl;
            patients[i].display();
        }
    }

    void updatePatientHistory(int index, const string& newHistory) {
        if (index >= 0 && index < patients.size()) {
            patients[index].updateMedicalHistory(newHistory);
            cout << "\nMedical history updated for Patient " << (index + 1) << endl;
        } else {
            cout << "\nInvalid patient index!" << endl;
        }
    }

    void searchPatientByName(const string& name) const {
        bool found = false;
        for (const auto& patient : patients) {
            if (patient.name == name) {
                cout << "\nPatient Found: " << endl;
                patient.display();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "\nPatient not found!" << endl;
        }
    }

    int getTotalPatients() const {
        return patients.size();
    }
};

int main() {
    PatientManagement management;
    int choice;
    bool exitFlag = false;

    while (!exitFlag) {
        cout << "\n--- Telemedicine Registration System ---";
        cout << "\n1. Register New Patient";
        cout << "\n2. Display All Patients";
        cout << "\n3. Update Patient Medical History";
        cout << "\n4. Search Patient by Name";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                Patient newPatient;
                cout << "\nRegistering New Patient" << endl;
                cin >> newPatient;
                management.addPatient(newPatient);
                cout << "\nNew patient registered successfully!" << endl;
                break;
            }

            case 2: {
                cout << "\nDisplaying All Patients:" << endl;
                management.displayAllPatients();
                break;
            }

            case 3: {
                int index;
                string newHistory;
                cout << "\nEnter Patient Index to Update Medical History: ";
                cin >> index;
                cin.ignore();
                cout << "\nEnter New Medical History: ";
                getline(cin, newHistory);
                management.updatePatientHistory(index - 1, newHistory);
                break;
            }

            case 4: {
                string name;
                cout << "\nEnter Patient Name to Search: ";
                getline(cin, name);
                management.searchPatientByName(name);
                break;
            }

            case 5: {
                cout << "\nExiting Telemedicine Registration System." << endl;
                exitFlag = true;
                break;
            }

            default:
                cout << "\nInvalid Choice! Please try again." << endl;
                break;
        }
    }

    return 0;
}
