#pragma once
#include <mutex>
#include <unordered_map>
#include <string>
#include <thread>
#include "trip.hpp"
#include "common.hpp"
#include "notificationMgr.hpp"
#include "tripNotFoundException.hpp"
// using namespace std;

class TripManager
{
    static TripManager* tripManagerInstance;
    static mutex mtx;
    NotificationMgr* notificationMgr;
    unordered_map<string, Trip*> completedTrips;
    unordered_map<string, Trip*> inProgressTrips;
    TripManager() {
        NotificationMgr* notificationMgr = NotificationMgr::getNotificationMgr();
    };
    public:
    static TripManager* getTripManagerInstance();
    void addUserForNotificationUpdates(string tripId, User* user);
    string createTrip(Traveler* travler, Location* startLoc,Location* endLoc);
    void startTrip(string tripId);
    void addTravelerCompanion(string tripId, User* travelerCompanion);
    void completeTrip(string tripId);
    void notifyUpdatesToTravelerCompanions(string tripId,string message);
    Trip* getTrip(string tripId);
    vector<string> getAvailableTrips();
};