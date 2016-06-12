#include<stdlib.h>
#include<assert.h>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

class Min_pq
{
	private:
		//vector<unsigned int> arr_linear;
		vector<unsigned int> arr;
		unsigned int len;


	public:
		Min_pq() { srand(time(NULL)); len=0; }
		unsigned int size() { return len; }
		
		//void read_input_from_file();
		void build_random_input();
		
		void init_from_rand_array();
		void fix_down(unsigned int i);
		void fix_up(unsigned int i);

		void insert(const unsigned int x);
		unsigned int get_root();
		unsigned int pop_root();

		void test(unsigned int count);
};

void Min_pq::test(unsigned int count)
{
	while(count > 0)
	{
		arr.clear();
		//arr_linear.clear();	
		len = 0;
		build_random_input();

		cout<<"Random input= ";
		for(int i=1; i<=size(); i++)
			cout<< arr[i] <<" ";
		cout<<endl;

		vector<unsigned int> arr_linear = arr;
		//arr_linear = arr;
		
		init_from_rand_array();
		
		unsigned int add_count = rand()%50;
		for(int i=0; i<add_count; i++)
		{
			unsigned int val = rand()%100;
			insert(val);
			arr_linear.push_back(val);
		}	
		sort(arr_linear.begin()+1, arr_linear.end());

		for(int i=1;i< arr_linear.size(); i++)
		{
			if(arr_linear[i] != get_root())
			{
				cout<<"Sorted val= " << arr_linear[i] <<", min-pq val= " << get_root() << endl;
				assert(false);
			}	
			else
			{
				//cout <<"Same vale " << get_root() << endl;	
				pop_root();	
			}	
		}

		count--;
	}
}


void Min_pq::build_random_input()
{
	len = 5+rand()%50;

	arr.push_back(len);
	for(int i=0; i<len; i++)
		arr.push_back(rand()%100);
}

void Min_pq::init_from_rand_array()
{
	for(int i=size()/2; i>0; i--)
	{
		fix_down(i);
	}
}

void Min_pq::fix_down(unsigned int i)
{
	while(i <= size()/2)
	{
		unsigned int min_index = i;
		if(arr[2*i] < arr[min_index])
		{
			min_index = 2*i;
		} 
		if(2*i+1 <=len && arr[2*i+1] < arr[min_index])
		{
			min_index = 2*i+1;
		}
		if(min_index == i)
			break;

		unsigned int tmp = arr[i];
		arr[i] = arr[min_index];
		arr[min_index] = tmp;
		i = min_index;
	}
}

void Min_pq::fix_up(unsigned int i)
{
	while(i > 1)
	{
		unsigned int p_index = i/2;
		if(arr[i] >= arr[p_index])
		{
			break;	
		}

		unsigned int tmp = arr[i];
		arr[i] = arr[p_index];
		arr[p_index] = tmp;
		i = p_index;
	}
}


void Min_pq::insert(const unsigned int x)
{
	len++;
	arr.push_back(x);
	fix_up(len);
}


unsigned int Min_pq::get_root()
{
	if(size() > 0)
		return arr[1];
	else
	{
		assert(false);
		return 0;
	}	
}

unsigned int Min_pq::pop_root()
{
	if(len == 0)
		assert(false);

	unsigned int result = arr[1];
	len--;
	arr[1] = arr[len+1];
	fix_down(1);
}



int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		cout <<"\n Usage:- exe test_iteration-count\n";
		exit(0);
	}
	Min_pq obj;
	obj.test(atoi(argv[1]));
	return 0;
}
