#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class BusTicket {
public:
    char name[50];
    int seatNumber;
    float fare;

    void input() {
        cout << "Enter passenger name: ";
        cin.ignore(); // Clear the buffer
        cin.getline(name, sizeof(name));
        cout << "Enter seat number: ";
        cin >> seatNumber;
        cout << "Enter fare: ";
        cin >> fare;
    }

    void display() {
        cout << "Passenger: " << name << "\tSeat Number: " << seatNumber << "\tFare: $" << fixed << setprecision(2) << fare << endl;
    }
};

void bookTicket() {
    ofstream outFile("bus_tickets.txt", ios::app | ios::binary);

    BusTicket ticket;
    ticket.input();

    outFile.write(reinterpret_cast<char*>(&ticket), sizeof(ticket));

    cout << "Ticket booked successfully!" << endl;

    outFile.close();
}

void displayTickets() {
    ifstream inFile("bus_tickets.txt", ios::binary);

    if (!inFile) {
        cout << "No tickets booked yet." << endl;
        return;
    }

    BusTicket ticket;

    cout << "------ Booked Tickets ------" << endl;

    while (inFile.read(reinterpret_cast<char*>(&ticket), sizeof(ticket))) {
        ticket.display();
    }

    inFile.close();
}

int main() {
    int choice;

    do {
        cout << "\n1. Book Ticket\n2. Display Tickets\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bookTicket();
                break;
            case 2:
                displayTickets();
                break;
            case 3:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
