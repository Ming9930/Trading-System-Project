/**
 * BondAlgoStreamingService.hpp
 * register a ServiceListerner on the BondPricingService 
 * and send the bid/offer prices to the BondStreamingService
 * 
 * @author Ming Fu
 */

#ifndef BOND_ALGO_STREAMING_SERVICE_HPP
#define BOND_ALGO_STREAMING_SERVICE_HPP

#include "AlgoStream.hpp"
#include "products.hpp"
#include "soa.hpp"
#include <map>
#include <vector>
#include <string>

using namespace std;

class BondAlgoStreamingService: public Service<string, AlgoStream>{
private:
	map<string, AlgoStream > algoMap; 
	vector<ServiceListener<AlgoStream>* > listenerList;  
public:
	// ctor
    BondAlgoStreamingService();

	// get AlgoStream given id 
    virtual AlgoStream& GetData(string id) override;              
	
    virtual void OnMessage(AlgoStream &) override;                   
	
	// add BondStreamingServiceListeners
    virtual void AddListener(ServiceListener<AlgoStream> *listener) override;  
	
	// get BondStreamingServiceListeners
    virtual const vector<ServiceListener<AlgoStream> *>& GetListeners() const override;  
	
	// add a new price from BondPricingService
    void AddPrice(const Price<Bond>& price);       
		
};

BondAlgoStreamingService::BondAlgoStreamingService(){
	algoMap=map<string, AlgoStream>();
}

AlgoStream& BondAlgoStreamingService::GetData(string id){
	return algoMap.at(id);
}

void BondAlgoStreamingService::OnMessage(AlgoStream & algo){
}

void BondAlgoStreamingService::AddListener(ServiceListener<AlgoStream> *listener){
	listenerList.push_back(listener);
}

const vector<ServiceListener<AlgoStream> *>& BondAlgoStreamingService::GetListeners() const{
	return listenerList;
}

void BondAlgoStreamingService::AddPrice(const Price<Bond>& price){
	auto id=price.GetProduct().GetProductId();
	auto it=algoMap.find(id);

	if(it!=algoMap.end()){
		(it->second).RunAlgo(price);
	}
	else{
		PriceStreamOrder p1(0, 0, 0, BID);
		PriceStreamOrder p2(0, 0, 0, OFFER);
		PriceStream<Bond> ps(price.GetProduct(), p1, p2);
		algoMap.insert(pair<string,PriceStream<Bond> >(id,ps));
		AddPrice(price);
		return;
	}
	
	// notify the listeners
	for(auto& listener:listenerList){
		listener->ProcessAdd(it->second);
	}

	return;
}
#endif