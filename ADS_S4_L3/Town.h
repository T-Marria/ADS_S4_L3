#include <iostream>
using namespace std;

class Town {
    string name;
    size_t population;

public:
    Town() : name(std::string()), population(0) { }

    Town(const char* name, const size_t population) : name(name), population(population) { }

    Town(const Town& rhs) {
        name = rhs.name;
        population = rhs.population;
    }

    bool operator== (const Town& rhs) const {
        return name == rhs.name;
    }


    std::string get_name() const {
        return name;
    }

    size_t get_population() const {
        return population;
    }

    void print_town() const {
        std::cout << "Name of town: " << name << "\n";
        std::cout << "Population of town: " << population << "\n\n";
    }
};


enum type_road {
    federal = 0,
    regional,
    local,
    private_road,
};

class Road {

    std::string name;
    type_road _type;
    double _length;
    double _price;

public:
    Road() : name(std::string()), _type(local), _length(0), _price(0) { }

    Road(const char* name, const type_road type, const double length, const double price) : name(name), _type(type),
        _length(length), _price(price) { }

    Road(const Road& rhs) {
        name = rhs.name;
        _type = rhs._type;
        _length = rhs._length;
        _price = rhs._price;
    }

    std::string get_name() const {
        return name;
    }

    type_road get_type() const {
        return _type;
    }

    double get_length() const {
        return _length;
    }

    double get_price() const {
        return _price;
    }

    explicit operator double() const {
        double result = 0;
        switch (_type) {
        case type_road::federal:
            result += _length;
            break;
        case type_road::regional:
            result += _length * 1;
            break;
        case type_road::local:
            result += _length * 1;
            break;
        case type_road::private_road:
            result += _length * 1;
            break;
        default:
            throw std::logic_error("Invalid roadType enum value");
        }
        return result;
    }

};


template<typename TRoad>
struct defaultWeightConverter {
    double operator()(const TRoad& road) const {
        return static_cast<double>(road);
    }
};