/*
 * BondMarketDataService.hpp
 * read data from marketdata.ext and publish via socket into the trading system
 *
 * @author Ming Fu
 */

#ifndef BOND_MARKET_DATA_SERVICE_HPP
#define BOND_MARKET_DATA_SERVICE_HPP

using namespace std; 

#include "BondMarketDataServiceConnector.hpp"
#include <vector>
#include <string>
#include <unordered_map>

class BondMarketDataService:public MarketDataService<Bond>{
private:
	map<string, OrderBook<Bond> > orderMap;
	vector<ServiceListener<OrderBook<Bond> >*> listenerList;      
                        
public:
	// ctor
	BondMarketDataService();
	
	// get order book given id
    virtual OrderBook<Bond> & GetData(string id) override;   
	
	// add orderBook 
	virtual void OnMessage(OrderBook<Bond> &orderBook) override;  

	// add BondAlgoExecutionServiceListeners
    virtual void AddListener(ServiceListener<OrderBook<Bond> > *listener) override;  
	
	// get BondAlgoExecutionServiceListeners
    virtual const vector<ServiceListener<OrderBook<Bond> > *>& GetListeners() const override;  
	
	// return the best bid/ask
    virtual BidOffer GetBestBidOffer(const string &productId) override;  
	
	// merge the quantity with the same price
    virtual OrderBook<Bond> AggregateDepth(const string &productId) override;  
};

BondMarketDataService::BondMarketDataService(){
	orderMap=map<string, OrderBook<Bond> >();
}

OrderBook<Bond> & BondMarketDataService::GetData(string id){
	return orderMap.at(id);
}

void BondMarketDataService::OnMessage(OrderBook<Bond> & orderBook){
	auto id=orderBook.GetProduct().GetProductId();
	if(orderMap.find(id)!=orderMap.end())
		orderMap.erase(id);
	orderMap.insert(pair<string,OrderBook<Bond> >(id,orderBook));
	
	auto bestOrder=GetBestBidOffer(id);
	vector<Order> bid,ask;
	bid.push_back(bestOrder.GetBidOrder());
	ask.push_back(bestOrder.GetOfferOrder());
	OrderBook<Bond> bestBook=OrderBook<Bond>(orderBook.GetProduct(),bid,ask);
	
	for(auto& listener:listenerList){
		listener->ProcessAdd(bestBook);
	}
	return;
}

void BondMarketDataService::AddListener(ServiceListener<OrderBook<Bond> > *listener) {
    listenerList.push_back(listener);
	return;
}

const vector<ServiceListener<OrderBook<Bond> > *>& BondMarketDataService::GetListeners() const{
	return listenerList;
}

BidOffer BondMarketDataService::GetBestBidOffer(const string &productId){
	auto orderBook = orderMap.at(productId);
	auto bidStack=orderBook.GetBidStack();
	auto askStack=orderBook.GetOfferStack();
	auto bestBid=bidStack[0];
	auto bestAsk=askStack[0];
	
	for(auto& item:bidStack){
		if(item.GetPrice()>bestBid.GetPrice())
			bestBid=item;
	}
	
	for(auto& item:askStack){
		if(item.GetPrice()<bestAsk.GetPrice())
			bestAsk=item;
	}
    return BidOffer(bestBid,bestAsk);
}

OrderBook<Bond> BondMarketDataService::AggregateDepth(const string &productId){
	auto orderBook = orderMap.at(productId);
	auto bidStack=orderBook.GetBidStack();
	auto askStack=orderBook.GetOfferStack();
	
	// if price is same, merge quantity
	unordered_map<double,long> bidRecord,askRecord;
	for(auto& item:bidStack){
		if(bidRecord.find(item.GetPrice())!=bidRecord.end())
			bidRecord[item.GetPrice()]+=item.GetQuantity();
		else 
			bidRecord[item.GetPrice()]=item.GetQuantity();
	}
	for(auto& item:askStack){
		if(askRecord.find(item.GetPrice())!=askRecord.end())
			askRecord[item.GetPrice()]+=item.GetQuantity();
		else 
			askRecord[item.GetPrice()]=item.GetQuantity();
	}

	vector<Order> bidStack_,askStack_;
	for(auto& item:bidRecord){
		bidStack_.push_back(Order(item.first,item.second,BID));
	}
	for(auto& item:askRecord){
		askStack_.push_back(Order(item.first,item.second,OFFER));
	}

	auto b=orderBook.GetProduct();
	return OrderBook<Bond>(b,bidStack_,askStack_);
}


void BondMarketDataServiceConnector::Subscribe(){
	ifstream input;
	input.open("marketdata.txt");
	string row;
	
	while (getline(input, row)) {
		stringstream line(row);
		string temp;
		vector<Order> bidStack,askStack;
		
		// price
		getline(line, temp, ',');    
		auto bond = bondProductService->GetData(temp);
		
		for(int i=0;i<10;++i){
			// price
			getline(line, temp, ',');
			auto price = TransformStringToPrice(temp);
			// quantity
			getline(line, temp, ',');
			auto quantity = stol(temp);
			// side
			getline(line, temp, ',');
			auto side = temp;
			if(side=="BID"){
				bidStack.push_back(Order(price,quantity,BID));
			}
			else{
				askStack.push_back(Order(price,quantity,OFFER));
			}
		}
		
		OrderBook<Bond> orderBook(bond, bidStack, askStack);
		bondMarketDataService -> OnMessage(orderBook);
	}
	return;
}
#endif