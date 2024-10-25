# PhoneBook

First school project on uni in C langueage.

## Assignment

Create the program to search in given phone book of contacts based on input.
The input looks like sequence of numbers like on basic push button phone.
For example input string `"23"` would search for all contacts with these letters or numbers: `"23", "2d", "2e", "2f", "a3", "ad"...`

Each contact is represented by two lines in the passed phone book.
First line is name, second line is phone number. All the possible errors should be handeled.
The program should be started using this line:
```bash
./tnine NUMBER_INPUT <seznam.txt
```

`seznam.txt` is the file containing all the contacts.

<img src="https://qph.cf2.quoracdn.net/main-qimg-a3d6e910c9ee593af2df1d8e8a8bf026-lq" alt="Image description" width="200"/>

## Algorithm used

Before writing the code, I wanted to think about the algorithm, since going throug all the combinations from input would take really long and the time would grow exponencionally. Firts I thought about regex.

### Using RegEx

First idea was using regular expresions. I wanted to create array of strings, where each index would represent specific number, here is part of the array and how would it look like:

`
{"[0_]", "[1+]", "[2abc]", "[3edf]", ..., "[9wxyz]"};
`

I would than convert the input string to regular expression. I will get back to the example with `"23"`, this string would convert into this regular expression: `"[2abc][3def]"`. Than I would just run this regular expression on each line and see if match was found. This solution would be even great for bonus assignment, more about it later.

Even though I liked this solution the most, I did not use it. Simply because the leader of the project banned using the RegEx.

### Converting the contacts

My second solution was converting contacts to their numeric representation. For example name `"John"` would be converted to `"5646"`. Then I would only search input string inside this numeric representation, which would not grow exponentionally anymore. Only thing I do not like about this solution is the way I am converting letters to the numbers. This resulted in huge switch case block.

### Bonus asignment

Bonus asignment stated that if the first argument of calling exe file is `-s` the program should use advanced search. Advanced search works similarly as basic search, but accepts not matching characters between desired characters. For example if we search `-s 65` in string `361587` we still get match, beacuse numbers `5` and `6` are present in the string and they are in correct order.

I solved this using only simple for loop, but I would return to the old idea of RegEx, which would only needed `.*` between sets of characters. Example with `-s 65` on input: `[6mno].*[5jkl]`.
## How to run

### Requirements

- [GCC compiler](https://gcc.gnu.org/install/) (if you want to make some changes to code)

1. **Clone the repository**:
    ```bash
    git clone https://github.com/Waaatzon/PhoneBook.git
    ```

2. **Run the exe file inside the cmd**:
    ```bash
    .\tnine NUMBER <seznam.txt
    ```

    For advanced search use `-s` os first argument:
    ```bash
    .\tnine -s NUMBER <seznam.txt
    ```

### Customizing code

If the code was modified, the exe file must be build with this command:

```bash
gcc -std=c11 -Wall -Wextra -Werror tnine.c -o tnine
```

All the warning used are from the assignment and they were mandatory.

### Testing

For test I used program from another student he shared. The program is in python. Link to his repo is [here](https://github.com/TheRamsay/izp-project-1).