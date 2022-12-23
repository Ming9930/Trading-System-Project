/*
 * HistoricalRiskListener.hpp
 *
 * @author: Ming Fu
 */

#pragma once 

#ifndef HISTORICAL_RISK_LISTENER_HPP
#define HISTORICAL_RISK_LISTENER_HPP

class HistoricalRiskListener : public ServiceListener<PV01<Bond> > {
private:
	BondHistoricalRiskService* service;

public:
	// ctor
	HistoricalRiskListener(BondHistoricalRiskService * p):service(p){}

	virtual void ProcessAdd(PV01<Bond> &data) override{
		service->PersistData(data.GetProduct().GetProductId(),data);
		return;
	} 
	virtual void ProcessRemove(PV01<Bond> &data) override{} 
	virtual void ProcessUpdate(PV01<Bond> &data) override{}

};

#endif 