#include "Functions.h"

void KnapsackProblem()
{
    // std::array<std::string, 6> filenames = { "datasets/pr1_30", "datasets/pr2_50", "datasets/pr3_200", "datasets/pr4_400", "datasets/pr5_1000", "datasets/pr6_10000" };
    std::array<std::string, 5> filenames = { "datasets/pr1_30", "datasets/pr2_50", "datasets/pr3_200", "datasets/pr4_400", "datasets/pr5_1000" };
    std::string filename = "datasets/pr4_400";

    // Main driver code
    for (const auto& filename : filenames)
    {
        {
            Dataset ds;
            ReadDataset(filename, ds);

            // Timed solution approaches
            {
                Timer timer;
                Random(ds);
            }

            {
                Timer timer;
                Greedy(ds);
            }
            
            {
                Timer timer;
                DynamicProgramming(ds);
            }

            std::cout << '\n';
        }
    }

    // Dataset ds;
    // ReadDataset(filename, ds);
}

void ReadDataset(std::string filename, Dataset& ds)
{
    // Opening binary file for reading
    std::ifstream file(filename, std::ios::binary);

    // Error handling
    if (!file.is_open())
    {
        std::cout << "Unable to open file.\n";
        exit(EXIT_FAILURE);
    }

    // Tokenizing dataset
    TokenizeDataset(file, ds);

    std::cout << "Dataset '" << filename << "' was successfully parsed.\n";
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    // Closing binary file
    file.close();
}

void TokenizeDataset(std::ifstream& file, Dataset& ds)
{
    bool isFirst = true;
    std::string line;
    std::string token;
    std::stringstream sstream;
    std::vector<std::string> tokens;
    char delim = '\t';

    // Reading first line
    getline(file, line);

    // Filling stringstream with line
    sstream.str(line);

    // For knapsack capacity and number of objects
    while (getline(sstream, token, delim))
    {
        if (isFirst)
        {
            ds.knapsackCap = stoi(token);
            isFirst = false;
        }
        else
        {
            ds.numOfObjs = stoi(token);
            isFirst = true;
        }
    }

    // Clearing stringstream
    sstream.clear();

    // Allocating space for vectors
    ds.weights.reserve(ds.numOfObjs);
    ds.values.reserve(ds.numOfObjs);

    // Reading file line by line
    while (getline(file, line))
    {
        // Filling stringstream with line
        sstream.str(line);

        // Tokenizing line
        while (getline(sstream, token, delim))
        {
            if (isFirst)
            {
                // std::cout << "Weight is: " << token << "\n";
                ds.weights.push_back(stoi(token));
                isFirst = false;
            }
            else
            {
                // std::cout << "Value is: " << token << "\n";
                ds.values.push_back(stoi(token));
                isFirst = true;
            }
        }

        // Clearing stringstream
        sstream.clear();
    }
}

void Random(Dataset& ds)
{
    int randObj = 0;
    int range = ds.numOfObjs;
    std::vector<int> isTaken(ds.numOfObjs, 0);

    // Seed value for rand()
    srand((unsigned int)time(NULL));

    // Adding objects to knapsack
    while (true)
    {
        // Choosing object randomly
        randObj = rand() % range;

        if (isTaken[randObj] != 0)
        {
            continue;
        }

        // Adding the weight and value
        ds.finalWeight += ds.weights[randObj];
        ds.finalValue += ds.values[randObj];
        isTaken[randObj] = 1;

        if (ds.finalWeight > ds.knapsackCap)
        {
            ds.finalWeight -= ds.weights[randObj];
            ds.finalValue -= ds.values[randObj];
            isTaken[randObj] = 0;

            break;
        }
    }

    std::cout << "Random -> ";
    ds.PrintResults();
    ds.ResetResults();
}

void Greedy(Dataset& ds)
{
    std::vector<std::pair<double, int>> valDivWt;
    std::pair<double, int> pair;

    // Allocating memory for vector valDivWt
    valDivWt.reserve(ds.numOfObjs);

    // Filling vector
    for (int i = 0; i < ds.numOfObjs; i++)
    {
        // pair = std::make_pair((double)ds.values[i] / ds.weights[i], i);
        valDivWt.emplace_back(std::make_pair((double)ds.values[i] / ds.weights[i], i));
    }

    // Sorting vector by value divided by weight
    std::sort(valDivWt.begin(), valDivWt.end(), std::greater<>());

    // Adding objects to knapsack
    int pos;

    for (int i = 0; i < valDivWt.size(); i++)
    {
        // Getting object position
        pos = valDivWt[i].second;

        if (ds.finalWeight + ds.weights[pos] <= ds.knapsackCap)
        {
            ds.finalWeight += ds.weights[pos];
            ds.finalValue += ds.values[pos];
        }
    }

    std::cout << "Greedy -> ";
    ds.PrintResults();
    ds.ResetResults();
}

void DynamicProgramming(Dataset& ds)
{
    int c1, c2;
    std::vector<std::vector<int>> table(ds.numOfObjs + 1, std::vector<int>(ds.knapsackCap + 1));

    // Calculating maximum value
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[i].size(); j++)
        {
            if (i == 0 || j == 0)
            {
                table[i][j] = 0;
                continue;
            }

            if (ds.weights[i - 1] <= j)
            {
                c1 = table[i - 1][j];
                c2 = table[i - 1][j - ds.weights[i - 1]] + ds.values[i - 1];

                if (c1 < c2)
                {
                    table[i][j] = c2;
                }
                else
                {
                    table[i][j] = c1;
                }
            }
            else
            {
                table[i][j] = table[i - 1][j];
            }
        }
    }

    // Saving final value
    ds.finalValue = table[ds.numOfObjs][ds.knapsackCap];

    // Finding which items were chosen
    int i = ds.numOfObjs;
    int j = ds.knapsackCap;

    while (true)
    {
        if (i == 0)
        {
            break;
        }

        if (table[i][j] == table[i - 1][j])
        {
            i -= 1;
        }
        else
        {
            ds.finalWeight += ds.weights[i - 1];

            j -= ds.weights[i - 1];
            i -= 1;
        }
    }

    std::cout << "Dynamic Programming -> ";
    ds.PrintResults();
    ds.ResetResults();
}

void Testing(Dataset& ds)
{
    std::vector<Object> obj;

    // Allocating memory for vector obj
    obj.reserve(ds.numOfObjs);

    // Emplacing objects in vector
    for (int i = 0; i < ds.numOfObjs; i++)
    {
        obj.emplace_back(i, ds.weights[i], ds.values[i]);
    }

    for (int i = 0; i < obj.size(); i++)
    {
        std::cout << "Pos: " << obj[i].pos << ", W: " << obj[i].wt << ", V: " << obj[i].val << "\n";
    }

    std::sort(obj.begin(), obj.end(), std::greater<>());
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    for (int i = 0; i < obj.size(); i++)
    {
        std::cout << "Pos: " << obj[i].pos << ", W: " << obj[i].wt << ", V: " << obj[i].val << "\n";
    }
}