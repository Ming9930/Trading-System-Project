/**
 * BondTradingBookingServiceConnector.hpp
 *
 * @author: Ming Fu
 */ 
#pragma once

#ifndef BOND_TRADE_BOOKING_SERVICE_CONNECTOR_HPP
#define BOND_TRADE_BOOKING_SERVICE_CONNECTOR_HPP

using namespace std;

#include "soa.hpp"
#include "BondTradeBookingService.hpp"
#include "tradebookingservice.hpp"
#include "BondProductService.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

class BondTradeBookingService;

class BondTradeBookingServiceConnector: public Connector<Trade<Bond> > {
private:
	BondTradeBookingService* bondTradeBookingService;
	BondProductService* bondProductService;

	// transform a string to price
	float TransformStringToPrice(string& s);
public:
	// ctor
	BondTradeBookingServiceConnector(BondTradeBookingService* _bondTradeBookingService, BondProductService* _bondProductService);

	virtual void Publish(Trade<Bond>& data) override {};
	
	virtual void Subscribe() override;
};

float BondTradeBookingServiceConnector::TransformStringToPrice(string& s) {
	int n=s.size();
	if(s[n-1]=='+')s[n-1]='4';
	return stoi(s.substr(0, n-4))+stoi(s.substr(n-3,2))/32.0+stoi(s.substr(n-1,1))/256.0;
}

BondTradeBookingServiceConnector::BondTradeBookingServiceConnector
(BondTradeBookingService* _bondTradeBookingService, BondProductService* _bondProductService) {
	bondTradeBookingService=_bondTradeBookingService;
	bondProductService= _bondProductService;
}

// define void BondTradeBookingServiceConnector::Subscribe() in BondTradeBookingService.hpp
	

#endif
