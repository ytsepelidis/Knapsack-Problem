#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include "Dataset.h"
#include "Timer.h"

void KnapsackProblem();
void ReadDataset(std::string filename, Dataset& ds);
void TokenizeDataset(std::ifstream& file, Dataset& ds);
void Random(Dataset& ds);
void Greedy(Dataset& ds);
void DynamicProgramming(Dataset& ds);
void Testing(Dataset& ds);

#endif // FUNCTIONS_H