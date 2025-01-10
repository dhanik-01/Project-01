#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct business
{
    char bname[20];
    char pnum[20];
    char cat[20];
    char address[1024];
    struct business* link;
};
typedef struct business bus;

bus* createnode()
{
    bus* x=(bus*)malloc(sizeof(struct business));
    if(x==NULL)
    {
        printf("Memory allocation unsuccessful\n");
        return NULL;
    }
    x->link=NULL;
    return x;
}

bus* getdatacsv(const char* filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("No file found\n");
        return NULL;
    }

    bus *head = NULL;
    bus *temp = NULL;
    bus *newnode;
    char line[1024];  
    
    while (fgets(line, sizeof(line), file))
    {
        newnode = createnode();
        if (newnode == NULL)
        {
            fclose(file);
            return NULL;
        }

        int num = 0;
        int result = sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", newnode->bname,newnode->pnum, newnode->cat, newnode->address);
        
        if (head == NULL)
        {
            head = newnode;
        }
        else
        {
            temp->link = newnode;
        }
        temp = newnode;
    }
    fclose(file);
    return head;
}

bus* addbusiness(bus* head)
{
    bus* temp,*prev;
    char name[20], adrs[100], ctg[10];
    char num[20];
    temp = createnode();

    printf("Enter business name: ");
    getchar();
    scanf("%[^\n]", name);

    printf("\nEnter phone number of the business: ");
    scanf("%s", num);

    printf("\nEnter the category of the business: ");
    scanf("%s", ctg);
    getchar();

    printf("\nEnter the address of the business: \n");
    getchar();
    fgets(adrs, sizeof(adrs), stdin);
    adrs[strcspn(adrs, "\n")] = '\0';

    strcpy(temp->bname, name);
    strcpy(temp->address, adrs);
    strcpy(temp->pnum, num);
    strcpy(temp->cat, ctg);
    
    if (head == NULL)
    {
        return temp;
    }
    temp->link = head;
    head=temp;
    return head;
}

void savedatacsv(const char* filename, bus *head)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Can not open the file\n");
        return;
    }
    bus *temp = head;
    while (temp != NULL)
    {
        fprintf(file, "%s,%s,%s,%s\n", temp->bname, temp->pnum, temp->cat, temp->address);
        temp = temp->link;
    }
    fclose(file);
}

bus* freenodes(bus *head)
{
    bus *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->link;
        free(temp);
    }
    return NULL;
}

void srcat(bus* head) 
{
    char category[20];
    int found = 0; 
    printf("\nEnter the category to search: ");
    scanf("%s", category);

    bus* temp = head;
    while (temp != NULL) 
    {
        if (strcmp(strupr(temp->cat), strupr(category)) == 0) 
        {
            printf("Business Name: %s\n", temp->bname);
            printf("Phone Number: %s\n", temp->pnum);
            printf("Address: %s\n\n", temp->address);
            found = 1;
        }
        temp = temp->link;
    }
    if (!found)
    {
        printf("No businesses found under category %s\n", category);
    }
}

void srname(bus* head) 
{
    char name[20];
    int found = 0;
    printf("\nEnter the business name to search: ");
    scanf("%s", name);

    bus* temp = head;
    while (temp != NULL) 
    {
        if (strcmp(strupr(temp->bname), strupr(name)) == 0) 
        {
            printf("Business Name: %s\n", temp->bname);
            printf("Phone Number: %s\n", temp->pnum);
            printf("Category: %s\n", temp->cat);
            printf("Address: %s\n\n", temp->address);
            found = 1;
        }
        temp = temp->link;
    }
    if (!found)
    {
        printf("No business found with the name %s\n", name);
    }
}

void revphlook(bus* head) 
{
    int found = 0;
    char num[20];
    printf("\nEnter the phone number to search: ");
    scanf("%s", num);
    bus* temp = head;
    while (temp != NULL) 
    {
        if (strcmp(temp->pnum, num) == 0) 
        {
            printf("Business Name: %s\n", temp->bname);
            printf("Category: %s\n", temp->cat);
            printf("Address: %s\n\n", temp->address);
            found = 1;
        }
        temp = temp->link;
    }
    if (!found)
    {
        printf("No business found with the phone number %s\n", num);
    }
}

void display(bus *head)
{
    if (head == NULL)
    {
        printf("No business to display\n");
        return;
    }
    printf("\n--Displaying All Businesses--\n");
    while (head != NULL)
    {
        printf("\n---------------------------------\n");
        printf("Name: %s\n", strupr(head->bname));
        printf("Phone Number: %s\n", head->pnum);
        printf("Category: %s\n", strupr(head->cat));
        printf("Address: %s\n", head->address);
        head = head->link;
    }
    printf("\n---------------------------------\n");
}

void main()
{
    bus* head = NULL;
    int ch;
    head = getdatacsv("business.csv");
    do
    {
        printf("\n--Business Directory--\n1. Add your new business\n2. Search by category\n3. Search by name\n4. Reverse phone lookup\n5. Display all business\n6. Exit\n Enter your choice\n");
        scanf("%d", &ch);
        switch (ch)
        {
            case 1: head = addbusiness(head);
                    savedatacsv("business.csv", head);
                    head = freenodes(head);
                    head = getdatacsv("business.csv");
                    break;
            case 2: srcat(head);
                    break;
            case 3: srname(head);
                    break;
            case 4: revphlook(head);
                    break;
            case 5: display(head);
                    break;
            case 6: printf("Exiting...");
                    exit(0);
        }
    } while (ch != 6);
}
