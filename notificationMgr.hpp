#pragma once

#include <algorithm>
#include "common.hpp"
#include "iNotificationSender.hpp"
#include "unordered_map"
#include "vector"
#include "mutex"

//This class corresponds to subject in the observer design pattern
//NotificationSender is the observer interface

class NotificationMgr {
	NotificationMgr() {}
	static NotificationMgr* notificationMgrInstance;
	static mutex mtx;
	unordered_map<string, vector<pair<string,INotificationSender*>>> notificationSendersMap;

public:
	static NotificationMgr* getNotificationMgr();
	//register observer
	void addNotificationSender(string tripId, string userId, INotificationSender* notificationSender) {
		if (find(notificationSendersMap[tripId].begin(), notificationSendersMap[tripId].end(), make_pair(userId, notificationSender))
			== notificationSendersMap[tripId].end()) {
			notificationSendersMap[tripId].push_back(make_pair(userId, notificationSender));
		}
	}

	//unregister observer
	void removeNotificationSender(string tripId, string userId, INotificationSender* notificationSender) {
		auto senderPos = find(notificationSendersMap[tripId].begin(),
			notificationSendersMap[tripId].end(), make_pair(userId, notificationSender));
		if (senderPos != notificationSendersMap[tripId].end()) {
			notificationSendersMap[tripId].erase(senderPos);
		}
	}

	//notify Observers
	void notify(string tripId, string message) {
		for (auto sender : notificationSendersMap[tripId])
			sender.second->sendNotification(sender.first, message);
	}

	//notify particular user by a particular method
	void notifyParticularUser(string pUserId, string pMsg, INotificationSender* sender) {
		sender->sendNotification(pUserId, pMsg);
	}
};