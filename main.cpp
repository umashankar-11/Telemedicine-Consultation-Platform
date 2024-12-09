#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Doctor {
public:
    string name;
    string specialization;
    int id;

    Doctor(string n, string s, int i) : name(n), specialization(s), id(i) {}

    void saveToFile(ofstream &file) {
        file << id << "," << name << "," << specialization << endl;
    }

    static Doctor* loadFromFile(const string& line) {
        stringstream ss(line);
        string name, specialization;
        int id;
        getline(ss, name, ',');
        getline(ss, specialization, ',');
        ss >> id;
        return new Doctor(name, specialization, id);
    }
};

class Patient {
public:
    string name;
    int id;

    Patient(string n, int i) : name(n), id(i) {}

    void saveToFile(ofstream &file) {
        file << id << "," << name << endl;
    }

    static Patient* loadFromFile(const string& line) {
        stringstream ss(line);
        string name;
        int id;
        getline(ss, name, ',');
        ss >> id;
        return new Patient(name, id);
    }
};

class Appointment {
public:
    Patient* patient;
    Doctor* doctor;
    string date_time;

    Appointment(Patient* p, Doctor* d, string dt) : patient(p), doctor(d), date_time(dt) {}

    void saveToFile(ofstream &file) {
        file << patient->id << "," << doctor->id << "," << date_time << endl;
    }

    static Appointment* loadFromFile(const string& line, vector<Patient*> &patients, vector<Doctor*> &doctors) {
        stringstream ss(line);
        int patientId, doctorId;
        string date_time;
        ss >> patientId;
        ss.ignore(1, ',');
        ss >> doctorId;
        ss.ignore(1, ',');
        getline(ss, date_time);

        Patient* patient = nullptr;
        Doctor* doctor = nullptr;
        
        for (auto p : patients) {
            if (p->id == patientId) {
                patient = p;
                break;
            }
        }

        for (auto d : doctors) {
            if (d->id == doctorId) {
                doctor = d;
                break;
            }
        }

        return new Appointment(patient, doctor, date_time);
    }
};

class TelemedicinePlatform {
private:
    vector<Doctor*> doctors;
    vector<Patient*> patients;
    vector<Appointment*> appointments;

    void loadDoctors() {
        ifstream file("doctors.txt");
        string line;
        while (getline(file, line)) {
            Doctor* doctor = Doctor::loadFromFile(line);
            doctors.push_back(doctor);
        }
    }

    void loadPatients() {
        ifstream file("patients.txt");
        string line;
        while (getline(file, line)) {
            Patient* patient = Patient::loadFromFile(line);
            patients.push_back(patient);
        }
    }

    void loadAppointments() {
        ifstream file("appointments.txt");
        string line;
        while (getline(file, line)) {
            Appointment* appointment = Appointment::loadFromFile(line, patients, doctors);
            appointments.push_back(appointment);
        }
    }

    void saveDoctors() {
        ofstream file("doctors.txt");
        for (auto doctor : doctors) {
            doctor->saveToFile(file);
        }
    }

    void savePatients() {
        ofstream file("patients.txt");
        for (auto patient : patients) {
            patient->saveToFile(file);
        }
    }

    void saveAppointments() {
        ofstream file("appointments.txt");
        for (auto appointment : appointments) {
            appointment->saveToFile(file);
        }
    }

public:
    TelemedicinePlatform() {
        loadDoctors();
        loadPatients();
        loadAppointments();
    }

    ~TelemedicinePlatform() {
        for (auto doctor : doctors) {
            delete doctor;
        }
        for (auto patient : patients) {
            delete patient;
        }
        for (auto appointment : appointments) {
            delete appointment;
        }
    }

    void addDoctor(string name, string specialization) {
        int id = doctors.size() + 1;
        Doctor* newDoctor = new Doctor(name, specialization, id);
        doctors.push_back(newDoctor);
        saveDoctors();
        cout << "Doctor added: " << name << endl;
    }

    void addPatient(string name) {
        int id = patients.size() + 1;
        Patient* newPatient = new Patient(name, id);
        patients.push_back(newPatient);
        savePatients();
        cout << "Patient added: " << name << endl;
    }

    void scheduleAppointment(int patientId, int doctorId, string dateTime) {
        Patient* patient = nullptr;
        Doctor* doctor = nullptr;

        for (auto p : patients) {
            if (p->id == patientId) {
                patient = p;
                break;
            }
        }

        for (auto d : doctors) {
            if (d->id == doctorId) {
                doctor = d;
                break;
            }
        }

        if (patient && doctor) {
            Appointment* appointment = new Appointment(patient, doctor, dateTime);
            appointments.push_back(appointment);
            saveAppointments();
            cout << "Appointment scheduled with Dr. " << doctor->name << " for " << patient->name << " on " << dateTime << endl;
        } else {
            cout << "Invalid patient or doctor ID." << endl;
        }
    }

    void listAppointments() {
        cout << "\nScheduled Appointments: \n";
        for (auto& appointment : appointments) {
            cout << "Patient: " << appointment->patient->name
                 << " | Doctor: " << appointment->doctor->name
                 << " | Specialization: " << appointment->doctor->specialization
                 << " | Date/Time: " << appointment->date_time << endl;
        }
    }

    void showDoctors() {
        cout << "\nAvailable Doctors: \n";
        for (auto& doctor : doctors) {
            cout << doctor->id << ". " << doctor->name << " (" << doctor->specialization << ")\n";
        }
    }

    void showPatients() {
        cout << "\nRegistered Patients: \n";
        for (auto& patient : patients) {
            cout << patient->id << ". " << patient->name << endl;
        }
    }

    void run() {
        int option;
        do {
            cout << "\nTelemedicine Platform\n";
            cout << "1. Show Doctors\n";
            cout << "2. Show Patients\n";
            cout << "3. Schedule Appointment\n";
            cout << "4. List Appointments\n";
            cout << "5. Exit\n";
            cout << "Enter an option: ";
            cin >> option;

            switch (option) {
            case 1:
                showDoctors();
                break;
            case 2:
                showPatients();
                break;
            case 3: {
                int patientId, doctorId;
                string dateTime;
                showPatients();
                cout << "Enter Patient ID: ";
                cin >> patientId;
                showDoctors();
                cout << "Enter Doctor ID: ";
                cin >> doctorId;
                cout << "Enter Appointment Date and Time (e.g., 2024-12-12 14:00): ";
                cin.ignore(); // To consume the leftover newline character
                getline(cin, dateTime);
                scheduleAppointment(patientId, doctorId, dateTime);
                break;
            }
            case 4:
                listAppointments();
                break;
            case 5:
                cout << "Exiting platform..." << endl;
                break;
            default:
                cout << "Invalid option! Try again." << endl;
                break;
            }

        } while (option != 5);
    }
};

int main() {
    TelemedicinePlatform platform;
    platform.run();
    return 0;
}
