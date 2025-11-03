#include "Vehicle.h"
#include <sstream>

Vehicle::Vehicle(const std::string& manufacturer,
                 const std::string& model,
                 const std::string& licencePlate,
                 int buildYear,
                 int seats)
    : manufacturer(manufacturer)
    , model(model)
    , licencePlate(licencePlate)
    , buildYear(buildYear)
    , kilometers(0)
    , rentalDate(nullptr)
    , seats(seats)
{
}

Vehicle::~Vehicle() {
    if (rentalDate) {
        delete rentalDate;
        rentalDate = nullptr;
    }
}

const std::string& Vehicle::GetManufacturer() const {
    return manufacturer;
}

const std::string& Vehicle::GetModel() const {
    return model;
}

const std::string& Vehicle::GetLicencePlate() const {
    return licencePlate;
}

int Vehicle::GetKilometers() const {
    return kilometers;
}

bool Vehicle::IsAvailable() const {
    return rentalDate == nullptr;
}

// Default rent implementation: set rentalDate if available
bool Vehicle::Rent(const SimpleDate& rd) {
    if (!IsAvailable()) return false;
    rentalDate = new SimpleDate(rd);
    return true;
}

// Default return: compute days, update kilometers and calculate price via virtual CalculateRentalCosts
double Vehicle::Return(const SimpleDate& returnDate, int newKilometers) {
    if (IsAvailable() || !rentalDate) return -1.0; // not rented

    // assume SimpleDate has a DaysDifference method: days from rentalDate to returnDate
    int days = rentalDate->DaysDifference(returnDate);
    int driven = newKilometers - kilometers;
    if (days < 0 || driven < 0) {
        // invalid
        return -1.0;
    }

    // clear rental state
    delete rentalDate;
    rentalDate = nullptr;

    // update kilometers
    kilometers = newKilometers;

    // call derived class cost calculation
    return CalculateRentalCosts(days, driven);
}