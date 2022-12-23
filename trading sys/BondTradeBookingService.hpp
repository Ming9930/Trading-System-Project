/**
 * BondTradeBookingService.hpp
 * read data from trade.txt
 *
 * @author: Ming Fu
 */ 
#pragma once

#ifndef BOND_TRADE_BOOKING_SERVICE_HPP
#define BOND_TRADE_BOOKING_SERVICE_HPP

using namespace std;

#include "BondTradeBookingServiceConnector.hpp"
#include "tradebookingservice.hpp"
#include <map>
#include <vector>
#include <string>

class BondTradeBookingService: public TradeBookingService<Bond>{
private:
	map<string, Trade<Bond> > tradeMap;
	vector<ServiceListener<Trade<Bond> >*> listenerList;     
public:
	// ctor
	BondTradeBookingService();

	// get Trade given id
	virtual Trade<Bond> & GetData(string id) override;              
	
	// call BookTrade
	virtual void OnMessage(Trade<Bond> &trade) override;                  
	
	// add BondPositionServiceListeners
	virtual void AddListener(ServiceListener<Trade<Bond> > *listener) override;  
	
	// get BondPositionServiceListeners
	virtual const vector<ServiceListener<Trade<Bond> > *>& GetListeners() const override; 
	
	// add a trade to tradeMap
	virtual void BookTrade(Trade<Bond> trade) override;            
};


BondTradeBookingService::BondTradeBookingService(){
	tradeMap=map<string, Trade<Bond> >();
}

Trade<Bond> & BondTradeBookingService::GetData(string id){
	return tradeMap.at(id);
}             

void BondTradeBookingService::OnMessage(Trade<Bond> &trade){
	BookTrade(trade);
	return;
}                  

void BondTradeBookingService::AddListener(ServiceListener<Trade<Bond> > *listener){
	listenerList.push_back(listener);
	return;
} 

const vector<ServiceListener<Trade<Bond> > *>& BondTradeBookingService::GetListeners() const{
	return listenerList;
}

void BondTradeBookingService::BookTrade(Trade<Bond> trade){
	auto id=trade.GetProduct().GetProductId();
	if(tradeMap.find(id)!=tradeMap.end())
		tradeMap.erase(id);
	tradeMap.insert(pair<string,Trade<Bond> >(id,trade));
	
	for(auto& listener:listenerList){
		listener->ProcessAdd(trade);
	}
	return;
}           


void BondTradeBookingServiceConnector::Subscribe(){
	ifstream input;
	input.open("trades.txt");

	string row;
	while (getline(input, row)) {
		stringstream line(row);
		string temp;
		// bond
		getline(line, temp, ',');    
		auto bond = bondProductService->GetData(temp);
		// id
		getline(line, temp, ',');
		auto tradeID = temp;
		// price
		getline(line, temp, ',');
		auto price = TransformStringToPrice(temp);
		// book
		getline(line, temp, ',');
		auto book = temp;
		// quantity
		getline(line, temp, ',');
		long quantity = stol(temp);
		// B/S
		getline(line, temp, ',');
		Side side = (temp == "BUY" ? BUY : SELL);
		
		Trade<Bond> bondNew(bond,tradeID,price,book,quantity,side);
		bondTradeBookingService -> OnMessage(bondNew);
	}
	return;	
}


#endif