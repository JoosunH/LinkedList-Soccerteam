//
// EECS2031 team.c
//
// Program for maintaining a personal team.
//
//
// Uses a linked list to hold the team players.
//
// Author: <Your Name Goes Here>
// Student Info: <Your Student Number Goes Here>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

//**********************************************************************
// Linked List Definitions
//  Define your linked list node and pointer types
//  here for use throughout the file.
//
//
//   ADD STATEMENT(S) HERE

//**********************************************************************
// Linked List Function Declarations
//
// Functions that modify the linked list.
//   Declare your linked list functions here.
//
//   ADD STATEMENT(S) HERE
typedef struct NODE
{
    struct NODE *next;
    char *familyName;
    char *firstName;
    char position;
    int worthValue;
} Node;

const int MAX_LENGTH = 1023;
//**********************************************************************
// Support Function Declarations
//

void safegets(char s[], int arraySize);      // gets without buffer overflow
void familyNameDuplicate(char familyName[]); // marker/tester friendly
void familyNameFound(char familyName[]);     //   functions to print
void familyNameNotFound(char familyName[]);  //     messages to user
void familyNameDeleted(char familyName[]);
void printTeamEmpty(void);
void printTeamTitle(void);
void printNoPlayersWithLowerValue(int value);
bool checkForDuplicateFamilyName(Node *head, char FamilyNameAlready[MAX_LENGTH]);
void searchFamilyName(Node *head, char familyNameToFound[MAX_LENGTH]);
void printTeam();
Node *deleteTheFamily(Node *head, char familyNameDelte[MAX_LENGTH]);
void insertNodesInOrder(char familyName[MAX_LENGTH], char firstName[MAX_LENGTH], char position, int worthValue);
void deleteAllNodes();
void worthLess(int worthValue);

//**********************************************************************
// Program-wide Constants
//

const char NULL_CHAR = '\0';
const char NEWLINE = '\n';
const char GOALKEEPER = 'G';
const char DEFENDER = 'D';
const char MIDFIELDER = 'M';
const char STRIKER = 'S';
Node *head;

//**********************************************************************
// Main Program
//

int main(void)
{
    const char bannerString[] = "Personal Team Maintenance Program.\n\n";
    const char commandList[] = "Commands are I (insert), D (delete), S (search by name),\n"
                               "  V (search by value), P (print), Q (quit).\n";

    // Declare linked list head.
    //   ADD STATEMENT(S) HERE TO DECLARE LINKED LIST HEAD.

    char *familyName, *firstName;
    char position;

    char valueChar[MAX_LENGTH];

    familyName = (char *)malloc(MAX_LENGTH * sizeof(char));
    firstName = (char *)malloc(MAX_LENGTH * sizeof(char));

    // announce start of program
    printf("%s", bannerString);
    printf("%s", commandList);

    char response;
    char input[MAX_LENGTH + 1];
    do
    {
        printf("\nCommand?: ");
        safegets(input, MAX_LENGTH + 1);
        // Response is first char entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if (response == 'I')
        {
            // Insert a player entry into the linked list.
            // Maintain the list in correct order (G, D, M, S).
            //   ADD STATEMENT(S) HERE

            printf("  family name: ");
            safegets(familyName, MAX_LENGTH);

            printf("  first name: ");
            safegets(firstName, MAX_LENGTH);

            printf("  position: ");
            safegets(&position, MAX_LENGTH);

            printf("  value: ");
            safegets(valueChar, MAX_LENGTH);
            int worthValue = strtol(valueChar, NULL, 10);

            if (!checkForDuplicateFamilyName(head, familyName))
            {
                insertNodesInOrder(familyName, firstName, position, worthValue);
            }
            else
            {
                familyNameDuplicate(familyName);
            }

            // USE THE FOLLOWING PRINTF STATEMENTS WHEN PROMPTING FOR DATA:
            // printf("  family name: ");
            // printf("  first name: ");
            // printf("  position: ");
            // printf("  value: ");
        }
        else if (response == 'D')
        {
            // Delete a player from the list.

            printf("\nEnter family name for entry to delete: ");
            char *familyName = (char *)malloc(MAX_LENGTH * sizeof(char));
            //   ADD STATEMENT(S) HERE
            safegets(familyName, MAX_LENGTH);
            head = deleteTheFamily(head, familyName);
        }
        else if (response == 'S')
        {
            // Search for a player by family name.

            printf("\nEnter family name to search for: ");

            //   ADD STATEMENT(S) HERE
            safegets(familyName, MAX_LENGTH);
            searchFamilyName(head, familyName);
        }
        else if (response == 'V')
        {
            // Search for players that are worth less than or equal a value.

            printf("\nEnter value: ");

            //   ADD STATEMENT(S) HERE
            safegets(valueChar, MAX_LENGTH);
            int worthValue = strtol(valueChar, NULL, 10);

            worthLess(worthValue);
        }
        else if (response == 'P')
        {

            //   ADD STATEMENT(S) HERE
            printTeam();
        }
        else if (response == 'Q')
        {
            ; // do nothing, we'll catch this case below
        }
        else
        {
            // do this if no command matched ...
            printf("\nInvalid command.\n%s\n", commandList);
        }
    } while (response != 'Q');

    // Delete the whole linked list that hold the team.
    //   ADD STATEMENT(S) HERE
    deleteAllNodes();

    // Print the linked list to confirm deletion.
    //   ADD STATEMENT(S) HERE
    printTeam();

    return 0;
}

//**********************************************************************
// Support Function Definitions

// Function to get a line of input without overflowing target char array.
void safegets(char s[], int arraySize)
{
    int i = 0, maxIndex = arraySize - 1;
    char c;
    while (i < maxIndex && (c = getchar()) != NEWLINE)
    {
        s[i] = c;
        i = i + 1;
    }
    s[i] = NULL_CHAR;
}

// Function to call when user is trying to insert a family name
// that is already in the book.
void familyNameDuplicate(char familyName[])
{
    printf("\nAn entry for <%s> is already in the team!\n"
           "New entry not entered.\n",
           familyName);
}

// Function to call when a player with this family name was found in the team.
void familyNameFound(char familyName[])
{
    printf("\nThe player with family name <%s> was found in the team.\n",
           familyName);
}

// Function to call when a player with this family name was not found in the team.
void familyNameNotFound(char familyName[])
{
    printf("\nThe player with family name <%s> is not in the team.\n",
           familyName);
}

// Function to call when a family name that is to be deleted
// was found in the team.
void familyNameDeleted(char familyName[])
{
    printf("\nDeleting player with family name <%s> from the team.\n",
           familyName);
}

// Function to call when printing an empty team.
void printTeamEmpty(void)
{
    printf("\nThe team is empty.\n");
}

// Function to call to print title when whole team being printed.
void printTeamTitle(void)
{
    printf("\nMy Team: \n");
}

// Function to call when no player in the team has lower or equal value to the given value
void printNoPlayersWithLowerValue(int value)
{
    printf("\nNo player(s) in the team is worth less than or equal to <%d>.\n", value);
}

//**********************************************************************
// Add your functions below this line.
bool checkForDuplicateFamilyName(Node *head, char FamilyNameAlready[MAX_LENGTH])
{
    if (head == NULL)
    {
        return false;
    }
    Node *curr = head;
    while (curr != NULL)
    {
        if (strcmp(head->familyName, FamilyNameAlready) == 0)
        {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void insertNodesInOrder(char familyName[MAX_LENGTH], char firstName[MAX_LENGTH], char position, int worthValue)
{
    if (position == 'G') // going very first
    {
        Node *newNode = (Node *)malloc(sizeof(Node));

        newNode->firstName = strdup(firstName);
        newNode->familyName = strdup(familyName);
        newNode->position = position;
        newNode->worthValue = worthValue;

        newNode->next = head;
        head = newNode;
    }
    else if (position == 'S') // going very last
    {
        Node *newNode = (Node *)malloc(sizeof(Node));

        newNode->firstName = strdup(firstName);
        newNode->familyName = strdup(familyName);
        newNode->position = position;
        newNode->worthValue = worthValue;
        newNode->next = NULL;
        if (head == NULL)
        {
            head = newNode;
            return;
        }
        Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next; // set temp to point very last node address.
        }
        temp->next = newNode; // using that address to point the next one and store it.
    }
    else if (position == 'M')
    {
        Node *newNode = (Node *)malloc(sizeof(Node));

        newNode->firstName = strdup(firstName);
        newNode->familyName = strdup(familyName);
        newNode->position = position;
        newNode->worthValue = worthValue;

        Node *temp = head, *prev;

        if (head == NULL)
        { // if node is by itself, the input node becomes an head of the node
            newNode->next = NULL;
            head = newNode;
            return;
        }

        while (temp->position != 'S' && temp->next != NULL)
        { // going through the loop until it hits value S, the loop will stop right befroe the node with value 'S
            prev = temp;
            temp = temp->next;
        }

        if (temp->next == NULL)
        { // putting input node between prev node and temp
            if (temp->position == 'S')
            {
                newNode->next = temp;
                prev->next = newNode;
                return;
            }
            else

                prev->next = temp;
            temp->next = newNode;
            return;
        }

        newNode->next = temp;
        prev->next = newNode;
    }
    else if (position == 'D')
    {
        Node *newNode = (Node *)malloc(sizeof(Node));

        newNode->firstName = strdup(firstName);
        newNode->familyName = strdup(familyName);
        newNode->position = position;
        newNode->worthValue = worthValue;

        Node *temp = head, *prev;
        prev = NULL;

        if (head == NULL)
        { // if node is by itself, the input node becomes an head of the node
            newNode->next = NULL;
            head = newNode;
            return;
        }

        while (temp->next != NULL && temp->position != 'M')
        { // going through the loop until it hits value M, the loop will stop right befroe the node with value 'S
            prev = temp;
            temp = temp->next;
        }
        if (temp->next == NULL)
        {
            if (temp->position == 'M')
            {
                prev->next = newNode;
                newNode->next = temp;
                return;
            }

            else
                newNode->next = temp;
            prev->next = newNode;
            return;
        }
        newNode->next = temp;
        prev->next = newNode;
    }
}
Node *deleteTheFamily(Node *head, char familyNameDelte[MAX_LENGTH])
{
    if (head == NULL)
    {
        return NULL;
    }

    // If the first node is to be deleted
    if (strcmp(head->familyName, familyNameDelte) == 0)
    {
        Node *temp = head->next;
        familyNameDeleted(head->familyName);
        free(head->familyName);

        free(head);
        return temp;
    }

    bool foundTheFamilyName = false;

    Node *current = head;

    while (!foundTheFamilyName && current->next != NULL)
    {
        if (strcmp(current->next->familyName, familyNameDelte) == 0)
        {
            foundTheFamilyName = true;
        }

        else
        {
            current = current->next;
        }
    }

    // if there exists a node to be deleted
    if (current->next != NULL)
    {
        Node *familyNameToRemove = current->next;
        current->next = current->next->next;
        familyNameDeleted(familyNameToRemove->familyName);
        free(familyNameToRemove->familyName);
        free(familyNameToRemove);
    }

    return head;
}
void searchFamilyName(Node *head, char familyNameToFound[MAX_LENGTH])
{
    if (head == NULL)
    {
        return;
    }

    Node *current = head;

    while (current != NULL)
    {
        if (strcmp(current->familyName, familyNameToFound) == 0)
        {
            familyNameFound(familyNameToFound);
            printf("%s\n", current->familyName);
            printf("%s\n", current->firstName);
            printf("%c\n", current->position);
            printf("%d\n", current->worthValue);
            return;
        }
        current = current->next;
    }

    familyNameNotFound(familyNameToFound);
    return;
}
void printTeam()
{

    Node *current = head;

    if (current == NULL)
    {
        printTeamEmpty();
    }

    else
    {
        printTeamTitle();

        while (current != NULL)
        {
            printf("\n");
            printf("%s\n", current->familyName);
            printf("%s\n", current->firstName);
            printf("%c\n", current->position);
            printf("%d\n", current->worthValue);
            current = current->next;
        }
    }
}
void deleteAllNodes()
{
    if (head == NULL)
    {
        printTeamEmpty();
    }

    while (head != NULL)
    {
        Node *firstNode = head;
        head = head->next;
        familyNameDeleted(firstNode->familyName);
        free(firstNode->familyName);
        free(firstNode->firstName);
        free(firstNode);
    }
}

void worthLess(int Value)
{
    Node *current = head;

    if (current->worthValue < Value)
    {
        while (current != NULL)
        {
            printf("\n");
            printf("%s\n", current->familyName);
            printf("%s\n", current->firstName);
            printf("%c\n", current->position);
            printf("%d\n", current->worthValue);
            current = current->next;
        }
    }
    else
    {
        printNoPlayersWithLowerValue(Value);
    }
}
