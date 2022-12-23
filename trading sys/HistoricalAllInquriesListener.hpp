/*
 * HistoricalAllInquiriesListener.hpp
 *
 * @author: Ming Fu
 */

#pragma once 

#ifndef HISTORICAL_INQUIRY_LISTENER_HPP
#define HISTORICAL_INQUIRY_LISTENER_HPP

class HistoricalAllInquriesListener : public ServiceListener<Inquiry<Bond> > {
private:
	BondHistoricalAllInquiriesService* service;

public:
	// ctor
	HistoricalAllInquriesListener(BondHistoricalAllInquiriesService * p):service(p){}

	virtual void ProcessAdd(Inquiry<Bond> &data) override{
		service->PersistData(data.GetInquiryId(),data);
		return;
	} 
	virtual void ProcessRemove(Inquiry<Bond> &data) override{} 
	virtual void ProcessUpdate(Inquiry<Bond>  &data) override{}

};

#endif 