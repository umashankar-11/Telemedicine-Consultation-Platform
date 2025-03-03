#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

template <typename T>
class VoiceCommand {
public:
    virtual void execute(T command) = 0;
};

template <typename T>
class BookAppointmentCommand : public VoiceCommand<T> {
public:
    void execute(T command) override {
        cout << "Booking appointment: " << command << endl;
    }
};

template <typename T>
class CheckHealthStatusCommand : public VoiceCommand<T> {
public:
    void execute(T command) override {
        cout << "Checking health status: " << command << endl;
    }
};

template <typename T>
class StartVideoConsultationCommand : public VoiceCommand<T> {
public:
    void execute(T command) override {
        cout << "Starting video consultation: " << command << endl;
    }
};

template <typename T>
class VoiceCommandInvoker {
private:
    map<string, VoiceCommand<T>*> commands;

public:
    void addCommand(string commandName, VoiceCommand<T>* command) {
        commands[commandName] = command;
    }

    void invokeCommand(string commandName, T command) {
        if (commands.find(commandName) != commands.end()) {
            commands[commandName]->execute(command);
        } else {
            cout << "Command not found!" << endl;
        }
    }
};

template <typename T>
class VoiceRecognitionSystem {
private:
    VoiceCommandInvoker<T> invoker;

public:
    void registerCommand(string commandName, VoiceCommand<T>* command) {
        invoker.addCommand(commandName, command);
    }

    void processVoiceCommand(string commandName, T command) {
        invoker.invokeCommand(commandName, command);
    }
};

template <typename T>
class TelemedicineConsultation {
private:
    VoiceRecognitionSystem<T> system;

public:
    void registerVoiceCommands() {
        BookAppointmentCommand<T>* bookAppointment = new BookAppointmentCommand<T>();
        CheckHealthStatusCommand<T>* checkHealth = new CheckHealthStatusCommand<T>();
        StartVideoConsultationCommand<T>* videoConsultation = new StartVideoConsultationCommand<T>();

        system.registerCommand("Book Appointment", bookAppointment);
        system.registerCommand("Check Health Status", checkHealth);
        system.registerCommand("Start Video Consultation", videoConsultation);
    }

    void handleVoiceCommand(string commandName, T command) {
        system.processVoiceCommand(commandName, command);
    }
};

int main() {
    TelemedicineConsultation<string> consultation;
    consultation.registerVoiceCommands();

    cout << "Voice Command: 'Book Appointment'" << endl;
    consultation.handleVoiceCommand("Book Appointment", "Doctor's Appointment with Dr. Smith at 10 AM");

    cout << "\nVoice Command: 'Check Health Status'" << endl;
    consultation.handleVoiceCommand("Check Health Status", "Patient's Health Data for Alice");

    cout << "\nVoice Command: 'Start Video Consultation'" << endl;
    consultation.handleVoiceCommand("Start Video Consultation", "Patient Alice with Dr. Smith");

    return 0;
}
