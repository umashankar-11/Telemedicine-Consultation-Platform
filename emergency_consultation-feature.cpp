#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class ConsultationDetails {
private:
    string patientName;
    string doctorName;
    string consultationTime;
    string consultationType;
    string consultationStatus;

public:
    ConsultationDetails(string pName, string dName, string cTime, string cType) {
        patientName = pName;
        doctorName = dName;
        consultationTime = cTime;
        consultationType = cType;
        consultationStatus = "Scheduled";
    }

    void setConsultationStatus(string status) {
        consultationStatus = status;
    }

    string getPatientName() {
        return patientName;
    }

    string getDoctorName() {
        return doctorName;
    }

    string getConsultationTime() {
        return consultationTime;
    }

    string getConsultationType() {
        return consultationType;
    }

    string getConsultationStatus() {
        return consultationStatus;
    }

    void displayConsultationDetails() {
        cout << "Patient Name: " << patientName << endl;
        cout << "Doctor Name: " << doctorName << endl;
        cout << "Consultation Time: " << consultationTime << endl;
        cout << "Consultation Type: " << consultationType << endl;
        cout << "Consultation Status: " << consultationStatus << endl;
    }
};

class EmergencyConsultation {
private:
    ConsultationDetails consultation;

public:
    EmergencyConsultation(string pName, string dName, string cTime, string cType) 
        : consultation(pName, dName, cTime, cType) {}

    void initiateEmergencyConsultation() {
        cout << "Emergency Consultation Requested!\n";
        consultation.setConsultationStatus("In Progress");
        cout << "Consultation Status: " << consultation.getConsultationStatus() << endl;
        consultation.displayConsultationDetails();
    }

    void completeConsultation() {
        consultation.setConsultationStatus("Completed");
        cout << "Emergency Consultation Completed.\n";
        consultation.displayConsultationDetails();
    }

    void cancelConsultation() {
        consultation.setConsultationStatus("Canceled");
        cout << "Emergency Consultation Canceled.\n";
        consultation.displayConsultationDetails();
    }
};

class DoctorAvailability {
private:
    string doctorName;
    bool isAvailable;

public:
    DoctorAvailability(string name) : doctorName(name), isAvailable(true) {}

    bool checkAvailability() {
        return isAvailable;
    }

    void setAvailability(bool availability) {
        isAvailable = availability;
    }

    string getDoctorName() {
        return doctorName;
    }
};

class Patient {
private:
    string patientName;
    bool isEmergency;

public:
    Patient(string name, bool emergency) : patientName(name), isEmergency(emergency) {}

    bool isEmergencyConsultation() {
        return isEmergency;
    }

    string getPatientName() {
        return patientName;
    }
};

class EmergencyService {
private:
    DoctorAvailability doctor;
    Patient patient;

public:
    EmergencyService(DoctorAvailability d, Patient p) : doctor(d), patient(p) {}

    void handleEmergency() {
        if (patient.isEmergencyConsultation() && doctor.checkAvailability()) {
            cout << "Doctor " << doctor.getDoctorName() << " is available for emergency consultation.\n";
            EmergencyConsultation consultation(patient.getPatientName(), doctor.getDoctorName(), getCurrentTime(), "Emergency");
            consultation.initiateEmergencyConsultation();
        } else {
            cout << "Emergency service cannot be initiated. Doctor not available.\n";
        }
    }

    string getCurrentTime() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        string time = to_string(1900 + ltm->tm_year) + "-" +
                      to_string(1 + ltm->tm_mon) + "-" +
                      to_string(ltm->tm_mday) + " " +
                      to_string(1 + ltm->tm_hour) + ":" +
                      to_string(1 + ltm->tm_min);
        return time;
    }
};

int main() {
    DoctorAvailability doctor1("Dr. Smith");
    Patient patient1("John Doe", true); 

    EmergencyService emergencyService(doctor1, patient1);

    emergencyService.handleEmergency();

    cout << "\n--- Completing Consultation ---\n";
    EmergencyConsultation consultation1(patient1.getPatientName(), doctor1.getDoctorName(), emergencyService.getCurrentTime(), "Emergency");
    consultation1.completeConsultation();

    cout << "\n--- Canceling Consultation ---\n";
    consultation1.cancelConsultation();

    return 0;
}
