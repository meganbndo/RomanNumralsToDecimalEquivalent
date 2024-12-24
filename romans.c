#include <stdio.h>   // Standard I/O library for file operations and console I/O

// Function prototypes
int romanToValue(char c);  // Converts a Roman numeral character to its integer value
int romanToDecimal(const char *roman);  // Converts a Roman numeral string to a decimal integer
void numberToWords(int num, char *output);  // Converts an integer to its English word representation
void processFile(const char *inputFile, const char *outputFile);  // Processes input and output files
int performOperation(int num1, int num2, char op);  // Performs arithmetic operations
int isValidRoman(const char *roman);  // Checks if a string is a valid Roman numeral
int isArithmeticSymbol(char c);  // Checks if a character is a valid arithmetic symbol
int customStrlen(const char *str);  // Custom function to calculate the length of a string
void customStrcpy(char *dest, const char *src);  // Custom function to copy a string

// Function to get the integer value of a Roman numeral character
int romanToValue(char c) {
    switch (c) {
        case 'I': return 1;         // Roman Numeral I and i
        case 'i': return 1;         
        case 'V': return 5;         // Roman Numeral V and v
        case 'v': return 5;   
        case 'X': return 10;        // Roman Numeral X and x
        case 'x': return 10;  
        case 'L': return 50;        // Roman Numeral L and l
        case 'l': return 50;  
        case 'C': return 100;       // Roman Numeral C and c
        case 'c': return 100; 
        case 'D': return 500;       // Roman Numeral D and d
        case 'd': return 500; 
        case 'M': return 1000;      // Roman Numeral M and m
        case 'm': return 1000;
        default: return 0;    // Invalid character
    }
}

// Custom function to calculate the length of a string
int customStrlen(const char *str) {
    int length = 0;                 // Initialize length counter which is 0
    while (str[length] != '\0') {   // Loop until null terminator is found 
        length++;                   // Increment length for each character
    }
    return length;                  // Return the total length
}

// Custom function to copy a string
void customStrcpy(char *dest, const char *src) {
    while ((*dest++ = *src++) != '\0');             // Copy each character from source to destination
}

// Function to validate if a string is a valid Roman numeral
int isValidRoman(const char *roman) {
    for (int i = 0; i < customStrlen(roman); i++) {  // Iterate over each character in the string
        if (romanToValue(roman[i]) == 0) {           // Check if the character is a valid Roman numeral
            return 0;                                // Return 0 or false if invalid character is found
        }
    }
    return 1;                                     // Return 1 or true if all characters are valid Roman numerals
}

// Function to validate if a character is an arithmetic symbol
int isArithmeticSymbol(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');  // Check if the character is a valid operator
}

// Function to convert Roman numeral string to its decimal equivalent
int romanToDecimal(const char *roman) {
    int total = 0;  // Initialize total to 0 to accumulate the decimal value
    int i;

    for (i = 0; i < customStrlen(roman); i++) {  // Iterate over each character
        int current = romanToValue(roman[i]);   // Get the integer value of the current character
        int next = (i + 1 < customStrlen(roman)) ? romanToValue(roman[i + 1]) : 0;  // Get the integer value of the next character

        if (current < next) {  // If the current value is less than the next value, subtract the current value
            total -= current;
        } else {               // Otherwise, add the current value
            total += current;
        }
    }

    return total;              // Return the total decimal value
}

// Function to convert an integer to its word representation
void numberToWords(int num, char *output) {
    // Arrays for word representation of numbers
    char *ones[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    char *teens[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};


    if (num / 1000 > 0) {  // Check if the number is in the thousands
        sprintf(output + customStrlen(output), "%s Thousand ", ones[num / 1000]);
        num %= 1000;    // Remove the thousands from the number
    }

    if (num / 100 > 0) {  // Check if the number is in the hundreds
        sprintf(output + customStrlen(output), "%s Hundred ", ones[num / 100]);
        num %= 100;     // Remove the hundreds from the number
    }

    if (num >= 10 && num < 20) {  // Check if the number is in the teens
        sprintf(output + customStrlen(output), "%s ", teens[num - 10]);
    } else {
        if (num / 10 > 0) {  // Check if the number is in the tens
            sprintf(output + customStrlen(output), "%s ", tens[num / 10]);
        }
        if (num % 10 > 0) {  // Check if the number is in the ones
            sprintf(output + customStrlen(output), "%s ", ones[num % 10]);
        }
    }
}

// Function to perform arithmetic operation
int performOperation(int num1, int num2, char op) {
    switch (op) {                           // Perform addition to all arithmetic operations
        case '+': return num1 + num2;  
        case '-': return num1 + num2;  
        case '*': return num1 + num2;  
        case '/': return num1 + num2;  
        default: return 0;      // Invalid operator
    }
}

// Function to process a file and compute results
void processFile(const char *inputFile, const char *outputFile) {
    FILE *inFile = fopen(inputFile, "r");       // Open input file for reading
    FILE *outFile = fopen(outputFile, "w");     // Open output file for writing

    if (inFile == NULL || outFile == NULL) {    // Check if files were opened successfully
        printf("Error opening file!\n");        // Print error message if file opening fails
        return;                                 // Exit the function if files cannot be opened
    }

    char roman1[100], roman2[100], op;  // Buffers to store parsed Roman numerals and operator
    while (fscanf(inFile, "%99s", roman1) == 1) {  // Read the first Roman numeral or part of the line
        int numParsed = fscanf(inFile, " %c %99s", &op, roman2);  // Try to read an operator and a second Roman numeral

        if (numParsed == 2 && isValidRoman(roman1) && isValidRoman(roman2) && isArithmeticSymbol(op)) {  // Validate input
            int num1 = romanToDecimal(roman1);                  // Convert first Roman numeral to decimal
            int num2 = romanToDecimal(roman2);                  // Convert second Roman numeral to decimal
            int result = performOperation(num1, num2, op);      // Perform the operation

            char resultWords[500] = "";                         // Buffer to store the result in words
            numberToWords(result, resultWords);                 // Convert the result to words
            fprintf(outFile, "%s\n", resultWords);              // Write the result to the output file
        } else if (numParsed == EOF && isValidRoman(roman1)) {  // Handle lines with a single Roman numeral
            int num = romanToDecimal(roman1);                   // Convert Roman numeral to decimal
            char resultWords[500] = "";                         // Buffer to store the result in words
            numberToWords(num, resultWords);                    // Convert the result to words
            fprintf(outFile, "%s\n", resultWords);              // Write the result to the output file
        } else {
            // Handle invalid input
            fprintf(outFile, "Invalid Input (Invalid character/s: ");  // Write error message to output file
            printf("\nWarning: Invalid input found - ");               // Print warning message to console

            // Check each character in the first Roman numeral for validity
            for (int i = 0; i < customStrlen(roman1); i++) {
                if (romanToValue(roman1[i]) == 0) {  
                    fprintf(outFile, "%c ", roman1[i]);  // Write invalid character to output file
                    printf("%c ", roman1[i]);            // Print invalid character to console
                }
            }

            // Check if the operator is invalid
            if (numParsed > 0 && !isArithmeticSymbol(op)) {
                fprintf(outFile, "%c ", op);  // Write invalid operator to output file
                printf("%c ", op);            // Print invalid operator to console
            }

            // Check each character in the second Roman numeral for validity
            if (numParsed == 2) {
                for (int i = 0; i < customStrlen(roman2); i++) {
                    if (romanToValue(roman2[i]) == 0) {  
                        fprintf(outFile, "%c ", roman2[i]);  // Write invalid character to output file
                        printf("%c ", roman2[i]);            // Print invalid character to console
                    }
                }
            }

            fprintf(outFile, ")\n");  // Close the error message in the output file
            printf("\n");             // Print a newline to the console
        }

        // Clear the input buffer if the line was not fully read
        while (fgetc(inFile) != '\n' && !feof(inFile));  // Read until the end of the line or file
    }

    fclose(inFile);  // Close the input file
    fclose(outFile);  // Close the output file
}

// Main function
int main() {
    char inputFile[50], outputFile[50];  // Buffers to store file names

    printf("Enter input file name: ");  // Prompt user for input file name
    scanf("%s", inputFile);  // Read input file name from user
    printf("Enter output file name: ");  // Prompt user for output file name
    scanf("%s", outputFile);  // Read output file name from user

    processFile(inputFile, outputFile);  // Call function to process the files

    printf("\nProcessing complete. Output written to %s\n", outputFile);  // Notify user of completion
    return 0;  // Return success
}
