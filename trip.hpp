#pragma once
#include "user.hpp"
#include "common.hpp"
#include "traveler.hpp"
#include "tripevent.hpp"
class Trip
{
    string tripId;
    Traveler* traveler;
    vector<User*> travelerCompanions;
    TRIP_STATUS status;
    Location* startLocation;
    Location* endLocation;
    time_t startTime;
    vector<TripEvent*> events;
    // time.....
    public:
    Trip(Traveler* driver, Location* startLoc, Location* endLoc);
    void addTravelerCompanion(User* travelerCompanion);
    void setTripStatus(TRIP_STATUS status);
    void getTripDetails();
    void addEvent(TripEvent* event);
};