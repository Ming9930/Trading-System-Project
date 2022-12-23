/**
 * BondPricingConnector.hpp
 * 
 * @author: Ming Fu
 */

#pragma once

#ifndef BOND_PRICING_SERVICE_CONNECTOR_HPP
#define BOND_PRICING_SERVICE_CONNECTOR_HPP

#include "soa.hpp"
#include "pricingservice.hpp"
#include "BondProductService.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

class BondPricingService;

class BondPricingServiceConnector: public Connector<Price<Bond> > {
private:
	BondPricingService* bondPricingService;
	BondProductService* bondProductService;

	// transform a string to price
	float TransformStringToPrice(string& s);
public:
	// ctor
	BondPricingServiceConnector(BondPricingService* _bondPricingService,BondProductService* _bondProductService);

	// read data
	virtual void Subscribe() override;

	virtual void Publish(Price<Bond>& data) override;
};


float BondPricingServiceConnector::TransformStringToPrice(string& s) {
	int n=s.size();
	if(s[n-1]=='+')s[n-1]='4';
	return stoi(s.substr(0, n-4))+stoi(s.substr(n-3,2))/32.0+stoi(s.substr(n-1,1))/256.0;
}


BondPricingServiceConnector::BondPricingServiceConnector(BondPricingService* _bondPricingService,BondProductService* _bondProductService) {
	bondPricingService=_bondPricingService;
	bondProductService=_bondProductService;
}

//void BondPricingServiceConnector::Subscribe() defined in BondPricingServce.hpp

void BondPricingServiceConnector::Publish(Price<Bond>& data) {
	return;
}
#endif
