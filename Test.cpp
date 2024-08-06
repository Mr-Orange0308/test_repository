
#include <iostream>
#include<string>
#include<mysql.h>
using namespace std;

struct Student
{
	string name;
	int age;
	double score;
};

const char* host = "127.0.0.1";
const char* user = "root";
const char* psw = "123456";
const char* database_name = "ship_test";
const int port = 3306;

class MMSql
{
public:
	MMSql();
	~MMSql();
	MYSQL* getConnect();
	void updateID();
	void addToMySQL();
	void delToMySQL();
	void editToMySQL();
	void findToMySQL();
private:
	MYSQL* con;
};

MMSql::MMSql()
{
	//��ʼ��mysql
	con = mysql_init(0);
	//VS�ı��뷽ʽΪGBK,�������MYSQL�ı��뷽ʽΪGBK
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");

	//�������ݿ�
	if (!mysql_real_connect(con, host, user, psw, database_name, port, NULL, 0))
	{
		cout << mysql_error(con) << endl;
	}

}

MMSql::~MMSql()
{
	mysql_close(this->getConnect());
}

MYSQL* MMSql::getConnect()
{
	return this->con;
}

void MMSql::updateID()
{
	/*/ ɾ������������id�ı�� /*/
	const char* query[] = {
		//����id�ֶε�ֵ�����´�1��ʼ���
		"SET @new_id = 0;",
		"UPDATE ship01 SET id = @new_id:=@new_id+1;",
		//���������������е���СֵΪ1
		"ALTER TABLE ship01 AUTO_INCREMENT = 1;"
	};

	// ִ�ж���Query���
	int num_queries = sizeof(query) / sizeof(query[0]);
	for (int i = 0; i < num_queries; ++i) {
		if (mysql_query(this->getConnect(), query[i]) != 0) {
			cout << "ִ��Query���ʧ��: " << mysql_error(this->getConnect()) << endl;
			return;
		}
	}
}

void MMSql::addToMySQL()
{
	Student stu;
	stu.name = "xiaowang";
	stu.age = 79;
	stu.score = 88.9;
	/*/ ��*/
		//ͨ��query��������
	string query = "INSERT INTO ship01 (`name`, age, score) VALUES ('" + stu.name + "', " + to_string(stu.age) + ", " + to_string(stu.score) + ")";

	if (mysql_query(this->getConnect(), query.c_str()) != 0)
	{
		cout << mysql_error(this->getConnect()) << endl;
		mysql_close(this->getConnect());
		return; // Exit the program with an error code
	}
	cout << "��ӳɹ�!" << "��ǰ����Ϊ:" << endl;
	this->updateID();//��������
	this->findToMySQL();
}

void MMSql::delToMySQL()
{
	///ɾ
//ͨ��queryɾ������
	string query2 = "DELETE FROM ship01 WHERE id=2;";
	if (mysql_query(this->getConnect(), query2.c_str()) != 0)
	{
		cout << mysql_error(this->getConnect()) << endl;
		mysql_close(this->getConnect());
		return; // Exit the program with an error code
	}
	cout << "ɾ���ɹ�!" << "��ǰ����Ϊ:" << endl;
	this->updateID();//��������
	this->findToMySQL();
}

void MMSql::editToMySQL()
{
	///��
	int num1 = 39;
	string name1 = "fd";
	string query1 = "update ship01 set score=" + to_string(num1) + " where name = " + "'" + name1 + "'";
	if (mysql_query(this->getConnect(), query1.c_str()) != 0)
	{
		cout << mysql_error(this->getConnect()) << endl;
		mysql_close(this->getConnect());
		return; // Exit the program with an error code
	}
	cout << "�޸ĳɹ�!" << "��ǰ����Ϊ:" << endl;
	this->findToMySQL();
}

void MMSql::findToMySQL()
{
	//��
//ͨ��query��ѯ����
	mysql_query(this->getConnect(), "SELECT * FROM ship01");
	//ʹ��res�ռ���ѯ��������
	MYSQL_RES* res = mysql_store_result(this->getConnect());
	if (!res)
	{
		cout << mysql_error(this->getConnect()) << endl;
		mysql_close(this->getConnect());
		return; // Exit the program with an error code
	}
	//ȡ���ռ��������ݵ�����(���ڱ���)
	int num_fields = mysql_num_fields(res);
	//ȡÿһ�е�����,��ӡ
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			cout << row[i] << " ";
		}
		cout << endl;
	}
	//�ͷ��ռ�������
	mysql_free_result(res);
}


int main()
{
	MMSql* mysq = new MMSql();
	mysq->addToMySQL();

	//mysq->editToMySQL();

	//mysq->delToMySQL();

	cout << "Hello World!\n";
	return 0;
}

