#include "stdio.h"
#include "conio.h"
#include "process.h"
#include "string.h"
#include "stdlib.h"
#define TRUE 1
void AddStudent();
void DeleteStudent();
void ViewStudents();
void SaveStudents();
void LoadStudents();
void DeleteAll();
struct SStudent
{
	int m_ID;
	char m_Name[40];
	float m_Height;
};
struct SStudent *gStudents = NULL;
int gCount = 0;



void main()
{
while(TRUE)
{
	printf("\n'a' add new student\n'd' deleteexisting student\n'v' list all students");
	printf("\n'w' save to file \n'l' load fromfile \n'q' exit\n");
	switch(getch())
	{
		case 'a': AddStudent(); break;
		case 'd': DeleteStudent(); break;
		case 'v': ViewStudents(); break;
		case 'w': SaveStudents(); break;
		case 'l': LoadStudents(); break;
		case 'q': DeleteAll(); exit(0); break;
		default:
		puts("\nEnter only selection listed.");
	}
	puts("\nPress any key to continue.");
	getch();
	system("cls");
	}
}


void AddStudent()
{
		char tempText[40];
		gStudents = (struct SStudent*)realloc(gStudents, (gCount+1) * sizeof(struct SStudent));
		if(gStudents==NULL)
			{
				printf("\nfailed to allocate more memore");
				return;
			}
			printf("\nRecord %d.\nEnter ID: ", gCount+1);
			gets(tempText);
			gStudents[gCount].m_ID = atoi(tempText);
			printf("Enter name: ");
			gets(gStudents[gCount].m_Name);
			printf("Enter height: ");
			gets(tempText);
			gStudents[gCount].m_Height = atof(tempText);
			gCount++;
}



void DeleteStudent()
{
	char tempText[40];
	int i, ID;
	printf("\nEnter Student ID to be Deleted:");
	gets(tempText);
	ID = atoi(tempText);
	for(i=0;i<gCount;i++)
	{
		if(gStudents[i].m_ID==ID)
	{
	memcpy(&gStudents[i], &gStudents[i+1],(gCount-(i+1))*sizeof(struct SStudent));
	gCount--;
	gStudents = (struct SStudent*) realloc(gStudents, gCount*sizeof(struct SStudent));
	return;
	}
	}
	printf("\nCannot find Student ID.");
}


void ViewStudents()
{
	int j;
	if(gCount<1)printf("\nEmpty list.\n");
	for(j=0;j<gCount;j++)
		{
			printf("\nRecord number %d\n", j+1);
			printf(" ID: %d\n", gStudents[j].m_ID);
			printf(" Name: %s\n", gStudents[j].m_Name);
			printf(" Height: %4.2f\n", gStudents[j].m_Height);
		}
}



void DeleteAll()
{
	if(gStudents)free(gStudents);
	gStudents = NULL;
}



void SaveStudents()
{
	FILE *pFile;
	if(gCount<1)
	{
		printf("\nEmpty list.\n");
		return;
	}
	if((pFile = fopen("agents.rec", "wb"))==NULL)
	{
		printf("\nCannot open file.\n");return;
	}
	if(fwrite(gStudents, sizeof(struct SStudent),gCount, pFile)!=gCount)
	{
		printf("\nCannot write to file.\n");
		return;
	}
	fclose(pFile);
	printf("\nFile of %d records written.", gCount);
}

void LoadStudents()
{
	long file_size;
	FILE *pFile;
	DeleteAll();
	if((pFile = fopen("agents.rec", "rb"))==NULL)
	{
	printf("\nCannot open file.\n");
	return;
	}
	fseek(pFile, 0, SEEK_END);
	file_size = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	if((gStudents = (struct SStudent*)malloc(file_size))==NULL)
	{
		printf("\nCannot allocate memory.\n");
		return;
	}
	gCount = file_size / sizeof(struct SStudent);
	if(fread(gStudents, sizeof(struct SStudent), gCount, pFile) != gCount)
	{
	printf("\nCannot read from file.\n");
	return;
	}
	fclose(pFile);
	printf("\nFile read. Total records : %d.", gCount);
}