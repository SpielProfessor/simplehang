// H A N G M A N -- a Hangman game written in C by MrVollbart; Copyright (c) 2023 MrVollbart. All Rights Reserved. //


// FILE TL;DR //
/* 
 * This is a Hangman program, contained in only this file
 */



// PROJECT TODO //
/*
 // PLATFORMS //
 - linux (arch) -> thus other unix-like systems (e.g. macOS)
 - win 11 -> thus win10
 expected platforms:
 - win95->win8.1
 - DOS
 - other platforms supporting C99
 // FINISHED // 
 - basic gameplay
 - win/loose
 - basic word/phrase selection
 // TODO //
 - show hangman character
 - check for security holes
 - make compatible with more systems
 - Improve overall code quality
 TODO STATE: 04.10.23
 */

// INCLUDES //
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

// CLEAR SCREEN FUNCTION - PORTABLE ACROSS WIN/POSIX //
#ifdef _WIN32
#define clear() system("cls");
#else
#define clear() system("clear");
#endif

// GLOBALS //

// DECLARATIONS //

// check if a char has already been guessed //
// if it has, return 1; if it hasn't, return 0 //
int checkIfInWord(char input, char word[]);

// loop through every char in word, if it is equal to character, replace char at current index in output //
void transformWord(char character, char word[], char output[]);

// MAIN BLOCK //

int main(){
  // seed random //
  srand(time(NULL));
  // dictionary //
  const char* dictionary[] = {
    "dog", "cat", "elephant", "banana", "apple", "car", "book", "computer", "chair", "table", "penguin", "orange", "guitar", "television", "laptop", "flower", "house", "mountain", "bicycle", "phone", "shoes", "pencil", "glass", "clock", "camera", "globe", "pizza", "moon", "star", "ocean", "key", "hat", "rainbow", "fireplace", "butterfly", "rain", "soccer", "guitar", "headphones", "wallet", "bridge", "island", "toothbrush", "brush", "spoon", "umbrella", "kite", "train", "lamp", "bracelet", "microphone", "headphones", "earrings", "cupcake", "candle", "volcano", "airplane", "cookie", "robot", "hammer", "suitcase", "drum", "couch", "garden", "violin", "magnet", "wallet", "glasses", "helicopter", "bottle", "whistle", "flag", "map", "rope", "shovel", "camera", "binoculars", "lighthouse", "tornado", "it", "python", "creeper", "is", "never gonna give you up", "its monty pythons flying circus", "spam", "spam spam spam spam baked beans spam spam and spam"
  };
  //number of words in the dictionary //
  const int numWords = sizeof(dictionary) / sizeof(dictionary[0]);
  
  // VARIABLES //
  // randomly chosen word in the dictionary //
  int dictindex = rand() % numWords;

  // word to guess //
  char *word = malloc(sizeof(dictionary[dictindex]));
  strcpy(word, dictionary[dictindex]);
  // already guessed word //
  char *guessedWord = malloc(sizeof(dictionary[dictindex]));
  int i;
  for (i=0; i<strlen(dictionary[dictindex]); i++){
    guessedWord[i] = '_'; 
  }

  char guessedLetters[90] = "";

  bool running = true;
  int lives = 12;


  clear();
	printf("Welcome to  -[H A N G M A N]-  v. 1.0\n");
	
	// MAIN LOOP //
	while (running){
		// if we didn't have the title above, we'd put the clear statement here //
    // menu //
    printf("Guess away!\n");
    printf("The Word is: %s\n",guessedWord);
		printf("Already used Characters: %s\n", guessedLetters);
		printf("Lives left: %d\n",lives);
		printf("----\n");
		
    // guessing //
		printf("Which character would you like to try next?\n> ");
		char guess=getchar();
		//scanf("\n%c", &guess);
    if (checkIfInWord(guess, guessedLetters) == 0){
      strncat(guessedLetters, &guess,1);
      if (checkIfInWord(guess, word) == 1){
        transformWord(guess, word, guessedWord);
      } else {
        lives--;
      }
    }

    clear();
    
    // dying / winning //
    if (lives==0){
      running=false;
      printf("You've Lost! The word or phrase was \"%s\"!\n",word);
    }
    if (strcmp(word, guessedWord) == 0){
      running=false;
      printf("You've won with %d lives left! The word or phrase indeed was \"%s\"!\n", lives, word);
    }    
      
	}
  
  free(word);
  free(guessedWord);
  return 0;
}

// CHECK IF A CHAR HAS ALREADY BEEN GUESSED //
// if it has, return 1; if it hasn't, return 0 //
int checkIfInWord(char input, char word[]){
	int success;
	int i;
	for (i=0; i < strlen(word); i++) {
		if (input==word[i]){
			success=1;
			break;
		}
	}
	if (success==1){
    return 1;
	} else {
    return 0;
  }
}

// loop through every char in word, if it is equal to character, replace char at current index in output //
void transformWord (char character, char word[], char output[]){
  int i;
  int success;
  for (i=0; i < strlen(word); i++){
    if (word[i] == character){
      output[i] = character;
    }
  }
  //return output;
}
