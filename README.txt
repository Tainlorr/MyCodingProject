Elevator Program README.

This program was created in Visual Studio 2012, and uses
the C++ compiler that comes with that.

Everything in this program was written by Ethan Revere Smith, during the alotted timeframe of the assignment (from 7:15PM to 11:15PM AZ time)


I. Build Instructions:

1. Open Project in Visual Studio
2. Compile and Run


OR, if you do not have Visual Studio, 

1. Open and compile "Main.cpp" using another C++ compiler,
and hope for the best. I have not tested it with GNU, but
it should still work.


II. Solution and Data Structures

To solve the elevator problem, I broke it up into as many 
data structures and small components as I could. 

From the top down:

First of all, we have a SHAFT object. The SHAFT stores all of the user's elevators. Having a shaft
allows the user to set boundaries on the building (floor height, or something like that) and it
manages the updating of all elevators simultaneously.

The SHAFT object has a vector of ELEVATORS. The ELEVATOR object is where most of the work and calculations
are done. In order to solve the queueing problem, each ELEVATOR has two linked lists called UpQ and DownQ.

UpQ and DownQ are made up of very simple NODE structs. 

Essentially, when the elevator gets a new destination, it thinks like this:

- Is that floor above the elevator? 
	- Put it in the UpQ, we know it's above us
	- Sort (lowest to highest) the UpQ in order to hit all floors in the right sequence
- Is that floor below the elevator?
	- Put it in the DownQ, we know it's below us
	- Reverse Sort (highest to lower) the DownQ in order to hit all floors in the right descending sequence



III. Using the Program:

The user interface isn't particularly friendly. If you scroll down
to the main function, you can essentially feed your elevator system 
commands from there. You can create new elevators by writing:

Elevator thisElevator(floor that it starts on, name, and how many seconds it takes to move up/down a floor)

and add it to the shaft by writing:

mainShaft.Insert(thisElevator);


From there, the only command that you can actually feed to the elevators is setDestination(floor #).

The elevators will handle all of the floor numbers you give to them, in the correct order.
For example, if I start an elevator at floor 7 and tell it to go to floor 3, floor 10, floor 2, and floor 8, it 
will behave like this:

The elevator will go to floor 8 first, since it is predisposed to going up.
Then the elevator will go to floor 10. Once it has no more upper floors to go to, 
it will go down to floor 3, and then floor 2.


Unfortunately there is no way to add new destinations while the program is running- I didn't have time
to implement a working user interface or anything like that.


Known Issues:

One of the main drawbacks of this program is that there's no way to feed it destinations after it's already started.
The Elevators themselves could actually handle it fine, but I didn't have time to write a UI that could take inputs.

Also there's no way to just "check" on the elevators- I opted for a display that CONSTANTLY updates the user about 
each elevator. This can be easily changed.

Lastly, a major issue is that the elevators don't always know what floor they are on. CurrentFloor is only updated
when an elevator reaches its destination. Therefore, all of the intermediary destinations aren't recorded.
This can be solved by working with my timer and my distance algorithm.

