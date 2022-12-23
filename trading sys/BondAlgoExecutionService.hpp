/*
 * BondAlgoExecutionService.hpp
 * register a ServiceListener on the BondMarketDataService and aggress the top of the book
 * 
 * @author Ming Fu
 */

#ifndef BOND_ALGO_EXECUTION_SERVICE_HPP
#define BOND_ALGO_EXECUTION_SERVICE_HPP

using namespace std;

#include "AlgoExecution.hpp"

class BondAlgoExecutionService: public Service<string, AlgoExecution>{
private:
	map<string,AlgoExecution> algoMap;
	vector<ServiceListener<AlgoExecution >*> listenerList;      
	
public:
    // ctor
    BondAlgoExecutionService();

	// get algoExecution by id 
    AlgoExecution & GetData(string id);       
	
    void OnMessage(AlgoExecution &);                
	
	// add BondExecutionServiceListeners
    void AddListener(ServiceListener<AlgoExecution> *listener);  
	
	// get BondExecutionServiceListeners
    const vector<ServiceListener<AlgoExecution> *>& GetListeners() const;  
	
	// add a order book and call RunAlgo
    void AddOrderBook(OrderBook<Bond>& orderBook);        
};

BondAlgoExecutionService::BondAlgoExecutionService(){
	algoMap=map<string, AlgoExecution>();
}

AlgoExecution& BondAlgoExecutionService::GetData(string id){
	return algoMap.at(id);
}

void BondAlgoExecutionService::OnMessage(AlgoExecution & a){
	return;
}

void BondAlgoExecutionService::AddListener(ServiceListener<AlgoExecution> *listener){
	listenerList.push_back(listener);
	return;
}

const vector<ServiceListener<AlgoExecution> *>& BondAlgoExecutionService::GetListeners() const{
	return listenerList;
}

void BondAlgoExecutionService::AddOrderBook(OrderBook<Bond>& orderBook){
	auto id=orderBook.GetProduct().GetProductId();
	auto it=algoMap.find(id);

	if(it!=algoMap.end()){
		(it->second).RunAlgo(orderBook);
	}	
	else{
		auto eo = ExecutionOrder<Bond>(orderBook.GetProduct(), BID, "0", FOK, 0, 0, 0, "0", true);
		algoMap.insert(pair<string,AlgoExecution >(id,AlgoExecution(eo)));
		AddOrderBook(orderBook);
		return;
	}
	
	// notify the listeners
	for(auto& listener:listenerList){
		listener->ProcessAdd(it->second);
	}

	return;
}
#endif 