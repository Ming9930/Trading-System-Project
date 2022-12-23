/**
 * AlgoStream.hpp
 * class with a reference to an PriceStream object
 *
 * @author Ming Fu
 */

#ifndef ALGO_STREAM_HPP
#define ALGO_STREAM_HPP

#include "streamingservice.hpp"
#include "pricingservice.hpp"
#include "products.hpp"
#include <iostream>

using namespace std;

class AlgoStream{
private:
	PriceStream<Bond> priceStream;
public:
	// ctor
	AlgoStream(const PriceStream<Bond>& _priceStream);
	
	// update priceStream according to bond price
	void RunAlgo(Price<Bond> price);
	
	PriceStream<Bond> GetPriceStream() const;
};


AlgoStream::AlgoStream(const PriceStream<Bond>& _priceStream):priceStream(_priceStream){
}

void AlgoStream::RunAlgo( Price<Bond> price){
	auto bond = price.GetProduct();
	if(bond.GetProductId() != priceStream.GetProduct().GetProductId()) return;
    
	float mid=price.GetMid();
	float spread=price.GetBidOfferSpread();
	float bid = mid - spread / 2.0;
	float offer = mid + spread / 2.0;
	
	// only aggress when the spread is at its tightest 
	// to reduce the cost of crossing the spread
	if(spread<2/256.0){
		PriceStreamOrder order_bid(bid, 1000000, 2000000, BID);
		PriceStreamOrder order_ask(offer, 1000000, 2000000, OFFER);
		priceStream = PriceStream<Bond>(bond, order_bid, order_ask);
	}
    else{
		PriceStreamOrder order_bid(bid, 0, 0, BID);
		PriceStreamOrder order_ask(offer, 0, 0, OFFER);
		priceStream = PriceStream<Bond>(bond, order_bid, order_ask);
	}
	
	return;
}


PriceStream<Bond> AlgoStream::GetPriceStream() const{
	return priceStream;
}
#endif 