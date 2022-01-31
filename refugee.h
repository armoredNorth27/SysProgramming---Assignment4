#define MAX_ID 11
#define MAX_STR 32

// Defines the structure to represent a Refugee
typedef struct{
  char userid[MAX_ID]; // alphanumeric, 10 characters long, and must not contain any special characters
  char name[MAX_STR]; // person's name
  char profession[MAX_STR]; // person's profession
  int age; // value is between 1 and 120
} Refugee;

// Represents a Node in a Linked list
typedef struct Node{
	Refugee *data; 
	struct Node *next;
} NodeType;

// Initializes the Refugee structure with the values passed as parameters
void init_refugee(char* userid, char* name, char* profession, int age, Refugee **new_refugee);

// Prints the data associated with a Refugee object
void print_refugee(const Refugee *refugee);

// Displays all the users in the Linked list
void display_users(NodeType **list); 

// Returns the user in the Linked list that matches the userid
Refugee* search_user(NodeType **list, char *userid); 

// Returns the youngest user in the Linked list
Refugee* youngest_user(NodeType **list); // new function

// Adds a user to the Linked list
void add_user(NodeType **list, Refugee *refugee, int pos);

// Removes a user from the Linked list
int remove_user(NodeType **list, char *userid);

// Deallocates memory for the Linked list
void cleanup(NodeType *head);