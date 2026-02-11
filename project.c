#include <stdio.h>
#include <string.h>
#include <stdbool.h> //فراخوانی کتابخانه ها 
#include <stdlib.h>

typedef char *string;//راحت کار خود 
struct Done_List
{
    string done;    
};
struct Main_List //دیتا ست اصلی 
{
    string todo;
};
int LS_DONE();
int BUFFER_CLEANER();
int CREATE_BACKUP();
void USE_BACKUP();
void LOWER_CASE(string input);
int DONE();
int CLEAN();
int DEL();
int LS();   //استفاده شده توابع 
int EDIT();
int ADD();  

int num_done=0;
int num_todo=0; //متغیر های گلوبال 
struct Main_List todos_list[100]; //ایجاد ارایه برای ورود کردن todo
struct Done_List Done_L[100];// ارایه برای تودو های انجام شده
int main(void){
bool loop_key=true;//کلید حلقه
char input[10];

while(loop_key){
    int j=0;
    printf("choose one of the oprators for your todo list (add/edit/done/ls/del/backup/exit):\n");
    scanf("%s",input); 
    BUFFER_CLEANER();
    LOWER_CASE(input);
    
    
    if(strcmp(input,"add")==0)
    {
        ADD();
        continue;
    }   
    if(strcmp(input,"edit")==0)
    {
        EDIT();
        continue;
    }

    if(strcmp(input,"del")==0)
    {
        DEL();
        continue;
    }
    if(strcmp(input,"backup")==0)
    {
        USE_BACKUP();
        continue;
    }   
    if(strcmp(input,"ls")==0)
    {
        LS();
        printf("DONE:\n");
        LS_DONE();
        continue;
    }
    if(strcmp(input,"exit")==0)
    {
        char buff[10];
        printf("do you want to save your todo tasks?(yes,no)");//درخواست برای بکاپ از یوزر
        scanf("%s",buff);
        LOWER_CASE(buff);
        if (strcmp(buff,"yes")==0)
        {
            CREATE_BACKUP();
        }
        CLEAN();
        loop_key=false; //متوقف کردن لوپ
        printf("tnx for using this program!! \n goodbye!");
        continue;
    }                                
    if(strcmp(input,"done")==0){

        DONE();
        continue;

    }
    else{
        printf("invalid OP!!!!\n");
    }    
}
}
int ADD(void){
    char append[100]; //بافر موقت برای گرفتن اینپوت از کاربر
    if (num_todo>=100)
    {
        printf("sorry todo list is full!!!\n");// تست برای پر بودن ارایه
        return 1;
    }
    
    
    
    printf("what do you want to add in your todo list \n");

    scanf(" %[^\n]", append);// باید وایت اسپیس ها هم گرفته شود
    BUFFER_CLEANER();
    todos_list[num_todo].todo=malloc(strlen(append)+1);//باز کردن مموری موقت برای رشته ها 
    if (todos_list[num_todo].todo==NULL)
    {
        printf("memory allociton has failed please try again later!!!\n");
        return 1;
    }
    
    
    
    strcpy(todos_list[num_todo].todo, append);//اعمال کردن بافر موقت بر روی لیست 
    printf("Added: %s\n", todos_list[num_todo].todo);
    num_todo++;
    return 0;

}
int EDIT(void)
{
    char buff[100];//بافر موقت برای تغییر
    int j;
    if (num_todo==0)
    {
        printf("list is empty there is nothing to edit");
        return -1;
    }
    
    LS();
    printf("which todos you want to edit ?\n");
    scanf("%d",&j);
    BUFFER_CLEANER();
    if (j<1 || j>num_todo)
    {
        printf("invalid num");//باید اینپوت جزعی از ایندکس ارایه تودو باشد
        return 0;
    }
    
    
    
    
    printf("what is your new todo to replace?\n");
    scanf("%s",buff);
    j--;
    
    strcpy(todos_list[j].todo, buff);// پیست کردن از بافر به لیست
    printf("your new todo list is \n");
    LS();
    return 0;
}
int DEL(void)
{
    int num_del;
    LS();
    if (num_todo==0)
    {
        printf("there is nothing to delete");
        return 0;
    }
    
    printf("which todo you want to del? \n");
    scanf("%d", &num_del);

    int index = num_del - 1;
    if (index < 0 || index >= num_todo)//مطمعن شدن از درستی اینپوت
    {
        printf("not valid\n");
        return 1;
    }

    free(todos_list[index].todo);//خالی سازی المنت وابسطه به ایندکس


    for (int i = index; i < num_todo - 1; i++)// شیفت کردن المنت های پایینی به سمت بالا به اندازه یک ایندکس
    {
        todos_list[i].todo = todos_list[i + 1].todo;
    }

    num_todo--;//کم کردن تعداد المنت در ارایه

    printf("your new list is \n");
    LS();

    return 0;
}
int LS(void)
{
    if (num_todo==0)
    {
        printf("there is nothing to show");
        return 0;
    }
    
    
    
    for (int i = 0; i < num_todo; i++)
    {
        printf("%d-%s\n",i+1,todos_list[i].todo);//لوپ برای نشان دادن المنت ها
    }
}
int CLEAN(void)
{
    for (int i = 0; i < num_todo; i++)//خالی سازی مموری های موقت برای کرش نکردن سافتور در اینپوت های زیاد
{
    free(todos_list[i].todo);
    todos_list[i].todo=NULL;//خالی کردن کل ارایه موقت شده
}
    num_todo=0;
    
    for (int j = 0; j < num_done; j++)//خالی سازی مموری های موقت برای کرش نکردن سافتور در اینپوت های زیاد
{
    free(Done_L[j].done);
    Done_L[j].done=NULL;//خالی کردن کل ارایه موقت شده
}
    num_done=0;    
    return 0;
}
int DONE(){
    int buff;//بافر موقت
    printf("choose your done task for the day \n");
    LS();
    
    scanf("%d",&buff);
    if (buff<1 || buff>num_todo)
    {
        printf("invalid input !!!\n");//اطمینان بودن ایندکس
        return 0;
    }
    
     Done_L[num_done].done=malloc(strlen(todos_list[buff-1].todo)+1);
    
    
    strcpy(Done_L[num_done].done,todos_list[buff-1].todo);
    num_done++;
    free(todos_list[buff-1].todo);//خالی سازی المنت وابسطه به ایندکس


    for (int i = buff-1; i < num_todo - 1; i++)// شیفت کردن المنت های پایینی به سمت بالا به اندازه یک ایندکس
    {
        todos_list[i].todo = todos_list[i + 1].todo;
    }

    num_todo--;//کم کردن تعداد المنت در ارایه
     
    printf("task is done as:%s\n",Done_L[num_done-1].done);
 
    
    return 0;

}
int BUFFER_CLEANER(){
    while (getchar() !='\n');//خالی کردن بافر های اضافه در ترمینال 
    
}
int CREATE_BACKUP(){
    FILE *backup_todo;
    string buffer;
    BUFFER_CLEANER();
    char c;
    printf("give me a directry for a new folder (txt)(use double\\ to use back slash notation):\n");
    scanf("%s",buffer);
    BUFFER_CLEANER();
    backup_todo=fopen(buffer,"w");//ساختن فایل برای نوشتن
    if (backup_todo==NULL)
    {
        printf("couldnt allocate the folder please try again !!!!\n");//چک کردن ادرس درست
        return 1;
    }
    fprintf(backup_todo,"=======TODO TASK=======\n");
    for (int i = 0; i < num_todo; i++)
    {
        fprintf(backup_todo,"%d.%s\n",i+1,todos_list[i].todo);//لوپ برای اضافه کردن کل ارایه تودو به تکست
    }
        
    
    fprintf(backup_todo,"=========DONE TASK=======\n");
    for (int j = 0; j < num_done; j++)
    {
        fprintf(backup_todo,"%d.%s\n",j+1,Done_L[j].done);
    }
    printf("backup has been created in this location:%s\n",buffer);//لوپ برای اضافه کردن کل تسک های انجام شده به تکست
    fclose(backup_todo);
    
}
void LOWER_CASE(string input){
    for (int i = 0; input[i]!='\0'; i++)
    {
        if (input[i]>='A' &&input[i]<='Z')//کوچک کردن حروف با کمک بیت 
        {
            input[i]+=32;
        }
        
    }
    

} 
void USE_BACKUP(){
    FILE *BACKUP;
    char loc[100];
    char content[500];
    int num_loaded=0;
    string dot;
    
    printf("give me a location of your backup (use double \\ to use back slash notation!!):");
    scanf("%s",loc);
    BUFFER_CLEANER();
    BACKUP=fopen(loc,"r");
     if (BACKUP == NULL) {
        printf("Couldn't open file: %s\n", loc);
        return;
    }   
    while (fgets(content,sizeof(content),BACKUP)!=NULL)//گرفتن اینپوت از تکست یا فایل
    {
        content[strcspn(content,"\n")]='\0';//حذفenter های اضافی 
        if (strlen(content) == 0) {
            continue;
        }
        string todo_text=content;

        dot = strchr(content,'.');//حذف نقطه با رد کردن 
        if (dot !=NULL)
        {
            todo_text=dot+1;
        }
        while (*todo_text==' ')//رفتن به کاراکتر بعد 
        {
            todo_text++;
        }
        if (strlen(todo_text) == 0) 
        {
            continue;
        }
        todos_list[num_todo].todo = malloc(strlen(todo_text) + 1);//ایجاد مموری موقت برای اینپوت های جدید
        if (todos_list[num_todo].todo == NULL) 
        {
            printf("Memory error for: %s\n", todo_text);
            continue;
        }
        strcpy(todos_list[num_todo].todo,todo_text);
        num_todo++;
        num_loaded++;

    }

fclose(BACKUP);

    printf("\nLoaded %d todos from backup.\n", num_loaded);
    printf("Total todos now: %d\n\n", num_todo);
  LS();
}  

int LS_DONE(){
    if (num_done==0)
    {
        printf("there is nothing to show");
        return 0;
    }
    
    
    
    for (int i = 0; i < num_done; i++)
    {
        printf("%d-%s\n",i+1,Done_L[i].done);//لوپ برای نشان دادن المنت ها
    }

}
