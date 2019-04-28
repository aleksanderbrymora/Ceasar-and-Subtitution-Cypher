#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * ----OVERVIEW----
 * Program is divided in 5 sections:
 *      Rotation encryption
 *      Rotation decryption
 *      Substitution encryption
 *      Substitution decryption
 *      Rotation decryption
 *
 * You choose which option you want to use with numbers
 *
 * Program is used to either encrypt or decrypt given message
 * using different data needed from the user which he either
 * inputs into txt files (which he is instructed to) or terminal.
 *
 * User message to either encrypt or decrypt is restricted to 1024 characters
 * however its easy to change as it is set in a variable called arraySize.
 */

//----Function prototypes---------------------------

//Function used to encrypt given message using rotation encryption
void rotationEncryption();

//Function used to decrypt given message using rotation decryption
void rotationDecryption();

//Function used to encrypt given message using substitution encryption
void substitutionEncryption();

//Function used to decrypt given message using substitution decryption
void substitutionDecryption();

//Function used to decrypt rotation cypher by bruteforce
void bruteRotationDecryption();

//Function used to exit main menu
int exitLoop();


//----Global Variables------------------------------
int userChoice = 0; //used to store user choices
int i = 0;  //used for loops and counting

/*
 * main function only holds the menu to open other functions
 *
 * It requires:
 *      User input into the terminal
 */

int main() {
    printf("------------------------------------------------\n");
    printf("This program accepts inputs only from txt\n");
    printf("files located in the same folder as this program\n");
    printf("------------------------------------------------\n\n");

    //Main menu
    do {
        printf("What would you like to do?\n");
        printf("(1) Rotation Encryption\n");
        printf("(2) Rotation Decryption\n");
        printf("(3) Substitution Encryption\n");
        printf("(4) Substitution Decryption\n");
        printf("(5) Rotation Decryption\n");
        printf("Input number: ");
        scanf("%d", &userChoice);
        while (userChoice < 1 && userChoice > 5) {
            printf("That is an invalid input\n");
            printf("Input must be between 1 and 4: ");
            scanf("%d", &userChoice);
        }
        switch(userChoice) {
            case 1 :
                printf("-------------------------------------\n");
                printf("----You chose Rotation Encryption----\n");
                printf("-------------------------------------\n");
                rotationEncryption();
                userChoice = exitLoop();
                break;
            case 2 :
                printf("-------------------------------------\n");
                printf("----You chose Rotation Decryption----\n");
                printf("-------------------------------------\n");
                rotationDecryption();
                userChoice = exitLoop();
                break;
            case 3 :
                printf("-----------------------------------------\n");
                printf("----You chose Substitution Encryption----\n");
                printf("-----------------------------------------\n");
                substitutionEncryption();
                userChoice = exitLoop();
                break;
            case 4 :
                printf("-----------------------------------------\n");
                printf("----You chose Substitution Decryption----\n");
                printf("-----------------------------------------\n");
                substitutionDecryption();
                userChoice = exitLoop();
                break;
            case 5 :
                printf("-------------------------------------\n");
                printf("----You chose Rotation Decryption----\n");
                printf("-------------------------------------\n");
                bruteRotationDecryption();
                userChoice = exitLoop();
                break;
            case 9 :
                break;
            default :
                printf("Invalid input\n" );
        }
    } while (userChoice != 9);
    printf("Thanks for using the program!\n" );
    printf("---------------------------\n");
}

/*
 * rotationEncryption function is used to encrypt a message by shifting
 * characters by given key
 *
 * It requires:
 *     User inputting key into the terminal
 *     User inputting message into input.txt
 */

void rotationEncryption() {
    //----Setting up file IO------------------------
    FILE *input;
    FILE *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    //----Setting up variables----------------------
    int arraySize = 1024; //Size of array
    char charArray[arraySize]; //array used to hold a message
    i = 0; //counter
    int key = 0; //Key used for rotation Cypher
    int length = 0; //Used to store array size

    //Zeroing the array
    for (i = 0; i <= arraySize; i++) {
        charArray[i] = 0;
    }

    //----Asking for the key------------------------
    printf("Input the key: ");
    scanf("%d", &key);
    printf("Got the key and it is: %d.\n", key);

    //----Making sure Key is between 0 and 25k------
    if (key < 0) {
        //I'm increasing the key by 26 as many times
        //as it takes to get between 0 and 25
        for (; key < 0; key += 26) {}
    }
    else if (key > 25) {
        //Same here - decreasing it to get between 0 and 25
        for (; key > 25; key -= 26) {}
    }

    printf("Input message to encrypt to input.txt\n");
    printf("When you ready press any character and press enter: ");
    char anyKey;
    //i seriously have no idea why i have to put 2 of these here
    //but that is the only way it works the way i want it to...
    scanf("%c", &anyKey);
    scanf("%c", &anyKey);

    //----Checking if input file exists-------------
    if (input == NULL) {
        printf("Error Reading File\n");
        exit(0);
    }

    //----From file to array------------------------
    /*
    * Im inputting character by character symbols
    * from input.txt file into an array of chars
    * charArray
    */
    for (i = 0; i < arraySize; i++) {
        fscanf(input, "%1c", &charArray[i]);
    }

    //----Making every character upper case---------
    for (i = 0; i < arraySize; i++) {
        charArray[i] = toupper(charArray[i]);
    }

    //----Counting characters in a string-----------
    for (length = 0; charArray[length] != '\0'; length++) {}

    //----Cypher algorithm--------------------------
    for (i = 0; i <= length; i++){
        //Ignoring all different signs and printing them as they are
        if (charArray[i] >= 32 && charArray[i] <= 64) {}

        //Some other characters to ignore
        else if (charArray[i] >= 91 && charArray[i] <= 96) {}

        //Some other characters to ignore
        else if (charArray[i] >= 123 && charArray[i] <= 127) {}

        else if (charArray[i] + key > 90) {
            charArray[i] = (charArray[i] + key) - 26;
        }
        else if (charArray[i] + key < 65) {
            charArray[i] = (charArray[i] + key) + 26;
        }
        else {
            charArray[i] = charArray[i] + key;
        }
    }

    //----Outputting encoded message to file--------
    fprintf(output, "Encrypted message: \n");
    printf("Encrypted message: \n"); //and to the terminal
    for (i = 0; i < length; i++){
        if (charArray[i] >= 32 && charArray[i] <= 127) {
            fprintf(output, "%c", charArray[i]);
            printf("%c", charArray[i]);
        }
    }

    //----Closing both files------------------------
    fclose(input);
    fclose(output);

    printf("\nCheck output.txt for encrypted message\n");
    printf("--------------------------------------\n");
}

/*
 * rotationDecryption function is used to decrypt a message by shifting
 * characters by a given key
 * It requires:
 *     User inputting the key into the terminal
 *     User inputting message into input.txt
 */

void rotationDecryption() {
    //----Setting up file IO------------------------
    FILE *input;
    FILE *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    //----Setting up variables----------------------
    int arraySize = 1024; //Size of array
    char charArray[arraySize]; //array used to hold a message
    i = 0; //counter
    int key = 0; //Key used for rotation Cypher
    int length = 0; //Used to store array size

    //Zeroing the array
    for (i = 0; i <= arraySize; i++) {
        charArray[i] = 0;
    }

    //----Asking for the key------------------------
    printf("Input the key: ");
    scanf("%d", &key);
    printf("Got the key and it is: %d.\n", key);

    //----Making sure Key is between 0 and 25k------
    if (key < 0) {
        //I'm increasing the key by 26 as many times
        //as it takes to get between 0 and 25
        for (; key < 0; key += 26) {}
    }
    else if (key > 25) {
        //Same here - decreasing it to get between 0 and 25
        for (; key > 25; key -= 26) {}
    }

    //----Inverting the key-------------------------
    /*
     * I am changing the key as the decryption is
     * just inverted encryption
     */
    key = key * (-1);

    printf("Input message to decrypt to input.txt\n");
    printf("When you ready press any character and press enter: ");
    char anyKey;
    //i seriously have no idea why i have to put 2 of these here
    //but that is the only way it works the way i want it to...
    scanf("%c", &anyKey);
    scanf("%c", &anyKey);

    //----Checking if input file exists-------------
    if (input == NULL) {
        printf("Error Reading File\n");
        exit(0);
    }

    //----From file to array------------------------
    /*
    * Im inputting character by character symbols
    * from input.txt file into an array of chars
    * charArray
    */
    for (i = 0; i < arraySize; i++) {
        fscanf(input, "%1c", &charArray[i]);
    }

    //----Making every character upper case---------
    for (i = 0; i < arraySize; i++) {
        charArray[i] = toupper(charArray[i]);
    }

    //----Counting characters in a string-----------
    for (length = 0; charArray[length] != '\0'; length++) {}

    //----Cypher algorithm--------------------------
    for (i = 0; i <= length; i++){
        //Ignoring all different signs and printing them as they are
        if (charArray[i] >= 32 && charArray[i] <= 64) {}

            //Some other characters to ignore
        else if (charArray[i] >= 91 && charArray[i] <= 96) {}

            //Some other characters to ignore
        else if (charArray[i] >= 123 && charArray[i] <= 127) {}

        else if (charArray[i] + key > 90) {
            charArray[i] = (charArray[i] + key) - 26;
        }
        else if (charArray[i] + key < 65) {
            charArray[i] = (charArray[i] + key) + 26;
        }
        else {
            charArray[i] = charArray[i] + key;
        }
    }

    //----Outputting encoded message to file--------
    fprintf(output, "Decrypted message: \n");
    printf("Decrypted message: \n");
    for (i = 0; i < length; i++){
        if (charArray[i] >= 32 && charArray[i] <= 127) {
            fprintf(output, "%c", charArray[i]);
            printf("%c", charArray[i]);
        }
    }

    //----Closing both files------------------------
    fclose(input);
    fclose(output);

    printf("\nCheck output.txt for encrypted message\n");
    printf("--------------------------------------\n\n");
}

/*
 * substitutionEncryption function is used to encrypt user's message
 * with provided string of shuffled characters from the alphabet which
 * do not repeat. Then it replaces first character in alphabet with a
 * first character in the substitution string
 *
 * it requires:
 *      user input into a input.txt file of a message to encrypt
 *      user input into a subString.txt of a substitution string
 */

void substitutionEncryption() {
    //----Setting up file IO------------------------
    FILE *input;
    FILE *output;
    FILE *substitutionString;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    substitutionString = fopen("subString.txt", "r");

    //----Setting up variables----------------------
    int arraySize = 1024; //Size of array
    char charArray[arraySize]; //array used to hold a message
    char subString[arraySize]; //array used to hold substitution string
    i = 0; //counter
    int length = 0; //Used to store array size
    int reInput = 0; //Used to tell if subString is wrong

    do {
        //Zeroing the array
        for (i = 0; i <= arraySize; i++) {
            subString[i] = 0;
        }

        //----Asking for substitution string -----------
        //user is to fill substitutionString.txt
        printf("Input substitution string into substitutionString.txt\n");
        printf("It must consist of all letters of alphabet, which don't repeat\n");
        printf("When you ready press any character and press enter: ");
        char anyKey;
        //i seriously have no idea why i have to put 2 of these here
        //but that is the only way it works the way i want it to...
        scanf("%c", &anyKey);
        scanf("%c", &anyKey);

        //----Checking if subString file exists---------
        if (substitutionString == NULL) {
            printf("Error Reading subString.txt File\n");
            exit(0);
        }

        //----Getting subString from file to array------
        for (i = 0; i < arraySize; i++) {
            fscanf(substitutionString, "%1c", &subString[i]);
        }

        //----Making every char go upper case-----------
        for (i = 0; i < arraySize; i++) {
            subString[i] = toupper(subString[i]);
        }

        //----Counting characters in subString----------
        //Making sure string is 26 characters (amount of alphabet letters)
        for (i = 0; subString[i] != '\0'; i++) {}
        while (i != 26) {
            printf("You have inputted wrong string\n");
            printf("The substitution string must be 26 characters long\n");
            printf("Please input again\n");
            printf("To substitute: ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
            printf("When you ready press any character and press enter: ");
            scanf("%c", &anyKey);
            scanf("%c", &anyKey);

            //Reopening the subString.txt
            fclose(substitutionString);
            FILE *substitutionString;
            substitutionString = fopen("subString.txt", "r");

            //Zeroing the array
            for (i = 0; i <= arraySize; i++) {
                subString[i] = 0;
            }

            //Getting subString from file to array
            for (i = 0; i < arraySize; i++) {
                fscanf(substitutionString, "%1c", &subString[i]);
            }

            //Making every char go upper case
            for (i = 0; i < arraySize; i++) {
                subString[i] = toupper(subString[i]);
            }

            //Counting characters again
            for (i = 0; subString[i] != '\0'; i++) {}
        }

        //Making sure all characters are different
        //Letters up to this point MUST BE upper case
        int differ[30]; //array to store how many occurrences are of each letter
        for (i = 0; i < 30; i++) {
            differ[i] = 0;
        }
        int letterCounter = 0; //variable used to count how many letters of one kind are in subString
        int iteration = 0; //measures on which letter we are right now
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            for (i = 0; i < 26; i++) {
                if (subString[i] == letter) {
                    letterCounter++;
                }
            }
            differ[iteration] = letterCounter;
            iteration++;
            letterCounter = 0;
        }
        reInput = 0;
        for (i = 0; i < 26; i++) {
            if (differ[i] == 0) {
                printf("Missing letter in a string: %c\n", 'A' + i);
                reInput++;
            } else if (differ[i] >= 2) {
                printf("Too many (%d) of one letter in a string: %c\n", differ[i], 'A' + i);
                reInput++;
            }
        }
    } while (i != 26 || reInput > 0);

    //----Printing subString----------------------------
    printf("Substitution string is: \n");
    for (i = 0; i < 26; i++) {
        printf("%c", subString[i]);
    }
    printf("\n--------------------------\n");

    //----Checking if input file exists-------------
    if (input == NULL) {
        printf("Error Reading input.txt File\n");
        exit(0);
    }

    //Zeroing the array
    for (i = 0; i <= arraySize; i++) {
        charArray[i] = 0;
    }

    //----Asking user to input message to encrypt---
    //user is to fill input.txt
    printf("Input message into input.txt\n");
    printf("Only letters will be encrypted\n");
    printf("Letters will be converted to upper case\n");
    printf("When you ready press any character and press enter: ");
    char anyKey;
    //i seriously have no idea why i have to put 2 of these here
    //but that is the only way it works the way i want it to...
    scanf("%c", &anyKey);
    scanf("%c", &anyKey);

    //----Getting message from file to array--------
    for (i = 0; i <= arraySize; i++) {
        fscanf(input, "%1c", &charArray[i]);
    }

    //----Making every character upper case---------
    for (i = 0; i < arraySize; i++) {
        charArray[i] = toupper(charArray[i]);
    }

    printf("Got the message and it is: \n");
    for (i = 0; i <= arraySize; i++) {
        if (charArray[i] > 0 && charArray[i] < 127){
            printf("%c", charArray[i]);
        }
    }
    printf("\n--------------------------\n");

    //----ENCRYPTION--------------------------------
    /*
     * 1. Check if a sign is a letter if not ignore it
     * 2. Convert a letter to a number from 0 to 25
     * 3. Use the same number to access the array used to store subString
     * 4. Replace it the letters
     * 5. Ignore all other signs
     */
    for (i = 0; i <= arraySize; i++) {
        if (charArray[i] > 0 && charArray[i] < 127) {
            if (charArray[i] >= 65 && charArray[i] <= 90) {
                fprintf(output, "%c", subString[charArray[i] - 65]);
                printf("%c", subString[charArray[i] - 65]);
            }
            else {
                fprintf(output, "%c", charArray[i]);
                printf("%c", charArray[i]);
            }
        }
    }

    printf("Check out output.txt for the encrypted message\n");

    //----Closing all the files---------------------
    fclose(input);
    fclose(output);
    fclose(substitutionString);
}

/*
 * substitutionDecryption function is used to decrypt user's message
 * with provided string of shuffled characters from the alphabet which
 * do not repeat. Then it replaces first character in alphabet with a
 * first character in the substitution string
 *
 * it requires:
 *      user input into a input.txt file of a message to decrypt
 *      user input into a subString.txt of a substitution string
 */

void substitutionDecryption() {
    /*
     * It is basically the same as encryption
     * the differences are in printf statements
     */

    //----Setting up file IO------------------------
    FILE *input;
    FILE *output;
    FILE *substitutionString;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    substitutionString = fopen("subString.txt", "r");

    //----Setting up variables----------------------
    int arraySize = 1024; //Size of array
    char charArray[arraySize]; //array used to hold a message
    char subString[arraySize]; //array used to hold substitution string
    i = 0; //counter
    int length = 0; //Used to store array size
    int reInput = 0; //Used to tell if subString is wrong

    do {
        //Zeroing the array
        for (i = 0; i <= arraySize; i++) {
            subString[i] = 0;
        }

        //----Asking for substitution string -----------
        //user is to fill substitutionString.txt
        printf("Input substitution string into substitutionString.txt\n");
        printf("It must consist of all letters of alphabet, which don't repeat\n");
        printf("When you ready press any character and press enter: ");
        char anyKey;
        //i seriously have no idea why i have to put 2 of these here
        //but that is the only way it works the way i want it to...
        scanf("%c", &anyKey);
        scanf("%c", &anyKey);

        //----Checking if subString file exists---------
        if (substitutionString == NULL) {
            printf("Error Reading subString.txt File\n");
            exit(0);
        }

        //----Getting subString from file to array------
        for (i = 0; i < arraySize; i++) {
            fscanf(substitutionString, "%1c", &subString[i]);
        }

        //----Making every char go upper case-----------
        for (i = 0; i < arraySize; i++) {
            subString[i] = toupper(subString[i]);
        }

        //----Counting characters in subString----------
        //Making sure string is 26 characters (amount of alphabet letters)
        for (i = 0; subString[i] != '\0'; i++) {}
        while (i != 26) {
            printf("You have inputted wrong string\n");
            printf("The substitution string must be 26 characters long\n");
            printf("Please input again\n");
            printf("To substitute: ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
            printf("When you ready press any character and press enter: ");
            scanf("%c", &anyKey);
            scanf("%c", &anyKey);

            //Reopening the subString.txt
            fclose(substitutionString);
            FILE *substitutionString;
            substitutionString = fopen("subString.txt", "r");

            //Zeroing the array
            for (i = 0; i <= arraySize; i++) {
                subString[i] = 0;
            }

            //Getting subString from file to array
            for (i = 0; i < arraySize; i++) {
                fscanf(substitutionString, "%1c", &subString[i]);
            }

            //Making every char go upper case
            for (i = 0; i < arraySize; i++) {
                subString[i] = toupper(subString[i]);
            }

            //Counting characters again
            for (i = 0; subString[i] != '\0'; i++) {}
        }

        //Making sure all characters are different
        //Letters up to this point MUST BE upper case
        int differ[30]; //array to store how many occurrences are of each letter
        for (i = 0; i < 30; i++) {
            differ[i] = 0;
        }
        int letterCounter = 0; //variable used to count how many letters of one kind are in subString
        int iteration = 0; //measures on which letter we are right now
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            for (i = 0; i < 26; i++) {
                if (subString[i] == letter) {
                    letterCounter++;
                }
            }
            differ[iteration] = letterCounter;
            iteration++;
            letterCounter = 0;
        }
        reInput = 0;
        for (i = 0; i < 26; i++) {
            if (differ[i] == 0) {
                printf("Missing letter in a string: %c\n", 'A' + i);
                reInput++;
            } else if (differ[i] >= 2) {
                printf("Too many (%d) of one letter in a string: %c\n", differ[i], 'A' + i);
                reInput++;
            }
        }
    } while (i != 26 || reInput > 0);

    //----Printing subString----------------------------
    printf("Substitution string is: \n");
    for (i = 0; i < 26; i++) {
        printf("%c", subString[i]);
    }
    printf("\n--------------------------\n");

    //----Checking if input file exists-------------
    if (input == NULL) {
        printf("Error Reading input.txt File\n");
        exit(0);
    }

    //Zeroing the array
    for (i = 0; i <= arraySize; i++) {
        charArray[i] = 0;
    }

    //----Asking user to input message to encrypt---
    //user is to fill input.txt
    printf("Input message into input.txt\n");
    printf("Only letters will be decrypted\n");
    printf("Letters will be converted to upper case\n");
    printf("When you ready press any character and press enter: ");
    char anyKey;
    //i seriously have no idea why i have to put 2 of these here
    //but that is the only way it works the way i want it to...
    scanf("%c", &anyKey);
    scanf("%c", &anyKey);

    //----Getting message from file to array--------
    for (i = 0; i <= arraySize; i++) {
        fscanf(input, "%1c", &charArray[i]);
    }

    //----Making every character upper case---------
    for (i = 0; i < arraySize; i++) {
        charArray[i] = toupper(charArray[i]);
    }

    printf("Got the message and it is: \n");
    for (i = 0; i <= arraySize; i++) {
        if (charArray[i] > 0 && charArray[i] < 127){
            printf("%c", charArray[i]);
        }
    }
    printf("\n--------------------------\n");

    //----ENCRYPTION--------------------------------
    /*
     * 1. Check if a sign is a letter if not ignore it
     * 2. Convert a letter to a number from 0 to 25
     * 3. Use the same number to access the array used to store subString
     * 4. Replace it the letters
     * 5. Ignore all other signs
     */
    for (i = 0; i <= arraySize; i++) {
        if (charArray[i] > 0 && charArray[i] < 127) {
            if (charArray[i] >= 65 && charArray[i] <= 90) {
                fprintf(output, "%c", subString[charArray[i] - 65]);
                printf("%c", subString[charArray[i] - 65]);
            }
            else {
                fprintf(output, "%c", charArray[i]);
                printf("%c", charArray[i]);
            }
        }
    }

    printf("Check out output.txt for the decrypted message\n");

    //----Closing all the files---------------------
    fclose(input);
    fclose(output);
    fclose(substitutionString);
}

/*
 * bruteRotationDecryption function is used to decrypt a message encrypted
 * with a rotation encryption.
 * first it tries all the possibilities of a decrypted message
 * then it compares all the options with a dictionary file and gives each
 * try a score based on matching consecutive characters (2 or more)
 * Then it outputs the most probable message (the one with the highest score)
 */

void bruteRotationDecryption() {
    //----Setting up file IO------------------------
    FILE *input;
    FILE *output;
    FILE *dictionary;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    dictionary = fopen("20k.txt", "r");


    //----Setting up variables----------------------
    int arraySize = 1024; //Size of array
    int big_arraySize = 200000;
    char charArray[arraySize]; //array used to hold a message
    char bruteArray[arraySize]; //array used to store brute decryption
    char dict[big_arraySize]; //array used to store top100 words
    int dictWord[arraySize]; //array to store lengths of words in an dictionary file
    int messageWord[arraySize]; //array to store lengths of words in a message file
    int messageScore[30]; //array used to store score that the message gets
    char finalDecryption[arraySize]; //array used to hold the most probable message
    int length = 0;
    int score = 0;
    int previousScore = 0;
    int bestKey = 0;
    i = 0; //counter

    //Zeroing all the arrays
    for (i = 0; i <= arraySize; i++) {
        charArray[i] = 0;
        bruteArray[i] = 0;
        dictWord[i] = 0;
    }

    for (i = 0; i <= big_arraySize; i++) {
        dict[i] = 0;
    }

    printf("Input message to decrypt into input.txt\n");
    printf("This process may take few seconds...\n");
    printf("When you ready press any character and press enter: ");
    char anyKey;
    //i seriously have no idea why i have to put 2 of these here
    //but that is the only way it works the way i want it to...
    scanf("%c", &anyKey);
    scanf("%c", &anyKey);

    //----Checking if dictionary file exists--------
    if (dictionary == NULL) {
        printf("Error Reading Dictionary File\n");
        exit(0);
    }

    //----Checking if input file exists-------------
    if (input == NULL) {
        printf("Error Reading Input File\n");
        exit(0);
    }


    //----Attempting to put dictionary into array---
    /*
     * THIS IS THE HARD WAY USING 20K DICTIONARY
     * The idea is to scan the dictionary file first for 2-letter words
     * then put them in an array next to each other
     * they wont need to be separated as they all are 2-letter words
     * then increase to the 3-letter words and put them into a separate array
     */

    /*
     * THIS IS THE EASY WAY USING TOP 100 WORDS
     * scan the top 100 file and put words into
     * an array separated by some unique character
     * algorithm will then:
     *      count the letters of a first word in a brute forced sentence
     *      then start with a first word in the top 100 and count its letters
     *          up to the unique character
     *      if they match the algorithm will compare each letter with each other
     *      if they match it will add up to the score of a sentence and end the search
     *      if they dont it will skip to the next word
     */

    //----DICTIONARY STUFF--------------------------

    //----From File to Array------------------------
    /*
     * I am inputting each word from 100.txt file into an array
     * separating them with a space
     */

    // inputting every character from file into an array
    for (i = 0; i < big_arraySize; i++) {
        fscanf(dictionary, "%1c", &dict[i]);
    }

    //----Making every character upper case---------
    for (i = 0; i < big_arraySize; i++) {
        dict[i] = toupper(dict[i]);
    }

    /*
    //Counting the lengths of a word in a top100 dictionary
    int wordPlace = 0;
    length = 0;
    for (i = 0; i < arraySize; i++) {
        if (dict[i] >= 65 && dict[i] <= 95) {
            length++;
        }
        else if (dict[i] == 32) {
            //Putting lengths into an array to access later
            messageWord[wordPlace] = length;
            wordPlace++;
            length = 0;
        }
    }
     */

    //----From file to array------------------------
    /*
    * Im inputting character by character symbols
    * from input.txt file into an array of chars
    * charArray
    */
    for (i = 0; i < arraySize; i++) {
        fscanf(input, "%1c", &charArray[i]);
    }

    //----Making every character upper case---------
    for (i = 0; i < arraySize; i++) {
        charArray[i] = toupper(charArray[i]);
    }

    //----Counting characters in a string-----------
    for (length = 0; charArray[length] != '\0'; length++) {}


    //----Counting word lengths in a message--------
    /*
     * out of this function we are getting an array
     * of lengths of words
     * If we get a 0 it means there are more than one
     * signs different than capital letters, example: ". "
     */
    /*
    wordPlace = 0;
    length = 0;
    for (i = 0; i < arraySize; i++) {
        if (charArray[i] >= 0 && charArray[i] <= 127) {
            if (charArray[i] >= 65 && charArray[i] <= 90) {
                length++;
            }
            else {
                messageWord[wordPlace] = length;
                wordPlace++;
                length = 0;
            }
        }
    }
     */

    //----Bruteforce decryption---------------------
    /*
     * 1. Set key to 1 and increase it every loop by 1
     * 2. Decrypt only capital letters (if statement)
     * 3. print different options to output in that format:
     * -----------------------------------
     * Key: x
     * Decrypted message:
     * xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
     * Dictionary matches: xx
     * 4. Compare all outputs with some dictionary and maybe add
     *    how many words match with a dictionary
     * 5. Zero the array holding the brute forced decryption
     */

    //----Counting characters in a string-----------
    for (length = 0; charArray[length] != '\0'; length++) {}

    //loop to try all characters (hence the 26)
    for (i = 1; i < 26; i++) {
        //fprintf(output, "----------------------------\n");
        //fprintf(output, "Key: %d\n", i);
        //fprintf(output, "Brutforce-decrypted message:\n");

        for (int counter = 0; counter <= length; counter++) {
            //ignoring all other garbage that may be there
            if (charArray[counter] >= 0 && charArray[counter] <= 127) {

                //Increasing array (that stores an encrypted message)
                //by 1 every loop
                bruteArray[counter] = charArray[counter] + i;

                //Decrypting only capital letters
                if (charArray[counter] >= 65 && charArray[counter] <= 90) {

                    //Letters may go over 90 so we decrease
                    //them by 26 to again become letters
                    if (bruteArray[counter] > 90) {
                        bruteArray[counter] = bruteArray[counter] - 26;
                        //fprintf(output, "%c", bruteArray[counter]);
                    } else {
                        //fprintf(output, "%c", bruteArray[counter]);
                    }
                }
                else {
                    bruteArray[counter] = charArray[counter];
                }
            }
        }

        //----Dictionary comparison---------------------

        /*
         * all this mess with the lengths of words is not worth it with
         * dictionary this size, but if i chose to compare to a bigger
         * one it would optimize a tiny bit the program because it makes
         * sure it compares to words that are the same length only
         * (at least in theory...)
         *
         * i might get back to that...
         */

        /*
        int letterMatch = 0; //a temporary variable to store current length of a word
        int match = 0;
        //counter to cycle through lengths of words
        for (i = 0; i < arraySize; i++) {
            //making sure we are not checking punctuation for a match
            if (messageWord[i] != 0) {
                //cycling through arrays storing lengths of the words for a match
                for (int counter = 0; counter < arraySize; counter++) {
                    //if there is a match in lengths im starting the
                    //counter to cycle comparison in letters
                    if (messageWord[i] == dictWord[counter]) {
                        //cycling through letters in matching words
                        for (int anotherCounter = 0; anotherCounter <= messageWord[counter]; anotherCounter++) {
                            //Here im comparing
                            if (charArray[anotherCounter] == dictWord[anotherCounter]){
                                letterMatch++;
                            }
                            else {
                                letterMatch = 0;
                            }
                            if (letterMatch > 0) {
                                match++;
                            }
                        }
                    }
                }
            }
        }
         */

        /*
         * this approach is much easier as all it does is cycles through
         * letters in the dictionary comparing it to one letter in the
         * message.
         * if it finds a match it compares a letter after it to the matched
         * word in dictionary
         * if its a miss it moves on to looking again for another matching word
         * to repeat the algorithm
         * if it does match the next word it compares to the letter after that
         * if that's a match i increase the score for that sentence
         * the highest score will be the most probable sentence to be real
         */


        score = 0;
        for (int ii = 0; ii < length; ii++) {
            for (int counter = 0; counter < big_arraySize; counter++) {
                if (bruteArray[ii] == dict[counter] && bruteArray[ii + 1] == dict[counter + 1] && bruteArray[ii + 2] == dict[counter + 2]) {
                    score++;
                    ii++;
                    counter = 0;
                }
            }
        }


        //fprintf(output, "\nScore: %d\n", score);


        if (score >= previousScore) {
            previousScore = score;
            bestKey = i;
        }

    }

    fprintf(output, "Best Key: %d\nScore: %d\n", bestKey, previousScore);
    printf("\nBest Key: %d\nScore: %d\n", bestKey, previousScore);


    for (int counter = 0; counter <= length; counter++) {
        //ignoring all other garbage that may be there
        if (charArray[counter] >= 0 && charArray[counter] <= 127) {

            //Increasing array (that stores an encrypted message)
            //by 1 every loop
            finalDecryption[counter] = charArray[counter] + bestKey;

            //Decrypting only capital letters
            if (charArray[counter] >= 65 && charArray[counter] <= 90) {

                //Letters may go over 90 so we decrease
                //them by 26 to again become letters
                if (finalDecryption[counter] > 90) {
                    finalDecryption[counter] = finalDecryption[counter] - 26;
                }
            }
            else {
                finalDecryption[counter] = charArray[counter];
            }
        }
    }


    for (i = 0; i < length; i++) {
        if (finalDecryption[i] >= 0 && finalDecryption[i] <= 127) {
            fprintf(output, "%c", finalDecryption[i]);
            printf("%c", finalDecryption[i]);
        }
    }
    printf("\n\nCheck out output.txt for the most probable decryption of a message\n");


}

int exitLoop() {
    printf("\n--------------------\n");
    printf("Do you wish to exit?\n");
    printf("(1) Yes\n(2) No\n");
    userChoice = 0;
    printf("Your input: ");
    scanf("%d", &userChoice);
    while (userChoice != 1 && userChoice != 2) {
        printf("That is an invalid input\n");
        printf("Input either 1 or 2: ");
        scanf("%d", &userChoice);
    }
    if (userChoice == 1) {
        printf("You chose to exit\n");
        printf("---------------------------\n");
        return 9;
    }
    else {
        printf("You chose to continue\n");
        printf("---------------------------\n");
        return 0;
    }
}