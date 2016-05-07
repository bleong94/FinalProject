#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	vector<unsigned long long> counts; //will keep counts of cells with each number of divisions left. 
	int gens; //number of generations
	int divs = 0; //number of times cells can divide
	unsigned long long numCells = 0; //total number of cells


	while (divs < 40 || divs > 60) //makes sure that user inputs between 40 and 60
	{
		cout << "Cells can only divide between 40 and 60 times. Please input how many times you would like a cell can divide: ";
		cin >> divs;
	}

	cout << "Each time the cells divide, a new generation of cells are created. What generation would you like to see a snapshot of? Generation: ";
	cin >> gens;

	for (int i = 0; i <= divs; i++) //initialize everything in vector as zero
	{
		counts.push_back(0);
	}

	counts[divs] = 1; //generation 0 = 1 cell before any divisions


	if (gens >= divs)
	{
		int dying1, dying2; //cells that will die after generations are larger than divs
		
		for (int i = 0; i < divs-1; i++) //divisions for gens before cells start to die
		{
			
			if (i % 2 == 0) //counts[1] are cells that are about to die next generation so that we can subtract from multiplication in 2 generations so need 2 dyings so only 1 changes each gen
			{
				dying1 = counts[1];
			}
			else
			{
				dying2 = counts[1];
			}

			for (int j = 1; j < divs; j++) //since all cells lose 1 life each generation the number of cells with n lives will be equal to number of cells with n-1 lives next generation
			{
				counts[j] = counts[j + 1];
			}

			if (i != 0) //double amount of new cells each division
			{
				counts[divs] = 2 * counts[divs];
			}
		}

		

		for (int i = divs; i <= gens; i++) //divisions for when cells start to die 
		{
			if (i % 2 == 0)
			{
				dying1 = counts[1];
			}
			else
			{
				dying2 = counts[1];
			}

			counts[0] = counts[0] + counts[1]; //count for dead cells is equal to current dead cells plus cells that had 1 division left in last generation which is why it is before the loop below

			for (int j = 1; j < divs; j++) //since all cells lose 1 life each generation the number of cells with n lives will be equal to number of cells with n-1 lives next generation
			{
				counts[j] = counts[j + 1];
			}
			
			if (i % 2 == 0) //subtract cells that died last generation because dead cells can't be multiplied again
			{
				counts[divs] = 2 * counts[divs] - dying2; //since some cells die now need to subtract these dead cells from multiplication
			}
			else
			{
				counts[divs] = 2 * counts[divs] - dying1;
			}
		
			
		}
	}
	else //for when gens < divs
	{
		for (int i = 0; i < gens; i++) 
		{
			for (int j = 1; j < divs; j++) //since all cells lose 1 life each generation the number of cells with n lives will be equal to number of cells with n-1 lives next generation
			{
				counts[j] = counts[j + 1];
			}

			if (i != 0) //double amount of new cells each division
			{
				counts[divs] = 2 * counts[divs];
			}
		}
	}
	
	

	for (int i = 1; i < counts.size(); i++)
	{
		numCells = numCells + counts[i];
	}

	cout << "In this generation there are " << numCells << " cells alive." << endl;


	cout << counts[0] << " cells died." << endl;

	for (int i = divs; i >0; i--)
	{
		if (counts[i] != 0)
		{
			cout << "There are " << counts[i] << " cells that can still divide " << i << " times." << endl;
		}
	}

	system("pause");
}