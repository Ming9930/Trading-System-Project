/**
 * BondStreamingServiceListener.hpp
 *
 * @author: Ming Fu
 */ 
#pragma once

#ifndef BOND_STREAMING_SERVICE_LISTENER_HPP
#define BOND_STREAMING_SERVICE_LISTENER_HPP

#include "BondStreamingService.hpp"
#include "soa.hpp"

using namespace std;

class BondStreamingServiceListener: public ServiceListener<AlgoStream>{
private:
    BondStreamingService* bondStreamingService;

public:
    // ctor
    BondStreamingServiceListener(BondStreamingService* _bondStreamingService);

	// call addAlgo and PublishPrice
    virtual void ProcessAdd(AlgoStream& algoStream) override; 
	
    virtual void ProcessRemove(AlgoStream &) override;  
	
    virtual void ProcessUpdate(AlgoStream &) override;  
};

BondStreamingServiceListener::BondStreamingServiceListener(BondStreamingService* _bondStreamingService){
	bondStreamingService=_bondStreamingService;
}

void BondStreamingServiceListener::ProcessAdd(AlgoStream& algoStream){
	bondStreamingService->AddAlgo(algoStream);
	auto priceStream=algoStream.GetPriceStream();
    bondStreamingService->PublishPrice(priceStream);
	return;
}

void BondStreamingServiceListener::ProcessRemove(AlgoStream& data){
	return;
}

void BondStreamingServiceListener::ProcessUpdate(AlgoStream& data){
	return;
}
#endif