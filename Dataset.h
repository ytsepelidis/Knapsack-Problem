#ifndef DATASET_H
#define DATASET_H

#include <vector>

class Dataset
{
public:
	int knapsackCap;
	int numOfObjs;
	std::vector<int> weights;
	std::vector<int> values;
	int finalWeight;
	int finalValue;

	Dataset();
	~Dataset();
	void PrintDataset() const;
	void PrintResults() const;
	void ResetResults();
};

class Object
{
public:
	int pos;
	int wt;
	int val;

	Object(int pos, int wt, int val);
	bool operator<(const Object& rhs);
	bool operator>(const Object& rhs);
};

#endif // DATASET_H