#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t mylock;

int things_table[4][3] = {0};
void *student1(){
pthread_mutex_lock(&mylock);
printf("\nStudent1 took 2(Paper) and 3(Question Paper).\n");

things_table[3][0] = 1;

printf("Student1 is finished with the assisgnment.\n"); pthread_mutex_unlock(&mylock);
}

void *student2(){
pthread_mutex_lock(&mylock);

printf("\nStudent2 took 1(Pen) and 3(Question Paper).\n"); 
things_table[3][1] = 1;

printf("Student2 is finished with the assisgnment.\n"); pthread_mutex_unlock(&mylock);
}
void *student3(){
pthread_mutex_lock(&mylock);
printf("\nStudent3 took 1(Pen) and 2(Paper).\n");
things_table[3][2] = 1;
printf("Student3 is finished with the assisgnment.\n"); pthread_mutex_unlock(&mylock);
}
int choice1, choice2;
void *teacher()
{
pthread_mutex_lock(&mylock);
printf("\nResource 1 to be kept on table: ");
scanf("%d",&choice1);
printf("\nResource 2 to be kept on table: ");
scanf("%d",&choice2);
pthread_mutex_unlock(&mylock);
}

 int main(){
int i=0,j=0;
pthread_mutex_init(&mylock, NULL);
pthread_t student_thread;
pthread_t teacher_thread;
things_table[0][0] = 1; printf("\t\t\t\t\t --by Vishal Agrawal,EE035,11706065\n"); 
printf("\n\t\t Allocations(what each number means)\n\n"); printf("\t 1 --> Pen\t\t2 --> Paper\t\t3 --> Question Paper\n");

for(i=0;i<4;i++){
for(j = 0; j<3;j++){
printf("\t%d\t",things_table[i][j]);
}
printf("\n");
}

while(1 > 0){

if(things_table[3][0] && things_table[3][1] &&	
things_table[3][2]){	
break;	

}
pthread_create(&teacher_thread, NULL, teacher, NULL); pthread_join(teacher_thread, NULL);
if(((choice1 == 2 && choice2 == 3) ||(choice1 == 3 && choice2 == 2)) && things_table[3][0] == 0){

pthread_create(&student_thread, NULL, student1, NULL); pthread_join(student_thread, NULL);
}

else if(((choice1 == 1 && choice2 == 3) ||(choice1 == 3 && choice2 == 1)) && things_table[3][1] == 0){

pthread_create(&student_thread, NULL, student2, NULL); pthread_join(student_thread, NULL);
}

else if(((choice1 == 1 && choice2 == 2) ||(choice1 == 2 && choice2 == 1)) && things_table[3][2] == 0){

pthread_create(&student_thread, NULL, student3, NULL); pthread_join(student_thread, NULL);
}
else{

printf("\nEither all the students are finished with their assisgnments or you have given wrong inputs!\n");
}
}
printf("\n");
for(i =0;i<6;i++){
printf("Exitting from the program...\n");
}
}

