 /**
  * AlgoExecution.hpp
  * class with a reference to an ExecutionOrder object
  *
  * @author Ming Fu
  */

#ifndef ALGO_EXECUTION_HPP
#define ALGO_EXECUTION_HPP

using namespace std;

#include "BondMarketDataService.hpp"
#include "executionservice.hpp"
#include <string>
#include <sstream>
#include <random>

class AlgoExecution {
private:
	static int order_ID;
	ExecutionOrder<Bond> executionOrder;
	
public:
	// ctor
	AlgoExecution(ExecutionOrder<Bond> _executionOrder);

	// update priceStream according to order book
	void RunAlgo(OrderBook<Bond> orderBook);

	// get the executionOrder
	ExecutionOrder<Bond> GetExecutionOrder() const;
};

int AlgoExecution::order_ID=0;

AlgoExecution::AlgoExecution(ExecutionOrder<Bond> _executionOrder)
	:executionOrder(_executionOrder) {}

void AlgoExecution::RunAlgo(OrderBook<Bond> orderBook){
	auto bond=orderBook.GetProduct();
	if(bond.GetProductId() != executionOrder.GetProduct().GetProductId()) return;

	// order id
	string orderID = to_string(order_ID);
	stringstream ss;
	ss << setw(10) << setfill('0') << orderID;
	ss >> orderID;
	
	// order type
	OrderType orderType;
	int rd = rand() % 5;
	switch(rd){
	case 0: orderType = FOK; break;
	case 1: orderType = MARKET; break;
	case 2: orderType = LIMIT; break;
	case 3: orderType = STOP; break;
	case 4: orderType = IOC; break;
	}

	

	// B/S
	PricingSide pricingSide = (rand() % 2 == 0 ? BID : OFFER);
	
	// get order
	auto bidOrder = orderBook.GetBidStack().begin();
	auto askOrder = orderBook.GetOfferStack().begin();
	
	// only aggress when the spread is at its tightest 
	// to reduce the cost of crossing the spread
	double price;
	long visiableQ = 0, hiddenQ;
	if(pricingSide==BID){
		price = bidOrder->GetPrice();
		if (askOrder->GetPrice() - bidOrder->GetPrice() < 2 / 256.0)
			visiableQ = bidOrder->GetQuantity();
		hiddenQ = 2 * visiableQ;
	}
	else{
		price = askOrder->GetPrice();
		if (askOrder->GetPrice() - bidOrder->GetPrice() < 2 / 256.0)
			visiableQ = askOrder->GetQuantity();
		hiddenQ = 2 * visiableQ;
	}
    
	// parent order id
	string parentID = "P" + orderID;

	// execute order
	executionOrder = ExecutionOrder<Bond>(bond, pricingSide, orderID, orderType, price, visiableQ, hiddenQ, parentID, true);
	order_ID++;

	return;
}

ExecutionOrder<Bond> AlgoExecution::GetExecutionOrder() const{
	return executionOrder;
}
#endif
