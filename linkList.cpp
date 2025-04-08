
class LinkedList
{
		private:
	
		class llnode
		{
			public: 
			llnode(){}
			int data; 
			llnode* next; 
			llnode* previous;
		};

		int nodeCount; 
		llnode* head; 
		llnode* tail;
	
		public:
	
		LinkedList()
		{
			int nodeCount = 0; 
			head = nullptr;
			tail = nullptr; 
		}

		// ---- insert at end
		void insert(int num)
		{
			llnode* newNode = new llnode(); 

			if (nodeCount == 0) 
			{
				head = newNode; 
				tail = newNode; 
				nodeCount++; 
			}
			else
			{
				tail -> next = newNode; 
				newNode -> previous = tail; 
				
				tail = newNode; 

				tail -> next = head; 
				head -> previous = tail; 
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
		// ------- view data at first node
		int peek()
		{
			return head->data; 
		}
		// ------- print entire list
		void print()
		{
			/*
			llnode* travelNode = head;
			for(int i =0; i < nodeCount; i++)
			{
				std::cout << travelNode->data << std::endl; 
				travelNode = travelNode->next; 
			}
			*/
		}
		// ------- find specific node
		void findNode(int num)
		{
		}
};
