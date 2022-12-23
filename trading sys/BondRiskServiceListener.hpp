/**
 * BondRiskServiceListener.hpp
 *
 * @author: Ming Fu
 */

#pragma once

#ifndef BOND_RISK_SERVICE_LISTENER_HPP
#define BOND_RISK_SERVICE_LISTENER_HPP

using namespace std;

#include "BondRiskService.hpp"
#include "soa.hpp"

class BondRiskServiceListener : public ServiceListener<Position<Bond> > {
private:
    BondRiskService* bondRiskService;
public:
    //ctor
    BondRiskServiceListener(BondRiskService* _bondRiskService);

	// call bondRiskService AddPosition method
    virtual void ProcessAdd(Position<Bond> &data) override; 
	
    virtual void ProcessRemove(Position<Bond> &data) override{};  
	
    virtual void ProcessUpdate(Position<Bond> &data) override{}; 
};

BondRiskServiceListener::BondRiskServiceListener(BondRiskService* _bondRiskService) {
	bondRiskService=_bondRiskService;
}

void BondRiskServiceListener::ProcessAdd(Position<Bond> &data) {
	bondRiskService -> AddPosition(data);
	return;
}

#endif