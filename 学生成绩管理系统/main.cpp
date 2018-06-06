#include<stdlib.h>
#include<stdio.h>
#include<string.h> 
struct student{
    char num[10];
    char name[20];
    int  score[3];
    int grades;
    struct student *next;
};
typedef struct student DATE;
void Menu(){
    printf("\n\n\n");
    printf("\t\t**************************欢迎访问学生成绩管理系统**************************\n\n\n");
    printf("\t\t                        1---学生信息数据的录入\n");
    printf("\t\t                        2---显示所有的学生信息\n");
    printf("\t\t                        3---学生信息数据追加\n");
    printf("\t\t                        4---学生信息数据修改\n");
    printf("\t\t                        5---学生信息数据删除\n");
    printf("\t\t                        6---学生信息数据查询\n");
    printf("\t\t                        0---退出系统\n\n\n");
	printf("\t\t 作者：阿卜杜热伊木·阿卜杜力木  学号：U201612616  班级：医学影像学201601班\n");
	printf("\t\t****************************************************************************");
    printf("\n\n请在0-6中选择，并按回车键结束\n");
}
void Wenjian(DATE *head){ //将链表中数据保存在文件中
    FILE *fp;
    DATE *p;
    p=head;
    fp=fopen("students_information.txt","wt");
    if(fp == NULL){
        printf("\n文件打开失败，students_information.txt文件可能不存在\n");
        getchar();
        exit(0);
    }
    while(p!= NULL){
        fprintf(fp,"%s %s %d %d %d %d\n",p->name,p->num,p->score[0],p->score[1],p->score[2],p->grades);
        p=p->next;
    }
    fclose(fp);
} 
int icount;
DATE *Creat(){ //学生数据信息创建
    DATE *head=NULL;
    DATE *p1,*p2;
    int i,sum=0;
    icount=0;
    printf("写文件程序......\n");
    p1=p2=(DATE *)malloc(sizeof(DATE));
    printf("请输入学生的信息：\n");
    while(1){
    	printf("\n");
		printf("请输入学生的学号（回车继续，#号停止）：");
        scanf("%s",p1->num);
        if(!strcmp("#\0",p1->num)){
            break;
        }
        printf("请输入学生的姓名（回车继续）：");
        scanf("%s",p1->name);
        printf("请分别输入学生的语文，数学，英语成绩（每项成绩输入完成后请按回车）：");
        sum=0;
        for(i=0;i<3;i++){
            scanf("%d",&p1->score[i]);
            sum+=p1->score[i];
        }
        icount++;
        p1->grades=sum;
        if(icount==1){
            head=p1;
            p1->next=NULL;
            p2=p1;
        }
        else{
            p1->next=NULL;
            p2->next=p1;
            p2=p1;
        }
        p1=(DATE *)malloc(sizeof(DATE));
    }
    free(p1);
    printf("\n\n*****共有%d个学生信息录入*****\n\n",icount);
    Wenjian(head);
    return head;
}
DATE *Print()					//将学生信息从文件中取出保存到链表中 
{
    DATE *ptemp,*head,*r;
    FILE *fp;
    fp=fopen("students_information.txt","rt");
    if(fp==NULL)
    {
    	printf("\n\nstudents_information.txt文件打开失败\n\n");
    	getchar();
    	exit(0);
    }
    head=(struct student *)malloc(sizeof(struct student));
    head->next=NULL;
    r=head;
    while(!feof(fp))
    {
        ptemp=(DATE *)malloc(sizeof(DATE));
        fscanf(fp,"%s %s %d %d %d %d\n",ptemp->name,ptemp->num,&ptemp->score[0],&ptemp->score[1],&ptemp->score[2],&ptemp->grades);
        r->next=ptemp;
        r=ptemp;
    }
    r->next=NULL;
    fclose(fp);
    head=head->next ;
    return head;
}
void Output(){ //显示所有学生的数据信息
    DATE *p;
    p=Print();
    while(p){
        printf("\n学号：%s",p->num);
        printf("\n姓名：%s",p->name);
        printf("\n语文，数学，英语：%d  %d  %d",p->score[0],p->score[1],p->score[2]);
        printf("\n总分：%d",p->grades);
        p=p->next;
        printf("\n");
    }
    printf("\n");
}
void Add(){ //学生数据信息的追加 尾加
    DATE *pt,*p1,*head;
    int i = 1,sum=0;
    head= pt = Print();
    while(pt->next){
        pt=pt->next;
    }
    p1=(DATE *)malloc(sizeof(DATE));
    printf("请输入要插入的学生信息：\n\n");
    printf("\n请输入学号（回车继续）：");
    scanf("%s",p1->num);
    printf("\n请输入姓名（回车继续）：");
    scanf("%s",p1->name);
    printf("\n请分别输入学生的语文，数学，英语成绩（每项成绩输入完成后请按回车）：：");
    for(i=0;i<3;i++){
        scanf("%d",&p1->score[i]);
        sum+=p1->score[i];
    }
    p1->grades=sum;
    pt->next = p1;
    p1->next=NULL;
    Wenjian(head);
}
int Change(){ //学生数据信息修改
    printf("\n请输入要修改的学生的学号（回车继续）：\n");
    DATE *pt,*head;
    head=pt=Print();
    char str[10];
    int i,sum=0,flag=1;
    scanf("%s",str);
    do{
    	if(!strcmp(str,pt->num)){
            break;
        }
        pt=pt->next;
        if(!strcmp(str,pt->num)){
            flag=0;
        }
        else if(pt->next==NULL){
            printf("\n\n*****您输入的学号可能不存在*****\n\n");
        	return 0; 
        }
    }while(flag==1);
    printf("\n您要修改的学生信息为：\n\n");
    printf("\n学号：%s",pt->num);
    printf("\n姓名：%s",pt->name);
    printf("\n语文，数学，英语：%d %d %d",pt->score[0],pt->score[1],pt->score[2]);
    printf("总分:%d",pt->grades);
    printf("\n\n");
    printf("\n请输入您要修改的学生的信息\n\n");
    printf("请输入学号（回车继续）：");
    scanf("%s",pt->num);
    printf("\n姓名（回车继续）：");
    scanf("%s",pt->name);
    printf("\n请分别输入学生的语文，数学，英语成绩（每项成绩输入完成后请按回车）：");
    for(i=0;i<3;i++){
        scanf("%d",&pt->score[i]);
        sum+=pt->score[i];
    }
    pt->grades=sum;
    Wenjian(head);
}
int Delete(){ //学生数据信息删除
    printf("\n请输入要删除学生的学号（回车继续）：");
    char str[10];
    int flag=1;
    scanf("%s",str);
    DATE *pt,*pi,*head;
    head=pt=pi=Print();
    do{
        if(!strcmp(str,pi->num)){
            printf("\n您要删除的学生信息为如下\n");
            printf("\n学号：%s",pi->num);
            printf("\n姓名：%s",pi->name);
            printf("\n语文，数学，英语：%d %d %d",pi->score[0],pi->score[1],pi->score[2]);
            printf("\n总分：%d",pi->grades);
            head=pi->next;
            pt=pt->next;
            free(pi);
            printf("\n\n*****该学生信息已删除*****\n");
            Wenjian(head);
            return 0; 
        }
        pi=pt;
        pt=pt->next;
        if(!strcmp(str,pt->num)){
            flag=0;
        }
        else if(pt->next==NULL){
            printf("\n\n*****您输入的学号可能不存在*****\n");
           return 0;
        }
    }while(flag==1);
    printf("\n您要删除的学生信息为如下\n");
    printf("\n\n学号：%s",pt->num);
    printf("\n姓名：%s",pt->name);
    printf("\n语文，数学，英语：%d %d %d",pt->score[0],pt->score[1],pt->score[2]);
    printf("\n总分：%d",pt->grades);
    pi->next=pt->next;
    free(pt);
    printf("\n*****该学生信息已删除*****\n");
    Wenjian(head);
}
int Search(){ //学生数据信息查询
    DATE *pt,*head;
    head=pt=Print();
    char str[10];
    int flag=1;
    printf("\n\n请输入要查询的学生的学号（回车继续）：");
    scanf("%s",str);
    do{
        if(!strcmp(str,pt->num)){
            printf("\n\n您要查询的学生信息为如下\n\n");
            printf("\n学号：%s",pt->num);
            printf("\n姓名：%s",pt->name);
            printf("\n语文，数学，英语：%d %d %d",pt->score[0],pt->score[1],pt->score[2]);
            printf("\n总分：%d\n\n",pt->grades);
            return 0;
        }
        pt=pt->next;
        if(!strcmp(str,pt->num)){
            flag=0;
        }
        else if(pt->next==NULL){
            printf("\n\n*****您输入的学号可能不存在*****\n\n");
            return 0;
        }
    }while(flag==1);
    printf("\n\n您要查询的学生信息为：\n");
    printf("\n学号：%s",pt->num);
    printf("\n姓名：%s",pt->name);
    printf("\n语文，数学，英语：%d  %d  %d",pt->score[0],pt->score[1],pt->score[2]);
    printf("\n总分：%d",pt->grades);
    printf("\n\n");
    return 0;
}
int main(){
    int choice;
    system("color 0b");
    Menu();
    scanf("%d",&choice);
    do{
        switch(choice){
            case 1:Creat();
                system("pause");
                system("cls");
                Menu(); break;
            case 2:Output();
                system("pause");
                system("cls");
                Menu(); break;
            case 3:Add();
                system("pause");
                system("cls");
                Menu(); break;
            case 4:Change() ;
                system("pause");
                system("cls");
                Menu(); break;
            case 5:Delete();
                system("pause");
                system("cls");
                Menu(); break;
            case 6:Search();
                system("pause");
                system("cls");
                Menu(); break;
            case 0:  exit(0) ;      break;
        }
        printf("\n是否继续操作,如果想要退出系统可以选择'0'，并按回车键\n");
        printf("\n\n请选择：\n");
        scanf("%d",&choice);
    }while(choice!=0);
    return 0;
}