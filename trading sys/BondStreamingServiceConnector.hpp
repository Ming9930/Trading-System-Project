/**
 * BondStreamingServiceConnector.hpp
 *
 * @author: Ming Fu
 */ 
#pragma once

#ifndef BOND_STREAMING_SERVICE_CONNECTOR_HPP
#define BOND_STREAMING_SERVICE_CONNECTOR_HPP

using namespace std;

#include "soa.hpp"
#include "BondStreamingService.hpp"
#include "streamingservice.hpp"
#include "products.hpp"
#include <string>
#include <iostream>

class BondStreamingServiceConnector: public Connector<PriceStream<Bond> >{
public:
    // ctor
    BondStreamingServiceConnector();

	virtual void Subscribe() override;
	
	// publish priceStream 
	virtual void Publish(PriceStream<Bond>& data) override;
};

BondStreamingServiceConnector::BondStreamingServiceConnector(){
}

void BondStreamingServiceConnector::Publish(PriceStream<Bond>& data) {
    auto bond = data.GetProduct();
    auto bidOrder = data.GetBidOrder();
    auto askOrder = data.GetOfferOrder();
	
    cout<<bond.GetProductId()<<"\n"
		<< " BidOrder: " << "Price: " << bidOrder.GetPrice() 
		<< " VisibleQuantity: " << bidOrder.GetVisibleQuantity()
		<< " HiddenQuantity: " << bidOrder.GetHiddenQuantity() << "\n"
		<< " offerOrder: " << "Price: " << askOrder.GetPrice() 
		<< " VisibleQuantity: " << askOrder.GetVisibleQuantity()
		<< " HiddenQuantity: " << askOrder.GetHiddenQuantity() << "\n"
		<<endl;

    return;
}

void BondStreamingServiceConnector::Subscribe(){
}

void BondStreamingService::PublishPrice(PriceStream<Bond>& priceStream){
	bondStreamingServiceConnector->Publish(priceStream);
	return;
}

#endif