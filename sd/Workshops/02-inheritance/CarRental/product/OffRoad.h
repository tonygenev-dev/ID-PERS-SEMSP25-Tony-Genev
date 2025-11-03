#pragma once
#include "Vehicle.h"
#include <string>

class OffRoad : public Vehicle {
public:
    // Matches usage in main: (manufacturer, model, licencePlate, hasFourWheelDrive, buildYear)
    OffRoad(const std::string& manufacturer,
           const std::string& model,
           const std::string& licencePlate,
           bool hasFourWheelDrive,
           int buildYear);

    bool HasFourWheelDrive() const;

    // Vehicle interface
    std::string ToString() const override;
    std::string getType() const override { return "OffRoad"; }
    double CalculateRentalCosts(int daysRented, int kilometersDriven) const override;

private:
    bool hasFourWheelDrive_;
};