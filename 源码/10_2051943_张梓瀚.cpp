#include <cstdlib>
#include <random>
#include <iostream>
using namespace std;

template<typename T>
void my_swap(T& a, T& b)
{
	a ^= b ^= a ^= b;
}

//冒泡排序
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

//选择排序
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

//直接插入排序
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

//希尔排序
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

//快速排序
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
//优先队列（小顶堆）类
template<typename T>
class priQue
{
private:
	//数据
	T* pArray;
	//堆大小
	int m_length;
	//结点下沉
	void swim(int k, long long& cnt);
	//结点上浮
	void sink(int k, long long& cnt);
public:
	//默认构造函数
	priQue();
	//指定堆大小的构造函数
	priQue(int N);
	//取堆顶
	T top();
	//弹出堆顶
	void pop(long long& cnt);
	//将元素入堆
	void push(const T& v, long long& cnt);
	//判断堆是否为空
	bool empty();
	//获取堆大小
	int size();
};

template <typename T>
void priQue<T>::swim(int k, long long& cnt)
{
	//若k结点数据比它的父结点小，则一直上浮
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
		//比较k的左右儿子哪一个较小
		if (j < m_length && (pArray[j] > pArray[j + 1])) j++;
		//如果已经下沉到正确位置就退出循环
		if (pArray[k] < pArray[j]) break;
		//k结点下沉到j位置
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
	//将堆顶与末尾元素交换，再减小堆大小，达到弹顶的效果
	swap(pArray[1], pArray[m_length--]);
	//堆顶下沉，维护小顶堆性质
	sink(1, cnt);
}

template <typename T>
void priQue<T>::push(const T& v, long long& cnt)
{
	//在末尾加入新元素
	pArray[++m_length] = v;
	//该叶子结点上浮，维护小顶堆性质
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


//堆排序
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

//部分归并
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

//归并排序
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

//求数组的最大数位数
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

//MSD基数排序
long long radix_sort(int arr[], int l, int r)
{
	long long cnt = 0;
	int num_of_digits = max_digit(arr, l, r);
	int len = r - l + 1;
	int* tmp = new int[r + 1]; //临时存放排过序的数据
	int* count = new int[10]; //0~9每个数字开一个桶记录
	int radix = 1; //基数 从小到大
	for (int i = 1; i <= num_of_digits; i++) //从低到高每一位分别排序
	{
		for (int j = 0; j < 10; j++)
			count[j] = 0; //数组清零
		cnt += 10;
		for (int j = l; j <= r; j++)
		{
			int k = (arr[j] / radix) % 10; //提取对应数位数值
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
	"**          排序算法比较          **",
	"************************************",
	"**         1 --- 冒泡排序         **",
	"**         2 --- 选择排序         **",
	"**         3 --- 直接插入排序     **",
	"**         4 --- 希尔排序         **",
	"**         5 --- 快速排序         **",
	"**         6 --- 堆排序           **",
	"**         7 --- 归并排序         **",
	"**         8 --- 基数排序         **",
	"**         9 --- 退出程序         **",
	"************************************"
};
const char name[8][20] =
{
	"冒泡排序","选择排序","直接插入排序","希尔排序","快速排序","堆排序","归并排序","基数排序"
};
int main() {
	for (int i = 0; i < 12; i++)
		cout << init_prompts[i] << endl;
	int num = -1;
	cout << endl << "请选择要生成的随机数个数：";
	cin >> num;
	while (cin.fail() || num <= 0) {
		//错误处理
		cerr << "请重新输入个数：";
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
			cout << "请选择排序算法：";
			cin >> opt;
			if (opt < 1 || opt>9)
			{
				cerr << "输入错误，请重新输入1~9之间的操作" << endl;
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
		cout << name[opt - 1] << (opt == 7 ? "比较次数：  " : "交换次数：  ") << exchange_num << endl;
		size_t t2 = clock();
		cout << name[opt - 1] << "所用时间：  " << t2 - t1 << endl << endl;
	}
	return 0;
}