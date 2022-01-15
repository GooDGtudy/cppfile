#include"stdio.h"
#include"iostream"
#include"vector"
#include"stack"
#include"string"
#include"fstream"
using namespace std;

//��һά�����ʾ��������
typedef struct HTree {
	int weight;
	int parent, right, left;
};

void GetHTree(vector<HTree>& HT)
{
	ifstream ifs;
	ifs.open("HTree.txt", ios::in);
	if (!ifs.is_open())
		cout << "���ļ�ʧ�ܣ�" << endl;
	int weight;
	while (ifs >> weight) {
		HT.push_back({weight,0,0,0});
	}
	ifs.close();
}

void SearchChild(vector<HTree>& HT) {
	int n = HT.size()-1;//ʵ����Ч��ֵֻ��HT.size()-1��
	for (int i = n+1; i < 2*n; i++) {
		int frimin = 0;
		int secmin = 0;
		for (int j = 1; j < HT.size(); j++) {//Ѱ����С��Ȩֵ
			if (HT[j].parent != 0) continue;
			if (HT[j].weight < HT[frimin].weight) {
				frimin = j;
			}
		}
		for (int j = 1; j < HT.size(); j++) {//Ѱ�ҵڶ�С��Ȩֵ
			if (HT[j].parent != 0) continue;
			if (HT[j].weight <= HT[secmin].weight && HT[j].weight >= HT[frimin].weight && j != frimin)
				secmin = j;
		}
		//���кϲ�
		int Neweight = HT[frimin].weight + HT[secmin].weight;
		HT.push_back({ Neweight,0,frimin,secmin });
		HT[frimin].parent = i;
		HT[secmin].parent = i;
	}
}

vector<HTree> TurnToHTree(vector<int> hash) {
	int length = hash.size();
	vector<HTree> HT(length+1);
	HT[0] = { INT_MAX,INT_MAX,INT_MAX,INT_MAX };
	for (int i = 1; i < hash.size(); i++) {
		HT[i].weight = hash[i - 1];
		HT[i].parent = 0;
		HT[i].left = 0;
		HT[i].right = 0;
	}
	return HT;
}

void ShowHT(vector<HTree>& HT) {
	cout <<"λ��\t" << "Ȩֵ\t" << "˫��\t" << "����\t" << "�Һ���\t"<< endl;
	for (int i = 1; i < HT.size(); i++) {
		cout << i <<"\t" << HT[i].weight << "\t" << HT[i].parent << "\t" << HT[i].left << "\t" << HT[i].right << endl;
	}
}

vector<HTree> GetWeight() {
	vector<int> hash(26);
	ifstream ifs;
	ifs.open("string.txt", ios::in);
	if (!ifs.is_open())
		cout << "�ַ��ļ���ʧ�ܣ�" << endl;
	char s;
	while (ifs >> s) {
		hash[s - 'a']++;
	}
	ifs.close();
	vector<HTree> HT;
	HT = TurnToHTree(hash);
	SearchChild(HT);
	return HT;
}

void CreatHuffmanCode(vector<HTree> HT, vector<vector<char>>& HC) {
	for (int i = 1; i <= 26; i++) {
		stack<char> st;
		int child = i;
		int parent = HT[i].parent;
		int left = HT[i].left;
		int right = HT[i].right;
		while (parent != 0) {
			if (HT[parent].left == child) st.push('0');
			else st.push('1');
			child = parent;
			parent = HT[parent].parent;
		}
		while (!st.empty()) {
			HC[i - 1].push_back(st.top());
			st.pop();
		}
	}
}

void ShowHuffmanCode(vector<vector<char>>& HC) {
	cout << "���������룺" << endl;
	for (int i = 0; i < HC.size(); i++) {
		char c = 'a' + i;
		cout << c <<":";
		for (int j = 0; j < HC[i].size(); j++) {
			cout << HC[i][j];
		}
		cout << endl;
	}
}

int main(){
	vector<HTree> HT;//��������
	vector<vector<char>> HC(26);
	GetHTree(HT);
	HT = GetWeight();
	ShowHT(HT);
	CreatHuffmanCode(HT, HC);
	ShowHuffmanCode(HC);
	

	system("pause");
	system("cls");
}