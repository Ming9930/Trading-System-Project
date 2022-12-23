/**
 * BondAlgoExectuionServiceListener.hpp
 * send order from BondMarketDataService to BondAlgoExecutionService
 *   
 * @author Ming Fu
 */

#ifndef BOND_ALGO_EXECUTION_SERVICE_LISTENER_HPP
#define BOND_ALGO_EXECUTION_SERVICE_LISTENER_HPP

using namespace std;

#include "BondAlgoExecutionService.hpp"
#include "soa.hpp"

class BondAlgoExecutionServiceListener: public ServiceListener<OrderBook<Bond> >{
private:
    BondAlgoExecutionService* bondAlgoExecutionService;
public:
    //ctor
    BondAlgoExecutionServiceListener(BondAlgoExecutionService* _bondAlgoExecutionService);

    // call AddOrderBook in BondAlgoExecutionService
    virtual void ProcessAdd(OrderBook<Bond> &data) override; 
	
    virtual void ProcessRemove(OrderBook<Bond> &data) override{};  

    virtual void ProcessUpdate(OrderBook<Bond> &data) override{};  
};

BondAlgoExecutionServiceListener::BondAlgoExecutionServiceListener(BondAlgoExecutionService* _bondAlgoExecutionService){
	bondAlgoExecutionService=_bondAlgoExecutionService;
}

void BondAlgoExecutionServiceListener::ProcessAdd(OrderBook<Bond> &data){
	bondAlgoExecutionService -> AddOrderBook(data);
	return;
}

#endif