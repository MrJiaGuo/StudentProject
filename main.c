#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "teacher.h"
#include "student.h"
#include "manager.h"

//设计主函数来选择登陆方式
int main()
{
	
	int select=0;
	
	teacher_t us = create_teacher();  //创建老师链表
	student_t us1 = create_student(); //创建学生链表
	open_teacher_file(us);			  //打开老师数据文件并读入链表
	open_student_file(us1);			  //打开学生数据文件并读入链表

	while(1)
	{   
		    printf("\033[0;32m ☣★★★★★★★★★ 正方教务学生管理系统 ★★★★★★★★☣\n\033[0m");
			printf("\033[0;36m ☣     ♡      1.管理员登陆       ♡       ☣\n\033[0m");
			printf("\033[0;31m ☣     ♡      2.教师登陆         ♡       ☣\n\033[0m");
			printf("\033[0;34m ☣     ♡      3.学生登陆         ♡       ☣\n\033[0m");
			printf("\033[0;33m ☣     ♡      4.退出系统         ♡       ☣\n\033[0m");		
	        printf("\033[0;38m ❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦\n\033[0m");
		
		while(scanf("%d",&select)!=1){       
            printf("输入错误，请重新输入:");
            scanf("%*[^\n]");
            scanf("%*c");
        }
        scanf("%*[^\n]");
        scanf("%*c");
		
		switch(select){
            case 1:
			    manager_login(us,us1);   //管理员登陆界面函数
                break;
				
            case 2:
			    teacher_login(us,us1);	//教师登陆界面函数
                break;
				
            case 3:
			    student_login(us1);	//学生登陆界面函数
                break;
				
            case 4:
               	close_teacher_file(us);  //把操作完的老师链表数据重新写入老师文件
				close_student_file(us1); //把操作完的学生链表数据重新写入学生文件
				exit(0);	
                break;
								
            default:
                printf("选择选项不存在，请重新选择!\n");

        }
		
        getchar();
		system("clear");
	}
	return 0;
}