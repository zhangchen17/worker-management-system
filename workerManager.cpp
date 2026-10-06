#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"
#include <string.h>

//统计文件中人数 
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//统计人数变量 
//		cout<<id<<"   "<<name<<"   "<<dId<<endl;
		num++;
	}

	return num;
}

//初始化员工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker * worker = NULL;
		if (dId == 1) //普通职工
		{
			worker = new Employee(id, name, dId);
		}

		else if (dId == 2) //经理
		{
			worker = new Manager(id, name, dId);
		}

		else if (dId == 3) //老板
		{
			worker = new Boss(id, name, dId);
		}


		this->m_EmpArray[index] = worker;
		index++;
	}
	//关闭文件 
	ifs.close();

}

//构造函数 
WorkerManager::WorkerManager()
{
	//1.文件不存在 
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件
		//1.文件不存在 
	if (!ifs.is_open())
	{
		//		cout<<"文件不存在"<<endl;
				//初始化属性
				//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2. 文件存在，但数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
//		 cout<<"文件为空"<<endl; 
		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.文件存在，并且记录数据
	int num = this->get_EmpNum();
	//	  cout <<"职工人数为："<<num<<endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	// 将文件中的数据，存到数组中
	this->init_Emp();

}

//析构函数 
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

//保存文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //用输出的方式打开文件   写文件

	 //将每个人数据写入到文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	//关闭文件
	ofs.close();

}


//添加职工 
void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工数量：" << endl;

	int addNum = 0; //保存用户输入的数量
	cin >> addNum;
	if (addNum > 0)
	{
		//添加

		 //计算 添加新空间大小 
		int newSize = this->m_EmpNum + addNum;  //新空间人数 =  原来记录人数 +  新增人数 

		 //开辟新空间
		Worker ** newSpace = new Worker*[newSize];

		//将原来空间下数据，拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//			delete[]  this->m_EmpArray;
					//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int ret;
			int id;//职工编号
			string name; //职工姓名
			int dSelect; //部门选择

			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;
			ret = this->IsExist(id);
			while (ret != -1)
			{
				cout << "职工编号已存在，请重新输入：" << endl;
				cin >> id;
				ret = this->IsExist(id);
			}
			cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
			cin >> name;

			cout << "请选择该职工岗位：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			//将创建职工职责，保存到数组中
			newSpace[this->m_EmpNum] = worker;
			this->m_EmpNum = this->m_EmpNum + 1;

			this->m_EmpArray = newSpace;
			this->m_FileIsEmpty = false;

		}
		//释放原有空间
//			 delete[]  this->m_EmpArray;

			 //更改新空间的指向
//			 this->m_EmpArray = newSpace;

			 //更新新的职工人数
//			  this->m_EmpNum = newSize; 

			//更新职工不为空标志
//			this->m_FileIsEmpty = false; 
//			  
		this->save();
		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;
	}
	else
	{
		cout << "输入的数据有误" << endl;
	}
	system("pause");
	system("cls");
}

//显示职工
void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	//按任意键后清屏
	system("pause");
	system("cls");
}

//判断职工是否存在 
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//找到职工
			index = i;
			break;
		}
	}
	return index;
}

//判断职工是否存在  按姓名查找 
int *WorkerManager::IsExist(std::string name)
{
	int arr[100] = {};
	int num = 0;
	int * res;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Name == name)
		{
			//找到职工
			arr[num] = i;
			num++;
		}
	}

	res = new int[num+1];
	res[0] = num;
	for (int j = 0; j < num+1; j++)
	{
		res[j+1] = arr[j];
	}
	return res;
}

//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		//按职工编号删除
		cout << "请输入要删除的员工编号：" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)   //存在并删除职工 
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				//数据前移
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}

			this->m_EmpNum--;  //更新数组中记录人员个数 
			this->save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，未找到职工" << endl;
		}
	}
	//按任意键 清屏
	system("pause");
	system("cls");
}

//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		int id;
		cout << "请输入要修改的职工编号：" << endl;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1) {
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到：" << id << "号职工，请输入新职工号：" << endl;
			cin >> newId;

			cout << "请输入新姓名：" << endl;
			cin >> newName;

			cout << "请输入岗位：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;

			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				cout << "输入岗位错误" << endl;
				break;
			}
			//更新数据 到数组中
			this->m_EmpArray[ret] = worker;
			cout << "修改完成！" << endl;

			//保存 到文件中 
			this->save();
		}
		else
		{
			cout << "要修改的员工不存在" << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找员工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在，或记录为空" << endl;
	}
	else
	{
		cout << "请输入查找方式：" << endl;
		cout << "1.按职工编号查找" << endl;
		cout << "2.按员工的姓名查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) {
			//按编号查
			int id;
			cout << "请输入职工编号：" << endl;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1)
			{
				//找到员工
				cout << "查找成功，该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败" << endl;
			}
		}
		else if (select == 2) {
			//按姓名查找
			string name;
			cout << "请输入职工姓名：" << endl;
			cin >> name;
			int *ret = this->IsExist(name);
			int num_length = ret[0];
			cout << num_length << endl;
			if (num_length != 0)
			{
				//找到员工
				cout << "查找成功，该职工信息如下：" << endl;
				for(int i=0;i<num_length;i++)
				{
					this->m_EmpArray[ret[i+1]] ->showInfo();
				}	

				if (ret != NULL) {

					ret = NULL;
				}
				
			}
			else
			{
				cout << "查找失败" << endl;
			}
		}
		else
		{
			cout << "请选择正确的查找方式！" << endl;
		}
	}
	
	system("pause");
	system("cls");
}

//排序员工
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录清空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1.按职工号进行升序" << endl;
		cout << "2.按职工号进行降序" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minormax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1) //升序
				{
					if (m_EmpArray[minormax]->m_Id > m_EmpArray[j]->m_Id)
					{
						minormax = j;
					}
				}
				else  //降序
				{
					if (m_EmpArray[minormax]->m_Id < m_EmpArray[j]->m_Id)
					{
						minormax = j;
					}
				}
			}
			if (i != minormax)
			{
				Worker *temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minormax];
				m_EmpArray[minormax] = temp;
			}


		}
	}
	cout << "排序成功 ：" << endl;
	this->save();  //保存文件
	this->Show_Emp();
	system("pause");
	
}

//清空文件
void WorkerManager::Clean_File()
{
	cout << "确定清空？" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();


		if (this->m_EmpArray != NULL)
		{
			//删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;

		}
	}
}

//菜单展示 
void WorkerManager::Show_Menu()
{
	cout << "*****************************************************" << endl;
	cout << "****************欢迎使用职工管理系统*****************" << endl;
	cout << "*******************0.退出管理程序********************" << endl;
	cout << "*******************1.增加职工信息********************" << endl;
	cout << "*******************2.显示职工信息********************" << endl;
	cout << "*******************3.删除离职职工********************" << endl;
	cout << "*******************4.修改职工信息********************" << endl;
	cout << "*******************5.查找职工信息********************" << endl;
	cout << "*******************6.按照编号排序********************" << endl;
	cout << "*******************7.清空所有文档********************" << endl;
	cout << "*****************************************************" << endl;
	cout << endl;
}

//退出系统
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//退出程序 
}