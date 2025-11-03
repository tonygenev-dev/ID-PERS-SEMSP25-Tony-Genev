#pragma once
#include "Vehicle.h"
#include <string>

class Truck : public Vehicle {
public:
    Truck(const std::string& manufacturer,
          const std::string& model,
          const std::string& licencePlate,
          double cargoSpace,
          int maxWeight,
          int buildYear);

    // accessors declared here (were missing)
    double GetCargoSpace() const;
    int GetMaxWeight() const;

    std::string ToString() const override;
    std::string getType() const override { return "Truck"; }
    double CalculateRentalCosts(int daysRented, int kilometersDriven) const override;

private:
    double cargoSpace;
    int maxWeight;
};