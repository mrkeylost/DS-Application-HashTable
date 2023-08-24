// 2502011404
// Nikolaus Chandra
// Kelas LB01

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int input, gate;
const int size = 100;

struct Product{
	char id[100];
	char name[25];
	char type[20];
	char variant[20];
	double price;
	
	Product *next;
}*head[size];

// hash function

int hash(char id[]){
	
	int key = 0;
	int idLen = strlen(id);
	
	for(int i = 0;i<idLen;i++){
		key += id[i];
	}
	
	return key % size;
}

// allocation

Product *createProd(char id[], char name[], char type[], char variant[], double price){
	Product *newProd = (Product*)malloc(sizeof(Product));
	
	strcpy(newProd->id, id);
	strcpy(newProd->name, name);
	strcpy(newProd->type, type);
	strcpy(newProd->variant, variant);
	newProd->price = price;
	
	newProd->next = NULL;
	
	return newProd;
}

// insert

Product *entry(Product *curr, char id[], char name[], char type[], char variant[], double price){
	
	if(!curr){
		return createProd(id, name, type, variant, price);
	} else if(strcmp(curr->id, id) == 0){
		strcpy(curr->name, name);
		strcpy(curr->type, type);
		strcpy(curr->variant, variant);
		curr->price = price;
		
		return curr;
	}
	
	curr->next = entry(curr->next, id, name, type, variant, price);
	
	return curr;
}

void menu();
void view();

void insert(){
	
	char id[100];
	char name[25];
	char type[20];
	char variant[20];
	double price;
	int nameLen, tValid, vValid;
	
	do{
		fflush(stdin);
		printf("Input Product Name [3...20] : ");
		scanf("%[^\n]", name);
		nameLen = strlen(name);
	} while(nameLen < 3 || nameLen > 20);
	
	gate++;
	
	do{
		fflush(stdin);
		printf("Input Product Type [Body Care | Skin Care] (case sensitive) : ");
		scanf("%[^\n]", type);
		
		if(strcmp(type, "Body Care") == 0){
			tValid = 1;
			
			if(gate > 0 && gate < 10){
				sprintf(id, "BC00%d", gate);
			} else if(gate >= 10 && gate < 100){
				sprintf(id, "BC0%d", gate);
			} else if(gate >= 100 && gate < 1000){
				sprintf(id, "BC%d", gate);
			}
		} else if (strcmp(type, "Skin Care") == 0){
			tValid = 2;
			
			if(gate > 0 && gate < 1000){
				sprintf(id, "SC00%d", gate);
			} else if(gate >= 10 && gate < 100){
				sprintf(id, "SC0%d", gate);
			} else if(gate >= 100 && gate < 1000){
				sprintf(id, "SC%d", gate);
			}
		}
	} while(tValid < 1 || tValid > 2);
	
	do{
		fflush(stdin);
		printf("Input Product Variant [Relaxing | Calming | Balancing] (case sensitive) : ");
		scanf("%s", variant);
		
		if(strcmp(variant, "Relaxing") == 0){
			vValid = 1;
		} if(strcmp(variant, "Calming") == 0){
			vValid = 2;	
		} if(strcmp(variant, "Balancing") == 0){
			vValid = 3;
		}
	} while(vValid < 1 || vValid > 3);
	
	do{
		fflush(stdin);
		printf("Input Product Price [10.0 - 100.0] : ");
		scanf("%lf", &price);
	} while(price < 10.0 || price > 100.0);
	
	int hash_entry = hash(id);
	head[hash_entry] = entry(head[hash_entry], id, name, type, variant, price);
	
	for(int i = 0;i<size;i++){
		Product *temp = head[i];
				
		while(temp){
			printf("Product ID : %s\n", temp->id);
			break;
		}
	}
	
	if(getchar()){
		printf("Press Enter to continue...");
		getchar();
		system("cls");
	//	view();
		menu();
	}
}

// delete

Product *search(Product *curr, char id[]){
	
	if(!curr){
		return NULL;
	} else if(strcmp(curr->id, id) == 0){
		return curr;
	}
	
	return search(curr->next, id);
}

Product *pull(Product *curr, char id[]){
	
	if(!curr){
		return NULL;
	} else if(strcmp(curr->id, id) == 0){
		Product *temp = curr->next;
		
		free(curr);
		
		return temp;
	}
	
	curr->next = pull(curr->next, id);
	
	return curr;
}

void cut(){
	
	char select[15];
	char confirm[10];
	int conf;
	
	printf("Input product id you want to delete : ");
	scanf("%s", select);
	
	do{
		printf("Delete Product Confirmation [yes | no] (case sensitive): ");
		scanf("%s", confirm);
		
		if(strcmp(confirm, "yes") == 0){
			conf = 1;
			
			int hash_delete = hash(select);
			Product *temp = search(head[hash_delete], select);
	
			if(!temp){
				system("cls");
				menu();
			} else if (strcmpi(temp->id, select) == 0){
				head[hash_delete] = pull(head[hash_delete], select);
				gate--;
		
				printf("Id 		: %s\n", select);
				printf("Name 	: %s\n", temp->name);
				printf("Succes Delete a Product\n");
		
				if(getchar()){
					printf("Press Enter to continue...");
					getchar();
					menu();
				}
			}
		} else if(strcmp(confirm, "no") == 0){
			conf = 2;
			menu();
		}
	} while(conf < 1 || conf > 2);
}

void view(){
	
	if(gate == 0){
		printf("No Product to view\n");
	} else {
		printf("| ID     | Name              | Type              | Variant          | Price     |\n");
		for(int i = 0;i<size;i++){
			if(!(head[i])){
				continue;
			} else {
				Product *temp = head[i];
				
				while(temp){
					printf("| %s  | %s              | %s         |  %s         | %.1lf      |\n", temp->id, temp->name, temp->type, temp->variant, temp->price);
					
					temp = temp->next;
				}
			}
		}
	}
}

void exit(){
	printf("PRESS ENTER TO EXIT...");
	getchar();
}

void menu(){
	
	do{
		printf("Sensatia V0tanicals\n");
		printf("1. Insert Menu\n");
		printf("2. View Menu\n");
		printf("3. Delete Menu\n");
		printf("4. Exit\n>> ");
		scanf("%d", &input);
		system("cls");
	} while(input < 1 || input > 4);
	
	switch(input){
		case 1:
			insert();
			break;
			
		case 2:
			view();
			if(getchar()){
				printf("PRESS ENTER TO MENU...");
				getchar();
				system("cls");
				menu();
			}
			break;
			
		case 3:
			cut();
			view();
			break;
			
		case 4:
			exit();
			break;
	}
}

int main(){
	
	menu();
	
	return 0;
}
