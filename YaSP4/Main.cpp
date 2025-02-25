#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>

class RandList
{
private:
	std::list<int> list;
public:
	RandList() {};
	RandList(const RandList& other);
	RandList& operator=(const RandList& other);
	RandList(const size_t size);
	RandList(std::ifstream& file);
	void fill_generate(const int radius);
	void fill_iter(const int radius);
	int abs_min() const;
	RandList modify_for() const;
	RandList modify_transform() const;
	friend std::ostream& operator<<(std::ostream& os, const RandList& rlist);
};

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	RandList list(10);
	list.fill_generate(100);
	std::cout << list << '\n';
	RandList list2 = list.modify_for();
	std::cout << list2 << '\n';
}

std::ostream& operator<<(std::ostream& os, const RandList& rlist)
{
	for (const int i : rlist.list)
		os << i << ' ';
	return os;
}

RandList::RandList(const RandList& other)
{
	for (const int i : other.list)
		this->list.push_back(i);
}

RandList& RandList::operator=(const RandList& other)
{
	if (this != &other)
	{
		list.clear();
		for (const int i : other.list)
			this->list.push_back(i);
	}
	return *this;
}

RandList::RandList(const size_t size)
{
	for (size_t i{}; i < size; ++i)
		list.push_back(0);
}

RandList::RandList(std::ifstream& file)
{
	int elem{};
	while (!file.eof())
	{
		file >> elem;
		list.push_back(elem);
	}
}

void RandList::fill_generate(const int radius)
{
	std::generate_n(list.begin(), list.size(), [&]() { return rand() % (2 * radius) - radius; });
}

void RandList::fill_iter(const int radius)
{
	for (int i : list)
		i = rand() % (2 * radius) - radius;
}

int RandList::abs_min() const
{
	int result = abs(list.front());
	for (const int i : list)
	{
		if (abs(i) < result)
			result = abs(i);
	}
	return result;
}

RandList RandList::modify_for() const
{
	RandList res_list{};
	int sqrt_abs_min = trunc(sqrt(abs_min()));

	// перебор списка и прибавление к каждому второму числу sqrt_abs_min
	bool second = false;
	for (const int i : list)
	{
		if (second == true)
		{
			res_list.list.push_back(i + sqrt_abs_min);
			second = false;
		}
		else
		{
			res_list.list.push_back(i);
			second = true;
		}
	}
	return res_list;
}

RandList RandList::modify_transform() const // need to test
{
	RandList res_list{};
	int sqrt_abs_min = trunc(sqrt(abs_min()));
	bool second = false;
	std::transform(list.begin(), list.end(), std::back_inserter(res_list), [&second, sqrt_abs_min](int a)
		{
			if (second)
			{
				second = false;
				return a + sqrt_abs_min;
			}
			else
			{
				second = true;
				return a;
			}
		});

}


