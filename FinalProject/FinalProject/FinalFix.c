#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int year;
	char month;
	char day;


}Date;
typedef struct
{
	long long int id;
	char* name;
	char* family;
	long long int PartnerId;
	long long int MotherId;
	long long int FatherId;
	char NumOfChildern;
	long long int* ChildrenPtr;
}Person;
typedef struct
{
	Person* Manage;
	int sizeManage;

}db_mgr;
void init_db(db_mgr* city)
{
	do
	{
		printf("please enter valid positive number for amount of managers");
		scanf("%d", &city->sizeManage);

	} while (city->sizeManage < 0);

	city->Manage = (Person*)calloc(city->sizeManage, sizeof(Person)); //remember to do FREE 
	if (city->Manage == NULL)
	{
		printf("there is no memory to create Manage ptr");
		return;
	}
}
void Print_Person(const Person* SomeOne)
{
	printf("your id : %lld \n your full name : %s %s \n your partner id is : %lld \n your father id is : %lld \n your mother id is : %lld \n number of children : %d \n ", SomeOne->id, SomeOne->name, SomeOne->family, SomeOne->PartnerId, SomeOne->FatherId, SomeOne->MotherId, SomeOne->NumOfChildern);
	for (int i = 0; i < SomeOne->NumOfChildern; i++)
	{
		printf("%d 's kid  id: %lld \n", (i + 1), SomeOne->ChildrenPtr[i]);
	}
}
Person* fakeRealloc(db_mgr* city)
{
	Person* newCity = (Person*)calloc(city->sizeManage + 1, sizeof(Person));
	if (newCity == NULL)
	{
		printf("there is no memory to create Manage ptr");
		return NULL;
	}
	for (int i = 0; i < city->sizeManage; i++)
	{
		newCity[i] = city->Manage[i];

	}
	city->sizeManage++;
	free(city->Manage);
	return newCity;
}
void input_Person_inf(Person* newMan)
{
	char local[256];
	do
	{
		printf("please enter valid id with 8 digits\n");
		scanf(" %lld", &newMan->id);
		fseek(stdin, 0, SEEK_END);
	} while (newMan->id < 10000000 || newMan->id > 100000000);
	do
	{
		printf("please enter name\n");
		scanf(" %s", local);
	} while (local < 0);
	newMan->name = (char*)calloc(strlen(local) + 1, sizeof(char));
	if (newMan->name == NULL)
	{
		printf("there is no memory to give you name");
		return;
	}
	strcpy(newMan->name, local);
	do
	{
		printf("please enter last name\n");
		scanf(" %s", local);
	} while (local < 0);
	newMan->family = (char*)calloc(strlen(local) + 1, sizeof(char));
	if (newMan->family == NULL)
	{
		printf("there is no memory to give you family name");
		return;
	}
	strcpy(newMan->family, local);
	do
	{
		printf("please enter your valid partner id with 8 digits\n");
		scanf(" %lld", &newMan->PartnerId);
		fseek(stdin, 0, SEEK_END);
	} while (newMan->PartnerId < 10000000 || newMan->PartnerId > 100000000);
	do
	{
		printf("please enter your valid mother id with 8 digits\n");
		scanf("%lld", &newMan->MotherId);
		fseek(stdin, 0, SEEK_END);
	} while (newMan->MotherId < 10000000 || newMan->MotherId > 100000000);
	do
	{
		printf("please enter your valid father id with 8 digits\n");
		scanf("%lld", &newMan->FatherId);
		fseek(stdin, 0, SEEK_END);
	} while (newMan->FatherId < 10000000 || newMan->FatherId > 100000000);
	do
	{
		printf("please enter your number of children\n");
		scanf("%d", &newMan->NumOfChildern);
		fseek(stdin, 0, SEEK_END);
	} while (newMan->NumOfChildern < 0);
	if (newMan->NumOfChildern > 0)
	{
		newMan->ChildrenPtr = (long long int*)calloc(newMan->NumOfChildern, sizeof(long long int));
		if (newMan->ChildrenPtr == NULL)
		{
			printf("there is no memory to give you children id's");
			return;
		}
		for (int i = 0; i < newMan->NumOfChildern; i++)
		{
			do
			{
				printf("please enter your valid %d kid id with 8 digits\n", (i + 1));
				scanf("%lld", &newMan->ChildrenPtr[i]);
				fseek(stdin, 0, SEEK_END);
			} while (newMan->ChildrenPtr[i] < 10000000 || newMan->ChildrenPtr[i] > 100000000);
		}
	}
}
void sortedPerson(db_mgr* city)
{
	Person Zon;
	for (int i = 0; i < city->sizeManage - 1; i++)
	{
		if (city->Manage[i].id > city->Manage[i + 1].id)
		{
			Zon = city->Manage[i];
			city->Manage[i] = city->Manage[i + 1];
			city->Manage[i + 1] = Zon;
			i = 0;
		}
	}
}
void addPerson(db_mgr* city)
{
	for (int i = 0; i < city->sizeManage; i++)
	{
		if (city->Manage[i].name == NULL && city->Manage[i].family == NULL)
		{
			input_Person_inf(&city->Manage[i]);
			sortedPerson(city);
			return;
		}
	}
	city->Manage = fakeRealloc(city);
	input_Person_inf(&city->Manage[city->sizeManage - 1]);
	sortedPerson(city);
}
char menu()
{
	char exit = -1;
	do {
		printf("please enter your selection 1-8\n"
			"Database System Menu:\n"
			"1. Add person\n"
			"2. Search a person\n"
			"3. Search Parents\n"
			"4. Delete a person\n"
			"5. Get generation\n"
			"6. Print database\n"
			"7. Search by name\n"
			"8. Quit ");
		scanf("%d", &exit);
		fseek(stdin, 0, SEEK_END);
		if (exit < 1 || exit>8)
		{
			printf("please enter valid number between 1-8 again\n");
		}
	} while (exit < 1 || exit>8);
	return exit;

}
Person* search_id(db_mgr* city, long long idcheck)
{
	for (int i = 0; i < city->sizeManage; i++)
	{
		if (city->Manage[i].name == NULL)
		{
			return NULL;
		}
		else
		{
			if (city->Manage[i].id == idcheck)
				return &(city->Manage[i]);
		}
	}
	return NULL;
}
void search_person(db_mgr* city)
{
	long long int local;
	do
	{
		printf("please enter valid id with 8 digits that you want to find\n");
		scanf("%lld \n", &local);
		fseek(stdin, 0, SEEK_END);
	} while (local < 10000000 || local > 100000000);
	Person* ans = search_id(city, local);
	if (ans == NULL)
	{
		printf("sorry there is no existed people with that id \n");
		return;
	}
	else
		Print_Person(ans);
}
void search_parents(db_mgr* city)
{
	long long int local;
	do
	{
		printf("please enter valid id with 8 digits that you want to find\n");
		scanf("%lld \n", &local);
		fseek(stdin, 0, SEEK_END);
	} while (local < 10000000 || local > 100000000);
	Person* ans = search_id(city, local);
	if (ans == NULL)
	{
		printf("sorry there is no existed people with that id \n");
		return;
	}
	(ans->FatherId == NULL) ? printf("no father \n") : printf("father id %lld \n", ans->FatherId);
	(ans->MotherId == NULL) ? printf("no mother \n") : printf("mother id %lld \n", ans->MotherId);

}

void main()
{
	db_mgr country;

	init_db(&country);
	char chose;
	do
	{
		chose = menu();
		switch (chose)
		{
		case 1:
			addPerson(&country);
			break;
		case 2:
			search_person(&country);
			break;
		case 3:
			search_parents(&country);
			break;
		case 4:
			delete_person(&country);
			break;
		case 5:
			get_gen(&country);
			break;
		case 6:
			printdb(&country);
			break;
		case 7:
			search_by_name(&country);
			break;
		case 8:
			quit(&country);
			break;
		}

	} while (chose != 8);




}