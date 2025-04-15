#ifndef ALGS_H
#define ALGS_H

#include "linkList.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


class Algorithms {

	private: LinkedList* readFile(std::string fileName) {
		
		std::ifstream file(fileName);
		file.open(fileName);

		if (!file.is_open()) {
			std::cout << "Error, file does not open! Check for errors.";
		}

		int i = 0;
		LinkedList* numbers = nullptr;

		std::string number; 
		std::string line; 
		std::getline(file, line);
		std::stringstream ss(line); 

		while (getline(ss, number, ',')) {
			
			try 
			{
				if(i == 0)// frame size
				{
					int frameSize = stoi(number);
					numbers = new LinkedList(frameSize);
					i++; 
				}
				else // stores the pages 
				{
					numbers->insert(stoi(number));
				}

			}catch(...)
			{}	
		}
		
		
		file.close();
		return numbers;

	}

	private: void pageToReplace()
	{

	}

	// ================ algorithms ============	
	public: void fifo(std::string filename) {

		LinkedList* list = readFile(filename);
		int frameSize = list->getFrameSize();
		int totalSize = list->getSize();

		int** nonDups = new int*[frameSize];

		int current = list->resetTravelPtr();
		

		//Initialize 2d array
		for (int i = 0; i < frameSize; i++) {
			nonDups[i] = new int[totalSize];
			for (int j = 0; j < totalSize; j++)
			{
				nonDups[i][j] = -1; //empty array
			}
		}

		int count = 0;
		int hit = 0;

		for (int i = 0; i < totalSize; i++)
		{
			current = list->getTravelPtrData();

			//Copys previous data over
			for (int previous = 0; previous < i; previous++) {
				for (int row = 0; row < frameSize; row++) {
					if (previous != 0 && row != 0 && i != 0) {
					
						nonDups[row][i] = nonDups[row][previous];
					}
					 
				}
			}

			//Checks value to see if it needs to be replaced/inserted
			for (int j = 0; j < frameSize; j++) {
				if (current == nonDups[j][i]) {
					continue;
				}
				elseif(current != nonDups[j][i] && nonDups[j][i] == -1) {
					nonDups[j][i] = current;
					hit++;
					break;
				}
				elseif(current != nonDups[j][i] && nonDups[j][i] != -1)
				{
					fifoReplace(i, nonDups, list);
					nonDups[j][i] = current;
					hit++;
					break;
	
				}
	
			}

			current = list->moveRight_TravelPtr();
			
		}
	

		delete list; 
	}

	private: void fifoReplace(int i, int** nonDups, LinkedList list) {

		int firstMostNum = 0;
		int frameSize = list->getFrameSize();

		//Finds oldest value within the column
		for (int previous = 0; previous < i;, ++previous) {
			for (int row = 0; row < frameSize; ++row) {
				while (nonDups[row][previous != -1]) {

					firstMostNum = nonDups[row][previous];
				}

			}
		}

		//Removes oldest value in column
		for (int row = 0; row < frameSize; row++) {
			if (nonDup[row][i] == firstMostNum) {
				nonDups[row][i] = -1;
				break;
			}
		}



	}




	public: void optAlg(std::string filename)
	{
		LinkedList* optList = readFile(filename);

		int fs[optList->getFrameSize()]  = {0}; // fs = frame slots
		int hitCount =0; 
		int missCount =0; // other word for a page fault

		/*
		std::string outputFileName = "opt_output.txt";
		std::ofstream output(outputFileName);
		output.open(outputFileName); 
		*/

		int outputArray[optList->getFrameSize()][optList->getSize()] = {0}; 
		int columnTracker = 0;
		
		while(columnTracker <= optList->getSize())
		{
			int dtbi = optList->getData(); // dtbi = data to be inserted
			for(int i =0; i < optList->getFrameSize(); i++)
			{
				
			}

		}
		
		delete optList; 
	}

	Algorithms(){}
};

#endif