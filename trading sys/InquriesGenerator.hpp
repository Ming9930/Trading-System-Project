/**
 * InquiryGenerator.hpp
 * generate inquiries.txt
 * 
 * @author: Ming Fu
 */ 
#pragma once

#ifndef INQURIES_GENERATOR_HPP
#define INQURIES_GENERATOR_HPP

using namespace std;

#include "BondInformation.hpp"
#include <fstream>
#include <sstream>
#include <random>
#include <vector>
#include <string>

class InquriesGenerator 
{
public:
	// ctor
	InquriesGenerator();

	// overload ( operator
	void operator()(int n);
};


InquriesGenerator::InquriesGenerator() 
{
}

void InquriesGenerator::operator()(int n) 
{
	ofstream output;
	output.open("inquiries.txt");
	// output << "id, cusip, B/S, trades, quotes" << endl;
	
	// for each bond, we would generate n data
	// in total, 7*n lines are generated
	// Counter
	vector<int> counter = { 0,0,0,0,0,0,0 };
	
	for (int i = 0; i < 7 * n; i++) {
		int j = rand() % 7;
		// if jth bond already has n data
		while (counter[j] == n){
			j = rand() % 7;
		}
		string cusip= bondCusip[j];
		counter[j]++;
		
		// output to file
		// id
		string id = to_string(i);
		stringstream ss;
		ss << setw(10) << setfill('0') << id;
		ss >> id;
		output << id << "," << cusip << ",";
		
		// buy or sell
		output << (rand() % 2 == 0 ? "BUY" : "SELL") << ",";
		
		// quantity
		output << to_string((rand() % 5 + 1) * 1000000) << ",";
		
		// price
		// integer part
		int a = rand() % 2 + 99;
		string A = to_string(a);
		// factional part
		int xy = rand() % 32;
		int z = rand() % 8;
		string XY = to_string(xy);
		string Z = to_string(z);
		if (XY.size() < 2) XY = "0" + XY;
		if (z == 4) Z = "+";
		// fractional notation
		string price = A + "-" + XY + Z;
		output << price << ",";
		
		output <<endl;
	}
	output.close();
	return;
}
#endif