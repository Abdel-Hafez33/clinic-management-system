#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "header file/STD_Types.h"

#define DAYS 7
#define TIME_SLOTS 6
#define STATUS_LENGTH 15
#define password 1234
#define password_tim_limit 3
#define intial_counter 0

typedef struct node
{
    u8 id;
    u8 name[20];
    s8 gender[10];
    u8 age;
    s8 day;
    s8 time_slots;
    u8 flag;
    struct node *next_patient;
    struct node *prev_patient;
    

    
}patient_package;

patient_package *intial_pakage=NULL;
patient_package *last_pakage=NULL;

//helper func
patient_package *creating_patient_package ();
s8 check_id_existane(int user_id);
void scanning_data (patient_package *scan);
void printSchedule(char schedule[DAYS][TIME_SLOTS][STATUS_LENGTH], const char* days[DAYS]);
void changeReceivedToNot(char schedule[DAYS][TIME_SLOTS][STATUS_LENGTH], int dayIndex, int timeSlotIndex);
void changeNotToReceived(char schedule[DAYS][TIME_SLOTS][STATUS_LENGTH], int dayIndex, int timeSlotIndex);
void printing_linked_data();
patient_package  *search_id (int id_user);
u8 check_if_reservition(u8 dayindex,u8 timeslot);

// the admin mode function 
void add_patient();
void edit_patient_record();
void reserve_aslot_with_doc(char schedule[DAYS][TIME_SLOTS][STATUS_LENGTH], const char* days[DAYS],u8 id,int dayIndex, int timeSlotIndex);
void show_reservstion();
void cancel_reserve_aslot_with_doc(char schedule[DAYS][TIME_SLOTS][STATUS_LENGTH], const char* days[DAYS],u8 id);

//user mod function
void view_patient_record(int id);
void view_todays_reservtion(int id);

/**************************************program****************************************/

int main ()
{

    int mode_number;
    int id;
    int day_index;
    int time_index;
    int counter=intial_counter;
    int scanning_password;
    int sub_mode=intial_counter;
    char schedule[DAYS][TIME_SLOTS][STATUS_LENGTH] = {
        {"Not Received", "Not Received", "Not Received", "Not Received", "Not Received", "Not Received"},
        {"Not Received", "Not Received", "Not Received", "Not Received", "Not Received", "Not Received"},
        {"Not Received", "Not Received", "Not Received", "Not Received", "Not Received", "Not Received"},
        {"Not Received", "Not Received", "Not Received", "Not Received", "Not Received", "Not Received"},
        {"Not Received", "Not Received", "Not Received", "Not Received", "Not Received", "Not Received"},
        {"Not Received", "Not Received", "Not Received", "Not Received", "Not Received", "Not Received"},
        {"Not Received", "Not Received", "Not Received", "Not Received", "Not Received", "Not Received"}
    };
    //helow message 
    printf("******************hallow to our Clinic**************");

    //chossing mode number
    while (1)
    {

  do {  
    printf("\n we have two mode \n");
    printf("mode 1: admin                      //need password\n");
    printf("mode 2: user (for patient) \n");
    printf("please enter mode\n");


    scanf("%d",&mode_number);
    if ((mode_number>0)&&(mode_number<3))
    {
        break;
    }
    else 
    {
        printf("error in mode message");
    }
  } while (~(mode_number==1)||(mode_number==2));
  
/***************************the mode 1 */
    if (mode_number==1)
    {
        //starting admin mode 
        printf("\n*****************you now in admin mode***********\n");
        //tell admin how many trials have
        printf(" you have 3 chance to try password");

        //enter password by admin


        for( counter =intial_counter;counter<password_tim_limit;counter++)
        {

        printf("\nplease enter pass\n");
        scanf("%d",&scanning_password);
        if (scanning_password==password)
        {
            break;
        }
        printf("\n error password ");
        }
        if (counter==3)
        {
            printf("\n the trials is ended");
            return 0;
        }
        
        // tell admin what he can do 
        printf("\n**************choose your function********\n");
        printf("\nthe function you have is\n");
        printf("1_  Add new patient record \n ");
        printf("2_Edit patient record\n");
        printf("3_reserve a slot with the doctor \n");
        printf("4_ Cancel reservation \n");
        printf("please enter function number \n");
        scanf("%d",&sub_mode);

        //check sub mode from one to 
       if ((sub_mode<1)||(sub_mode>4))
       {
        printf ("error you enter invalid function number ");
        return 0;
       }

/*********************function 1 in admin mod************/
    if (sub_mode==1)
    {
        printf("\n **********you choose func 1*******\n");

    add_patient();
    }
    /*****************function 2 in admin mode***********/
    else if (sub_mode==2)
    {
        printf("\n**************you choose func2******\n");
        edit_patient_record();

    }
    /***********func 3 in admin mode****************** */
    // Define a 2D array to store the status for each time slot of each day
     

 // Define the names of the days
    const char* days[DAYS] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};


    /****************************************in func 3 in admin mode***************************************/



if (sub_mode==3)
{

    // Print the initial schedule
    printf("\nInitial Schedule:\n");
    printSchedule(schedule, days);
    //recieving 
    printf("\n  id to reservation\n");
    scanf("%d",&id);
    //choose day index
    printf("take care the day index from 0 to 6 the monday is 0 up to sunday is 6\n");
    printf("\nplease enter the day index to recived\n");
    scanf("%d",&day_index);
    printf("\ntake care the time slot is 30 minute and number of time slot from (0 to 5)  ex  (2.00pm is 0) ,(2.300 is 1), (4.30pm is 5\n)");

    //chosing time index
    printf("\n enter the time to recived ");
    scanf("%d",&time_index);

    reserve_aslot_with_doc(schedule,days,id,day_index,time_index);
    if ((time_index==0)&&day_index==0)
    {
         strcpy(schedule[0][0], "Received");
    }
    //print after updates 
     printf(" Schedule after apdates:\n");
    printSchedule(schedule, days);
}   
else if (sub_mode==4)
{
    printf("\n*******************func 4 in mode admin*****************");
    printf("\nplease enter your id\n ");
    scanf("%d",&id);
 cancel_reserve_aslot_with_doc(schedule,days,id);
  printf(" Schedule after apdates:\n");
    printSchedule(schedule, days);

}
    }

    /*****************************mode 2**********************************/
    else if (mode_number==2)
    {
    printf("\n***************you now in user mode *****************\n");
   
   //tell the user moode 
   printf("\n the fuction you have in user mode is\n");
   printf("1_View patient record.\n ");
   printf("2_ View today reservations\n");
   printf("\n please enter number of function\n");
   scanf("%d",&sub_mode );

if((sub_mode<1)||(sub_mode>2))
{
    printf("\nerror\n");
    return 0;
}
if (sub_mode==1)
{
    printf("**************you now in func 2 in user mode************");
    //scaning id
    printf("\nplease enter id \n");
    scanf("%d",&id);
    fflush(stdin);
      
    view_patient_record(id);
}
if (sub_mode==2)
{
printf("*********************you now in func 2 in user mode **************");
printf("\nplease enter id \n");
    scanf("%d",&id);

    view_todays_reservtion(id);



}
    }
    printf("\n***********************the process is done*******************");

    }
    for (int i=counter;i<1000;i++)
    {

    }
    
    return 0;
    




/******************************end program***************************/


    

}
/************************ADDING PATIENT PACKAGE**********************/

patient_package * creating_patient_package ()
{
     patient_package *new_pakage;
     new_pakage=(patient_package*)malloc(sizeof(patient_package));
     new_pakage->day=-1;
     new_pakage->time_slots=-1;
     new_pakage->flag=0;
     return new_pakage;
}
void add_patient()
{
    //creating the pointer that point on the new package
    patient_package* new_pakage=creating_patient_package();

    // if frist element and system the frist one start
    if ((intial_pakage==NULL)&&(last_pakage==NULL))
    {

    intial_pakage=last_pakage=new_pakage;
    intial_pakage->prev_patient=NULL;
    intial_pakage->next_patient=NULL;


    }
    else
     {
      new_pakage->prev_patient=last_pakage;
      last_pakage->next_patient=new_pakage;
      new_pakage->next_patient=NULL;
      last_pakage=new_pakage;


     }
     scanning_data (new_pakage);

}
// function check id exist or not 
s8 check_id_existane(int user_id)
{
    patient_package *pointer=intial_pakage;
    while(pointer!=NULL)
    {
      if (pointer->id==user_id)
      {
        return 0;
      }
      pointer=pointer->next_patient;

    }
return 1;
}
// scaning data

void scanning_data (patient_package *scan)
{
    u8 checking;
    printf("\n please enter your id : ");
    scanf("%d",&checking);
    if (check_id_existane(checking))
    {
        scan->id=checking;
        printf("please enter your name :");
        scanf("%s",&scan->name);
        printf("please enter your age :");
        scanf("%d",&scan->age);
        printf("please enter your gender ");
        scanf("%s",&scan->gender);
        if (scan->flag==0)
        {
            scan->day=-1;
            scan->time_slots=-1;
        }
       
        printf("\n");
        }
        else 
        {
            printf("the id are recieved by anthor one");
            last_pakage=scan->prev_patient;
            last_pakage->next_patient=NULL;
            free(scan);
            
        }

}
/******************ending adding functions******************/
void edit_patient_record()
{
    u8 named[20]; 
    u8 age11;
    s8 gender11[10];

    u8 id_user;
    u8 poin_time;
    u8 point_day;
    patient_package *scan;
   printf("please enter your id ");
   scanf("%d",&id_user);
   scan=search_id(id_user);
   poin_time=scan->time_slots;
   point_day=scan->day;

   if (scan!=NULL)
   {
      
        printf("please enter your name \n");
        scanf ("%s",&scan->name);
        fflush(stdin);
        printf("please your age\n");
        scanf("%d",&age11);
        fflush(stdin);
          printf("please your gender\n");
          scanf("%s",&gender11);
           // Use strcpy for string copying
          printf("your name is %s",scan->name);

          strcpy(scan->gender, gender11);  // Use strcpy for string copying
          scan->age=age11;


        

   }

}

// searshing for id package 

patient_package  *search_id (int id_user)
{
    patient_package* pointer=intial_pakage;
    while (pointer!=NULL)
    {
        if (pointer->id==id_user)
        {
            return pointer;
        }
        pointer=pointer->next_patient;
    }
    printf("the id is not exist\n");
    pointer=NULL;
    return pointer;
    
}



/**********************end editing func*********************/

/**************checking function for me not project ********/
void printing_linked_data()

{
    u8 flag=1;
    patient_package *pointer=intial_pakage;
    while (pointer!=NULL)
    
    {
      printf("the data for patient number %d ",flag,"\n");
      printf("id :%d ",pointer->id);
      printf("\n name :%s",pointer->name,"\n");
      printf("\n age : %d",pointer->age);
      printf("\n gender %s",pointer->gender,"\n");
      flag++;

      pointer=pointer->next_patient;
      printf("\n");

    }
    

}




/*********************schedule functtion********************/

// Function to print the schedule table
void printSchedule(char schedule[DAYS][TIME_SLOTS][STATUS_LENGTH], const char* days[DAYS]) 
{
    // Print the table header
    printf("| Day       |    2:00 PM   |    2:30 PM   |    3:00 PM   |    3:30 PM   |    4:00 PM   |    4:30 PM   |\n");
    printf("|-----------|--------------|--------------|--------------|--------------|--------------|--------------|\n");

    // Print each day's schedule
    for (int i = 0; i < DAYS; ++i) {
        printf("| %-9s | ", days[i]);
        for (int j = 0; j < TIME_SLOTS; ++j) {
            printf("%-12s | ", schedule[i][j]);
        }
        printf("\n");
    }
}

// Function to change status from "Received" to "Not Received"
void changeReceivedToNot(char schedule[DAYS][TIME_SLOTS][STATUS_LENGTH], int dayIndex, int timeSlotIndex)
{
    if (strcmp(schedule[dayIndex][timeSlotIndex], "Received") == 0)
     {
        strcpy(schedule[dayIndex][timeSlotIndex], "Not Received");

    }
}

// Function to change status from "Not Received" to "Received"
void changeNotToReceived(char schedule[DAYS][TIME_SLOTS][STATUS_LENGTH], int dayIndex, int timeSlotIndex)
 {

    if (strcmp(schedule[dayIndex][timeSlotIndex], "Not Received") == 0)
     {
        strcpy(schedule[dayIndex][timeSlotIndex], "Received");
    }
}

/***********************************reservision****************/
void reserve_aslot_with_doc(char schedule[DAYS][TIME_SLOTS][STATUS_LENGTH], const char* days[DAYS],u8 id,int dayIndex, int timeSlotIndex)
{
    patient_package *pointer=search_id(id);
    if ((dayIndex>=0)&&(dayIndex<7)&&(timeSlotIndex>=0)&&(timeSlotIndex<6))
    {
    if (check_if_reservition(dayIndex,timeSlotIndex))
    {
        if (pointer->flag==1)
        {
            cancel_reserve_aslot_with_doc(schedule,days,id);
        }
        pointer->day=dayIndex;
        pointer->time_slots=timeSlotIndex;
        pointer->flag=1;
        changeNotToReceived(schedule, dayIndex, timeSlotIndex);
        if ((dayIndex==0)&&(timeSlotIndex==0))
        {
             strcpy(schedule[0][0], "Received");
             pointer->flag=1;
             
        } 
       

        
    }
    else 
    {

        printf("\n*************sorry  the time is recived already by another one you****** ********\n\n");
        

    }
    }
    else 
    {
        printf("the time slot index and time slot is not defiend please try again ");

    }


}
//checking if reservition or not
u8 check_if_reservition(u8 dayindex, u8 timeslot)
{   
    patient_package *pointer = intial_pakage;
    while (pointer != NULL)
    {
        if (pointer->day == dayindex && pointer->time_slots == timeslot)
        {
            return 0; // Slot is already reserved
        }
        pointer = pointer->next_patient;
    }
    return 1; // Slot is available
}
/*********************cancel reservation*******************/
void cancel_reserve_aslot_with_doc(char schedule[DAYS][TIME_SLOTS][STATUS_LENGTH], const char* days[DAYS],u8 id)
{
    patient_package *pointer=search_id(id);
    if ((pointer->time_slots==-1)&&(pointer->day==-1))
    {
     printf ("you dont reseve any time");
    }
    else
    {
        
        changeReceivedToNot(schedule, pointer->day, pointer->time_slots);
        strcpy(schedule[pointer->day][pointer->time_slots], "Not Received");
        if ((pointer->day==0)&&(pointer->time_slots==0))
        {
             strcpy(schedule[0][0], "Not Received");
             
        } 
        if ((pointer->day==0)&&(pointer->time_slots==1))
        {
            strcpy(schedule[0][1], "Not Received");
        }
         strcpy(schedule[pointer->day][pointer->time_slots], "Not Received");

        pointer->day=-1;
        pointer->time_slots=-1;
        pointer->flag=0;
       

        
    }
    

}
/***************************************user mode ********************************* */
void view_patient_record(int id)
{

  patient_package* pointer=search_id(id);
  if (pointer!=NULL)
  {
  printf("\n the basic  data for patient is \n");
  //printing data
     printf("id :%d ",pointer->id);
      printf("\n name :%s",pointer->name);
      printf("\n age : %d",pointer->age);
      printf("\n gender %s",pointer->gender,"\n");
      printf("\n");  
}
else
  {
    printf("the id is not correct");
  }
}
void view_todays_reservtion(int id)
{
      char * days[DAYS] = {"Monday","Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
      char *time_slot[TIME_SLOTS] = {"2.00pm", "2.30pm", "3.00pm", "3.30pm", "4.00pm", "4.30pm"};
    
    
  patient_package*pointer=search_id(id);
  if (pointer->flag==0)
  {
    printf("\n you not reserve yet ! \n\n");
  }
  else if (pointer!=NULL)
  {
    printf(" \n the day  that you recieved is ");
    printf("\n %s",days[pointer->day]);
    //print the time slot that resieved
    printf("\n the time that you resieved is");
    printf("\n %s",time_slot[pointer->time_slots]);

  }
}





