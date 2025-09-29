#pragma once

#include "SimpleDate.h"

#include <string>
#include <memory>

using namespace std;

class OffRoad { 
public:
    // Constructor
    OffRoad(const string& manufacturer, const string& model, const string& licencePlate, bool hasFourWheelDrive, int buildYear);    
    virtual ~OffRoad();

    // Getters
    const string& GetManufacturer() const;
    const string& GetModel() const;
    const string& GetLicencePlate() const;
    int GetKilometers() const;
    bool IsAvailable() const;
    bool HasFourWheelDriveFunc() const; // Avoids name clash with member
    int GetBuildYear() const;

    // Rental functions
    bool Rent(const SimpleDate& rentalDate);
    double Return(const SimpleDate& returnDate, int kilometers);

    // String representation
    string ToString() const;

private:
    string manufacturer;
    string model;
    string licencePlate;
    int kilometers;
    bool hasFourWheelDrive;
    SimpleDate* rentalDate; // nullptr if not rented
    int buildYear;

    double CalculateRentalCosts(int daysRented, int kilometersDriven) const;
};