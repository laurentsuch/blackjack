#include <iostream>
#include <cstdlib>

using namespace std;

void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;


const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};


void shuffle(int cards[])
{
  // initializing deck of cards 
  for(int i = 0; i < NUM_CARDS; i++) {
    cards[i] = i;
  }
  // setting different index to cards randomly using temporary variable and for loop 
  int temp;
  for(int i = NUM_CARDS-1; i > 0; i--) {
    int j = rand() % (i+1);
    temp = cards[i];
    cards[i] = cards[j];
    cards[j] = temp;
  }
}


void printCard(int id)
{
  int cardId;
  cardId = id;

  // mathematical calculations to find index in arrays
  int cardSuit = cardId / 13;

  int cardType = cardId % 13;
  // lookup suit and type in given arrays 
  cout << type[cardType] << "-" << suit[cardSuit];
}


int cardValue(int id)
{
  // card value is calculated with math 
  int cardVal = id % 13;
  // lookup in values arrays using index number  
  return value[cardVal];
  

}


void printHand(int hand[], int numCards)
{
  for(int i = 0; i < numCards; i++) {
    // for loop prints out each card in hand array 
    printCard(hand[i]);
    cout << " ";
  }
  cout << endl;


}


int getBestScore(int hand[], int numCards)
{
  int totalScore = 0;
  for(int i = 0; i < numCards; i++) {
    // for each card in hand, add up value 
    totalScore = totalScore + cardValue(hand[i]); 
    
  }
  for(int i = 0; i < numCards; i++) {
    if(cardValue(hand[i]) == 11 && totalScore > 21) {
      totalScore = totalScore - 10;
    }
  }

  
  return totalScore;



}


int main(int argc, char* argv[])
{
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
 
  char userChoice = 'y';
  while(userChoice == 'y') {
    // while loop for if player wants to play game again
    int playerCount = 0;
    int dealerCount = 0;
    int cardCount = 0;
    shuffle(cards);
    phand[playerCount++] = cards[cardCount++];
    dhand[dealerCount++] = cards[cardCount++];
    phand[playerCount++] = cards[cardCount++];
    dhand[dealerCount++] = cards[cardCount++];
    // deal out cards, for example first card in deck goes to player, second card to dealer, etc.
    
    cout << "Dealer: ? ";
    printCard(dhand[1]);
    cout << endl;
    cout << "Player: ";
    printHand(phand, 2);
    
  
    // display cards to player and dealer
    
    while(true) {
      // will use break statements to break out of while loop 
      if(getBestScore(phand, playerCount) > 21) {
        break; // if player score busts, break loop 
      }
      else if(getBestScore(phand, playerCount) == 21) {
        while(getBestScore(dhand, dealerCount) < 17) {
          dhand[dealerCount++] = cards[cardCount++]; // logic for getting dealer best score
        }
        cout << "Dealer: ";
        printHand(dhand, dealerCount);
        break;
      }
      else {
        cout << "Type 'h' to hit and 's' to stay: " << endl;
        cin >> userChoice; 
  // logic to player whether to hit or stand 
  // always increment cards to deck number(index)
        if(userChoice == 'h') {
          phand[playerCount++] = cards[cardCount++];
          cout << "Player: ";
          printHand(phand, playerCount);
        }
        else if(userChoice == 's') {
          while(getBestScore(dhand, dealerCount) < 17) {
            dhand[dealerCount++] = cards[cardCount++];
          }
          cout << "Dealer: ";
          printHand(dhand, dealerCount);
          break;
        }
      }
    }

      if(getBestScore(phand, playerCount) > 21) {
        // if player gets a hand greater than 21, they bust 
        cout << "Player busts" << endl;
        cout << "Lose " << getBestScore(phand, playerCount) << " " << getBestScore(dhand, dealerCount) << endl;
      }

      else if(getBestScore(dhand, dealerCount) > 21) {
        // if dealer busts, player wins 
        cout << "Dealer busts" << endl;
        cout << "Win" << getBestScore(phand, playerCount) << getBestScore(dhand, dealerCount);
      }

     
        // statements comparing dealer and player score to see who wins 
      else if(getBestScore(phand,playerCount) > getBestScore(dhand, dealerCount)) {
        cout << "Win " << getBestScore(phand,playerCount) << " " << getBestScore(dhand, dealerCount) << endl;
        }
      else if(getBestScore(phand,playerCount) < getBestScore(dhand, dealerCount)) {
        cout << "Lose " << getBestScore(phand,playerCount) << " " << getBestScore(dhand, dealerCount) << endl;
        }
      else {
        cout << "Tie " << getBestScore(phand,playerCount) << " " << getBestScore(dhand, dealerCount) << endl;
        }

  
    cout << endl;
    cout << "Play again? [y/n]" << endl;
    // while loop to continue or stop game
    cin >> userChoice;
    
  }




  return 0;
}
