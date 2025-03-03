#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class HealthRiskAssessment {
public:
    virtual double calculateRisk() = 0;
    virtual void displayRiskLevel() = 0;
    virtual ~HealthRiskAssessment() {}
};

class AgeRisk : public HealthRiskAssessment {
private:
    int age;

public:
    AgeRisk(int a) : age(a) {}

    double calculateRisk() override {
        if (age < 20) return 0.1;
        else if (age < 40) return 0.2;
        else if (age < 60) return 0.3;
        else return 0.5;
    }

    void displayRiskLevel() override {
        double risk = calculateRisk();
        cout << "Age Risk Level: ";
        if (risk <= 0.2) cout << "Low" << endl;
        else if (risk <= 0.4) cout << "Moderate" << endl;
        else cout << "High" << endl;
    }
};

class BMI_Risk : public HealthRiskAssessment {
private:
    double bmi;

public:
    BMI_Risk(double b) : bmi(b) {}

    double calculateRisk() override {
        if (bmi < 18.5) return 0.1;
        else if (bmi < 24.9) return 0.2;
        else if (bmi < 29.9) return 0.3;
        else return 0.5;
    }

    void displayRiskLevel() override {
        double risk = calculateRisk();
        cout << "BMI Risk Level: ";
        if (risk <= 0.2) cout << "Low" << endl;
        else if (risk <= 0.4) cout << "Moderate" << endl;
        else cout << "High" << endl;
    }
};

class SmokingRisk : public HealthRiskAssessment {
private:
    bool smokes;

public:
    SmokingRisk(bool s) : smokes(s) {}

    double calculateRisk() override {
        if (!smokes) return 0.1;
        else return 0.6;
    }

    void displayRiskLevel() override {
        double risk = calculateRisk();
        cout << "Smoking Risk Level: ";
        if (risk <= 0.2) cout << "Low" << endl;
        else if (risk <= 0.4) cout << "Moderate" << endl;
        else cout << "High" << endl;
    }
};

class ExerciseRisk : public HealthRiskAssessment {
private:
    int exerciseHours;

public:
    ExerciseRisk(int hours) : exerciseHours(hours) {}

    double calculateRisk() override {
        if (exerciseHours >= 5) return 0.1;
        else if (exerciseHours >= 3) return 0.3;
        else return 0.5;
    }

    void displayRiskLevel() override {
        double risk = calculateRisk();
        cout << "Exercise Risk Level: ";
        if (risk <= 0.2) cout << "Low" << endl;
        else if (risk <= 0.4) cout << "Moderate" << endl;
        else cout << "High" << endl;
    }
};

class HealthProfile {
private:
    vector<HealthRiskAssessment*> risks;

public:
    ~HealthProfile() {
        for (auto risk : risks) {
            delete risk;
        }
    }

    void addRisk(HealthRiskAssessment* risk) {
        risks.push_back(risk);
    }

    void displayAllRisks() {
        for (auto risk : risks) {
            risk->displayRiskLevel();
        }
    }

    double calculateTotalRisk() {
        double totalRisk = 0;
        for (auto risk : risks) {
            totalRisk += risk->calculateRisk();
        }
        return totalRisk;
    }
};

template <typename T>
class VoiceCommand {
public:
    virtual void execute(T command) = 0;
};

template <typename T>
class HealthRiskAssessmentCommand : public VoiceCommand<T> {
private:
    HealthProfile& profile;

public:
    HealthRiskAssessmentCommand(HealthProfile& p) : profile(p) {}

    void execute(T command) override {
        cout << "Health Risk Assessment for patient: " << command << endl;
        profile.displayAllRisks();
        cout << "Total Risk: " << profile.calculateTotalRisk() << endl;
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
    void registerVoiceCommands(HealthProfile& profile) {
        HealthRiskAssessmentCommand<T>* healthRiskCommand = new HealthRiskAssessmentCommand<T>(profile);
        system.registerCommand("Assess Health Risk", healthRiskCommand);
    }

    void handleVoiceCommand(string commandName, T command) {
        system.processVoiceCommand(commandName, command);
    }
};

int main() {
    HealthProfile profile;

    // Patient's Health Data
    AgeRisk* ageRisk = new AgeRisk(45);
    BMI_Risk* bmiRisk = new BMI_Risk(27);
    SmokingRisk* smokingRisk = new SmokingRisk(true);
    ExerciseRisk* exerciseRisk = new ExerciseRisk(2);

    profile.addRisk(ageRisk);
    profile.addRisk(bmiRisk);
    profile.addRisk(smokingRisk);
    profile.addRisk(exerciseRisk);

    TelemedicineConsultation<string> consultation;
    consultation.registerVoiceCommands(profile);

    cout << "Voice Command: 'Assess Health Risk'" << endl;
    consultation.handleVoiceCommand("Assess Health Risk", "Alice");

    return 0;
}
