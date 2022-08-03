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
	Date DateOfbirth;
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
void init_db(db_mgr* city)// פונקציה הקולטת מספר מהמשתמש על מנת לצור מערך אנשים  ולעדכן את מספר המקומות מחדש
{
	do
	{
		printf("please enter valid positive number for amount of managers\n");
		scanf("%d", &city->sizeManage);

	} while (city->sizeManage < 0);//יוצא אך ורק אם יש קלט תקין

	city->Manage = (Person*)calloc(city->sizeManage, sizeof(Person));
	if (city->Manage == NULL)//בדיקה האם בוצע הקצאת מקום כראוי במידה ולא הדפסת הודאת שגיאה בהתאם
	{
		printf("there is no memory to create Manage ptr\n");
		return;
	}
}
void Print_Person(const Person* SomeOne)// פונקציה המקבלת מצביע לאדם ומדפיסה את פרטיו
{
	printf("your id : %lld \n your full name : %s %s \n your partner id is : %lld \n your father id is : %lld \n your mother id is : %lld \n number of children : %d \n ", SomeOne->id, SomeOne->name, SomeOne->family, SomeOne->PartnerId, SomeOne->FatherId, SomeOne->MotherId, SomeOne->NumOfChildern);
	printf("your birthday is %d / %d / %d \n", (int)SomeOne->DateOfbirth.day, SomeOne->DateOfbirth.month, SomeOne->DateOfbirth.year);
	for (int i = 0; i < SomeOne->NumOfChildern; i++)
	{
		printf("%d 's kid  id: %lld \n", (i + 1), SomeOne->ChildrenPtr[i]);
	}
}
Person* fakeRealloc(db_mgr* city)// פונקציה המקבלת מצביע לדי בי מנגר ומקצה לו זיכרון לתא נוסף ומעתיקה את הנתונים שהיו בקודם
{//פונקציית דמוי REALLOC
	Person* newCity = (Person*)calloc(city->sizeManage + 1, sizeof(Person));
	if (newCity == NULL)//בדיקה האם בוצע הקצאת מקום כראוי במידה ולא הדפסת הודאת שגיאה בהתאם
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
Person* removeRealloc(db_mgr* city)// פוקנצית דמוי ריאלוק אשר מורידה מקום אחד ,ומעתיקה את כל האיברים
{
	Person* newCity = NULL;
	if (city->sizeManage != 1)
	{
		newCity = (Person*)calloc(city->sizeManage - 1, sizeof(Person));
		if (newCity == NULL)//בדיקה האם בוצע הקצאת מקום כראוי במידה ולא הדפסת הודאת שגיאה בהתאם
		{
			printf("there is no memory to create Manage ptr");
			return NULL;
		}
		for (int i = 1; i < city->sizeManage; i++)//מתחיל מהמקום ה1 בהנחה כי הוא בהכרח יהיה ריק לאחר מיון (ID=0)
		{
			newCity[i - 1] = city->Manage[i];

		}
	}
	city->sizeManage--;
	free(city->Manage);
	return newCity;// הפונקציה מחזירה את המערך החדש 
}
Person* search_id(db_mgr* city, long long idcheck)//הפונקציה מחפשת תעודת זהות של אדם מהמאגר ומחזירה את המצביע אליו
{
	for (int i = 0; i < city->sizeManage; i++)
	{
		if (city->Manage[i].name == NULL)// לטובת יעילות מדלג על האיברים הריקים
		{
			continue;
		}
		else
		{
			if (city->Manage[i].id == idcheck)
				return &(city->Manage[i]);
		}
	}
	return NULL;// במידה ולא נמצא אדם עם תעודה כזאת מחזירה NULL
}
void input_Person_inf(Person* newMan)//פונקציה שמקבלת מצביע לאדם וקולטת ערכים לתוכו
{
	char local[256];
	do
	{
		printf("please enter valid id with 8 digits\n");
		scanf(" %lld", &newMan->id);
		fseek(stdin, 0, SEEK_END);
	} while (newMan->id < 10000000 || newMan->id > 100000000);//בדיקה האם הקלט תקין
	do
	{
		printf("please enter name\n");
		scanf(" %s", local);
		fseek(stdin, 0, SEEK_END);
	} while (local < 0);//בדיקה האם הקלט תקין
	newMan->name = (char*)calloc(strlen(local) + 1, sizeof(char));
	if (newMan->name == NULL)//בדיקה האם הוקצה מקום בזכרון כראוי
	{
		printf("there is no memory to give you name");
		return;
	}
	strcpy(newMan->name, local);
	do
	{
		printf("please enter last name\n");
		scanf(" %s", local);
		fseek(stdin, 0, SEEK_END);

	} while (local < 0);//בדיקה האם הקלט תקין
	newMan->family = (char*)calloc(strlen(local) + 1, sizeof(char));
	if (newMan->family == NULL)
	{
		printf("there is no memory to give you family name");
		return;
	}
	strcpy(newMan->family, local);
	do
	{
		printf("please enter your valid partner id with 8 digits, if there is no one like that enter 0\n");
		scanf(" %lld", &newMan->PartnerId);
		fseek(stdin, 0, SEEK_END);
	} while ((newMan->PartnerId < 10000000 && newMan->PartnerId != 0) || newMan->PartnerId > 100000000);//בדיקה האם הקלט תקין
	do
	{
		printf("please enter your valid mother id with 8 digits\n");
		scanf("%lld", &newMan->MotherId);
		fseek(stdin, 0, SEEK_END);
	} while ((newMan->MotherId < 10000000 && newMan->MotherId != 0) || newMan->MotherId > 100000000);//בדיקה האם הקלט תקין
	do
	{
		printf("please enter your valid father id with 8 digits\n");
		scanf("%lld", &newMan->FatherId);
		fseek(stdin, 0, SEEK_END);
	} while ((newMan->FatherId < 10000000 && newMan->FatherId != 0) || newMan->FatherId > 100000000);//בדיקה האם הקלט תקין
	do
	{
		printf("please enter your number of children\n");
		scanf("%d", &newMan->NumOfChildern);
		fseek(stdin, 0, SEEK_END);
	} while (newMan->NumOfChildern < 0);//בדיקה האם הקלט תקין
	if (newMan->NumOfChildern > 0)
	{
		newMan->ChildrenPtr = (long long int*)calloc(newMan->NumOfChildern, sizeof(long long int));
		if (newMan->ChildrenPtr == NULL)//בדיקה האם הוקצה מקום בזכרון כראוי
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
	do
	{
		printf("please enter your month of birth\n");
		scanf("%d", &newMan->DateOfbirth.month);
		fseek(stdin, 0, SEEK_END);

	} while (newMan->DateOfbirth.month < 1 || newMan->DateOfbirth.month >12);//בדיקה האם הקלט תקין
	do
	{
		printf("please enter your day of birth\n");
		scanf("%d", &newMan->DateOfbirth.day);
		fseek(stdin, 0, SEEK_END);

	} while (newMan->DateOfbirth.day < 1 || newMan->DateOfbirth.day >30);//בדיקה האם הקלט תקין
	do
	{
		printf("please enter your year of birth\n");
		scanf("%d", &newMan->DateOfbirth.year);
		fseek(stdin, 0, SEEK_END);

	} while (newMan->DateOfbirth.year < 1850 || newMan->DateOfbirth.year >2021);//בדיקה האם הקלט תקין

}
void sortedPerson(db_mgr* city)// הפונקציה ממיינת את המאגר לפי תעודות הזהות מהקטן לגדול
{
	Person Zon;//אדם זמני לשמירה
	for (int i = 0; i < city->sizeManage - 1; i++)
	{
		if (city->Manage[i].id > city->Manage[i + 1].id)//בכל פעם שנמצא גדול יותר מהשני , מחליפה בין המיקומים וחוזרת מההתחלה
		{
			Zon = city->Manage[i];
			city->Manage[i] = city->Manage[i + 1];
			city->Manage[i + 1] = Zon;
			i = 0;
		}
	}
}
void addPerson(db_mgr* city)//פונקציה שמוסיפה אדם למאגר
{
	for (int i = 0; i < city->sizeManage; i++)
	{
		if (city->Manage[i].name == NULL && city->Manage[i].family == NULL)
		{
			input_Person_inf(&city->Manage[i]);
			for (int j = 0; j < city->sizeManage; j++)//רץ על כל האנשים במאגר על מנת לבדוק
			{
				if (j == i)//במידה ומדובר היכן שהזנו את האדם הוא ידלג על מנת שנוכל לדעת אם יש אדם מעבר לזה שהקלדנו
				{
					continue;
				}
				if (city->Manage[i].id == city->Manage[j].id)//בדיקה אם תעודת הזהות קיים במאגר כבר
				{//במידה ואכן קיים מרוקן את הנתונים שהוקלדו ומבקש חדשים
					city->Manage[i].id = 0;
					free(city->Manage[i].name);
					free(city->Manage[i].family);
					free(city->Manage[i].ChildrenPtr);
					city->Manage[i].NumOfChildern = 0;
					city->Manage[i].FatherId = 0;
					city->Manage[i].MotherId = 0;
					city->Manage[i].PartnerId = 0;
					city->Manage[i].DateOfbirth.day = 0;
					city->Manage[i].DateOfbirth.month = 0;
					city->Manage[i].DateOfbirth.year = 0;
					printf("you entered already exsist person, please enter agian \n");
					addPerson(city);//חוזר על הפעולה שוב במידה ונמצא אדם זהה לאדם שיצרנו ומוחק את האדם שיצרנו כרגע

				}
			}
			sortedPerson(city);// ממיין מחדש
			return;//עוצר
		}
	}
	city->Manage = fakeRealloc(city);// במידה ואין מקום יוצרים מקום לאדם נוסף במאגר
	input_Person_inf(&city->Manage[city->sizeManage - 1]);
	for (int j = 0; j < city->sizeManage; j++)// בדיקה שהאדם אינו קיים כבר במאגר
	{
		if (j == city->sizeManage - 1)
		{
			continue;
		}
		if (city->Manage[city->sizeManage - 1].id == city->Manage[j].id)
		{
			city->Manage[city->sizeManage - 1].id = 0;
			free(city->Manage[city->sizeManage - 1].name);
			free(city->Manage[city->sizeManage - 1].family);
			free(city->Manage[city->sizeManage - 1].ChildrenPtr);
			city->Manage[city->sizeManage - 1].NumOfChildern = 0;
			city->Manage[city->sizeManage - 1].FatherId = 0;
			city->Manage[city->sizeManage - 1].MotherId = 0;
			city->Manage[city->sizeManage - 1].PartnerId = 0;
			city->Manage[city->sizeManage - 1].DateOfbirth.day = 0;
			city->Manage[city->sizeManage - 1].DateOfbirth.month = 0;
			city->Manage[city->sizeManage - 1].DateOfbirth.year = 0;
			printf("you entered already exsist person, please enter agian \n");
			addPerson(city);

		}
	}
	sortedPerson(city);//ממיין מחדש
}
char menu()// פונקציית תפריט, בחירת פעולה לביצוע, הפונקציה מחזירה את הפעולה המובקשת כתו
{
	int exit = -1;
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
			"8. Quit \n");
		scanf("%d", &exit);
		fseek(stdin, 0, SEEK_END);
		if (exit < 1 || exit>8)
		{
			printf("please enter valid number between 1-8 again\n");
		}
	} while (exit < 1 || exit>8);// תנאי יציאה אך ורק אם הקלט תקין 
	return (char)exit;//המרתו לתו

}
void search_person(const db_mgr* city)//מחפש אדם לפי ID ומדפיס פרטיו
{
	long long int local;
	do
	{
		printf("please enter valid id with 8 digits that you want to find\n");
		scanf("%lld", &local);
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
void search_parents(const db_mgr* city)//מחפש הורים של אדם לפי תעודת זהות ומדפיס פרטיהם
{
	long long int local;
	do
	{
		printf("please enter valid id with 8 digits that you want to find\n");
		scanf("%lld \n", &local);
		fseek(stdin, 0, SEEK_END);
	} while (local < 10000000 || local > 100000000);//בודק תקינות הקלט
	Person* ans = search_id(city, local);
	if (ans == NULL)
	{
		printf("sorry there is no existed people with that id \n");
		return;
	}
	(ans->FatherId == NULL) ? printf("no father \n") : printf("father id %lld \n", ans->FatherId);
	(ans->MotherId == NULL) ? printf("no mother \n") : printf("mother id %lld \n", ans->MotherId);

}
void delete_children(db_mgr* city, long long int Parent_id, long long int child)// מוחק ילד שזהותו נמחקה מהמאגר
{
	Person* parent = search_id(city, Parent_id);
	for (int i = 0; i < parent->NumOfChildern; i++)
	{
		if (parent->ChildrenPtr[i] == child)
		{
			parent->ChildrenPtr[i] = 0;
		}
	}
	long long int* newchildren = (long long int*)calloc(parent->NumOfChildern - 1, sizeof(long long int));//יוצר מערך ילדים חדש לאדם ללא הילד שנמחק
	if (newchildren == NULL)//בודק אם בוצע הקצאת מקום
	{
		printf("there is no memory to create children array");
		return;
	}
	int j = 0;
	for (int i = 0; i < parent->NumOfChildern; i++)
	{
		if (parent->ChildrenPtr[i] == 0)
		{
			continue;
		}
		newchildren[j] = parent->ChildrenPtr[i];
		j++;
	}
	free(parent->ChildrenPtr);
	parent->ChildrenPtr = newchildren;
	parent->NumOfChildern--;

}
void zero_parent(db_mgr* city, Person* parent)//מאפס את תעודת הזות של ההורים במידה ונמחק הורה מהמאגר
{
	Person* chilrentmp;
	for (int i = 0; i < parent->NumOfChildern; i++)
	{
		chilrentmp = search_id(city, parent->ChildrenPtr[i]);
		if (chilrentmp != NULL)
		{
			if (chilrentmp->FatherId == parent->id)
			{
				chilrentmp->FatherId = 0;
			}
			if (chilrentmp->MotherId == parent->id)
			{
				chilrentmp->MotherId = 0;
			}
		}
	}
}
void delete_person(db_mgr* city)//מוחק אדם לפי תעודת זהות מהמאגר
{
	long long int local;
	do
	{
		printf("please enter valid id with 8 digits that you want to delete\n");
		scanf("%lld", &local);
		fseek(stdin, 0, SEEK_END);
	} while (local < 10000000 || local > 100000000);//בדיקת תקינות הקלט
	Person* ans = search_id(city, local);
	if (ans == NULL)//בודק אם אדם שכזה קיים במאגר
	{
		printf("sorry there is no person like that\n");
		return;
	}
	Person* Partner = search_id(city, ans->PartnerId);
	if (ans->PartnerId != 0 && Partner != NULL)
	{
		Partner->PartnerId = 0;

	}
	if (ans->FatherId != 0)
	{
		Person* papa = search_id(city, ans->FatherId);
		if (papa != NULL)
		{
			delete_children(city, ans->FatherId, ans->id);

		}
		ans->FatherId = 0;
	}
	if (ans->MotherId != 0)
	{
		Person* moma = search_id(city, ans->MotherId);
		if (moma != NULL)
		{
			delete_children(city, ans->MotherId, ans->id);

		}
		ans->MotherId = 0;
	}
	zero_parent(city, ans);
	ans->NumOfChildern = 0;
	free(ans->ChildrenPtr);
	free(ans->name);
	free(ans->family);
	ans->id = 0;
	ans->DateOfbirth.day = 0, ans->DateOfbirth.month = 0, ans->DateOfbirth.year = 0;
	sortedPerson(city);
	city->Manage = removeRealloc(city);
	printf("the person id %lld has been deleted \n", local);
}
void get_gen(const db_mgr* city)//מחזיר כמה דורות יש לאדם לפי תעודת זהות
{
	int genertion = 0;
	int sumcildren = 1;
	long long int local;
	do
	{
		printf("please enter valid id with 8 digits that you want to check genertion\n");//קליטה של ת.ז
		scanf(" %lld", &local);
		fseek(stdin, 0, SEEK_END);
	} while (local < 10000000 || local > 100000000);
	Person* ans = search_id(city, local);
	if (ans == NULL)//בדיקה האם הקצאת המקום בוצעה כראוי
	{
		printf("sorry there is no person like that\n");
		return;
	}
	if (ans->NumOfChildern == 0)// במידה ואין ילדים יודפס 1
	{
		printf("the genertion is 1\n");
		return;
	}
	long long int* parents = (long long int*) malloc(sizeof(long long int));
	if (parents == NULL)//בדיקה האם הקצאת המקום בוצעה כראוי
	{
		printf("there is no place for array \n");
		return;
	}
	int sumparents = 1;
	*parents = local;
	sumcildren = ans->NumOfChildern;
	long long int* children = (long long int*)malloc(sizeof(long long int) * sumcildren);
	if (children == NULL)//בדיקה האם הקצאת המקום בוצעה כראוי
	{
		printf("there is no place for array \n");
		return;
	}
	while (sumcildren != 0)//רץ כל עוד מספר הילדים שווה ל0 ,ברגע שיהיה 0 ילדים אין דור המשך
	{
		//שימוש בשני מערכים דינאמים על מנת לשמור את ת.ז של הילדים וההורים. בכל פעם הילדים יהפכו להיות ההורים וכן הלאה
		sumcildren = 1;
		for (int i = 0; i < sumparents; i++)
		{
			if (search_id(city, parents[i]) != NULL)
			{
				sumcildren += search_id(city, parents[i])->NumOfChildern;
			}
		}
		sumcildren--;
		children = (long long int*)malloc(sizeof(long long int) * sumcildren);
		if (children == NULL)
		{
			printf("there is no place for array \n");
			return;
		}
		int countchild = 0;
		for (int i = 0; i < sumparents; i++)
		{
			Person* tmp = search_id(city, parents[i]);
			if (tmp != NULL)
			{
				for (int j = 0; j < tmp->NumOfChildern; j++)
				{

					children[countchild] = tmp->ChildrenPtr[j];
					countchild++;
				}
			}
		}
		free(parents);
		parents = children;
		sumparents = sumcildren;
		genertion++;
	}
	printf("the genertion is %d \n", genertion);
}
void printdb(const db_mgr* city)//הפונקציה מדפיסה את כל האנשים במאגר באמצעות פונקציה קודמת
{
	for (int i = 0; i < city->sizeManage; i++)
	{
		if (city->Manage[i].id == 0)
			continue;
		Print_Person(&city->Manage[i]);
	}
}
void search_by_name(const db_mgr* city)//הפונקציה מקבלת את המאגר , וקולטת שם מלא ומחפשת לפי השם במאגר את האדם ומדפיסה אותו במידה וקיים
{
	char name[250];
	char lastname[250];
	do
	{
		printf("please enter name\n");
		scanf(" %s", name);
		fseek(stdin, 0, SEEK_END);
	} while (name < 0);//בדיקת קלט
	do
	{
		printf("please enter last name\n");
		scanf(" %s", lastname);
		fseek(stdin, 0, SEEK_END);

	} while (lastname < 0);
	int checkTrue = 0;
	for (int i = 0; i < city->sizeManage; i++)//ריצה על המאגר
	{
		if (city->Manage[i].id == 0)
			continue;
		if (strcmp(name, city->Manage[i].name) == 0 && strcmp(city->Manage[i].family, lastname) == 0)//בדיקת המחרוזת של השם
		{
			Print_Person(&city->Manage[i]);
			checkTrue++;
		}
	}
	if (checkTrue == 0)// במידה והסתיים הלולאה אך לא נמצא תודפס הודעעה בהתאם
		printf("no matching person!\n");
}
void quit(db_mgr* city)//  פונקציה אשר משחררת את כל הזכרונות הדינאמיים במאגר
{
	for (int i = 0; i < city->sizeManage; i++)// רצה על האנשים במאגר ומשחררת את הנתונים הדינאמיים
	{
		if (city->Manage[i].id != 0)
		{
			free(city->Manage[i].name);
			free(city->Manage[i].family);
			free(city->Manage[i].ChildrenPtr);

		}
	}
	free(city->Manage);
	printf("done \n");
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

