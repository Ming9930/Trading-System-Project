/**
 * BondInquiryService.hpp
 * read inquiries from inquires.txt and publish via socket into the trading system
 *
 * @author Ming Fu
 */

#ifndef BOND_INQUIRY_SERVICE_HPP
#define BOND_INQUIRY_SERVICE_HPP

using namespace std;

#include "BondInquiryServiceConnector.hpp"
#include <string>
#include <map>
#include <vector>

class BondInquiryService: public InquiryService<Bond>{
private:
    map<string, Inquiry<Bond> > inquiryMap;  
	vector<ServiceListener<Inquiry<Bond> >*> listenerList;

public:
    // ctor
    BondInquiryService();

	// get inquiry given id
    virtual Inquiry<Bond> & GetData(string id) override;   

    virtual void OnMessage(Inquiry<Bond> &inquiry) override;        

	// add BondHistoricalDataServiceListeners
    virtual void AddListener(ServiceListener<Inquiry<Bond> > *listener) override;  
	
	// get BondHistoricalDataServiceListeners
    virtual const vector<ServiceListener<Inquiry<Bond> > *>& GetListeners() const override;  
	
    virtual void SendQuote(const string& inquiryId, double price) override{} 
	
    virtual void RejectInquiry(const string &inquiryId) override{}
	
};

BondInquiryService::BondInquiryService(){
	inquiryMap=map<string, Inquiry<Bond> >();
}

Inquiry<Bond> & BondInquiryService::GetData(string id){
	return inquiryMap.at(id);
}

void BondInquiryService::OnMessage(Inquiry<Bond> &inquiry){
	inquiry.SetState(inquiry.GetPrice(), DONE);
    inquiryMap.insert(pair<string,Inquiry<Bond> >(inquiry.GetInquiryId(),inquiry));
    for(auto& listener : listenerList) {
        listener->ProcessAdd(inquiry); 
	}
	
	return;
}

void BondInquiryService::AddListener(ServiceListener<Inquiry<Bond> > *listener){
	listenerList.push_back(listener);
	return;
}

const vector<ServiceListener<Inquiry<Bond> > *>& BondInquiryService::GetListeners() const{
	return listenerList;
}


void BondInquiryServiceConnector::Subscribe(){
	ifstream input;
	// read inquiries from a file
	input.open("inquiries.txt");
	string row;
	
	while (getline(input, row)) {
		stringstream line(row);
		string temp;
		// id
		getline(line, temp, ',');   
		string inquiry_ID = temp;
		// bond
		getline(line, temp, ',');
		auto bond = bondProductService->GetData(temp);
		// B/S
		getline(line, temp, ',');
		Side side = (temp=="BUY" ? BUY:SELL);
        // quantity
		getline(line, temp, ',');
		long quantity = stol(temp);
		// quote
		getline(line, temp, ',');
		double quote = TransformStringToPrice(temp);
            
		getline(line, temp, ',');
		InquiryState state_ = RECEIVED;
		
		Inquiry<Bond> inquiry(inquiry_ID, bond, side, quantity, quote, state_);
		bondInquiryService -> OnMessage(inquiry);
	}
	return;
}

#endif