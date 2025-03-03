#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <ctime>
using namespace std;

struct Patient {
    string name;
    int id;
    time_t arrivalTime;
    Patient(string n, int i) {
        name = n;
        id = i;
        arrivalTime = time(0);
    }
};

class VirtualWaitingRoom {
private:
    queue<Patient*> waitingQueue;
    vector<Patient*> servedPatients;
    int nextPatientId;

public:
    VirtualWaitingRoom() {
        nextPatientId = 1;
    }

    void addPatient(string name) {
        Patient* newPatient = new Patient(name, nextPatientId++);
        waitingQueue.push(newPatient);
        cout << "Patient " << newPatient->name << " added to the waiting room.\n";
    }

    void servePatient() {
        if (waitingQueue.empty()) {
            cout << "No patients in the waiting room.\n";
            return;
        }

        Patient* patient = waitingQueue.front();
        waitingQueue.pop();
        servedPatients.push_back(patient);
        cout << "Serving patient " << patient->name << " (ID: " << patient->id << ").\n";
    }

    void viewWaitingRoom() {
        if (waitingQueue.empty()) {
            cout << "No patients waiting.\n";
            return;
        }
        
        cout << "Patients in the waiting room:\n";
        queue<Patient*> tempQueue = waitingQueue;
        while (!tempQueue.empty()) {
            Patient* patient = tempQueue.front();
            tempQueue.pop();
            cout << "ID: " << patient->id << " | Name: " << patient->name 
                 << " | Arrival Time: " << ctime(&patient->arrivalTime);
        }
    }

    void viewServedPatients() {
        if (servedPatients.empty()) {
            cout << "No patients have been served yet.\n";
            return;
        }

        cout << "List of served patients:\n";
        for (Patient* patient : servedPatients) {
            cout << "ID: " << patient->id << " | Name: " << patient->name 
                 << " | Arrival Time: " << ctime(&patient->arrivalTime);
        }
    }

    void removePatient(int id) {
        queue<Patient*> tempQueue;
        bool found = false;

        while (!waitingQueue.empty()) {
            Patient* patient = waitingQueue.front();
            waitingQueue.pop();
            if (patient->id == id) {
                delete patient;
                found = true;
            } else {
                tempQueue.push(patient);
            }
        }

        waitingQueue = tempQueue;
        
        if (found) {
            cout << "Patient with ID " << id << " removed from the waiting room.\n";
        } else {
            cout << "Patient with ID " << id << " not found.\n";
        }
    }

    void clearAllPatients() {
        while (!waitingQueue.empty()) {
            Patient* patient = waitingQueue.front();
            waitingQueue.pop();
            delete patient;
        }
        cout << "All patients removed from the waiting room.\n";
    }

    ~VirtualWaitingRoom() {
        clearAllPatients();
        for (Patient* patient : servedPatients) {
            delete patient;
        }
    }
};

int main() {
    VirtualWaitingRoom* vrRoom = new VirtualWaitingRoom;

    vrRoom->addPatient("John Doe");
    vrRoom->addPatient("Alice Smith");
    vrRoom->addPatient("Bob Johnson");

    cout << "\nViewing Waiting Room:\n";
    vrRoom->viewWaitingRoom();

    vrRoom->servePatient();

    cout << "\nViewing Waiting Room after serving one patient:\n";
    vrRoom->viewWaitingRoom();

    vrRoom->viewServedPatients();

    vrRoom->removePatient(2);

    cout << "\nViewing Waiting Room after removing a patient:\n";
    vrRoom->viewWaitingRoom();

    vrRoom->clearAllPatients();

    delete vrRoom;
    return 0;
}
