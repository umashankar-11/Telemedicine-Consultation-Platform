#include <iostream>
#include <string>
using namespace std;

struct HealthData {
    string patientName;
    float heartRate;
    float bloodPressure;
    float temperature;
};

class HealthMonitor {
private:
    HealthData* healthDataArray;
    int size;
    int capacity;

public:
    HealthMonitor(int cap) {
        capacity = cap;
        size = 0;
        healthDataArray = new HealthData[capacity];
    }

    void addHealthData(string patientName, float heartRate, float bloodPressure, float temperature) {
        if (size >= capacity) {
            cout << "Array is full, cannot add more data." << endl;
            return;
        }
        healthDataArray[size].patientName = patientName;
        healthDataArray[size].heartRate = heartRate;
        healthDataArray[size].bloodPressure = bloodPressure;
        healthDataArray[size].temperature = temperature;
        size++;
        cout << "Health data added for " << patientName << endl;
    }

    void updateHealthData(string patientName, float heartRate, float bloodPressure, float temperature) {
        for (int i = 0; i < size; i++) {
            if (healthDataArray[i].patientName == patientName) {
                healthDataArray[i].heartRate = heartRate;
                healthDataArray[i].bloodPressure = bloodPressure;
                healthDataArray[i].temperature = temperature;
                cout << "Health data updated for " << patientName << endl;
                return;
            }
        }
        cout << "Patient not found." << endl;
    }

    void viewHealthData(string patientName) {
        for (int i = 0; i < size; i++) {
            if (healthDataArray[i].patientName == patientName) {
                cout << "Patient: " << patientName << "\n";
                cout << "Heart Rate: " << healthDataArray[i].heartRate << "\n";
                cout << "Blood Pressure: " << healthDataArray[i].bloodPressure << "\n";
                cout << "Temperature: " << healthDataArray[i].temperature << "\n";
                return;
            }
        }
        cout << "Patient not found." << endl;
    }

    void removeHealthData(string patientName) {
        for (int i = 0; i < size; i++) {
            if (healthDataArray[i].patientName == patientName) {
                for (int j = i; j < size - 1; j++) {
                    healthDataArray[j] = healthDataArray[j + 1];
                }
                size--;
                cout << "Health data removed for " << patientName << endl;
                return;
            }
        }
        cout << "Patient not found." << endl;
    }

    void viewAllData() {
        if (size == 0) {
            cout << "No health data available." << endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            cout << "Patient: " << healthDataArray[i].patientName << "\n";
            cout << "Heart Rate: " << healthDataArray[i].heartRate << "\n";
            cout << "Blood Pressure: " << healthDataArray[i].bloodPressure << "\n";
            cout << "Temperature: " << healthDataArray[i].temperature << "\n\n";
        }
    }

    ~HealthMonitor() {
        delete[] healthDataArray;
        cout << "Health monitor system cleaned up." << endl;
    }
};

int main() {
    HealthMonitor* monitor = new HealthMonitor(5);

    monitor->addHealthData("John Doe", 75.5, 120.8, 98.6);
    monitor->addHealthData("Jane Smith", 80.0, 115.0, 99.1);
    monitor->addHealthData("Alice Brown", 70.3, 130.5, 98.3);

    cout << "\nViewing All Health Data:\n";
    monitor->viewAllData();

    monitor->updateHealthData("John Doe", 78.0, 118.0, 98.7);
    monitor->removeHealthData("Alice Brown");

    cout << "\nUpdated Health Data:\n";
    monitor->viewAllData();

    monitor->viewHealthData("John Doe");

    delete monitor;
    return 0;
}
