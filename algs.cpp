#include "linkedList.cpp"
#include "String"
#include <iostream>
#include <iostream>
#include <fstream>


class Algorithms {

	int* readFile(string fileName, int size) {

		int i = 0;
		int* numbers = new int[size];
		ifstream file(fileName);
		file.open(fileName);

		if (!file.is_open()) {
			std::cout << "Error, file does not open! Check for errors.";
		}



		while (std::getline(file, number)) {
			if (number[i] = number[0] || number[1]) {
				i++
				continue;
			}
			else {
				file >> number[i];
				i++;
			}
		}

		file.close();
		return numbers;

	}

	void LinkedList:: fifo(int numbers[]) {
		LinkedList list;
		int arraySize = sizeof(numbers) / sizeof(numbers[0]);
		int[] nonDups = new int[20];

		for (int i = 0, i <= arraySize i++)
		{
	


	

		}
	}

	void checkDuplicates(int numbers[], int[] comparisonArray) {




	}

	
};



