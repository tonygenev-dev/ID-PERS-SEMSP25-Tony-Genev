#pragma once

#include "SimpleDate.h"

#include <string>
#include <memory>

class Sedan {
public:
    // Creates a sedan
    Sedan(const string& manufacturer, const string& model, const string& licencePlate, bool hasTowbar, int buildYear);
    virtual ~Sedan();

    // Getters
    const string& GetManufacturer() const;
    const string& GetModel() const;
    const string& GetLicencePlate() const;
    int GetKilometers() const;
    bool IsAvailable() const;
    bool HasTowbarFunc() const; // 'HasTowbar' is a member, so method renamed
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
    bool hasTowbar;
    SimpleDate* rentalDate;
    int buildYear; 

    double CalculateRentalCosts(int daysRented, int kilometersDriven) const;
};
