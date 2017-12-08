#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class STACK {
	int  *const  elems;	//申请内存用于存放栈的元素
	const  int   max;	//栈能存放的最大元素个数
	int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
	STACK(int m);		//初始化栈：最多m个元素
	STACK(const STACK&s); //用栈s拷贝初始化栈
	int  size() const;		//返回栈的最大元素个数max
	int  howMany() const;	//返回栈的实际元素个数pos
	int  getelem(int x) const;	//取下标x处的栈元素
	STACK& push(int e); 	//将e入栈,并返回栈
	STACK& pop(int &e); 	//出栈到e,并返回栈
	STACK& assign(const STACK&s); //赋s给栈,并返回被赋值的栈
	void print() const;		//打印栈
	~STACK();				//销毁栈
};

STACK stack0 = 0;//用于标识异常情况


STACK::STACK(int m):max(m), elems(new int[m])//const类型用初始化列表赋值
{
	pos = 0;
}

STACK::STACK(const STACK&s): max(s.max), elems(new int[s.max])//拷贝构造函数(新建栈)
{
	for (int i = 0;i<=s.pos;i++)//复制栈元素
	{
		elems[i] = s.elems[i];
	}
	pos = s.pos;
	//cout << "copy finished" << endl;
}

int STACK::size() const
{
	return max;
}

int  STACK::howMany() const	//返回栈的实际元素个数pos
{
	return pos;
}

int  STACK::getelem(int x) const	//取下标x处的栈元素
{
	if (x <= pos)
		return elems[x];
	else
		return -1984;
}

STACK& STACK::push(int e)//返回一个入栈结果
{
	if (pos < max)//判断当前栈空间大小是否足够
	{
		elems[pos] = e;
		pos++;
		return (*this);
	}
	else
	{
		//cout << "栈空间已满！" << endl;
		return stack0;//返回一个大小为0的栈，表示栈满
	}
}

STACK& STACK::pop(int &e)
{
	if (pos == 0)
	{
		//cout << "空栈！" << endl;
		return stack0;//返回一个大小为0的栈，表示栈空
	}
	else
	{
		e = elems[pos - 1];//把栈顶元素出栈到e
		elems[pos - 1] = 0;//栈顶元素赋0
		pos--;
		return (*this);
	}
}

STACK& STACK::assign(const STACK&s)//赋值（已经存在的栈）
{
	*((int*)(&max))= s.max;
	delete elems;
	*((int**)(&elems))=NULL;
	*((int**)(&elems))= new int[s.max];
	for (int i = 0;i<=s.pos;i++)//复制栈元素
	{
		elems[i] = s.elems[i];
	}
	pos = s.pos;
	return (*this);
}

void STACK::print() const
{
	for (int i = 0; i < max; i++)
	{
		cout << "  " << elems[i];
	}
}

STACK::~STACK()
{
	delete[]elems;
	//max = 0;
	pos = 0;

}

void PrintToFile(STACK &p, ofstream &MyFile, int fin_flag, int x)//输出操作和结果
{
	if (fin_flag <5)//完成的操作为I 0 C A
	{
		for (int i = 0; i < p.howMany(); i++)
		{
			cout << "  " << p.getelem(i);
			MyFile << "  " << p.getelem(i);
		}
	}
	if (fin_flag == 5)//当前栈的剩余个数 N
	{
		cout << "  " << p.howMany();
		MyFile << "  " << p.howMany();
	}
	if (fin_flag == 6)//对应下标栈 G
	{
		cout << "  " << p.getelem(x);
		MyFile << "  " << p.getelem(x);
	}
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

	ofstream MyFile("U201514559_2.txt");//新建一个对应文件名的文本文档

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

		STACK stack1 = size_1;//调用构造函数
		cout << "  " << stack1.size();//返回max
		MyFile << "  " << stack1.size();//在文件中写入 返回栈的最大元素max


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
				STACK stack2 = stack1;
				stack1.assign(stack2);//把新栈赋值给旧栈，以后操作新栈
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
					if (stack1.push(push_e).size()==0)//判断入栈结果返回值
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
						if (stack1.pop(pop_e).size() == 0)//调用出栈函数
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
					STACK stack3 = size_2;//new
					stack3.assign(stack1);//assign
					stack1.assign(stack3);//把新栈赋值给旧栈，以后操作新栈
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
					if (-1984 == stack1.getelem(x))
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
	return 0;
}

