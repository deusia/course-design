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
Stuff::Stuff()                                    //Stuff�����Ĭ�ϳ�ʼ��
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
//Stuff����ĳ�ʼ������ù��ţ��������绰���Ա�ѧλ����ַ������
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

//��ʾְ������Ϣ
//�������ݿ��л�ȡ���������
void Stuff::dispInfo()
{
	Menu me;
	Mysql mys;
	mys.mysqConnect();                              //�������ӵ�mysql���ݿ�����ӳ�ʼ������
	mys.mysql_fetch("select * from info");
						                            //����Mysql��������Ϣ��ȡ����
	cin.get();
	me.function_menu();
}

//¼��ְ������Ϣ
void Stuff::addStuff()
{
	Mysql mys;
	Stuff worker;
	Menu me;

	cout << "������¼��ְ���Ĺ���";
	string id_;
	cin >> id_;
	if (id_ == "q")                                              //����qʱ�˳����ܲ˵�����
	{
		system("cls");
		me.welcome();
		me.function_menu();
		me.function_menu_ctr();
	}
	else
			worker.id = stoi(id_);                                //���ַ���תΪint����
	cout << "������¼��ְ��������:";
	cin >> worker.name;
	cout << "������¼��ְ��������:";
	cin >> worker.age;
	cout << "������¼��ְ�����Ա�:";
	cin >> worker.gender;
	cout << "������¼��ְ���Ĳ���:";
	cin >> worker.department;
	cout << "������¼��ְ���Ĺ���:";
	cin >> worker.salary;
	cout << "������¼��ְ����ѧ��:";
	cin >> worker.degree;
	cout << "������¼��ְ������ϵ�绰:";
	cin >> worker.tel;
	cout << "������¼��ְ���ľ�ס��ַ:";
	cin >> worker.addr;
	//��ϵ������ݿ��ָ��������е�ֵ��д��sql���֮��
	char sql[300];
	sprintf_s(sql,300,"insert into info(name,age,gender,tel,salary,department,degree,addr) values('%s','%d','%s','%s','%d','%s','%s','%s')",
		(worker.name).data(), worker.age, (worker.gender).data(), (worker.tel).data(), worker.salary, (worker.department).data(), (worker.degree).data(), (worker.addr).data());
	//data()������string����ת��Ϊchar���͵��ַ�������

	mys.mysqConnect();
	mysql_query(&(mys.conn), sql);
	pause_out("�ɹ�¼�룡����");

	cout << endl;
	pause_out("��������Ĳ���:");
	me.function_menu();
}

//�޸�ְ������Ϣ
void Stuff::modifyStuff()
{
	int id;
	Menu me;
	string name;
	string key;
	Mysql mys;
	mys.mysqConnect();

	char sql[] = "select * from info";
	mysql_query(&(mys.conn), sql);                            //ִ���������sql��������
	mys.result = mysql_store_result(&(mys.conn));             //��ִ�еĽ�����ظ�mys.result
	mys.field = mysql_fetch_field(mys.result);                //��ȡ�Ĵ�������ݿ���е��ֶ�


	pause_out("�������޸ĵ�Ա������:");
	cin >> id;

	pause_out("ȷ���޸�����[yes],��������[no]");
	string head = "�Ƿ��޸�";
	int q = 0;
	for (int i=1;i<9;)
	{
		string tail = (mys.put_field(i));     //put_field����洢���ֶ�
		string whole = head + tail+":";       //ͨ��ѭ������ͬ�ֶ���ϳ�ͬһ�仰
		pause_out(whole);                     //Ȼ��������Ӷ����ٴ�����
		cin >> key;
		if (key == "yes")
		{
			pause_out("�������޸ĵ���Ϣ:");
			cin >> name;
			mys.mysqConnect();
			char sql[50];
			sprintf_s(sql, 50, "update info set %s='%s' where id=%d",mys.field[i].name ,(name).data(), id);
			mysql_query(&(mys.conn), sql);
			cout << "�޸ĳɹ�";
			q++;                              //����޸ĵĻ�����Խ�����һ��ѭ��
			i++;                              //�Ӷ��޸���һ���ֶΣ��������ͬһ��ѭ��
		}
		else
		{
			if (key != "no")                  //��Ϊ��yes�ͷ�no���쳣����Ķ�Ӧ
				pause_out("*****������[yes]����[no]*****");
			else
				i++;                          //keyΪnoʱ�����Ը����ֶν����޸�
		}
	}
	cout << "�ɹ��޸�ְ������Ϣ" << "(" << q << " �������޸��ˣ�"<<endl<<endl;//����޸���һ����q+1��������ʾ�޸ĵ�����
	me.function_menu();
}

//ɾ��ְ������Ϣ
void Stuff::delStuff()
{
	Menu me;
	Mysql mys;
	string name;
	pause_out("��������Ҫɾ����ְ��������");
	cin >> name;

	char sql[50];
	sprintf_s(sql, 50, "delete from info where name='%s'", name.data());
	
	if (name != "q")
	{
		mys.mysqConnect();
		if (!(mysql_query(&(mys.conn), sql)))//�ɹ����㡣�������������Ϊ����
		{                                    //ժ��Mysql�ֲ�
			cin.get();
			cout << "ɾ���ɹ�" << endl;
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

//����ְ����Ϣ
void Stuff::saveStuff()
{
	Mysql mys;
	Menu me;
	mys.mysqConnect();
	mysql_query(&mys.conn, "select * from info");
	mys.result = mysql_store_result(&mys.conn);
	
	ofstream fout;
	fout.open("C:\\Users\\gzc10\\Desktop\\data.txt");  //ע�⡮\\���Ĺ��򣬲�Ȼ·�����������
	while (mys.row = mysql_fetch_row(mys.result))
	{
		string fields;
		for (int i = 0; i < 9; i++)
		{
			fields += mys.put_field(i)+":";  //������ֶ�ƴ������ϳ�һ����¼
			fields += (mys.row[i]);          //ͨ��string�������ʵ��
			fields += "     ";               
		}
		fields += "\n";                      //����\n������һ����¼��ռһ��
		fout << fields;                      //д�봴�����ı��ĵ�֮��
	}
	fout.close();
	pause_out("����ɹ�������");
	system("pause");
	system("cls");
	me.welcome();
	me.function_menu();
}


//��Ϊid�������Ͳ��Ų���
void Stuff::searchStuff()
{
	Menu me;
	me.search_menu();           //���ò��Ҳ˵��Ľ����ѡ����
	me.search_menu_ctr();       //ѡ�����а����˲��ҵķ���

}

//����ְ�����Ž��в���
int Stuff::searchId()
{
	int id;
	pause_out("��������Ҫ���ҵ�ְ���Ĺ���");
	cin >> id;
	//���Ҫ���ҵ���Ϣ������

	Mysql mys;
	mys.mysqConnect();
	char sql[80];
	sprintf_s(sql, 80, "select * from info where id=%d", id);
	//ͨ��sprintf_s�����Ĺ��ܽ�sqlָ���������
	mysql_query(&mys.conn, sql);                        //ִ��mysql����
	mys.result = mysql_store_result(&mys.conn);
	if (mysql_fetch_row(mys.result))                    //�����ȡ�����ݣ�����Ϊ�ǿ�
	{                                                   //���򷵻�NULL
		for (int i = 0; i < 9; i++)
			cout << setw(13) << mys.put_field(i);
		cout << endl;
		mysql_query(&mys.conn, sql);
		mys.result = mysql_store_result(&mys.conn);    //�ж����������õ��˵�һ�δ洢������
		while (mys.row = mysql_fetch_row(mys.result))  //�˴���Ŀ��ʱ���»�ȡһ�γɹ�ȡ�õ�����
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
		pause_out("��Ǹ��û�и�Ա������Ϣ��");
	return 0;

	
}

//����ְ���������в���
int Stuff::searchName()
{
	string name;
	pause_out("��������Ҫ���ҵ�ְ��������");
	cin >> name;
	//���Ҫ���ҵ���Ϣ������

	Mysql mys;
	mys.mysqConnect();
	char sql[80];
	sprintf_s(sql, 80, "select * from info where name='%s'", (name).data());
	//ͨ��sprintf_s�����Ĺ��ܽ�sqlָ���������
	mysql_query(&mys.conn, sql);                   //ִ��mysql����
	mys.result = mysql_store_result(&mys.conn);
	if (mysql_fetch_row(mys.result))               //�����ȡ�����ݣ�����Ϊ�ǿ�
	{                                              //���򷵻�NULL
		for (int i = 0; i < 9; i++)
			cout << setw(13) << mys.put_field(i);
		cout << endl;
		mysql_query(&mys.conn, sql);
		mys.result = mysql_store_result(&mys.conn);   //�ж����������õ��˵�һ�δ洢������
		while (mys.row = mysql_fetch_row(mys.result)) //�˴���Ŀ��ʱ���»�ȡһ�γɹ�ȡ�õ�����
		{
			for (int i = 0; i < 9; i++)
			{
				cout << setw(13) << mys.row[i];
			}
			cout << endl;
		}

		return 1;
	}
	//���û�л�ȡ��ΪNULLִ�д˴������
	else
		pause_out("��Ǹ��û�и�Ա������Ϣ��");
	return 0;
}

//����ְ�����Ž��в���
int Stuff::searchDepartment()
{
	string department;
	pause_out("��������Ҫ���ҵ�ְ���Ĳ���");
	cin >> department;
	//���Ҫ���ҵ���Ϣ�Ĳ���

	Mysql mys;
	mys.mysqConnect();
	char sql[80];                                           
	sprintf_s(sql, 80, "select * from info where department='%s'", (department).data());
	//ͨ��sprintf_s�����Ĺ��ܽ�sqlָ���������

	mysql_query(&mys.conn, sql);
	mys.result = mysql_store_result(&mys.conn);           //�˴���������һ�������ĵ��÷���ͬ
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
		pause_out("��Ǹ��û�и�Ա������Ϣ��");
	return 0;

}


//����ְ����Ϣ
void Stuff::sortStuff()
{
	Menu me;
	me.sort_menu();

}

//���ݹ��ʽ�������
int Stuff::sortSalary()
{
	Mysql mys;
	Menu me;
	int option;
	if(!mys.mysqConnect())
		return 0 ;

	pause_out("��ѡ�����������л��ǽ�������:");
	pause_out("1--��������");
	pause_out("2--��������");
	cin >> option;
	cout << endl;

	switch (option)
	{
	case 1:
		mys.mysql_fetch("select * from info order by salary asc");
		//ͨ��mysql��ָ��ʵ����������
		break;
	case 2:
		mys.mysql_fetch("select * from info order by salary desc");
		//ͨ��mysql��ָ��ʵ�ֽ�������

		break;
	default:
		break;
	}
	me.sort_menu();
	pause_out("���������:");
	return 1;
}

//����ѧ����������
int Stuff::sortDegree()
{
	Mysql mys;
	Menu me;
	int option;

	pause_out("��ѡ�����������л��ǽ�������:");
	pause_out("1--��������");
	pause_out("2--��������");
	cin >> option;                            //����ѡ��
	cout << endl;

	for (int i = 0; i < 9; i++)
		cout << setw(10) << mys.put_field(i);
	cout << endl;
	switch (option)
	{
	case 1:
		for (int k = 0; k < 9; k++)
			searchDegree(k);    //searchDegree�����б�����ӵڵ��ߵ�ѧ��˳��
		//�˴�ʱ�ӵ͵��ߵ���
		break;
	case 2:
		for (int j = 8; j >=0; j--)  //�ظ����øú�����ʵ��һ��ѡ���Ե�����
			searchDegree(j);         //�Ӷ�������⣬ȥ����ķ�������
		//�˴�ʱ�Ӹߵ��׵���
		break;
	default:
		sortDegree();
		break;
	}
	me.sort_menu();
	return 1;
}

//���������������
int Stuff::sortAge()
{
	Mysql mys;
	Menu me;
	int option;
	
	if (!mys.mysqConnect())
		return 0;
	pause_out("��ѡ�����������л��ǽ�������:");
	pause_out("1--��������");
	pause_out("2--��������");
	cin >> option;
	if (option == 1)
	{
		const char* sql = "select * from info order by age asc";
		//ʹ��mysqlָ��ʵ����������
		mys.mysql_fetch(sql);
		me.sort_menu();
	}
	else
	{
		if (option == 2)
		{
			const char* sql = "select * from info order by age desc";
			//ʹ��mysqlָ��ʵ�ֽ�������
			mys.mysql_fetch(sql);
			me.sort_menu();
		}
		else
		{
			pause_out("��������ȷ�����:");

			me.sort_menu();
		}

	}

	pause_out("���������:");

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
		if (mys.row[7] ==getDegree(num))         //row[7]�д洢����ѧ��
			//getDegree()�д洢���ǲ�ͬ��ѧ��
		{
			for (int i = 0; i < 9; i++)
				//����жϳ������򽫸����ֶ����
				cout <<setw(10)<< mys.row[i];
			cout << endl;
		}
	}
	return 1;
}

//�������ѧ��
string Stuff::getDegree(int num)
{
	char degree[9][10] = { "Сѧ","����","��ר","����","��ר","����","˶ʿ","��ʿ","��ʿ��" };
	return degree[num];

}

//��������Ա�
string Stuff::getGender(int num)
{
	char gender[2][5] = { "��","Ů" };
	return gender[num];
}

//��������Ա�
string Stuff::getDepartment(int num)
{
	char gender[2][5] = { "��","Ů" };
	return gender[num];
}
/*  *******************************Stuff*******************************  */
/*  *******************************Stuff*******************************  */
/*  *******************************Stuff*******************************  */




/*  *******************************Menu*******************************  */
/*  *******************************Menu*******************************  */
/*  *******************************Menu*******************************  */

//��ʾ��ӭ����
void Menu::welcome()
{
	for (int i = 0; i < 120; i++)
		//ͨ��ѭ���ﵽһ���������
		cout << "*";
	cout << endl << endl;
	cout <<setw(65)<< "��ӭ���ĵ���"<<endl<<endl;
	for (int i = 0; i < 120; i++)
		cout << "*";
	cout << endl;
}

//��ʾ���ܲ˵�
void Menu::function_menu()
{
	pause_out("�� �� �� �� Ӧ �� �� �� �� �� �� Ӧ �� �� �ţ�");
	pause_out("ְ �� �� Ϣ ¼ ȡ <A/a>");
	pause_out("ְ �� �� Ϣ � �� <B/b>");
	pause_out("ְ �� �� Ϣ �� �� <C/c>");
	pause_out("ְ �� �� Ϣ �� �� <D/d>");
	pause_out("ְ �� �� Ϣ ɾ �� <E/e>");
	pause_out("ְ �� �� Ϣ �� �� <F/f>");
	pause_out("ְ �� �� Ϣ �� �� <S/s>");
	pause_out("�� �� �� �� <G/g>");
}

//���ܽ���ѡ�������
void Menu::function_menu_ctr()
{
	pause_out("������ѡ��Ĳ˵�:");
	Stuff worker;
	char key;
	cin >> key;
	while (key != 'q')                      //ͨ��һ��keyֵ�жϵ�ѭ������ʵ��һ�����ܵ�����
	{                                       //����qʱǿ���ж�ѭ���˳�����
		key = tolower(key);
		switch (key)
		{
		case 'a':
			worker.addStuff();             //������Ϣ¼��ĺ���
			break;
		case 'b':
			worker.dispInfo();             //���������Ϣ�ĺ���
			break;
		case 'c':
			worker.modifyStuff();          //�޸���Ϣ�ĺ���
			break; 
		case 'd':
			worker.searchStuff();          //������Ϣ�ĺ���
			break;	
		case 'e':
			worker.delStuff();             //ɾ����Ϣ�ĺ���
			break;
		case 'f':
			worker.sortStuff();            //����ĺ���
			break;
		case 's':
			worker.saveStuff();             //������Ϣ�ĺ���
			break;

		case 'g':                          //�˳�����
			system("cls");                 //��������ʾ�������
			login_menu();
			login_menu_ctr();
			break;
		default:
			pause_out("��������ȷ�Ĳ˵���");  //�˴�ʱ�����淶�����ѡ��
			function_menu();
		}
		cin >> key;
	}
}

//��ʾ�������
void Menu::login_menu()
{
	cout << endl << endl;
	cout << setw(70)<<"ְ  ��  ��  Ϣ  ��  ��  ϵ  ͳ";
	cout << endl<< endl << endl << endl;
	cout << setw(62) << "����Ա����<A/a>" << endl << endl; 
	cout << setw(62) << "����Աע��<B/b>" << endl << endl;
	cout << setw(60) << "�˳�ϵͳ<C/c>"<<endl;
	cout << endl << endl << endl << endl << endl;
	cout << setw(100) << "18 ��Ƕ3�� ��������" << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "ע��������Ҫֹͣ��ѡ���Ĺ���ʱ���밴��q���������ôβ�������"<<endl;

}

//�������ѡ�������
void Menu::login_menu_ctr()
{
	char key;
	cin >> key;
	//����Сд��ת��ΪСд���Ӷ������С��ͳһ������
	key = tolower(key);   
	while (key!='q')
	{
		switch (key)
		{
		case 'a':
			system("cls");
			//����ɹ��Ļ�����1��ʧ���򷵻�0�Ӷ������Ƿ����ϵͳ
			if (check_menu())  
			{
				system("cls");
				welcome();
				function_menu();
				function_menu_ctr();
			}
			else //ʧ�ܵ����ִ��������䣬���»ش�������
				system("cls");
				login_menu();
			break;
		case 'b':
			system("cls");
			//�����û�ע��
			sign_up();     
			break;
		case 'c':
			//�˳�����ϵͳ
			pause_out("��л����ʹ�ã�����");
			exit(0);
			//exit�Ĺ�������ֹ��������У�����0������������
			break;
		default:
			//����쳣������
			cout << "��������ȷ�����";
			break;
		}
		cin >> key;
	}
}

//��ʾ����˵�
void Menu::sort_menu()
{
	char key;
	Stuff worker;

	pause_out("�� ѡ �� �� �� �� ��:");
	pause_out("1--�� �� �� �� ��");
	pause_out("2--�� ѧ �� �� ��");
	pause_out("3--�� �� �� �� ��");
	pause_out("4--�� �� �� һ �� �� ��");

	pause_out("��ѡ��");
	cin >> key;
	while (key != 'q')            //ͨ��keyʵ�����ڸü��Ķ���
	{
		switch (key)
		{
		case '1':
			worker.sortSalary();  //���ݹ�������ĺ���
			break;
		case '2':
			worker.sortDegree();  //����ѧ������ĺ���
			break;
		case '3':
			worker.sortAge();     //������������ĺ���
			break;
		case '4':                 //���ص���һ��
			system("cls");
			welcome();
			function_menu();
			function_menu_ctr();
			break;
		default:
			cout << "��������ȷ�����";
		}
		cin >> key;
	}
}

//����������
//�ú�������һ��int���͵�ֵ������ӳ�Ƿ��ҵ����ݿ��еĸ��û�
int  Menu::check_menu()
{
	string username;          //������û���
	string password;          //���������
	cout << endl << endl;
	cout << setw(70) << "ְ  ��  ��  Ϣ  ��  ��  ϵ  ͳ";
	cout << endl << endl << endl << endl;
	cout << setw(60) << "������û���:" << endl << endl;
	cout << "                                               " ;
	cin >> username;
	cout << endl;
	cout << setw(58) << "���������:" << endl << endl;
	cout << "                                               ";
	cin >> password;


	Mysql mys;
	mys.mysqConnect();

	const char* sql = "select * from user";
	mysql_query(&mys.conn, sql);
	//�����ݿ��л�ȡ�û���������
	mys.result = mysql_store_result(&mys.conn);
	//��ÿһ���û�����������бȶԣ�����ҵ��򷵻�1
	//���ȫ���ȶԷ���û�еĻ��򷵻�0
	while (mys.row = mysql_fetch_row(mys.result))
	{
		if (mys.row[1] == username)
			if (mys.row[2] == password)
				return 1;

	}
	//����ȫ���ȶԺ���Ȼû��ƥ��ģ���ִ���������
	cout << setw(48)<< endl << endl;
	pause_out("������ĵ�����Ϣ���������ԡ�");
	system("pause");
	return 0;
}

//��ʾ���Ҳ˵�����
void Menu::search_menu()
{
	pause_out("�� ѡ �� �� �� �� ʽ:");
	pause_out("1--���Ų���");
	pause_out("2--��������");
	pause_out("3--���Ų���");
	pause_out("4--������һ��");
	cout << "������:";
}

//���Ҳ˵����������
void Menu::search_menu_ctr()
{
	Menu me;
	Stuff worker;

	char option;
	cin >> option;
	while (option!='q')                        //ͨ��optionʵ�ֶ����ڸü�
	{
		switch (option)
		{
		case '1':
			worker.searchId();                 //���ݹ��Ų��ҵĺ���
			break;
		case '2':
			worker.searchName();               //�����������ҵĺ���
			break;
		case '3':
			worker.searchDepartment();         //���ݲ��Ų��ҵĺ���
			break;
		case '4':                              //������һ���˵�
			system("cls");
			me.welcome();
			me.function_menu();
			me.function_menu_ctr();
			break;
		default:
			pause_out("��������ȷ�����:");
			break;
		}
		me.search_menu();
		cin >> option;

	}

}


//�û�ע�����
void Menu::sign_up()
{
	Mysql mys;
	string username;                 //ע����û���
	string password;                 //ע�������
	string repassword;               //ע���������֤

	cout << endl << endl;
	cout << setw(76) << "ְ  ��  ��  Ϣ  ��  ��  ϵ  ͳ  ע  ��";
	cout << endl << endl << endl << endl;
	cout << setw(60) << "������û���:" << endl << endl;
	cout << "                                               ";
	cin >> username;
	cout << endl;
	cout << setw(58) << "���������:" << endl << endl;
	cout << "                                               ";
	cin >> password;
	cout << endl;
	cout << setw(62) << "���ٴ��������:" << endl << endl;
	cout << "                                               ";
	cin >> repassword;

	if (password==repassword)
		//���������֤�ɹ��Ļ�ִ�н��û���Ϣ�������ݿ��ָ��
	{
		char sql[100];
		sprintf_s(sql, 100,"insert into user(username,password) values('%s','%s')", (username).data(), (password).data());
		//ͨ��sprintf_s�ѱ�����ֵ��sql��������һ��

		//��ʼ�����ݿ�
		mys.mysqConnect();
		//ִ��sqlָ��
		mysql_query(&mys.conn, sql);


		//ָ��ִ�гɹ������㣬�ô����õ��Ǹú����ķ���ֵ���෴��
		if (!mysql_query(&mys.conn, sql))  		{
			pause_out("ע��ɹ�");
			system("pause");
		}
		else
		{
			pause_out("ע��ʧ��");
			system("pause");
		}
		system("cls");
		login_menu();
		login_menu_ctr();
	}
	else
		pause_out("�������Ϣ����");
}

/*  *******************************Menu*******************************  */
/*  *******************************Menu*******************************  */
/*  *******************************Menu*******************************  */


/*  *******************************Mysql*******************************  */
/*  *******************************Mysql*******************************  */
/*  *******************************Mysql*******************************  */

//���ӵ��������ݿⲢ��ʼ���ķ���
int Mysql::mysqConnect()
{
	const char user[] = "root";                    //���ݿ�ϵͳ��������
	const char pswd[] = "123";                     //���ݿ������
	const char host[] = "localhost";               //���ݿ��վ��
	const char table[] = "manage_system";          //���ݿ������
	unsigned int port = 3306;                      //����ռ�õĶ˿ں�

	if (mysql_init(&conn) == NULL)                 //������ݿ�����ʼ��ʧ��
	{
		cout << "���ӳ�ʼ������";
		//�򷵻�0
		return 0;                                  
	}

	if (mysql_real_connect(&conn, host, user, pswd, table, port, NULL, 0))//�����Ƿ�������������ݿ�
		//����mysql���ַ���
		mysql_query(&conn, "SET NAMES gbk");    
	else
	{
		cout << "���ӵ����ݿ��Ƿ�������";
		return 0;
	}
	return 1;
}

//��ȡ���ݿ��е�ְ���ǵ���Ϣ
//�ú�������һ��const char* ���͵Ĳ��������� MYSQL_ROW�Ķ���
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

//�ӵ͵���һ�δ�Ų�ͬ��ѧ��
//�ú�������һ��int���͵�ֵ������һ���ַ���
string Mysql::put_field(int num)
{
	char field[9][10] = {"����", "����" , "����" , "�Ա�" ,  "�绰" ,  "����" , "����" ,  "ѧ��" ,  "��ס��ַ" };
	return field[num];
}

/*  *******************************Mysql*******************************  */
/*  *******************************Mysql*******************************  */
/*  *******************************Mysql*******************************  */

//��̬�������
//�ú�������һ���ַ���
void pause_out(string str)
{
	long count = 10000000;
	//ͨ����һ����Ϊ0����������һ���ܴ��ֵ���ӳ����һ���ַ���ʱ��
	//�ﵽһ�ֶ�̬�����Ч��
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
