#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct Message {
    string sender;
    string content;
    Message* next;
};

class ChatSystem {
private:
    Message* head;
    Message* tail;
    
public:
    ChatSystem() {
        head = nullptr;
        tail = nullptr;
    }

    void sendMessage(string sender, string content) {
        Message* newMessage = new Message;
        newMessage->sender = sender;
        newMessage->content = content;
        newMessage->next = nullptr;

        if (tail == nullptr) {
            head = newMessage;
            tail = newMessage;
        } else {
            tail->next = newMessage;
            tail = newMessage;
        }
        cout << sender << " sent: " << content << endl;
    }

    void displayMessages() {
        if (head == nullptr) {
            cout << "No messages to display." << endl;
            return;
        }
        Message* temp = head;
        while (temp != nullptr) {
            cout << temp->sender << ": " << temp->content << endl;
            temp = temp->next;
        }
    }

    void deleteMessage() {
        if (head == nullptr) {
            cout << "No messages to delete." << endl;
            return;
        }
        Message* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) {
            tail = nullptr;
        }
        cout << "Message deleted." << endl;
    }

    void deleteAllMessages() {
        while (head != nullptr) {
            deleteMessage();
        }
        cout << "All messages deleted." << endl;
    }

    ~ChatSystem() {
        deleteAllMessages();
    }
};

int main() {
    ChatSystem* chat = new ChatSystem;

    chat->sendMessage("Alice", "Hello, how are you?");
    chat->sendMessage("Bob", "I'm good, thanks!");
    chat->sendMessage("Alice", "Great to hear!");

    cout << "\nMessages:\n";
    chat->displayMessages();

    chat->deleteMessage();

    cout << "\nMessages after deletion:\n";
    chat->displayMessages();

    chat->deleteAllMessages();

    delete chat;
    return 0;
}
