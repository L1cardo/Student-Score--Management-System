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
    printf("\t\t**************************��ӭ����ѧ���ɼ�����ϵͳ**************************\n\n\n");
    printf("\t\t                        1---ѧ����Ϣ���ݵ�¼��\n");
    printf("\t\t                        2---��ʾ���е�ѧ����Ϣ\n");
    printf("\t\t                        3---ѧ����Ϣ����׷��\n");
    printf("\t\t                        4---ѧ����Ϣ�����޸�\n");
    printf("\t\t                        5---ѧ����Ϣ����ɾ��\n");
    printf("\t\t                        6---ѧ����Ϣ���ݲ�ѯ\n");
    printf("\t\t                        0---�˳�ϵͳ\n\n\n");
	printf("\t\t ���ߣ�����������ľ����������ľ  ѧ�ţ�U201612616  �༶��ҽѧӰ��ѧ201601��\n");
	printf("\t\t****************************************************************************");
    printf("\n\n����0-6��ѡ�񣬲����س�������\n");
}
void Wenjian(DATE *head){ //�����������ݱ������ļ���
    FILE *fp;
    DATE *p;
    p=head;
    fp=fopen("students_information.txt","wt");
    if(fp == NULL){
        printf("\n�ļ���ʧ�ܣ�students_information.txt�ļ����ܲ�����\n");
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
DATE *Creat(){ //ѧ��������Ϣ����
    DATE *head=NULL;
    DATE *p1,*p2;
    int i,sum=0;
    icount=0;
    printf("д�ļ�����......\n");
    p1=p2=(DATE *)malloc(sizeof(DATE));
    printf("������ѧ������Ϣ��\n");
    while(1){
    	printf("\n");
		printf("������ѧ����ѧ�ţ��س�������#��ֹͣ����");
        scanf("%s",p1->num);
        if(!strcmp("#\0",p1->num)){
            break;
        }
        printf("������ѧ�����������س���������");
        scanf("%s",p1->name);
        printf("��ֱ�����ѧ�������ģ���ѧ��Ӣ��ɼ���ÿ��ɼ�������ɺ��밴�س�����");
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
    printf("\n\n*****����%d��ѧ����Ϣ¼��*****\n\n",icount);
    Wenjian(head);
    return head;
}
DATE *Print()					//��ѧ����Ϣ���ļ���ȡ�����浽������ 
{
    DATE *ptemp,*head,*r;
    FILE *fp;
    fp=fopen("students_information.txt","rt");
    if(fp==NULL)
    {
    	printf("\n\nstudents_information.txt�ļ���ʧ��\n\n");
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
void Output(){ //��ʾ����ѧ����������Ϣ
    DATE *p;
    p=Print();
    while(p){
        printf("\nѧ�ţ�%s",p->num);
        printf("\n������%s",p->name);
        printf("\n���ģ���ѧ��Ӣ�%d  %d  %d",p->score[0],p->score[1],p->score[2]);
        printf("\n�ܷ֣�%d",p->grades);
        p=p->next;
        printf("\n");
    }
    printf("\n");
}
void Add(){ //ѧ��������Ϣ��׷�� β��
    DATE *pt,*p1,*head;
    int i = 1,sum=0;
    head= pt = Print();
    while(pt->next){
        pt=pt->next;
    }
    p1=(DATE *)malloc(sizeof(DATE));
    printf("������Ҫ�����ѧ����Ϣ��\n\n");
    printf("\n������ѧ�ţ��س���������");
    scanf("%s",p1->num);
    printf("\n�������������س���������");
    scanf("%s",p1->name);
    printf("\n��ֱ�����ѧ�������ģ���ѧ��Ӣ��ɼ���ÿ��ɼ�������ɺ��밴�س�������");
    for(i=0;i<3;i++){
        scanf("%d",&p1->score[i]);
        sum+=p1->score[i];
    }
    p1->grades=sum;
    pt->next = p1;
    p1->next=NULL;
    Wenjian(head);
}
int Change(){ //ѧ��������Ϣ�޸�
    printf("\n������Ҫ�޸ĵ�ѧ����ѧ�ţ��س���������\n");
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
            printf("\n\n*****�������ѧ�ſ��ܲ�����*****\n\n");
        	return 0; 
        }
    }while(flag==1);
    printf("\n��Ҫ�޸ĵ�ѧ����ϢΪ��\n\n");
    printf("\nѧ�ţ�%s",pt->num);
    printf("\n������%s",pt->name);
    printf("\n���ģ���ѧ��Ӣ�%d %d %d",pt->score[0],pt->score[1],pt->score[2]);
    printf("�ܷ�:%d",pt->grades);
    printf("\n\n");
    printf("\n��������Ҫ�޸ĵ�ѧ������Ϣ\n\n");
    printf("������ѧ�ţ��س���������");
    scanf("%s",pt->num);
    printf("\n�������س���������");
    scanf("%s",pt->name);
    printf("\n��ֱ�����ѧ�������ģ���ѧ��Ӣ��ɼ���ÿ��ɼ�������ɺ��밴�س�����");
    for(i=0;i<3;i++){
        scanf("%d",&pt->score[i]);
        sum+=pt->score[i];
    }
    pt->grades=sum;
    Wenjian(head);
}
int Delete(){ //ѧ��������Ϣɾ��
    printf("\n������Ҫɾ��ѧ����ѧ�ţ��س���������");
    char str[10];
    int flag=1;
    scanf("%s",str);
    DATE *pt,*pi,*head;
    head=pt=pi=Print();
    do{
        if(!strcmp(str,pi->num)){
            printf("\n��Ҫɾ����ѧ����ϢΪ����\n");
            printf("\nѧ�ţ�%s",pi->num);
            printf("\n������%s",pi->name);
            printf("\n���ģ���ѧ��Ӣ�%d %d %d",pi->score[0],pi->score[1],pi->score[2]);
            printf("\n�ܷ֣�%d",pi->grades);
            head=pi->next;
            pt=pt->next;
            free(pi);
            printf("\n\n*****��ѧ����Ϣ��ɾ��*****\n");
            Wenjian(head);
            return 0; 
        }
        pi=pt;
        pt=pt->next;
        if(!strcmp(str,pt->num)){
            flag=0;
        }
        else if(pt->next==NULL){
            printf("\n\n*****�������ѧ�ſ��ܲ�����*****\n");
           return 0;
        }
    }while(flag==1);
    printf("\n��Ҫɾ����ѧ����ϢΪ����\n");
    printf("\n\nѧ�ţ�%s",pt->num);
    printf("\n������%s",pt->name);
    printf("\n���ģ���ѧ��Ӣ�%d %d %d",pt->score[0],pt->score[1],pt->score[2]);
    printf("\n�ܷ֣�%d",pt->grades);
    pi->next=pt->next;
    free(pt);
    printf("\n*****��ѧ����Ϣ��ɾ��*****\n");
    Wenjian(head);
}
int Search(){ //ѧ��������Ϣ��ѯ
    DATE *pt,*head;
    head=pt=Print();
    char str[10];
    int flag=1;
    printf("\n\n������Ҫ��ѯ��ѧ����ѧ�ţ��س���������");
    scanf("%s",str);
    do{
        if(!strcmp(str,pt->num)){
            printf("\n\n��Ҫ��ѯ��ѧ����ϢΪ����\n\n");
            printf("\nѧ�ţ�%s",pt->num);
            printf("\n������%s",pt->name);
            printf("\n���ģ���ѧ��Ӣ�%d %d %d",pt->score[0],pt->score[1],pt->score[2]);
            printf("\n�ܷ֣�%d\n\n",pt->grades);
            return 0;
        }
        pt=pt->next;
        if(!strcmp(str,pt->num)){
            flag=0;
        }
        else if(pt->next==NULL){
            printf("\n\n*****�������ѧ�ſ��ܲ�����*****\n\n");
            return 0;
        }
    }while(flag==1);
    printf("\n\n��Ҫ��ѯ��ѧ����ϢΪ��\n");
    printf("\nѧ�ţ�%s",pt->num);
    printf("\n������%s",pt->name);
    printf("\n���ģ���ѧ��Ӣ�%d  %d  %d",pt->score[0],pt->score[1],pt->score[2]);
    printf("\n�ܷ֣�%d",pt->grades);
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
        printf("\n�Ƿ��������,�����Ҫ�˳�ϵͳ����ѡ��'0'�������س���\n");
        printf("\n\n��ѡ��\n");
        scanf("%d",&choice);
    }while(choice!=0);
    return 0;
}