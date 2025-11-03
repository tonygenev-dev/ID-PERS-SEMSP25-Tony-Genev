#pragma once
#include "SimpleDate.h"
#include <string>

class Vehicle {
protected:
    std::string manufacturer;
    std::string model;
    std::string licencePlate;
    int buildYear;
    int kilometers;
    SimpleDate* rentalDate;
    int seats;

public:
    Vehicle(const std::string& manufacturer,
            const std::string& model,
            const std::string& licencePlate,
            int buildYear,
            int seats);
    virtual ~Vehicle();

    const std::string& GetManufacturer() const;
    const std::string& GetModel() const;
    const std::string& GetLicencePlate() const;
    int GetKilometers() const;
    bool IsAvailable() const;

    virtual bool Rent(const SimpleDate& rentalDate);
    virtual double Return(const SimpleDate& returnDate, int kilometers);

    // Polymorphic interface (must match derived signatures exactly)
    virtual std::string ToString() const = 0;
    virtual std::string getType() const = 0;
    virtual double CalculateRentalCosts(int daysRented, int kilometersDriven) const = 0;
};