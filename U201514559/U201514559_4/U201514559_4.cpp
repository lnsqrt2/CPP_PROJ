#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int x;//Ԫ���±�
ofstream MyFile("U201514559_4.txt");//�ļ�
int opt_flag;//������־

class QUEUE{
    int  *const  elems;	//�����ڴ����ڴ�Ŷ��е�Ԫ��
    const  int   max;	//elems�ܴ�ŵ����Ԫ�ظ���
    int   head, tail;		//����ͷ��β�����п�ʱhead=tail;��ʼʱhead=tail=0
public:
	QUEUE(int m);		//��ʼ��ѭ�����У�elems��m��Ԫ��
	QUEUE(const QUEUE&s); 			//�ö���s������ʼ������
	virtual operator int ( ) const;			//���ض��е�ʵ��Ԫ�ظ���
	virtual int full ( ) const;		       //���ض����Ƿ�������������1�����򷵻�0
	virtual int operator[ ](int x)const;   //ȡ�±�Ϊx��Ԫ��,��1��Ԫ���±�Ϊ0
	virtual QUEUE& operator<<(int e); 	//��e�����,�����ض���
	virtual QUEUE& operator>>(int &e);	//�����е�e,�����ض���
	virtual QUEUE& operator=(const QUEUE&s); //��s������,�����ر���ֵ�Ķ���
	virtual void print( ) const;			//��ӡ����
	virtual ~QUEUE( );					//���ٶ���
};

QUEUE queue0 = 2;//���ڱ�ʶ�쳣���

QUEUE::QUEUE(int m) :max(m), elems(new int[m])//const�����ó�ʼ���б�ֵ
{
	head = 0;
	tail = 0;
}

QUEUE::QUEUE(const QUEUE&s): max(s.max), elems(new int[s.max])//�ö���s������ʼ������
{
	int i = 0;
	head = s.head;
	tail = s.tail;
	if(head>tail)//copy elems
	{
		for (i = head;i<max;i++)//��head��ʼ
		{
			elems[i] = s.elems[i];
		}
		for (i = 0;i<tail;i++)//��0��ʼ
		{
			elems[i] = s.elems[i];
		}
	}
	else
	{
		for (int i = head;i<tail;i++)//��head��ʼ
		{
			elems[i] = s.elems[i];
		}
	}
	//cout << "copy finished" << endl;
}

QUEUE::operator int() const//���ض��е�ʵ��Ԫ�ظ���
{
	return (tail - head +max)%max;
}

int QUEUE::full ( ) const		       //���ض����Ƿ�������������1�����򷵻�0
{
	if((tail+1)%max==head)//�жϵ�ǰ���пռ������ռ��С
	{
		return 1;
	}
	return 0;
}

int QUEUE::operator[ ](int x)const   //ȡ�±�Ϊx��Ԫ��,��1��Ԫ���±�Ϊ0
{
	if (x < tail && x>=head)
		return elems[x];
	else
		return -1984;
}

QUEUE& QUEUE::operator<<(int e)//��e�����,�����ض���
{
	if(full() == 0)//�жϵ�ǰ���пռ��С�Ƿ��㹻
	{
		elems[tail] = e;
		//tail++;
		tail = (tail + 1) % max;
		return (*this);
	}
	else
	{
		//cout << "���пռ�������" << endl;
		return queue0;//����һ����СΪ0�Ķ��У���ʾ������
	}
}

QUEUE& QUEUE::operator>>(int &e)//�����е�e,�����ض���
{
	if (head == tail)
	{
		//cout << "�ն��У�" << endl;
		return queue0;//��ʾ��
	}
	else
	{
		e = elems[head];//�Ѷ��ж�Ԫ�س���e
		elems[head] = 0;//���ж�Ԫ�ظ�0
		head = (head + 1) % max;
		return (*this);
	}
}

QUEUE& QUEUE::operator=(const QUEUE&s) //��s������,�����ر���ֵ�Ķ���
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
		for (i = head;i<max;i++)//��head��ʼ
		{
			elems[i] = s.elems[i];
		}
		for (i = 0;i<tail;i++)//��0��ʼ
		{
			elems[i] = s.elems[i];
		}
	}
	else
	{
		for (int i = head;i<tail;i++)//��head��ʼ
		{
			elems[i] = s.elems[i];
		}
	}
	return (*this);
}

void QUEUE::print() const//��ӡ����
{
	int i =0;
	if (opt_flag <5)//��ɵĲ���ΪI 0 C A
	{
		if(head>tail)
		{
			for (i = head;i<max;i++)//��head��ʼ���
			{
				cout << "  " << elems[i];
				MyFile << "  " << elems[i];
			}
			for (i = 0;i<tail;i++)//��head��ʼ���
			{
				cout << "  " << elems[i];
				MyFile << "  " << elems[i];
			}
		}
		else
		{
			for (int i = head;i<tail;i++)//��head��ʼ���
			{
				cout << "  " << elems[i];
				MyFile << "  " << elems[i];
			}
		}
	}
	if (opt_flag == 5)//��ǰ���е�ʣ����� N
	{
		cout << "  " << int(*this);
		MyFile << "  " << int(*this);
	}
	if (opt_flag == 6)//�����±�Ϊx��Ԫ�� G
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
	int push_e = 0;//�����Ԫ��
	int pop_e = 0;//������Ԫ��
	int pop_num = 0;//������Ԫ�ظ���
	x = 0;
	opt_flag = 0;
	queue0<<1984;
	//ofstream MyFile("U201514559_4.txt");//�½�һ����Ӧ�ļ������ı��ĵ�

	//�ж��Ƿ��趨ջ����д�С��-S
	if ((strcmp("-S", argv[1]) == 0) || (strcmp("-s", argv[1]) == 0))
	{
		//��ȷ����-S��
		//�ж��Ƿ�������ջ�Ͷ��д�С
		cout << "S";
		MyFile << "S";//���ļ���д��S����
		if (argv[2] == NULL)
		{
			//cout << "δ����ջ�ӻ���д�С��" << endl;
			return -3;
		}
		sscanf(argv[2], "%d", &size_1);//��ȡ�����в���

		QUEUE queue1 = size_1;//���ù��캯��
		cout << "  " << size_1;//����max
		MyFile << "  " << size_1;//���ļ���д��max


		//ѭ���ж�����
		for (int i = 3; i < argc; i++)
		{
			//��⵽������
			if ((strcmp("-I", argv[i]) == 0) || (strcmp("-i", argv[i]) == 0))
			{
				queue1.print();//������ɺ����
				opt_flag = 1;
				cout << "  " << "I";
				MyFile << "  " << "I";//���ļ���д��I
				continue;
			}
			if ((strcmp("-O", argv[i]) == 0) || (strcmp("-o", argv[i]) == 0))
			{
				queue1.print();//������ɺ����
				opt_flag = 2;
				cout << "  " << "O";
				MyFile << "  " << "O";//���ļ���д��O
				continue;
			}
			if ((strcmp("-C", argv[i]) == 0) || (strcmp("-c", argv[i]) == 0))
			{
				queue1.print();//������ɺ����
				opt_flag = 3;
				cout << "  " << "C";
				MyFile << "  " << "C";//���ļ���д��C

				//����Ҫ���������ֱ�ӵ��ÿ������캯��
				QUEUE queue2 = queue1;
				queue1 = queue2;//�Ժ�����¶���
				continue;
			};
			if ((strcmp("-A", argv[i]) == 0) || (strcmp("-a", argv[i]) == 0))
			{
				queue1.print();//������ɺ����
				opt_flag = 4;
				cout << "  " << "A";
				MyFile << "  " << "A";//���ļ���д��A
				continue;
			}
			if ((strcmp("-N", argv[i]) == 0) || (strcmp("-n", argv[i]) == 0))
			{
				queue1.print();//������ɺ����
				opt_flag = 5;
				cout << "  " << "N";
				MyFile << "  " << "N";//���ļ���д��N
				continue;
			}
			if ((strcmp("-G", argv[i]) == 0) || (strcmp("-g", argv[i]) == 0))
			{
				queue1.print();//������ɺ����
				opt_flag = 6;
				cout << "  " << "G";
				MyFile << "  " << "G";//���ļ���д��G
				continue;
			}

			switch (opt_flag)
			{
			case 0:
				{
					break;
				}
			case 1://�����
				{
					sscanf(argv[i], "%d", &push_e);
					if ((queue1<<push_e)[0] == 1984)//�ж���ջ�������ֵ
					{
						cout << "  " << "E";
						MyFile << "  " << "E";
						return -1;
					}

					//cout << push_e << " �ɹ���ջ!" << endl;
					break;
				}
			case 2://��ջ
				{
					sscanf(argv[i], "%d", &pop_num);
					for (int j = 0; j < pop_num; j++)
					{
						if ((queue1>>pop_e)[0] == 1984)//���ó�ջ����
						{
							cout << "  " << "E";
							MyFile << "  " << "E";
							return -2;
						}
						//cout << pop_e << "�ɹ���ջ!" << endl;
					}
					break;
				}
			case 3://�������
				{
					//�޲�������
					break;
				}
			case 4://�����ֵ
				{
					sscanf(argv[i], "%d", &size_2);
					QUEUE queue3 = size_2;//new
					queue3 = queue1;//assign
					queue1 = queue3;//����ջ��ֵ����ջ���Ժ������ջ
					break;
				}
			case 5://ʣ��Ԫ�ظ���
				break;
			case 6://����±�Ϊx��Ԫ��
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
		queue1.print();//�������������
	}
	else
	{
		//cout << "δ�趨ջ�ӻ���д�С��" << endl;
		return -2;
	}
	MyFile.close();//�ر��ļ�
	//system("pause");
	return 0;
}