/*
    Author: Michael Cooper
    Date:   May 23rd, 2021  2:00pm
    Purpose:Project 2 - Yahtzee
    Version:1 - Mainly focused on using arrays to shorten the extremely long scoring system
*/

/*
Official Rules for Yahtzee can be found here:
https://www.hasbro.com/common/instruct/Yahtzee.pdf
*/

//System Libraries
#include <iostream>    //Input/Output Library
#include <iomanip>     //I/O manipulation Library
#include <ctime>       //For rand
#include <cmath>       //find max
#include <cstdlib>     
#include <string>      //Can use for tutorial and dialogue options
#include <fstream>     //For input output files


using namespace std;   //Library Name-space

//User Libraries

//Global/Universal Constants -- No Global Variables
//Science, Math, Conversions, Higher Dimensioned constants only

//Function Prototypes
//Execution Begins Here
int main(int argc, char** argv) {
    //Set the Random number seed
    srand( time(0) );
    
    //Declare variables
    int rndNum; //round number
    int roll[5];

    //The roll of dices for turn 1 of up to 3
    int  rolCts[6];
    //Roll counts: stores dice roll results, how .
    int score;              //Score for just the current round
    int scr3k;              //Score with 3 of a Kind
    //int Scores[6];        //Scores over all 6 rounds
    
    char tut,beg,st,ans;    //tutorial, begin, start, answer(to roll or stop)
    string tutor,p1,s;      //tutorial, player 1, stop
    
    bool keep[5];
    //Dice to keep for 1st,2nd, and 3rd rolls.
    bool r2ndT, r3rdT;                      //Rolled 2nd Time? Rolled 3rd time?
    //Will player roll a 2nd or 3rd time?
    bool done;                              //Done playing?

    //Initialize variables
    rndNum = 1;  //Default to Round #1
    done = false;
    //Initialize Strings (putting strings here)
    tutor = "Game Summary:\nOn each turn, roll the dice to get the highest "
    "scoring combination for one of the 13 categories.\nKeep any dice you do not not wish to reroll. You can roll up to 3 times,\n"
    "but once you fill a category with a score it cannot be replaced.\nAfter you finish rolling, "
    "your score (or zero) will be logged.\nThe game ends when all 13 boxes are filled by all players, "
    "scores are then totaled,\nincluding any bonus points and the player with the highest total wins.\n\n"
            
    "The Thirteen Categories:\n"
    "There are two sections in which to place scores:\nan upper area and a lower area.\n\n"
    "The upper section is aces-sixes (63+ scores a 35 bonus)\n"
    "For example: Total of aces(ones) only, total of twos only, and so on...\n\n"
    "The lower section consists of the following:\n"        
    "3 of a kind = total of all 5 dice\n4 of a kind = total of all 5 dice\n"
    "Full house (3 of a kind and a pair) = 25 points\nSmall straight (any sequence of 4 numbers) = 30 points\n"
    "Large straight (any sequence of 5 numbers) = 40 points\nYahtzee (five of a kind) = 50 points\n"
    "Chance: score the total of any 5 dice, this comes in handy when you\ncan't or don't want to score"
    " in another category and dont want to enter a zero.\n\n";
    
    //Intro
    cout << "Welcome to Yahtzee!\nWould you like to read the rules?"<< endl;
    cout << "Enter Y for yes or N for no" << endl;
    cin  >> tut;

    if(tut=='y'||tut=='Y')
        cout<<tutor<<endl;

    cout<<"Press any key to start the game!"<<endl;
    cin>>st;

    //Check if game file exists. If so, open it.
    ifstream In( "yahtzee.txt" );
    if( In ) {  //If there is a file & it can be opened, read it.
        In >> rndNum >> p1;
        In >> score;
        //For saving multiple round scores
        // for( int i = 0; i < RoundNum; i++ )
        //   In >> Scores[i];
        // RoundNum++;
    }

    if( ! In || rndNum > 6 ) {
      do{
        cout << "Enter player 1 name"<<endl;
        cin  >> p1;
        cout << endl;
        cout << "Player 1 is "<<p1<<", ready to begin? (y/n)";
        cin  >> beg;
      } while (!(beg=='y'||beg=='Y')); //validate player names
    }

    if( In ) In.close();
    
    do {  //For multiple rounds, start over here.

        //Turn begins //First roll
        cout << "roll 1:\n(Dice are labeled a-e)\n";
        for( int i = 0; i < 5; i++ )
          roll[i] = rand() % 6 + 1;

        //Show dice
        for( int i = 0; i < 5; i++ ) 
          cout << 'a' + i << ") Roll: " << roll[i] << endl;
        cout << endl;    
        r2ndT = r3rdT = false; 
        //setting to false so user can decide if they want to set to true.
        //after first roll dialogue

        cout << "Do you want to (S)top, or choose dice to hold and (R)oll again? [S or R]:";
        cin >> ans;
        ans = toupper( ans ); //will make sure entry is uppercase

        if( ans == 'R' ) {  //User wants to reroll
            r2ndT = true;

            cin.clear();
            cin.ignore();
            cout << "\nType letters of dice (a - e) you would like to keep:"<<endl;
            cout << "(please type a space between letters)"<<endl;
            std::getline( cin, s );  //Get whatever user types ('a' - 'e)

            //Go through string character by character
            for( int i = 0; i < 5; i++ )
                keep[i] = false;

            for( int i = 0; i < s.length(); i++ ) {      
              char choice = s[i];  //String property -- treating as array
              choice = tolower( choice );  //Make sure it's lowercase
              //If a, b, c, d, or e was typed, treat as a choice
              if( choice >= 'a' && choice <= 'e' )
                keep[ choice - 'a' ] = true;

              //Should validate choice is 'a' through 'e'.
            }

            //Second roll
            cout << "roll 2:\n";

            for( int i = 0; i < 5; i++ ) {
              cout << (char)(i + 'a') << ") ";
              string msg = keep[i] ? "KEPT: ":"Roll: ";
              if( keep[i] )  cout << msg << roll[i] << endl;
              else {
                roll[i] = rand() % 6 + 1;
                 cout << msg << roll[i] << endl;
              }
            }

            cout << "Do you want to (S)top, or choose dice to hold and (R)oll again? [S or R]:\n";
            cin >> ans;
            ans = toupper( ans ); //will make sure entry is uppercase

            if( ans == 'R' ) {  //User wants to reroll
                r3rdT = true;   //this was rolled 2nd time. was it a mistake to change this to 3rd?
                //GetKeepersFromUser( Keepers1 );

                cin.clear();
                cin.ignore();
                cout << "Type letters of dice (a - e) you would like to keep:"<<endl;
                cout << "(You must reselect any dice you wish to keep)"<<endl;
                std::getline( cin, s );  //Get whatever user types ('a' - 'e' hopefully)

                //Go through string character by character
                for( int i = 0; i < 5; i++ )
                  keep[i] = false;
                for( int i = 0; i < s.length(); i++ ) {      
                  char choice = s[i];  //This is a property strings have -- treat as array
                  choice = tolower( choice );  //Make sure it's lowercase

                  //If a, b, c, d, or e was typed, treat as a choice
                  if( choice >= 'a' && choice <= 'e' )
                    keep[ choice - 'a' ] = true;

                  //Should validate choice is 'a' through 'e'.
                }

                //Third roll
                cout << "roll 3:\n";
                for( int i = 0; i < 5; i++ ) {
                  cout << (char)(i + 'a') << ") ";
                  string msg = keep[i] ? "KEPT: ":"Roll: ";
                  if( keep[i] )  cout << msg << roll[i] << endl;
                  else {
                    roll[i] = rand() % 6 + 1;
                    cout << msg << roll[i] << endl;
                  }
                }

            } //End of if for 3rd roll
        } //end of if for 2nd roll

        //Scoring sequence beings
        //Score UPPER section.
        //Clear out count 
        for( int i = 0; i < 6; i++ )
          rolCts[i] = 0;

        //Look at each die in a roll.
        //Add the number to the appropriate entry in Counts
        for( int r = 0; r < 5; r++ ) {  //Loop through rolls
            int index = roll[i] - 1;
            rolCts[ index ]++;
        }

        score = 0;

        bool got_yahtzee = false;
        for( int i = 0; i < 6; i++ ) {
            if( rolCts[i] == 5 ) {
              cout << "Yahtzee!" << endl;
              score += 50;
              got_yahtzee = true;
            }
        }

        if( ! got_yahtzee ) {
          for( int i = 0; i < 6; i++ ) {
            if( rolCts[i] == 3 ) {
              int scr3k = 0;
              for( int j = 0; j < 6; j++ )
                  scr3k += rolCts[i] * (j+1);
              if( scr3k > 25 )
                  score += scr3k;
              else {
                  bool full_house = false;
                  for( int j = 0; j < 6; j++ ) {
                    if( i != j ) {                      
                      if( rolCts[j] == 2 ) {
                        cout << "Full House with three " << (i+1)
                             << "'s and two " << (j+1) << "'s" << endl;
                        score += 25;
                        full_house = true;
                        break;
                      }
                    }
                  }
                    
                  if( ! full_house ) {
                    cout << "Three of a kind with " << (i+1) << endl;
                    //Total of all 5 dice
                    score += scr3k;
                  }
              }
          }

          for( int i = 0; i < 6; i++ ) {
            if( rolCts[i] == 4 ) {
              cout << "Four of a kind with " << (i+1) << endl;
                //Total of all 5 dice
              score += rolCts1 * 1 +
                       rolCts2 * 2 +
                       rolCts3 * 3 +
                       rolCts4 * 4 +
                       rolCts5 * 5 +
                       rolCts6 * 6;
            }
          }

          //Check for straights
          if( (rolCts1 == 0 && rolCts2 == 1 && rolCts3 == 1 &&
               rolCts4 == 1 && rolCts5 == 1 && rolCts6 == 1) ||
              (rolCts1 == 1 && rolCts2 == 1 && rolCts3 == 1 &&
               rolCts4 == 1 && rolCts5 == 1 && rolCts6 == 0) ) {
            cout << "Large straight" << endl;
            score += 40;
          }
          else {
            if( (rolCts1 == 1 && rolCts2 == 1 && rolCts3 == 1 &&
                 rolCts4 == 1) ||                                                 //1,2,3,4
                (rolCts2 == 1 && rolCts3 == 1 && rolCts4 == 1 &&
                 rolCts5 == 1) ||                                                 //2,3,4,5
                (rolCts3 == 1 && rolCts4 == 1 && rolCts5 == 1 &&
                 rolCts6 == 1) ) {                                                //3,4,5,6
              cout << "Small straight" << endl;
              score += 30;
            }
          }      
        }  //end of else

        if( score == 0 ) {  //Chance
            score = rolCts1 * 1 +
                    rolCts2 * 2 +
                    rolCts3 * 3 +
                    rolCts4 * 4 +
                    rolCts5 * 5 +
                    rolCts6 * 6;   
        }

        //Scores[RoundNum-1] = score;
        cout << "Congratulations " << p1 << "!\nYour Score: " << score << endl;


        //Ask if player wants to continue
        if( rndNum < 6 ) {
          cout << "Do you want to play another round? (Y or N): " << endl;

          //Remember to validate user choice.
          char choice;
          cin >> choice;
          choice = toupper( choice );
          if( choice == 'N' ) {
              //Save game.
              cout << "Saving game for next time!" << endl;
              ofstream Out( "yahtzee.txt" );
              Out << rndNum << " " << p1 << " ";
              Out << score;
              //For multiple round scores:
              //for( int i = 0; i < RoundNum; i++ )
              //  Out << Scores[i] << " ";
              Out.close();

              done = true;
          }
        }
        else {
          //STUB: End of game. Total scores, etc.
            cout<<"ending dialogue";
          //Indicate in the file that the last game was completed.
          ofstream Out( "yahtzee.txt" );
          Out << 7 << " " << p1 << " " << score;
          Out.close(); 

          done = true;
        }

        rndNum++;
    
    } while( ! done );  //For multiple round game
    
    //printf ("fmax (100.0, 1.0) = %f\n", fmax(100.0,1.0));
    //cout << setprecision(2)<<fixed<<shopwpoint<<static_cast<float>;
    //to show use of iomanip and cmath. Can create and average or high low stats output.
    //could also offer additional bonus points or recognition.
  
    //Exit stage right
    return 0;
}