#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <portaudio.h>
#include <thread>

using namespace std;
using namespace cv;

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (256)
#define NUM_CHANNELS (1)
#define DITHER_FLAG (0)
#define SAMPLE_TYPE (paInt16)

PaStream *audio_stream;

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

static int audio_callback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags statusFlags, void *userData) {
    const short *in = (const short *)inputBuffer;
    short *out = (short *)outputBuffer;

    for (unsigned long i = 0; i < framesPerBuffer; i++) {
        *out++ = *in++;  
    }
    return paContinue;
}

void init_audio_stream() {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(err) << endl;
        exit(1);
    }

    err = Pa_OpenDefaultStream(&audio_stream, NUM_CHANNELS, NUM_CHANNELS, SAMPLE_TYPE,
                               SAMPLE_RATE, FRAMES_PER_BUFFER, audio_callback, NULL);
    if (err != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(err) << endl;
        exit(1);
    }

    err = Pa_StartStream(audio_stream);
    if (err != paNoError) {
        cerr << "PortAudio error: " << Pa_GetErrorText(err) << endl;
        exit(1);
    }
}

void capture_video(const string &filename) {
    VideoCapture cap(0); 
    if (!cap.isOpened()) {
        cerr << "Error: Could not open video stream" << endl;
        exit(1);
    }

    VideoWriter video_output(filename, VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(640, 480));

    namedWindow("Video Stream", WINDOW_NORMAL);

    while (true) {
        Mat frame;
        cap >> frame; 
        if (frame.empty()) {
            cerr << "Error: Could not capture frame" << endl;
            break;
        }

        video_output.write(frame);  
        imshow("Video Stream", frame);

        if (waitKey(10) == 'q') {
            break;
        }
    }

    cap.release();
    video_output.release();
    destroyAllWindows();
}

void start_telemedicine_session(PatientManagement &management) {
    string patient_name;
    cout << "Enter patient name for the session: ";
    cin.ignore();
    getline(cin, patient_name);

    management.searchPatientByName(patient_name);

    thread video_thread(capture_video, "telemedicine_session.avi"); 
    video_thread.join();
}

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
        cout << "\n5. Start Telemedicine Session (Video + Audio)";
        cout << "\n6. Exit";
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
                cout << "\nStarting Telemedicine Session (Video + Audio)..." << endl;
                init_audio_stream();
                start_telemedicine_session(management);
                break;
            }

            case 6: {
                cout << "\nExiting Telemedicine Registration System." << endl;
                exitFlag = true;
                break;
            }

            default:
                cout << "\nInvalid Choice! Please try again." << endl;
                break;
        }
    }

    Pa_StopStream(audio_stream);
    Pa_CloseStream(audio_stream);
    Pa_Terminate();

    return 0;
}
