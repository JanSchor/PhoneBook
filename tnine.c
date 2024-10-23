
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Maximal length of contact or number
#define MAX_CONTACT_LENGTH 100


// Struct contact used here for creating contact to work with
// numericRepresenation is contacts name converted to numbers as expected on input
typedef struct Contact {
    char name[MAX_CONTACT_LENGTH+1];
    char number[10];
    char numericRepresentaion[MAX_CONTACT_LENGTH+1];
} Contact;

// Converts text to numeric representation, used for contacts names
char* convertToNumbers(char name[MAX_CONTACT_LENGTH+1]) {
    static char result[MAX_CONTACT_LENGTH+1];
    bool end = false;
    int nChar;
    for (nChar = 0; nChar < MAX_CONTACT_LENGTH+1; nChar++) {
        switch (tolower(name[nChar])) {
        case '+': case '0':
            result[nChar] = '0';
            break;
        case 'a': case 'b': case 'c': case '2':
            result[nChar] = '2';
            break;
        case 'd': case 'e': case 'f': case '3':
            result[nChar] = '3';
            break;
        case 'g': case 'h': case 'i': case '4':
            result[nChar] = '4';
            break;
        case 'j': case 'k': case 'l': case '5':
            result[nChar] = '5';
            break;
        case 'm': case 'n': case 'o': case '6':
            result[nChar] = '6';
            break;
        case 'p': case 'q': case 'r': case 's': case '7':
            result[nChar] = '7';
            break;
        case 't': case 'u': case 'v': case '8':
            result[nChar] = '8';
            break;
        case 'w': case 'x': case 'y': case 'z': case '9':
            result[nChar] = '9';
            break;
        case '\0':
            result[nChar] = '\0';
            end = true;
            break;
        default:
            result[nChar] = name[nChar];
            break;
        }
        if (end) break;
    }
    return result;
}

// Checks if contact number or numericRepresentaion contains input numbers
int isMatch(char inputSearch[MAX_CONTACT_LENGTH+1], Contact contact) {
    if (strstr(contact.numericRepresentaion, inputSearch)) return 1;
    else if (strstr(contact.number, inputSearch)) return 2;
    else return 0;
}

int isMatchAdvanced(char inputSearch[MAX_CONTACT_LENGTH+1], Contact contact) {
    int pivot = 0;
    for (int chName = 0; chName < (int)strlen(contact.name); chName++) {
        if (contact.numericRepresentaion[chName] == inputSearch[pivot]) {
            pivot++;
            if (inputSearch[pivot] == '\0') {
                return 1;
            }
        }
    }
    pivot = 0;
    for (int chNum = 0; chNum < (int)strlen(contact.name); chNum++) {
        if (contact.number[chNum] == inputSearch[pivot]) {
            pivot++;
            if (inputSearch[pivot] == '\0') {
                return 2;
            }
        }
    }
    return 0;
}

// printing contact
void printContact(Contact contact) {
    printf("%s, %s\n", contact.name, contact.number);
}

int isAllDigits(char input[MAX_CONTACT_LENGTH+1]) {
    for (int iChar = 0; iChar < (int)strlen(input); iChar++) {
        if (!isdigit(input[iChar])) return 0;
    }
    return 1;
}


int main(int argc, char *argv[]) {
    int mod = 0;
    // Number of contacts found, used for detecting in no contacts were found
    int numOfMatches = 0;
    Contact workingContact;
    
    if (argc > 1) {
        if (strcmp(argv[1], "-s") == 0) mod = 1;
    }
    char inputSearch[MAX_CONTACT_LENGTH+1];
    if (argc <= 1+mod) {
        strcpy(inputSearch, "\0");
    } else if (!isAllDigits(argv[1+mod])) {
        fprintf(stderr, "Searched string should be all digits!\n");
        return 1;
    } else strcpy(inputSearch, argv[1+mod]);

    char cName[MAX_CONTACT_LENGTH+2];
    char cNumber[MAX_CONTACT_LENGTH+2];
    // Loop that goes through entire list of contacts
    while (fgets(cName, sizeof(cName), stdin)) {
        // Check if contact name is not longer than MAX_CONTACT_LENGTH
        if (cName[MAX_CONTACT_LENGTH+1] == '\n') {
            fprintf(stderr, "Line in the contacts file is too long (name)!\n");
            return 1;
        }
        // Replacing new line character with string end character
        cName[strcspn(cName, "\n")] = '\0';
        // Getting the next line (should be number)
        if (!fgets(cNumber, sizeof(cNumber), stdin)) {
            fprintf(stderr, "Contact without phone number found!");
            return 1;
        }
        // Same check as for contact name
        if (cNumber[MAX_CONTACT_LENGTH+1] == '\n') {
            fprintf(stderr, "Line in the contacts file is too long (number)!\n");
            return 1;
        }
        // Same replace
        cNumber[strcspn(cNumber, "\n")] = '\0';



        // loading current contact to the working contact struct
        strcpy(workingContact.name, cName);
        strcpy(workingContact.number, cNumber);
        strcpy(workingContact.numericRepresentaion, convertToNumbers(workingContact.name));

        // check if phone number is valid
        if (!isAllDigits(workingContact.number)) {
            fprintf(stderr, "Contact number contains non-digit characters!\n");
            return 1;
        }

        if (mod == 0) {
            if (isMatch(inputSearch, workingContact)) {
                printContact(workingContact);
                numOfMatches++;
            }
        } else {
            if (isMatchAdvanced(inputSearch, workingContact)) {
                printContact(workingContact);
                numOfMatches++;
            }
        }
    }
    if (numOfMatches == 0) printf("not found\n");
    return 0;
}
