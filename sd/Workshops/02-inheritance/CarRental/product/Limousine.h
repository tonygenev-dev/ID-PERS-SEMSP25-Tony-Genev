#pragma once

#include "SimpleDate.h"

#include <string>
#include <memory>

using namespace std;

class Limousine {
public:
    // Constructor
    Limousine(const string& manufacturer, const string& model, const string& licencePlate, bool hasMinibar, int buildYear);
    virtual ~Limousine();

    // Getters
    const string& GetManufacturer() const;
    const string& GetModel() const;
    const string& GetLicencePlate() const;
    int GetKilometers() const;
    bool IsAvailable() const;
    bool HasMinibarFunc() const; // Avoids name clash with member
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
    bool hasMinibar;
    SimpleDate* rentalDate; // nullptr if not rented
    int buildYear;

    double CalculateRentalCosts(int daysRented, int kilometersDriven) const;
};
