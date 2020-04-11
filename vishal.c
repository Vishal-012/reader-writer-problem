#include<stdio.h> 
#include<pthread.h> 
#include<semaphore.h> 
#include<unistd.h> 
 
sem_t mutex,writeblock; 
int data=0,rcount=0; 
void *reader(void *arg) 
{ 
int f; 
f=((__intptr_t)arg); 
sem_wait(&mutex); 
rcount++; 
if(rcount==1) 
{ 
sem_wait(&writeblock); 
} 
sem_post(&mutex); 
printf("Data read by the reader %d is %d\n",f,rcount); 
sleep(1); 
sem_wait(&mutex); 
rcount--; 
if(rcount==0)  
{ 
sem_post(&writeblock); 
sem_post(&mutex); 
} 
 void *writer(void *arg) 
{                                                                                                                        
int f;                                                                                                                   
f=((__intptr_t)arg); 
sem_wait(&writeblock); 
data++;                                                           
printf("Data writen by the writer %d is %d\n",f,data); 
sleep(1); 
sem_post(&writeblock); 
}                                                                                                                                                                                                                                               int main()                                                                                                              { 
int i,b;                                                                                                                
 pthread_t read[5],write[3]; 
sem_init(&mutex,0,1); 
sem_init(&writeblock,0,1);                                                                                              
 for(i=1;i<=5;i++){ 
pthread_create(&read[i],NULL,reader,(void *)(__intptr_t)i); 
}                                                                                                                        
for(i=1;i<=3;i++) 
{                                                                                                                       
pthread_create(&write[i],NULL,writer,(void *)(__intptr_t)i); 
} 
for(i=1;i<=5;i++)                                                                                                      
{ 
pthread_join(read[i],NULL);                                                                                             
}                                                                                                                       
for(i=1;i<=3;i++) 
{ 
pthread_join(write[i],NULL);                                                                                           
} 
return 0; 
}
