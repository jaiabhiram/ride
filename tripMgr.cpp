#include "tripMgr.hpp"
#include "smsNotificationSender.hpp"
#include <mutex>

TripManager* TripManager::tripManagerInstance = nullptr;
mutex TripManager::mtx;

TripManager* TripManager::getTripManagerInstance()
{
    if(tripManagerInstance == nullptr)
    {
        mtx.lock();
        if(tripManagerInstance == nullptr) {
            tripManagerInstance = new TripManager();
        }
        mtx.unlock();
    }
    return tripManagerInstance;
}

void TripManager::addUserForNotificationUpdates(string tripId, User* user) {
	
	notificationMgr->addNotificationSender(tripId, user->getUserId(), new SMSNotificationSender());
}

string TripManager::createTrip(Traveler* traveler, Location* startLoc,Location* endLoc)
{
    string tripId = to_string(boost::uuids::random_generator()());
    Trip* trip = new Trip(traveler, startLoc, endLoc);
    trip->addEvent(new TripEvent("Trip Created"));
    inProgressTrips[tripId] = trip;
    return(tripId);
}

void TripManager::startTrip(string tripId)
{
    Trip* trip = inProgressTrips[tripId];
    trip->addEvent(new TripEvent("Trip started"));
    trip->setTripStatus(TRIP_STATUS::IN_PROCESS);
}

void TripManager::addTravelerCompanion(string tripId, User* travelerCompanion)
{
    Trip* trip = inProgressTrips[tripId];
    trip->addTravelerCompanion(travelerCompanion);
    addUserForNotificationUpdates(tripId, travelerCompanion);
}

void TripManager:: completeTrip(string tripId)
{
    Trip* trip = inProgressTrips[tripId];
    inProgressTrips.erase(tripId);
    completedTrips[tripId] = trip;
    trip->setTripStatus(TRIP_STATUS::COMPLETED);
    trip->addEvent(new TripEvent("Trip completed"));
    notificationMgr->notify(tripId, "Trip Completed");
}

void TripManager::notifyUpdatesToTravelerCompanions(string tripId,string message)
{
    notificationMgr->notify(tripId, message);
}

Trip* TripManager::getTrip(string tripId)
{
    if(inProgressTrips.count(tripId)) return(inProgressTrips[tripId]);
    else if(completedTrips.count(tripId)) return(completedTrips[tripId]);
    throw TripNotFoundException(tripId);
}

vector<string> TripManager::getAvailableTrips()
{
    vector<string> trips;
    for(auto x : inProgressTrips)
    {
        trips.push_back(x.first);
    }
    return(trips);
}