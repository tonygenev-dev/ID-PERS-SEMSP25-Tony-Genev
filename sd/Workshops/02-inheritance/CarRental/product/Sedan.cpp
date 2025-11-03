#include "Sedan.h"
#include <sstream>

// Constructor: note parameter order matches Vehicle args (buildYear before seats)
Sedan::Sedan(const std::string& manufacturer,
             const std::string& model,
             const std::string& licencePlate,
             int buildYear,
             bool hasTowbar)
    : Vehicle(manufacturer, model, licencePlate, buildYear, 5) // sedans have 5 seats
    , hasTowbar(hasTowbar)
{
}

bool Sedan::HasTowbar() const {
    return hasTowbar;
}

std::string Sedan::ToString() const {
    std::stringstream ss;
    ss << "Sedan: " << GetManufacturer() << " " << GetModel()
       << " | Plate: " << GetLicencePlate()
       << " | Year: " << /*buildYear*/ /* no direct getter for buildYear in this version */ 0
       << " | Km: " << GetKilometers()
       << " | Towbar: " << (hasTowbar ? "Yes" : "No");
    return ss.str();
}

double Sedan::CalculateRentalCosts(int daysRented, int kilometersDriven) const {
    const double baseRate = 50.0;
    const double kmRate = 0.20;
    double cost = (daysRented * baseRate) + (kilometersDriven * kmRate);
    if (hasTowbar) cost += 10.0 * daysRented;
    return cost;
}