/**
 * BondExecutionService.hpp
 * use a Connector to publish executions via socket
 * 
 * @author Ming Fu
 */

#ifndef BOND_EXECUTION_SERVICE_HPP
#define BOND_EXECUTION_SERVICE_HPP

using namespace std;

#include "BondAlgoExecutionService.hpp"
#include "executionservice.hpp"

class BondExecutionServiceConnector;

class BondExecutionService: public ExecutionService<Bond> {
private:
	map<string, ExecutionOrder<Bond> > executionMap;   
	vector<ServiceListener<ExecutionOrder<Bond> >*> listenerList;      
    BondExecutionServiceConnector* bondExecutionServiceConnector;  
public:
    // ctor
    BondExecutionService(BondExecutionServiceConnector* _bondExecutionServiceConnector);

	// get execution order by id
    virtual ExecutionOrder<Bond> & GetData(string id) override;     
	
    virtual void OnMessage(ExecutionOrder<Bond> &) override;      
	
	// add BondHistoricalDataServiceListeners
    virtual void AddListener(ServiceListener<ExecutionOrder<Bond> > *listener) override;  
	
	// get BondHistoricalDataServiceListeners
    virtual const vector<ServiceListener<ExecutionOrder<Bond> > *>& GetListeners() const override; 
	
	// pass execution order to connector
    virtual void ExecuteOrder(ExecutionOrder<Bond> &order, Market market) override;   
	
	// add algo to AlgoMap and notify listeners
    void AddAlgoExecution(const AlgoExecution& algo);         
};

BondExecutionService::BondExecutionService(BondExecutionServiceConnector* _bondExecutionServiceConnector){
	bondExecutionServiceConnector=_bondExecutionServiceConnector;
}

ExecutionOrder<Bond> & BondExecutionService::GetData(string id){
	return executionMap.at(id);
} 
	
void BondExecutionService::OnMessage(ExecutionOrder<Bond> &){
	return;
}     

void BondExecutionService::AddListener(ServiceListener<ExecutionOrder<Bond> > *listener){
	listenerList.push_back(listener);
	return;
} 
	
const vector<ServiceListener<ExecutionOrder<Bond> > *>& BondExecutionService::GetListeners() const{
	return listenerList;
}

void BondExecutionService::AddAlgoExecution(const AlgoExecution& algo){
	auto executionOrder = algo.GetExecutionOrder();
    string id = executionOrder.GetProduct().GetProductId();
	
	if(executionMap.find(id)!=executionMap.end())
		executionMap.erase(id);
	executionMap.insert(pair<string,ExecutionOrder<Bond> >(id,executionOrder));

    for(auto& listener :listenerList) {
        listener->ProcessAdd(executionOrder );
    }
	
	return;
}
#endif