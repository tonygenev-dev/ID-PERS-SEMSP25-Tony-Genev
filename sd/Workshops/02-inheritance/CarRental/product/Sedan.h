#pragma once
#include "Vehicle.h"
#include <string>

class Sedan : public Vehicle {
public:
    Sedan(const std::string& manufacturer,
          const std::string& model,
          const std::string& licencePlate,
          int buildYear,
          bool hasTowbar);

    bool HasTowbar() const;

    std::string ToString() const override;
    std::string getType() const override { return "Sedan"; }
    double CalculateRentalCosts(int daysRented, int kilometersDriven) const override;

private:
    bool hasTowbar;
};