#include"stdio.h"
#include"stdlib.h"
#include"iostream"
#include"stack"
#define MaxSize 256
using namespace std;
typedef int TElemType;

//�������Ķ���
typedef struct LNBiTree {
	TElemType data;
	struct LNBiTree* lchild, * rchild;//������ҽ��Ķ���
}LNBiTree,*BiTree;

//����
typedef struct {
	BiTree data[MaxSize];
	int front, rear;
}SqQueue;


//ջ
typedef struct {
	BiTree data[MaxSize];
	int top;
}Stack;

//void InitTree1(BiTree &T);��GetBiTree����ƥ��
void InitTree2(BiTree& T);//��InputBiTree����ƥ��
//void GetBiTree(BiTree &T);//���������(�Լ�д�ĺ���)
//LNBiTree* InputTree();//��������(����һ�������ĸ�������)

void InputBiTree(BiTree& T);//���򷽷�����������

//��������(�ݹ����)
void PreBiTree(BiTree T);//���򷽷�����������
void InBiTree(BiTree T);//���򷽷�����������
void PostBiTree(BiTree T);//���򷽷�����������

//��α���
void LevelBiTree(BiTree T);//��η���(���и���)����������
void InitSqQueue(SqQueue &Q);//���еĳ�ʼ��
void EnSqQueue(SqQueue& Q, BiTree p);//����к���
LNBiTree* DeSqQueue(SqQueue& Q, BiTree p);//�����к���
int QueueEmpty(SqQueue& Q);//�ж������Ƿ�Ϊ��


//ջ���������
void InOrderTraverse(BiTree T);
void InitStack(Stack& S);//��ʼ��ջ
int StackEmpty(Stack S);//�ж�ջ�Ƿ�Ϊ��
void PushStack(Stack& S,BiTree p);//��ջ
LNBiTree *PopStack(Stack& S,BiTree p);//��ջ

//ջ���������
void PreOrderTraverse(BiTree T);

//ջ�ĺ������
void PostOrderTraverse(BiTree T);

int main()
{
	BiTree T;
	//InitTree1(T);
	//GetBiTree(T);
	InitTree2(T);
	InputBiTree(T);

	cout << "���������";
	PreBiTree(T);
	//cout <<endl<<"���������";
	//InBiTree(T);
	//cout << endl << "���������";
	//PostBiTree(T);
	
	//��α���
	//LevelBiTree(T);

	//ջ���������
	cout << endl;
	//InOrderTraverse(T);

	//ջ���������
	PreOrderTraverse(T);
}

void InitTree1(BiTree &T)
{
	T = new LNBiTree();
	cout << "�����׽���ֵ��";
	cin >> T->data;
	T->lchild = NULL;
	T->rchild = NULL;
}

//void GetBiTree(BiTree &T)
//{
//	//����������ĺ�����Ŀǰֻ�������Ϊ�򵥵Ķ�����������Ķ�����ֻ�ܶ�ĳ
//	//������һ��������и�ֵ
//	BiTree head = T;
//	int k=0;
//	while (k != 100)
//	{
//		cout << "**�������Ĳ���**"<<endl;
//		cout << "1.����������һ����ڵ�" << endl;
//		cout << "2.����������һ���ҽڵ�" << endl;
//		cout << "3.������ڵ�" << endl;
//		cout << "4.�����ҽڵ�" << endl;
//		cout << "100.�˳�" << endl;
//		cout << "������Ҫ���еĲ�����";
//		cin >> k;
//		switch (k)
//		{
//		case 1: head->lchild = InputTree(); break;
//		case 2: head->rchild = InputTree(); break;
//		case 3: 
//		{
//			if (head->lchild)
//				head = head->lchild;
//			else
//				cout << "���㲻���ڣ�" << endl;
//		}break;
//		case 4:
//		{
//			if (head->rchild)
//				head = head->rchild;
//			else
//				cout << "�ҽ�㲻���ڣ�" << endl;
//		}break;
//		case 100:break;
//		default:cout << "�������ݲ��Ϸ����������룡" << endl;
//		}
//		system("pause");
//		system("cls");
//	}
//}

//LNBiTree* InputTree()
//{
//	BiTree s=new LNBiTree();
//	cout << "�������ֵ��";
//	cin >> s->data;
//	s->lchild = NULL;
//	s->rchild = NULL;
//	return s;
//}

void InitTree2(BiTree& T)
{
	T = new LNBiTree();
	T->lchild = NULL;
	T->rchild = NULL;
}
//�ݹ鷽�����������
void InputBiTree(BiTree& T)
{
	//���򷽷�����һ�����������õݹ鷽��ʵ�֣���0��ʾ��ָ��
	int n;
	cout << "�������ֵ��";
	cin >> n;
	if (n == 0)
		T = NULL;
	else
	{
		T = new LNBiTree();
		T->data = n;
		InputBiTree(T->lchild);
		InputBiTree(T->rchild);
	}
}
//���򷽷�����������
void PreBiTree(BiTree T)
{
	if (T != NULL)
	{
		cout << T->data << "  ";
		PreBiTree(T->lchild);
		PreBiTree(T->rchild);
	}
}
//���򷽷�����������
void InBiTree(BiTree T)
{
	if (T != NULL)
	{
		InBiTree(T->lchild);
		cout << T->data<<"  ";
		InBiTree(T->rchild);
	}
}
//���򷽷�����������
void PostBiTree(BiTree T)
{
	if (T != NULL)
	{
		PostBiTree(T->lchild);
		PostBiTree(T->rchild);
		cout << T->data << "  ";
	}
}

//��α���������
void LevelBiTree(BiTree T)
{
	cout << "��α�����";
	BiTree p=new LNBiTree();
	SqQueue Q;
	InitSqQueue(Q);
	EnSqQueue(Q, T);
	while (!QueueEmpty(Q))
	{
		p=DeSqQueue(Q, p);
		cout << p->data << " ";
		if(p->lchild!=NULL)
			EnSqQueue(Q, p->lchild);
		if(p->rchild!=NULL)
			EnSqQueue(Q, p->rchild);
	}
}

void InitSqQueue(SqQueue &Q)
{
	Q.front = 0;
	Q.rear = 0;
}

void EnSqQueue(SqQueue& Q, BiTree p)
{
	Q.data[Q.rear] = p;
	Q.rear++;
}

LNBiTree* DeSqQueue(SqQueue& Q, BiTree p)
{
	p = Q.data[Q.front];
	Q.front++;
	return p;
}

int QueueEmpty(SqQueue& Q)
{
	if (Q.front == Q.rear)
		return 1;
	else
		return 0;
}
//ջ���������
void InOrderTraverse(BiTree T)
{
	cout << "����ջ�����������";
	BiTree p=T;
	Stack S;
	InitStack(S);
	while (p || StackEmpty(S))
	{
		if (p)
		{
			PushStack(S, p);
			p = p->lchild;
		}
		else
		{
			p=PopStack(S, p);
			cout << p->data << " ";
			p = p->rchild;
		}
	}
}
//ջ���������
void PreOrderTraverse(BiTree T)
{
	stack<BiTree> S;
	cout << "ջ�����������";
	BiTree p = T;
	while (p || !S.empty())
	{
		while (p)
		{
			cout << p->data << "  ";
			S.push(p);
			p = p->lchild;
		}

		p = S.top();
		S.pop();
		p = p->rchild;
	}
}
//ջ�ĺ������
void PostOrderTraverse(BiTree T)
{
	;
}

void InitStack(Stack& S)
{
	S.top = 0;
}

int StackEmpty(Stack S) 
{
	if (S.top == 0)
		return 0;
	else
		return 1;
}

void PushStack(Stack& S, BiTree p)
{
	S.data[S.top] = p;
	S.top++;
}

LNBiTree* PopStack(Stack& S, BiTree p)
{
	p = S.data[S.top - 1];
	S.top--;
	return p;
}
