#ifndef _STUDENT_H
#define _STUDENT_H

typedef struct node2
{
	char name[20];
	char passwd[16];
	char class[20];
	char age[5];
	char id[5];
	char c[5];
	char math[5];
	char chinese[5];
	char score[8];
	char evaluate[50];
	char evaluate_t[50];
	char homework[80];
	char words[80];

	struct node2 *prev; //前置指针
	struct node2 *next; //后置指针
}student,*student_t;


void student_login(student_t us1);  	//学生登陆函数声明
student_t create_student();         	//创建学生链表函数声明
void destory_student(student_t *phead); //销毁学生链表函数声明
void modify_self_passwd(char *p);		//修改学生自己密码函数声明
void show_homework(student_t tmp);		//查看作业
void write_words(char *p,student_t us1);//学生留言
void read_words(student_t tmp);         //显示留言


int read_error_time(time_t t,time_t t_cur);    //读取输入密码错误时间
void write_error_time(time_t t,time_t t_cur);  //写入输入密码错误时间


void evaluate_teacher(student_t tmp);   //评价老师函数声明

#endif
