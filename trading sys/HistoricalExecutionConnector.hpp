/*
 * HistoricalExecutionConnector.hpp
 *
 * @author: Ming Fu
 */

#pragma once 

#ifndef HISTORICAL_EXECUTION_CONNECTOR_HPP
#define HISTORICAL_EXECUTION_CONNECTOR_HPP

using namespace std;

#include "soa.hpp"
#include "BondHistoricalDataService.hpp"
#include "GUIServiceConnector.hpp"
#include "products.hpp"
#include <string>
#include <iostream>

class HistoricalExecutionConnector: public Connector<ExecutionOrder<Bond> >{
public:
    // ctor
    HistoricalExecutionConnector(){};

	virtual void Subscribe() override{}
	
	virtual void Publish(ExecutionOrder<Bond>& data) override;
};


void HistoricalExecutionConnector::Publish(ExecutionOrder<Bond>& data) {
	auto bond=data.GetProduct();

	string orderType;
	switch(data.GetOrderType()) {
		case FOK: orderType = "FOK"; break;
		case MARKET: orderType = "MARKET"; break;
		case LIMIT: orderType = "LIMIT"; break;
		case STOP: orderType = "STOP"; break;
		case IOC: orderType = "IOC"; break;
	}
	
    ofstream out;
    out.open("executions.txt",ios::app);
	out << bond.GetProductId() << "," 
		<< data.GetOrderId() << "," 
		<< (data.GetSide() == BID ? "Bid" : "Ask") << "," 
		<< orderType << ","
		<< (data.IsChildOrder() ? "True" : "False") << "," 
		<< data.GetPrice() << "," 
		<< data.GetVisibleQuantity() << "," 
		<< data.GetHiddenQuantity() << endl;

    return;
}

void BondHistoricalExecutionService::PersistData(string persistKey, ExecutionOrder<Bond>& data){
	auto id=data.GetOrderId();
	if(dataMap.find(id)!=dataMap.end())
		dataMap.erase(id);
	dataMap.insert(pair<string,ExecutionOrder<Bond> >(id,data));
	connector->Publish(data);
	return;
}

#endif