/**
 * BondTradeBookingServiceListener.hpp
 *
 * @author: Ming Fu
 */ 
#pragma once

#ifndef BOND_TRADE_BOOKING_SERVICE_LISTENER_HPP
#define BOND_TRADE_BOOKING_SERVICE_LISTENER_HPP

#include "BondTradeBookingService.hpp"
#include "BondExecutionService.hpp"
#include "soa.hpp"
#include <string>

using namespace std;

class BondTradeBookingServiceListener: public ServiceListener<ExecutionOrder<Bond> >{
private:
    BondTradeBookingService* bondTradeBookingService;

public:
    // ctor
    BondTradeBookingServiceListener(BondTradeBookingService* _bondTradeBookingService);

	// convert ExecutionOrder to Trade and pass to BondTradeBookingServce
    virtual void ProcessAdd(ExecutionOrder<Bond>& data) override; 
	
    virtual void ProcessRemove(ExecutionOrder<Bond> &data) override{}  
	
    virtual void ProcessUpdate(ExecutionOrder<Bond> &data) override{}
};

BondTradeBookingServiceListener::BondTradeBookingServiceListener(BondTradeBookingService* _bondTradeBookingService){
	bondTradeBookingService=_bondTradeBookingService;
}

void BondTradeBookingServiceListener::ProcessAdd(ExecutionOrder<Bond>& data){
	auto bond = data.GetProduct();
	string tradeID = "Execution";
	auto price = data.GetPrice();
	string book = "Book";
	auto quantity = data.GetVisibleQuantity();
	Side side = BUY;
	if (data.GetSide() == BID)
		side = SELL;
	Trade<Bond> trade(bond,tradeID,price,book,quantity,side);

	bondTradeBookingService->BookTrade(trade);
	return;
}

#endif