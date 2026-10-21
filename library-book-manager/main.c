/*
   Zara Gonzalez
   project9_requests.c

   Description:
   This program maintains a linked list of requested books for a classroom library.
   It allows the user to add books in alphabetical order by author's last name
   and first name, delete books by matching title and author, print the list,
   and clear all allocated memory before quitting.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TITLE_LEN 100
#define NAME_LEN 30

struct book{
	char title[TITLE_LEN+1];
	char first[NAME_LEN+1];
	char last[NAME_LEN+1];
	double price;
	int num_requests;
	struct book *next;
};


//function prototypes
struct book *add_to_list(struct book *list);
struct book *delete_from_list(struct book *list);
void print_list(struct book *list);
void clear_list(struct book *list);
int read_line(char str[], int n);

/**********************************************************
 * main: Prompts the user to enter an operation code,     *
 *       then calls a function to perform the requested   *
 *       action. Repeats until the user enters the        *
 *       command 'q'. Prints an error message if the user *
 *       enters an illegal code.                          *
 **********************************************************/
int main(void)
{
  char code;

  struct book *book_list = NULL;  
  printf("Operation Code: a for adding to the list, d for deleting a book"
	  ", p for printing the list; q for quit.\n");
  for (;;) {
    printf("Enter operation code: ");
    scanf(" %c", &code);
    while (getchar() != '\n')   /* skips to end of line */
      ;
    switch (code) {
      case 'a': book_list = add_to_list(book_list);
                break;
      case 'd': book_list = delete_from_list(book_list);
		break;
      case 'p': print_list(book_list);
                break;
      case 'q': clear_list(book_list);
		return 0;
      default:  printf("Illegal code\n");
    }
    printf("\n");
  }
}

struct book *add_to_list(struct book *list){

 struct book *prev, *cur, *new_node;

  new_node = malloc(sizeof(struct book));
  if (new_node == NULL) {
    printf("Database is full; can't add more.\n");
    return list;
  }

  printf("Enter book title: ");
  read_line(new_node->title, TITLE_LEN);

  printf("Enter author's first name: ");

  read_line(new_node->first, NAME_LEN);

  printf("Enter author's last name: ");

  read_line(new_node->last, NAME_LEN);


  for (cur = list;cur != NULL;cur = cur->next)
  if (cur != NULL && strcmp(new_node->title, cur->title)==0 && strcmp(new_node->first, cur->first)==0&&strcmp(new_node->last, cur->last)==0) {
    printf("book already exists\n");
    free(new_node);
    return list;
  }

  printf("Enter book's price: ");
  scanf("%lf", &new_node->price);


  printf("Enter the number of requests: ");
  scanf("%d", &new_node->num_requests);

  /* New node will be inserted into the linked list */
  new_node->next = NULL;

  /* Find the correct ordered position:
     alphabetical by author's last name, then first name */
  prev = NULL;
  cur = list;

  while (cur != NULL &&
         (strcmp(new_node->last, cur->last) > 0 ||
         (strcmp(new_node->last, cur->last) == 0 &&
          strcmp(new_node->first, cur->first) > 0))) {
    prev = cur;
    cur = cur->next;
  }

  /* Insert at the front if list is empty or new node belongs first */
  if (prev == NULL) {
    new_node->next = list;
    return new_node;
  }

  /* Otherwise insert between prev and cur */
  prev->next = new_node;
  new_node->next = cur;

  return list;
}



struct book *delete_from_list(struct book *list)
{
  char first_name[NAME_LEN+1];
  char last_name[NAME_LEN+1];
  char book_title[TITLE_LEN+1];
 
  struct book *cur=list, *prev=NULL;

  printf("Enter title: ");
  read_line(book_title, TITLE_LEN);
  printf("Enter author first name: ");
  read_line(first_name, NAME_LEN);
  printf("Enter author last name: ");
  read_line(last_name, NAME_LEN);

  /* Search for the matching book by title and author name */
  while (cur != NULL) {
    if (strcmp(cur->title, book_title) == 0 &&
        strcmp(cur->first, first_name) == 0 &&
        strcmp(cur->last, last_name) == 0) {

      /* Remove first node if match is at the front */
      if (prev == NULL) {
        list = cur->next;
      } else {
        prev->next = cur->next;
      }

      free(cur);
      printf("book deleted\n");
      return list;
    }

    prev = cur;
    cur = cur->next;
  }

  /* No matching book was found */
  printf("book does not exist\n");
  return list;
  

}

//print all books in the list
void print_list(struct book *list){

 struct book *p;

  printf("\nTitle\t\t\t\t\tFirst Name\tLast Name\t"
         "Requests  Price\n");
  for (p =list; p != NULL; p = p->next)
    printf("%-40s%-16s%-16s%6d%10.2f\n", p->title, p->first,p->last,
           p->num_requests, p->price);

}
//release memory of the nodes in the linked list
void clear_list(struct book *list){
  struct book *p;

  while(list!=NULL){
         p = list;
         list = list->next;
         if(p!=NULL)
            free(p);
  }
}

//read a line of text
int read_line(char str[], int n){
  int ch, i = 0;

  while (isspace(ch = getchar()))
    ;
  str[i++] = ch;
  while ((ch = getchar()) != '\n') {
    if (i < n)
      str[i++] = ch;
    
   }
   str[i] = '\0';
   return i;
}
