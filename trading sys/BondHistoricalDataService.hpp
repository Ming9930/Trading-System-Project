/**
 * BondHistoricalDataService.hpp
 * register a ServiceListener on 
 * BondPositionService, BondRiskService, BondExecutionService, BondStreamingService, BondInquiryService
 *
 * @author Ming Fu
 */

#ifndef BOND_HISTORICAL_DATA_SERVICE_HPP
#define BOND_HISTORICAL_DATA_SERVICE_HPP

#include "historicaldataservice.hpp"
#include "GUIServiceConnector.hpp"
#include "BondStreamingService.hpp"
#include "BondRiskService.hpp"
#include "BondPositionService.hpp"
#include "BondExecutionService.hpp"
#include "BondInquiryService.hpp"
#include <iostream>

using namespace std;

class HistoricalPositionConnector;
class HistoricalRiskConnector;
class HistoricalExecutionConnector;
class HistoricalStreamingConnector;
class HistoricalAllInquiriesConnector;


class BondHistoricalPositionService: public HistoricalDataService<Position<Bond> > {
private:
	HistoricalPositionConnector* connector;
	map<string, Position<Bond> > dataMap;
	vector<ServiceListener<Position<Bond>  >*> listenerList;
public:
	// ctor
	BondHistoricalPositionService(HistoricalPositionConnector* _p):connector(_p){}

	// get data given id
	virtual Position<Bond>  & GetData(string id) override {return dataMap.at(id);}

	virtual void OnMessage(Position<Bond>  & bond) override {}

	virtual void AddListener(ServiceListener<Position<Bond>  > *listener) override {}

	virtual const vector<ServiceListener<Position<Bond>  >*>& GetListeners() const override { return listenerList; }

	virtual void PersistData(string persistKey, Position<Bond>& data) override;
};


class BondHistoricalRiskService: public HistoricalDataService<PV01<Bond> > {
private:
	HistoricalRiskConnector* connector;
	map<string, PV01<Bond> > dataMap;
	vector<ServiceListener<PV01<Bond>  >*> listenerList;
public:
	// ctor
	BondHistoricalRiskService(HistoricalRiskConnector* _p):connector(_p){}

	// get data given id
	virtual PV01<Bond>  & GetData(string id) override {return dataMap.at(id);}

	virtual void OnMessage(PV01<Bond>  & bond) override {}

	virtual void AddListener(ServiceListener<PV01<Bond>  > *listener) override {}

	virtual const vector<ServiceListener<PV01<Bond>  >*>& GetListeners() const override { return listenerList; }

	virtual void PersistData(string persistKey, PV01<Bond>& data) override;
};


class BondHistoricalExecutionService: public HistoricalDataService<ExecutionOrder<Bond> > {
private:
	HistoricalExecutionConnector* connector;
	map<string, ExecutionOrder<Bond> > dataMap;
	vector<ServiceListener<ExecutionOrder<Bond>  >*> listenerList;
public:
	// ctor
	BondHistoricalExecutionService(HistoricalExecutionConnector* _p):connector(_p){}

	// get data given id
	virtual ExecutionOrder<Bond> & GetData(string id) override {return dataMap.at(id);}

	virtual void OnMessage(ExecutionOrder<Bond> & bond) override {}

	virtual void AddListener(ServiceListener<ExecutionOrder<Bond>  > *listener) override {}

	virtual const vector<ServiceListener<ExecutionOrder<Bond>  >*>& GetListeners() const override {return listenerList;}

	virtual void PersistData(string persistKey, ExecutionOrder<Bond>& data) override;
};


class BondHistoricalStreamingService: public HistoricalDataService<PriceStream<Bond> > {
private:
	HistoricalStreamingConnector* connector;
	map<string, PriceStream<Bond> > dataMap;
	vector<ServiceListener<PriceStream<Bond>  >*> listenerList;
public:
	// ctor
	BondHistoricalStreamingService(HistoricalStreamingConnector* _p):connector(_p){}

	// get data given id
	virtual PriceStream<Bond> & GetData(string id) override {return dataMap.at(id);}

	virtual void OnMessage(PriceStream<Bond> & bond) override {}

	virtual void AddListener(ServiceListener<PriceStream<Bond>  > *listener) override {}

	virtual const vector<ServiceListener<PriceStream<Bond>  >*>& GetListeners() const override { return listenerList; }

	virtual void PersistData(string persistKey, PriceStream<Bond>& data) override;
};


class BondHistoricalAllInquiriesService: public HistoricalDataService<Inquiry<Bond> > {
private:
	HistoricalAllInquiriesConnector* connector;
	map<string, Inquiry<Bond> > dataMap;
	vector<ServiceListener<Inquiry<Bond> >*> listenerList;
public:
	// ctor
	BondHistoricalAllInquiriesService(HistoricalAllInquiriesConnector* _p):connector(_p){}

	// get data given id
	virtual Inquiry<Bond> & GetData(string id) override {return dataMap.at(id);}

	virtual void OnMessage(Inquiry<Bond> & bond) override {}

	virtual void AddListener(ServiceListener<Inquiry<Bond>  > *listener) override {}

	virtual const vector<ServiceListener<Inquiry<Bond> >*>& GetListeners() const override { return listenerList; }

	virtual void PersistData(string persistKey, Inquiry<Bond>& data) override;
};


#endif
