#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//----Function prototypes---------------------------

//Function used to encrypt given message using rotation encryption
void rotationEncryption();

//Function used to decrypt given message using rotation decryption
void rotationDecryption();

//Function used to encrypt given message using substitution encryption
void substitutionEncryption();

//Function used to decrypt given message using substitution decryption
void substitutionDecryption();

//Function used to exit main menu
int exitLoop();
//--------------------------------------------------


//----Global Variables------------------------------

int userChoice = 0; //used to store user choices
int i = 0;  //used for loops and counting
//--------------------------------------------------

//Main menu
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

    //----Printing the key--------------------------
    fprintf(output, "Key is: %d\n", key);

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
    for (i = 0; i < length; i++){
        if (charArray[i] >= 32 && charArray[i] <= 127) {
            fprintf(output, "%c", charArray[i]);
        }
    }

    //----Closing both files------------------------
    fclose(input);
    fclose(output);

    printf("Check output.txt for encrypted message\n");
    printf("--------------------------------------\n");
}

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
    for (i = 0; i < length; i++){
        if (charArray[i] >= 32 && charArray[i] <= 127) {
            fprintf(output, "%c", charArray[i]);
        }
    }

    //----Closing both files------------------------
    fclose(input);
    fclose(output);

    printf("Check output.txt for encrypted message\n");
    printf("--------------------------------------\n\n");
}

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
            }
            else {
                fprintf(output, "%c", charArray[i]);
            }
        }
    }

    printf("Check out output.txt for the encrypted message\n");

    //----Closing all the files---------------------
    fclose(input);
    fclose(output);
    fclose(substitutionString);
}

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
            }
            else {
                fprintf(output, "%c", charArray[i]);
            }
        }
    }

    printf("Check out output.txt for the decrypted message\n");

    //----Closing all the files---------------------
    fclose(input);
    fclose(output);
    fclose(substitutionString);
}

//Function written to exit the option loop
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