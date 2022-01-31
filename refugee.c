// Name: Alex Nedev
// Student Number: 101195595

//=================================================================================//
//                                 Include statements                              //
//=================================================================================//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "refugee.h"

//=================================================================================//
//                           Header Function Definition                            //
//=================================================================================//

// Initializes a Refugee structure with the values passed as parameters
void init_refugee(char* userid, char* name, char* profession, int age, Refugee **new_refugee){

    // Assigns memory for the new refugee structure
    *new_refugee = (Refugee*)malloc(sizeof(Refugee));
    if(*new_refugee == NULL){
        printf("Memory allocation error\n");
        exit(0);
    }

    // Assigns the values of the fields for the new refugee
    strcpy((*new_refugee)->userid, userid);
    strcpy((*new_refugee)->name, name);
    strcpy((*new_refugee)->profession, profession);
    (*new_refugee)->age = age;

}

// Adds a user to the Linked list
void add_user(NodeType **list, Refugee *refugee, int pos){
    
    // Node that contains the new refugee data
    NodeType *newRefugee = (NodeType*)malloc(sizeof(NodeType));;
    newRefugee->data = refugee;
    newRefugee->next = NULL;

    // Node that keeps track of the current refugee we're looking at
    NodeType *previousNode = NULL;
    NodeType *currentNode = *list;
    int currentPos = 0;

    // Find the node at the specified position
    while(currentNode != NULL){
        if(currentPos == pos){
            break;
        }
        ++currentPos;

        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    // If the position doesn't exist in the list, return an error
    if(currentPos != pos){
        printf("You have entered an invalid position.\n");
        return;
    }

    // Catches case where we're working with the first element or list is empty
    if(previousNode == NULL){
        *list = newRefugee;
    }
    // Adds element to the middle or end of the list
    else{
        previousNode->next = newRefugee;
    }
    newRefugee->next = currentNode;

}

// Prints the data associated with a Refugee object
void print_refugee(const Refugee *refugee){
    printf("\n");
    printf("Refugee ID: %s\n", refugee->userid);
    printf("Refugee Name: %s\n", refugee->name);
    printf("Refugee Profession: %s\n", refugee->profession);
    printf("Refugee age: %d\n", refugee->age);
}

// Displays all the users in the Linked list
void display_users(NodeType **list){

    NodeType* currentNode = *list;

    // Prints out all users in the list
    while(currentNode != NULL){
        print_refugee(currentNode->data);
        currentNode = currentNode->next;
    }

}

// Returns the user in the Linked list that matches the userid
Refugee* search_user(NodeType **list, char *userid){

    NodeType* currentNode = *list;

    // Iterate over all refugees in the list
    while(currentNode != NULL){
        // If ID of current refugee matches ID we're looking for
        // return that refugee
        if(strcmp(currentNode->data->userid, userid) == 0){
            return currentNode->data;
        }
        currentNode = currentNode->next;
    }

    return NULL;

}

// Returns the youngest user in the Linked list
Refugee* youngest_user(NodeType **list){

    NodeType* currentNode = *list;
    // Returns NULL if the list is empty(Needed for sort function)
    if(currentNode == NULL){
        return NULL;
    }
    Refugee* youngestRefugee = currentNode->data;

    // If there's only 1 user in the list, return that user
    if(currentNode->next == NULL){
        return currentNode->data;
    }
    else{
        // Iterate over all refugees in the list
        while(currentNode != NULL){
            // If current refugee is younger than the currently stored
            // youngest refugee, set youngest refugee to the current refugee
            if(currentNode->data->age < youngestRefugee->age){
                youngestRefugee = currentNode->data;
            }

            currentNode = currentNode->next;
        }
    }

    return youngestRefugee;
}

// Removes a user from the Linked list
int remove_user(NodeType **list, char *userid){

    // Keeps track of the current and previous users
    NodeType *currentNode, *previousNode;
    previousNode = NULL;
    currentNode = *list;

    // Find the user we want to remove
    while(currentNode != NULL){
        if(strcmp(currentNode->data->userid, userid) == 0){
            break;
        }

        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    // Deals with cases where the refugee we're trying to remove
    // doesn't exist
    if(currentNode == NULL){
        return 0;
    }
    // Set the head of the list to be the next element
    if(previousNode == NULL){
        *list = currentNode->next;
    }
    // Remove all connections with the current node
    else{
        previousNode->next = currentNode->next;
    }

    // Free up the memory taken up by the node
    free(currentNode->data);
    free(currentNode);

    return 1;
}

// Deallocates memory for the Linked list
void cleanup(NodeType *head){

    // Checks if there are refugees in the linked list
    if(head != NULL){
        NodeType* currentNode = head;
        NodeType* nextNode = currentNode->next;

        // Go through the entire list an deallocate all allocated memory
        while(currentNode != NULL){
            free(currentNode->data);
            free(currentNode);
            currentNode = nextNode;

            // Ensures we're not trying to access field of a NULL node
            if(nextNode != NULL){
                nextNode = nextNode->next;
            }
        }
    }

}

// BONUS: Sorts the database in descending order
void sort_refugees(NodeType **list){

    // Stores sorted list
    NodeType* sortedList = NULL;
    // Used to store a deep copy of the youngest refugee
    Refugee* newYoungestRefugee = NULL;
    // Youngest refugee of the unsorted list
    Refugee* youngestRefugee = youngest_user(list);
    
    // Create a sorted list
    while(youngestRefugee != NULL){
        // Make deep copy of youngest refugee
        init_refugee(youngestRefugee->userid, youngestRefugee->name, youngestRefugee->profession, youngestRefugee->age, &newYoungestRefugee);
        // Add this copy to the front of the list
        add_user(&sortedList, newYoungestRefugee, 0);
        // Remove the original youngest refugee from the unsorted list
        remove_user(list, youngestRefugee->userid);
        // Find new youngest refugee now that the previous one is removed
        youngestRefugee = youngest_user(list);

        // Repeat the process until unsorted list is empty
    }

    *list = sortedList;
    printf("List has been sorted!\n");
}