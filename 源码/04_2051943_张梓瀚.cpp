#define _CRT_SECURE_NO_WARNINGS
#include "MyStack.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
const int MAX_LEN = 2 * 100;

/*������������ȼ�*/
int priority(char c) {
	if (c == '(')
		return 0;
	else if (c == '+' || c == '-')
		return 1;
	else
		return 2;
}

/*�Ƚ���������ȼ�*/
bool cmp(char a, char b) {
	return priority(a) > priority(b);
}

const char* infix_to_suffix(const char* infix)
{
	char* suffix = new char[MAX_LEN + 1];
	char last = '1'; //last��¼�ϸ����ţ����ж�
	bool fir = false, is_opt = false; // �ж��׸����ź͸����Ƿ�Ϊ������ı�־
	int cnt = 0; //��¼�ں�׺���ʽ�е�λ��
	myStack<char>stk;
	for (int i = 0; infix[i] != '\0'; i++) {
		char c = infix[i];
		//ɨ�赽����ĩβ������ѭ��
		if (c == '\0') {
			break;
		}
		else if (c == ' ') {
			last = c;
			continue;
		}
		//����С��������֣�ֱ�����
		else if (isdigit(c) || c == '.') {
			if (isdigit(c))
				is_opt = true;
			//�жϵ�ǰ�������Ƿ��ǰ��������ͬ��һ��������
			if (!(!fir || last == '-' || isdigit(last) || last == '.'))
				suffix[cnt++] = ' ';
			suffix[cnt++] = c;
			fir = true;
			last = c;
			continue;
		}
		//�����ţ���ջ�����ų�ջֱ����Ӧ�������ų�ջ
		else if (c == ')') {
			while (!stk.empty() && stk.top() != '(') {
				suffix[cnt++] = ' ';
				suffix[cnt++] = stk.top();
				last = stk.top();
				stk.pop();
			}
			stk.pop();
		}
		//������ֱ��ѹջ
		else if (c == '(') {
			stk.push(c);
		}
		else {
			if ((c == '+' || c == '-') && isdigit(infix[i + 1])) {
				//�Ը��������⴦��
				if (c == '-') {
					//������Ϊ�����������ո�
					if (is_opt)
						suffix[cnt++] = ' ';
					suffix[cnt++] = c;
					last = c;
				}
				continue;
			}
			while (!stk.empty() && !cmp(c, stk.top())) {
				suffix[cnt++] = ' ';
				suffix[cnt++] = stk.top();
				last = stk.top();
				stk.pop();
			}
			stk.push(c);
		}
	}
	//��ջ�ڻ���ʣ���������������ȫ�����
	while (!stk.empty()) {
		suffix[cnt++] = ' ';
		suffix[cnt++] = stk.top();
		stk.pop();
	}
	suffix[cnt] = '\0';
	return suffix;
}

int main() {
	char str[MAX_LEN + 1];
	bool is_valid = 1;
	while (1)
	{
		cout << "�������ת������׺���ʽ�����Ȳ�����100���ַ�����" << endl;
		cin.get(str, MAX_LEN);
		is_valid = 1;
		for (int i = 0; str[i] != '\0'; i++)
		{
			if (str[i] <= -1 || str[i] >= 255)
			{
				is_valid = 0;
				break;
			}
		}
		if (is_valid)
			break;
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "������ʽ���зǷ��ַ�������������" << endl;
	}
	cout << "ת����ĺ�׺���ʽΪ��" << endl << infix_to_suffix(str);
	return 0;
}