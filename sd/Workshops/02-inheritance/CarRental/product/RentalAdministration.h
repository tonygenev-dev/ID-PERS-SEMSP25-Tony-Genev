#pragma once
#include <vector>
#include <memory>

class Sedan;
class Limousine;
class Truck;
class SimpleDate;
class OffRoad;

using namespace std;

class RentalAdministration {
public:
    // Constructor
    RentalAdministration();

    // Getters for the collections (returns a copy)
    vector<Sedan*> GetSedans() const;
    vector<Limousine*> GetLimousines() const;
    vector<Truck*> GetTrucks() const;
    vector<OffRoad*> GetOffRoads() const;

    // Add vehicles
    void Add(Sedan* sedan);
    void Add(Limousine* limousine);
    void Add(Truck* truck);
    void Add(OffRoad* offRoad);

    // Rent and return vehicles
    bool RentCar(const string& licencePlate, const SimpleDate& rentalDate);
    double ReturnCar(const string& licencePlate, const SimpleDate& returnDate, int kilometers);

private:
    vector<Sedan*> sedans;
    vector<Limousine*> limousines;
    vector<Truck*> trucks;
    vector<OffRoad*> offRoads;
};
