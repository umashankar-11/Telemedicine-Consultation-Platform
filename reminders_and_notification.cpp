#include <iostream>
#include <string>
using namespace std;

struct Notification {
    string message;
    int priority;
    Notification(string msg, int prio) : message(msg), priority(prio) {}
};

class NotificationQueue {
private:
    Notification** queue;
    int front, rear, capacity, count;

public:
    NotificationQueue(int cap) {
        capacity = cap;
        queue = new Notification*[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    void addNotification(string message, int priority) {
        if (count == capacity) {
            cout << "Queue is full. Cannot add new notification.\n";
            return;
        }
        rear = (rear + 1) % capacity;
        queue[rear] = new Notification(message, priority);
        count++;
        cout << "Notification added: " << message << " with priority " << priority << endl;
    }

    void sendNotification() {
        if (count == 0) {
            cout << "No notifications to send.\n";
            return;
        }
        Notification* notification = queue[front];
        cout << "Sending notification: " << notification->message << " with priority " << notification->priority << endl;
        front = (front + 1) % capacity;
        count--;
    }

    void viewNotifications() {
        if (count == 0) {
            cout << "No notifications in the queue.\n";
            return;
        }
        cout << "Notifications in the queue:\n";
        int idx = front;
        for (int i = 0; i < count; i++) {
            cout << "Message: " << queue[idx]->message << " | Priority: " << queue[idx]->priority << endl;
            idx = (idx + 1) % capacity;
        }
    }

    void removeNotification() {
        if (count == 0) {
            cout << "No notifications to remove.\n";
            return;
        }
        Notification* notification = queue[front];
        cout << "Removing notification: " << notification->message << endl;
        front = (front + 1) % capacity;
        count--;
    }

    ~NotificationQueue() {
        while (count > 0) {
            Notification* notification = queue[front];
            delete notification;
            front = (front + 1) % capacity;
            count--;
        }
        delete[] queue;
        cout << "Notification system cleaned up.\n";
    }
};

int main() {
    NotificationQueue* nQueue = new NotificationQueue(5);

    nQueue->addNotification("Appointment reminder: Dr. Smith at 10:00 AM", 1);
    nQueue->addNotification("Payment due for subscription", 2);
    nQueue->addNotification("Meeting reminder: Team meeting at 3:00 PM", 1);
    nQueue->addNotification("New message from Alice", 3);
    nQueue->addNotification("Password change reminder", 1);

    cout << "\nViewing Current Notifications:\n";
    nQueue->viewNotifications();

    nQueue->sendNotification();
    nQueue->removeNotification();

    cout << "\nViewing Notifications after sending and removing:\n";
    nQueue->viewNotifications();

    nQueue->addNotification("New promotion available", 2);
    nQueue->sendNotification();

    delete nQueue;
    return 0;
}
