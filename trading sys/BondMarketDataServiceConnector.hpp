/**
 * BondMarketDataServiceConnector.hpp
 *
 * @author Ming Fu
 */ 

#ifndef BOND_MARKET_DATA_SERVICE_CONNECTOR_HPP
#define BOND_MARKET_DATA_SERVICE_CONNECTOR_HPP

using namespace std; 

#include "soa.hpp"
#include "marketdataservice.hpp"
#include "BondProductService.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>


class BondMarketDataService;

class BondMarketDataServiceConnector: public Connector<OrderBook<Bond> >{
private:
	BondMarketDataService* bondMarketDataService;
    BondProductService* bondProductService;
	
	// transform a string to price
	float TransformStringToPrice(string& s);
public:
	// ctor
	BondMarketDataServiceConnector(BondMarketDataService* _bondMarketDataService, BondProductService* _bondProductService);

    virtual void Publish(OrderBook<Bond>& data) override;   
	
    virtual void Subscribe() override;   
};

float BondMarketDataServiceConnector::TransformStringToPrice(string& s) {
	int n=s.size();
	if(s[n-1]=='+')s[n-1]='4';
	return stoi(s.substr(0, n-4))+stoi(s.substr(n-3,2))/32.0+stoi(s.substr(n-1,1))/256.0;
}

BondMarketDataServiceConnector::BondMarketDataServiceConnector(BondMarketDataService* _bondMarketDataService, BondProductService* _bondProductService){
	bondMarketDataService=_bondMarketDataService;
	bondProductService=_bondProductService;
}

void BondMarketDataServiceConnector::Publish(OrderBook<Bond>& data){
	return;
}

// void BondMarketDataServiceConnector::Subscribe() defines in BondMarketDataService.hpp

#endif