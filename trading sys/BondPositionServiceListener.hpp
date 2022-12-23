/**
 * BondPositionServiceListener.hpp
 * send data from BondTradeBookingService to BondPositionService
 *
 * @author Ming Fu
 */

#ifndef BOND_POSITION_SERVICE_LISTENER_HPP
#define BOND_POSITION_SERVICE_LISTENER_HPP

#include "BondPositionService.hpp"
#include "soa.hpp"

using namespace std;

class BondPositionServiceListener : public ServiceListener<Trade<Bond> > {
private:
    BondPositionService* bondPositionService;

public:
    // ctor
    BondPositionServiceListener(BondPositionService* _bondPositionService);

	// call bondPositionService AddTrade method
    virtual void ProcessAdd(Trade<Bond> &data); 
	
    virtual void ProcessRemove(Trade<Bond> &data) override{}
	
    virtual void ProcessUpdate(Trade<Bond> &data) override{}
};

BondPositionServiceListener::BondPositionServiceListener(BondPositionService* _bondPositionService) {
	 bondPositionService= _bondPositionService;
}

void BondPositionServiceListener::ProcessAdd(Trade<Bond> &data) {
    bondPositionService->AddTrade(data);
	return;
}


#endif