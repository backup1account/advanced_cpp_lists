#ifndef CPP_FUEL_TANK_HPP
#define CPP_FUEL_TANK_HPP

namespace cpplab {
    class FuelTank;
}

class cpplab::FuelTank {
    public:
    FuelTank(unsigned int availableFuel) : availableFuel(availableFuel) {}

    unsigned int refuel(unsigned int desiredFuel) {
        if (desiredFuel <= availableFuel) {
            availableFuel -= desiredFuel;
            return desiredFuel;
        }
        return 0;
    }

    private:
    unsigned int availableFuel;
};

#endif