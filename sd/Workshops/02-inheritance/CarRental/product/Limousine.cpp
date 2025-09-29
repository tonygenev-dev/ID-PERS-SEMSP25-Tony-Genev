#include "Limousine.h"
#include "SimpleDate.h"
#include <sstream>

// Constructor
Limousine::Limousine(const std::string& manufacturer, const std::string& model, const std::string& licencePlate, bool hasMinibar, int buildYear)
    : manufacturer(manufacturer),
      model(model),
      licencePlate(licencePlate),
      kilometers(0),
      hasMinibar(hasMinibar),
      rentalDate(nullptr),
      buildYear(buildYear)
{}

// Destructor
Limousine::~Limousine() {
    if (rentalDate) {
        delete rentalDate;
        rentalDate = nullptr;
    }
}

// Getters
const std::string& Limousine::GetManufacturer() const { return manufacturer; }
const std::string& Limousine::GetModel() const { return model; }
const std::string& Limousine::GetLicencePlate() const { return licencePlate; }
int Limousine::GetKilometers() const { return kilometers; }
bool Limousine::IsAvailable() const { return rentalDate == nullptr; }
bool Limousine::HasMinibarFunc() const { return hasMinibar; }

// Rent the limousine
bool Limousine::Rent(const SimpleDate& rentalDateInput) {
    if (IsAvailable()) {
        if (rentalDate) delete rentalDate;
        rentalDate = new SimpleDate(rentalDateInput);
        return true;
    }
    return false;
}

// Return the limousine and calculate rental cost
double Limousine::Return(const SimpleDate& returnDateInput, int kilometersInput) {
    if (!IsAvailable() && rentalDate) {
        int daysRented = rentalDate->DaysDifference(returnDateInput);
        int kilometersDriven = kilometersInput - kilometers;

        if (daysRented >= 0 && kilometersDriven >= 0) {
            delete rentalDate;
            rentalDate = nullptr; // Limousine is now available again
            kilometers = kilometersInput;
            return CalculateRentalCosts(daysRented, kilometersDriven);
        }
    }
    return -1.0;
}

// Calculate the price of a rental
double Limousine::CalculateRentalCosts(int daysRented, int kilometersDriven) const {
    const double dayRate = 200.0;
    const double kmRate = 0.25;
    double minibarDayRate = hasMinibar ? 20.0 : 0.0;

    return (dayRate * daysRented) + (kilometersDriven * kmRate)
        + (minibarDayRate * daysRented);
}

// String representation
std::string Limousine::ToString() const {
    std::ostringstream oss;
    oss << "Limousine: "
        << licencePlate << ", "
        << (IsAvailable() ? "available" : "not available") << ", "
        << manufacturer << ", "
        << model << ", "
        << kilometers << ", "
        << (hasMinibar ? "with mini bar" : "without mini bar")
        << ", " << buildYear;
    return oss.str();
}
