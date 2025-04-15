#ifndef LINKED_LIST_H
#define LINKED_LIST_H

class LinkedList
{
		private:
	
		class llnode
		{
			public: 
			llnode(int num)
			{
				data = num;
			}
			int data; 
			llnode* next; 
			llnode* previous;
		};

		int nodeCount;
		int fsize;  
		llnode* head; 
		llnode* tail;
		llnode* travelPtr; 
	
		public:
	
		LinkedList(int frameSize)
		{
			int nodeCount = 0; 
			fsize = frameSize; 
			head = nullptr;
			tail = nullptr; 
			travelPtr = nullptr; 
		}

		// ---- insert at end
		void insert(int num)
		{
			llnode* newNode = new llnode(num); 

			if (nodeCount == 0) 
			{
				head = newNode; 
				tail = newNode; 
				travelPtr = head; 
				nodeCount++; 
			}
			else
			{
				tail -> next = newNode; 
				newNode -> previous = tail; 
				
				tail = newNode; 

				tail -> next = head; 
				head -> previous = tail; 
				nodeCount++; 
			}
		}
		// ------- remove last node
		void removeEnd() 
		{
			tail = tail->previous; 
			delete tail->next; 
		
			tail -> next = head; 
			head -> previous = tail; 

			nodeCount--;   
		}
		// --------- remove first node
		void removeFirst()
		{
			if (nodeCount == 1)
			{
				delete head;
				head = nullptr;
				tail = nullptr;   
			}
			else
			{
				llnode* holder = head;
					
				head = head-> next;
				head -> previous = tail; 
				tail -> next = head; 

				delete holder; 

			}
			nodeCount --; 
		}
		void resetTravelPtr()
		{
			travelPtr = head; 
		}
		void jumpToLast_travelPtr()
		{
			travelPtr = tail; 
		}
		void moveRight_TravelPtr()
		{
			travelPtr = travelPtr -> next; 
		}
		void moveLeft_TravelPtr()
		{
			travelPtr = travelPtr -> previous; 
		}
		// -------- gets the frameSize
		int getFrameSize(){return fsize;}
		int getSize(){return nodeCount;}
		int getFirstNum() {return head->data;}
		int getLastNum(){return tail->data;}
		int getTravelPtrData(){return travelPtr->data;}
		bool travIsHead()
		{
			if(travelPtr == head)
			{
				return true;
			}
			else
			{
				return false; 
			}
		}
		bool travIsTail()
		{
			if(travelPtr == tail)
			{
				return true; 
			}
			else
			{
				return false; 
			}
		}
		
		~LinkedList()
		{
			
			if(nodeCount == 1)
			{
				delete head; 
				head = nullptr; 
				tail = nullptr;
				nodeCount--; 
			}
			else 
			{
				llnode* traveler = head; 
				while (traveler != tail)
				{
					llnode* temp = traveler; 
					traveler = traveler -> next; 
					delete temp;  
				} 
				delete tail; 
				tail = nullptr; 
				head = nullptr; 
				travelPtr = nullptr; 
			}
		}
			
};

#endif