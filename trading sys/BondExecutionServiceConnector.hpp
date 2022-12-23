/**
 * BondExecutionServiceConnector.hpp
 * receive data from BondExecutionService and publish executions
 * 
 * @author Ming Fu
 */

#ifndef	BOND_EXECUTION_SERVICE_CONNECTOR_HPP
#define BOND_EXECUTION_SERVICE_CONNECTOR_HPP

using namespace std;

#include "BondExecutionService.hpp"
#include "soa.hpp"
#include "products.hpp"
#include <string>
#include <iostream>

class BondExecutionServiceConnector:public Connector<ExecutionOrder<Bond> >{
public:
    // ctor
    BondExecutionServiceConnector();

    // publish executions
    virtual void Publish(ExecutionOrder<Bond>& data) override;   
	
    virtual void Subscribe() override;   
};

BondExecutionServiceConnector::BondExecutionServiceConnector(){}

void BondExecutionServiceConnector::Publish(ExecutionOrder<Bond>& data){
	auto bond=data.GetProduct();
	string orderType;
	switch(data.GetOrderType()) {
		case FOK: orderType = "FOK"; break;
		case MARKET: orderType = "MARKET"; break;
		case LIMIT: orderType = "LIMIT"; break;
		case STOP: orderType = "STOP"; break;
		case IOC: orderType = "IOC"; break;
	}

	// publish executions
	cout << bond.GetProductId() << " OrderId: " << data.GetOrderId() << "\n"
		 << " OrderType: " << orderType << " PricingSide: " << (data.GetSide()==BID? "Bid":"Ask")
		 << " IsChildOrder: " << (data.IsChildOrder()?"True":"False")
	  	 << "\n"
		 << " Price: " << data.GetPrice()<< " VisibleQuantity: " << data.GetVisibleQuantity()
		 << " HiddenQuantity: " << data.GetHiddenQuantity() << "\n" <<endl;
		
	return;
}

void BondExecutionServiceConnector::Subscribe(){
	return;
}

void BondExecutionService::ExecuteOrder(ExecutionOrder<Bond> &order, Market market){
	bondExecutionServiceConnector->Publish(order);
} 
#endif