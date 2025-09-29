#pragma once
#include "Vehicle.h"

class Sedan : public Vehicle {
    public:
        Sedan(const std::string& manufacturer, const std::string& model, 
              int licencePlate, bool hasTowbar);

        bool HasTowbar() const;

        // Override rental cost calculation
        virtual std::string ToString() const override;

    protected:
        virtual double CalculateRentalCosts(int daysRented, 
                                            int kilometersDriven) const override;

    private:
        bool hasTowbar;
};
