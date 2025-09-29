#include "Truck.h"
#include "SimpleDate.h"
#include <sstream>

// Constructor
Truck::Truck(const std::string& manufacturer, const std::string& model, const std::string& licencePlate, int cargoSpace, int maxWeight, int buildYear)
    : manufacturer(manufacturer),
      model(model),
      licencePlate(licencePlate),
      kilometers(0),
      cargoSpace(cargoSpace),
      maxWeight(maxWeight),
      rentalDate(nullptr),
      buildYear(buildYear)
{}

// Destructor
Truck::~Truck() {
    if (rentalDate) {
        delete rentalDate;
        rentalDate = nullptr;
    }
}

// Getters
const std::string& Truck::GetManufacturer() const { return manufacturer; }
const std::string& Truck::GetModel() const { return model; }
const std::string& Truck::GetLicencePlate() const { return licencePlate; }
int Truck::GetKilometers() const { return kilometers; }
int Truck::GetCargoSpace() const { return cargoSpace; }
int Truck::GetMaxWeight() const { return maxWeight; }
bool Truck::IsAvailable() const { return rentalDate == nullptr; }

// Rent the truck
bool Truck::Rent(const SimpleDate& rentalDateInput) {
    if (IsAvailable()) {
        if (rentalDate) delete rentalDate;
        rentalDate = new SimpleDate(rentalDateInput);
        return true;
    }
    return false;
}

// Return the truck and calculate rental cost
double Truck::Return(const SimpleDate& returnDateInput, int kilometersInput) {
    if (!IsAvailable() && rentalDate) {
        int daysRented = rentalDate->DaysDifference(returnDateInput);
        int kilometersDriven = kilometersInput - kilometers;

        if (daysRented >= 0 && kilometersDriven >= 0) {
            delete rentalDate;
            rentalDate = nullptr; // Truck is now available again
            kilometers = kilometersInput;
            return CalculateRentalCosts(daysRented, kilometersDriven);
        }
    }
    return -1.0;
}

// Calculate the price of a rental
double Truck::CalculateRentalCosts(int daysRented, int kilometersDriven) const {
    const double dayRate = 400.0;
    const double kmRate = 0.39;
    return (dayRate * daysRented) + (kilometersDriven * kmRate);
}

// String representation
std::string Truck::ToString() const {
    std::ostringstream oss;
    oss << "Truck: "
        << licencePlate << ", "
        << (IsAvailable() ? "available" : "not available") << ", "
        << manufacturer << ", "
        << model << ", "
        << kilometers << ", "
        << cargoSpace << ", "
        << maxWeight
        << ", " << buildYear;
    return oss.str();
}
