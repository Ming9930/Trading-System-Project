/*
 * HistoricalStreamingConnector.hpp
 *
 * @author: Ming Fu
 */

#pragma once 

#ifndef HISTORICAL_STREAMING_CONNECTOR_HPP
#define HISTORICAL_STREAMING_CONNECTOR_HPP

using namespace std;

#include "soa.hpp"
#include "BondHistoricalDataService.hpp"
#include "GUIServiceConnector.hpp"
#include "products.hpp"
#include <string>
#include <iostream>

class HistoricalStreamingConnector: public Connector<PriceStream<Bond> >{
public:
    // ctor
    HistoricalStreamingConnector(){};

	virtual void Subscribe() override{}
	
	virtual void Publish(PriceStream<Bond> & data) override;
};


void HistoricalStreamingConnector::Publish(PriceStream<Bond> & data) {
	auto bond = data.GetProduct();
    auto bidOrder = data.GetBidOrder();
    auto askOrder = data.GetOfferOrder();
	
    ofstream out;
    out.open("streaming.txt",ios::app);
	out << bond.GetProductId() << ","
		<< bidOrder.GetPrice() << "," 
		<< bidOrder.GetVisibleQuantity() << "," 
		<< bidOrder.GetHiddenQuantity() << "," 
		<< askOrder.GetPrice() << "," 
		<< askOrder.GetVisibleQuantity() << "," 
		<< askOrder.GetHiddenQuantity() << endl;

    return;
}


void BondHistoricalStreamingService::PersistData(string persistKey, PriceStream<Bond>& data){
	auto id=data.GetProduct().GetProductId();
	if(dataMap.find(id)!=dataMap.end())
		dataMap.erase(id);
	dataMap.insert(pair<string,PriceStream<Bond> >(id,data));
	connector->Publish(data);
	return;
}

#endif