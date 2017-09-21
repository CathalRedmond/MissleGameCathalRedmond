//@name: Cathal Redmond
//@login: C00214190
//----------------------
// Text based missle game
//----------------------
// Known Bugs:
// no known bugs


#include <iostream>
#include <string>
#include <stdlib.h>     
#include <time.h>


void warheadSelection();
void acquireTarget();
void inputLaunchCode();
void armAndFireMissle();
void update();
void restart();



typedef struct Position
{
	float x;	
	float y;

	void print()
	{
		std::cout << x << y << std::endl;
	}

}Coordinates;

enum Warhead { EXPLOSIVE, NUCLEAR };

typedef struct Enemy {
	Coordinates coordinates;
}Target;

struct Missle {
	Warhead payload;
	Coordinates coordinates;
	Target targets[5];
	bool armed;
	bool playerDead;
	bool hitDetected;
	int blastRadius = 20;		// radius of impact between target and missle
	int const NUMBER_OF_TARGETS = 5;		//number of enemy targets player can chose to hit
	int chosenTarget;

	// checks for collsion between player missle and enemy target
	bool collisionDetection()
	{
		bool coollsion = false;
		for (int index = 0; index < NUMBER_OF_TARGETS; index++)
		{
			if ((sqrt(((coordinates.x - targets[index].coordinates.x)*(coordinates.x - targets[index].coordinates.x))
				+ ((coordinates.y - targets[index].coordinates.y)*(coordinates.y - targets[index].coordinates.y)))) <= blastRadius)
			{
				coollsion = true;
				break;
			}
			else
			{
				coollsion = false;
			}
		}
		return coollsion;
	}

	// sets enemy target position
	void setUpEnemyCoordiantes()
	{
		for (int index = 0; index < NUMBER_OF_TARGETS; index++)
		{
			targets[index].coordinates.x = (rand() % 401);
			targets[index].coordinates.y = (rand() % 301);
		}
	}
	//sets missle position
	void intializeMisslePos()
	{
		coordinates.x = 200;
		coordinates.y = 400;
	}

	void arm()
	{
		if (armed)
		{
			armed = false;
		}
		else
		{
			armed = true;
		}
	}

	// causes player missle to aim for target 
	void update()
	{
		coordinates.x += ((targets[chosenTarget].coordinates.x - coordinates.x))/30;
		coordinates.y += ((targets[chosenTarget].coordinates.y - coordinates.y))/30;
	}

	void setMissleType(const int type)
	{
		if (type == NUCLEAR)
		{
			payload = NUCLEAR;
			
		}
		else if (type == EXPLOSIVE)
		{
			payload = EXPLOSIVE;
			
		}
	}
	std::string getMissleType()
	{
		std::string warheadTypeString = "";
		if (payload == NUCLEAR)
		{
			warheadTypeString = "NUCLEAR";
		}
		else if (payload == EXPLOSIVE)
		{
			warheadTypeString = "EXPLOSIVE";
		}
		return warheadTypeString;
	}
}playerMissle;

int main()
{
	srand(time(nullptr));		// used for random number
	warheadSelection();
	while (!playerMissle.playerDead)		// allows player to repeat unless player is dead
	{
		acquireTarget();
		inputLaunchCode();
		armAndFireMissle();
		if (!playerMissle.playerDead)			// only occurs if player is missle is viable 
		{
			update();
			restart();
		}
	}

	system("pause");
	return 0;
}

// function that allows player to choose which warhead for their missle
void warheadSelection()
{
	float warheadType = 0;		// input from user to choose warhead type
	int errorCounter = 0;			// used to check for error and output error message to screen
	while (warheadType != 1 && warheadType != 2 )	// repeats if acceptable numbers aren't inputted 
	{
		errorCounter++;
		if (errorCounter > 1)	// outputs error message if unacceptable numbers are inputted
		{
			std::cout << std::endl;
			std::cout << "Error, Only Enter the Numbers 1 or 2" << std::endl;
			std::cout << std::endl;
		}
		std::cout << "Which Type Of Warhead Would You Like?" << std::endl;
		std::cout << "1) EXPLOSIVE or 2) NUCLEAR" << std::endl;
		std::cin >> warheadType;
	}
	playerMissle.setMissleType(warheadType - 1);		// sets the current missle type
	std::cout << "You Have Chosen The " << playerMissle.getMissleType() << " Warhead " << std::endl;		// confirms player choice 
	std::cout << std::endl;
	system("Pause");
	std::cout << std::endl;
	warheadType = 0;		// resets value
	errorCounter = 0;		// resets value


}

// function that finds enemy targets to hit
void acquireTarget()
{
	int targetNumber = 0;			// which target is chosen to hit
	playerMissle.setUpEnemyCoordiantes();
	std::cout << "Five targets detected" << std::endl;
	for (int index = 0; index < playerMissle.NUMBER_OF_TARGETS; index++)		// repeats for all five targets
	{
		std::cout << "Target " << index +1 << " Located at X:" << playerMissle.targets[index].coordinates.x << " and Y:" << playerMissle.targets[index].coordinates.y << std::endl;
		std::cout << std::endl;
	}
	while (targetNumber != 1 && targetNumber != 2 && targetNumber != 3 && targetNumber != 4 && targetNumber != 5)	// checks if inputted value out of bounds
	{
		std::cout << "Which target do you wish to hit? " << std::endl;
		std::cin >> targetNumber;
	}
	playerMissle.chosenTarget = targetNumber - 1;	// sets 
	targetNumber = 0;		// resets number back to zero 
	std::cout << std::endl;
	system("Pause");
	std::cout << std::endl;
	targetNumber = 0;			//resets value

}


// function that updates the position of the missle
void update()
{
	playerMissle.intializeMisslePos();		// intialize missle position
	int hitTarget = 0;						// int for if the missle wwnt out of bounds or if it hit target
	while (!(playerMissle.hitDetected))		// program keeps updating position until collsion detected
	{
		playerMissle.update();		// updates missle position
		
		if (playerMissle.collisionDetection())
		{
			playerMissle.hitDetected = true;
			hitTarget = 1;
		}
		else if (playerMissle.coordinates.x <= 0 || playerMissle.coordinates.x >= 400						// checks if the missle coordiantes is out of bounds
			|| playerMissle.coordinates.y <= 0 || playerMissle.coordinates.y >= 400)					
		{
			playerMissle.hitDetected = true;
			hitTarget = 2;
		}
		
		else 
		{
			playerMissle.hitDetected = false;
		}
		
	}
	
	std::cout << "Missle has hit ";
	if (hitTarget == 1)
	{
		std::cout << "target" << std::endl;
	}
	else if (hitTarget == 2)
	{
		std::cout << "boundary" << std::endl;
	}
	playerMissle.hitDetected = false;		// resets value
	system("Pause");
	std::cout << std::endl;
	hitTarget = 0;		// resets value
}

// function that6 allows player to restart program i.e. fire missler again
void restart()
{
	int inputtednumber = 0;
	if (playerMissle.playerDead == false)		// only allows restart if player missle is viable or alive
	{
		while (inputtednumber != 1 && inputtednumber != 2)
		{
			std::cout << "Missle is still viable fire again?" << std::endl;
			std::cout << "1) Yes or 2) No" << std::endl;
			std::cin >> inputtednumber;
		}
	}
	if (inputtednumber == 1)
	{
		playerMissle.playerDead = false;
	}
	else
	{
		playerMissle.playerDead = true;
	}
	playerMissle.playerDead == false;		//resets value
	inputtednumber = 0;	//resets value
}

// function that allows the input of a launch code
void inputLaunchCode()
{
	int launchCode = 0;
	int inputtedCode = 0;
	int errorCounter = 0;

	
	launchCode = (rand() % 9000) + 1000;
	while (launchCode != inputtedCode )	// repeats until correct number is inputted
	{
		
		errorCounter++;
		if (errorCounter > 1)		// outputs error message to screen in incorrect number entered
		{
			std::cout << std::endl;
			std::cout << "Error , Number entered doesn't match launch code" << std::endl;
			std::cout << std::endl;
		}
		std::cout << "Current Launch Code is " << launchCode << " input code to continue " << std::endl;
		std::cin >> inputtedCode;
	}
	std::cout << "Launch Code Accepted " << std::endl;
	std::cout << std::endl;
	system("Pause");
	std::cout << std::endl;
	errorCounter = 0;		// resets value
	
}


// function that allows user to arm and fire missle
void armAndFireMissle()
{
	int inputtednumber = 0;
	int randomNumber = 0;
	while (inputtednumber != 1 && inputtednumber != 2)	// repeats if incorrect value isn't entered
	{
		std::cout << "Arm and Fire Missle?" << std::endl;
		std::cout << "1) Yes or 2) No" << std::endl;
		std::cin >> inputtednumber;
	}
	playerMissle.arm();
	std::cout << "Missle has been armed and is now firing " << std::endl;
	if (inputtednumber == 2)
	{
		std::cout << "Free Will is an illusion , this was always the outcome" << std::endl;
	}

	randomNumber = rand() % 101 + 1;			
	if (randomNumber <= 33)		// random chance missle will malfunction
	{
		playerMissle.playerDead = true;
		std::cout << "Missle Malfunction" << std::endl;
		std::cout << "Missle has exploded" << std::endl;
	}


	std::cout << std::endl;
	system("Pause");
	
	std::cout << std::endl;
	inputtednumber = 0;		// resets value
}
