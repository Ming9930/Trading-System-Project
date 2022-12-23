/**
 * BondStreamingService_hpp
 * read data and publish streams
 *
 * @author: Ming Fu
 */ 
#pragma once

#ifndef BOND_STREAMING_SERVICE_HPP
#define BOND_STREAMING_SERVICE_HPP

#include "streamingservice.hpp"
#include "BondAlgoStreamingService.hpp"

using namespace std;

class BondStreamingServiceConnector;

class BondStreamingService: public StreamingService<Bond>{
private:
	map<string, PriceStream<Bond> > streamMap;
	vector<ServiceListener<PriceStream<Bond> >*> listenerList;
	BondStreamingServiceConnector* bondStreamingServiceConnector;
public:
	// ctor
    BondStreamingService(BondStreamingServiceConnector* _bondStreamingServiceConnector);

	// return PriceStream given id
    virtual PriceStream<Bond>& GetData(string id) override;   

    virtual void OnMessage(PriceStream<Bond>&) override;  
	
	// add BondHistoricalDataServiceListeners
    virtual void AddListener(ServiceListener<PriceStream<Bond> > *listener) override;  
	
	// get BondHistoricalDataServiceListeners
    virtual const vector<ServiceListener<PriceStream<Bond> > *>& GetListeners() const override;  
	
	// publish stream
    virtual void PublishPrice(PriceStream<Bond>& priceStream) override;  
	
	void AddAlgo(const AlgoStream& algo);          
};

BondStreamingService::BondStreamingService(BondStreamingServiceConnector*_bondStreamingServiceConnector){
	bondStreamingServiceConnector=_bondStreamingServiceConnector;
	streamMap=map<string, PriceStream<Bond> >();
}

PriceStream<Bond>& BondStreamingService::GetData(string id){
	return streamMap.at(id);
}

void BondStreamingService::OnMessage(PriceStream<Bond>& stream){
	return;
}

void BondStreamingService::AddListener(ServiceListener<PriceStream<Bond> > *listener){
	listenerList.push_back(listener);
	return;
}

const vector<ServiceListener<PriceStream<Bond> > *>& BondStreamingService::GetListeners() const{
	return listenerList;
}

// void BondStreamingService::PublishPrice(PriceStream<Bond>&) defined in BondStreamingServiceConnector.hpp

void BondStreamingService::AddAlgo(const AlgoStream& algo){
	// priceStream
	auto stream=algo.GetPriceStream();
	auto id =stream.GetProduct().GetProductId();
	if(streamMap.find(id)!=streamMap.end())
		streamMap.erase(id);
	streamMap.insert(pair<string,PriceStream<Bond> >(id,stream));
	for(auto& listener:listenerList){
		listener->ProcessAdd(stream);
	}

	return;
}
#endif 