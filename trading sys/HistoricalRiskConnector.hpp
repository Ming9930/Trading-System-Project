/*
 * HistoricalRiskConnector.hpp
 *
 * @author: Ming Fu
 */

#pragma once 

#ifndef HISTORICAL_RISK_CONNECTOR_HPP
#define HISTORICAL_RISK_CONNECTOR_HPP

using namespace std;

#include "soa.hpp"
#include "BondHistoricalDataService.hpp"
#include "GUIServiceConnector.hpp"
#include "products.hpp"
#include <string>
#include <iostream>

class HistoricalRiskConnector: public Connector<PV01<Bond> >{
public:
    // ctor
    HistoricalRiskConnector(){};

	virtual void Subscribe() override{}
	
	// publish position
	virtual void Publish(PV01<Bond>& data) override;
};


void HistoricalRiskConnector::Publish(PV01<Bond>& data) {
	auto bond = data.GetProduct();
	auto risk = data.GetPV01();
	
    ofstream out;
	out.open("risk.txt", ios::app);
	out << bond.GetProductId() << "," << risk << endl;

    return;
}

void BondHistoricalRiskService::PersistData(string persistKey, PV01<Bond>& data){
	auto id=data.GetProduct().GetProductId();
	if(dataMap.find(id)!=dataMap.end())
		dataMap.erase(id);
	dataMap.insert(pair<string,PV01<Bond> >(id,data));
	connector->Publish(data);
	return;
}



#endif