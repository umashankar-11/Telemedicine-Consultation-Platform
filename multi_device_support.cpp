#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Device {
private:
    string deviceName;
    string deviceType;
    bool isActive;

public:
    Device(string name, string type) : deviceName(name), deviceType(type), isActive(false) {}

    void activateDevice() {
        isActive = true;
        cout << deviceName << " (" << deviceType << ") is now active." << endl;
    }

    void deactivateDevice() {
        isActive = false;
        cout << deviceName << " (" << deviceType << ") is now inactive." << endl;
    }

    void displayStatus() const {
        cout << deviceName << " (" << deviceType << ") is " 
             << (isActive ? "active" : "inactive") << "." << endl;
    }

    string getDeviceName() const {
        return deviceName;
    }

    string getDeviceType() const {
        return deviceType;
    }

    bool getDeviceStatus() const {
        return isActive;
    }
};

class MultiDeviceSupport {
private:
    vector<Device> devices;

public:
    void addDevice(const Device& device) {
        devices.push_back(device);
        cout << "Device " << device.getDeviceName() << " added." << endl;
    }

    void removeDevice(const string& deviceName) {
        for (auto it = devices.begin(); it != devices.end(); ++it) {
            if (it->getDeviceName() == deviceName) {
                devices.erase(it);
                cout << "Device " << deviceName << " removed." << endl;
                return;
            }
        }
        cout << "Device " << deviceName << " not found!" << endl;
    }

    void activateDevice(const string& deviceName) {
        for (auto& device : devices) {
            if (device.getDeviceName() == deviceName) {
                device.activateDevice();
                return;
            }
        }
        cout << "Device " << deviceName << " not found!" << endl;
    }

    void deactivateDevice(const string& deviceName) {
        for (auto& device : devices) {
            if (device.getDeviceName() == deviceName) {
                device.deactivateDevice();
                return;
            }
        }
        cout << "Device " << deviceName << " not found!" << endl;
    }

    void displayAllDevices() const {
        if (devices.empty()) {
            cout << "No devices available." << endl;
            return;
        }
        for (const auto& device : devices) {
            device.displayStatus();
        }
    }

    void displayActiveDevices() const {
        bool foundActive = false;
        for (const auto& device : devices) {
            if (device.getDeviceStatus()) {
                device.displayStatus();
                foundActive = true;
            }
        }
        if (!foundActive) {
            cout << "No active devices." << endl;
        }
    }

    void displayInactiveDevices() const {
        bool foundInactive = false;
        for (const auto& device : devices) {
            if (!device.getDeviceStatus()) {
                device.displayStatus();
                foundInactive = true;
            }
        }
        if (!foundInactive) {
            cout << "No inactive devices." << endl;
        }
    }
};

class User {
protected:
    string name;
    string role;

public:
    User(string userName, string userRole) : name(userName), role(userRole) {}

    string getName() const {
        return name;
    }

    string getRole() const {
        return role;
    }

    virtual void startConsultation() = 0;
};

class Patient : public User {
private:
    MultiDeviceSupport deviceManager;

public:
    Patient(string userName) : User(userName, "Patient") {}

    void addDevice(const Device& device) {
        deviceManager.addDevice(device);
    }

    void startConsultation() override {
        cout << name << " is starting the consultation." << endl;
    }

    void displayDevices() {
        deviceManager.displayAllDevices();
    }
};

class Doctor : public User {
private:
    MultiDeviceSupport deviceManager;

public:
    Doctor(string userName) : User(userName, "Doctor") {}

    void addDevice(const Device& device) {
        deviceManager.addDevice(device);
    }

    void startConsultation() override {
        cout << name << " is starting the consultation." << endl;
    }

    void displayDevices() {
        deviceManager.displayAllDevices();
    }
};

template <typename T>
class TelemedicineConsultation {
private:
    vector<User*> users;

public:
    void addUser(User* user) {
        users.push_back(user);
        cout << user->getName() << " (" << user->getRole() << ") added to the platform." << endl;
    }

    void startConsultation() {
        for (auto& user : users) {
            user->startConsultation();
        }
    }

    void addDeviceToUser(const string& userName, const Device& device) {
        for (auto& user : users) {
            if (user->getName() == userName) {
                if (user->getRole() == "Patient") {
                    dynamic_cast<Patient*>(user)->addDevice(device);
                } else if (user->getRole() == "Doctor") {
                    dynamic_cast<Doctor*>(user)->addDevice(device);
                }
                return;
            }
        }
        cout << "User " << userName << " not found!" << endl;
    }

    void displayUserDevices(const string& userName) {
        for (auto& user : users) {
            if (user->getName() == userName) {
                if (user->getRole() == "Patient") {
                    dynamic_cast<Patient*>(user)->displayDevices();
                } else if (user->getRole() == "Doctor") {
                    dynamic_cast<Doctor*>(user)->displayDevices();
                }
                return;
            }
        }
        cout << "User " << userName << " not found!" << endl;
    }
};

int main() {
    TelemedicineConsultation<string> platform;

    Patient* patient1 = new Patient("Alice");
    Doctor* doctor1 = new Doctor("Dr. John");

    platform.addUser(patient1);
    platform.addUser(doctor1);

    platform.addDeviceToUser("Alice", Device("Laptop", "Computing"));
    platform.addDeviceToUser("Dr. John", Device("Smartphone", "Mobile"));

    platform.startConsultation();

    platform.displayUserDevices("Alice");
    platform.displayUserDevices("Dr. John");

    platform.addDeviceToUser("Alice", Device("Tablet", "Mobile"));
    platform.addDeviceToUser("Dr. John", Device("Smartwatch", "Wearable"));

    platform.displayUserDevices("Alice");
    platform.displayUserDevices("Dr. John");

    return 0;
}
