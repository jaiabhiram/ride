#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
using namespace std;
// #include "Ride.h"

class User {
protected:
    string userId;
    string name;
    string phoneNumber;
public:
    User(const string& name, const string& phoneNumber);
    // virtual ~User() = default;

    string getName() const;
    string getPhoneNumber() const;
    string getUserId() const;

    virtual void displayRole() const = 0;
};

#endif // USER_H
