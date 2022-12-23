/**
 * BondProductService.hpp 
 * defines bond product service
 * 
 * @author: Ming Fu
 */
#pragma once

#ifndef BOND_PRODUCT_SERVICE_HPP
#define BOND_PRODUCT_SERVICE_HPP

#include "products.hpp"
#include "soa.hpp"
#include <iostream>
#include <map>

using namespace std;


class BondProductService : public Service<string,Bond> {
private:
	vector<ServiceListener<Bond >*> listenerList;
	map<string, Bond> bondMap;
public:
	// ctor
	BondProductService();

	// return the bond data for a particular bond product identifier
	Bond& GetData(string productId);

	// add a bond 
	void Add(Bond &bond);

	// get Bonds with the specified ticker
	vector<Bond> GetBonds(string& _ticker);

	virtual void OnMessage(Bond &data) override{}

	virtual void AddListener(ServiceListener<Bond > *listener) override{}
	
	virtual const vector< ServiceListener<Bond>* >& GetListeners() const override { return listenerList; };
	
};

BondProductService::BondProductService() {
	bondMap = map<string,Bond>();
}

Bond& BondProductService::GetData(string productId) {
	return bondMap[productId];
}

void BondProductService::Add(Bond &bond) {
	bondMap.insert(pair<string,Bond>(bond.GetProductId(), bond));
}

vector<Bond> BondProductService::GetBonds(string& _ticker){
	vector<Bond> res;
	for(auto it=bondMap.begin();it!=bondMap.end();++it){
		if((it->second).GetTicker()==_ticker)
			res.push_back(it->second);
	}
	return res;
}

#endif