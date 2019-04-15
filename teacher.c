#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "student.h"
#include "manager.h"
#include "teacher.h"

teacher_t create_teacher()   //创建新的教师链表函数定义
{
	//构造头节点
	teacher_t head = (teacher_t)malloc(sizeof(teacher));
	if(head){
		//头节点的前置和后置都指向自己表示空链表
		head->name[0] = '\0';
		head->passwd[0] = '\0';
		head->class[0]='\0';
		head->age[0]='\0';
		head->prev = head;
		head->next = head;
	}

	return head;
}

void destory_teacher(teacher_t *phead)   //销毁教师链表函数定义
{
	teacher_t head = (*phead)->next,p = NULL;

	while(head!=*phead){
		p = head;
		head = head->next;
		free(p);
	}
	free(head);

	*phead = NULL;
	p = NULL;   
}

void modify_self_teacher_passwd(char *p)  //修改教师自己密码函数定义
{
	char modify_passwd[16];
	char modify_passwd2[16];
	printf("请输入修改登陆密码：");
	fgets(modify_passwd,16,stdin);

	printf("请再输入一遍确认：");
	fgets(modify_passwd2,16,stdin);

	if(strcmp(modify_passwd,modify_passwd2)==0)
	{
		strcpy(p,modify_passwd);
		printf("修改成功！\n");
	}
	else
		printf("两次输入的密码不匹配，修改失败！\n");

}

void sort_student(student_t us1,int select)   //学生排序
{
	student_t tmp = us1->next,p = NULL,q = NULL;
	//将链表置空
	us1->next = us1;
	us1->prev = us1;

	while(tmp!=us1){

		//保存原链表中tmp的下一个节点
		q = tmp->next;
		if(select == 1)		
			//找到tmp插入的位置
			for(p=us1->prev;p!=us1&&atoi(p->score)>atoi(tmp->score);p=p->prev);
		else if(select == 2)
			for(p=us1->prev;p!=us1&&atoi(p->id)<atoi(tmp->id);p=p->prev);
		else if(select == 3)
			for(p=us1->prev;p!=us1&&atoi(p->c)>atoi(tmp->c);p=p->prev);
		else if(select == 4)
			for(p=us1->prev;p!=us1&&atoi(p->math)>atoi(tmp->math);p=p->prev);
		else if(select == 5)
			for(p=us1->prev;p!=us1&&atoi(p->chinese)>atoi(tmp->chinese);p=p->prev);
		
		//将tmp插入到p之后
		tmp->prev = p;
		tmp->next = p->next;
		p->next->prev = tmp;
		p->next = tmp;

		//将tmp指向要插入的下一个节点
		tmp = q;

	}
}


void travel_self_student(char *s,student_t us1)		//遍历自己班的学生函数定义
{
	int choice = 0;
	printf("请选择排序查看方式（1-5）：\n");
	printf("1:按总分查看！\n");
	printf("2:按学号查看！\n");
	printf("3:按c语言成绩查看！\n");
	printf("4:按数学成绩查看！\n");
	printf("5:按语文成绩查看！\n");

	while(scanf("%d",&choice)!=1)
	{
		printf("输入错误，请重新输入:");
		scanf("%*[^\n]");
		scanf("%*c");
	}
	scanf("%*[^\n]");
	scanf("%*c");

	if(choice==1)
		sort_student(us1,1);
	
	else if(choice==2)
		sort_student(us1,2);
	
	else if(choice==3)
		sort_student(us1,3);
	
	else if(choice==4)
		sort_student(us1,4);
	
	else if(choice==5)
		sort_student(us1,5);
	
	else
	{	
		printf("暂时没有该查看方式！\n");
		return;
	}

	student_t tmp = us1->prev;
	printf("学生姓名 学生密码 学生班级 学生年龄 学生学号 c语言成绩 数学成绩 语文成绩 总分   评价\n");
	while(tmp!=us1)
	{
		if(strcmp(s,tmp->class)==0)
		{
			printf("\033[0;32m☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼\033[0m\n");
			change_student1(tmp);
		}
		tmp = tmp->prev;
	}
	printf("\n");

}

void find_self_student(char *p,student_t us1)		 //查找自己班学生的函数声明
{
	int flag=0;
	char find_name[20];
	student_t tmp = us1->next;

	printf("请输入要查找学生的名字：");
	fgets(find_name,20,stdin);

	printf("该名学生信息如下:\n");
	while(tmp!=us1){
		if(strcmp(p,tmp->class)==0&&strcmp(find_name,tmp->name)==0)
		{
			flag=1;
			printf("学生姓名 学生密码 学生班级 学生年龄 学生学号 c语言成绩 数学成绩 语文成绩 总分   评价\n");
			change_student1(tmp);
		}
		tmp = tmp->next;
	}
	if(flag==0)
		printf("本班没有该名学生！\n");

}

void scanf_student_score(char *p,student_t us1)		//录入自己班学生成绩的函数声明
{
	int sum;
	int flag=0;
	char find_name[20];
	student_t tmp = us1->next;

	printf("请输入要录入成绩学生的名字：");
	fgets(find_name,20,stdin);

	while(tmp!=us1){
		if(strcmp(p,tmp->class)==0&&strcmp(find_name,tmp->name)==0)
		{
			flag=1;
			printf("请输入c语言成绩：");
			fgets(tmp->c,5,stdin);

			printf("请输入数学成绩：");
			fgets(tmp->math,5,stdin);

			printf("请输入语文成绩：");
			fgets(tmp->chinese,5,stdin);

			sum = atoi(tmp->c)+atoi(tmp->math)+atoi(tmp->chinese);
			sprintf(tmp->score,"%d\n",sum);

			printf("录入完成!\n");

		}
		tmp = tmp->next;
	}
	if(flag==0)
		printf("本班没有该名学生！\n");

}

void evaluate_student(char *p,student_t us1)		//评价自己班学生的函数定义
{
	int flag=0;
	char find_name[20];
	char evaluate[50];
	student_t tmp = us1->next;

	printf("请输入要评价学生的名字：");
	fgets(find_name,20,stdin);

	while(tmp!=us1){
		if(strcmp(p,tmp->class)==0&&strcmp(find_name,tmp->name)==0)
		{
			flag=1;
			printf("请输入评价：");
			fgets(tmp->evaluate,50,stdin);
			printf("评价成功！\n");

		}
		tmp = tmp->next;
	}
	if(flag==0)
		printf("本班没有该名学生！\n");

}

void show_student_evaluate(char *p,student_t us1)		//显示学生对自己评价的函数定义
{
	char name[20];
	char evaluate_t[50];
	student_t tmp = us1->next;

	while(tmp!=us1)
	{
		if(strcmp(p,tmp->class)==0)
		{
			strcpy(name,tmp->name);
			strcpy(evaluate_t,tmp->evaluate_t);
			name[strlen(name)-1] = '\0';
			evaluate_t[strlen(evaluate_t)-1] = '\0';

			printf("学生姓名:%s   学生评价:%s\n",name,evaluate_t);      
		}
		tmp = tmp->next;
	}

}

void student_homework(char *p,student_t us1)
{
	int flag = 0;
	char homework[80];
	student_t tmp = us1->next;
	
	printf("请输入公告内容：");
	fgets(homework,80,stdin);
	
	while(tmp!=us1){
		if(strcmp(p,tmp->class)==0)
		{
			flag = 1;
			strcpy(tmp->homework,homework);
		}
		tmp = tmp->next;
	}
	if(flag==0)
		printf("本班还没有学生！\n");
	else
		printf("发布成功！\n");
	
}




void teacher_login(teacher_t us,student_t us1)   //教师登陆函数定义
{
	char name[20];
	char passwd[20];

	printf("请输入教师登陆姓名：");
	fgets(name,20,stdin);

	printf("请输入登陆密码：");
	fgets(passwd,16,stdin);

	teacher_t tmp=search_by_name(us,name);

	if(tmp!=NULL&&strcmp(tmp->passwd,passwd)==0)
	{
		printf("即将进入教师主界面！欢迎您！\n");
		sleep(1);
		system("clear");

	}
	else
	{
		printf("用户名或者密码错误！\n");
		return;
	}
	
    name[strlen(name)-1] = '\0';  //去掉'\n'
	
	int select=0;
	while(1)
	{   
		printf("\033[0;32m ★★★★★★★★★★★ 欢迎来到教师主界面 ★★★★★★★★★★★★\n\033[0m");
		printf(" ☣               欢迎您，%s             ☣\n",             name);
		printf("\033[0;36m ☣     ♡        1. 查看个人信息      ♡      ☣\n\033[0m");
		printf("\033[0;31m ☣     ♡        2. 修改登陆密码      ♡      ☣\n\033[0m");
		printf("\033[0;33m ☣     ♡        3. 查看学生信息      ♡      ☣\n\033[0m");
		printf("\033[0;34m ☣     ♡        4. 评价学生          ♡      ☣\n\033[0m");
		printf("\033[0;37m ☣     ♡        5. 查找学生信息      ♡      ☣\n\033[0m");
		printf("\033[0;35m ☣     ♡        6. 录入学生成绩      ♡      ☣\n\033[0m");
		printf("\033[0;31m ☣     ♡        7. 显示学生评价      ♡      ☣\n\033[0m");
		printf("\033[0;33m ☣     ♡        8. 发布班级公告      ♡      ☣\n\033[0m");	
		printf("\033[0;36m ☣     ♡        9. 返回登陆界面      ♡      ☣\n\033[0m");
		printf("\033[0;33m ❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦\n\033[0m");

		while(scanf("%d",&select)!=1){       
			printf("输入错误，请重新输入:");
			scanf("%*[^\n]");
			scanf("%*c");
		}
		scanf("%*[^\n]");
		scanf("%*c");

		switch(select){
			case 1:
				printf("教师个人信息如下：\n");
				change_teacher(tmp);
				break;

			case 2:
				modify_self_teacher_passwd(tmp->passwd);
				break;

			case 3:
				travel_self_student(tmp->class,us1);
				break;

			case 4:
				evaluate_student(tmp->class,us1);
				break;

			case 5:
				find_self_student(tmp->class,us1);
				break;

			case 6:
				scanf_student_score(tmp->class,us1);
				break;
				
			case 7:
				show_student_evaluate(tmp->class,us1);
				break;	
				
			case 8:
				student_homework(tmp->class,us1);
				break;	

			case 9:
				printf("\033[0;32m ~(@^_^@)~按任意键返回登陆界面！\n\033[0m");
				return;
				break;				

			default:
				printf("选择选项不存在，请重新选择!\n");

		}

		getchar();
		system("clear");
	}
	return;
}
