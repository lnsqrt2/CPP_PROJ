#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class STACK {
	int  *const  elems;	//�����ڴ����ڴ��ջ��Ԫ��
	const  int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;			//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
	STACK(int m);		//��ʼ��ջ�����m��Ԫ��
	STACK(const STACK&s); //��ջs������ʼ��ջ
	int  size() const;		//����ջ�����Ԫ�ظ���max
	int  howMany() const;	//����ջ��ʵ��Ԫ�ظ���pos
	int  getelem(int x) const;	//ȡ�±�x����ջԪ��
	STACK& push(int e); 	//��e��ջ,������ջ
	STACK& pop(int &e); 	//��ջ��e,������ջ
	STACK& assign(const STACK&s); //��s��ջ,�����ر���ֵ��ջ
	void print() const;		//��ӡջ
	~STACK();				//����ջ
};

STACK stack0 = 0;//���ڱ�ʶ�쳣���


STACK::STACK(int m):max(m), elems(new int[m])//const�����ó�ʼ���б�ֵ
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

int  STACK::howMany() const	//����ջ��ʵ��Ԫ�ظ���pos
{
	return pos;
}

int  STACK::getelem(int x) const	//ȡ�±�x����ջԪ��
{
	if (x <= pos)
		return elems[x];
	else
		return -1984;
}

STACK& STACK::push(int e)//����һ����ջ���
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

STACK& STACK::pop(int &e)
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

STACK& STACK::assign(const STACK&s)//��ֵ���Ѿ����ڵ�ջ��
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

void PrintToFile(STACK &p, ofstream &MyFile, int fin_flag, int x)//��������ͽ��
{
	if (fin_flag <5)//��ɵĲ���ΪI 0 C A
	{
		for (int i = 0; i < p.howMany(); i++)
		{
			cout << "  " << p.getelem(i);
			MyFile << "  " << p.getelem(i);
		}
	}
	if (fin_flag == 5)//��ǰջ��ʣ����� N
	{
		cout << "  " << p.howMany();
		MyFile << "  " << p.howMany();
	}
	if (fin_flag == 6)//��Ӧ�±�ջ G
	{
		cout << "  " << p.getelem(x);
		MyFile << "  " << p.getelem(x);
	}
}

int main(int argc, char* argv[])
{
	int x = 0;//ջԪ���±�
	int size_1 = 0;
	int size_2 = 0;
	int opt_flag = 0;//������ʼ��־
	int push_e = 0;//��ջԪ��
	int pop_e = 0;//��ջԪ��
	int pop_num = 0;//��ջԪ�ظ���

	ofstream MyFile("U201514559_2.txt");//�½�һ����Ӧ�ļ������ı��ĵ�

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

		STACK stack1 = size_1;//���ù��캯��
		cout << "  " << stack1.size();//����max
		MyFile << "  " << stack1.size();//���ļ���д�� ����ջ�����Ԫ��max


		//ѭ���ж�����
		for (int i = 3; i < argc; i++)
		{
			//��⵽������
			if ((strcmp("-I", argv[i]) == 0) || (strcmp("-i", argv[i]) == 0))
			{
				PrintToFile(stack1, MyFile, opt_flag, x);//������ɺ����
				opt_flag = 1;
				cout << "  " << "I";
				MyFile << "  " << "I";//���ļ���д��I
				continue;
			}
			if ((strcmp("-O", argv[i]) == 0) || (strcmp("-o", argv[i]) == 0))
			{
				PrintToFile(stack1, MyFile, opt_flag, x);//������ɺ����
				opt_flag = 2;
				cout << "  " << "O";
				MyFile << "  " << "O";//���ļ���д��O
				continue;
			}
			if ((strcmp("-C", argv[i]) == 0) || (strcmp("-c", argv[i]) == 0))
			{
				PrintToFile(stack1, MyFile, opt_flag, x);//������ɺ����
				opt_flag = 3;
				cout << "  " << "C";
				MyFile << "  " << "C";//���ļ���д��C

				//����Ҫ���������ֱ�ӵ��ÿ������캯��
				STACK stack2 = stack1;
				stack1.assign(stack2);//����ջ��ֵ����ջ���Ժ������ջ
				continue;
			};
			if ((strcmp("-A", argv[i]) == 0) || (strcmp("-a", argv[i]) == 0))
			{
				PrintToFile(stack1, MyFile, opt_flag, x);//������ɺ����
				opt_flag = 4;
				cout << "  " << "A";
				MyFile << "  " << "A";//���ļ���д��A
				continue;
			}
			if ((strcmp("-N", argv[i]) == 0) || (strcmp("-n", argv[i]) == 0))
			{
				PrintToFile(stack1, MyFile, opt_flag, x);//������ɺ����
				opt_flag = 5;
				cout << "  " << "N";
				MyFile << "  " << "N";//���ļ���д��N
				continue;
			}
			if ((strcmp("-G", argv[i]) == 0) || (strcmp("-g", argv[i]) == 0))
			{
				PrintToFile(stack1, MyFile, opt_flag, x);//������ɺ����
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
			case 1://��ջ
				{
					sscanf(argv[i], "%d", &push_e);
					if (stack1.push(push_e).size()==0)//�ж���ջ�������ֵ
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
						if (stack1.pop(pop_e).size() == 0)//���ó�ջ����
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
					STACK stack3 = size_2;//new
					stack3.assign(stack1);//assign
					stack1.assign(stack3);//����ջ��ֵ����ջ���Ժ������ջ
					break;
				}
				
			case 5://ʣ��Ԫ�ظ���
				{
					//�޲�������
					break;
				}
				
			case 6://����±�Ϊx��Ԫ��
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
		PrintToFile(stack1, MyFile, opt_flag, x);//�������������
	}
	else
	{
		//cout << "δ�趨ջ�ӻ���д�С��" << endl;
		return -2;
	}
	MyFile.close();//�ر��ļ�
	return 0;
}

