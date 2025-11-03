#pragma once
#include <vector>
#include <string>

class Vehicle;
class Sedan;
class Limousine;
class Truck;
class OffRoad;
class SimpleDate;

class RentalAdministration {
public:
    RentalAdministration();
    ~RentalAdministration();

    void Add(Vehicle* vehicle);
    bool RentCar(const std::string& licencePlate, const SimpleDate& rentalDate);
    double ReturnCar(const std::string& licencePlate, const SimpleDate& returnDate, int kilometers);

    std::vector<Sedan*> GetSedans() const;
    std::vector<Limousine*> GetLimousines() const;
    std::vector<Truck*> GetTrucks() const;
    std::vector<OffRoad*> GetOffRoads() const;

    // convenience: return all vehicles
    std::vector<Vehicle*> GetAllVehicles() const;

private:
    std::vector<Vehicle*> vehicles;
};