#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*******************STACK类定义*******************/
class STACK {
	int  *const  elems;	//申请内存用于存放栈的元素
	const  int   max;	//栈能存放的最大元素个数
	int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
	STACK(int m);		//初始化栈：最多m个元素
	STACK(const STACK&s); //用栈s拷贝初始化栈
	virtual int  size() const;			//返回栈的最大元素个数max
	virtual operator int() const;			//返回栈的实际元素个数pos
	virtual int operator[ ] (int x) const;	//取下标x处的栈元素
	virtual STACK& operator<<(int e); 	//将e入栈,并返回栈
	virtual STACK& operator>>(int &e);	//出栈到e,并返回栈
	virtual STACK& operator=(const STACK&s); //赋s给栈,并返回被赋值的栈
	virtual void print() const;			//打印栈
	virtual ~STACK();					//销毁栈
};

STACK stack0 = 0;//用于标识异常情况

STACK::STACK(int m) :max(m), elems(new int[m])//const类型用初始化列表赋值
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

STACK::operator int() const//返回栈的实际元素个数pos
{
	return pos;
}

int STACK::operator[ ] (int x) const	//取下标x处的栈元素
{
	if (x <= pos)
		return elems[x];
	else
		return -1984;
}

STACK& STACK::operator<<(int e) 	//将e入栈,并返回栈
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

STACK& STACK::operator>>(int &e)	//出栈到e,并返回栈
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

STACK& STACK::operator=(const STACK&s) //赋s给栈,并返回被赋值的栈
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
	for (int i = 0; i < int(*this); i++)
	{
		cout << "  " << elems[i];
	}
}

STACK::~STACK()
{
	if(elems!=NULL)
	  delete[]elems;
	*((int*)(&max)) = 0;
	pos = 0;

}
/*******************STACK类结束*******************/
int x = 0;//元素下标
ofstream MyFile("U201514559_6.txt");//文件
int opt_flag = 0;//操作标志
/*******************QUEUE类定义*******************/

class QUEUE:public STACK{
    STACK  s2;//s2为出队，栈顶表示队首。
public:
	QUEUE(int m); //每个栈最多m个元素，要求实现的队列最多能入2m个元素
	QUEUE(const QUEUE&s); 			//用队列s拷贝初始化队列
	virtual operator int ( ) const;			//返回队列的实际元素个数
	virtual int full ( ) const;		       //返回队列是否已满，满返回1，否则返回0
	virtual int operator[ ](int x)const;   //取下标为x的元素，第1个元素下标为0
	virtual QUEUE& operator<<(int e);  //将e入队列,并返回队列
	virtual QUEUE& operator>>(int &e);	//出队列到e,并返回队列
	virtual QUEUE& operator=(const QUEUE&s); //赋s给队列,并返回被赋值的队列
	virtual void print( ) const;			//打印队列
	virtual ~QUEUE( );					//销毁队列
};

QUEUE queue0 = 2;//用于标识异常情况

QUEUE::QUEUE(int m):STACK(m), s2(m)
{
}

QUEUE::QUEUE(const QUEUE&s):STACK(s),s2(s.s2)//可以用父类的地方也可以用子类
{
}

QUEUE::operator int() const//返回队列的实际元素个数
{
	return (STACK::operator int ()+int(s2));
}

int QUEUE::full ( ) const//返回队列是否已满，满返回1，否则返回0
{
	if(int(*this)>=STACK::size()+s2.size())//判断当前队列空间与最大空间大小
	{
		return 1;
	}
	return 0;
}

int QUEUE::operator[ ](int x)const   //取下标为x的元素,第1个元素下标为0
{
	int i = 0;
	int j = 0;
	if(x>=(STACK::operator int ()+int(s2)))//超出队列元素范围
	{
		return -1984;
	}
	else
	{
		if(x<=(int(s2)-1))//x可从s2中取得
		{
			i = (int(s2)-1);//第一个元素下标
			for(j=0;j<x;j++)
			{
				i--;
			}
			return s2[i];
		}
		else//x从s1中取
		{
			x=x-int(s2);
			return STACK::operator [](x);
		}
	}
}

QUEUE& QUEUE::operator<<(int e)//将e入队列,并返回队列
{
	int p = 0;
	if ((STACK::operator<<(e)).size() != 0)//如果栈s1不满，直接入栈s1中
		return *this;
	else
		if(int(s2)== 0)//如果s1满了，s2为空，则把s1中的元素弹栈到s2中，再入栈s1
		{
			while((STACK::operator>>(p)).size()!=0)
			{
				s2<<p;
			}
			STACK::operator<<(e);
			return *this;
		}
		else
			if(int(s2) < s2.size())//如果s1满了，s2中存在一些元素且不满(中途进行过出栈操作)
			{
				return queue0;//这样设置为无法入队列
			}
			else //s1和s2都满了
				return queue0;//返回一个大小为0的队列，表示队列满
}

QUEUE& QUEUE::operator>>(int &e)//出队列到e,并返回队列
{
	int p = 0;
	if ((s2>>e).size() != 0)//如果s2不为空，直接弹出
		return *this;
	else
		if(STACK::operator int ()!=0)//s2为空，s1不为空，则把s1中的元素弹到s2中，再从s2出栈
		{
			while((STACK::operator>>(p)).size()!=0)
			{
				s2<<p;
			}
			s2>>e;
			return *this;
		}
		else//s1和s2都空
			return queue0;//返回一个大小为0的队列，表示队列空

}

QUEUE& QUEUE::operator=(const QUEUE&s) //赋s给队列,并返回被赋值的队列
{
	STACK::operator=(s);
	s2 = s.s2;
	return (*this);
}


void QUEUE::print() const//打印队列
{
	int i =0;
	if (opt_flag <5)//完成的操作为I 0 C A
	{
		if(int(s2)!=0)//s2不为空，输出
		{
			for (i = (int(s2)-1) ; i >= 0; i--)//栈底的下标为0,从栈顶输出到栈底，s2的栈顶为队列头
			{
				cout << "  " << s2[i];
				MyFile << "  " << s2[i];
			}
		}

		if(STACK::operator int ()!=0)//s2中所有元素输出结束后，若s1不为空，输出
		{
			for (i = 0 ; i < STACK::operator int (); i++)//栈底的下标为0,从栈顶输出到栈底，s1的栈顶为队列尾
			{
				cout << "  " << STACK::operator [](i);
				MyFile << "  " << STACK::operator [](i);
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

}

/*******************QUEUE类结束*******************/



int main(int argc, char* argv[])
{
	if (argc==1)//处理舞伴问题
	{
		int M,F,m,f;
		cout << "请输入男队人数M：";
		cin >>M;
		cout << "请输入女队人数F：";
		cin >>F;
		cout << "请输入男士位置m：";
		cin >>m;
		cout << "请输入女士位置f：";
		cin >>f;
		if(M==F || m>M || f>F)
		{
			cout << "输入不合规范，已退出程序" <<endl;
			return -1;
		}
		else
		{
			QUEUE Mqueue = M;//申请男队队列
			QUEUE Fqueue = F;//申请女队队列
			for(int m1=1;m1<=M;m1++)//给男队赋初值
			{
				if(m1 == m)
					Mqueue<<2;//被选中的男生
				else
					Mqueue<<1;//表示普通男生
			}
			for(int f1=1;f1<=F;f1++)//给女队赋初值
			{
				if(f1 == f)
					Fqueue<<2;//被选中的女生
				else
					Fqueue<<1;//表示普通女生
			}
			
			int male,female;//在跳舞的男女
			int dance = 1;//跳舞计数
			while(1)
			{
				Mqueue>>male;
				Fqueue>>female;
				if(male == 2 && female == 2)
				{
					cout << "他在第 "<< dance <<" 支舞曲可以和那位女士跳舞"<<endl;
					system("pause");
					return 0;
				}
				Mqueue<<male;
				Fqueue<<female;
				dance++;
			}
		}
		return 0;
	}
	else//栈自动测试
	{
		int size_1 = 0;
		int size_2 = 0;
		int push_e = 0;//入队列元素
		int pop_e = 0;//出队列元素
		int pop_num = 0;//出队列元素个数
		queue0<<1984;
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
		return 0;
	}
}