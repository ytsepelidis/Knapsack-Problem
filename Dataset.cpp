#include <iostream>
#include "Dataset.h"

Dataset::Dataset()
{
	knapsackCap = 0;
	numOfObjs = 0;
	finalWeight = 0;
	finalValue = 0;
}

Dataset::~Dataset()
{
	std::vector<int>().swap(weights);
	std::vector<int>().swap(values);
}

void Dataset::PrintDataset() const
{
	std::cout << "Knapsack capacity: " << knapsackCap << "\n";
	std::cout << "Number of objects: " << numOfObjs << "\n";
	std::cout << "Cap\tValues\n";

	for (int i = 0; i < weights.size(); i++)
	{
		std::cout << weights[i] << "\t" << values[i] << "\n";
	}
}

void Dataset::PrintResults() const
{
	std::cout << "W: " << finalWeight << "/" << knapsackCap << ", V: " << finalValue << "\n";
}

void Dataset::ResetResults()
{
	finalWeight = 0;
	finalValue = 0;
}

Object::Object(int pos, int wt, int val)
{
	this->pos = pos;
	this->wt = wt;
	this->val = val;
}

bool Object::operator<(const Object& rhs)
{
	return wt < rhs.wt;
}

bool Object::operator>(const Object& rhs)
{
	return wt > rhs.wt;
}