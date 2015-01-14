//Code by Ethan Revere Smith, 1/13/2015 from 7:15 to 11:15. Please see the README.txt in the folder.



#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

struct Node{
	int v;
	Node* next;
	Node* previous;
};

class DList{
	Node* head;
	//This class is just a doubly linked list, with some modified functions
public:
	DList()
	{
		head = NULL;
	}
	
	void insert(int value)
	{
		//Inserts at the FRONT of the list, every time
		Node* newNode = NULL;

		newNode = (struct Node *)malloc(sizeof(struct Node));  

		newNode->v = value;
		newNode->next = NULL;
		newNode->previous = NULL;

		if(head == NULL) //If there is nothing in the list
		{
			head = newNode;		
		}

		else if(head != NULL) //If there is already something here
		{
			newNode->next = head;
			head->previous = newNode;

			head = newNode;
		}

	}

	int peek()
	{
		//Takes a peek at the FRONT of the list
		if(head != NULL)
		{
			return head->v;
		}
		else return 0;
	}

	void Remove()//Removes the FRONT of the list. 
	{
		struct Node* p = head;
		struct Node* temp = NULL;


		if(p->next != NULL)
		{
			temp = p;
			head = p->next;
			head->previous = p->previous;
			free(temp);
		}
		else //If there isn't enough to remove, just set the head back to nothing
			head = NULL;
	}

	bool isEmpty()
	{
		//Checks if there's anything in this list
		if(head == NULL)
			return true;
		else
			return false;
	}

	void sortUp()
	{
		//Standard Bubble Sort, from lowest to highest. 
		int swapped;
		struct Node *i, *p, *j;

		j = head;

		while(j->next != NULL) //This iterates N-1 amount of times, where N is the amount of elements in the Linkedlist
		{
			p = head;
			swapped = 1;
			while(p->next != NULL) //This is the iterator that goes through each element in the list one by one
			{
				swapped = 0;
				i = p;
				if(i->next == NULL)
					break;
				while(swapped != 1) //This is the iterator goes through every element after P for each iteration of P
				{
					if(i->next == NULL)
						break;
			
					if(i->v > i->next->v)
					{
						swapData(i,i->next);
						i = i->next;
					}
					else swapped = 1;
				}
				p = p->next;
			}
			j = j->next;
		}
	}

	void sortDown()
	{ 
		//A modified version of SortUp. Does the same thing, but sorts from highest to lowest instead.
		int swapped;
		struct Node *i, *p, *j;

		j = head;

		while(j->next != NULL) //This iterates N-1 amount of times, where N is the amount of elements in the Linkedlist
		{
			p = head;
			swapped = 1;
			while(p->next != NULL) //This is the iterator that goes through each element in the list one by one
			{
				swapped = 0;
				i = p;
				if(i->next == NULL)
					break;
				while(swapped != 1) //This is the iterator goes through every element after P for each iteration of P
				{
					if(i->next == NULL)
						break;
			
					if(i->v < i->next->v)
					{
						swapData(i,i->next);
						i = i->next;
					}
					else swapped = 1;
				}
				p = p->next;
			}
			j = j->next;
		}
	}

	void swapData(struct Node* first, struct Node* second) //Swaps the data between two nodes
	{
		//Important for sorting
		int temp = first->v;
		first->v = second->v;
		second->v = temp;
	}

	void print()
	{
		//Used for finding errors
		struct Node* p;
		p = head;

		while(p != NULL)
		{
			cout<<p->v<<"->";
			p = p->next;
		}

	}

};


class Elevator{
//Each individual elevator object
private:

	int currentFloor; //Let us assume that the floors start at 0 and can go as high as the hotel goes. 
	int dest_floor; //This is the destination floor. This variable changes frequently.

	int timer; //This is used for timing

	int speed; //This is the amount of seconds it takes for an elevator to go up or down a floor. Therefore, 1 is actually the fastest speed, and 10 would be much slower.

	DList UpQ; //The Queue of upward destinations
	DList DownQ; //The Queue of downward destinations

	string name; //ID
	string state; //Can be Still, Up, or Down

public:
	Elevator(int f, string n, int s) //Constructor
	{
		currentFloor = f;
		dest_floor = f; //Sets original destination floor to the currentFloor to avoid any conflicts
		name = n;
		speed = s;
		timer = 0;
		state = "Up"; //Starts the elevator going up. No reason in particular- it could have started by going down as well. 
	};

	void setDestination(int d)
	{
		if(d > currentFloor)//This floor is above us, add it to the Q and sort it
		{
			UpQ.insert(d); 
			UpQ.sortUp();
		}
		else if(d < currentFloor)//This floor is below us, add it to the Q and reverse sort it
		{
			DownQ.insert(d);
			DownQ.sortDown();
		}
		else if(d == currentFloor) //We are already here, don't do anything
		{
			return;
		}
	}

	void Update() //This is called every second by the infinite loop in Main.
	{
		cout<<name<<":  ";

		if(state == "Up")
		{
			if(timer == 0)
			{
				if(UpQ.isEmpty()) //If we no longer have any upwards destinations,
				{
					if(!(DownQ.isEmpty())) //Check to see if we have downward destinations
						state = "Down";
					else
						state = "Still";
				}
				else
				{
					dest_floor = UpQ.peek(); //Sets next upward destination
					int distance = (abs (currentFloor - dest_floor)); //The numerical distance between floors
					timer = speed * distance;
				}
			}
			

		}

		if(state == "Down")
		{
			if(timer == 0)
			{
				if(DownQ.isEmpty()) //If we no longer have downward destinations,
				{
					if(!(UpQ.isEmpty())) //Check to see if we have upward destinations
						state = "Up";
					else
						state = "Still";
				}
				else
				{
					dest_floor = DownQ.peek(); //Sets downward destination
					int distance = (abs (currentFloor - dest_floor)); //The numerical distance between floors
					timer = speed * distance;
				}
			}
			

		}


		if(state != "Still")
		{
			//Prints the status of the elevator
			cout<<"Going "<<state<<" to floor "<<dest_floor<<". \n";
		}
		else
			cout<<"is Still.\n"; //Once something is still, it can't do anything else. This is because there are no way to currently give instructions once the program has started.


		if(timer > 0)
		{
			timer--; //Ticks down the timer every second
			cout<<timer<<" seconds remain until destination.";

			if(timer == 0)//When timer HITS 0 
			{
				if(state == "Up")
				{
					UpQ.Remove(); //Shaves off the FRONT of UpQ once it reaches that destination and updates our current floor
					currentFloor = dest_floor; 
				}
				else if(state == "Down")
				{
					DownQ.Remove(); //Shaves off the FRONT of DownQ and updates our current floor
					currentFloor = dest_floor;
				}
			}
		}

	}


};

class Shaft{
private:
	//Contains all of the individual elevators
	vector<Elevator> elevators;

public:
	Shaft(){

	};

	void Insert(Elevator e){
		elevators.push_back(e);
	}

	void UpdateAll()
	{
		for(int i = 0; i< elevators.size(); i++)
		{
			elevators.at(i).Update();
		}

	}
	



};

int main()
{
	//Keep this, basic declarations
	Shaft mainShaft;

	//Declare elevators (floor that it starts on, name, and how many seconds it takes to go one floor)
	Elevator myElevator(5,"Elevator1", 2);


	//Push some buttons on this elevator to set its destination
	myElevator.setDestination(4);
	myElevator.setDestination(2);
	myElevator.setDestination(10);

	//Add your elevators to the list of all elevators
	mainShaft.Insert(myElevator);


	int i = 0;
	while(i != -1)//Infinite Loop that manages timing
	{
		i++;
		cout<<"\n\n"<<i<<": ";
		mainShaft.UpdateAll();
		Sleep(1000);
	}


	return 0;
} 