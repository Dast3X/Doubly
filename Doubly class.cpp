#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>


using namespace std;

string DATASET = "dataset.csv";



template<typename T>
class Doubly
{
public:
	Doubly()
	{
		this->tail = nullptr;
		this->head = nullptr;
		this->size = 0;
	}
	unsigned int length() { return this->size; }
	void erase(unsigned int index)
	{
		if (index < 0 || index >(unsigned int)(size - 1))
			throw new out_of_range("Out of bound");
		int iteration = 0;
		auto currentNode = this->head;
		if (size == 1)
		{
			delete head;
			head = tail = nullptr;
			size--;
			return;
		}
		if (size > 1)
		{
			Node* temp = new Node();
			float midElement = ((float)(size - 1)) / 2;
			if (index <= midElement)
			{

				auto currentNode = this->head;
				if (index == 0)
				{
					temp = head->pNext;
					delete head;
					temp->pPrev = nullptr;
					head = temp;
					size--;
					return;
				}
				while (currentNode != nullptr)
				{
					if (iteration == index)
					{
					
						temp->pNext = currentNode->pNext;
						temp->pPrev = currentNode->pPrev;
						delete currentNode;
						temp->pPrev->pNext = temp->pNext;
						temp->pNext->pPrev = temp->pPrev;
						size--;
						return;
					}
					currentNode = currentNode->pNext;
					iteration++;
				}
			}
			else if (index > midElement)
			{
					auto currentNode = this->tail;
					iteration = size - 1;
					if (index == iteration)
					{
						temp = tail->pPrev;
						delete tail;
						temp->pNext = nullptr;
						tail = temp;
						size--;
						return;
					}
					while (currentNode != nullptr)
					{
						if (iteration == index)
						{
							temp->pNext = currentNode->pNext;
							temp->pPrev = currentNode->pPrev;
							delete currentNode;
							temp->pPrev->pNext = temp->pNext;
							temp->pNext->pPrev = temp->pPrev;
							size--;
							return;
						}
						currentNode = currentNode->pPrev;
						iteration--;
					}
			}
			throw exception("Something goes wrong while erasing");
		}
	}
	T& get(unsigned int index)
	{
		if (index < 0 || index > (unsigned int)(size - 1))
			throw new out_of_range("Out of bound");
		int iteration = 0;
		
		if (size == 1)
			return head->data;
		else if (size > 1)
		{
			float midElement = ((float)(size-1)) / 2;
			if (index <= midElement)
			{
				auto currentNode = this->head;
				while (currentNode != nullptr)
				{
					if (iteration == index)
					{
						return currentNode->data;
					}
					currentNode = currentNode->pNext;
					iteration++;
				}
			}
			else if (index > midElement)
			{
				auto currentNode = this->tail;
				iteration = size - 1;
				while (currentNode != nullptr)
				{
					if (iteration == index)
					{
						return currentNode->data;
					}
					currentNode = currentNode->pPrev;
					iteration--;
				}
			}
		}
		throw exception("Something goes wrong :(");
	}
	void append(T data)
	{

		if (head == nullptr && tail == nullptr)
		{
			Node* first_node = new Node(data);
			tail = head = first_node;
			tail->pNext = nullptr;
			head->pPrev = nullptr;
			size++;
		}
		else
		{
			auto prevNode = tail;
			tail = new Node(data);
			prevNode->pNext = tail;
			tail->pPrev = prevNode;
			size++;
		}
	}
	void insert(unsigned int index, T value)
	{
		if (index < 0 || index >(unsigned int)(size))
			throw new out_of_range("Out of bound");
		if (index == size)
			{
				this->append(value);
				return;
			}
		auto currentNode = this->head;
		if (index == 0)
			{
				head = new Node(value);
				head->pNext = currentNode;
				currentNode->pPrev = head;
				size++;
				return;
			}

		float midElement = ((float)(size - 1)) / 2;
		int iteration = 0;
		if (index <= midElement)
		{
			Node* currentNode = this->head;
			for (unsigned int i = 0; i < index - 1; i++)
				currentNode = currentNode->pNext;
			Node* newNode = new Node(value, currentNode->pNext, currentNode->pPrev);
			currentNode->pNext = newNode;
			currentNode->pPrev = newNode;
			size++;
			return;
		}
		else if (index > midElement)
		{
			Node* currentNode = this->tail;
			for (unsigned int i = this->size - 1; i > index; i--)
				currentNode = currentNode->pPrev;
			Node* newNode = new Node(value, currentNode->pNext, currentNode->pPrev);
			currentNode->pNext = newNode;
			currentNode->pPrev = newNode;
			size++;
			return;
		}
		throw exception("Something goes wrong while erasing");
	}
	void clear()
	{
		while(size)
		{
			erase(0);
		}
		return;
	}
	T& operator[](unsigned int index)
	{
		if (index < 0 || index > (unsigned int)(size - 1))
			throw new out_of_range("Out of bound");
		int iteration = 0;

		if (size == 1)
			return head->data;
		else if (size > 1)
		{
			float midElement = ((float)(size - 1)) / 2;
			if (index <= midElement)
			{
				auto currentNode = this->head;
				while (currentNode != nullptr)
				{
					if (iteration == index)
					{
						return currentNode->data;
					}
					currentNode = currentNode->pNext;
					iteration++;
				}
			}
			else if (index > midElement)
			{
				auto currentNode = this->tail;
				iteration = size - 1;
				while (currentNode != nullptr)
				{
					if (iteration == index)
					{
						return currentNode->data;
					}
					currentNode = currentNode->pPrev;
					iteration--;
				}
			}
		}
		throw exception("Something goes wrong :(");
	}

private:
	class Node
	{
	public:
		Node* pNext;
		Node* pPrev;
		T data;
		Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
	};
	Node* head; 
	Node* tail;
	unsigned size;
	
};

struct Passenger
{
	bool survived{};
	int passengerClass{};
	string name{};
	string gender{};
	unsigned short age{};
	unsigned short sibblingsAboard{};
	unsigned short familyAboard{};
	float fare{};
};

Passenger parseLine(string line)
{
	Passenger passenger;
	string temp;
	int i = 0;
	for (; line[i] != ','; i++)
		temp += line[i];
	if (line[i] == ',')
		i++;
	passenger.survived = stoi(temp);

	temp = "";
	for (; line[i] != ','; i++)
		temp += line[i];
	if (line[i] == ',')
		i++;
	passenger.passengerClass = stoi(temp);

	temp = "";
	for (; line[i] != ','; i++)
		temp += line[i];
	if (line[i] == ',')
		i++;
	passenger.name = temp;

	temp = "";
	for (; line[i] != ','; i++)
		temp += line[i];
	if (line[i] == ',')
		i++;
	passenger.gender = temp;

	temp = "";
	for (; line[i] != ','; i++)
		temp += line[i];
	if (line[i] == ',')
		i++;
	passenger.age = stoi(temp);

	temp = "";
	for (; line[i] != ','; i++)
		temp += line[i];
	if (line[i] == ',')
		i++;
	passenger.sibblingsAboard = stoi(temp);

	temp = "";
	for (; line[i] != ','; i++)
		temp += line[i];
	if (line[i] == ',')
		i++;
	passenger.familyAboard = stoi(temp);

	temp = "";
	for (; line[i] != '\0'; i++)
		temp += line[i];
	passenger.fare = stof(temp);
	return passenger;
}


void readFile(string DATASET, Doubly<Passenger>& passengers)
{
	string line;
	ifstream file;
	file.open(DATASET);
	getline(file, line);
	while (!file.eof())
	{
		getline(file, line);
		passengers.append(parseLine(line));
	}
	file.close();
}

ostream& operator<<(ostream& out, const Passenger& passenger)
{
	if (passenger.name == "")
	{
		out << "";
		return out;
	}
	out << "Survived: " << ((passenger.survived == 0) ? "false" : "true") << '\n'
		<< "Class: " << passenger.passengerClass << '\n'
		<< "Name: " << passenger.name << '\n'
		<< "Gender: " << passenger.gender << '\n'
		<< "Age: " << passenger.age << '\n'
		<< "Sibblings: " << passenger.sibblingsAboard << '\n'
		<< "Family: " << passenger.familyAboard << '\n'
		<< "Fare: " << passenger.fare;
	return out;
}

Passenger findElementByName(string name, Doubly<Passenger>& passengers)
{
	Passenger passenger;
	for (unsigned i = 0; i < passengers.length(); i++)
		if (name == passengers[i].name)
			return passengers[i];
	cout << "Doesn't exist";
	return passenger;
}
Doubly<Passenger> filterByAge(unsigned age, Doubly<Passenger>& passengers)
{
	Doubly<Passenger> pass;
	for (unsigned i = 0; i < passengers.length(); i++)
	{
		if (age == passengers[i].age)
		{
			pass.append(passengers[i]);
		}
	}
	if (pass.length() == 0)
		throw exception("Can't find person with this age");
	return pass;
}
void findTheEldest(Doubly<Passenger>& passengers)
{
	Passenger pass;
	pass = passengers[0];
	for (unsigned i = 0; i < passengers.length(); i++)
		if (pass.age < passengers[i].age)
			pass = passengers[i];
	cout <<"The eldest passenger info \n" << pass;
}
void findSafestClass(Doubly<Passenger>& passengers)
{
	int counter1 = 0, counter2 = 0, counter3 = 0,
		survived1 = 0, survived2 = 0, survived3 = 0;
	float ratio1, ratio2, ratio3;
	for (unsigned i = 0; i < passengers.length(); i++)
	{
		if (passengers[i].passengerClass == 1)
		{
			counter1++;
			if (passengers[i].survived == true)
				survived1++;
		}
		else if (passengers[i].passengerClass == 2)
		{
			counter2++;
			if (passengers[i].survived == true)
				survived2++;
		}
		else if (passengers[i].passengerClass == 3)
		{
			counter3++;
			if (passengers[i].survived == true)
				survived3++;
		}
	}
	ratio1 = ((float)survived1) / ((float)counter1);
	ratio2 = ((float)survived2) / ((float)counter2);
	ratio3 = ((float)survived3) / ((float)counter3);
	if (ratio1 > ratio2 && ratio1 > ratio3)
		cout << "Safest class is 1st\n" << "\npercentage of survived:\n";
	else if (ratio2 > ratio1 && ratio2 > ratio3)
		cout << "Safest class is 2st\n" << "\npercentage of survived:\n";
	else if (ratio3 > ratio1 && ratio3 > ratio2)
		cout << "Safest class is 3st\n" << "\npercentage of survived:\n";
	cout << "1st - " << ratio1*100 << "%\n"
		<< "2nd - " << ratio2*100 << "%\n"
		<< "3rd - " << ratio3*100 << "%";
}
void findUnluckiest(Doubly<Passenger>& passengers)
{
	Passenger pass;

	for (unsigned i = 0; i < passengers.length(); i++)
		if (pass.name == "" && passengers[i].survived == false)
			pass = passengers[i];
	for (unsigned i = 0; i < passengers.length(); i++)
		if (passengers[i].survived == false)
			if (passengers[i].fare > pass.fare)
				pass = passengers[i];
	cout << "Unluckiest is\n\n"
		<< pass;
}

int main()
{
	try
	{
		Doubly<Passenger> passengers;
		readFile(DATASET, passengers);
		cout << "##############################################\n1 variant\n\n";
		Passenger passenger = findElementByName("Miss. Laina Heikkinen", passengers);
		cout << passenger;
		cout << "\n\n##############################################\n2 variant";
		Doubly<Passenger> filterBy;
		filterBy = filterByAge(70, passengers);
		cout << '\n';
		for (unsigned i = 0; i < filterBy.length(); i++)
			cout << "\n" << filterBy[i] << '\n';
		cout << "\n\n##############################################\n3 variant\n\n";
		findTheEldest(passengers);
		cout << "\n\n##############################################\n4 variant\n\n";
		findTheEldest(passengers);
		cout << "\n\n##############################################\n5 variant\n\n";
		findSafestClass(passengers);
		cout << "\n\n##############################################\n6 variant\n\n";
		findUnluckiest(passengers);
		cout << "\n\n";
	}
	catch (const exception& e)
	{
		cout << "\n\n";
		cout << e.what();
		cout << "\n\n";
	}
}
