/*
 * Made by @dduuh
 * Github: https://github.com/dduuh
 * This is free software. You can modify it or just read it for your learning path.
 * This software used for testing my Linked List. This is Beta-Test..
 * So you can find some bugs in my program when you're trying to add node with value in linked list
 * But node would add after the second try... This is horrible mistake!
 * If you can fix it then modify this code as possible as you can.
*/

#ifndef RUN_H
#define RUN_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

typedef struct Node {
	char data[1024];
	struct Node* next;
} Node;

void
add_node(Node** head, char* data)
{
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (newNode == NULL) {
    perror("Failed to allocate memory");
    return;
  }
  
  strncpy(newNode->data, data, sizeof(newNode->data) - 1);
  //newNode->data[sizeof(newNode->data) - 1] = '\0';
  newNode->next = NULL;

  if (*head == NULL) {
    *head = newNode;
  } else {
    Node* current = *head;
    while (current->next != NULL) {
    	current = current->next;
    }
    current->next = newNode;
  }
}

Node*
pop_last_node(Node** head)
{
	if (*head == NULL) {
		return NULL;
	}

	if ((*head)->next == NULL) {
		Node* last_node = *head;
		*head == NULL;
		return last_node;
	}

	Node* current = *head;
	Node* prev;

	while (current->next != NULL) {
		prev = current;
		current = current->next;
	}

	prev->next = NULL;

	return current;
}

Node*
pop_first_node(Node** head)
{
  if (*head == NULL) {
	return NULL;
  }

  Node* tmp = *head;
  *head = (*head)->next;
  tmp->next = NULL;

  return tmp;
}

void
print_node(Node* head)
{
	if (head == NULL) {
		puts("NULL");
		return;
	}

	while (head->next != NULL) {
		printf("%s ", head->data);
		head = head->next;
	}
	puts("NULL\n");
}

void
freenode(Node* head)
{
	Node* current = head;
	Node* nextNode;
	
	while (current->next != NULL) {
		nextNode = current->next;
		free(current);
		current = nextNode;
	}
}

void
save_to_file(Node* head, const char* filename)
{
	if (head == NULL) {
		fprintf(stderr, "You're trying to save NULL Linked List which is not acceptable");
		_exit(1);
	}

	FILE* save = fopen(filename, "a");

	if (save == NULL) {
		perror("Error creating file");
		_exit(1);
	}

	Node* current = head;
	while (current->next != NULL) {
		fprintf(save, "%s ", current->data);
		current = current->next;
	}
	fclose(save);
	printf("Saved Linked List to %s\n", filename);
}

#define BUFFLEN 1024
char buffer[BUFFLEN];
int nodeChoose = 0;

// Main/Run function
void
run(void)
{
	int choose = 0;
	Node* root = NULL;
S:
	puts("Choose operation:");
	puts("0. Exit");
	puts("1. Linked List");

	scanf("%d", &choose);

	switch (choose) {
	case 0:
		_exit(0);
		break;
	case 1:
	S1:
		puts("0. To the menu");
		puts("1. Add node");
		puts("2. Pop last element");
		puts("3. Pop first element");
		puts("4. Print Node");

		scanf("%d", &nodeChoose);

		switch (nodeChoose) {
		case 0:
		  puts("Save? (Y/n/acc) acc - I came in by accident");
			scanf("%s", buffer);
			if (strcmp(buffer, "n") == 0) {
				freenode(root);
				goto S;
			} else if (strcmp(buffer, "acc") == 0) {
				goto S;
			} else if (strcmp(buffer, "Y") == 0) {
				save_to_file(root, "LinkedList.txt");
				goto S;
			}
		  break;
		case 1:
		  printf("Enter the value: ");
		  scanf("%s", buffer);
		  add_node(&root, buffer);
		  printf("Successfully add \'%s\' in Linked List!\n", buffer);
		  goto S1;
		  break;
		case 2:

		  if (pop_last_node(&root) == NULL) {
			puts("Linked list is empty!");
		  } else {
			puts("Last node has been popped successfully!");
		  }

		  goto S1;
		  break;
		case 3:
		  
		  if (pop_first_node(&root) == NULL) {
			puts("Linked list is empty!");
		  } else {
			puts("First node has benn popped successfully!");
		  }

		  goto S1;
		  break;
		case 4:
		  print_node(root);
		  goto S1;
		  break;
		default:
		  fprintf(stderr, "Incorrect selection!n\n");
		  goto S1;
		  break;
		}
		break;
	default:
		fprintf(stderr, "There is no number choose: %d\n", choose);
		goto S;
		break;
	}
}

#endif