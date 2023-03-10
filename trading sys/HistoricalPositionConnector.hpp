/*
 * HistoricalPositionConnector.hpp
 *
 * @author: Ming Fu
 */

#pragma once 

#ifndef HISTORICAL_POSITION_CONNECTOR_HPP
#define HISTORICAL_POSITION_CONNECTOR_HPP

using namespace std;

#include "soa.hpp"
#include "BondHistoricalDataService.hpp"
#include "GUIServiceConnector.hpp"
#include "products.hpp"
#include <string>
#include <iostream>

class HistoricalPositionConnector: public Connector<Position<Bond> >{
public:
    // ctor
    HistoricalPositionConnector(){};

	virtual void Subscribe() override{}
	
	virtual void Publish(Position<Bond>& data) override;
};


void HistoricalPositionConnector::Publish(Position<Bond>& data) {
	auto bond = data.GetProduct();
	auto position = data.GetAggregatePosition();
	
    ofstream out;
    out.open("positions.txt",ios::app);
	out << bond.GetProductId() << "," << position << endl;

    return;
}


void BondHistoricalPositionService::PersistData(string persistKey, Position<Bond>& data) {
	auto id=data.GetProduct().GetProductId();
	if(dataMap.find(id)!=dataMap.end())
		dataMap.erase(id);
	dataMap.insert(pair<string,Position<Bond> >(id,data));
	connector->Publish(data);
	return;
}


#endif