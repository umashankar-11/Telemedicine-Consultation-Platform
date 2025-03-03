#include <iostream>
#include <string>
using namespace std;

struct Appointment {
    string patientName;
    string doctorName;
    string date;
    string time;
    Appointment* next;
};

class AppointmentScheduler {
private:
    Appointment* head;

public:
    AppointmentScheduler() {
        head = nullptr;
    }

    void scheduleAppointment(string patientName, string doctorName, string date, string time) {
        Appointment* newAppointment = new Appointment;
        newAppointment->patientName = patientName;
        newAppointment->doctorName = doctorName;
        newAppointment->date = date;
        newAppointment->time = time;
        newAppointment->next = nullptr;

        if (head == nullptr) {
            head = newAppointment;
        } else {
            Appointment* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newAppointment;
        }

        cout << "Appointment Scheduled: " << patientName << " with Dr. " << doctorName << " on " << date << " at " << time << endl;
    }

    void viewAppointments() {
        if (head == nullptr) {
            cout << "No appointments scheduled." << endl;
            return;
        }

        Appointment* temp = head;
        while (temp != nullptr) {
            cout << "Patient: " << temp->patientName << ", Doctor: " << temp->doctorName 
                 << ", Date: " << temp->date << ", Time: " << temp->time << endl;
            temp = temp->next;
        }
    }

    void cancelAppointment(string patientName, string date, string time) {
        if (head == nullptr) {
            cout << "No appointments to cancel." << endl;
            return;
        }

        Appointment* temp = head;
        Appointment* prev = nullptr;

        while (temp != nullptr && (temp->patientName != patientName || temp->date != date || temp->time != time)) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Appointment not found." << endl;
            return;
        }

        if (prev == nullptr) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }

        delete temp;
        cout << "Appointment canceled for " << patientName << " on " << date << " at " << time << endl;
    }

    ~AppointmentScheduler() {
        Appointment* temp = head;
        while (temp != nullptr) {
            Appointment* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        cout << "Scheduler cleaned up." << endl;
    }
};

int main() {
    AppointmentScheduler* scheduler = new AppointmentScheduler;

    scheduler->scheduleAppointment("John Doe", "Dr. Smith", "2025-03-05", "10:00 AM");
    scheduler->scheduleAppointment("Jane Smith", "Dr. Johnson", "2025-03-06", "11:30 AM");
    scheduler->scheduleAppointment("Alice Brown", "Dr. Davis", "2025-03-07", "02:00 PM");

    cout << "\nCurrent Appointments: \n";
    scheduler->viewAppointments();

    scheduler->cancelAppointment("Jane Smith", "2025-03-06", "11:30 AM");

    cout << "\nUpdated Appointments: \n";
    scheduler->viewAppointments();

    delete scheduler;
    return 0;
}
