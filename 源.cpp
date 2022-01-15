#include"stdio.h"
#include"stdlib.h"
#include"iostream"
#include"stack"
#define MaxSize 256
using namespace std;
typedef int TElemType;

//二叉树的定义
typedef struct LNBiTree {
	TElemType data;
	struct LNBiTree* lchild, * rchild;//左结点和右结点的定义
}LNBiTree,*BiTree;

//队列
typedef struct {
	BiTree data[MaxSize];
	int front, rear;
}SqQueue;


//栈
typedef struct {
	BiTree data[MaxSize];
	int top;
}Stack;

//void InitTree1(BiTree &T);与GetBiTree函数匹配
void InitTree2(BiTree& T);//与InputBiTree函数匹配
//void GetBiTree(BiTree &T);//输入二叉树(自己写的函数)
//LNBiTree* InputTree();//辅助函数(上面一个函数的辅助函数)

void InputBiTree(BiTree& T);//先序方法建立二叉树

//遍历方法(递归遍历)
void PreBiTree(BiTree T);//先序方法遍历二叉树
void InBiTree(BiTree T);//中序方法遍历二叉树
void PostBiTree(BiTree T);//后序方法遍历二叉树

//层次遍历
void LevelBiTree(BiTree T);//层次方法(队列辅助)遍历二叉树
void InitSqQueue(SqQueue &Q);//队列的初始化
void EnSqQueue(SqQueue& Q, BiTree p);//入队列函数
LNBiTree* DeSqQueue(SqQueue& Q, BiTree p);//出队列函数
int QueueEmpty(SqQueue& Q);//判读队列是否为空


//栈的中序遍历
void InOrderTraverse(BiTree T);
void InitStack(Stack& S);//初始化栈
int StackEmpty(Stack S);//判断栈是否为空
void PushStack(Stack& S,BiTree p);//入栈
LNBiTree *PopStack(Stack& S,BiTree p);//出栈

//栈的先序遍历
void PreOrderTraverse(BiTree T);

//栈的后序遍历
void PostOrderTraverse(BiTree T);

int main()
{
	BiTree T;
	//InitTree1(T);
	//GetBiTree(T);
	InitTree2(T);
	InputBiTree(T);

	cout << "先序遍历：";
	PreBiTree(T);
	//cout <<endl<<"中序遍历：";
	//InBiTree(T);
	//cout << endl << "后序遍历：";
	//PostBiTree(T);
	
	//层次遍历
	//LevelBiTree(T);

	//栈的中序遍历
	cout << endl;
	//InOrderTraverse(T);

	//栈的先序遍历
	PreOrderTraverse(T);
}

void InitTree1(BiTree &T)
{
	T = new LNBiTree();
	cout << "输入首结点的值：";
	cin >> T->data;
	T->lchild = NULL;
	T->rchild = NULL;
}

//void GetBiTree(BiTree &T)
//{
//	//输入二叉树的函数，目前只能输入较为简单的二叉树，输入的二叉树只能对某
//	//个结点的一个方向进行赋值
//	BiTree head = T;
//	int k=0;
//	while (k != 100)
//	{
//		cout << "**二叉树的操作**"<<endl;
//		cout << "1.创建并输入一个左节点" << endl;
//		cout << "2.创建并输入一个右节点" << endl;
//		cout << "3.进入左节点" << endl;
//		cout << "4.进入右节点" << endl;
//		cout << "100.退出" << endl;
//		cout << "输入想要进行的操作：";
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
//				cout << "左结点不存在！" << endl;
//		}break;
//		case 4:
//		{
//			if (head->rchild)
//				head = head->rchild;
//			else
//				cout << "右结点不存在！" << endl;
//		}break;
//		case 100:break;
//		default:cout << "输入内容不合法！重新输入！" << endl;
//		}
//		system("pause");
//		system("cls");
//	}
//}

//LNBiTree* InputTree()
//{
//	BiTree s=new LNBiTree();
//	cout << "输入结点的值：";
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
//递归方法输入二叉树
void InputBiTree(BiTree& T)
{
	//先序方法建立一个二叉树，用递归方法实现，用0表示空指针
	int n;
	cout << "输入结点的值：";
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
//先序方法遍历二叉树
void PreBiTree(BiTree T)
{
	if (T != NULL)
	{
		cout << T->data << "  ";
		PreBiTree(T->lchild);
		PreBiTree(T->rchild);
	}
}
//中序方法遍历二叉树
void InBiTree(BiTree T)
{
	if (T != NULL)
	{
		InBiTree(T->lchild);
		cout << T->data<<"  ";
		InBiTree(T->rchild);
	}
}
//后序方法遍历二叉树
void PostBiTree(BiTree T)
{
	if (T != NULL)
	{
		PostBiTree(T->lchild);
		PostBiTree(T->rchild);
		cout << T->data << "  ";
	}
}

//层次遍历二叉树
void LevelBiTree(BiTree T)
{
	cout << "层次遍历：";
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
//栈的中序遍历
void InOrderTraverse(BiTree T)
{
	cout << "利用栈的中序遍历：";
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
//栈的先序遍历
void PreOrderTraverse(BiTree T)
{
	stack<BiTree> S;
	cout << "栈的先序遍历：";
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
//栈的后序遍历
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
