#include <iostream>
#include <string>
using namespace std;

class Translator {
public:
    virtual void translate(string text) = 0;
};

class EnglishToSpanishTranslator : public Translator {
public:
    void translate(string text) override {
        cout << "Translating to Spanish: " << text << " -> " << "Español" << endl;
    }
};

class EnglishToFrenchTranslator : public Translator {
public:
    void translate(string text) override {
        cout << "Translating to French: " << text << " -> " << "Français" << endl;
    }
};

class EnglishToGermanTranslator : public Translator {
public:
    void translate(string text) override {
        cout << "Translating to German: " << text << " -> " << "Deutsch" << endl;
    }
};

class ConsultationDetails {
private:
    string patientName;
    string doctorName;
    string consultationTime;
    string consultationType;

public:
    ConsultationDetails(string pName, string dName, string cTime, string cType) {
        patientName = pName;
        doctorName = dName;
        consultationTime = cTime;
        consultationType = cType;
    }

    void displayDetails() {
        cout << "Patient Name: " << patientName << endl;
        cout << "Doctor Name: " << doctorName << endl;
        cout << "Consultation Time: " << consultationTime << endl;
        cout << "Consultation Type: " << consultationType << endl;
    }
};

class TelemedicineConsultation {
private:
    ConsultationDetails consultation;
    Translator* translator;

public:
    TelemedicineConsultation(string pName, string dName, string cTime, string cType) 
        : consultation(pName, dName, cTime, cType), translator(nullptr) {}

    void setTranslator(Translator* t) {
        translator = t;
    }

    void performConsultation() {
        consultation.displayDetails();
        cout << "Consultation Details: ";
        if (translator != nullptr) {
            translator->translate("Hello, how can I assist you today?");
        } else {
            cout << "Translation not available.\n";
        }
    }

    ~TelemedicineConsultation() {
        delete translator;
    }
};

class TranslationService {
private:
    Translator* translator;

public:
    TranslationService() : translator(nullptr) {}

    void setTranslator(Translator* t) {
        translator = t;
    }

    void performTranslation(string text) {
        if (translator != nullptr) {
            translator->translate(text);
        } else {
            cout << "No translator set!\n";
        }
    }

    ~TranslationService() {
        delete translator;
    }
};

int main() {
    EnglishToSpanishTranslator* spanishTranslator = new EnglishToSpanishTranslator();
    EnglishToFrenchTranslator* frenchTranslator = new EnglishToFrenchTranslator();
    EnglishToGermanTranslator* germanTranslator = new EnglishToGermanTranslator();

    TelemedicineConsultation consultation1("Alice", "Dr. Smith", "2025-03-03 10:00", "General Consultation");
    consultation1.setTranslator(spanishTranslator);
    consultation1.performConsultation();

    cout << "\n--- Second Consultation ---\n";
    TelemedicineConsultation consultation2("Bob", "Dr. Johnson", "2025-03-03 11:00", "Specialist Consultation");
    consultation2.setTranslator(frenchTranslator);
    consultation2.performConsultation();

    cout << "\n--- Third Consultation ---\n";
    TelemedicineConsultation consultation3("Charlie", "Dr. Brown", "2025-03-03 12:00", "Follow-up Consultation");
    consultation3.setTranslator(germanTranslator);
    consultation3.performConsultation();

    return 0;
}
