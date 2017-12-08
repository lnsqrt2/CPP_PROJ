#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*******************STACK�ඨ��*******************/
class STACK {
	int  *const  elems;	//�����ڴ����ڴ��ջ��Ԫ��
	const  int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;			//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
	STACK(int m);		//��ʼ��ջ�����m��Ԫ��
	STACK(const STACK&s); //��ջs������ʼ��ջ
	virtual int  size() const;			//����ջ�����Ԫ�ظ���max
	virtual operator int() const;			//����ջ��ʵ��Ԫ�ظ���pos
	virtual int operator[ ] (int x) const;	//ȡ�±�x����ջԪ��
	virtual STACK& operator<<(int e); 	//��e��ջ,������ջ
	virtual STACK& operator>>(int &e);	//��ջ��e,������ջ
	virtual STACK& operator=(const STACK&s); //��s��ջ,�����ر���ֵ��ջ
	virtual void print() const;			//��ӡջ
	virtual ~STACK();					//����ջ
};

STACK stack0 = 0;//���ڱ�ʶ�쳣���

STACK::STACK(int m) :max(m), elems(new int[m])//const�����ó�ʼ���б�ֵ
{
	pos = 0;
}

STACK::STACK(const STACK&s): max(s.max), elems(new int[s.max])//�������캯��(�½�ջ)
{
	for (int i = 0;i<=s.pos;i++)//����ջԪ��
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

STACK::operator int() const//����ջ��ʵ��Ԫ�ظ���pos
{
	return pos;
}

int STACK::operator[ ] (int x) const	//ȡ�±�x����ջԪ��
{
	if (x <= pos)
		return elems[x];
	else
		return -1984;
}

STACK& STACK::operator<<(int e) 	//��e��ջ,������ջ
{
	if (pos < max)//�жϵ�ǰջ�ռ��С�Ƿ��㹻
	{
		elems[pos] = e;
		pos++;
		return (*this);
	}
	else
	{
		//cout << "ջ�ռ�������" << endl;
		return stack0;//����һ����СΪ0��ջ����ʾջ��
	}
}

STACK& STACK::operator>>(int &e)	//��ջ��e,������ջ
{
	if (pos == 0)
	{
		//cout << "��ջ��" << endl;
		return stack0;//����һ����СΪ0��ջ����ʾջ��
	}
	else
	{
		e = elems[pos - 1];//��ջ��Ԫ�س�ջ��e
		elems[pos - 1] = 0;//ջ��Ԫ�ظ�0
		pos--;
		return (*this);
	}
}

STACK& STACK::operator=(const STACK&s) //��s��ջ,�����ر���ֵ��ջ
{
	*((int*)(&max))= s.max;
	delete elems;
	*((int**)(&elems))=NULL;
	*((int**)(&elems))= new int[s.max];
	for (int i = 0;i<=s.pos;i++)//����ջԪ��
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
/*******************STACK�����*******************/
int x = 0;//Ԫ���±�
ofstream MyFile("U201514559_6.txt");//�ļ�
int opt_flag = 0;//������־
/*******************QUEUE�ඨ��*******************/

class QUEUE:public STACK{
    STACK  s2;//s2Ϊ���ӣ�ջ����ʾ���ס�
public:
	QUEUE(int m); //ÿ��ջ���m��Ԫ�أ�Ҫ��ʵ�ֵĶ����������2m��Ԫ��
	QUEUE(const QUEUE&s); 			//�ö���s������ʼ������
	virtual operator int ( ) const;			//���ض��е�ʵ��Ԫ�ظ���
	virtual int full ( ) const;		       //���ض����Ƿ�������������1�����򷵻�0
	virtual int operator[ ](int x)const;   //ȡ�±�Ϊx��Ԫ�أ���1��Ԫ���±�Ϊ0
	virtual QUEUE& operator<<(int e);  //��e�����,�����ض���
	virtual QUEUE& operator>>(int &e);	//�����е�e,�����ض���
	virtual QUEUE& operator=(const QUEUE&s); //��s������,�����ر���ֵ�Ķ���
	virtual void print( ) const;			//��ӡ����
	virtual ~QUEUE( );					//���ٶ���
};

QUEUE queue0 = 2;//���ڱ�ʶ�쳣���

QUEUE::QUEUE(int m):STACK(m), s2(m)
{
}

QUEUE::QUEUE(const QUEUE&s):STACK(s),s2(s.s2)//�����ø���ĵط�Ҳ����������
{
}

QUEUE::operator int() const//���ض��е�ʵ��Ԫ�ظ���
{
	return (STACK::operator int ()+int(s2));
}

int QUEUE::full ( ) const//���ض����Ƿ�������������1�����򷵻�0
{
	if(int(*this)>=STACK::size()+s2.size())//�жϵ�ǰ���пռ������ռ��С
	{
		return 1;
	}
	return 0;
}

int QUEUE::operator[ ](int x)const   //ȡ�±�Ϊx��Ԫ��,��1��Ԫ���±�Ϊ0
{
	int i = 0;
	int j = 0;
	if(x>=(STACK::operator int ()+int(s2)))//��������Ԫ�ط�Χ
	{
		return -1984;
	}
	else
	{
		if(x<=(int(s2)-1))//x�ɴ�s2��ȡ��
		{
			i = (int(s2)-1);//��һ��Ԫ���±�
			for(j=0;j<x;j++)
			{
				i--;
			}
			return s2[i];
		}
		else//x��s1��ȡ
		{
			x=x-int(s2);
			return STACK::operator [](x);
		}
	}
}

QUEUE& QUEUE::operator<<(int e)//��e�����,�����ض���
{
	int p = 0;
	if ((STACK::operator<<(e)).size() != 0)//���ջs1������ֱ����ջs1��
		return *this;
	else
		if(int(s2)== 0)//���s1���ˣ�s2Ϊ�գ����s1�е�Ԫ�ص�ջ��s2�У�����ջs1
		{
			while((STACK::operator>>(p)).size()!=0)
			{
				s2<<p;
			}
			STACK::operator<<(e);
			return *this;
		}
		else
			if(int(s2) < s2.size())//���s1���ˣ�s2�д���һЩԪ���Ҳ���(��;���й���ջ����)
			{
				return queue0;//��������Ϊ�޷������
			}
			else //s1��s2������
				return queue0;//����һ����СΪ0�Ķ��У���ʾ������
}

QUEUE& QUEUE::operator>>(int &e)//�����е�e,�����ض���
{
	int p = 0;
	if ((s2>>e).size() != 0)//���s2��Ϊ�գ�ֱ�ӵ���
		return *this;
	else
		if(STACK::operator int ()!=0)//s2Ϊ�գ�s1��Ϊ�գ����s1�е�Ԫ�ص���s2�У��ٴ�s2��ջ
		{
			while((STACK::operator>>(p)).size()!=0)
			{
				s2<<p;
			}
			s2>>e;
			return *this;
		}
		else//s1��s2����
			return queue0;//����һ����СΪ0�Ķ��У���ʾ���п�

}

QUEUE& QUEUE::operator=(const QUEUE&s) //��s������,�����ر���ֵ�Ķ���
{
	STACK::operator=(s);
	s2 = s.s2;
	return (*this);
}


void QUEUE::print() const//��ӡ����
{
	int i =0;
	if (opt_flag <5)//��ɵĲ���ΪI 0 C A
	{
		if(int(s2)!=0)//s2��Ϊ�գ����
		{
			for (i = (int(s2)-1) ; i >= 0; i--)//ջ�׵��±�Ϊ0,��ջ�������ջ�ף�s2��ջ��Ϊ����ͷ
			{
				cout << "  " << s2[i];
				MyFile << "  " << s2[i];
			}
		}

		if(STACK::operator int ()!=0)//s2������Ԫ�������������s1��Ϊ�գ����
		{
			for (i = 0 ; i < STACK::operator int (); i++)//ջ�׵��±�Ϊ0,��ջ�������ջ�ף�s1��ջ��Ϊ����β
			{
				cout << "  " << STACK::operator [](i);
				MyFile << "  " << STACK::operator [](i);
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

}

/*******************QUEUE�����*******************/



int main(int argc, char* argv[])
{
	if (argc==1)//�����������
	{
		int M,F,m,f;
		cout << "�������ж�����M��";
		cin >>M;
		cout << "������Ů������F��";
		cin >>F;
		cout << "��������ʿλ��m��";
		cin >>m;
		cout << "������Ůʿλ��f��";
		cin >>f;
		if(M==F || m>M || f>F)
		{
			cout << "���벻�Ϲ淶�����˳�����" <<endl;
			return -1;
		}
		else
		{
			QUEUE Mqueue = M;//�����жӶ���
			QUEUE Fqueue = F;//����Ů�Ӷ���
			for(int m1=1;m1<=M;m1++)//���жӸ���ֵ
			{
				if(m1 == m)
					Mqueue<<2;//��ѡ�е�����
				else
					Mqueue<<1;//��ʾ��ͨ����
			}
			for(int f1=1;f1<=F;f1++)//��Ů�Ӹ���ֵ
			{
				if(f1 == f)
					Fqueue<<2;//��ѡ�е�Ů��
				else
					Fqueue<<1;//��ʾ��ͨŮ��
			}
			
			int male,female;//���������Ů
			int dance = 1;//�������
			while(1)
			{
				Mqueue>>male;
				Fqueue>>female;
				if(male == 2 && female == 2)
				{
					cout << "���ڵ� "<< dance <<" ֧�������Ժ���λŮʿ����"<<endl;
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
	else//ջ�Զ�����
	{
		int size_1 = 0;
		int size_2 = 0;
		int push_e = 0;//�����Ԫ��
		int pop_e = 0;//������Ԫ��
		int pop_num = 0;//������Ԫ�ظ���
		queue0<<1984;
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
		return 0;
	}
}