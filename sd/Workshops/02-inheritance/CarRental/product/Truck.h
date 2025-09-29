#pragma once

#include "SimpleDate.h"

#include <string>
#include <memory>

using namespace std;

class Truck {
public:
    // Constructor
    Truck(const string& manufacturer, const string& model, const string& licencePlate, int cargoSpace, int maxWeight, int buildYear);
    virtual ~Truck();

    // Getters
    const string& GetManufacturer() const;
    const string& GetModel() const;
    const string& GetLicencePlate() const;
    int GetKilometers() const;
    int GetCargoSpace() const;
    int GetMaxWeight() const;
    bool IsAvailable() const;
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
    int cargoSpace;
    int maxWeight;
    SimpleDate* rentalDate; // nullptr if not rented
    int buildYear;

    double CalculateRentalCosts(int daysRented, int kilometersDriven) const;
};
