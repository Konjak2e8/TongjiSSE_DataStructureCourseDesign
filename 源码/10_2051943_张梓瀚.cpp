#include <cstdlib>
#include <random>
#include <iostream>
using namespace std;

template<typename T>
void my_swap(T& a, T& b)
{
	a ^= b ^= a ^= b;
}

//ð������
template<typename T>
long long bubble_sort(T arr[], int l, int r)
{
	long long cnt = 0;
	for (int i = l; i < r; i++)
	{
		bool exchange = false;
		for (int j = r - 1; j >= i; j--)
		{
			if (arr[j - 1] > arr[j])
			{
				my_swap(arr[j - 1], arr[j]);
				cnt++;
				exchange = true;
			}
		}
		if (exchange == false)
			return cnt;
	}
	return cnt;
}

//ѡ������
template<typename T>
long long select_sort(T arr[], int l, int r) {
	static long long cnt = 0;
	for (int i = l; i < r; ++i)
	{
		int min = i;
		for (int j = i + 1; j < r; ++j)
		{
			if (arr[j] < arr[min])
				min = j;
			++cnt;
		}
		if (min != i)
		{
			my_swap(arr[i], arr[min]);
			++cnt;
		}
	}
	return cnt;
}

//ֱ�Ӳ�������
template<typename T>
long long insert_sort(T arr[], int l, int r) {
	long long cnt = 0;
	for (int i = l + 1; i < r; i++) {
		T key = arr[i];
		int j = i - 1;
		while (j >= 0 && key < arr[j]) {
			arr[j + 1] = arr[j];
			j--;
			cnt++;
		}
		arr[j + 1] = key;
		cnt++;
	}
	return cnt;
}

//ϣ������
template<typename T>
long long shell_sort(T arr[], int l, int r) {
	long long cnt = 0;
	for (int gap = (r - l + 1) / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < r; i++) {
			T tmp = arr[i];
			int j;
			for (j = i; j >= gap && tmp < arr[j - gap]; j -= gap)
				arr[j] = arr[j - gap];
			arr[j] = tmp, cnt++;
		}
	}
	return cnt;
}

//��������
template<typename T>
long long quick_sort(T arr[], int l, int r)
{
	long long cnt = 0;
	if (l >= r) return 0;
	int i = l - 1, j = r + 1;
	T x = arr[(l + r) >> 1];
	while (i < j)
	{
		do
		{
			i++;
		} while (arr[i] < x);
		do
		{
			j--;
		} while (arr[j] > x);
		if (i < j) my_swap(arr[i], arr[j]), cnt++;
	}
	return cnt + quick_sort(arr, l, j) + quick_sort(arr, j + 1, r);
}

const int DEFAULT_SIZE = 100;
//���ȶ��У�С���ѣ���
template<typename T>
class priQue
{
private:
	//����
	T* pArray;
	//�Ѵ�С
	int m_length;
	//����³�
	void swim(int k, long long& cnt);
	//����ϸ�
	void sink(int k, long long& cnt);
public:
	//Ĭ�Ϲ��캯��
	priQue();
	//ָ���Ѵ�С�Ĺ��캯��
	priQue(int N);
	//ȡ�Ѷ�
	T top();
	//�����Ѷ�
	void pop(long long& cnt);
	//��Ԫ�����
	void push(const T& v, long long& cnt);
	//�ж϶��Ƿ�Ϊ��
	bool empty();
	//��ȡ�Ѵ�С
	int size();
};

template <typename T>
void priQue<T>::swim(int k, long long& cnt)
{
	//��k������ݱ����ĸ����С����һֱ�ϸ�
	while (k > 1 && pArray[k] < pArray[k / 2]) {
		swap(pArray[k / 2], pArray[k]);
		cnt++;
		k /= 2;
	}
}

template <typename T>
void priQue<T>::sink(int k, long long& cnt)
{
	while (2 * k <= m_length)
	{
		int j = 2 * k;
		//�Ƚ�k�����Ҷ�����һ����С
		if (j < m_length && (pArray[j] > pArray[j + 1])) j++;
		//����Ѿ��³�����ȷλ�þ��˳�ѭ��
		if (pArray[k] < pArray[j]) break;
		//k����³���jλ��
		my_swap(pArray[k], pArray[j]);
		k = j;
		cnt++;
	}
}

template <typename T>
priQue<T>::priQue()
{
	pArray = new T[DEFAULT_SIZE + 1];
	m_length = 0;
}

template <typename T>
priQue<T>::priQue(int N)
{
	pArray = new T[N + 1];
	m_length = 0;
}

template <typename T>
T priQue<T>::top()
{
	return pArray[1];
}

template <typename T>
void priQue<T>::pop(long long& cnt)
{
	//���Ѷ���ĩβԪ�ؽ������ټ�С�Ѵ�С���ﵽ������Ч��
	swap(pArray[1], pArray[m_length--]);
	//�Ѷ��³���ά��С��������
	sink(1, cnt);
}

template <typename T>
void priQue<T>::push(const T& v, long long& cnt)
{
	//��ĩβ������Ԫ��
	pArray[++m_length] = v;
	//��Ҷ�ӽ���ϸ���ά��С��������
	swim(m_length, cnt);
}

template <typename T>
bool priQue<T>::empty()
{
	return m_length == 0;
}

template <typename T>
int priQue<T>::size()
{
	return m_length;
}


//������
template<typename T>
long long heap_sort(T arr[], int l, int r)
{
	long long cnt = 0;
	priQue<T>heap(r - l + 1);
	for (int i = l; i <= r; i++)
		heap.push(arr[i], cnt);
	for (int i = l; i <= r; i++)
		heap.pop(cnt);
	return cnt;
}

//���ֹ鲢
long long merge(int* arr, int* tmp, int l, int mid, int r)
{
	for (int k = l; k <= r; k++)
		tmp[k] = arr[k];
	int i = l, j = mid;
	for (int k = l; k <= r; k++)
	{
		if (i >= mid)
			arr[k] = tmp[j++];
		else if (j >= r)
			arr[k] = tmp[i++];
		else
		{
			if (tmp[j] < tmp[i])
				arr[k] = tmp[j++];
			else
				arr[k] = tmp[i++];
		}
	}
	return r - l + 1;
}

//�鲢����
template<typename T>
long long merge_sort(T arr[], int l, int r)
{
	if (r - l <= 1)
		return 0;
	int mid = (l + r) / 2;
	int* tmp = new int[r + 1];
	long long cnt = merge_sort(arr, l, mid) + merge_sort(arr, mid, r) + merge(arr, tmp, l, mid, r);
	delete tmp;
	tmp = nullptr;
	return cnt;
}

//������������λ��
inline int max_digit(int arr[], int l, int r)
{
	int max_data = arr[l];
	for (int i = l + 1; i <= r; i++)
		if (max_data < arr[i])
			max_data = arr[i];
	int upper_bound = 10, num_of_digits = 1;
	while (upper_bound < max_data)
	{
		upper_bound *= 10;
		num_of_digits++;
	}
	return num_of_digits;
}

//MSD��������
long long radix_sort(int arr[], int l, int r)
{
	long long cnt = 0;
	int num_of_digits = max_digit(arr, l, r);
	int len = r - l + 1;
	int* tmp = new int[r + 1]; //��ʱ����Ź��������
	int* count = new int[10]; //0~9ÿ�����ֿ�һ��Ͱ��¼
	int radix = 1; //���� ��С����
	for (int i = 1; i <= num_of_digits; i++) //�ӵ͵���ÿһλ�ֱ�����
	{
		for (int j = 0; j < 10; j++)
			count[j] = 0; //��������
		cnt += 10;
		for (int j = l; j <= r; j++)
		{
			int k = (arr[j] / radix) % 10; //��ȡ��Ӧ��λ��ֵ
			count[k]++;
		}
		for (int j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j];
		cnt += 9;
		for (int j = r; j >= l; j--)
		{
			int k = (arr[j] / radix) % 10;
			tmp[count[k] - 1] = arr[j];
			count[k]--;
		}
		for (int j = 0; j < len; j++)
			arr[j] = tmp[j];
		radix *= 10;
	}
	delete[] tmp;
	delete[] count;
	return cnt;
}
const char init_prompts[12][100] =
{
	"**          �����㷨�Ƚ�          **",
	"************************************",
	"**         1 --- ð������         **",
	"**         2 --- ѡ������         **",
	"**         3 --- ֱ�Ӳ�������     **",
	"**         4 --- ϣ������         **",
	"**         5 --- ��������         **",
	"**         6 --- ������           **",
	"**         7 --- �鲢����         **",
	"**         8 --- ��������         **",
	"**         9 --- �˳�����         **",
	"************************************"
};
const char name[8][20] =
{
	"ð������","ѡ������","ֱ�Ӳ�������","ϣ������","��������","������","�鲢����","��������"
};
int main() {
	for (int i = 0; i < 12; i++)
		cout << init_prompts[i] << endl;
	int num = -1;
	cout << endl << "��ѡ��Ҫ���ɵ������������";
	cin >> num;
	while (cin.fail() || num <= 0) {
		//������
		cerr << "���������������";
		cin.clear();
		cin.ignore(1024, '\n');
		cin >> num;
	}
	cout << endl;
	int *arr0 = new int[num + 1], *arr = new int[num + 1];
	std::default_random_engine e{ random_device{}() };
	for (int i = 0; i <= num; i++)
		arr0[i] = (int)(e() % 1000000000);
	while (1) {
		int opt = 0;
		do
		{
			cout << "��ѡ�������㷨��";
			cin >> opt;
			if (opt < 1 || opt>9)
			{
				cerr << "�����������������1~9֮��Ĳ���" << endl;
				cin.clear();
				cin.ignore(1024, '\n');
			}
		} while (opt < 1 || opt > 9);
		if (opt == 9)
			break;
		for (int i = 1; i <= num; i++)
			arr[i] = arr0[i];
		size_t t1 = clock();
		long long exchange_num = 0;
		switch (opt) {
		case 1:
			exchange_num = bubble_sort<int>(arr, 1, num);
			break;
		case 2:
			exchange_num = select_sort<int>(arr, 1, num);
			break;
		case 3:
			exchange_num = insert_sort<int>(arr, 1, num);
			break;
		case 4:
			exchange_num = shell_sort<int>(arr, 1, num);
			break;
		case 5:
			exchange_num = quick_sort<int>(arr, 1, num);
			break;
		case 6:
			exchange_num = heap_sort<int>(arr, 1, num);
			break;
		case 7:
			try
			{
				exchange_num = merge_sort<int>(arr, 1, num);
			}
			catch (exception& exc)
			{
				cerr << exc.what() << endl;
			};
			break;
		case 8:
			exchange_num = radix_sort(arr, 1, num);
			break;
		default:
			break;
		}
		cout << name[opt - 1] << (opt == 7 ? "�Ƚϴ�����  " : "����������  ") << exchange_num << endl;
		size_t t2 = clock();
		cout << name[opt - 1] << "����ʱ�䣺  " << t2 - t1 << endl << endl;
	}
	return 0;
}