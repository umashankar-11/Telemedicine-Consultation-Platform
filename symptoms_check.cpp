#include <iostream>
#include <string>
#include <vector>
using namespace std;

class SymptomChecker {
private:
    vector<string> symptomsList;
    vector<string> possibleConditions;

public:
    void addSymptom(string symptom) {
        symptomsList.push_back(symptom);
    }

    void checkSymptoms(vector<string> symptoms) {
        cout << "Checking symptoms...\n";
        possibleConditions.clear();

        for (string symptom : symptoms) {
            if (symptom == "fever") {
                possibleConditions.push_back("Flu");
                possibleConditions.push_back("COVID-19");
            } 
            else if (symptom == "headache") {
                possibleConditions.push_back("Migraine");
                possibleConditions.push_back("Flu");
            }
            else if (symptom == "cough") {
                possibleConditions.push_back("Cold");
                possibleConditions.push_back("COVID-19");
            }
            else if (symptom == "fatigue") {
                possibleConditions.push_back("Anemia");
                possibleConditions.push_back("COVID-19");
            }
            else if (symptom == "chest pain") {
                possibleConditions.push_back("Heart Attack");
                possibleConditions.push_back("Pneumonia");
            }
            else if (symptom == "shortness of breath") {
                possibleConditions.push_back("Asthma");
                possibleConditions.push_back("COVID-19");
            }
        }

        displayPossibleConditions();
    }

    void displayPossibleConditions() {
        if (possibleConditions.empty()) {
            cout << "No conditions found for the given symptoms.\n";
        } else {
            cout << "Possible conditions based on the symptoms: \n";
            for (string condition : possibleConditions) {
                cout << "- " << condition << endl;
            }
        }
    }
};

class Patient {
private:
    string name;
    vector<string> symptoms;

public:
    Patient(string patientName) {
        name = patientName;
    }

    void addSymptom(string symptom) {
        symptoms.push_back(symptom);
    }

    void checkSymptoms(SymptomChecker &checker) {
        checker.checkSymptoms(symptoms);
    }

    void displayPatientInfo() {
        cout << "Patient Name: " << name << endl;
        cout << "Symptoms: ";
        for (string symptom : symptoms) {
            cout << symptom << " ";
        }
        cout << endl;
    }
};

class AIConsultation {
private:
    Patient patient;
    SymptomChecker symptomChecker;

public:
    AIConsultation(Patient p) : patient(p) {}

    void initiateConsultation() {
        patient.displayPatientInfo();
        patient.checkSymptoms(symptomChecker);
    }

    void addSymptomToPatient(string symptom) {
        patient.addSymptom(symptom);
    }

    void startAIConsultation() {
        initiateConsultation();
    }
};

int main() {
    Patient patient1("Alice");
    patient1.addSymptom("fever");
    patient1.addSymptom("headache");
    patient1.addSymptom("cough");

    AIConsultation consultation(patient1);

    consultation.startAIConsultation();

    cout << "\n Second Consultation \n";
    Patient patient2("Bob");
    patient2.addSymptom("fatigue");
    patient2.addSymptom("chest pain");

    AIConsultation consultation2(patient2);
    consultation2.startAIConsultation();

    return 0;
}
