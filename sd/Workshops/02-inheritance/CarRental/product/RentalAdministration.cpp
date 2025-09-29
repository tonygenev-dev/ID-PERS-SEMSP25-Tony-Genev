#include "RentalAdministration.h"
#include "Sedan.h"
#include "Limousine.h"
#include "Truck.h"
#include "SimpleDate.h"
#include "OffRoad.h"

// Constructor
RentalAdministration::RentalAdministration() {}

// Getters (returns a copy of the pointers)
vector<Sedan*> RentalAdministration::GetSedans() const {
    return sedans;
}

vector<Limousine*> RentalAdministration::GetLimousines() const {
    return limousines;
}

vector<Truck*> RentalAdministration::GetTrucks() const {
    return trucks;
}

vector<OffRoad*> RentalAdministration::GetOffRoads() const {
    return offRoads;
}

// Add vehicles
void RentalAdministration::Add(Sedan* sedan) {
    if (sedan != nullptr) {
        sedans.push_back(sedan);
    }
}

void RentalAdministration::Add(Limousine* limousine) {
    if (limousine != nullptr) {
        limousines.push_back(limousine);
    }
}

void RentalAdministration::Add(Truck* truck) {
    if (truck != nullptr) {
        trucks.push_back(truck);
    }
}

void RentalAdministration::Add(OffRoad* offRoad) {
    if (offRoad != nullptr) {
        offRoads.push_back(offRoad);
    }
}

// Rent a car by licence plate
bool RentalAdministration::RentCar(const string& licencePlate, const SimpleDate& rentalDate) {
    // Try to find the car with the given licence plate. Is it a Sedan?
    for (auto sedan : sedans) {
        if (sedan->GetLicencePlate() == licencePlate) {
            return sedan->Rent(rentalDate);
        }
    }
    // Try Limousine
    for (auto limousine : limousines) {
        if (limousine->GetLicencePlate() == licencePlate) {
            return limousine->Rent(rentalDate);
        }
    }
    // Try Truck
    for (auto truck : trucks) {
        if (truck->GetLicencePlate() == licencePlate) {
            return truck->Rent(rentalDate);
        }
    }
    // Try OffRoad
    for (auto offRoad : offRoads) {
        if (offRoad->GetLicencePlate() == licencePlate) {
            return offRoad->Rent(rentalDate);
        }
    }
    return false; // Not found
}

// Return a car by licence plate
double RentalAdministration::ReturnCar(const string& licencePlate, const SimpleDate& returnDate, int kilometers) {
    // Try to find the car with the given licence plate. Is it a Sedan?
    for (auto sedan : sedans) {
        if (sedan->GetLicencePlate() == licencePlate) {
            return sedan->Return(returnDate, kilometers);
        }
    }
    // Try Limousine
    for (auto limousine : limousines) {
        if (limousine->GetLicencePlate() == licencePlate) {
            return limousine->Return(returnDate, kilometers);
        }
    }
    // Try Truck
    for (auto truck : trucks) {
        if (truck->GetLicencePlate() == licencePlate) {
            return truck->Return(returnDate, kilometers);
        }
    }
    // Try OffRoad
    for (auto offRoad : offRoads) {
        if (offRoad->GetLicencePlate() == licencePlate) {
            return offRoad->Return(returnDate, kilometers);
        }
    }
    return -1.0; // Not found
}
