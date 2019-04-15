#ifndef _MANAGER_H
#define _MANAGER_H
#include "teacher.h"
#include "student.h"

typedef unsigned int uint;

typedef struct node
{
	char name[20];
	char passwd[16];
	struct node *prev; //前置指针
	struct node *next; //后置指针
}manager,*manager_t;

//管理员相关函数声明

void open_teacher_file(teacher_t us);
void open_student_file(student_t us1);
void close_teacher_file(teacher_t us);
void close_student_file(student_t us1);

void manager_login(teacher_t us,student_t us1);
manager_t create_manager();
void destory_manager(manager_t *phead);

/********************************教师相关函数声明*****************************/

//向链表插入老师新结点
teacher_t insert_teacher(teacher_t  p,const char *name,const char *passwd,const char *class,const char * age);
//添加老师函数
void add_teacher(teacher_t  us);
//按名字查找老师函数
teacher_t search_by_name(teacher_t head,const char *name);
void find_teacher(teacher_t  us);

//按名字删除老师函数
int delete_teacher_by_name(teacher_t head,const char *name);
void delete_teacher(teacher_t  us);

//修改教师密码函数
void modify_teacher(teacher_t  us);

//遍历老师函数
void travel_teacher(teacher_t  us);
void change_teacher(teacher_t tmp);

/********************************学生相关函数声明*****************************/
//向链表插入学生新结点
student_t insert_student(student_t  q,const char *name,const char *passwd,const char *class,const char * age,const char * id,const char *c,const char *math,const char * chinese,const char *evaluate,const char * evaluate_t,const char *homework,const char *words,const char * score);
//添加学生函数
void add_student(student_t us1);

//按名字查找学生函数
student_t search_by_name1(student_t head,const char *name);
void find_student(student_t us1);

//按名字删除学生函数
int delete_student_by_name(student_t head,const char *name);
void delete_student(student_t us1);

//修改学生密码函数
void modify_student(student_t us1);

//遍历学生函数
void travel_student(student_t us1);
void change_student(student_t tmp);
void change_student1(student_t tmp);


#endif
