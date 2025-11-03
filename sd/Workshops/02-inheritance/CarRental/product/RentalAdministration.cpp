#include "RentalAdministration.h"
#include "Vehicle.h"
#include "Sedan.h"
#include "Limousine.h"
#include "Truck.h"
#include "OffRoad.h"
#include "SimpleDate.h"
#include <algorithm>
#include <iostream>

RentalAdministration::RentalAdministration() = default;

RentalAdministration::~RentalAdministration() {
    for (auto* v : vehicles) delete v;
    vehicles.clear();
}

void RentalAdministration::Add(Vehicle* vehicle) {
    if (vehicle) {
        vehicles.push_back(vehicle);
        std::cout << "[DEBUG] Added vehicle: " << vehicle->GetLicencePlate() << "\n";
    }
}

bool RentalAdministration::RentCar(const std::string& licencePlate,
                                   const SimpleDate& rentalDate)
{
    for (auto* v : vehicles) {
        if (v->GetLicencePlate() == licencePlate) {
            return v->Rent(rentalDate);
        }
    }
    return false;
}

double RentalAdministration::ReturnCar(const std::string& licencePlate,
                                       const SimpleDate& returnDate,
                                       int kilometers)
{
    for (auto* v : vehicles) {
        if (v->GetLicencePlate() == licencePlate) {
            return v->Return(returnDate, kilometers);
        }
    }
    return -1.0;
}

std::vector<Sedan*> RentalAdministration::GetSedans() const {
    std::vector<Sedan*> out;
    for (auto* v : vehicles) if (auto* s = dynamic_cast<Sedan*>(v)) out.push_back(s);
    return out;
}

std::vector<Limousine*> RentalAdministration::GetLimousines() const {
    std::vector<Limousine*> out;
    for (auto* v : vehicles) if (auto* l = dynamic_cast<Limousine*>(v)) out.push_back(l);
    return out;
}

std::vector<Truck*> RentalAdministration::GetTrucks() const {
    std::vector<Truck*> out;
    for (auto* v : vehicles) if (auto* t = dynamic_cast<Truck*>(v)) out.push_back(t);
    return out;
}

std::vector<OffRoad*> RentalAdministration::GetOffRoads() const {
    std::vector<OffRoad*> out;
    for (auto* v : vehicles) if (auto* o = dynamic_cast<OffRoad*>(v)) out.push_back(o);
    return out;
}

std::vector<Vehicle*> RentalAdministration::GetAllVehicles() const {
    return vehicles;
}