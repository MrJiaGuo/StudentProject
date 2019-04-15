#ifndef _TEACHER_H
#define _TEACHER_H

#include "student.h"

typedef struct node1
{
	char name[20];
	char passwd[16];
	char class[20];
	char age[5];

	struct node1 *prev; //前置指针
	struct node1 *next; //后置指针
}teacher,*teacher_t;


void teacher_login(teacher_t us,student_t us1);   //教师登陆函数声明
teacher_t create_teacher();                       //创建新的教师链表声明
void destory_teacher(teacher_t *phead);           //销毁链表
void modify_self_teacher_passwd(char *p);         //修改自己密码函数声明

void travel_self_student(char *,student_t us1);   //遍历自己班的学生函数声明
void find_self_student(char *,student_t us1);     //查找自己班学生的函数声明
void scanf_student_score(char *,student_t us1);   //录入自己班学生成绩的函数声明
void evaluate_student(char *,student_t us1);	  //评价自己班学生的函数声明
void show_student_evaluate(char *,student_t us1); //显示学生对自己评价的函数声明
void student_homework(char *,student_t us1);	  //布置学生作业函数声明

void sort_student(student_t us1,int select);       //学生排序


#endif
