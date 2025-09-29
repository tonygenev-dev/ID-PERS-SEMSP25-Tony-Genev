#include "OffRoad.h"
#include "SimpleDate.h"
#include <sstream>

// Constructor
OffRoad::OffRoad(const std::string& manufacturer, const std::string& model, const std::string& licencePlate, bool hasFourWheelDrive, int buildYear)
    : manufacturer(manufacturer),
      model(model),
      licencePlate(licencePlate),
      kilometers(0),
      hasFourWheelDrive(hasFourWheelDrive),
      rentalDate(nullptr),
      buildYear(buildYear)
{}

// Destructor
OffRoad::~OffRoad() {
    if (rentalDate) {
        delete rentalDate;
        rentalDate = nullptr;
    }
}

// Getters
const std::string& OffRoad::GetManufacturer() const { return manufacturer; }
const std::string& OffRoad::GetModel() const { return model; }
const std::string& OffRoad::GetLicencePlate() const { return licencePlate; }
int OffRoad::GetKilometers() const { return kilometers; }
bool OffRoad::IsAvailable() const { return rentalDate == nullptr; }
bool OffRoad::HasFourWheelDriveFunc() const { return hasFourWheelDrive; }
int OffRoad::GetBuildYear() const { return buildYear; }

// Rent the off-road vehicle
bool OffRoad::Rent(const SimpleDate& rentalDateInput) {
    if (IsAvailable()) {
        if (rentalDate) delete rentalDate;
        rentalDate = new SimpleDate(rentalDateInput);
        return true;
    }
    return false;
}

// Return the off-road vehicle and calculate rental cost
double OffRoad::Return(const SimpleDate& returnDateInput, int kilometersInput) {
    if (!IsAvailable() && rentalDate) {
        int daysRented = rentalDate->DaysDifference(returnDateInput);
        int kilometersDriven = kilometersInput - kilometers;

        if (daysRented >= 0 && kilometersDriven >= 0) {
            delete rentalDate;
            rentalDate = nullptr; // Off-road vehicle is now available again
            kilometers = kilometersInput;
            return CalculateRentalCosts(daysRented, kilometersDriven);
        }
    }
    return -1.0;
}

// Calculate the price of a rental
double OffRoad::CalculateRentalCosts(int daysRented, int kilometersDriven) const {
    const double dayRate = 170.0;
    const double kmRate = 0.35;
    return (daysRented * dayRate) + (kilometersDriven * kmRate);
}

// String representation    
std::string OffRoad::ToString() const {
    std::ostringstream oss;
    oss << "OffRoad: " 
        << licencePlate << ", "
        << (IsAvailable() ? "available" : "not available") << ", "
        << manufacturer << ", "
        << model << ", "
        << kilometers << ", "
        << (hasFourWheelDrive ? "4WD" : "2WD")
        << ", " << buildYear;
    return oss.str();
}