#include "user.hpp"

User::User(const string& name, const string& phoneNumber)
    : name(name), phoneNumber(phoneNumber) {}

string User::getName() const {
    return name;
}

string User::getPhoneNumber() const {
    return phoneNumber;
}

string User::getUserId() const {
    return("tempUserId");
}