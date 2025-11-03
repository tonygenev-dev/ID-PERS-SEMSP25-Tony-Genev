#include "Truck.h"
#include <sstream>

Truck::Truck(const std::string& manufacturer,
             const std::string& model,
             const std::string& licencePlate,
             double cargoSpace,
             int maxWeight,
             int buildYear)
    : Vehicle(manufacturer, model, licencePlate, buildYear, 2) // assume 2 seats for trucks
    , cargoSpace(cargoSpace)
    , maxWeight(maxWeight)
{
}

double Truck::GetCargoSpace() const {
    return cargoSpace;
}

int Truck::GetMaxWeight() const {
    return maxWeight;
}

double Truck::CalculateRentalCosts(int daysRented, int kilometersDriven) const {
    // Example pricing:
    // - base daily rate higher for trucks
    // - per-km rate
    // - overweight surcharge per day if heavy truck
    const double dayRate = 120.0;
    const double kmRate = 0.30;
    const double heavySurchargePerDay = (maxWeight > 3000) ? 30.0 : 0.0;

    double cost = (dayRate * daysRented) + (kilometersDriven * kmRate) + (heavySurchargePerDay * daysRented);
    return cost;
}

std::string Truck::ToString() const {
    std::stringstream ss;
    ss << getType() << " [" << GetLicencePlate() << "] "
       << GetManufacturer() << " " << GetModel()
       << " | built: " << /* no public getter for buildYear in Vehicle */ 0
       << " | km: " << GetKilometers()
       << " | cargo m^3: " << cargoSpace
       << " | max kg: " << maxWeight
       << " | " << (IsAvailable() ? "available" : "rented");
    return ss.str();
}