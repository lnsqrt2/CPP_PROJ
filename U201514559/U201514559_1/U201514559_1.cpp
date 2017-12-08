#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct STACK {
	int  *elems;	//申请内存用于存放栈的元素
	int   max;	//栈能存放的最大元素个数
	int   pos;	//栈实际已有元素个数，栈空时pos=0;
};

void initSTACK(STACK *const p, int m);	//初始化p指向的栈：最多m个元素
void initSTACK(STACK *const p, const STACK&s); //用栈s初始化p指向的栈
int  size(const STACK *const p);		//返回p指向的栈的最大元素个数max
int  howMany(const STACK *const p);	//返回p指向的栈的实际元素个数pos
int  getelem(const STACK *const p, int x);	//取下标x处的栈元素
STACK *const push(STACK *const p, int e); 	//将e入栈，并返回p
STACK *const pop(STACK *const p, int &e); 	//出栈到e，并返回p
STACK *const assign(STACK*const p, const STACK&s); //赋s给p指的栈,并返回p
void print(const STACK*const p);			//打印p指向的栈
void destroySTACK(STACK*const p);		//销毁p指向的栈

void PrintToFile(const STACK*const p, ofstream &MyFile,int fin_flag, int x);//打印p指向的栈，并输出到文件

void initSTACK(STACK *const p, int m)//构造函数
{
	if (p == NULL)
	{
		return;
	}
	if (m > 0)//确认有空间分配
	{
		p->elems = (int*)malloc(sizeof(int)*m);
		p->max = m;
		p->pos = 0;
	}
	return;
}

void initSTACK(STACK *const p, const STACK&s) //用栈s初始化p指向的栈
{

	p->elems = (int*)malloc((s.max) * sizeof(int));
	for (int i = 0; i<(s.pos); i++)
	{
		p->elems[i] = s.elems[i];
	}
	p->pos = s.pos;
	p->max = s.max;
}

int  size(const STACK *const p)		//返回p指向的栈的最大元素个数max
{
	return p->max;
}

int  howMany(const STACK *const p)	//返回p指向的栈的实际元素个数pos
{
	return p->pos;
}

int  getelem(const STACK *const p, int x)	//取下标x处的栈元素
{
	if (x <= p->pos)
		return p->elems[x];
	else
		return -1984;
}

STACK *const push(STACK *const p, int e)//入栈函数
{

	if ((p->pos) < (p->max))//判断当前栈空间大小是否足够
	{
		p->elems[p->pos] = e;
		(p->pos)++;
		return p;
	}
	else
	{
		return NULL;
	}

}

STACK *const pop(STACK *const p, int &e)  //出栈函数
{ 

	if ((p->pos) == 0)
	{
		return NULL;
	}
	else    
	{        
		e = p->elems[(p->pos) - 1];//把栈顶元素出栈到e
		(p->elems[(p->pos) - 1]) = 0;
		(p->pos)--;
		return p;
	} 
}

STACK *const assign(STACK*const p, const STACK&s) //赋s给p指的栈, 并返回p
{
	p->max = s.max;
	free(p->elems);
	p->elems = NULL;
	p->elems = (int*)malloc((s.max) * sizeof(int));
	for (int i = 0; i < (s.pos); i++)
	{
		p->elems[i] = s.elems[i];
	}
	p->pos = s.pos;
	return p;
}

void print(const STACK*const p)//打印p指向的栈,并输出到文件
{
	for (int i = 0; i < p->pos; i++)
	{
		cout<< "  " << getelem(p, i);
	}
}

void PrintToFile(const STACK*const p, ofstream &MyFile, int fin_flag,int x)//打印p指向的栈,并输出到文件
{
	if (fin_flag <5)//完成的操作为1-5
	{
		for (int i = 0; i < p->pos; i++)
		{
			cout<< "  " << getelem(p, i);
			MyFile << "  " << getelem(p, i);
		}
	}
	if (fin_flag == 5)
	{
		cout << "  " << howMany(p);
		MyFile << "  " << howMany(p);
	}
	if (fin_flag == 6)
	{ 
		cout << "  " << getelem(p, x);
		MyFile << "  " << getelem(p, x);
	}
}

void destroySTACK(STACK*const p)//析构函数
{
	if(p->elems!=NULL && p->max > 0)
	  free(p->elems);
	p->max = 0;
	p->pos = 0;
	return;
}

int main(int argc, char* argv[])
{
	int x = 0;//栈元素下标
	int size_1 = 0;
	int size_2 = 0;
	int opt_flag = 0;//操作开始标志
	int push_e = 0;//入栈元素
	int pop_e = 0;//出栈元素
	int pop_num = 0;//出栈元素个数
	STACK *stack1 = NULL;
	STACK *stack2 = NULL;
	STACK *stack3 = NULL;
	stack1 = (STACK *)malloc(sizeof(STACK));//给s分配内存
	stack2 = (STACK *)malloc(sizeof(STACK));//给s分配内存
	stack3 = (STACK *)malloc(sizeof(STACK));//中间操作

	ofstream MyFile("U201514559_1.txt");//新建一个对应文件名的文本文档

	//判断是否设定栈或队列大小，-S
	if ((strcmp("-S", argv[1]) == 0) || (strcmp("-s", argv[1]) == 0))
	{
		//正确输入-S后
		//判断是否输入了栈和队列大小
		cout << "S";
		MyFile << "S";//在文件中写入S操作
		if (argv[2] == NULL)
		{
			//cout << "未输入栈队或队列大小！" << endl;
			return -3;
		}
		sscanf(argv[2], "%d", &size_1);//获取命令行参数

		initSTACK(stack1, size_1);//调用构造函数
		cout << "  " << size_1;//返回max
		MyFile << "  " << size_1;//在文件中写入 返回栈的最大元素max


		//循环判定操作
		for (int i = 3; i < argc; i++)
		{
			//检测到操作符
			if ((strcmp("-I", argv[i]) == 0) || (strcmp("-i", argv[i]) == 0))
			{
				PrintToFile(stack1, MyFile, opt_flag, x);//操作完成后调用
				opt_flag = 1;
				cout << "  " << "I";
				MyFile << "  " << "I";//在文件中写入I
				continue;
			}
			if ((strcmp("-O", argv[i]) == 0) || (strcmp("-o", argv[i]) == 0))
			{
				PrintToFile(stack1, MyFile, opt_flag, x);//操作完成后调用
				opt_flag = 2;
				cout << "  " << "O";
				MyFile << "  " << "O";//在文件中写入O
				continue;
			}
			if ((strcmp("-C", argv[i]) == 0) || (strcmp("-c", argv[i]) == 0))
			{
				PrintToFile(stack1, MyFile, opt_flag, x);//操作完成后调用
				opt_flag = 3;
				cout << "  " << "C";
				MyFile << "  " << "C";//在文件中写入C

				//不需要输入参数，直接调用拷贝构造函数
				initSTACK(stack2, *stack1);
				assign(stack1, *stack2);//把新栈赋值给旧栈，以后操作新栈
				continue;
			};
			if ((strcmp("-A", argv[i]) == 0) || (strcmp("-a", argv[i]) == 0))
			{
				PrintToFile(stack1, MyFile, opt_flag, x);//操作完成后调用
				opt_flag = 4;
				cout << "  " << "A";
				MyFile << "  " << "A";//在文件中写入A
				continue;
			}
			if ((strcmp("-N", argv[i]) == 0) || (strcmp("-n", argv[i]) == 0))
			{
				PrintToFile(stack1, MyFile, opt_flag, x);//操作完成后调用
				opt_flag = 5;
				cout << "  " << "N";
				MyFile << "  " << "N";//在文件中写入N
				continue;
			}
			if ((strcmp("-G", argv[i]) == 0) || (strcmp("-g", argv[i]) == 0))
			{
				PrintToFile(stack1, MyFile, opt_flag, x);//操作完成后调用
				opt_flag = 6;
				cout << "  " << "G";
				MyFile << "  " << "G";//在文件中写入G
				continue;
			}

			switch (opt_flag)
			{
			case 0:
				{
					break;
				}
			case 1://入栈
				{
					sscanf(argv[i], "%d", &push_e);
					if (NULL== push(stack1, push_e))//判断入栈结果返回值
					{
						cout << "  " << "E";
						MyFile << "  " << "E";
						return -1;
					}
					break;
				}
			case 2://出栈
				{
					sscanf(argv[i], "%d", &pop_num);
					for (int j = 0; j < pop_num; j++)
					{
						if (NULL == pop(stack1, pop_e))//调用出栈函数
						{
							cout << "  " << "E";
							MyFile << "  " << "E";
							return -2;
						}
						//cout << pop_e << "成功出栈!" << endl;
					}
					break;
				}
			case 3://深拷贝构造
				{
					//无参数输入
					break;
				}
				
			case 4://深拷贝赋值
				{
					sscanf(argv[i], "%d", &size_2);
					initSTACK(stack3,size_2);//new
					assign(stack3, *stack1);//assign
					assign(stack1, *stack3);//把新栈赋值给旧栈，以后操作新栈
					break;
				}
				
			case 5://剩余元素个数
				{
					//无参数输入
					break;
				}
				
			case 6://获得下标为x的元素
				{
					sscanf(argv[i], "%d", &x);
					if (-1984 == getelem(stack1, x))
					{
						cout << "  " << "E";
						MyFile << "  " << "E";
						return -3;
					}
					break;
				}
			default:
				break;
			}
		}
		PrintToFile(stack1, MyFile, opt_flag, x);//命令结束后后调用
	}
	else
	{
		//cout << "未设定栈队或队列大小！" << endl;
		return -2;
	}
	MyFile.close();//关闭文件
	destroySTACK(stack1);//调用析构函数
    //destroySTACK(stack2);//调用析构函数
	//destroySTACK(stack3);//调用析构函数
	stack1 = NULL;
	stack2 = NULL;
	stack3 = NULL;
	return 0;
}

