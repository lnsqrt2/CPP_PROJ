#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int x;//元素下标
ofstream MyFile("U201514559_4.txt");//文件
int opt_flag;//操作标志

class QUEUE{
    int  *const  elems;	//申请内存用于存放队列的元素
    const  int   max;	//elems能存放的最大元素个数
    int   head, tail;		//队列头和尾，队列空时head=tail;初始时head=tail=0
public:
	QUEUE(int m);		//初始化循环队列：elems有m个元素
	QUEUE(const QUEUE&s); 			//用队列s拷贝初始化队列
	virtual operator int ( ) const;			//返回队列的实际元素个数
	virtual int full ( ) const;		       //返回队列是否已满，满返回1，否则返回0
	virtual int operator[ ](int x)const;   //取下标为x的元素,第1个元素下标为0
	virtual QUEUE& operator<<(int e); 	//将e入队列,并返回队列
	virtual QUEUE& operator>>(int &e);	//出队列到e,并返回队列
	virtual QUEUE& operator=(const QUEUE&s); //赋s给队列,并返回被赋值的队列
	virtual void print( ) const;			//打印队列
	virtual ~QUEUE( );					//销毁队列
};

QUEUE queue0 = 2;//用于标识异常情况

QUEUE::QUEUE(int m) :max(m), elems(new int[m])//const类型用初始化列表赋值
{
	head = 0;
	tail = 0;
}

QUEUE::QUEUE(const QUEUE&s): max(s.max), elems(new int[s.max])//用队列s拷贝初始化队列
{
	int i = 0;
	head = s.head;
	tail = s.tail;
	if(head>tail)//copy elems
	{
		for (i = head;i<max;i++)//从head开始
		{
			elems[i] = s.elems[i];
		}
		for (i = 0;i<tail;i++)//从0开始
		{
			elems[i] = s.elems[i];
		}
	}
	else
	{
		for (int i = head;i<tail;i++)//从head开始
		{
			elems[i] = s.elems[i];
		}
	}
	//cout << "copy finished" << endl;
}

QUEUE::operator int() const//返回队列的实际元素个数
{
	return (tail - head +max)%max;
}

int QUEUE::full ( ) const		       //返回队列是否已满，满返回1，否则返回0
{
	if((tail+1)%max==head)//判断当前队列空间与最大空间大小
	{
		return 1;
	}
	return 0;
}

int QUEUE::operator[ ](int x)const   //取下标为x的元素,第1个元素下标为0
{
	if (x < tail && x>=head)
		return elems[x];
	else
		return -1984;
}

QUEUE& QUEUE::operator<<(int e)//将e入队列,并返回队列
{
	if(full() == 0)//判断当前队列空间大小是否足够
	{
		elems[tail] = e;
		//tail++;
		tail = (tail + 1) % max;
		return (*this);
	}
	else
	{
		//cout << "队列空间已满！" << endl;
		return queue0;//返回一个大小为0的队列，表示队列满
	}
}

QUEUE& QUEUE::operator>>(int &e)//出队列到e,并返回队列
{
	if (head == tail)
	{
		//cout << "空队列！" << endl;
		return queue0;//表示空
	}
	else
	{
		e = elems[head];//把对列顶元素出到e
		elems[head] = 0;//对列顶元素赋0
		head = (head + 1) % max;
		return (*this);
	}
}

QUEUE& QUEUE::operator=(const QUEUE&s) //赋s给队列,并返回被赋值的队列
{
	int i = 0;
	*((int*)(&max))= s.max;
	delete []elems;
	*((int**)(&elems))=NULL;
	*((int**)(&elems))= new int[s.max];
	head = s.head;
	tail = s.tail;
	if(head>tail)//copy elems
	{
		for (i = head;i<max;i++)//从head开始
		{
			elems[i] = s.elems[i];
		}
		for (i = 0;i<tail;i++)//从0开始
		{
			elems[i] = s.elems[i];
		}
	}
	else
	{
		for (int i = head;i<tail;i++)//从head开始
		{
			elems[i] = s.elems[i];
		}
	}
	return (*this);
}

void QUEUE::print() const//打印队列
{
	int i =0;
	if (opt_flag <5)//完成的操作为I 0 C A
	{
		if(head>tail)
		{
			for (i = head;i<max;i++)//从head开始输出
			{
				cout << "  " << elems[i];
				MyFile << "  " << elems[i];
			}
			for (i = 0;i<tail;i++)//从head开始输出
			{
				cout << "  " << elems[i];
				MyFile << "  " << elems[i];
			}
		}
		else
		{
			for (int i = head;i<tail;i++)//从head开始输出
			{
				cout << "  " << elems[i];
				MyFile << "  " << elems[i];
			}
		}
	}
	if (opt_flag == 5)//当前队列的剩余个数 N
	{
		cout << "  " << int(*this);
		MyFile << "  " << int(*this);
	}
	if (opt_flag == 6)//数组下标为x的元素 G
	{
		cout << "  " << (*this)[x];
		MyFile << "  " << (*this)[x];
	}
}

QUEUE::~QUEUE()
{
	if (elems !=NULL)
	{
		delete[]elems;
	}
	*((int*)(&max))= 0;
	head = 0;
	tail = 0;
}

int main(int argc, char* argv[])
{
	int size_1 = 0;
	int size_2 = 0;
	int push_e = 0;//入队列元素
	int pop_e = 0;//出队列元素
	int pop_num = 0;//出队列元素个数
	x = 0;
	opt_flag = 0;
	queue0<<1984;
	//ofstream MyFile("U201514559_4.txt");//新建一个对应文件名的文本文档

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

		QUEUE queue1 = size_1;//调用构造函数
		cout << "  " << size_1;//返回max
		MyFile << "  " << size_1;//在文件中写入max


		//循环判定操作
		for (int i = 3; i < argc; i++)
		{
			//检测到操作符
			if ((strcmp("-I", argv[i]) == 0) || (strcmp("-i", argv[i]) == 0))
			{
				queue1.print();//操作完成后调用
				opt_flag = 1;
				cout << "  " << "I";
				MyFile << "  " << "I";//在文件中写入I
				continue;
			}
			if ((strcmp("-O", argv[i]) == 0) || (strcmp("-o", argv[i]) == 0))
			{
				queue1.print();//操作完成后调用
				opt_flag = 2;
				cout << "  " << "O";
				MyFile << "  " << "O";//在文件中写入O
				continue;
			}
			if ((strcmp("-C", argv[i]) == 0) || (strcmp("-c", argv[i]) == 0))
			{
				queue1.print();//操作完成后调用
				opt_flag = 3;
				cout << "  " << "C";
				MyFile << "  " << "C";//在文件中写入C

				//不需要输入参数，直接调用拷贝构造函数
				QUEUE queue2 = queue1;
				queue1 = queue2;//以后操作新队列
				continue;
			};
			if ((strcmp("-A", argv[i]) == 0) || (strcmp("-a", argv[i]) == 0))
			{
				queue1.print();//操作完成后调用
				opt_flag = 4;
				cout << "  " << "A";
				MyFile << "  " << "A";//在文件中写入A
				continue;
			}
			if ((strcmp("-N", argv[i]) == 0) || (strcmp("-n", argv[i]) == 0))
			{
				queue1.print();//操作完成后调用
				opt_flag = 5;
				cout << "  " << "N";
				MyFile << "  " << "N";//在文件中写入N
				continue;
			}
			if ((strcmp("-G", argv[i]) == 0) || (strcmp("-g", argv[i]) == 0))
			{
				queue1.print();//操作完成后调用
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
			case 1://入队列
				{
					sscanf(argv[i], "%d", &push_e);
					if ((queue1<<push_e)[0] == 1984)//判断入栈结果返回值
					{
						cout << "  " << "E";
						MyFile << "  " << "E";
						return -1;
					}

					//cout << push_e << " 成功入栈!" << endl;
					break;
				}
			case 2://出栈
				{
					sscanf(argv[i], "%d", &pop_num);
					for (int j = 0; j < pop_num; j++)
					{
						if ((queue1>>pop_e)[0] == 1984)//调用出栈函数
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
					QUEUE queue3 = size_2;//new
					queue3 = queue1;//assign
					queue1 = queue3;//把新栈赋值给旧栈，以后操作新栈
					break;
				}
			case 5://剩余元素个数
				break;
			case 6://获得下标为x的元素
				sscanf(argv[i], "%d", &x);
				if (-1984 == queue1[x])
				{
					cout << "  " << "E";
					MyFile << "  " << "E";
					return -3;
				}
				break;
			default:
				break;
			}
		}
		queue1.print();//命令结束后后调用
	}
	else
	{
		//cout << "未设定栈队或队列大小！" << endl;
		return -2;
	}
	MyFile.close();//关闭文件
	//system("pause");
	return 0;
}