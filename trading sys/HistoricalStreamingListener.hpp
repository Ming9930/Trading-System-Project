/*
 * HistoricalStreamingListener.hpp
 *
 * @author: Ming Fu
 */

#pragma once 

#ifndef HISTORICAL_STREAMING_LISTENER_HPP
#define HISTORICAL_STREAMING_LISTENER_HPP

class HistoricalStreamingListener : public ServiceListener<PriceStream<Bond>  > {
private:
	BondHistoricalStreamingService* service;

public:
	// ctor
	HistoricalStreamingListener(BondHistoricalStreamingService * p):service(p){}

	virtual void ProcessAdd(PriceStream<Bond>  &data) override{
		service->PersistData(data.GetProduct().GetProductId(),data);
		return;
	} 
	virtual void ProcessRemove(PriceStream<Bond>  &data) override{} 
	virtual void ProcessUpdate(PriceStream<Bond>  &data) override{}

};

#endif 