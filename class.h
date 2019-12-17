#include<string>
#include <mysql.h>
#include<iostream>
using namespace std;
#ifndef CLASS_H_
#define CLASS_H_
class Stuff
{
private:
	int id;                                   //����
	int age;                                  //����
	int salary;                               //����
	string tel;                               //�绰����
	string name;                              //����
	string gender;                            //�Ա�
 	string department;                        //����
	string degree;                            //ѧ��
	string addr;                              //��ססַ
public:
	Stuff();                                  //Ĭ��ְ����Ϣ�Ĺ��캯��
	Stuff(int, int, string, string, string, string, string, string);
                                              //¼�����ݿ�Ĺ��캯��
	void dispInfo();                          //��ʾְ����Ϣ
	void addStuff();                          //¼��ְ����Ϣ
	void modifyStuff();                       //�޸�ְ����Ϣ
	void delStuff();                          //ɾ��ְ����Ϣ
	void saveStuff();                         //����ְ����Ϣ
	void searchStuff();                       //����ְ����Ϣ
	void sortStuff();                         //����ְ����Ϣ
	int sortSalary();                         //���ݹ��ʽ�������
	int sortDegree();                         //����ѧ����������
	int sortAge();
	int searchId();                           //���ݹ��Ž��в���
	int searchName();                         //�����������в���
	int searchDepartment();                   //���ݲ��Ž��в���
	int searchDegree(int num);                //����ѧ�����в���


	string getAge(int num);                   //��ȡְ������
	string getTel(int numr);                  //��ȡְ���绰
	string getGender(int num);                //��ȡְ���Ա�
	string getDepartment(int num);            //��ȡְ������
	string getDegree(int num);                //��ȡְ��ѧ��

};

class Menu
{
public:
	void welcome();                           //�����Ļ�ӭ����
	void function_menu();                     //���ܲ˵�����
	void function_menu_ctr();                 //���ܲ˵����������
	void login_menu();                        //����Ա�������
  	void sort_menu();                         //����˵�����
	void login_menu_ctr();                    //����Ա������������
	void search_menu();                       //���Ҳ˵�����
	void search_menu_ctr();                   //���Ҳ˵����������
	int check_menu();                         //����Ա������Ϣ��֤����
	void sign_up();                           //����Աע�����

};

class Mysql
{
public:
	MYSQL conn;                               //�������ݿ����Ӷ���
	MYSQL_FIELD* field;                       //�����ֶε�ָ��
	MYSQL_RES* result;                        //����ָ��ִ�н����ָ��
	MYSQL_ROW row;                            //���ش����ݿ�ȡ��������
	MYSQL_ROW mysql_fetch(const char* sql);   //�����������
	int mysqConnect();                        //���ݿ����ӳ�ʼ������
	string put_field(int num);                //�����ֶεĺ���
};

void pause_out(string);                       //��̬�������
#endif