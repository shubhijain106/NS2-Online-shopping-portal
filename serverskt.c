/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
   
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
typedef struct
{
	APP app[10];
	APP app1[20];
}APPLICATION;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    APPLICATION ap;
    APPLICATION ap1;
    int client;
    int login=0;
    APP a[10];
    APP c[10];
    APP e[10];
    APP f[10];
    APP g[10];
    APP b;
    APP z;
    
     FILE *fp1,*fp2,*fp3,*fp4,*fp5,*fp6;
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n,i,flag=0,j=0,k=0,l=0,m=0,t=0,u=0;
	ap.app[0].len=0;
    fp1=fopen("user_account","r");
	i=0;
	
	while(!feof(fp1))
	{
		fscanf(fp1,"%s%s",a[i].l.uname,a[i].l.pwd);
		i++;
	}	
	a[0].len=i-1;
	//printf("\n%d\n",a[0].len);

	//readbook(&a[0]);
	//printf("\n%s\n",a[0].book.bname);
	//for(i=0;i<s.f[0].len-1;i++)
	//	printf("%d %s %s %d\n",s.f[i].fno,s.f[i].fcity,s.f[i].tcity,s.f[i].aval);
      fp2=fopen("dress","r");
	while(!feof(fp2))
	{
		fscanf(fp2,"%s%s%s%s%f",c[j].d.color,c[j].d.type,c[j].d.size,c[j].d.material,&c[j].d.cost);
		printf("%s\t%s\t%s\t%s \t%f\n",c[j].d.color,c[j].d.type,c[j].d.size,c[j].d.material,c[j].d.cost);
		j++;
	}
	c[0].d.len=j-1;	
         //printf("%d",c[0].d.len);
	j=0;
	 fp3=fopen("watch","r");
         k=0;
	while(!feof(fp3))
	{
		fscanf(fp3,"%s%s%s%f",e[k].w.color,e[k].w.type,e[k].w.make,&e[k].w.cost);
		printf("%s\t%s\t%s\t%f\n",e[k].w.color,e[k].w.type,e[k].w.make,e[k].w.cost);
		k++;
	}
        
	e[0].w.len=k-1;
       k=0;
	fp4=fopen("offers","r");
       while(!feof(fp4))
	{
		fscanf(fp4,"%s%d",f[l].o.type,&f[l].o.discount);
		//printf("%s\t%s\t%s\t%f\n",e[k].w.color,e[k].w.type,e[k].w.make,e[k].w.cost);
		l++;
	}
	f[0].o.len=l-1;
	l=0;

       fp5=fopen("offers1","r");
       while(!feof(fp5))
	{
		fscanf(fp5,"%s%d",g[m].o1.type,&g[m].o1.discount);
		//printf("%s\t%s\t%s\t%f\n",e[k].w.color,e[k].w.type,e[k].w.make,e[k].w.cost);
		m++;
	}
	g[0].o1.len=m-1;
	m=0;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
while(1)
{
     listen(sockfd,15);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
     n = read(newsockfd,&b,sizeof(APP));
     if (n < 0) error("ERROR reading from socket");
     
    
     
   //printf("\n%d\n",b.code);
     if(b.code==-33)
     	{
     		for(i=0;i<a[0].len;i++)
     		{
     			if(strcmp(b.l.uname,a[i].l.uname)==0 && strcmp(b.l.pwd,a[i].l.pwd)==0)
     			{
     				printf("\nlogged in\n");
     				b.code=1;
     				login=1;
     				client=i;
     				n = write(newsockfd,&b,sizeof(APP));
     				break;
     			} 
     		}
     	}
     	
     	while(login)
     	{
     		    n = read(newsockfd,&b,sizeof(APP));
		    printf("\n---%s---\n",b.d.type);
		    
     		    if(b.code==0)
     		    {
     		    	login=0;
     		    	printf("\nUser successfully logged out\n");
     		    	break;	
     		    }
     		    if(b.code==1)
     		    {
     		    	
     		    	for(i=0;i<c[0].d.len;i++)
				{
     		    		ap.app[i]=c[i];
				}
     		    	//printf("\n%d\n",c[0].d.len);
     		    	//printf("\n%s\n",ap.app[0].d.color);
     		    	n = write(newsockfd,&ap,sizeof(APPLICATION));
     		    }
		     if(b.code==2)
     		    {
     		    	
     		    	for(i=0;i<e[0].w.len;i++)
				{
     		    		ap1.app1[i]=e[i];
				}
     		    	//printf("\n%d\n",e[0].w.len);
     		    	//printf("\n%s\n",ap1.app1[0].w.color);
     		    	n = write(newsockfd,&ap1,sizeof(APPLICATION));
     		    }
		     if(b.code==3)
                       {
			printf("\nsearching\n");
     		    		for(i=0;i<c[0].d.len;i++)
     				{
     					if(strcmp(b.d.type,c[i].d.type)==0)
     					{
						strcpy(b.msg,"Success");
     						printf("\nsearching success\n");
     						b.d.cost=c[i].d.cost;
     						n = write(newsockfd,&b,sizeof(APP));
						break;
					}
			         }
			}

			if(b.code==4)
                       {
			printf("\nsearching\n");
     		    		for(i=0;i<e[0].w.len;i++)
     				{
     					if(strcmp(b.w.type,e[i].w.type)==0)
     					{
						strcpy(b.msg,"Success");
     						printf("\nsearching successs\n");
     						b.w.cost=e[i].w.cost;
     						n = write(newsockfd,&b,sizeof(APP));
						break;
			         	}
			         }
		      }
		if(b.code==5)
                       {
     		    		for(i=0;i<c[0].d.len;i++)
     				{
     					if(strcmp(b.d.type,c[i].d.type)==0)
     					{
					   	strcpy(ap.app[0].msg,"Success");
			   			ap.app[j]=c[i];
						ap1.app1[t]=c[i];
						ap1.app1[t].code=11;
						ap.app[0].len+=1;
     						n = write(newsockfd,&ap,sizeof(APPLICATION));
						j++;
						t++;
						break;
					}
			         }
		      }
                      
			if(b.code==6)
                           {
                         	for(i=0;i<e[0].w.len;i++)
     				{
     					if(strcmp(b.w.type,e[i].w.type)==0)
     					{
			   			ap.app[k]=e[i];
						ap1.app1[t]=e[i];
						ap1.app1[t].code=12;
						ap.app[0].len+=1;
     						n = write(newsockfd,&ap,sizeof(APPLICATION));
						t++;
						k++;
						break;
					}
					

			         }
		      }	
			if(b.code==7)
                           {
                         	for(i=0;i<f[0].o.len;i++)
     				{
     					if(strcmp(b.d.type,f[i].o.type)==0)
     					{
			   			ap.app[l]=f[i];
						ap.app[0].len+=1;
						ap.app[l].o.pr1=c[i].d.cost;
						ap.app[l].o.pr2=c[i].d.cost-((c[i].d.cost*f[i].o.discount)/100);
     						n = write(newsockfd,&ap,sizeof(APPLICATION));
						break;
					}
					

			         }
		      }									
     		   if(b.code==8)
                           {
                         	for(i=0;i<g[0].o1.len;i++)
     				{
     					if(strcmp(b.w.type,g[i].o1.type)==0)
     					{
			   			ap.app[m]=g[i];
						ap.app[0].len+=1;
						ap.app[l].o1.pr1=e[i].w.cost;
						ap.app[l].o1.pr2=e[i].w.cost-((e[i].w.cost*g[i].o1.discount)/100);
     						n = write(newsockfd,&ap,sizeof(APPLICATION));
						break;
					}
					

			         }
		      }	
		if(b.code==9)
		{
			ap1.app1[0].len=t;
			n = write(newsockfd,&ap1,sizeof(APPLICATION));

		}
		if(b.code==10)
		{
		ap1.app1[0].len=t;
		if(ap1.app1[0].len>0)
		{
		ap1.app1[0].code1=101;
		for(i=0;i<ap1.app1[0].len;i++)
		{
			if(strcmp(b.d.type,ap1.app1[i].d.type)==0)
				{
				  if(i==(ap1.app1[0].len)-1)
				    {
					t=t-1;
					n = write(newsockfd,&ap1,sizeof(APPLICATION));
				    }
				  else if(i==0)
				{
				  j=t;
				  for(u=0;u<ap1.app1[0].len;u++)
				    {
					 if(u!=(ap1.app1[0].len)-1)
					{
					  t=u-1;
					  printf("---%d---\n",t);
					  ap1.app1[u]=ap1.app1[u+1];
					  ap1.app1[0].len=j;
					}
				     	else
					 {
					   break;
					 }
                                     
				     }
				 } 
				  }
		}
		}				
		else if(ap1.app1[0].len==0)
		{
			ap1.app1[0].code1=100;
			n = write(newsockfd,&ap1,sizeof(APPLICATION));
		}  
		}  
     	}
     	
     	close(newsockfd);
   }
     close(sockfd);
     return 0; 
}
