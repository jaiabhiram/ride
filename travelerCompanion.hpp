#include "user.hpp"
#include "tripMgr.hpp"
class TravelerCompanion : public User
{
    TripManager* tripManager;
    vector<string> sharedRides;
    public:
    TravelerCompanion(string name, string phoneNumber) : User(name, phoneNumber) {};
};