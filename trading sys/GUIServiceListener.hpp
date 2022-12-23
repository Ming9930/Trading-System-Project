/*
 * GUIServiceListener.hpp
 *
 * @author: Ming Fu
 */
#pragma once

#ifndef GUI_SERVICE_LISTENER_HPP
#define GUI_SERVICE_LISTENER_HPP

#include "soa.hpp"
#include "GUIService.hpp"

using namespace std;

class GUIServiceListener: public ServiceListener<Price<Bond> >{
private:
	GUIService* guiService;
public:
	// ctor
	GUIServiceListener(GUIService* _guiService);
	
	virtual void ProcessAdd(Price<Bond>& price) override; 
	
	virtual void ProcessRemove(Price<Bond>&) override{};  
	
	virtual void ProcessUpdate(Price<Bond>&) override{};  
};

GUIServiceListener::GUIServiceListener(GUIService* _guiService){
	guiService =_guiService;
}

void GUIServiceListener::ProcessAdd(Price<Bond>& price){
	guiService->SendToThrottle(price);
	return;
}






#endif