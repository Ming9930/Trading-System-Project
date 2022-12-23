/**
 * BondExecutionServiceListener.hpp
 * dpass data from BondAlgoExecutionService to BondExecutionService
 * 
 * @author Ming Fu
 */ 

#ifndef BOND_EXECUTION_SERVICE_LISTENER_HPP
#define BOND_EXECUTION_SERVICE_LISTENER_HPP

using namespace std;

#include "BondAlgoExecutionService.hpp"
#include "soa.hpp"
 
class BondExecutionServiceListener: public ServiceListener<AlgoExecution>{
private:
    BondExecutionService* bondExecutionService;

public:
    // ctor
    BondExecutionServiceListener(BondExecutionService* _bondExecutionService);

    // call BondExecutionService::AddAlgoExecution and BondExecutionService::ExecuteOrder
    virtual void ProcessAdd(AlgoExecution &data) override; 
	
    virtual void ProcessRemove(AlgoExecution &data) override{};
	
    virtual void ProcessUpdate(AlgoExecution &data) override{}; 
	
};

BondExecutionServiceListener::BondExecutionServiceListener(BondExecutionService* _bondExecutionService){
	bondExecutionService=_bondExecutionService;
}

void BondExecutionServiceListener::ProcessAdd(AlgoExecution &data){
	auto order=data.GetExecutionOrder();
	bondExecutionService->AddAlgoExecution(data);
	bondExecutionService->ExecuteOrder(order,BROKERTEC);
	return;
}

#endif