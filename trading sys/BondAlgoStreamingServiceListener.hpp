/*
 * BondAlgoStreamingServiceListener.hpp
 * send the bid/offer prices from BondPricingService to BondAlgoStreamingService
 *
 * @author Ming Fu
 */

#ifndef BOND_ALGO_STREAMING_SERVICE_LISTENER_HPP
#define BOND_ALGO_STREAMING_SERVICE_LISTENER_HPP

#include "soa.hpp"
#include "BondAlgoStreamingService.hpp"

using namespace std;

class BondAlgoStreamingServiceListener: public ServiceListener<Price<Bond> >{
private:
	BondAlgoStreamingService* bondAlgoStreamingService;
public:
	// ctor
	BondAlgoStreamingServiceListener(BondAlgoStreamingService* _bondAlgoStreamingService);
	
	// call AddPrice method in BondAlgoStreamingService
	virtual void ProcessAdd(Price<Bond>& price) override; 
	
	virtual void ProcessRemove(Price<Bond>&) override;  
	
	virtual void ProcessUpdate(Price<Bond>&) override;  
};

BondAlgoStreamingServiceListener::BondAlgoStreamingServiceListener(BondAlgoStreamingService* _bondAlgoStreamingService){
	bondAlgoStreamingService=_bondAlgoStreamingService;
}

void BondAlgoStreamingServiceListener::ProcessAdd(Price<Bond>& price){
	bondAlgoStreamingService->AddPrice(price);
	return;
}

void BondAlgoStreamingServiceListener::ProcessRemove(Price<Bond>& data){
	return;
}

void BondAlgoStreamingServiceListener::ProcessUpdate(Price<Bond>& data){
	return;
}

#endif