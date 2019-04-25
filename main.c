#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * BIG LIST
 * Add substitution encryption
 * Add substitution decryption
 */

//Function prototypes
void rotationEncryption();
void rotationDecryption();
void substitutionEncryption();
void substitutionDecryption();
int exitLoop();

//Variable used to stroe user choice (needs to be global)


int main() {

    int userChoice;

    do {
        printf("What would you like to do?\n");
        printf("(1) Rotation Encryption\n");
        printf("(2) Rotation Decryption\n");
        printf("(3) Substitution Encryption\n");
        printf("(4) Substitution Decryption\n");
        printf("Input number: ");
        scanf("%d", &userChoice);
        while (userChoice < 1 && userChoice > 4) {
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

            case 9 :
                break;
            default :
                printf("Invalid input\n" );
        }
    } while (userChoice != 9);
    printf("Thanks for using the program!\n" );
    printf("---------------------------\n");
}

//Algorithm for SUBSTITUTION ENCRYPTION
//SUBSTITUTION STRING and INPUT needed
void substitutionEncryption() {
    /*
     * Ask if user wants to input their substitution string in terminal or does he have it in a file
     * if he chooses to input - stdin
     * if he chooses the file ask him if its already in the substitutionString.txt file
     * if no tell him to fill it and press whatever key when ready to confirm
     * if yes just go ahead
     * ask if user has inputted a message to encryptint an input.txt file
     * if no tell him to do so and confirm with any key that he has done so
     * if yes continue
     * do all the algorithm after
     */

    printf("Do you want to input the substitution string\nin the terminal or into a file?\n" );
    printf("(1) In the terminal\n");
    printf("(2) Into a file\n");
    printf("Input number: ");
    printf("");
    int userNum = 0;
    //userNum = scanf("%i", &userNum);
    scanf ("%d",&userNum);

    //Making sure user inputs the right number
    while (userNum != 1 && userNum != 2) {
        printf("That is an invalid input\n");
        printf("Input must be 1 or 2: ");
        scanf("%d", &userNum);
        printf("\n");
    }

    //Creating an array to hold substitute string
    //It's 50 just to make sure user can "overinput" the 26 characters that are in the alphabet
    char subString[50];

    switch (userNum) {
        case 1:
            printf("--------------------------------\n");
            printf("You chose to input in a terminal\n");

            //Variable used to determine if repetition is needed
            int reInput = 0;
            do {
                printf("Input each of 26 letters in order you want to substitute from A to Z\n");
                printf("To substitute:    ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
                printf("Your substitutes: ");
                //Zeroing the array for future uses
                for (int i = 0; i <= 50; i++) {
                    subString[i] = 0;
                }
                scanf("%s", subString);
                //Making sure string is 26 characters (amount of alphabet letters)
                int i = 0; //counter
                //counting characters in a string
                for (i = 0; subString[i] != '\0'; i++) {}
                while (i != 26) {
                    printf("You have inputted wrong string\n");
                    printf("The substitution string must be 26 characters long\n");
                    printf("Please input again\n");
                    printf("To substitute:    ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
                    printf("Your substitutes: ");
                    scanf("%s", subString);
                    for (i = 0; subString[i] != '\0'; i++) {}
                }
                //Making every char go upper case
                for (int i = 0; i < 50; i++) {
                    subString[i] = toupper(subString[i]);
                }

                printf("The substitution string you inputed is:\n%s.\n", subString);
                printf("---------------------------------------\n");

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
                if (reInput > 0) {
                    printf("You must reenter your string\n");
                    printf("----------------------------\n");
                }

            } while (reInput != 0);
            break;
        case 2:
            printf("------------------------------\n");
            printf("You chose to input into a file\n");

            FILE *input;
            FILE *output;
            input = fopen("input.txt", "r");
            output = fopen("output.txt", "w");
            int i = 0; //counter
            do {
                //Zeroing the array for future uses
                for (i = 0; i <= 50; i++) {
                    subString[i] = 0;
                }

                //Checking if input file exists
                if (input == NULL) {
                    printf("Error Reading File\n");
                    exit(0);
                }

                printf("Input your substitution string in the input.txt file.\n");
                printf("String: ");
                for (i = 0; i < 50; i++) {
                    fscanf(input, "%1c", &subString[i]);
                }

                //Making every char go upper case
                for (int i = 0; i < 50; i++) {
                    subString[i] = toupper(subString[i]);
                }

                for (i = 0; i < 50; i++) {
                    printf("%c", subString[i]);
                }
                printf("\n");

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

                //Making sure string is 26 characters (amount of alphabet letters)
                //counting characters in a string
                for (i = 0; subString[i] != '\0'; i++) {}

                if (i != 26 || reInput > 0) {
                    if (i != 26) {
                        printf("You have inputted wrong string\n");
                        printf("The substitution string must be 26 characters long\n");
                        printf("--------------------------------------------------\n");
                        printf("Please input again, and input any key to continue: ");
                        char anyKey = 0;
                        scanf("%c", &anyKey);
                        for (i = 0; subString[i] != '\0'; i++) {}
                    } else if (reInput > 0) {
                        printf("You have inputted wrong string\n");
                        printf("--------------------------------------------------\n");
                        printf("Correct your mistakes and press any key when ready\n");
                        char anyKey = 0;
                        scanf("%c", &anyKey);
                    }
                }
            } while (reInput > 0 && i != 26);

            break;
        default:
            printf("Something went very wrong...\n");
    }
}

//Algorithm for SUBSTITUTION DECRYPTION
//SUBSTITUTION STRING and INPUT needed
void substitutionDecryption() {

}

//Algorithm for ROTATION DECRYPTION
//KEY and INPUT needed
void rotationDecryption() {
    //----INITIALIZATION-----------------------------------
    FILE *input;
    FILE *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    //-------------------------------------------------
    //Setting up variables
    int arraySize = 1024; //Size of array
    char charArray[arraySize]; //array used to hold a message
    int i = 0; //counter
    int key = 0; //Key used for rotatioin Cypher
    //-------------------------------------------------
//-----------------------------------------------------
    //-------------------------------------------------
    //Zeroing the array because it remembers previous inputs
    for (i = 0; i <= arraySize; i++) {
        charArray[i] = 0;
    }
    //-------------------------------------------------

//-----------------------------------------------------
//Asking for the key
    printf("Input the key: ");
    scanf("%d", &key);
    printf("Got the key and it is: %d.\n", key);
    printf("Check output.txt for decrypted message\n");
    printf("--------------------------------------\n");
//-----------------------------------------------------

    //-------------------------------------------------
    //Making sure Key is between 0 and 25
    if (key < 0) {
        //I'm increasing the key by 26 as many times
        //as it takes to get between 0 and 25
        for (; key < 0; key += 26) {
            //nothing as it just needs to increase
        }
    }
    else if (key > 25) {
        //Same here - decreasing it to get between 0 and 25
        for (; key > 25; key -= 26) {
            //nothing as it just needs to decrease
        }
    }
    //-------------------------------------------------

    //Printing out Key
    fprintf(output, "Key is: %d\n", key);

    //-------------------------------------------------
    //Changing the direction of the key as it is
    //exactly the same as encryption but the other way
    key = key * (-1);
    //-------------------------------------------------

    //-------------------------------------------------
    //Checking if input file exists
    if (input == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
    //-------------------------------------------------

    //-------------------------------------------------
    //Variable for the length of an input
    int length = 0;
    //Here it's scanning character by character (%1c)
    //from an input file
    //and putting it into array of chars
    for (i = 0; i < arraySize; i++){
        fscanf(input, "%1c", &charArray[i]);
    }

    //Making every char go upper case
    for(int i = 0; i < arraySize; i++){
        charArray[i] = toupper(charArray[i]);
    }

    //-------------------------------------------------
    //Checking Length of an input
    i = 0;
    while (charArray[i] <= 90){
        if (charArray[i] == 32) {
            length++;
            i++;
        }
        else if (charArray[i] >= 65) {
            length++;
            i++;
        }
        else {
            i++;
        }
    }
    //-------------------------------------------------

    //Printing original message
    for (i = 0; i < length; i++){
        fprintf(output, "%c", charArray[i]);
    }
    //-------------------------------------------------

    //Printing length
    fprintf(output, "\nLength: %d\n", length);
    //-------------------------------------------------

    //-------------------------------------------------
    //Cypher algorithm
    for (i = 0; i <= length; i++){
        if (charArray[i] == 32) {
            //do nothing
        }
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
    //-------------------------------------------------


    for (i = 0; i < length; i++){
        fprintf(output, "%c", charArray[i]);
    }

    //Closing both files
    fclose(input);
    fclose(output);
}

//Algorithm for ROTATION ENCRYPTION
//KEY and INPUT needed
void rotationEncryption() {
//----INITIALIZATION-----------------------------------
    FILE *input;
    FILE *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    //-------------------------------------------------
    //Setting up variables
    int arraySize = 1024; //Size of array
    char charArray[arraySize]; //array used to hold a message
    int i = 0; //counter
    int key = 0; //Key used for rotatioin Cypher
    //-------------------------------------------------
//-----------------------------------------------------

    //-------------------------------------------------
    //Zeroing the array because it remembers previous inputs
    for (i = 0; i <= arraySize; i++) {
        charArray[i] = 0;
    }
    //-------------------------------------------------

//-----------------------------------------------------
//Asking for the key
    printf("Input the key: ");
    scanf("%d", &key);
    printf("Got the key and it is: %d.\n", key);
    printf("Check output.txt for encrypted message\n");
    printf("---------------------------\n");
//-----------------------------------------------------

    //-------------------------------------------------
    //Making sure Key is between 0 and 25k
    if (key < 0) {
        //I'm increasing the key by 26 as many times
        //as it takes to get between 0 and 25
        for (; key < 0; key += 26) {
            //nothing as it just needs to increase
        }
    }
    else if (key > 25) {
        //Same here - decreasing it to get between 0 and 25
        for (; key > 25; key -= 26) {
            //nothing as it just needs to decrease
        }
    }
    //-------------------------------------------------

    //Printing out Key
    fprintf(output, "Key is: %d\n", key);

    //-------------------------------------------------
    //Checking if input file exists
    if (input == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
    //-------------------------------------------------

    //-------------------------------------------------
    //Variable for the length of an input
    int length = 0;
    //Here it's scanning character by character (%1c)
    //from an input file
    //and putting it into array of chars
    for (i = 0; i < arraySize; i++){
        fscanf(input, "%1c", &charArray[i]);
    }

    //Making every char go upper case
    for(int i = 0; i < arraySize; i++){
        charArray[i] = toupper(charArray[i]);
    }

    //-------------------------------------------------
    //Checking Length of an input
    i = 0;
    while (charArray[i] <= 90){
        if (charArray[i] == 32) {
            length++;
            i++;
        }
        else if (charArray[i] >= 65) {
            length++;
            i++;
        }
        else {
            i++;
        }
    }
    //-------------------------------------------------

    //Printing original message
    for (i = 0; i < length; i++){
        fprintf(output, "%c", charArray[i]);
    }
    //-------------------------------------------------

    //Printing length
    fprintf(output, "\nLength: %d\n", length);
    //-------------------------------------------------

    //-------------------------------------------------
    //Cypher algorithm
    for (i = 0; i <= length; i++){
        if (charArray[i] == 32) {
            //do nothing
        }
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
    //-------------------------------------------------


    for (i = 0; i < length; i++){
        fprintf(output, "%c", charArray[i]);
    }

    //Closing both files
    fclose(input);
    fclose(output);
}

//Function written to exit the option loop
int exitLoop() {
    printf("Do you wish to exit?\n");
    printf("(1) Yes\n(2) No\n");
    int userChoice = 0;
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