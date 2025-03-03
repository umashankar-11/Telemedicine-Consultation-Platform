#include <iostream>
#include <string>
using namespace std;

struct Patient {
    string name;
    int id;
    Patient(string n, int i) : name(n), id(i) {}
};

class VideoConsultationQueue {
private:
    Patient** queue;
    int front, rear, capacity, count;

public:
    VideoConsultationQueue(int cap) {
        capacity = cap;
        queue = new Patient*[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    void addPatient(string name, int id) {
        if (count == capacity) {
            cout << "Queue is full. Cannot add new patient.\n";
            return;
        }
        rear = (rear + 1) % capacity;
        queue[rear] = new Patient(name, id);
        count++;
        cout << "Patient " << name << " added to the video consultation queue.\n";
    }

    void startConsultation() {
        if (count == 0) {
            cout << "No patients in the queue for consultation.\n";
            return;
        }
        Patient* patient = queue[front];
        cout << "Starting video consultation with " << patient->name << " (ID: " << patient->id << ").\n";
        front = (front + 1) % capacity;
        count--;
    }

    void viewQueue() {
        if (count == 0) {
            cout << "No patients in the queue.\n";
            return;
        }
        cout << "Patients in the video consultation queue:\n";
        int idx = front;
        for (int i = 0; i < count; i++) {
            cout << "ID: " << queue[idx]->id << " | Name: " << queue[idx]->name << endl;
            idx = (idx + 1) % capacity;
        }
    }

    void removePatient() {
        if (count == 0) {
            cout << "No patients in the queue to remove.\n";
            return;
        }
        Patient* patient = queue[front];
        cout << "Removing patient " << patient->name << " from the queue.\n";
        front = (front + 1) % capacity;
        count--;
    }

    ~VideoConsultationQueue() {
        while (count > 0) {
            Patient* patient = queue[front];
            delete patient;
            front = (front + 1) % capacity;
            count--;
        }
        delete[] queue;
        cout << "Consultation system cleaned up.\n";
    }
};

int main() {
    VideoConsultationQueue* vcQueue = new VideoConsultationQueue(5);

    vcQueue->addPatient("John Doe", 1);
    vcQueue->addPatient("Alice Smith", 2);
    vcQueue->addPatient("Bob Johnson", 3);

    cout << "\nViewing Current Queue:\n";
    vcQueue->viewQueue();

    vcQueue->startConsultation();
    vcQueue->removePatient();

    cout << "\nViewing Queue after consultation and removal:\n";
    vcQueue->viewQueue();

    vcQueue->addPatient("Jane Brown", 4);
    vcQueue->startConsultation();

    delete vcQueue;
    return 0;
}
