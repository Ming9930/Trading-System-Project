/*
 * HistoricalAllInquiriesConnector.hpp
 *
 * @author: Ming Fu
 */

#pragma once 

#ifndef HISTORICAL_ALL_INQUIRIES_CONNECTOR_HPP
#define HISTORICAL_ALL_INQUIRIES_CONNECTOR_HPP

using namespace std;

#include "soa.hpp"
#include "BondHistoricalDataService.hpp"
#include "GUIServiceConnector.hpp"
#include "products.hpp"
#include <string>
#include <iostream>

class HistoricalAllInquiriesConnector: public Connector<Inquiry<Bond> >{
public:
    // ctor
    HistoricalAllInquiriesConnector(){};

	virtual void Subscribe() override{}
	
	// publish position
	virtual void Publish(Inquiry<Bond> & data) override;
};


void HistoricalAllInquiriesConnector::Publish(Inquiry<Bond> & data) {
	auto inquiry_id = data.GetInquiryId();
	auto id = data.GetProduct().GetProductId();
	auto price = data.GetPrice();
	auto quantity = data.GetQuantity();	
	string side = (data.GetSide() == BUY ? "BUY" : "SELL");
	
	auto state = data.GetState();
	string state_;
	switch(state){
	case RECEIVED:state_ = "RECEIVED"; break;
	case QUOTED:state_ = "QUOTED"; break;
	case DONE:state_ = "DONE"; break;
	case REJECTED:state_ = "REJECTED"; break;
	case CUSTOMER_REJECTED:state_ = "CUSTOMER_REJECTED"; break;
	}

    ofstream out;
	out.open("allinquiries.txt", ios::app);
	out << inquiry_id << "," << id << "," 
		<< price << "," << quantity 
		<< "," << side << "," << state_
		<< endl;

    return;
}

void BondHistoricalAllInquiriesService::PersistData(string persistKey, Inquiry<Bond>& data){
	auto id=data.GetInquiryId();
	if(dataMap.find(id)!=dataMap.end())
		dataMap.erase(id);
	dataMap.insert(pair<string,Inquiry<Bond> >(id,data));

	connector->Publish(data);
	return;
}

#endif