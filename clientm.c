#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "structure.h"

typedef struct
{
	APP app[10];
	APP app1[20];
}APPLICATION;



void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    APPLICATION ap;
    APPLICATION ap1;
    APP c;
    APP c1;
    APP c2[10];
    int chance=3; 
   int sockfd, portno, n,i,n1,n2;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    FILE *fp;
    fp=fopen("cart","w");
	
    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//printf("%d",sockfd);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
        
        
        while(chance>0)
        {
        	   	printf("Enter the USERNAME : ");
    		   	scanf("%s",c.l.uname);
    			
    		   	printf("Enter the PASSWORD : ");
    			scanf("%s",c.l.pwd);
    			
    			c.code=-33;
    			n = write(sockfd,&c,sizeof(APP));
    		        n = read(sockfd,&c1,sizeof(APP));
    			 if(c1.code==1)
    			 {
    			 printf("\n%s successfully logged in\n",c.l.uname);
    			 	break;
    			 }
    			 chance--;
    			 if(chance==0)
    			 {
    			 	printf("\nexceeds login chances\n");
    			 	return 1;
    			 }
    			
        }
        
        while(1){
printf("\n1.List Dresses.\n2.List Watches.\n3.Cost for a particular type in Dresses.\n4.Cost for a particular type in Watches.\n5.Order for Dresses.\n6.Order for watches.\n7.Offers available for dresses.\n8.Offers available for watches.\n9.Display Cart\n10.Remove dress from cart\n11.Remove watch from cart\n12.LOGOUT\n");   
     printf("\nPlease enter the selection:\n ");
     scanf("%d",&c.code);
   if(c.code==12)
   {
   	printf("\nUser is logging out........\n");
   	
   	c.code=0;
   	n=write(sockfd,&c,sizeof(APP));
   	close(sockfd);
   	break;
   	//return 1;
   }
   
   if(c.code==1)
   {
   	 n = write(sockfd,&c,sizeof(APP));
   	 n = read(sockfd,&ap,sizeof(APPLICATION));
   	printf("\nCOLOR\tTYPE\tSIZE\tMATERIAL\tCOST\n");
	//printf("%d\n",ap.app[0].d.len);
   	for(i=0;i<ap.app[0].d.len;i++)
   	{
   		printf("%s\t%s\t%s\t%s\tRs.%f\n",ap.app[i].d.color,ap.app[i].d.type,ap.app[i].d.size,ap.app[i].d.material,ap.app[i].d.cost);
   	}
    }
   if(c.code==2)
     {
   	 n = write(sockfd,&c,sizeof(APP));
   	 n = read(sockfd,&ap1,sizeof(APPLICATION));
   	printf("\nCOLOR\tTYPE\tMAKE\tCOST\n");
	printf("%d\n",ap1.app1[0].w.len);
   	for(i=0;i<ap1.app1[0].w.len;i++)
   	{
   		printf("%s\t%s\t%s\tRs.%f\n",ap1.app1[i].w.color,ap1.app1[i].w.type,ap1.app1[i].w.make,ap1.app1[i].w.cost);
   	}
   }
   
    if(c.code==3)
   {
   	 printf("\nEnter the type of the dress you want to search for to find its cost\n");
   	 scanf("%s",c.d.type);
   	 n = write(sockfd,&c,sizeof(APP));
   	 n = read(sockfd,&c,sizeof(APP));
	 printf("\nThe cost of the type of the dress which you have searced for is %f\n",c.d.cost);
	
   }
	  if(c.code==4)
            {
   	 printf("\nEnter the type of the watch you want to search for to find its cost\n");
   	 scanf("%s",c.w.type);     
   	 n = write(sockfd,&c,sizeof(APP));
   	 n = read(sockfd,&c,sizeof(APP));
	 printf("\nThe cost of the type of the watch which you have searced for is %f\n",c.w.cost);
	 }
           if(c.code==5)
            {
   	 printf("\nEnter the type of the dress you want to order\n");
   	 scanf("%s",c.d.type);     
   	 n = write(sockfd,&c,sizeof(APP));
   	 n = read(sockfd,&ap,sizeof(APPLICATION));
	//printf("\n%d\n",ap.app[0].len); 
	 printf("\nThe details of the ordered items are\n");
	
	 for(i=0;i<ap.app[0].len;i++)
   	{
   		printf("\n%s\t%s\t%s\t%s\t%f\n",ap.app[i].d.color,ap.app[i].d.type,ap.app[i].d.size,ap.app[i].d.material,ap.app[i].d.cost);
   	}
		while(1)
		{
		printf("\nWhether you want to continue order the items\n");
		printf("\n1.Yes and 2.NO\n");
		scanf("%d",&n1);
		if(n1==1)
		{
		 printf("\nEnter the type of the dress you want to order\n");
   	         scanf("%s",c.d.type);     
   	     	n = write(sockfd,&c,sizeof(APP));
   	 	n = read(sockfd,&ap,sizeof(APPLICATION));
	 	printf("\nThe details of the ordered items are\n"); 
	 	for(i=0;i<ap.app[0].len;i++)
   		{
   		printf("%s\t%s\t%s\t%s\t%f\n",ap.app[i].d.color,ap.app[i].d.type,ap.app[i].d.size,ap.app[i].d.material,ap.app[i].d.cost);
   		}
		}

		else
		{
			printf("\nThe user doesn't want to order more items\n");
			break;
		} 
		}
         }
	   if(c.code==6)
            {
   	 printf("\nEnter the type of the watch you want to order\n");
   	 scanf("%s",c.w.type);     
   	 n = write(sockfd,&c,sizeof(APP));
   	 n = read(sockfd,&ap,sizeof(APPLICATION));
	 printf("\nThe details of the ordered items are\n"); 
	 for(i=0;i<ap.app[0].len;i++)
   	{
   		printf("%s\t%s\t%s\t%f\n",ap.app[i].w.color,ap.app[i].w.type,ap.app[i].w.make,ap.app[i].w.cost);
   	}
		while(1)
		{
		printf("\nWhether you want to continue order the items\n");
		printf("\n1.Yes and 2.NO\n");
		scanf("%d",&n1);
		if(n1==1)
		{
		 printf("\nEnter the type of the watch you want to order\n");
   	         scanf("%s",c.w.type);     
   	     	n = write(sockfd,&c,sizeof(APP));
   	 	n = read(sockfd,&ap,sizeof(APPLICATION));
	 	printf("\nThe details of the ordered items are\n"); 
		//printf("%d",ap.app[0].len);
	 	for(i=0;i<ap.app[0].len;i++)
   		{
   		printf("%s\t%s\t%s\t%f\n",ap.app[i].w.color,ap.app[i].w.type,ap.app[i].w.make,ap.app[i].w.cost);
		}
                }
		else
		{
			printf("\nThe user doesn't want to order more items\n");
			break;
		} 
		}
         }
	  if(c.code==7)
            {
   	 printf("\nEnter the type of the dress for which you want to see the offer\n");
   	 scanf("%s",c.d.type);     
   	 n = write(sockfd,&c,sizeof(APP));
   	 n = read(sockfd,&ap,sizeof(APPLICATION));
	 printf("\nThe detail for the offer is\n");
	 printf("\nTYPE\tOFFER\n"); 
	 for(i=0;i<ap.app[0].len;i++)
   	{
   		printf("\n%s\t%dpercent\n",ap.app[i].o.type,ap.app[i].o.discount);
		printf("\nActual price of the dress which u have chosen is:Rs.%f\n",ap.app[i].o.pr1);
		printf("\nPrice of the dress after the offer will be:Rs.%f\n",ap.app[i].o.pr2);
   	}
	}

	 if(c.code==8)
            {
   	 printf("\nEnter the type of the watch for which you want to see the offer\n");
   	 scanf("%s",c.w.type);     
   	 n = write(sockfd,&c,sizeof(APP));
   	 n = read(sockfd,&ap,sizeof(APPLICATION));
	 printf("\nThe detail for the offer is\n");
	 printf("\nTYPE\tOFFER\n"); 
	 for(i=0;i<ap.app[0].len;i++)
   	{
   		printf("\n%s\t%dpercent\n",ap.app[i].o1.type,ap.app[i].o1.discount);
		printf("\nActual price of the watch which u have chosen is:Rs.%f\n",ap.app[i].o1.pr1);
		printf("\nPrice of the watch after the offer will be:Rs.%f\n",ap.app[i].o1.pr2);
   	}
	}
	if(c.code==9)
	{
	n=write(sockfd,&c,sizeof(APP));
	n = read(sockfd,&ap1,sizeof(APPLICATION));
	if(ap1.app1[0].len>0)
	{
         for(i=0;i<ap1.app1[0].len;i++)
   	{
		if(ap1.app1[i].code==11)
		{
printf("COLOR:%s\tTYPE:%s\tSIZE:%s\tMATERIAL:%s\tCOST:%f\n",ap1.app1[i].d.color,ap1.app1[i].d.type,ap1.app1[i].d.size,ap1.app1[i].d.material,ap1.app1[i].d.cost);
   		}
		else if(ap1.app1[i].code==12)
		{
		  printf("COLOR:%s\tTYPE:%s\tMAKE:%s\tCOST:%f\n",ap1.app1[i].w.color,ap1.app1[i].w.type,ap1.app1[i].w.make,ap1.app1[i].w.cost);
		}
   	}
	}
	else if(ap1.app1[0].len==0)
	{
	printf("\nThere are no more items in the cart\n");
	}

	}
	if(c.code==10)
	{
	printf("Enter the type of the dress you want to remove from the cart\n");
	scanf("%s",c.d.type);
	n=write(sockfd,&c,sizeof(APP));
	n = read(sockfd,&ap1,sizeof(APPLICATION));
	if(ap1.app1[0].code1==100)
	{
		printf("\nThe cart is empty\n");
	}
	else if(ap1.app1[0].code1==101)
	{
		continue;
	}
	}
	if(c.code>12)
	{
	printf("Please enter a valid input\n");
	}
   }

   
    if (n < 0) 
         error("\nERROR writing to socket\n");
    bzero(buffer,256);

    n = read(sockfd,&c,sizeof(APP));
    if (n < 0) 
         error("\nERROR reading from socket\n");
	
    close(sockfd);
    
    return 0;

}
