#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "manager.h"
#include "student.h"
#include "teacher.h"

student_t tmp;
time_t t = 0,t_cur = 0;
int n = 0;

//创建学生链表函数定义
student_t create_student()
{
	student_t head = (student_t)malloc(sizeof(student));     //构造头节点
	if(head){
		//头节点的前置和后置都指向自己表示空链表
		head->name[0] = '\0';
		head->passwd[0] = '\0';
		head->class[0]='\0';
		head->age[0]='\0';
		head->c[0]='\0';
		head->math[0]='\0';
		head->chinese[0]='\0';
		head->evaluate[0]='\0';
		head->evaluate_t[0]='\0';
		head->prev = head;
		head->next = head;
	}
	return head;
}

//销毁学生链表函数定义
void destory_student(student_t *phead)
{
	student_t head = (*phead)->next,p = NULL;


	while(head!=*phead){
		p = head;
		head = head->next;
		free(p);
	}
	free(head);

	*phead = NULL;
	p = NULL;   
}

//修改学生自己密码函数定义
void modify_self_passwd(char *p)
{
	char modify_passwd[16];
	char modify_passwd2[16];
	printf("请输入修改登陆密码：");
	fgets(modify_passwd,16,stdin);

	printf("请再输入一遍确认：");
	fgets(modify_passwd2,16,stdin);

	//判断修改两次密码是否相等
	if(strcmp(modify_passwd,modify_passwd2)==0)
	{
		strcpy(p,modify_passwd);
		printf("修改成功！\n");
	}
	else
		printf("两次输入的密码不匹配，修改失败！\n");

}

int read_error_time(time_t t,time_t t_cur)
{
    FILE *fp_t = fopen("time.dat","r");
    if(!fp_t)
	{
        perror("fopen_time");
    }
    else
	{
        t_cur = time(0);//当前时间
        fread(&t,sizeof(t),1,fp_t);//上次出错时间
		    
		fclose(fp_t);
        return t_cur-t;  //返回时间差
    }
        
}

void write_error_time(time_t t,time_t t_cur)
{
	FILE *fp_t = fopen("time.dat","w");
    if(!fp_t){
        perror("fopen_time");
        exit(0);
    }

    t = time(0);
    fwrite(&t,sizeof(t),1,fp_t); //写入输入三次密码错误的开始时间
    fclose(fp_t);
	
}

//评价老师函数定义
void evaluate_teacher(student_t tmp)
{
	if(strcmp(tmp->evaluate_t," \n")==0)
	{
		printf("请输入评价内容：");
		fgets(tmp->evaluate_t,50,stdin);
		printf("评价成功！\n");
		return;
	}
	else
	{
		printf("你已经评价过！\n");
		return;
	}
}

//查看学生作业函数定义
void show_homework(student_t tmp)
{
	printf("今日班级公告：%s\n",tmp->homework);
	
}

//写留言函数
void write_words(char *p,student_t us1)
{
	int flag = 0;
	char name[20];
	student_t tmp = us1->next;
	printf("请输入要留言的学生名字：");
	fgets(name,20,stdin);
	
	//查找班级有没有该名同学，有的话可以留言
	while(tmp!=us1)
	{
		if(strcmp(p,tmp->class)==0&&strcmp(name,tmp->name)==0)
		{
			flag = 1;
			printf("请输入留言内容：");
			fgets(tmp->words,80,stdin);
			printf("留言成功！\n");
			
		}
		tmp = tmp->next;
	}
	if(flag==0)
		printf("本班没有该名同学！");	
}


//学生读留言函数
void read_words(student_t tmp)
{
	if(strcmp(tmp->words," \n")==0)
		printf("暂时没有同学给你留言！\n");
	else
	    printf("某同学给你的留言是：%s\n",tmp->words);
	
}



//学生登陆函数定义
void student_login(student_t us1)
{
	
	char name[20];
	char passwd[16];

	//判断时间是否够10s，不够就返回主界面
	int error_time = read_error_time(t,t_cur);
	if(error_time<10)
	{
		printf("连续输入密码错误3次，请稍后再试!\n");
		return;
	}
	
	do{
			printf("请输入学生账号：");
			fgets(name,20,stdin);

			printf("请输入学生密码：");
			fgets(passwd,16,stdin);
			
			tmp=search_by_name1(us1,name);

			if(tmp!=NULL&&strcmp(tmp->passwd,passwd)==0)   //判断学生账号是否存在
			{
				printf("即将进入学生主界面！欢迎您！\n");
				sleep(1);
				system("clear");
				break;

			}
			else
			{
				printf("用户名或者密码错误！\n");
				n++;
			}
			
	}while(n<3);
	
	if(n == 3)
	{
		write_error_time(t,t_cur);
		printf("连续3次用户名或者密码输入错误，请10s后再试！\n");
		n = 0;
		return;
	}
	
	name[strlen(name)-1] = '\0';  //去掉姓名后的'\n'
	
	int select=0;
	while(1)
	{   
		printf("\033[0;32m ★★★★★★★★★ 欢迎来到学生界面  ★★★★★★★★★★★★★\n\033[0m");
		printf(" ☣            欢迎您，%s同学           ☣\n",             name);
		printf("\033[0;36m ☣      ☞      1. 查看信息         ☜     ☣\n\033[0m");
		printf("\033[0;31m ☣      ☞      2. 修改密码         ☜     ☣\n\033[0m");
		printf("\033[0;33m ☣      ☞      3. 评价教师         ☜     ☣\n\033[0m");
		printf("\033[0;34m ☣      ☞      4. 查看公告         ☜     ☣\n\033[0m");
		printf("\033[0;35m ☣      ☞      5. 学生留言         ☜     ☣\n\033[0m");
		printf("\033[0;34m ☣      ☞      6. 查看留言         ☜     ☣\n\033[0m");
		printf("\033[0;37m ☣      ☞      7. 返回登录界面     ☜     ☣\n\033[0m");
		printf("\033[0;35m ❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦\n\033[0m");

		while(scanf("%d",&select)!=1){       
			printf("输入错误，请重新输入:");
			scanf("%*[^\n]");
			scanf("%*c");
		}
		scanf("%*[^\n]");
		scanf("%*c");

		switch(select){
			case 1:
				printf("个人学生信息如下：\n");
				printf("学生姓名 学生密码 学生班级 学生年龄 学生学号 c语言成绩 数学成绩 语文成绩 总分   评价\n");
				change_student(tmp);
				break;

			case 2:
				modify_self_passwd(tmp->passwd);
				break;

			case 3:
				evaluate_teacher(tmp);
				break;
				
			case 4:
				show_homework(tmp);
				break;
				
			case 5:
				write_words(tmp->class,us1);
				break;
				
			case 6:
				read_words(tmp);
				break;

			case 7:
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
