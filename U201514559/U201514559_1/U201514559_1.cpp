#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct STACK {
	int  *elems;	//�����ڴ����ڴ��ջ��Ԫ��
	int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;	//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
};

void initSTACK(STACK *const p, int m);	//��ʼ��pָ���ջ�����m��Ԫ��
void initSTACK(STACK *const p, const STACK&s); //��ջs��ʼ��pָ���ջ
int  size(const STACK *const p);		//����pָ���ջ�����Ԫ�ظ���max
int  howMany(const STACK *const p);	//����pָ���ջ��ʵ��Ԫ�ظ���pos
int  getelem(const STACK *const p, int x);	//ȡ�±�x����ջԪ��
STACK *const push(STACK *const p, int e); 	//��e��ջ��������p
STACK *const pop(STACK *const p, int &e); 	//��ջ��e��������p
STACK *const assign(STACK*const p, const STACK&s); //��s��pָ��ջ,������p
void print(const STACK*const p);			//��ӡpָ���ջ
void destroySTACK(STACK*const p);		//����pָ���ջ

void PrintToFile(const STACK*const p, ofstream &MyFile,int fin_flag, int x);//��ӡpָ���ջ����������ļ�

void initSTACK(STACK *const p, int m)//���캯��
{
	if (p == NULL)
	{
		return;
	}
	if (m > 0)//ȷ���пռ����
	{
		p->elems = (int*)malloc(sizeof(int)*m);
		p->max = m;
		p->pos = 0;
	}
	return;
}

void initSTACK(STACK *const p, const STACK&s) //��ջs��ʼ��pָ���ջ
{

	p->elems = (int*)malloc((s.max) * sizeof(int));
	for (int i = 0; i<(s.pos); i++)
	{
		p->elems[i] = s.elems[i];
	}
	p->pos = s.pos;
	p->max = s.max;
}

int  size(const STACK *const p)		//����pָ���ջ�����Ԫ�ظ���max
{
	return p->max;
}

int  howMany(const STACK *const p)	//����pָ���ջ��ʵ��Ԫ�ظ���pos
{
	return p->pos;
}

int  getelem(const STACK *const p, int x)	//ȡ�±�x����ջԪ��
{
	if (x <= p->pos)
		return p->elems[x];
	else
		return -1984;
}

STACK *const push(STACK *const p, int e)//��ջ����
{

	if ((p->pos) < (p->max))//�жϵ�ǰջ�ռ��С�Ƿ��㹻
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

STACK *const pop(STACK *const p, int &e)  //��ջ����
{ 

	if ((p->pos) == 0)
	{
		return NULL;
	}
	else    
	{        
		e = p->elems[(p->pos) - 1];//��ջ��Ԫ�س�ջ��e
		(p->elems[(p->pos) - 1]) = 0;
		(p->pos)--;
		return p;
	} 
}

STACK *const assign(STACK*const p, const STACK&s) //��s��pָ��ջ, ������p
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

void print(const STACK*const p)//��ӡpָ���ջ,��������ļ�
{
	for (int i = 0; i < p->pos; i++)
	{
		cout<< "  " << getelem(p, i);
	}
}

void PrintToFile(const STACK*const p, ofstream &MyFile, int fin_flag,int x)//��ӡpָ���ջ,��������ļ�
{
	if (fin_flag <5)//��ɵĲ���Ϊ1-5
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

void destroySTACK(STACK*const p)//��������
{
	if(p->elems!=NULL && p->max > 0)
	  free(p->elems);
	p->max = 0;
	p->pos = 0;
	return;
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
	STACK *stack1 = NULL;
	STACK *stack2 = NULL;
	STACK *stack3 = NULL;
	stack1 = (STACK *)malloc(sizeof(STACK));//��s�����ڴ�
	stack2 = (STACK *)malloc(sizeof(STACK));//��s�����ڴ�
	stack3 = (STACK *)malloc(sizeof(STACK));//�м����

	ofstream MyFile("U201514559_1.txt");//�½�һ����Ӧ�ļ������ı��ĵ�

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

		initSTACK(stack1, size_1);//���ù��캯��
		cout << "  " << size_1;//����max
		MyFile << "  " << size_1;//���ļ���д�� ����ջ�����Ԫ��max


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
				initSTACK(stack2, *stack1);
				assign(stack1, *stack2);//����ջ��ֵ����ջ���Ժ������ջ
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
					if (NULL== push(stack1, push_e))//�ж���ջ�������ֵ
					{
						cout << "  " << "E";
						MyFile << "  " << "E";
						return -1;
					}
					break;
				}
			case 2://��ջ
				{
					sscanf(argv[i], "%d", &pop_num);
					for (int j = 0; j < pop_num; j++)
					{
						if (NULL == pop(stack1, pop_e))//���ó�ջ����
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
					initSTACK(stack3,size_2);//new
					assign(stack3, *stack1);//assign
					assign(stack1, *stack3);//����ջ��ֵ����ջ���Ժ������ջ
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
		PrintToFile(stack1, MyFile, opt_flag, x);//�������������
	}
	else
	{
		//cout << "δ�趨ջ�ӻ���д�С��" << endl;
		return -2;
	}
	MyFile.close();//�ر��ļ�
	destroySTACK(stack1);//������������
    //destroySTACK(stack2);//������������
	//destroySTACK(stack3);//������������
	stack1 = NULL;
	stack2 = NULL;
	stack3 = NULL;
	return 0;
}

