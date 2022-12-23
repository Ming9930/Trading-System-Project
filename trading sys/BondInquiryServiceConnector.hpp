/*
 * BondInquiryServiceConnector.hpp
 *
 * @author Ming Fu
 */

#ifndef BOND_INQUIRY_SERVICE_CONNECTOR_HPP		
#define BOND_INQUIRY_SERVICE_CONNECTOR_HPP

using namespace std;

#include "soa.hpp"
#include "BondProductService.hpp"
#include "inquiryservice.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

class BondInquiryService;

class BondInquiryServiceConnector: public Connector<Inquiry<Bond> >{
private:
	BondInquiryService* bondInquiryService;
	BondProductService* bondProductService;

	// transform a string to price
	float TransformStringToPrice(string& s);
public:
	// ctor
	BondInquiryServiceConnector(BondInquiryService* _bondInquiryService, BondProductService* _bondProductService);

	virtual void Publish(Inquiry<Bond>& data) override{} 
	
	virtual void Subscribe() override;   	
	
};

float BondInquiryServiceConnector::TransformStringToPrice(string& s) {
	int n=s.size();
	if(s[n-1]=='+')s[n-1]='4';
	return stoi(s.substr(0, n-4))+stoi(s.substr(n-3,2))/32.0+stoi(s.substr(n-1,1))/256.0;
}


BondInquiryServiceConnector::BondInquiryServiceConnector(BondInquiryService* _bondInquiryService, BondProductService* _bondProductService){
	bondInquiryService=_bondInquiryService;
	bondProductService=_bondProductService;
}

// define void BondInquiryServiceConnector::Subscribe() in BondInquiryService.hpp
#endif