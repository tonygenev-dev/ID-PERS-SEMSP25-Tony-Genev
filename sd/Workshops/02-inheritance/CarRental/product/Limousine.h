#pragma once
#include "Vehicle.h"
#include <string>

class Limousine : public Vehicle {
public:
    // Signature must match Limousine.cpp exactly (manufacturer, model, licencePlate, buildYear, withMiniBar)
    Limousine(const std::string& manufacturer,
              const std::string& model,
              const std::string& licencePlate,
              int buildYear,
              bool withMiniBar);

    bool HasMinibar() const;

    // Vehicle interface implementations
    std::string ToString() const override;
    std::string getType() const override { return "Limousine"; }
    double CalculateRentalCosts(int daysRented, int kilometersDriven) const override;

private:
    bool hasMiniBar;
};