#include<string>
#include <mysql.h>
#include<iostream>
using namespace std;
#ifndef CLASS_H_
#define CLASS_H_
class Stuff
{
private:
	int id;                                   //工号
	int age;                                  //年龄
	int salary;                               //工资
	string tel;                               //电话号码
	string name;                              //姓名
	string gender;                            //性别
 	string department;                        //部门
	string degree;                            //学历
	string addr;                              //居住住址
public:
	Stuff();                                  //默认职工信息的构造函数
	Stuff(int, int, string, string, string, string, string, string);
                                              //录入数据库的构造函数
	void dispInfo();                          //显示职工信息
	void addStuff();                          //录入职工信息
	void modifyStuff();                       //修改职工信息
	void delStuff();                          //删除职工信息
	void saveStuff();                         //保存职工信息
	void searchStuff();                       //查找职工信息
	void sortStuff();                         //排序职工信息
	int sortSalary();                         //根据工资进行排序
	int sortDegree();                         //根据学历进行排序
	int sortAge();
	int searchId();                           //根据工号进行查找
	int searchName();                         //根据姓名进行查找
	int searchDepartment();                   //根据部门进行查找
	int searchDegree(int num);                //根据学历进行查找


	string getAge(int num);                   //获取职工年龄
	string getTel(int numr);                  //获取职工电话
	string getGender(int num);                //获取职工性别
	string getDepartment(int num);            //获取职工部门
	string getDegree(int num);                //获取职工学历

};

class Menu
{
public:
	void welcome();                           //登入后的欢迎界面
	void function_menu();                     //功能菜单界面
	void function_menu_ctr();                 //功能菜单界面控制器
	void login_menu();                        //管理员登入界面
  	void sort_menu();                         //排序菜单界面
	void login_menu_ctr();                    //管理员登入界面控制器
	void search_menu();                       //查找菜单界面
	void search_menu_ctr();                   //查找菜单界面控制器
	int check_menu();                         //管理员登入信息验证界面
	void sign_up();                           //管理员注册界面

};

class Mysql
{
public:
	MYSQL conn;                               //创建数据库连接对象
	MYSQL_FIELD* field;                       //返回字段的指针
	MYSQL_RES* result;                        //返回指令执行结果的指针
	MYSQL_ROW row;                            //返回从数据库取出的数据
	MYSQL_ROW mysql_fetch(const char* sql);   //数据输出函数
	int mysqConnect();                        //数据库连接初始化函数
	string put_field(int num);                //返回字段的函数
};

void pause_out(string);                       //动态输出函数
#endif