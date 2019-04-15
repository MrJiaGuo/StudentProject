#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "manager.h"

void open_teacher_file(teacher_t us)  //打开老师数据文件函数的定义
{
	//定义几个老师的属性变量
	char name[20]={};
	char passwd[16]={};
	char class[20]={};
	char age[5]={};

	//打开老师数据文件
	FILE *fp = fopen("teacher.dat","r");
	if(!fp)
	{
		perror("fopen_teacher");
		exit(0);
	}
	
	/*
	fgets，从文件结构体指针stream中读取数据，每次读取一行。读取的数据保存在buf指向的字符数组中，每次最多读取bufsize-1个字符（第bufsize个字符赋'\0'），如果文件中的该行，不足bufsize-1个字符，则读完该行就结束。如若该行（包括最后一个换行符）的字符数超过bufsize-1，则fgets只返回一个不完整的行，但是，缓冲区总是以NULL字符结尾，对fgets的下一次调用会继续读该行。函数成功将返回buf，失败或读到文件结尾返回NULL。因此我们不能直接通过fgets的返回值来判断函数是否是出错而终止的，应该借助feof函数或者ferror函数来判断。
	*/
 
	//从文件里把数据插入链表
	while(fgets(name,20,fp))  
	{
		fgets(passwd,16,fp);
		fgets(class,20,fp);
		fgets(age,5,fp);
		insert_teacher(us,name,passwd,class,age);
	}
	fclose(fp);
}

void open_student_file(student_t us1)    //打开学生数据文件函数的定义
{
	//定义学生的属性变量
	char name[20]={};
	char passwd[16]={};
	char class[20]={};
	char age[5]={};
	char id[5];
	char c[5];
	char math[5];
	char chinese[5];
	char score[8];
	char evaluate[50];
	char evaluate_t[50];
	char homework[80];
	char words[80];

	//打开老师数据文件
	FILE *fp1 = fopen("student.dat","r");
	if(!fp1)
	{
		perror("fopen_student");
		exit(0);
	}

	//从文件里把数据插入链表
	while(fgets(name,20,fp1))
	{
		fgets(passwd,16,fp1);
		fgets(class,20,fp1);
		fgets(age,5,fp1);
		fgets(id,5,fp1);
		fgets(c,5,fp1);
		fgets(math,5,fp1);
		fgets(chinese,5,fp1);
		fgets(evaluate,50,fp1);
		fgets(evaluate_t,50,fp1);
		fgets(homework,80,fp1);
		fgets(words,80,fp1);
		fgets(score,8,fp1);

		insert_student(us1,name,passwd,class,age,id,c,math,chinese,evaluate,evaluate_t,homework,words,score);
	}
	fclose(fp1);
}

void close_teacher_file(teacher_t us)  //重新向老师文件写入数据的函数定义
{
	FILE *fp = fopen("teacher.dat","w");
	if(!fp)
	{
		perror("fopen_teacher");
		exit(0);
	}
	 //创建结构体指针变量
	teacher_t tmp = us->next;   
	//把数据重新从链表里写入文件
	while(tmp!=us){
		fprintf(fp,"%s",tmp->name);
		fprintf(fp,"%s",tmp->passwd);
		fprintf(fp,"%s",tmp->class);
		fprintf(fp,"%s",tmp->age);
		tmp = tmp->next;
	}

	destory_teacher(&us);
	fclose(fp);	
}

void close_student_file(student_t us1)   //重新向学生文件写入数据的函数定义
{
	FILE *fp1 = fopen("student.dat","w");
	if(!fp1){
		perror("fopen_student");
		exit(0);
	}

	 //创建结构体指针变量
	student_t tmp1 = us1->next;
	//把数据重新从链表里写入文件
	while(tmp1!=us1)
	{
		fprintf(fp1,"%s",tmp1->name);
		fprintf(fp1,"%s",tmp1->passwd);
		fprintf(fp1,"%s",tmp1->class);
		fprintf(fp1,"%s",tmp1->age);
		fprintf(fp1,"%s",tmp1->id);
		fprintf(fp1,"%s",tmp1->c);
		fprintf(fp1,"%s",tmp1->math);
		fprintf(fp1,"%s",tmp1->chinese);
		fprintf(fp1,"%s",tmp1->evaluate);
		fprintf(fp1,"%s",tmp1->evaluate_t);
		fprintf(fp1,"%s",tmp1->homework);
		fprintf(fp1,"%s",tmp1->words);
		fprintf(fp1,"%s",tmp1->score);

		tmp1 = tmp1->next;
	}

	destory_student(&us1);
	fclose(fp1);
}


manager_t create_manager()  //创建管理员链表
{
	//构造头节点
	manager_t head = (manager_t)malloc(sizeof(manager));
	if(head){
		//头节点的前置和后置都指向自己表示空链表
		head->name[0] = '\0';
		head->passwd[0] = '\0';
		head->prev = head;
		head->next = head;
	}
	return head;
}

void destory_manager(manager_t *phead)  //释放管理员内存空间
{
	manager_t head = (*phead)->next,p = NULL;


	while(head!=*phead){
		p = head;
		head = head->next;
		free(p);
	}
	free(head);

	*phead = NULL;   //*phead是一个指针，指向地址，**phead是一个值
	p = NULL;   
}

/**********************************教师相关函数定义***************************************/
//向链表插入老师新结点
teacher_t insert_teacher(teacher_t  p,const char *name,const char *passwd,const char *class,const char * age)
{
	if(!p)
		return NULL;

	//构造新节点
	teacher_t  newnode = (teacher_t )malloc(sizeof(teacher));
	if(newnode){
		strcpy(newnode->name,name);
		strcpy(newnode->passwd,passwd);
		strcpy(newnode->class,class);
		strcpy(newnode->age,age);
		//将新节点的前置指向p,后置指向p的下一个节点
		newnode->prev = p;
		newnode->next = p->next;
		//将p的后置指向新节点，将P的下一个节点的前置指向新节点
		p->next->prev = newnode;
		p->next = newnode;

	}

	return newnode;
}

//添加老师函数
void add_teacher(teacher_t  us)
{
	char name[20];
	char passwd[16];
	char class[20];
	char age[5];
	char evaluate_t[50];

	printf("请输入要添加教师的姓名:");
	fgets(name,20,stdin);
	
	//限制名字长度
	while(strlen(name)==19&&us->name[18]!='\n')
	{
		printf("输入的用户名过长，请重新输入:");
		scanf("%*[^\n]");  //scanf("%*[^\n]");
		scanf("%*c");		//scanf("%*c");
		fgets(name,20,stdin);
	}

	printf("请输入要添加教师账号的密码：");
	fgets(passwd,16,stdin);
	
	//限制密码长度
	while(strlen(passwd)==15&&passwd[14]!='\n')
	{
		printf("输入的密码过长，请重新输入:");
		scanf("%*[^\n]");
		scanf("%*c");
		fgets(passwd,16,stdin);
	}

	printf("请输入要添加教师的所在班级：");
	fgets(class,20,stdin);

	printf("请输入要添加教师的年龄：");
	fgets(age,5,stdin);

	//把新数据写入教师文件
	insert_teacher(us,name,passwd,class,age);
	printf("添加成功！\n");
}


teacher_t search_by_name(teacher_t head,const char *name)
{
	//略过无效头节点
	teacher_t tmp = head->next;

	while(tmp!=head){
		if(strcmp(name,tmp->name)==0)
			return tmp;
		tmp = tmp->next;
	}

	return NULL;
}


//按名字删除老师函数
int delete_teacher_by_name(teacher_t head,const char *name)
{
	int i = 0;
	teacher_t tmp = NULL;

	while(tmp = search_by_name(head,name)){
		//要删除节点的后一个节点的前置指针指向要删除节点的前一个节点
		tmp->next->prev = tmp->prev;
		//要删除节点的前一个节点的后置指针指向要删除节点的后一个节点
		tmp->prev->next = tmp->next;
		//释放要删除的节点
		free(tmp);
		tmp = NULL;
		i++;
	}

	return i;
}

void delete_teacher(teacher_t  us)
{
	char del_name[20];

	printf("请输入要删除的教师名字:");
	fgets(del_name,20,stdin);

	//调用删除函数删除节点，返回的是删除个数
	if(delete_teacher_by_name(us,del_name)==0){
		printf("没有该教师，删除失败!\n");
		return;
	}
	else
	{
		printf("删除成功！\n");
	}

}

//按名字查找老师函数
void find_teacher(teacher_t  head)
{
	int flag=0;
	char find_name[20];
	
	//创建结构体指针变量
	teacher_t tmp = head->next;

	printf("请输入要查找的教师名字：");
	fgets(find_name,20,stdin);

	while(tmp!=head){
		if(strcmp(find_name,tmp->name)==0)  //判断名字是否存在
		{
			flag=1;
			printf("查找到的教师的信息如下：\n");
			change_teacher(tmp);           //找到名字就输出
		}

		tmp = tmp->next;
	}
	if(flag==0)
		printf("没有该老师的信息！\n");

}

//修改教师密码函数
void modify_teacher(teacher_t  head)
{

	char modify_name[20];
	char modify_passwd[16];
	char modify_passwd2[16];
	
	teacher_t tmp =NULL;
	
	printf("请输入要修改密码的教师名字:");
	fgets(modify_name,20,stdin);

	//判断教师是否存在
	if((tmp=search_by_name(head,modify_name))==NULL)  
	{
		printf("没有该教师!\n");
		return;
	}
	else
	{
		printf("请输入修改教师的登陆密码：");
		fgets(modify_passwd,16,stdin);

		printf("请再输入一遍确认：");
		fgets(modify_passwd2,16,stdin);

		//判读第一次密码和第二次密码是否相等，相等就修改成功
		if(strcmp(modify_passwd,modify_passwd2)==0)
		{
			strcpy(tmp->passwd,modify_passwd);
			printf("修改成功！\n");
		}
		else
			printf("两次输入的密码不匹配，修改失败！\n");
		return;

	}
}

void change_teacher(teacher_t tmp)
{
	char name[20];
	char passwd[16];
	char class[20];
	char age[5];
	//把老师结点里的参数复制到新变量输出
	strcpy(name,tmp->name);
	strcpy(passwd,tmp->passwd);
	strcpy(class,tmp->class);
	strcpy(age,tmp->age);
	
	//去掉每个属性里的'\n',然后输出
	name[strlen(name)-1] = '\0';
	passwd[strlen(passwd)-1] = '\0';
	class[strlen(class)-1] = '\0';
	age[strlen(age)-1] = '\0';

	printf("教师姓名：%s 教师密码：%s 教师班级：%s 教师年龄：%s\n",name,passwd,class,age);

}

//遍历老师函数
void travel_teacher(teacher_t head)
{

	//略过无效头节点
	teacher_t tmp = head->next;

	while(tmp!=head){
		change_teacher(tmp);
		tmp = tmp->next;
	}
	printf("\n");


}
/*************************************************教师相关函数定义结束******************************************/



/*************************************************学生相关函数定义******************************************/
//向链表插入学生新结点
student_t search_by_name1(student_t head,const char *name)
{
	//略过无效头节点
	student_t tmp = head->next;

	while(tmp!=head){
		if(strcmp(name,tmp->name)==0)
			return tmp;
		tmp = tmp->next;
	}

	return NULL;
}

//添加学生函数
student_t insert_student(student_t  q,const char *name,const char *passwd,const char *class,const char * age,const char * id,const char *c,const char *math,const char * chinese,const char *evaluate,const char *evaluate_t ,const char *homework,const char *words,const char * score)
{
	if(!q)
		return NULL;
	student_t p=q->next;   //创建结构体指针变量

	while(p!=q)
		p = p->next;
	//构造新节点
	student_t  newnode = (student_t )malloc(sizeof(student));
	if(newnode){
		strcpy(newnode->name,name);
		strcpy(newnode->passwd,passwd);
		strcpy(newnode->class,class);
		strcpy(newnode->age,age);
		strcpy(newnode->id,id);
		strcpy(newnode->c,c);
		strcpy(newnode->math,math);
		strcpy(newnode->chinese,chinese);
		strcpy(newnode->evaluate,evaluate);
		strcpy(newnode->evaluate_t,evaluate_t);
		strcpy(newnode->homework,homework);
		strcpy(newnode->words,words);
		strcpy(newnode->score,score);

		//将新节点的前置指向p,后置指向p的下一个节点
		newnode->prev = p;
		newnode->next = p->next;
		//将p的后置指向新节点，将P的下一个节点的前置指向新节点
		p->next->prev = newnode;
		p->next = newnode;

	}

	return newnode;
}

//添加学生函数
void add_student(student_t  us1)
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
	int sum=0;
	char c1=' ';
	
	student_t tmp = us1->next;
	
	printf("请输入要添学生的姓名:");
	fgets(name,20,stdin);
	while(strlen(name)==19&&name[18]!='\n')
	{
		printf("输入的用户名过长，请重新输入:");
		scanf("%*[^\n]");
		scanf("%*c");
		fgets(name,20,stdin);
	}

	printf("请输入要添加学生账号的密码：");
	fgets(passwd,16,stdin);
	while(strlen(passwd)==15&&passwd[14]!='\n')
	{
		printf("输入的密码过长，请重新输入:");
		scanf("%*[^\n]");
		scanf("%*c");
		fgets(passwd,16,stdin);
	}

	printf("请输入要添加学生的所在班级：");
	fgets(class,20,stdin);

	printf("请输入要添加学生的年龄：");
	fgets(age,5,stdin);

	printf("请输入要添加学生的学号：");
	fgets(id,5,stdin);
	
	while(tmp!=us1)
	{
		if(strcmp(id,tmp->id)==0&&strcmp(class,tmp->class)==0)
		{	
			printf("该班的该学号已存在，请重新操作！\n");
			sleep(1);
			return;
		}
		
		tmp = tmp->next;
	}
	
	//把一些管理员不需要操作的属性置为" \n"
	sprintf(c,"%c\n",c1);
	sprintf(math,"%c\n",c1);
	sprintf(chinese,"%c\n",c1);

	//将字符类型的成绩转换成整形
	sum = atoi(c)+atoi(math)+atoi(chinese); 
	sprintf(score,"%d\n",sum);

	sprintf(evaluate,"%c\n",c1);
	sprintf(evaluate_t,"%c\n",c1);
	sprintf(homework,"%c\n",c1);
	sprintf(words,"%c\n",c1);

	//调用插入函数，把数据插入链表
	insert_student(us1,name,passwd,class,age,id,c,math,chinese,evaluate,evaluate_t,homework,words,score);

	printf("添加成功！\n");
}

//按名字删除学生函数
int delete_student_by_name(student_t head,const char *name)
{
	int i = 0;
	student_t tmp = NULL;

	while(tmp = search_by_name1(head,name)){
		//要删除节点的后一个节点的前置指针指向要删除节点的前一个节点
		tmp->next->prev = tmp->prev;
		//要删除节点的前一个节点的后置指针指向要删除节点的后一个节点
		tmp->prev->next = tmp->next;
		//释放要删除的节点
		free(tmp);
		tmp = NULL;
		i++;
	}

	return i;
}

void delete_student(student_t  us1)
{
	char del_name[20];

	printf("请输入要删除的学生名字:");
	fgets(del_name,20,stdin);

	if(delete_student_by_name(us1,del_name)==0){    //判断学生是否存在
		printf("没有该学生，删除失败!\n");
		return;
	}
	else
	{
		printf("删除成功！\n");
	}
}

//按名字查找学生函数
void find_student(student_t  head)
{
	//判断标志，找到置1
	int flag=0;
	char find_name[20];
	student_t tmp = head->next;

	printf("请输入要查找的学生名字：");
	fgets(find_name,20,stdin);

	while(tmp!=head){
		if(strcmp(find_name,tmp->name)==0)  //判断名字是否存在
		{
			flag=1;
			printf("查找到的学生的信息如下：\n");
			printf("学生姓名 学生密码 学生班级 学生年龄 学生学号 c语言成绩 数学成绩 语文成绩 总分   评价\n");
			change_student(tmp);
		}

		tmp = tmp->next;
	}
	
	if(flag==0)
		printf("没有该学生的信息！\n");
}

//修改学生密码函数
void modify_student(student_t  head)
{
	char modify_name[20];
	char modify_passwd[16];
	char modify_passwd2[16];
	student_t tmp =NULL;
	printf("请输入要修改密码的学生名字:");
	fgets(modify_name,20,stdin);

	if((tmp=search_by_name1(head,modify_name))==NULL)
	{
		printf("没有该学生!\n");
		return;
	}
	else
	{
		printf("请输入修改学生的登陆密码：");
		fgets(modify_passwd,16,stdin);

		printf("请再输入一遍确认：");
		fgets(modify_passwd2,16,stdin);

		if(strcmp(modify_passwd,modify_passwd2)==0)
		{
			strcpy(tmp->passwd,modify_passwd);
			printf("修改成功！\n");
		}
		else
			printf("两次输入的密码不匹配，修改失败！\n");
		return;

	}

}

void change_student(student_t tmp)
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

	strcpy(name,tmp->name);
	strcpy(passwd,tmp->passwd);
	strcpy(class,tmp->class);
	strcpy(age,tmp->age);
	strcpy(id,tmp->id);
	strcpy(c,tmp->c);
	strcpy(math,tmp->math);
	strcpy(chinese,tmp->chinese);
	strcpy(score,tmp->score);
	strcpy(evaluate,tmp->evaluate);

	//去掉每个字符属性里的换行符
	name[strlen(name)-1] = '\0';
	passwd[strlen(passwd)-1] = '\0';
	class[strlen(class)-1] = '\0';
	age[strlen(age)-1] = '\0';
	id[strlen(id)-1] = '\0';
	c[strlen(c)-1] = '\0';
	math[strlen(math)-1] = '\0';
	chinese[strlen(chinese)-1] = '\0';
	score[strlen(score)-1] = '\0';
	evaluate[strlen(evaluate)-1] = '\0';
	
	printf("%-12s %-10s %-6s %-10s %-8s %-8s %-8s %-6s %-5s %-5s\n",name,passwd,class,age,id,c,math,chinese,score,evaluate);
}

void change_student1(student_t tmp)
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

	strcpy(name,tmp->name);
	strcpy(passwd,"*****");
	strcpy(class,tmp->class);
	strcpy(age,tmp->age);
	strcpy(id,tmp->id);
	strcpy(c,tmp->c);
	strcpy(math,tmp->math);
	strcpy(chinese,tmp->chinese);
	strcpy(score,tmp->score);
	strcpy(evaluate,tmp->evaluate);

	//去掉每个字符属性里的换行符
	name[strlen(name)-1] = '\0';
	//passwd[strlen(passwd)-1] = '\0';
	class[strlen(class)-1] = '\0';
	age[strlen(age)-1] = '\0';
	id[strlen(id)-1] = '\0';
	c[strlen(c)-1] = '\0';
	math[strlen(math)-1] = '\0';
	chinese[strlen(chinese)-1] = '\0';
	score[strlen(score)-1] = '\0';
	evaluate[strlen(evaluate)-1] = '\0';
	
	printf("%-12s %-10s %-6s %-10s %-8s %-8s %-8s %-6s %-5s %-5s\n",name,passwd,class,age,id,c,math,chinese,score,evaluate);
}

//遍历学生函数
void travel_student(student_t head)
{
	//略过无效头节点
	student_t tmp = head->next;
	printf("学生姓名 学生密码 学生班级 学生年龄 学生学号 c语言成绩 数学成绩 语文成绩 总分   评价\n");
	while(tmp!=head){
		printf("\033[0;32m☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼ ☼\033[0m\n");
		change_student(tmp);  //调用去掉'\n'的函数，显示信息
		tmp = tmp->next;
	}
	printf("\n");


}

/*************************************************学生相关函数定义结束******************************************/

void manager_login(teacher_t us,student_t us1) //管理员登陆函数定义
{
	char name[20];
	char *passwd=NULL;
	
	printf("请输入管理员的账号：");
	fgets(name,20,stdin);
	name[strlen(name)-1] = '\0';//去掉最后的换行符

	passwd = getpass("请输入管理员的密码："); //调用不回显密码函数，输入密码

	if(strcmp(name,"admin")==0&&strcmp(passwd,"12345")==0)
	{
		printf("即将进入管理员主界面！欢迎您！\n");
		sleep(1);
		system("clear");	
	}
	else
	{
		printf("用户名或者密码错误！\n");
		return;
	}
	
	int select=0;
	while(1)
	{   
		printf("\033[0;32m ★★★★★★★★★  欢迎来到管理员界面 ★★★★★★★★★★\n\033[0m");
		printf("\033[0;37m ☣     ☺       1. 添加教师        ☺     ☣\n\033[0m");
		printf("\033[0;35m ☣     ☺       2. 删除教师        ☺     ☣\n\033[0m");
		printf("\033[0;33m ☣     ☺       3. 修改教师信息    ☺     ☣\n\033[0m");
		printf("\033[0;32m ☣     ☺       4. 查找教师        ☺     ☣\n\033[0m");	
		printf("\033[0;36m ☣     ☺       5. 显示所有教师    ☺     ☣\n\033[0m");
		printf("\033[0;31m ☣     ☺       6. 添加学生        ☺     ☣\n\033[0m");
		printf("\033[0;34m ☣     ☺       7. 删除学生        ☺     ☣\n\033[0m");
		printf("\033[0;33m ☣     ☺       8. 修改学生信息    ☺     ☣\n\033[0m");
		printf("\033[0;34m ☣     ☺       9. 查找学生        ☺     ☣\n\033[0m");
		printf("\033[0;35m ☣     ☺       10.显示所有学生    ☺     ☣\n\033[0m");
		printf("\033[0;37m ☣     ☺       11.返回登录界面    ☺     ☣\n\033[0m");
		printf("\033[0;31m ❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦❦\n\033[0m");

		while(scanf("%d",&select)>2){       
			printf("输入错误，请重新输入:");
			scanf("%*[^\n]");
			scanf("%*c");
		}
		scanf("%*[^\n]");
		scanf("%*c");

		switch(select){
			case 1:
				add_teacher(us);
				break;

			case 2:
				delete_teacher(us);
				break;

			case 3:
				modify_teacher(us);
				break;

			case 4:
				find_teacher(us);
				break;

			case 5:
				travel_teacher(us);
				break;

			case 6:
				add_student(us1);
				break;

			case 7:
				delete_student(us1);
				break;

			case 8:
				modify_student(us1);
				break;

			case 9:
				find_student(us1);
				break;

			case 10:
				travel_student(us1);
				break;

			case 11:
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
