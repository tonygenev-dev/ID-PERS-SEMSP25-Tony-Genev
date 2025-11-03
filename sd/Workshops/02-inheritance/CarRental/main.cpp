#include <iostream>
#include <string>
#include <limits>
#include "product/RentalAdministration.h"
#include "product/Sedan.h"
#include "product/Truck.h"
#include "product/Limousine.h"
#include "product/SimpleDate.h"
#include "product/OffRoad.h"

using namespace std;

void ClearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

SimpleDate InputDate(const string& prompt) {
    int day, month, year;
    cout << prompt << " (DD MM YYYY): ";
    while (!(cin >> day >> month >> year)) {
        cout << "Invalid input. Try again: ";
        ClearInput();
    }
    ClearInput();
    return SimpleDate(day, month, year);
}

void AddVehicleMenu(RentalAdministration& admin) {
    cout << "Add Vehicle:\n";
    cout << "1. Sedan\n2. Truck\n3. Limousine\n4. OffRoad\nChoice: ";
    int choice;
    cin >> choice;
    ClearInput();

    string manufacturer, model;
    string licencePlate;

    cout << "Manufacturer: ";
    getline(cin, manufacturer);
    cout << "Model: ";
    getline(cin, model);
    cout << "Licence Plate (number): ";
    while (!(cin >> licencePlate)) {
        cout << "Invalid input. Enter a number: ";
        ClearInput();
    }
    ClearInput();

    int buildYear;
    cout << "Build Year: ";
    while (!(cin >> buildYear)) {
        cout << "Invalid input. Enter a number: ";
        ClearInput();
    }
    ClearInput();

    if (choice == 1) {
        char towbar;
        cout << "Has towbar? (y/n): ";
        cin >> towbar;
        ClearInput();
        bool hasTowbar = (towbar == 'y' || towbar == 'Y');
        
        admin.Add(new Sedan(manufacturer, model, licencePlate, hasTowbar, buildYear));
        
        cout << "Sedan added!\n";
    } else if (choice == 2) {
        int cargoSpace, maxWeight;
        cout << "Cargo Space (liters): ";
        while (!(cin >> cargoSpace)) {
            cout << "Invalid input. Enter a number: ";
            ClearInput();
        }
        cout << "Max Weight (kg): ";
        while (!(cin >> maxWeight)) {
            cout << "Invalid input. Enter a number: ";
            ClearInput();
        }
        ClearInput();
        
        admin.Add(new Truck(manufacturer, model, licencePlate, cargoSpace, maxWeight, buildYear));
        
        cout << "Truck added!\n";
    } else if (choice == 3) {
        char minibar;
        cout << "Has minibar? (y/n): ";
        cin >> minibar;
        ClearInput();
        bool hasMinibar = (minibar == 'y' || minibar == 'Y');
        
        admin.Add(new Limousine(manufacturer, model, licencePlate, hasMinibar, buildYear));
        
        cout << "Limousine added!\n";
    }else if (choice == 4)
    {
        bool hasFourWheelDrive;
        cout << "Has four-wheel drive? (y/n): ";
        char fourWheelDriveInput;
        cin >> fourWheelDriveInput;
        ClearInput();
        hasFourWheelDrive = (fourWheelDriveInput == 'y' || fourWheelDriveInput == 'Y');

        admin.Add(new OffRoad(manufacturer, model, licencePlate, hasFourWheelDrive, buildYear));

        cout << "OffRoad added!\n";
    }
     else {
        cout << "Invalid choice.\n";
    }
}

void DisplayAdministration(const RentalAdministration& admin) {
    auto all = admin.GetAllVehicles();
    std::cout << "\nTotal vehicles: " << all.size() << "\n";
    if (all.empty()) {
        std::cout << "No vehicles available.\n\n";
        return;
    }

    // print each vehicle using its ToString()
    for (auto* v : all) {
        if (v) std::cout << v->ToString() << '\n';
    }
    std::cout << std::endl;
}

void RentVehicleMenu(RentalAdministration& admin) {
    string licencePlate;
    cout << "Enter licence plate of vehicle to rent: ";
    while (!(cin >> licencePlate)) {
        cout << "Invalid input. Enter a number: ";
        ClearInput();
    }
    ClearInput();
    SimpleDate rentalDate = InputDate("Enter rental date");
    if (admin.RentCar(licencePlate, rentalDate)) {
        cout << "Vehicle rented successfully!\n";
    } else {
        cout << "Vehicle not available or not found.\n";
    }
}

void ReturnVehicleMenu(RentalAdministration& admin) {
    string licencePlate;
    int kilometers;
    cout << "Enter licence plate of vehicle to return: ";
    while (!(cin >> licencePlate)) {
        cout << "Invalid input. Enter a number: ";
        ClearInput();
    }
    ClearInput();
    SimpleDate returnDate = InputDate("Enter return date");
    cout << "Enter total kilometers on return: ";
    while (!(cin >> kilometers)) {
        cout << "Invalid input. Enter a number: ";
        ClearInput();
    }
    ClearInput();
    double cost = admin.ReturnCar(licencePlate, returnDate, kilometers);
    if (cost >= 0) {
        cout << "Vehicle returned. Rental cost: " << cost << endl;
    } else {
        cout << "Return failed. Check input and rental state.\n";
    }
}

int main() {
    RentalAdministration admin;
    while (true) {
        cout << "\n--- Car Rental Administration ---\n";
        cout << "1. Add vehicle\n";
        cout << "2. Display all vehicles\n";
        cout << "3. Rent a vehicle\n";
        cout << "4. Return a vehicle\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        int option;
        cin >> option;
        ClearInput();

        switch (option) {
            case 1:
                AddVehicleMenu(admin);
                break;
            case 2:
                DisplayAdministration(admin);
                break;
            case 3:
                RentVehicleMenu(admin);
                break;
            case 4:
                ReturnVehicleMenu(admin);
                break;
            case 5:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid option. Try again.\n";
        }
    }
}
