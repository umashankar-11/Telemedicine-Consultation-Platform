#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

struct Appointment {
    string doctorName;
    string date;
    string time;
    Appointment(string doctor, string d, string t) : doctorName(doctor), date(d), time(t) {}
};

class PatientDashboard {
private:
    string patientName;
    stack<Appointment*> appointmentHistory;
    queue<Appointment*> upcomingAppointments;

public:
    PatientDashboard(string name) {
        patientName = name;
    }

    void addAppointment(string doctorName, string date, string time) {
        Appointment* newAppointment = new Appointment(doctorName, date, time);
        upcomingAppointments.push(newAppointment);
        cout << "Appointment added for " << patientName << " with Dr. " << doctorName << " on " << date << " at " << time << endl;
    }

    void viewUpcomingAppointments() {
        if (upcomingAppointments.empty()) {
            cout << "No upcoming appointments.\n";
            return;
        }

        cout << "Upcoming Appointments for " << patientName << ":\n";
        queue<Appointment*> tempQueue = upcomingAppointments;
        while (!tempQueue.empty()) {
            Appointment* appointment = tempQueue.front();
            tempQueue.pop();
            cout << "Doctor: " << appointment->doctorName << " | Date: " << appointment->date << " | Time: " << appointment->time << endl;
        }
    }

    void cancelUpcomingAppointment() {
        if (upcomingAppointments.empty()) {
            cout << "No upcoming appointments to cancel.\n";
            return;
        }

        Appointment* appointment = upcomingAppointments.front();
        upcomingAppointments.pop();
        appointmentHistory.push(appointment);
        cout << "Appointment with Dr. " << appointment->doctorName << " on " << appointment->date << " at " << appointment->time << " has been canceled.\n";
    }

    void viewAppointmentHistory() {
        if (appointmentHistory.empty()) {
            cout << "No appointment history available.\n";
            return;
        }

        cout << "Appointment History for " << patientName << ":\n";
        stack<Appointment*> tempStack = appointmentHistory;
        while (!tempStack.empty()) {
            Appointment* appointment = tempStack.top();
            tempStack.pop();
            cout << "Doctor: " << appointment->doctorName << " | Date: " << appointment->date << " | Time: " << appointment->time << endl;
        }
    }

    void undoCancelAppointment() {
        if (appointmentHistory.empty()) {
            cout << "No appointments to undo.\n";
            return;
        }

        Appointment* appointment = appointmentHistory.top();
        appointmentHistory.pop();
        upcomingAppointments.push(appointment);
        cout << "Appointment with Dr. " << appointment->doctorName << " on " << appointment->date << " at " << appointment->time << " has been restored.\n";
    }

    ~PatientDashboard() {
        while (!upcomingAppointments.empty()) {
            delete upcomingAppointments.front();
            upcomingAppointments.pop();
        }

        while (!appointmentHistory.empty()) {
            delete appointmentHistory.top();
            appointmentHistory.pop();
        }
    }
};

int main() {
    PatientDashboard* dashboard = new PatientDashboard("John Doe");

    dashboard->addAppointment("Smith", "2025-03-10", "10:00 AM");
    dashboard->addAppointment("Johnson", "2025-03-12", "02:00 PM");
    dashboard->addAppointment("Davis", "2025-03-15", "09:00 AM");

    cout << "\nViewing Upcoming Appointments:\n";
    dashboard->viewUpcomingAppointments();

    dashboard->cancelUpcomingAppointment();

    cout << "\nViewing Appointment History after canceling one appointment:\n";
    dashboard->viewAppointmentHistory();

    cout << "\nViewing Upcoming Appointments after canceling one:\n";
    dashboard->viewUpcomingAppointments();

    dashboard->undoCancelAppointment();

    cout << "\nViewing Upcoming Appointments after undoing the cancel:\n";
    dashboard->viewUpcomingAppointments();

    delete dashboard;
    return 0;
}
