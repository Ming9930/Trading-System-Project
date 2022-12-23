/**
 * BondPricingService.hpp
 * get data from prices.txt and publish into the trading system
 * 
 * @author: Ming Fu
 */ 
#pragma once

#ifndef BOND_PRICING_SERVICE_HPP
#define BOND_PRICING_SERVICE_HPP

#include "pricingservice.hpp"
#include "BondPricingServiceConnector.hpp"
#include "products.hpp"
#include "soa.hpp"
#include <map>
#include <vector>


using namespace std;

class BondPricingService: public PricingService<Bond>{
private:
	map<string, Price<Bond> > priceMap;
	vector<ServiceListener<Price<Bond> >* > listenerList;
public:
	// ctor
	BondPricingService();
	
	// given id return bond price
	virtual Price<Bond>& GetData(string id) override;
	
	// add bond prices 
	virtual void OnMessage(Price<Bond> &data) override;
	
	// add BondAlgoStreamingServiceListeners
	virtual void AddListener(ServiceListener<Price<Bond> > *listener) override;
	
	// get BondAlgoStreamingServiceListeners
	virtual const vector< ServiceListener<Price<Bond> >* >& GetListeners() const override;
	
};

BondPricingService::BondPricingService(){
	priceMap=map<string, Price<Bond> >();
}

Price<Bond>& BondPricingService::GetData(string id){
	return priceMap.at(id);
}

void BondPricingService::OnMessage(Price<Bond>& data){
	auto id=data.GetProduct().GetProductId();
	
	if(priceMap.find(id)!=priceMap.end())
		priceMap.erase(id);
	priceMap.insert(pair<string,Price<Bond> >(id,data));
	
	// notify the listener
	for(auto& listener:listenerList){
		listener->ProcessAdd(data);
	}

	return;
}

void BondPricingService::AddListener(ServiceListener<Price<Bond> > *listener){
	listenerList.push_back(listener);
	return;
}

const vector< ServiceListener<Price<Bond> >* >& BondPricingService::GetListeners() const{
	return listenerList;
}


void BondPricingServiceConnector::Subscribe() {
	ifstream input;
	// read from txt
	input.open("prices.txt");

	string row;
	while (getline(input, row)) {
		stringstream line(row);
		string temp;
		// bond
		getline(line, temp, ',');
		auto bond = bondProductService->GetData(temp);
		// price
		getline(line, temp, ',');
		auto price = TransformStringToPrice(temp);
		// spread
		getline(line, temp, ',');
		auto spread = TransformStringToPrice(temp);

		Price<Bond> bondPrice(bond, price, spread);

		bondPricingService -> OnMessage(bondPrice);
	}
	return;
}
#endif
