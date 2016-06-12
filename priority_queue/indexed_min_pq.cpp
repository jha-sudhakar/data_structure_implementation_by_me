#include<stdlib.h>
#include<assert.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<map>

using namespace std;

class Min_pq
{
	private:
		//vector<unsigned int> arr_linear;
		vector<unsigned int> arr;
		unsigned int len;
		map<unsigned int, vector<unsigned int> >hash;


	private:
		void init_from_rand_array();
		void fix_down(unsigned int i);
		void fix_up(unsigned int i);

		void update_hash(unsigned int old_key, unsigned int old_pos, unsigned int new_key, unsigned int new_pos);
		void insert_hash(unsigned int key, unsigned int pos);
		void remove_hash(unsigned int key, unsigned int pos);
		bool is_found_in_hash(unsigned int key, unsigned int pos);
		void validate_hash();
	public:
		Min_pq() { srand(time(NULL)); len=0; }
		unsigned int size() { return len; }
		
		//void read_input_from_file();
		void build_random_input();

		void insert(const unsigned int x);
		void update(unsigned int key, unsigned int new_key);
		unsigned int get_root();
		unsigned int pop_root();

		void test(unsigned int count);
};

void Min_pq::update_hash(unsigned int old_key, unsigned int old_pos, unsigned int new_key, unsigned int new_pos)
{
	int i=0;
	for(i=0; i< hash[old_key].size(); i++)
	{
		if(hash[old_key][i] == old_pos)
		break;
	}
	if(i == hash[old_key].size())
	{
		cout<<"\n Old_key = " << old_key <<", new_key= " << new_key << endl;
		assert(false);

	}	

	hash[old_key].erase( hash[old_key].begin()+i);
	if(hash[old_key].size() == 0)
		hash.erase(old_key);

	hash[new_key].push_back(new_pos);
}


void Min_pq::insert_hash(unsigned int key, unsigned int pos)
{
	hash[key].push_back(pos);
}

void Min_pq::remove_hash(unsigned int key, unsigned int pos)
{
	int i=0;
	for(i=0; i< hash[key].size(); i++)
	{
		if(hash[key][i] == pos)
		break;
	}
	if(i == hash[key].size())
	{
		cout<<"\n Not found key= " << key <<" pos= " << pos << endl;	
		assert(false);
	}	
	hash[key].erase(hash[key].begin()+i);

	if(hash[key].size() == 0)
		hash.erase(key);
}

bool Min_pq::is_found_in_hash(unsigned int key, unsigned int pos)
{
	bool is_found = false;
	for(int i=0; i<hash[key].size(); i++)
	{
		if(pos == hash[key][i])
			return true;
	}
	return is_found;
}

void Min_pq::validate_hash()
{
	unsigned int val_count=0;
	map<unsigned int, vector<unsigned int> >::iterator itr;
	for(itr=hash.begin(); itr!=hash.end(); itr++)
	{
		val_count += ((itr->second).size());
	}
	
	if(val_count != len)
		assert(false);

	for(int i=1; i<=len; i++)
	{
		if(false == is_found_in_hash(arr[i], i))
			assert(false);
	}
}


void Min_pq::build_random_input()
{
	len = 5+rand()%50;

	arr.push_back(len);
	for(int i=0; i<len; i++)
	{
		unsigned int val = rand()%100;
		arr.push_back(val);
		insert_hash(val, arr.size()-1);
	}	
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

		update_hash(arr[i], i, arr[i], min_index);
		update_hash(arr[min_index], min_index, arr[min_index], i);

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

		update_hash(arr[i], i, arr[i], p_index);
		update_hash(arr[p_index], p_index, arr[p_index], i);

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
	insert_hash(x,len);
	fix_up(len);
}

void Min_pq::update(unsigned int key, unsigned int new_key)
{
	if(key == new_key)
		return ;

	if(hash.end() == hash.find(key))
	{
		assert(false); //return;
	}	
	if(hash[key].size() == 0)
		assert(false);
		
	unsigned int pos = hash[key][hash[key].size()-1];
	hash[key].pop_back();
	if(hash[key].size() == 0)
		hash.erase(key);
	hash[new_key].push_back(pos);
	arr[pos] = new_key;

	if(new_key < key)
		fix_up(pos);
	else
		fix_down(pos);
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

	remove_hash(arr[len], len);
	insert_hash(arr[len], 1);
	remove_hash(arr[1], 1);
	
	unsigned int result = arr[1];
	arr[1] = arr[len];
	len--;
	fix_down(1);
}

void Min_pq::test(unsigned int count)
{
	while(count > 0)
	{
		arr.clear();
		//arr_linear.clear();	
		hash.clear();
		len = 0;
		build_random_input();

		cout<<"Random input= ";
		for(int i=1; i<=size(); i++)
			cout<< arr[i] <<" ";
		cout<<endl;

		vector<unsigned int> arr_linear = arr;
		//arr_linear = arr;
		
		init_from_rand_array();
		validate_hash();  	
#if 1		
		unsigned int add_count = rand()%50;
		for(int i=0; i<add_count; i++)
		{
			unsigned int val = rand()%100;
			insert(val);
			arr_linear.push_back(val);
			validate_hash();  	
		}	
#endif
		
#if 1
		unsigned int modify_count = rand()%50;
		for(int i=0; i<modify_count; i++)
		{
			unsigned int val = rand()%100;
			unsigned int index = (1+rand()%len);
			int k=0;
			for(k=1; k<arr_linear.size(); k++)
			{
				if(arr_linear[k] == arr[index])
				{
					arr_linear[k] = val;
					break;
				}
			}
			if(k == arr_linear.size())
				assert(false);
			
			update(arr[index], val);
			validate_hash();  	
		}	
#endif

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
			validate_hash();  	
		}

		count--;
	}
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
