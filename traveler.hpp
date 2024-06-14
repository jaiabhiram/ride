#include "user.hpp"
class Traveler : public User
{
    string carNumber;
    vector<string> tripHistory;
    public:
    Traveler(string name, string phoneNumber, string carNumber) : User(name, phoneNumber) {
        this->carNumber = carNumber;
    }
    string getCarNumber()
    {
        return(carNumber);
    }
};