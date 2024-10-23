
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Struct contact used here for creating contact to work with
// numericRepresenation is contacts name converted to numbers as expected on input
typedef struct Contact {
    char name[101];
    char number[10];
    char numericRepresentaion[101];
} Contact;

// Converts text to numeric representation, used for contacts names
char* convertToNumbers(char name[101]) {
    static char result[101];
    bool end = false;
    int nChar;
    for (nChar = 0; nChar < 101; nChar++) {
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
int isMatch(char inputSearch[101], Contact contact) {
    if (strstr(contact.numericRepresentaion, inputSearch)) return 1;
    else if (strstr(contact.number, inputSearch)) return 2;
    else return 0;
}

// printing contact
void printContact(Contact contact) {
    printf("%s, %s\n", contact.name, contact.number);
}

int isAllDigits(char input[101]) {
    for (int iChar = 0; iChar < (int)strlen(input); iChar++) {
        if (!isdigit(input[iChar])) return 0;
    }
    return 1;
}

// Arguments expected:
// 1: input for search;
// 2: file name
// optional argument on first position might be "-s", than all arguments are shifted by 1
int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Not enough arguments: %s <number> <filename>\n", argv[0]);
        return 1;
    }
    bool advancedSearch = false;
    int mod = 0;
    if (strcmp(argv[1], "-s") == 0) {
        advancedSearch = true;
        mod++;
    }
    if (!isAllDigits(argv[1+mod])) {
        fprintf(stderr, "Searched string should be all digits!\n");
    }

    if (advancedSearch) {
        printf("advanced\n");
    }

    printf("%d\n", isAllDigits("657"));
    printf("%d\n", isAllDigits("6+7"));
    printf("%d\n", isAllDigits("657f"));
    
    // Number of contacts found, used for detecting in no contacts were found
    int numOfMatches = 0;

    char inputSearch[101];
    strcpy(inputSearch, argv[1]);

    Contact workingContact;
    strcpy(workingContact.name, "Sam");
    strcpy(workingContact.number, "123456789");
    strcpy(workingContact.numericRepresentaion, convertToNumbers(workingContact.name));

    //printf("%s (%s): %s\n", workingContact.name, workingContact.number, workingContact.numericRepresentaion); // debug

    if (isMatch(inputSearch, workingContact)) {
        printContact(workingContact);
        numOfMatches++;
    }

    if (numOfMatches == 0) printf("not found\n");
    
    

    return 0;
}


