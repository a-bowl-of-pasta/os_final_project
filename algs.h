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
		
		int* nonDups = new int[20];

		delete list; 
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