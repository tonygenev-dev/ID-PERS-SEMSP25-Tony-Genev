#include "OffRoad.h"
#include <sstream>

OffRoad::OffRoad(const std::string& manufacturer,
                 const std::string& model,
                 const std::string& licencePlate,
                 bool hasFourWheelDrive,
                 int buildYear)
    : Vehicle(manufacturer, model, licencePlate, buildYear, 5) // assume 5 seats
    , hasFourWheelDrive_(hasFourWheelDrive)
{
}

bool OffRoad::HasFourWheelDrive() const {
    return hasFourWheelDrive_;
}

double OffRoad::CalculateRentalCosts(int daysRented, int kilometersDriven) const {
    const double dayRate = 170.0;
    const double kmRate = 0.35;
    const double fourWheelSurchargePerDay = hasFourWheelDrive_ ? 15.0 : 0.0;
    return (daysRented * dayRate) + (kilometersDriven * kmRate) + (daysRented * fourWheelSurchargePerDay);
}

std::string OffRoad::ToString() const {
    std::ostringstream ss;
    ss << getType() << " [" << GetLicencePlate() << "] "
       << GetManufacturer() << " " << GetModel()
       << " | km: " << GetKilometers()
       << " | " << (hasFourWheelDrive_ ? "4WD" : "2WD")
       << " | " << (IsAvailable() ? "available" : "rented");
    return ss.str();
}