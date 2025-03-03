#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

template <typename T>
class DataAnalytics {
private:
    vector<T> data;

public:
    void addData(T value) {
        data.push_back(value);
    }

    void displayData() {
        for (auto& value : data) {
            cout << value << " ";
        }
        cout << endl;
    }

    T calculateAverage() {
        T sum = 0;
        for (auto& value : data) {
            sum += value;
        }
        return sum / data.size();
    }

    T findMax() {
        return *max_element(data.begin(), data.end());
    }

    T findMin() {
        return *min_element(data.begin(), data.end());
    }

    T calculateMedian() {
        if (data.empty()) return 0;

        sort(data.begin(), data.end());
        if (data.size() % 2 == 0) {
            return (data[data.size() / 2 - 1] + data[data.size() / 2]) / 2;
        } else {
            return data[data.size() / 2];
        }
    }

    T calculateStandardDeviation() {
        if (data.size() < 2) return 0;

        T mean = calculateAverage();
        T sumSquares = 0;
        for (auto& value : data) {
            sumSquares += (value - mean) * (value - mean);
        }
        return sqrt(sumSquares / (data.size() - 1));
    }

    void sortData() {
        sort(data.begin(), data.end());
    }

    void clearData() {
        data.clear();
    }
};

template <typename T>
class PatientData {
private:
    string patientName;
    string patientID;
    DataAnalytics<T> dataAnalytics;

public:
    PatientData(string name, string id) : patientName(name), patientID(id) {}

    void addData(T value) {
        dataAnalytics.addData(value);
    }

    void displayPatientData() {
        cout << "Patient Name: " << patientName << endl;
        cout << "Patient ID: " << patientID << endl;
        cout << "Data: ";
        dataAnalytics.displayData();
        cout << "Average: " << dataAnalytics.calculateAverage() << endl;
        cout << "Max: " << dataAnalytics.findMax() << endl;
        cout << "Min: " << dataAnalytics.findMin() << endl;
        cout << "Median: " << dataAnalytics.calculateMedian() << endl;
        cout << "Standard Deviation: " << dataAnalytics.calculateStandardDeviation() << endl;
    }

    void clearPatientData() {
        dataAnalytics.clearData();
    }
};

template <typename T>
class PatientAnalytics {
private:
    vector<PatientData<T>> patients;

public:
    void addPatient(PatientData<T> patient) {
        patients.push_back(patient);
    }

    void displayAllPatientsData() {
        for (auto& patient : patients) {
            patient.displayPatientData();
            cout << endl;
        }
    }

    void clearAllPatientData() {
        patients.clear();
    }
};

int main() {
    PatientAnalytics<int> analytics;

    PatientData<int> patient1("Alice", "P001");
    patient1.addData(120);
    patient1.addData(130);
    patient1.addData(125);
    patient1.addData(140);
    analytics.addPatient(patient1);

    PatientData<int> patient2("Bob", "P002");
    patient2.addData(150);
    patient2.addData(160);
    patient2.addData(145);
    patient2.addData(155);
    analytics.addPatient(patient2);

    PatientData<int> patient3("Charlie", "P003");
    patient3.addData(100);
    patient3.addData(110);
    patient3.addData(115);
    patient3.addData(105);
    analytics.addPatient(patient3);

    cout << "All Patients Data Analytics:" << endl;
    analytics.displayAllPatientsData();

    return 0;
}
