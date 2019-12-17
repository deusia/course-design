#include <iostream>
#include <fstream>
#include<windows.h>
#include<cstring>
#include <mysql.h>
#include <cstdio>
#include <iomanip>
#include "class.h"
using namespace std;

/*  *******************************Stuff*******************************  */
/*  *******************************Stuff*******************************  */
/*  *******************************Stuff*******************************  */
Stuff::Stuff()                                    //Stuff对象的默认初始化
{
	id = 0;
	age = 0;
	tel = "0";
	salary = 0;
	name = "Unknown";
	gender = "Unknown";
	department="no belonging";
	degree="Unknown";
	addr = "Unknown";

}
//Stuff对象的初始化，获得工号，姓名，电话，性别，学位，地址和年龄
Stuff::Stuff(int id_, int age_, string tel_, string name_, string gender_, string degree_, string addr_,string department_)
{
	id = id_;
	age = age_;
	tel = tel_;
	salary = 0;
	name = name_;
	gender = gender_;
	department = department_;
	degree = degree_;
	addr = addr_;
}

//显示职工的信息
//将从数据库中获取的数据输出
void Stuff::dispInfo()
{
	Menu me;
	Mysql mys;
	mys.mysqConnect();                              //调用连接到mysql数据库的连接初始化方法
	mys.mysql_fetch("select * from info");
						                            //调用Mysql的数据信息获取方法
	cin.get();
	me.function_menu();
}

//录入职工的信息
void Stuff::addStuff()
{
	Mysql mys;
	Stuff worker;
	Menu me;

	cout << "请输入录入职工的工号";
	string id_;
	cin >> id_;
	if (id_ == "q")                                              //输入q时退出功能菜单界面
	{
		system("cls");
		me.welcome();
		me.function_menu();
		me.function_menu_ctr();
	}
	else
			worker.id = stoi(id_);                                //将字符串转为int类型
	cout << "请输入录入职工的姓名:";
	cin >> worker.name;
	cout << "请输入录入职工的年龄:";
	cin >> worker.age;
	cout << "请输入录入职工的性别:";
	cin >> worker.gender;
	cout << "请输入录入职工的部门:";
	cin >> worker.department;
	cout << "请输入录入职工的工资:";
	cin >> worker.salary;
	cout << "请输入录入职工的学历:";
	cin >> worker.degree;
	cout << "请输入录入职工的联系电话:";
	cin >> worker.tel;
	cout << "请输入录入职工的居住地址:";
	cin >> worker.addr;
	//组合调用数据库的指令，将变量中的值，写入sql语句之中
	char sql[300];
	sprintf_s(sql,300,"insert into info(name,age,gender,tel,salary,department,degree,addr) values('%s','%d','%s','%s','%d','%s','%s','%s')",
		(worker.name).data(), worker.age, (worker.gender).data(), (worker.tel).data(), worker.salary, (worker.department).data(), (worker.degree).data(), (worker.addr).data());
	//data()函数将string类型转换为char类型的字符串类型

	mys.mysqConnect();
	mysql_query(&(mys.conn), sql);
	pause_out("成功录入！！！");

	cout << endl;
	pause_out("请继续您的操作:");
	me.function_menu();
}

//修改职工的信息
void Stuff::modifyStuff()
{
	int id;
	Menu me;
	string name;
	string key;
	Mysql mys;
	mys.mysqConnect();

	char sql[] = "select * from info";
	mysql_query(&(mys.conn), sql);                            //执行所输出的sql语句的命令
	mys.result = mysql_store_result(&(mys.conn));             //将执行的结果返回给mys.result
	mys.field = mysql_fetch_field(mys.result);                //获取的存放在数据库表中的字段


	pause_out("请输入修改的员工工号:");
	cin >> id;

	pause_out("确认修改输入[yes],否则输入[no]");
	string head = "是否修改";
	int q = 0;
	for (int i=1;i<9;)
	{
		string tail = (mys.put_field(i));     //put_field里面存储这字段
		string whole = head + tail+":";       //通过循环将不同字段组合成同一句话
		pause_out(whole);                     //然后输出，从而减少代码量
		cin >> key;
		if (key == "yes")
		{
			pause_out("请输入修改的信息:");
			cin >> name;
			mys.mysqConnect();
			char sql[50];
			sprintf_s(sql, 50, "update info set %s='%s' where id=%d",mys.field[i].name ,(name).data(), id);
			mysql_query(&(mys.conn), sql);
			cout << "修改成功";
			q++;                              //如果修改的话则可以进入下一次循环
			i++;                              //从而修改下一个字段，否则持续同一个循环
		}
		else
		{
			if (key != "no")                  //此为非yes和非no的异常输出的对应
				pause_out("*****请输入[yes]或者[no]*****");
			else
				i++;                          //key为no时，不对该项字段进行修改
		}
	}
	cout << "成功修改职工的信息" << "(" << q << " 项属性修改了）"<<endl<<endl;//如果修改了一项则q+1，可以显示修改的项数
	me.function_menu();
}

//删除职工的信息
void Stuff::delStuff()
{
	Menu me;
	Mysql mys;
	string name;
	pause_out("请输入您要删除的职工的姓名");
	cin >> name;

	char sql[50];
	sprintf_s(sql, 50, "delete from info where name='%s'", name.data());
	
	if (name != "q")
	{
		mys.mysqConnect();
		if (!(mysql_query(&(mys.conn), sql)))//成功归零。如果发生错误，则为非零
		{                                    //摘自Mysql手册
			cin.get();
			cout << "删除成功" << endl;
			cin.get();
			system("cls");
			me.welcome();
			me.function_menu();
		}
	}
	else
	{
		cin.get();cin.get();
		system("cls");
		me.welcome();
		me.function_menu();
	}
}

//保存职工信息
void Stuff::saveStuff()
{
	Mysql mys;
	Menu me;
	mys.mysqConnect();
	mysql_query(&mys.conn, "select * from info");
	mys.result = mysql_store_result(&mys.conn);
	
	ofstream fout;
	fout.open("C:\\Users\\gzc10\\Desktop\\data.txt");  //注意‘\\’的规则，不然路径会出现问题
	while (mys.row = mysql_fetch_row(mys.result))
	{
		string fields;
		for (int i = 0; i < 9; i++)
		{
			fields += mys.put_field(i)+":";  //将多个字段拼起来组合成一条记录
			fields += (mys.row[i]);          //通过string类的重载实现
			fields += "     ";               
		}
		fields += "\n";                      //加上\n可以让一条记录独占一行
		fout << fields;                      //写入创建的文本文档之中
	}
	fout.close();
	pause_out("保存成功！！！");
	system("pause");
	system("cls");
	me.welcome();
	me.function_menu();
}


//分为id和姓名和部门查找
void Stuff::searchStuff()
{
	Menu me;
	me.search_menu();           //调用查找菜单的界面和选择器
	me.search_menu_ctr();       //选择器中包含了查找的方法

}

//根据职工工号进行查找
int Stuff::searchId()
{
	int id;
	pause_out("请输入您要查找的职工的工号");
	cin >> id;
	//输出要查找的信息的姓名

	Mysql mys;
	mys.mysqConnect();
	char sql[80];
	sprintf_s(sql, 80, "select * from info where id=%d", id);
	//通过sprintf_s函数的功能将sql指令组合起来
	mysql_query(&mys.conn, sql);                        //执行mysql命令
	mys.result = mysql_store_result(&mys.conn);
	if (mysql_fetch_row(mys.result))                    //如果获取到内容，则结果为非空
	{                                                   //否则返回NULL
		for (int i = 0; i < 9; i++)
			cout << setw(13) << mys.put_field(i);
		cout << endl;
		mysql_query(&mys.conn, sql);
		mys.result = mysql_store_result(&mys.conn);    //判断语句的条件用掉了第一次存储的数据
		while (mys.row = mysql_fetch_row(mys.result))  //此处的目的时重新获取一次成功取得的内容
		{
			for (int i = 0; i < 9; i++)
			{
				cout << setw(13) << mys.row[i];
			}
			cout << endl;
		}
		return 1;
	}
	else
		pause_out("抱歉，没有该员工的信息。");
	return 0;

	
}

//根据职工姓名进行查找
int Stuff::searchName()
{
	string name;
	pause_out("请输入您要查找的职工的姓名");
	cin >> name;
	//输出要查找的信息的姓名

	Mysql mys;
	mys.mysqConnect();
	char sql[80];
	sprintf_s(sql, 80, "select * from info where name='%s'", (name).data());
	//通过sprintf_s函数的功能将sql指令组合起来
	mysql_query(&mys.conn, sql);                   //执行mysql命令
	mys.result = mysql_store_result(&mys.conn);
	if (mysql_fetch_row(mys.result))               //如果获取到内容，则结果为非空
	{                                              //否则返回NULL
		for (int i = 0; i < 9; i++)
			cout << setw(13) << mys.put_field(i);
		cout << endl;
		mysql_query(&mys.conn, sql);
		mys.result = mysql_store_result(&mys.conn);   //判断语句的条件用掉了第一次存储的数据
		while (mys.row = mysql_fetch_row(mys.result)) //此处的目的时重新获取一次成功取得的内容
		{
			for (int i = 0; i < 9; i++)
			{
				cout << setw(13) << mys.row[i];
			}
			cout << endl;
		}

		return 1;
	}
	//如果没有获取则为NULL执行此处的语句
	else
		pause_out("抱歉，没有该员工的信息。");
	return 0;
}

//根据职工部门进行查找
int Stuff::searchDepartment()
{
	string department;
	pause_out("请输入您要查找的职工的部门");
	cin >> department;
	//输出要查找的信息的部门

	Mysql mys;
	mys.mysqConnect();
	char sql[80];                                           
	sprintf_s(sql, 80, "select * from info where department='%s'", (department).data());
	//通过sprintf_s函数的功能将sql指令组合起来

	mysql_query(&mys.conn, sql);
	mys.result = mysql_store_result(&mys.conn);           //此处的语句和上一个函数的的用法相同
		 if (mysql_fetch_row(mys.result))
		 {
			 for (int i = 0; i < 9; i++)
				 cout << setw(13) << mys.put_field(i);
			 cout << endl;

			 mysql_query(&mys.conn, sql);
			 mys.result = mysql_store_result(&mys.conn);
			 while (mys.row = mysql_fetch_row(mys.result))
			 {
				 for (int i = 0; i < 9; i++)
				 {
					 cout << setw(13) << mys.row[i];
				 }
				 cout << endl;
			 }
			 return 1;

		 }
	else
		pause_out("抱歉，没有该员工的信息。");
	return 0;

}


//排序职工信息
void Stuff::sortStuff()
{
	Menu me;
	me.sort_menu();

}

//根据工资进行排序
int Stuff::sortSalary()
{
	Mysql mys;
	Menu me;
	int option;
	if(!mys.mysqConnect())
		return 0 ;

	pause_out("请选择是升序排列还是降序排列:");
	pause_out("1--升序排列");
	pause_out("2--降序排列");
	cin >> option;
	cout << endl;

	switch (option)
	{
	case 1:
		mys.mysql_fetch("select * from info order by salary asc");
		//通过mysql的指令实现升序排序
		break;
	case 2:
		mys.mysql_fetch("select * from info order by salary desc");
		//通过mysql的指令实现降序排序

		break;
	default:
		break;
	}
	me.sort_menu();
	pause_out("请继续操作:");
	return 1;
}

//根据学历进行排序
int Stuff::sortDegree()
{
	Mysql mys;
	Menu me;
	int option;

	pause_out("请选择是升序排列还是降序排列:");
	pause_out("1--升序排列");
	pause_out("2--降序排列");
	cin >> option;                            //输入选择
	cout << endl;

	for (int i = 0; i < 9; i++)
		cout << setw(10) << mys.put_field(i);
	cout << endl;
	switch (option)
	{
	case 1:
		for (int k = 0; k < 9; k++)
			searchDegree(k);    //searchDegree函数中保存这从第到高的学历顺序
		//此处时从低到高调用
		break;
	case 2:
		for (int j = 8; j >=0; j--)  //重复调用该函数，实现一种选择性的排序
			searchDegree(j);         //从而解决问题，去升序的方法类似
		//此处时从高到底调用
		break;
	default:
		sortDegree();
		break;
	}
	me.sort_menu();
	return 1;
}

//根据年龄进行排序
int Stuff::sortAge()
{
	Mysql mys;
	Menu me;
	int option;
	
	if (!mys.mysqConnect())
		return 0;
	pause_out("请选择是升序排列还是降序排列:");
	pause_out("1--升序排列");
	pause_out("2--降序排列");
	cin >> option;
	if (option == 1)
	{
		const char* sql = "select * from info order by age asc";
		//使用mysql指令实现升序排序
		mys.mysql_fetch(sql);
		me.sort_menu();
	}
	else
	{
		if (option == 2)
		{
			const char* sql = "select * from info order by age desc";
			//使用mysql指令实现降序排序
			mys.mysql_fetch(sql);
			me.sort_menu();
		}
		else
		{
			pause_out("请输入正确的序号:");

			me.sort_menu();
		}

	}

	pause_out("请继续操作:");

	return 1;
}

int Stuff::searchDegree(int num)
{
	Mysql mys;
	mys.mysqConnect();
	const char* sql = "select * from info";
	mysql_query(&(mys.conn), sql);
	mys.result = mysql_store_result(&(mys.conn));

	while (mys.row = mysql_fetch_row(mys.result))
	{
		if (mys.row[7] ==getDegree(num))         //row[7]中存储的是学历
			//getDegree()中存储的是不同的学历
		{
			for (int i = 0; i < 9; i++)
				//如果判断成立则则将该条字段输出
				cout <<setw(10)<< mys.row[i];
			cout << endl;
		}
	}
	return 1;
}

//用于输出学历
string Stuff::getDegree(int num)
{
	char degree[9][10] = { "小学","初中","中专","高中","大专","本科","硕士","博士","博士后" };
	return degree[num];

}

//用于输出性别
string Stuff::getGender(int num)
{
	char gender[2][5] = { "男","女" };
	return gender[num];
}

//用于输出性别
string Stuff::getDepartment(int num)
{
	char gender[2][5] = { "男","女" };
	return gender[num];
}
/*  *******************************Stuff*******************************  */
/*  *******************************Stuff*******************************  */
/*  *******************************Stuff*******************************  */




/*  *******************************Menu*******************************  */
/*  *******************************Menu*******************************  */
/*  *******************************Menu*******************************  */

//显示欢迎界面
void Menu::welcome()
{
	for (int i = 0; i < 120; i++)
		//通过循环达到一种连续输出
		cout << "*";
	cout << endl << endl;
	cout <<setw(65)<< "欢迎您的登入"<<endl<<endl;
	for (int i = 0; i < 120; i++)
		cout << "*";
	cout << endl;
}

//显示功能菜单
void Menu::function_menu()
{
	pause_out("请 根 据 相 应 的 功 能 输 入 对 应 的 序 号：");
	pause_out("职 工 信 息 录 取 <A/a>");
	pause_out("职 工 信 息 浏 览 <B/b>");
	pause_out("职 工 信 息 修 改 <C/c>");
	pause_out("职 工 信 息 查 找 <D/d>");
	pause_out("职 工 信 息 删 除 <E/e>");
	pause_out("职 工 信 息 排 序 <F/f>");
	pause_out("职 工 信 息 保 存 <S/s>");
	pause_out("退 出 登 入 <G/g>");
}

//功能界面选择控制器
void Menu::function_menu_ctr()
{
	pause_out("请输入选择的菜单:");
	Stuff worker;
	char key;
	cin >> key;
	while (key != 'q')                      //通过一个key值判断的循环，来实现一个功能的连续
	{                                       //输入q时强制中断循环退出界面
		key = tolower(key);
		switch (key)
		{
		case 'a':
			worker.addStuff();             //进入信息录入的函数
			break;
		case 'b':
			worker.dispInfo();             //输出所有信息的函数
			break;
		case 'c':
			worker.modifyStuff();          //修改信息的函数
			break; 
		case 'd':
			worker.searchStuff();          //查找信息的函数
			break;	
		case 'e':
			worker.delStuff();             //删除信息的函数
			break;
		case 'f':
			worker.sortStuff();            //排序的函数
			break;
		case 's':
			worker.saveStuff();             //保存信息的函数
			break;

		case 'g':                          //退出登入
			system("cls");                 //清屏后显示登入界面
			login_menu();
			login_menu_ctr();
			break;
		default:
			pause_out("请输入正确的菜单号");  //此处时处理不规范输入的选择
			function_menu();
		}
		cin >> key;
	}
}

//显示登入界面
void Menu::login_menu()
{
	cout << endl << endl;
	cout << setw(70)<<"职  工  信  息  管  理  系  统";
	cout << endl<< endl << endl << endl;
	cout << setw(62) << "管理员登入<A/a>" << endl << endl; 
	cout << setw(62) << "管理员注册<B/b>" << endl << endl;
	cout << setw(60) << "退出系统<C/c>"<<endl;
	cout << endl << endl << endl << endl << endl;
	cout << setw(100) << "18 软嵌3班 顾震超制作" << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "注：当您想要停止所选定的功能时，请按‘q’便会放弃该次操作环节"<<endl;

}

//登入界面选择控制器
void Menu::login_menu_ctr()
{
	char key;
	cin >> key;
	//将大小写都转化为小写，从而解决大小的统一性问题
	key = tolower(key);   
	while (key!='q')
	{
		switch (key)
		{
		case 'a':
			system("cls");
			//登入成功的话返回1，失败则返回0从而决定是否进入系统
			if (check_menu())  
			{
				system("cls");
				welcome();
				function_menu();
				function_menu_ctr();
			}
			else //失败的情况执行下列语句，重新回答登入界面
				system("cls");
				login_menu();
			break;
		case 'b':
			system("cls");
			//进行用户注册
			sign_up();     
			break;
		case 'c':
			//退出登入系统
			pause_out("感谢您的使用！！！");
			exit(0);
			//exit的功能是终止程序的运行，参数0便是正常结束
			break;
		default:
			//输出异常的输入
			cout << "请输入正确的序号";
			break;
		}
		cin >> key;
	}
}

//显示排序菜单
void Menu::sort_menu()
{
	char key;
	Stuff worker;

	pause_out("请 选 择 排 序 方 案:");
	pause_out("1--按 工 资 排 序");
	pause_out("2--按 学 历 排 序");
	pause_out("3--按 年 龄 排 序");
	pause_out("4--返 回 上 一 级 菜 单");

	pause_out("请选择");
	cin >> key;
	while (key != 'q')            //通过key实现留在该级的逗留
	{
		switch (key)
		{
		case '1':
			worker.sortSalary();  //根据工资排序的函数
			break;
		case '2':
			worker.sortDegree();  //根据学历排序的函数
			break;
		case '3':
			worker.sortAge();     //根据年龄排序的函数
			break;
		case '4':                 //返回到上一级
			system("cls");
			welcome();
			function_menu();
			function_menu_ctr();
			break;
		default:
			cout << "请输入正确的序号";
		}
		cin >> key;
	}
}

//检验登入界面
//该函数返回一个int类型的值，来反映是否找到数据库中的该用户
int  Menu::check_menu()
{
	string username;          //登入的用户名
	string password;          //登入的密码
	cout << endl << endl;
	cout << setw(70) << "职  工  信  息  管  理  系  统";
	cout << endl << endl << endl << endl;
	cout << setw(60) << "请输出用户名:" << endl << endl;
	cout << "                                               " ;
	cin >> username;
	cout << endl;
	cout << setw(58) << "请输出密码:" << endl << endl;
	cout << "                                               ";
	cin >> password;


	Mysql mys;
	mys.mysqConnect();

	const char* sql = "select * from user";
	mysql_query(&mys.conn, sql);
	//从数据库中获取用户名和密码
	mys.result = mysql_store_result(&mys.conn);
	//对每一条用户名和密码进行比对，如果找到则返回1
	//否侧全部比对饭后没有的话则返回0
	while (mys.row = mysql_fetch_row(mys.result))
	{
		if (mys.row[1] == username)
			if (mys.row[2] == password)
				return 1;

	}
	//结束全部比对后，仍然没有匹配的，则执行下列语句
	cout << setw(48)<< endl << endl;
	pause_out("你输入的登入信息有误，请重试。");
	system("pause");
	return 0;
}

//显示查找菜单界面
void Menu::search_menu()
{
	pause_out("请 选 择 查 找 方 式:");
	pause_out("1--工号查找");
	pause_out("2--姓名查找");
	pause_out("3--部门查找");
	pause_out("4--返回上一级");
	cout << "请输入:";
}

//查找菜单界面控制器
void Menu::search_menu_ctr()
{
	Menu me;
	Stuff worker;

	char option;
	cin >> option;
	while (option!='q')                        //通过option实现逗留在该级
	{
		switch (option)
		{
		case '1':
			worker.searchId();                 //根据工号查找的函数
			break;
		case '2':
			worker.searchName();               //根据姓名查找的函数
			break;
		case '3':
			worker.searchDepartment();         //根据部门查找的函数
			break;
		case '4':                              //返回上一级菜单
			system("cls");
			me.welcome();
			me.function_menu();
			me.function_menu_ctr();
			break;
		default:
			pause_out("请输入正确的序号:");
			break;
		}
		me.search_menu();
		cin >> option;

	}

}


//用户注册界面
void Menu::sign_up()
{
	Mysql mys;
	string username;                 //注册的用户名
	string password;                 //注册的密码
	string repassword;               //注册的密码验证

	cout << endl << endl;
	cout << setw(76) << "职  工  信  息  管  理  系  统  注  册";
	cout << endl << endl << endl << endl;
	cout << setw(60) << "请输出用户名:" << endl << endl;
	cout << "                                               ";
	cin >> username;
	cout << endl;
	cout << setw(58) << "请输出密码:" << endl << endl;
	cout << "                                               ";
	cin >> password;
	cout << endl;
	cout << setw(62) << "请再次输出密码:" << endl << endl;
	cout << "                                               ";
	cin >> repassword;

	if (password==repassword)
		//如果密码验证成功的话执行将用户信息存入数据库的指令
	{
		char sql[100];
		sprintf_s(sql, 100,"insert into user(username,password) values('%s','%s')", (username).data(), (password).data());
		//通过sprintf_s把变量的值和sql语句组合在一起

		//初始化数据库
		mys.mysqConnect();
		//执行sql指令
		mysql_query(&mys.conn, sql);


		//指令执行成功返回零，该处运用的是该函数的返回值的相反数
		if (!mysql_query(&mys.conn, sql))  		{
			pause_out("注册成功");
			system("pause");
		}
		else
		{
			pause_out("注册失败");
			system("pause");
		}
		system("cls");
		login_menu();
		login_menu_ctr();
	}
	else
		pause_out("输出的信息有误");
}

/*  *******************************Menu*******************************  */
/*  *******************************Menu*******************************  */
/*  *******************************Menu*******************************  */


/*  *******************************Mysql*******************************  */
/*  *******************************Mysql*******************************  */
/*  *******************************Mysql*******************************  */

//连接到本地数据库并初始化的方法
int Mysql::mysqConnect()
{
	const char user[] = "root";                    //数据库系统的主机名
	const char pswd[] = "123";                     //数据库的密码
	const char host[] = "localhost";               //数据库的站点
	const char table[] = "manage_system";          //数据库的名称
	unsigned int port = 3306;                      //服务占用的端口号

	if (mysql_init(&conn) == NULL)                 //如果数据库对象初始化失败
	{
		cout << "连接初始化错误";
		//则返回0
		return 0;                                  
	}

	if (mysql_real_connect(&conn, host, user, pswd, table, port, NULL, 0))//检验是否真的连接上数据库
		//设置mysql的字符集
		mysql_query(&conn, "SET NAMES gbk");    
	else
	{
		cout << "连接到数据库是发生错误";
		return 0;
	}
	return 1;
}

//获取数据库中的职工们的信息
//该函数接受一个const char* 类型的参数，返回 MYSQL_ROW的对象
MYSQL_ROW  Mysql::mysql_fetch(const char* sql)
{
	//MYSQL_ROW row;
	mysql_query(&conn, sql);
	result = mysql_store_result(&conn);

	for (int i = 0; i < 9; i++)
		cout << setw(13) << put_field(i);
	cout << endl;

	while (row = mysql_fetch_row(result))
	{
		int control = 0;
		while (control < 9)
		{
			cout << setw(13) << row[control];
			control++;
		}
		cout << endl;
	}
	return mysql_fetch_row(result);
}

//从低到高一次存放不同的学历
//该函数接受一个int类型的值，返回一个字符串
string Mysql::put_field(int num)
{
	char field[9][10] = {"工号", "姓名" , "年龄" , "性别" ,  "电话" ,  "工资" , "部门" ,  "学历" ,  "居住地址" };
	return field[num];
}

/*  *******************************Mysql*******************************  */
/*  *******************************Mysql*******************************  */
/*  *******************************Mysql*******************************  */

//动态输出函数
//该函数接受一个字符串
void pause_out(string str)
{
	long count = 10000000;
	//通过让一个让为0的数自增到一个很大的值来延迟输出一个字符的时间
	//达到一种动态输出的效果
	int i = 0;
	while (str[i] != '\0')
	{
		while (count)
			count--;
		cout << str[i];
		i++;
		count = 10000000;
	}
	cout << endl;
}
