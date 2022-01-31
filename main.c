// Name: Alex Nedev
// Student Number: 101195595

//=================================================================================//
//                                 Include statements                              //
//=================================================================================//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "refugee.h"

//=================================================================================//
//                                   Main Function                                 //
//=================================================================================//

int main(){

    // Hold information about the refugee list
    NodeType* users = NULL;
    int numRefugees = 0;
    int position = -1;
    
    // Hold input for new user information
    char userID[MAX_ID] = "";
    char name[MAX_STR] = "";
    char profession[MAX_STR] = "";
    int age = -1;
    
    // Hold information for when navigating the menu
    char choice[10] = "";
    int isNotAlphNum = 1;

    while (1){

        // Input Menu
        printf("\n");
        printf("======================================\n");
        printf("(E): Enter information\n");
        printf("(A): Display information\n");
        printf("(I): Display information for an individual\n");
        printf("(Y): Show youngest person\n");
        printf("(R): Remove an individual\n");
        printf("(S): Sort the database\n");
        printf("(Q): Quit the program\n");
        printf("======================================\n");
        printf("Select one of the options in the menu: ");
        scanf(" %s", choice);

        //? Creates and adds a new refugee to the database
        if(toupper(choice[0]) == 'E' && strlen(choice) == 1){
            printf("Enter an alphanumeric ID for the refugee that's 10 characters long: ");
            scanf(" %[^\n]s", userID);

            // Checks the user ID to make sure it's alphanumeric and less than 10
            while(isNotAlphNum){
                // Ensures ID is of the appropriate length
                if(strlen(userID) != MAX_ID-1){
                    printf("Invalid refugee ID. Make sure it's 10 characters max: ");
                    scanf(" %[^\n]s", userID);
                }
                else{
                    // Ensures the ID is alphanumeric
                    for(int i=0; i<strlen(userID); i++){
                        if(isalnum(userID[i]) == 0){
                            break;
                        }
                        else if(i == strlen(userID)-1){
                            isNotAlphNum = 0;
                        }
                    }

                    // Gets new ID from user if entered ID is invalid
                    if(isNotAlphNum){
                        printf("Invalid refugee ID. Make sure it's alphanumeric!");
                        scanf(" %[^\n]s", userID);
                    }   
                }
            }
            isNotAlphNum = 1;

            printf("Enter the name of the refugee: ");
            scanf(" %[^\n]s", name);

            printf("Enter the profession of the refugee: ");
            scanf(" %[^\n]s", profession);

            printf("Enter the age of the refugee: ");
            scanf(" %d", &age);

            // Ensures the 0 < age <= 120
            while(1){
                if(age < 1 || age > 120){
                    printf("Invalid input. Age must be greater than 1 or less than or equal to 120: ");
                    scanf(" %d", &age);
                }
                else{
                    break;
                }
            }

            printf("\nThere are currently %d refugees in the list.\nEnter where you would like to store this new refugee(Between 0 and %d, inclusive): ", numRefugees, numRefugees);
            scanf(" %d", &position);

            // Ensures that the user selects a valid place to put the new refugee
            while(1){
                // If the selected position is valid, add the refugee
                if((position >= 0 && position <= numRefugees) || (position == 0 && numRefugees == 0)){
                    break;
                }

                // Get new input if the position is invalid
                else{
                    printf("Invalid position selected. Please enter a number between 0 and %d(inclusive): ", numRefugees);
                    scanf(" %d", &position);
                }
            }

            // Initializes new refugee
            Refugee* new_refugee = NULL;
            init_refugee(userID, name, profession, age, &new_refugee);
            numRefugees++;

            // Adds new refugee to the database
            add_user(&users, new_refugee, position);
            printf("Refugee has been successfully added!\n");
            
        }

        //? Displays all refugees in the linked list/database
        else if(toupper(choice[0]) == 'A' && strlen(choice) == 1){
            
            // Checks if there are refugees in the linked list
            if(users == NULL){
                printf("The list is currently empty!\n");
            }
            else{
                display_users(&users);
            }
        }
        
        //? Find and displays the refugee with the specified ID
        else if(toupper(choice[0]) == 'I' && strlen(choice) == 1){

            // Checks if there are refugees in the linked list
            if(users == NULL){
                printf("The list is currently empty!\n");
            }
            else{
                printf("Enter the ID of the user you want to find: ");
                scanf(" %[^\n]s", userID);

                Refugee* foundRefugee = search_user(&users, userID);
                // Ensures that the refugee was found before trying to print them
                if(foundRefugee == NULL){
                    printf("User wasn't found.\n");
                }
                else{
                    print_refugee(foundRefugee);
                }
            }

        }

        //? Finds and displays the youngest refugee
        else if(toupper(choice[0]) == 'Y' && strlen(choice) == 1){
            
            // Checks if there are refugees in the linked list
            if(users == NULL){
                printf("The list is currently empty!\n");
            }
            else{
                Refugee* youngestRefugee = youngest_user(&users);
                print_refugee(youngestRefugee);
            }

        }

        //? Removes the refugee with the specified ID
        else if(toupper(choice[0]) == 'R' && strlen(choice) == 1){

            // Checks if there are refugees in the linked list
            if(users == NULL){
                printf("The list is currently empty!\n");
            }
            else{
                printf("Enter the ID of the user you want to remove: ");
                scanf(" %[^\n]s", userID);
                int returnValue = remove_user(&users, userID);

                // Checks to see if the refugee was successfully removed
                if(returnValue){
                    printf("Refugee successfully removed!\n");
                    numRefugees--;
                }
                else{
                    printf("Refugee not found. Nothing was removed.\n");
                }
            }
        }

        //? Sorts the database in descending order
        else if(toupper(choice[0]) == 'S' && strlen(choice) == 1){
            
            // Checks if there are refugees in the linked list
            if(users == NULL){
                printf("The list is currently empty!\n");
            }
            // Checks if there's only 1 refugee in the database
            else if(users->next == NULL){
                printf("Only 1 refugee is present. The list is sorted!\n");
            }
            else{
                sort_refugees(&users);
            }
        }

        //? Quits the program
        else if(toupper(choice[0]) == 'Q' && strlen(choice) == 1){
            printf("Goodbye, see you next time!\n");
            break;
        }

        //? Catches any invalid input
        else{
            printf("Invalid input. Select one of the options in the menu.\n");
        }
    }

    //? Deallocates all allocated memory during runtime
    cleanup(users);

    return 0;
}