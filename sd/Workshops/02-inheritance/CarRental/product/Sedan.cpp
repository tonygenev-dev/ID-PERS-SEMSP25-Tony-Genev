#include "Sedan.h"
#include "SimpleDate.h"
#include <sstream>

// Constructor
Sedan::Sedan(const std::string& manufacturer, const std::string& model, const std::string& licencePlate, bool hasTowbar, int buildYear)
    : manufacturer(manufacturer),
      model(model),
      licencePlate(licencePlate),
      kilometers(0),
      hasTowbar(hasTowbar),
      rentalDate(nullptr),
      buildYear(buildYear)
{}

// Destructor
Sedan::~Sedan() {
    if (rentalDate) {
        delete rentalDate;
        rentalDate = nullptr;
    }
}

// Getters
const std::string& Sedan::GetManufacturer() const { return manufacturer; }
const std::string& Sedan::GetModel() const { return model; }
const std::string& Sedan::GetLicencePlate() const { return licencePlate; }
int Sedan::GetKilometers() const { return kilometers; }
bool Sedan::IsAvailable() const { return rentalDate == nullptr; }
bool Sedan::HasTowbarFunc() const { return hasTowbar; }

// Rent the sedan
bool Sedan::Rent(const SimpleDate& rentalDateInput) {
    if (IsAvailable()) {
        if (rentalDate) delete rentalDate;
        rentalDate = new SimpleDate(rentalDateInput);
        return true;
    }
    return false;
}

// Return the sedan and calculate rental cost
double Sedan::Return(const SimpleDate& returnDateInput, int kilometersInput) {
    if (!IsAvailable() && rentalDate) {
        int daysRented = rentalDate->DaysDifference(returnDateInput);
        int kilometersDriven = kilometersInput - kilometers;

        if (daysRented >= 0 && kilometersDriven >= 0) {
            delete rentalDate;
            rentalDate = nullptr; // Sedan is now available again
            kilometers = kilometersInput;
            return CalculateRentalCosts(daysRented, kilometersDriven);
        }
    }
    return -1.0;
}

// Calculate the price of a rental
double Sedan::CalculateRentalCosts(int daysRented, int kilometersDriven) const {
    const double dayRate = 80.0;
    const double kmRate = 0.19;
    double towbarDayRate = hasTowbar ? 5.0 : 0.0;

    return (dayRate * daysRented) + (kilometersDriven * kmRate)
        + (towbarDayRate * daysRented);
}

// String representation
std::string Sedan::ToString() const {
    std::ostringstream oss;
    oss << "Sedan: "
        << licencePlate << ", "
        << (IsAvailable() ? "available" : "not available") << ", "
        << manufacturer << ", "
        << model << ", "
        << kilometers << ", "
        << (hasTowbar ? "with towbar" : "without towbar")
        << ", " << buildYear;
    return oss.str();
}
