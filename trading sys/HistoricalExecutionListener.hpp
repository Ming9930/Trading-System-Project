/*
 * HistoricalExecutionListener.hpp
 *
 * @author: Ming Fu
 */

#pragma once 

#ifndef HISTORICAL_EXECUTION_LISTENER_HPP
#define HISTORICAL_EXECUTION_LISTENER_HPP

class HistoricalExecutionListener : public ServiceListener<ExecutionOrder<Bond> > {
private:
	BondHistoricalExecutionService* service;

public:
	// ctor
	HistoricalExecutionListener(BondHistoricalExecutionService * p):service(p){}

	virtual void ProcessAdd(ExecutionOrder<Bond> &data) override{
		service->PersistData(data.GetOrderId(),data);
		return;
	} 
	virtual void ProcessRemove(ExecutionOrder<Bond> &data) override{} 
	virtual void ProcessUpdate(ExecutionOrder<Bond> &data) override{}

};

#endif 