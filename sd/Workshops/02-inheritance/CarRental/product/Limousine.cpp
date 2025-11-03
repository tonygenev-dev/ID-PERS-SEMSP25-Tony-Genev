#include "Limousine.h"
#include <sstream>

Limousine::Limousine(const std::string& manufacturer,
                     const std::string& model,
                     const std::string& licencePlate,
                     int buildYear,               // buildYear first (match Limousine.h)
                     bool withMiniBar)            // then the bool (match Limousine.h)
    : Vehicle(manufacturer, model, licencePlate, buildYear, 4)
    , hasMiniBar(withMiniBar)         // use the exact member name from Limousine.h
{
}

bool Limousine::HasMinibar() const {
    return hasMiniBar;                 // use same member name
}

double Limousine::CalculateRentalCosts(int daysRented, int kilometersDriven) const {
    const double base = 120.0;
    const double kmRate = 0.25;
    const double minibarDayRate = hasMiniBar ? 20.0 : 0.0;
    return (base * daysRented) + (kmRate * kilometersDriven) + (minibarDayRate * daysRented);
}

std::string Limousine::ToString() const {
    std::stringstream ss;
    ss << getType() << " [" << GetLicencePlate() << "] "
       << GetManufacturer() << " " << GetModel()
       << " | km: " << GetKilometers()
       << " | minibar: " << (hasMiniBar ? "yes" : "no");
    return ss.str();
}