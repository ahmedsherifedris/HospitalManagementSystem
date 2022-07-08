#include <iostream>
#include <iomanip>
#include <cstdlib> // needed for functions srand() and rand()
#include <ctime>   // needed for function time()

using namespace std;

int rollDice(int result[], int roll = 2);

void gameCraps(int sum, int bankBalance, int bet);

enum Status {CONTINUE, WON, LOST};

int main()
{
	int sum;
	int result[2];
	int bankBalance = 1000;
	int bet;

	srand(time(0));

	sum = rollDice(result);

	cout << "Your bank balance is: " << bankBalance << "\n";
	cout << "Please enter a bet - ";

	cin >> bet;
	if (bet > 1000)
	{
		cout << "Not valid" << endl;
		cout << "Please enter a bet - " << endl;
		cin >> bet;
	}
	cout << "\n" << "Your bet: " << bet << "\n\n";
	cout << "Player rolled: " << result[0] << " + " << result[1] << endl;

	gameCraps(sum, bankBalance, bet);

	return 0;
}

int rollDice(int result[], int roll)
{
	int dicevalues = 0;

	for(int i = 0; i < roll; i++)
	{
		result[i] = 1 + rand()%6;
	}
	for(int i = 0; i < roll; i++)
	{
		dicevalues = dicevalues + result[i];
	}
	return dicevalues;
}

void gameCraps(int sum, int bankBalance, int bet)
{
	int myPoint;
	int result[2];
	char userchoice;
	Status gameStatus;

	switch(sum)
	{
		case 7:
			gameStatus = WON;
		case 11:
			gameStatus = WON;
			break;
		case 2:
			gameStatus = LOST;
		case 3:
			gameStatus = LOST;
		case 12:
			gameStatus = LOST;
			break;
		default:
			gameStatus = CONTINUE;
			myPoint = sum;
			cout << "Point is: " << myPoint << endl;
			break;
	}

	while (gameStatus == CONTINUE)
	{
		sum = rollDice(result);
		cout << "Player rolled: " << result[0] << " + " << result[1] << endl;

		if (sum == myPoint)
		{
			gameStatus = WON;
		}
		else if (sum == 7)
			{
				gameStatus = LOST;
			}

		if (gameStatus == WON)
		{
			cout << "\n\t***Player wins***\n" << endl;
			bankBalance = bankBalance + bet;
			cout << "Your bank balance is now: " << "€" << bankBalance << "\n";
			cout << "Would you like to cash-in or continue? (Select 'Y', then return to continue... "
						"or 'N' and return to cash-in!)\n";
			cin >> userchoice;

			if (userchoice == 'y')
			{
				cout << "You're up big. Now's the time to cash in your chips!\n";
				gameStatus = CONTINUE;
			}
			while (gameStatus == CONTINUE)
			{
				sum = rollDice(result);

				cout << "Your bank balance is: " << "€" << bankBalance << "\n";
				cout << "Please enter a bet - ";

				cin >> bet;

				cout << "\n" << "Your bet: " << "€" << bet << "\n\n";
				cout << "Player rolled: " << result[0] << " + " << result[1] << endl;

				gameCraps(sum, bankBalance, bet);
			}
			if (userchoice == 'n')
			{
				cout << "Ah c'mon, take a chance! You go away with a bank balance of " << "€" << bankBalance << "\n";
				exit(0);
			}
			if (userchoice !='n' || userchoice !='y')
			{
				cout << "Please enter a valid choice ('Y' or 'N')\n";
				exit(-1);
			}
		}
		else
		{
			cout << "\n\t***Player loses***\n" << endl;
			bankBalance = bankBalance - bet;
			if (bankBalance <= 0)
			{
				cout << "Sorry, you don't have enough cash to continue! Please try again.\n";
				cout << "Your bank balance is now " << "€" << bankBalance << "\n";
				exit(-1);
			}
			if (bankBalance > 0 )
			{
				cout << "Would you like to cash-in or continue? (Select 'Y', then return to continue... "
							"or 'N' and return to cash-in!)\n";
				cin >> userchoice;
				if (userchoice == 'y')
				{
					cout << "Oh, you're going for broke now?";
					gameStatus = CONTINUE;
				}
				while (gameStatus == CONTINUE)
				{
					sum = rollDice(result);

					cout << "Your bank balance is: " << "€" << bankBalance << "\n";
					cout << "Please enter a bet - ";

					cin >> bet;

					cout << "\n" << "Your bet: " << "€" << bet << "\n\n";
					cout << "Player rolled: " << result[0] << " + " << result[1] << endl;

					gameCraps(sum, bankBalance, bet);
				}
				if (userchoice == 'n')
				{
					cout << "Thanks for playing! You go away with a bank balance of " << "€" << bankBalance;
					exit(0);
				}
				if (userchoice !='y' || userchoice !='n')
				{
					cout << "Please enter a valid choice to continue\n";
					exit(-1);
				}
			}
		}
	}
}
