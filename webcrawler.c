#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
typedef struct Node
{
char url1[1000];
struct Node *next;
}node;

void addtohash(char*str,node*hash[1000])
{
	int i=0;
char check[]="<a";
	char check1[]="href=";
	
	while(str[i]!='\0')
	{
		char str1[1000]={0};
		int j=0,k=0,x=0;
		if(str[i]==check[0]&& str[i+1]==check[1]);
		{
	
			i++;
			while(str[i]!='>')
			{ int flag=0;
			if(str[i]==check1[0])
				{
					while(check1[j]!='\0')
						{
							if(str[i]!=check1[j])
								{
									flag=1;
									break;
								}
							i++;
							j++;
						}
					if(flag==0)
					{	
								int x=0;
							while(str[i]!='"')
								{
									str1[x]=str[i];
									i++;
									x++;
								}
						int length=strlen(str1);
						if(hash[length]==NULL)
						{
							node*temp=(node*)malloc(sizeof(node));
							strcpy(temp->url1,str1);
							hash[length]=temp;
							hash[length]->next=NULL;
						}
						else
						{
							node*ptr=hash[length];
							node*temp=(node*)malloc(sizeof(node));
							strcpy(temp->url1,str1);
							if (ptr->next==NULL)
							{
								if(strcmp(ptr->url1,str1)!=0)
								{
									ptr->next=temp;
									temp->next==NULL;
								}
							}
							else
							{
								int chk=0;
								while(ptr->next!=NULL)
								{
									if (strcmp(ptr->url1,str1)==0)
									{
										chk=1;
										break;
									}
									ptr=ptr->next;
								}
								if(strcmp(ptr->url1,str1)==0)
								{
									chk=1;
								}
								if(chk!=1)
								{
									ptr->next=temp;
									temp->next=NULL;
								}
							}
						}
	
	
					}
				}
			i++;
			}
		}
	i++;
	}
}

void getlinks(node* hash[1000])
{
	int static m=0;
	int j=0;
	for(j=0;j<1000;j++)
	{
		node*ptr=hash[j];
		while(ptr!=NULL)
		{
		char url[300]="wget -O temp";

		
		char txt[6]=".txt ";
		char buffer[7];
		sprintf(buffer,"%d",m);
		m++;
		strcat(url,buffer);
		strcat(url,txt);
		strcat(url,ptr->url1);
		system(url);
		if (ptr->next==NULL)
		{
			break;
		}
		ptr=ptr->next;

	    }
	}
}

int main()
{
	int i;
node*hash[1000];
char url[300];
fgets(url,300,stdin);
char c[500] = {0};
strcat(c,"wget -O ");
strcat(c,"temp.txt ");
strcat(c,url);

system(c);

FILE *fp;
fp=fopen("temp.txt","r");
fseek(fp,0,SEEK_END);
int fsize=ftell(fp);
fseek(fp,0,SEEK_SET);
char *str=(char*)malloc(fsize+1);

fread(str,fsize,1,fp);
str[fsize]='\0';

fclose(fp);

for (i = 0; i < 1000; i++)
	hash[i] = NULL;

addtohash(str,hash);


	i=0;
	while(i!=1000)
	{
		node*ptr=hash[i];
		if(ptr!=NULL)
		{
			while(ptr!=NULL)
			{
				printf("%s\n",ptr->url1);
				ptr=ptr->next;
			}
		}
		i++;
	}
	getlinks(hash);
}