
#include <iostream>
#include <string>
#include<fstream>
#include<string.h>
using namespace std;
class Node {
public:
	int counter=1;
	string word;
	Node* next;
	Node( string word="", Node* next = NULL) : word(word), next(next){ }
};
class List {
	Node* root;
	Node* tail;
public:
	List(){ 
		root = new Node();
		tail = root;
		tail->next= new Node();
	}
	Node* begin() const { return root->next; }
	Node* end() const { return tail->next; }
	bool isEmpty()const { return begin() == end(); }

	Node* find(const string word1) {
		Node* tmp = begin();
		Node* stop = end();
		while (tmp != stop  ) {

		if(_strcmpi(word1.c_str(), tmp->word.c_str()) == 0){
			 return tmp;
		}
		else tmp = tmp->next;
		}
		tmp = NULL;
		return tmp;
	}
	bool control(Node* tmp) {
		if (tmp == NULL) { return 0; }
		else if (tmp != NULL) { return 1; }
	}
	void insert(Node* pos, string word) {
		Node* tmp = find(word);
		bool a = control(tmp);
		if (a==1) {
			tmp->counter++;
		}
		else{			
		
		 if (pos == end()) {
			tail->next = new Node(word,end());
			tail=tail->next;
		}
		
	    }
	}
	void push_back(const string word) {
		insert(end(), word);
	}
	void swap(Node* a,Node*b) {
		string tempword = a->word;
		int tempcounter = a->counter;
		a->counter = b->counter;
		b->counter = tempcounter;
		a->word = b->word;
		b->word = tempword;
	}
	void Sorts(Node* node)
	{
		if (node == NULL) {
			return;
		}
		bool state = 1;
		while (state) {
			Node* iter = node;
			state = 0;
			while (iter->next != end()) {
				if (iter->counter < iter->next->counter) {
					swap(iter, iter->next);
					state = 1;
				}
				iter = iter->next;
			}
		}
	}
	void print() {
		int i = 0;
		Node* tmp = begin();
		while (tmp != end()&&i<10) {
			if(tmp->word.size()>1){
			cout << tmp->counter << " " << tmp->word<<endl;
			tmp = tmp->next;
			
			i++;
			}
		}
	}
};
void fileoclapse(List* list ) {
	ifstream bannedwords("stopwords.txt");
	string bannedwordss;
	string word;
	ifstream reading;
	while (bannedwords >> word) {
		bannedwordss = bannedwordss + " " + word;
	}
	for (size_t i = 0; i <= 21; i++) {
		int read = 0;
		string filename = "reut2-0";
		string filetype = ".sgm";
		string number;
		if (i < 10) number = "0" + to_string(i);
		else number = to_string(i);
		filename = filename + number + filetype;
		
		reading.open(filename);
		while (reading >> word) {
			if (word.find("BODY>") != string::npos) {
				read++;
				reading >> word;
			}
			if (read % 2 == 1) {
				int index;
				while ((index = word.find_first_of(".,!?;-*+<()/=")) != string::npos)
				{
					int it = index + 1;
					word.replace(index, it, "");
				}
				if ((bannedwordss.find(word)) != string::npos)
				{
					word.replace(0, word.size(), "");
				}
				if(word.size()>1){
					list->push_back(word);
				}
			}
		}
		reading.close();
	}
}
int main() {
	List* list=new List;
	fileoclapse(list);
	list->Sorts(list->begin());
	list->print();
}						