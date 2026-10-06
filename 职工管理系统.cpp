#include <iostream>
#include "workerManager.h" 
#include "worker.h"
#include "employee.h"
#include "manager.h" 
#include "boss.h" 
using namespace std;

int main()
{


	int choice = 0;
	//实例化管理者对象
	WorkerManager wm;

	while (true)
	{
		//调用展示菜单成员函数
		wm.Show_Menu();

		cout << "请输入你的选择：" << endl;
		cin >> choice;

		switch (choice)
		{
			/*
			0.退出管理程序
			1.增加职工信息
			2.显示职工信息
			3.删除离职职工
			4.修改职工信息
			5.查找职工信息
			6.按照编号排序
			7.清空所有文档
			 */
		case 0:
			wm.ExitSystem();
		case 1:
			wm.Add_Emp();
			break;
		case 2:
			wm.Show_Emp();
			break;
		case 3:
			wm.Del_Emp();
			break;
		case 4:
			wm.Mod_Emp();
			break;
		case 5:
			wm.Find_Emp();
			break;
		case 6:
			wm.Sort_Emp();
			break;
		case 7:
			wm.Clean_File();
			break;
		default:
			system("cls"); //清屏 
			break;

		}
	}


	system("pause"); //程序阻塞 
	return 0;
}