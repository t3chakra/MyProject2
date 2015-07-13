#include "/home/t3chakra/MyProject/librery/SAT.h"
#include <unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#define INF 1000

int **gr;
int **grk;
int thcount;
SAT_Manager mgr;
int init(int v);
void graph(int x,int y);
int cl_one(int n,int k);
int cl_two(int n,int k);
int cl_three(int n,int k);
int cl_four(int n,int k);
int make_clause(int c[],int l);
int vc(int v);
int apvc1(int v);
int revc1(int v);
int apvc2(int v);
int revc2(int v);
double standard_deviation(double data[], int n);
double average(double data[], int n);

double t1,t2,t3,t4,t5;

int compare (const void * a, const void * b);
char** split(char* str_edge, const char delimeter);
void *cnf(void *v);
void *apv1(void *v3);
void *re1(void *v4);
void *apv2(void *v5);
void *re2(void *v6);
int *node,*res1,*res2,*res3,*res4;
pthread_t tid1,tid2,tid3,tid4,tid5;
clockid_t cid1,cid2,cid3,cid4,cid5;
struct timespec ts1,ts2,ts3,ts4,ts5;

int main()
{
  int i,c,v,flag,v1,v2,v3,v4,v5,v6,graphcount=0,r,flag2,arr,d,s;
	char** tokens;
	char* token; 
	char** edge;
	char buffer[2500];	
        double at1[10],at2[10],at3[10],at4[10],at5[10];
	double st1[10],st2[10],st3[10],st4[10],st5[10];
	arr=0;

	while(fgets(buffer,sizeof buffer,stdin)!=NULL)
	
	{	flag=0;
		flag2=0;
		

		if(feof(stdin))		
			break;
		switch(buffer[0])
		{
			case 'V':
				if(graphcount>1)
				{   
				    for(i=0;i<=graphcount;i++)
				    {
                                          free(gr[i]);
					  free(grk[i]);
                                    }
				    free(gr);
                                    free(grk);
                                 }
				tokens=split(buffer,' ');
				v3=v4=v5=v6=v=atoi(*(tokens+1));
				if(v<0){fprintf(stderr,"Error: Number of total Vertices can not be negative\n");fflush(stderr);graphcount=0;}
				else if(v==0){fprintf(stderr,"Error: There will be no graph with 0 vertices\n");fflush(stderr);graphcount=0;}
				else
				{	graphcount=init(v);}
				free(tokens);				
				continue;
			case 'E':
				v1=v2=0;
                                if(buffer[3]=='}'){flag=1;}			
				else{tokens = split(buffer, ' ');
				if(tokens){					
					token=*(tokens+1);
					
					for(i=0;i<strlen(token);i++)
					{
						if(token[i]=='-')
						{
						  fprintf(stderr,"Error: Negetive vertex is not possible for edge\n");
					          fflush(stderr);
							flag=1;free(tokens);free(token);
							break;
						}
						if(token[i]=='{'||token[i]=='<')
						{
							token[i]='0';
						}

					}
				        if(flag!=1)
					{
						token[i-2]='\0';
						tokens=split(token,'>');
							
						if(tokens)
						{
        						for (i = 0; *(tokens + i); i++)
        						{
            							token=*(tokens + i);
								if(token[0]==',')token[0]='0';
            							edge=split(token,',');
								if(edge)							
								{
									v1=atoi(*(edge+0));
									v2=atoi(*(edge+1));
								
									if(v1>(v-1)||v2>(v-1))
									{
										fprintf(stderr,"Error: The vertex you have given for edge does not exist\n");
										fflush(stderr);
			          						flag2=1;
										break;
									}
									else
										graph(v1,v2);
							 	}
								
								free(token);
								free(edge);
							}

						}
        					free(tokens);
						
					}
				      
  				}}

				if(flag2!=1 && flag!=1)
				  { int counter;
				    	double time1[10],time2[10],time3[10],time4[10],time5[10];
					
					for(counter=0;counter<10;counter++)
					{
                                    	
/***************************************************Initializing Global array******************************/
	                                        node=(int*)malloc(v*sizeof(int));//cnf-sat
	                                  	for(i=0;i<v;i++)node[i]=INF;
						res1=(int*)malloc(v*sizeof(int));//approx-vc1
	                                  	for(i=0;i<v;i++)res1[i]=INF;
					  	res2=(int*)malloc(v*sizeof(int));//refine 1
	                                  	for(i=0;i<v;i++)res2[i]=INF;
					  	res3=(int*)malloc(v*sizeof(int));//approx vc 2
	                                  	for(i=0;i<v;i++)res3[i]=INF;
					  	res4=(int*)malloc(v*sizeof(int));//refine 2
	                                  	for(i=0;i<v;i++)res4[i]=INF;
/************************************************create and join threads************************************/				 
					
						pthread_create(&tid1, NULL,cnf, &v);
						s=pthread_getcpuclockid(tid1, &cid1);
						if (s != 0){printf("Error creating cid1");fflush(stdout);}
	                                        pthread_create(&tid2, NULL,apv1, &v3);
						s=pthread_getcpuclockid(tid2, &cid2);
						if (s != 0){printf("Error creating cid2");fflush(stdout);}
	           				pthread_create(&tid3, NULL,re1, &v4);
						s=pthread_getcpuclockid(tid3, &cid3);
						if (s != 0){printf("Error creating cid3");fflush(stdout);}
						pthread_create(&tid4, NULL,apv2, &v5);
						s=pthread_getcpuclockid(tid4, &cid4);
						if (s != 0){printf("Error creating cid4");fflush(stdout);}		           			
						pthread_create(&tid5, NULL,re2, &v6);
						s=pthread_getcpuclockid(tid5, &cid5);
					        if (s != 0){printf("Error creating cid5");fflush(stdout);}
                                        
/*********************************getting time *****************************************/
				   	
                                        	sleep(2);
						pthread_join(tid1,NULL);				  	
						pthread_join(tid2,NULL);
				 		pthread_join(tid3,NULL);
				  		pthread_join(tid4,NULL);
				  		pthread_join(tid5,NULL);
/********************************************Printing result**************************************************/				  
						free(node);
						free(res1);
						free(res2);
				  		free(res3);
                                        	free(res4);
                                        	time1[counter]=t1;
						time2[counter]=t2;
						time3[counter]=t3;
						time4[counter]=t4;
						time5[counter]=t5;
                                        }
					/**********finding average for 10 runs****/		
           				at1[arr]=average(time1,10);
           			        at2[arr]=average(time2,10);
           				at3[arr]=average(time3,10);
           				at4[arr]=average(time4,10);
           				at5[arr]=average(time5,10);
					arr++;	
					fprintf(stdout,"%d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",v,average(at1,arr),average(at2,arr),average(at3,arr),average(at4,arr),average(at5,arr),standard_deviation(at1,arr),standard_deviation(at2,arr),standard_deviation(at3,arr),standard_deviation(at4,arr),standard_deviation(at5,arr));
					fflush(stdout);
					
					
				}						
				continue;			
			


		}
		

         }				
		
	
return 0;
}


double average(double data[], int n)
{
    double mean=0.0, sum_deviation=0.0;
    int i;
    for(i=0; i<n;++i)
    {
        mean+=data[i];
    }
    mean=mean/n;
    return mean;           
}
/************************************I use standard davition function from thid source http://www.programiz.com/c-programming/examples/standard-deviation****************************/
double standard_deviation(double data[], int n)
{
    double mean=0.0, sum_deviation=0.0;
    int i;
    for(i=0; i<n;++i)
    {
        mean+=data[i];
    }
    mean=mean/n;
    for(i=0; i<n;++i)
    sum_deviation+=(data[i]-mean)*(data[i]-mean);
    return sqrt(sum_deviation/n);           
}


/*Call functions from threded function*/
void *cnf(void *v)
{
	int r,n;
	int *v1 = (int *)v;
	n=*v1;	
	r=vc(n);
	
	clock_gettime(cid1, &ts1);
	t1 = ts1.tv_sec +ts1.tv_nsec/ 1000000000.0;
	
        pthread_exit (NULL);
	//return NULL;
	
}
void *apv1(void *v3)
{
  
  int r,n;
  int *v1=(int *)v3;
  n=*v1;
  r=apvc1(n);
	clock_gettime(cid2, &ts2);
	t2 = ts2.tv_sec +ts2.tv_nsec/ 1000000000.0;
        pthread_exit (NULL);
  //return NULL;
}
void *re1(void *v4)
{
  int r,n;
  int *v1=(int *)v4;
  n=*v1;
  r=revc1(n);
	clock_gettime(cid3, &ts3);
	t3 = ts3.tv_sec +ts3.tv_nsec/ 1000000000.0;
  pthread_exit (NULL);
  //return NULL;  
}


void *apv2(void *v5)
{
  int r,n;
  int *v1 = (int *)v5;
   n=*v1;
   r=apvc2(n);
   clock_gettime(cid4, &ts4);
	t4 = ts4.tv_sec +ts4.tv_nsec/ 1000000000.0;
  pthread_exit (NULL);
  // return NULL;
}
void *re2(void *v6)
{
  int r,n; 
  int *v1 = (int *)v6;
  n=*v1;
  r=revc2(n);
	clock_gettime(cid5, &ts5);
	t5 = ts5.tv_sec +ts5.tv_nsec/ 1000000000.0;
  pthread_exit (NULL);
  //return NULL;
}




/*Forming graph with edge*/
void graph(int x,int y)
{
	gr[x+1][y+1]=gr[y+1][x+1]=1;

}
/*Forming initial empty adjacency matrix*/
int init(int v)
{	
	int i,j,val;
	val=1;
	// first allocate memory for pointer to each row
	gr = (int**) malloc((v+1) * sizeof(int*));
	grk = (int**) malloc((v+1) * sizeof(int*));
        
	// then allocate memory for each row
	for(i = 0; i <= v; i++)
    	{	gr[i] = (int*) malloc((v+1) * sizeof(int));	  
		grk[i] = (int*) malloc((v+1) * sizeof(int));	  
	}	 
    	for(i=0;i<= v;i++)
    	{	
		for(j=0;j<= v;j++)
     		{	gr[i][j] = 0;
			grk[i][j]=0;
   		}
        }	
	for(j=1;j<= v;j++)
    	{
		for(i=1;i<= v;i++)
     		{	grk[i][j] = val;
   			val++;
		}
	}
	
	return v;
}
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}
int apvc1(int v)
{
  int **temp,i,j,ind,maxi,maxc,count,edge;
  ind=0;
  edge=1;
/********************copying value temporary array****************************/
  temp=(int**)malloc(v*sizeof(int*));
  for(i=0;i<v;i++)temp[i]=(int*)malloc(v*sizeof(int));
  for(i=0;i<v;i++)
    {
      for(j=0;j<v;j++)
	{
	  temp[i][j]=gr[i+1][j+1];
      
	}
    }
/********************************Loop unitl no edge********************************/
  while(edge==1) 
    {
      edge=maxi=maxc=0;
      for(i=0;i<v;i++)
	{count=0;
	  for(j=0;j<v;j++)
	    {
	      if(temp[i][j]==1)
		{
                  edge=1;
		  count++;
		}
	     }
	   if(maxc<count){maxc=count;maxi=i;}
	}
      if(edge==1){res1[ind]=maxi;
	           ind++;}
        for(i=0;i<v;i++){temp[maxi][i]=temp[i][maxi]=0;}
    }
    for(i=0;i<v;i++)free(temp[i]);free(temp);
  return 1;
}
/**********************************refine 1**********************************************/
int revc1(int v)
{
  int **temp,*temp2,i,j,ind,maxi,maxc,count,edge,a,b,k,inv,inv2;
  ind=0;
  edge=1;
/********************copying value temporary array****************************/
  temp=(int**)malloc(v*sizeof(int*));
  for(i=0;i<v;i++)temp[i]=(int*)malloc(v*sizeof(int));
  for(i=0;i<v;i++)
    {
      for(j=0;j<v;j++)
	{
	  temp[i][j]=gr[i+1][j+1];
      
	}
    }
    temp2=(int*)malloc(v*sizeof(int));
/********************************Loop unitl no edge********************************/
  while(edge==1) 
    {
      edge=maxi=maxc=0;
      for(i=0;i<v;i++)
	{count=0;
	  for(j=0;j<v;j++)
	    {
	      if(temp[i][j]==1)
		{
                  edge=1;
		  count++;
		}
	     }
	   if(maxc<count){maxc=count;maxi=i;}
	}
      if(edge==1){temp2[ind]=maxi;
	           ind++;}
        for(i=0;i<v;i++){temp[maxi][i]=temp[i][maxi]=0;}
    }
    /////free temp[][]
    for(i=0;i<v;i++)free(temp[i]);free(temp);

	/***********refine start refinig********/
        for(i=0;i<ind;i++)
	{       
		a=temp2[i]+1;//element of vertex cover set
		inv2=0;
        	for(j=1;j<=v;j++)
		{       
			if(gr[a][j]==1) // edges to vertex from vertex cover set
			{
				inv=0;
				for(k=0;k<ind;k++)//check edge between set members
				{
					if((j-1)==temp2[k]){inv=1;break;}
					
				}
				if(inv!=1)//check edge between set members and other vertices
				{       
					for(k=0;k<ind;k++)
					{
						b=temp2[k]+1;
						if(gr[j][b]==1)
						{       
							inv2=1;
							break;
						}
					}
				}
				
			}
			
			
		}if(inv2==1) //if set member has no edge with vertices other then set members then delete them
				{
					res2[i]=temp2[i];
				}
                
	}
	
        free(temp2);

  return 1;
}
int apvc2(int v)
{
  int **temp,i,j,ind,x,y,edge,track;
/********************copying value temporary array****************************/
  temp=(int**)malloc(v*sizeof(int*));
  for(i=0;i<v;i++)
         temp[i]=(int*)malloc(v*sizeof(int));
  for(i=0;i<v;i++)
    {
      for(j=0;j<v;j++)
	{
	  temp[i][j]=gr[i+1][j+1];
      
	}
    }
x=y=ind=track=0;edge=1;
/********************************Loop unitl no edge********************************/
  while(edge==1) 
    {
      edge=0;
      for(i=0;i<v;i++)
	{
	  for(j=0;j<v;j++)
	    {
	      if(temp[i][j]==1)
		{
                  edge=1;
		  x=res3[ind]=i; 
		  y=res3[ind+1]=j;
	          ind=ind+2;
             
		  break;
		}
       	     }
	   if(edge==1)break;
	
	}
        for(i=0;i<v;i++){temp[x][i]=temp[i][x]=temp[y][i]=temp[i][y]=0;}
	
    }
    for(i=0;i<v;i++)free(temp[i]);free(temp);
  return 1;
}
int revc2(int v)
{
  int **temp,i,j,ind,x,y,edge,track,*temp2,a,b,k,inv,inv2;
  
/********************copying value temporary array****************************/
  temp2=(int*)malloc(v*sizeof(int));
  temp=(int**)malloc(v*sizeof(int*));
  for(i=0;i<v;i++)
         temp[i]=(int*)malloc(v*sizeof(int));
  for(i=0;i<v;i++)
    {
      for(j=0;j<v;j++)
	{
	  temp[i][j]=gr[i+1][j+1];
      
	}
    }
x=y=ind=track=0;edge=1;
/********************************Loop unitl no edge********************************/
  while(edge==1) 
    {
      edge=0;
      for(i=0;i<v;i++)
	{
	  for(j=0;j<v;j++)
	    {
	      if(temp[i][j]==1)
		{
                  edge=1;
		  x=temp2[ind]=i; 
		  y=temp2[ind+1]=j;
	          ind=ind+2;
             
		  break;
		}
       	     }
	   if(edge==1)break;
	
	}
        for(i=0;i<v;i++){temp[x][i]=temp[i][x]=temp[y][i]=temp[i][y]=0;}
	
    }
    for(i=0;i<v;i++)free(temp[i]);free(temp);

	/***********refine start refinig********/
        for(i=0;i<ind;i++)
	{       
		a=temp2[i]+1;//element of vertex cover set
		inv2=0;
        	for(j=1;j<=v;j++)
		{       
			if(gr[a][j]==1) // edges to vertex from vertex cover set
			{
				inv=0;
				for(k=0;k<ind;k++)//check edge between set members
				{
					if((j-1)==temp2[k]){inv=1;break;}
					
				}
				if(inv!=1)//check edge between set members and other vertices
				{       
					for(k=0;k<ind;k++)
					{
						b=temp2[k]+1;
						if(gr[j][b]==1)
						{       
							inv2=1;
							break;
						}
					}
				}
				
			}
			
			
		}if(inv2==1) //if set member has no edge with vertices other then set members then delete them
				{
					res4[i]=temp2[i]; 
			
				}
                
	}
free(temp2);
  return 1;
}
int vc(int v)
{ 
   int i,j,r,l,a,key,var,loop1,ind;
   int row,col,nop; 
   //int *node;
    for(i=1;i<=v;i++)
	{       
		l=v*i;
		
    		int p[2], bak;

		pipe(p);
    		bak = dup(STDOUT_FILENO);
		dup2(p[1], STDOUT_FILENO);
		mgr= SAT_InitManager();
			
                SAT_SetNumVariables(mgr,l);
               
		r=cl_one(v,i);
		r=cl_two(v,i);
		r=cl_three(v,i);
		r=cl_four(v,i);
		
		key = SAT_Solve(mgr);
		
		dup2(bak, STDOUT_FILENO);
                if(key == SATISFIABLE) 
		{
			ind=0;
			var= SAT_NumVariables(mgr);
			
		        for(j = 1; j <= var; j++) 
			{
				a = SAT_GetVarAsgnment(mgr,j);
	    			if(a == 1) {
			                      
                                                for(row=1;row<=v;row++)
						{
							for(col=1;col<=v;col++)
							{
								if(grk[row][col]==j)
								{
									node[ind]=row-1;
									ind++;
								}
							}
						}							
						
	    				   }
	    			else if(a == 0) {
						  nop=1;
				      	        }
	                        else {
		                      fprintf(stderr,"Error: Sat solver generet invalid state"); fflush(stderr);
	                            }
			}
			SAT_ReleaseManager(mgr);    
		
		       
			break;
    		}
    		else
		 {
			nop=1;
			SAT_ReleaseManager(mgr);
    		  }
		  
                 
	}
	
    return i;
}


int make_clause(int c[],int l)
{
	int i;
        for(i=0;i<l;i++)
	{
		if(c[i]<0)
		{
			c[i]=c[i]*(-1);
			c[i]=(c[i]<<1)+1;
		}
		else 
		{
			c[i]=(c[i]<<1);
		}
	}
	SAT_AddClause(mgr, c, l);
	
return 1;
}
int cl_one(int n,int k)
{
	int *cl,ind,i,j,r;
	
	cl=(int*)malloc(n*sizeof(int));
	for(j=1;j<=k;j++)
	{ 	ind=0;
		for(i=1;i<=n;i++)
		{
			cl[ind]=grk[i][j];
			ind++;
		}
		r=make_clause(cl,ind);
	}
	free(cl);
	return 1;
}

int cl_two(int n,int k)
{
	int cl[2],r,m,p,q,i;
				
	for(m=1;m<=n;m++)
	{
		for(i=1;i<k;i++)
		{
			p=i;
			for(q=p+1;q<=k;q++)
			{	
				cl[0]=(-1)*grk[m][p];
				cl[1]=(-1)*grk[m][q];
			      r=make_clause(cl,2);
			}
				
		}

	}
	return 1;
}
int cl_three(int n,int k)
{
	int cl[2],m,p,q,i,r;
	for(m=1;m<=k;m++)
	{
		for(i=1;i<n;i++)
		{
			p=i;
			for(q=p+1;q<=n;q++)
			{	
				cl[0]=(-1)*grk[p][m];
				cl[1]=(-1)*grk[q][m];
			        r=make_clause(cl,2);
                          }
		}
	}
	return 1;
}

int cl_four(int n,int k)
{
	int *cl,ind,i,j,l,r;
	
	cl=(int*)malloc((2*k)*sizeof(int));
	for(i=1;i<n;i++)
	{ 	
		for(j=i+1;j<=n;j++)
		{
			if(gr[i][j]==1)
			{
				ind=0;
				for(l=1;l<=k;l++)		
					{
						cl[ind]=grk[i][l];
						ind++;
						cl[ind]=grk[j][l];
						ind++;
					}
			
				r=make_clause(cl,ind);
			}
		}		
		
	}
	free(cl);
	return 1;
}

/*Acknowledgement: http://stackoverflow.com/questions/9210528/split-string-with-delimiters-in-c Author : Matt for this  function and use it as my assignment requirement*/

/*For spliting the edge input..*/
char** split(char* str_edge, const char delimeter)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = str_edge;
    char* last_comma = 0;
    char delim[2];
    delim[0] = delimeter;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (delimeter == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (str_edge + strlen(str_edge) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = (char**)malloc(count*sizeof(char*));

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(str_edge, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
