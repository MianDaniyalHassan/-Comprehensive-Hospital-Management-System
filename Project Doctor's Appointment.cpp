#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  
using namespace std;

class Doctor {
public:
    int id;
    string name;
    string specialization;
    string availableSlots;

    void addDoctor() {
        cout << "Enter Doctor ID: ";
        cin >> id;
        cout << "Enter Doctor Name: ";
        cin >> name;
        cout << "Enter Specialization: ";
        cin >> specialization;
        cout << "Enter Doctor's availability (Mor / Eve / Night / Emergency): ";
        cin >> availableSlots;

        ofstream outFile("doctors.txt", ios::app);
        outFile << id << " " << name << " " << specialization << " " << availableSlots << endl;
        outFile.close();
    }

    void viewDoctors() {
        ifstream inFile("doctors.txt");
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }
};

class Patient {
public:
    int Pat_id;
    string Pat_name;
    string Pat_availableSlots;

    void add_Patients() {
        cout << "Enter Patient ID: ";
        cin >> Pat_id;
        cout << "Enter Patient Name: ";
        cin >> Pat_name;
        cout << "Enter Patient's timing (Mor / Eve / Night / Emergency): ";
        cin >> Pat_availableSlots;

        ofstream outFile("Patient.txt", ios::app);
        outFile << Pat_id << " " << Pat_name << " " << Pat_availableSlots << endl;
        outFile.close();
    }

    void view_Patients() {
        ifstream inFile("Patient.txt");
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }
};

class Appointment {
public:
    int docId;
    int patId;
    string appointmentTime;

    void bookAppointment(Doctor& doctor, Patient& patient) {
        cout << "Enter Doctor ID: ";
        cin >> docId;
        cout << "Enter Patient ID: ";
        cin >> patId;
        cout << "Enter Appointment Time (Mor / Eve / Night / Emergency): ";
        cin >> appointmentTime;

        ofstream outFile("appointments.txt", ios::app);
        outFile << docId << " " << patId << " " << appointmentTime << endl;
        outFile.close();

        cout << "Appointment booked successfully!" << endl;
    }

    void viewAppointments() {
        ifstream inFile("appointments.txt");
        string line;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }



void cancelAppointment(int docId, int patId) {
    ifstream inFile("appointments.txt");
    ofstream tempFile("temp.txt");

    bool found = false;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        int id1, id2;
        
        // Read two integers from the stream
        if (!(ss >> id1 >> id2)) {
            cerr << "Warning: Invalid appointment data: " << line << endl;
            continue;
        }

        if (!(id1 == docId && id2 == patId)) {
            tempFile << line << endl;
        } else {
            found = true;
        }
    }

    inFile.close();
    tempFile.close();

    remove("appointments.txt");
    rename("temp.txt", "appointments.txt");

    if (found) {
        cout << "Appointment canceled successfully!" << endl;
    } else {
        cout << "No such appointment found." << endl;
    }
}

};

int main() {
    Doctor doc;
    Patient pat;
    Appointment appoint;
    int choice;
    while (true) {
        cout << "1. Add Doctor\n2. View Doctors\n3. Add Patient\n4. View Patients\n5. Book Appointment\n6. View Appointments\n7. Cancel Appointment\n8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                doc.addDoctor();
                break;
            case 2:
                doc.viewDoctors();
                break;
            case 3:
                pat.add_Patients();
                break;
            case 4:
                pat.view_Patients();
                break;
            case 5:
                appoint.bookAppointment(doc, pat);
                break;
            case 6:
                appoint.viewAppointments();
                break;
            case 7:
                int docId, patId;
                cout << "Enter Doctor ID: ";
                cin >> docId;
                cout << "Enter Patient ID: ";
                cin >> patId;
                appoint.cancelAppointment(docId, patId);
                break;
            case 8:
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}

