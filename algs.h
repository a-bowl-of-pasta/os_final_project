#ifndef ALGS_H
#define ALGS_H

#include "linkList.h"
#include <fstream>
#include <string>
#include <sstream>


class Algorithms {

// ================================== HELPER METHODS ===================
	private: bool isNumber(std::string number)
	{
		for(int i =0; i < number.length(); i++)
		{
			if(!isdigit(number.at(i)))
			{
				return false;  
			}
		}
		return true; 
	}
	
	private: LinkedList* readFile(std::string fileName) {
		
		std::ifstream file(fileName);

		if (!file.is_open()) {
			std::cout << "Error, file does not open! Check for errors.";
			return 0; 
		}

		int i = 0;
		LinkedList* numbers = nullptr;

		std::string number; 
		std::string line; 
		std::getline(file, line);
		std::stringstream ss(line); 
		
		// inserts node and creates list
		while (getline(ss, number, ',')) {
		
			if (!isNumber(number)) continue;
		
			if (i == 0) {
				numbers = new LinkedList(stoi(number));
			} else {
				numbers->insert(stoi(number));
			}
			i++;
		}
		
		
		file.close();
		return numbers;

	}

//  ================================== FIFO ALGORITHM ===================
	private: void fifoReplace(int i, int** nonDups, LinkedList* list) {

		int firstMostNum = 0;
		int frameSize = list->getFrameSize();

		//Finds oldest value within the column
		for (int previous = 0; previous < i; ++previous) {
			for (int row = 0; row < frameSize; ++row) {
				while (nonDups[row][previous != -1]) {

					firstMostNum = nonDups[row][previous];
				}

			}
		}

		//Removes oldest value in column
		for (int row = 0; row < frameSize; row++) {
			if (nonDups[row][i] == firstMostNum) {
				nonDups[row][i] = -1;
				break;
			}
		}



	}
	public: void fifo(std::string filename) {

		LinkedList* list = readFile(filename);

		int frameSize = list->getFrameSize();
		int totalSize = list->getSize();

		int** nonDups = new int*[frameSize];

		int current = list->getTravelPtrData();
		

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
						if(i > 0)
						{
							nonDups[row][i] = nonDups[row][i-1];
						}
					}

				}
			}

			//Checks value to see if it needs to be replaced/inserted
			for (int j = 0; j < frameSize; j++) {
				if (current == nonDups[j][i]) {
					continue;
				}
				else if(current != nonDups[j][i] && nonDups[j][i] == -1) {
					nonDups[j][i] = current;
					hit++;
					break;
				}
				else if(current != nonDups[j][i] && nonDups[j][i] != -1)
				{
					fifoReplace(i, nonDups, list);
					nonDups[j][i] = current;
					hit++;
					break;
	
				}
	
			}

			list->moveRight_TravelPtr();
			current = list->getTravelPtrData(); 
		}
	
		//Prints array
		std::cout << "Fifo Page Replacement Algorithm: \n";
		for (int i = 0; i < totalSize; i++) {
			for (int j = 0; j < frameSize; j++) {
				std::cout << nonDups[j][i] << " ";
			}
		}

		std::cout << std::endl;
		delete list; 
	}
	
// ====================================== OPT ALGORITHM =================
	private: int pageToReplace(LinkedList* refLst, int* frame, int frameSize)
	{

		int replacmentIndex = 0; 
		int compIndex = -100; //tnmc = travel node move count
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

					if(refLst->travIsTail() == true)// if not repeat -> compIndex = -1 and replaceIndex = i
					{
						compIndex = -1; 
						replacmentIndex = i;
						frameCheckComplete =true; 
					
					}
					else
					{
						// repeate found; has not circled back to head; compIndex is less than moveCount
						if(frame[i] == refLst->getTravelPtrData() && moveCount >= compIndex)
						{
							compIndex = moveCount; 
							replacmentIndex = i; 
							frameCheckComplete =true; 
						}
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
	
	public:void optAlg(std::string filename)
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
					int frame[optList->getFrameSize()];
					
					for(int i =0; i < optList->getFrameSize() ; i++)
					{
						frame[i] = outputArray[i][columnTracker];
					}
					
					missCount++; 
					outputArray[pageToReplace(optList, frame, optList->getFrameSize())][columnTracker] = dtbi; 
					i = optList->getFrameSize()-1; 
				}	
			}

			// ---- move to next column and linked list node
			optList->moveRight_TravelPtr();
			columnTracker++; 
		}
		
		// ========= print everything

		std::cout <<std::endl<< "opt algorithm" <<std::endl<< std::endl; 
		std::cout << "hit count = " << hitCount <<std::endl; 
		std::cout << "page faults = " << missCount << std::endl<<std::endl; 

		optList->resetTravelPtr();
		for(int i =0; i < optList->getSize(); i++)
		{
			std::cout << optList->getTravelPtrData() << "\t"; 
			optList->moveRight_TravelPtr(); 
		}
		std::cout << std::endl; 
		for(int i =0; i < 120; i++)
		{
			std::cout <<"-"; 
		}
		std::cout<<std::endl<<std::endl; 
		for(int i =0; i < optList->getFrameSize(); i++)
		{
			for(int j = 0; j < optList->getSize(); j++)
			{
				std::cout << outputArray[i][j] << "\t"; 
			}
			std::cout << std::endl;
		}

		delete optList; 
	}

// ======================== CONSTRUCTOR ====================
	Algorithms(){}
};

#endif
