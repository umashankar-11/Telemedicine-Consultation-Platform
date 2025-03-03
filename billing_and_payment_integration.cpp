#include <iostream>
#include <string>
using namespace std;

class BillingSystem {
public:
    
    double calculateBill(double consultationFee) {
        return consultationFee;
    }

    
    double calculateBill(double consultationFee, double discountPercent) {
        double discountAmount = (consultationFee * discountPercent) / 100;
        return consultationFee - discountAmount;
    }

    
    double calculateBill(double consultationFee, double taxPercent, double discountPercent) {
        double discountAmount = (consultationFee * discountPercent) / 100;
        double discountedFee = consultationFee - discountAmount;
        double taxAmount = (discountedFee * taxPercent) / 100;
        return discountedFee + taxAmount;
    }

    
    double calculateBill(int numberOfConsultations, double consultationFee) {
        return numberOfConsultations * consultationFee;
    }

   
    void processPayment(double amount) {
        cout << "Processing payment of $" << amount << "...\n";
        cout << "Payment successful.\n";
    }

    
    void processPayment(double amount, double discountPercent) {
        double discountedAmount = amount - (amount * discountPercent) / 100;
        cout << "Processing payment of $" << discountedAmount << " (after " << discountPercent << "% discount)...\n";
        cout << "Payment successful.\n";
    }

    
    void processPayment(double amount, double taxPercent, double discountPercent) {
        double discountedAmount = amount - (amount * discountPercent) / 100;
        double taxAmount = (discountedAmount * taxPercent) / 100;
        double finalAmount = discountedAmount + taxAmount;
        cout << "Processing payment of $" << finalAmount << " (after " << discountPercent << "% discount and " << taxPercent << "% tax)...\n";
        cout << "Payment successful.\n";
    }
};

class TelemedicineConsultation {
private:
    string patientName;
    string consultationType;
    double consultationFee;

public:
    TelemedicineConsultation(string name, string type, double fee) {
        patientName = name;
        consultationType = type;
        consultationFee = fee;
    }

    void displayDetails() {
        cout << "Patient Name: " << patientName << endl;
        cout << "Consultation Type: " << consultationType << endl;
        cout << "Consultation Fee: $" << consultationFee << endl;
    }

    void billConsultation(BillingSystem &billing, double discount = 0, double tax = 0) {
        if (discount == 0 && tax == 0) {
            double totalBill = billing.calculateBill(consultationFee);
            cout << "Total Bill: $" << totalBill << endl;
            billing.processPayment(totalBill);
        } else if (tax == 0) {
            double totalBill = billing.calculateBill(consultationFee, discount);
            cout << "Total Bill (after discount): $" << totalBill << endl;
            billing.processPayment(totalBill, discount);
        } else {
            double totalBill = billing.calculateBill(consultationFee, tax, discount);
            cout << "Total Bill (after discount and tax): $" << totalBill << endl;
            billing.processPayment(totalBill, tax, discount);
        }
    }

    void billMultipleConsultations(BillingSystem &billing, int numConsultations, double discount = 0, double tax = 0) {
        double totalBill = billing.calculateBill(numConsultations, consultationFee);
        if (discount == 0 && tax == 0) {
            cout << "Total Bill for " << numConsultations << " consultations: $" << totalBill << endl;
            billing.processPayment(totalBill);
        } else if (tax == 0) {
            totalBill = billing.calculateBill(numConsultations, consultationFee, discount);
            cout << "Total Bill for " << numConsultations << " consultations (after discount): $" << totalBill << endl;
            billing.processPayment(totalBill, discount);
        } else {
            totalBill = billing.calculateBill(numConsultations, consultationFee, tax, discount);
            cout << "Total Bill for " << numConsultations << " consultations (after discount and tax): $" << totalBill << endl;
            billing.processPayment(totalBill, tax, discount);
        }
    }
};

int main() {
    BillingSystem billing;

    TelemedicineConsultation consultation1("Alice Brown", "General Checkup", 50.0);
    consultation1.displayDetails();
    cout << "\n Billing Consultation (No Discount, No Tax) \n";
    consultation1.billConsultation(billing);

    cout << "\n Billing Consultation (With Discount) \n";
    consultation1.billConsultation(billing, 10.0);

    cout << "\n Billing Consultation (With Discount and Tax) \n";
    consultation1.billConsultation(billing, 10.0, 5.0);

    cout << "\n Billing Multiple Consultations (No Discount, No Tax) \n";
    consultation1.billMultipleConsultations(billing, 3);

    cout << "\n Billing Multiple Consultations (With Discount) \n";
    consultation1.billMultipleConsultations(billing, 3, 5.0);

    cout << "\n Billing Multiple Consultations (With Discount and Tax) \n";
    consultation1.billMultipleConsultations(billing, 3, 5.0, 8.0);

    return 0;
}
