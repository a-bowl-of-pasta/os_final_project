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

	private: int pageToReplace(LinkedList* refLst, int* frame, int frameSize)
	{
		int replacmentIndex = -100; 
		int compIndex = 0; //tnmc = travel node move count
		bool done = false; 
		// ---------- checks for empty slot
		for(int i =0; i < frameSize; i++)
		{
			if(frame[i] == -1)
			{
				replacmentIndex = i; 
				done = true; 
				i = frameSize -1; 
			}


		}
		// ------- checks for a replacment number
		if(done == false)
		{
			for(int i =0; i < frameSize; i++)
			{
				int moveCount =0; 
				bool frameCheckComplete = false; 

				// checks frame i against remaining list
				while(frameCheckComplete != true)
				{
				// repeate found; has not circled back to head; compIndex is less than moveCount
					if(frame[i] == refLst->getTravelPtrData() && refLst->travIsHead() != true && moveCount >= compIndex)
					{
						compIndex = moveCount; 
						replacmentIndex = i; 
						frameCheckComplete =true; 
					}
					else if (refLst->travIsHead() == true) // if not repeat -> compIndex = -1 and replaceIndex = i
					{
						compIndex = -1; 
						replacmentIndex = i; 
						frameCheckComplete = true;
					}

					refLst->moveRight_TravelPtr(); 
					moveCount++; 
				}
				for(int j =0; j< moveCount;j++ )
				{
					refLst->moveLeft_TravelPtr();
				}
			
			}
		}
	 return replacmentIndex;
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

		int hitCount =0; 
		int missCount =0; // other word for a page fault

		int outputArray[optList->getFrameSize()][optList->getSize()] = {0}; 
		
		// ---- sets default values of matrix to -1
		for(int i =0; i < optList->getFrameSize(); i++)
		{
			for(int j =0; j < optList->getSize(); j++) {outputArray[i][j] = -1; }
		}

		int columnTracker = 0;
	
		// ------- loops until the max column is hit
		while(columnTracker < optList->getSize())
		{
			bool hit = false; 
			int dtbi = optList->getTravelPtrData(); // dtbi = data to be inserted

			// ------- if we are currently passed column 1, copy previous column to current column
			if(columnTracker > 0)
			{
				for(int j = 0; j < optList->getFrameSize(); j++)
				{
					outputArray[j][columnTracker] = outputArray[j][columnTracker-1];
				}
			}
		
			// ------ loop through the rows (frame)
			for(int i =0; i < optList->getFrameSize(); i++) // check if num to be inserted is already in frame
			{
				
				if(dtbi == outputArray[i][columnTracker]) // if there is a hit, increase hitcount, and kill loop
				{
					hit = true; 
					hitCount++; 
					i = optList->getFrameSize()-1; 
				}
				else if(i == optList->getFrameSize()-1 && hit == false) // fault, page fault +1, hit stays false
				{
					missCount++; 
					// replace a node 
					// end loop 
				}	
			}

			// ---- move to next column and linked list node
			optList->moveRight_TravelPtr();
			columnTracker++; 
		}
		
		delete optList; 
	}

	Algorithms(){}
};

#endif