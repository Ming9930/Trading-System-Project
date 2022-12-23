/**
 * GUIService.hpp
 *
 * @author: Ming Fu
 */ 

#pragma once

#ifndef GUI_SERVICE_HPP
#define GUI_SERVICE_HPP

#include "boost/date_time/posix_time/posix_time.hpp"
#include "products.hpp"

using namespace std;
using namespace boost::posix_time;

#include "pricingservice.hpp"
#include "soa.hpp"
#include <boost/date_time.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

class GUIServiceConnector;

class PriceWithTimeStamp: public Price<Bond>{
private:
	ptime timeStamp;
public:
	PriceWithTimeStamp(ptime _timeStamp,Price<Bond> _price)
	:Price<Bond>(_price){
		timeStamp=_timeStamp;
	}
	
	ptime GetTimeStamp(){
		return timeStamp;
	}
};

class GUIService:public PricingService<Bond> {
private:
	GUIServiceConnector* gUIServiceConnector;
	ptime lastSendTime;
	time_duration throtteTime;
	vector< ServiceListener<Price<Bond> >* > listenerList;
	map<string, Price<Bond> > priceMap;
public:
	// ctor
	GUIService(GUIServiceConnector* _gUIServiceConnecto54r);
	
	void SendToThrottle(Price<Bond>& data);
	
	virtual Price<Bond>& GetData(string id) override { return priceMap.at(id); }
	
	virtual void OnMessage(Price<Bond> &data) override{}
	
	virtual void AddListener(ServiceListener<Price<Bond> > *listener) override{}
	
	virtual const vector< ServiceListener<Price<Bond> >* >& GetListeners() const override { return listenerList; }
};

GUIService::GUIService(GUIServiceConnector* _gUIServiceConnector){
	gUIServiceConnector=_gUIServiceConnector;
	throtteTime=millisec(3);
	lastSendTime=microsec_clock::local_time();
}

// define void GUIService::SendToThrottle(Price<Bond>& data) in GUIServiceCOnnector.hpp


#endif