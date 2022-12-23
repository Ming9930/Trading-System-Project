/**
 * BondPositionService.hpp
 * linked to a BondRiskService and send all positions to the BondRiskService
 *
 * @author Ming Fu
 */

#ifndef BOND_POSITION_SERVICE_HPP
#define BOND_POSITION_SERVICE_HPP

#include "BondTradeBookingService.hpp"
#include "positionservice.hpp"

using namespace std;

class BondPositionService: public PositionService<Bond> {
private:
	map<string,Position<Bond> >positionMap;
	vector<ServiceListener<Position<Bond> >*> listenerList;      
public:
	// ctor
	BondPositionService();

	// get position given id
	virtual Position<Bond>& GetData(string id) override;
	
	virtual void OnMessage(Position<Bond> &position) override;                   
	
	// add BondRickServiceListeners and BondHistoricalDataServiceListeners
	virtual void AddListener(ServiceListener<Position<Bond> > *listener) override;  
	
	// get BondRickServiceListeners and BondHistoricalDataServiceListeners
	virtual const vector<ServiceListener<Position<Bond> > *>& GetListeners() const override;  
	
	// add trade to map and notify listeners
	virtual void AddTrade(const Trade<Bond> &trade) override;        
};

BondPositionService::BondPositionService(){
	positionMap=map<string,Position<Bond> >();
}

Position<Bond>& BondPositionService::GetData(string id){
	return positionMap.at(id);
}

void BondPositionService::OnMessage(Position<Bond> &position){
	return;
}

void BondPositionService::AddListener(ServiceListener<Position<Bond> > *listener){
	listenerList.push_back(listener);
	return;
}

const vector<ServiceListener<Position<Bond> > *>& BondPositionService::GetListeners() const{
	return listenerList;
}  
	
void BondPositionService::AddTrade(const Trade<Bond> &trade){
	long quantity=trade.GetQuantity();
	if(trade.GetSide()==SELL)quantity=-quantity;
	auto bond=trade.GetProduct();
	auto id=bond.GetProductId();
	
	auto it=positionMap.find(id);
	if(it!=positionMap.end()){
		(it->second).AddPosition(trade.GetBook(),quantity);
	}
	else{
		positionMap.insert(pair<string,Position<Bond> >(id,Position<Bond>(bond)));
		AddTrade(trade);
		return;
	}
	
	for(auto& listener : listenerList) {
        listener->ProcessAdd(it->second);  
    }
	return;
}

#endif