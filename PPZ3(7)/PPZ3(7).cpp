#include <iostream>
using namespace std;
using std::cout;
struct Node
{
	int data;
	Node* next;
	Node(int val) : data(val), next(nullptr) {}
};
void add(Node*& head, int N, int j)
{
	if (N > j)
	{
		int n;
		n = rand() % 10105-104;
		Node* cur = new Node(n);
		head->next = cur;
		j++;
		add(cur, N, j);
	}
}

void show(Node* head)
{
	Node* current = head;
	while (current != nullptr) {
		cout << current->data << " ";
		current = current->next;
	}
	cout << endl;
}
void deleteList(Node* head)
{
	while (head != nullptr) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}
void insertionSort(Node*& head) {
	if (head == nullptr || head->next == nullptr) {
		return;
	}
	Node* sorted = nullptr;
	while (head != nullptr) {
		Node* current = head;
		head = head->next;
		if (sorted == nullptr || current->data < sorted->data) {
			current->next = sorted;
			sorted = current;
		}
		else {
			Node* temp = sorted;
			while (temp->next != nullptr && temp->next->data < current->data) {
				temp = temp->next;
			}
			current->next = temp->next;
			temp->next = current;
		}
	}
	head = sorted;
}
void mergeAllLists(Node**& lists, int K) {
	if (K == 0) {
		return;
	}
	Node* current = lists[0];
	for (int i = 1; i < K; i++) {
		if (lists[i] == nullptr) {
			// Пропускаємо порожні списки
			continue;
		}

		while (current->next) {
			current = current->next;
		}

		current->next = lists[i];
	}
}

int main()
{
	int N = -1, K = -1, i = 0, M = 10000;
	srand(time(NULL));
	do {
		cout << "Count of lists (0 < K < 10000): ";
		cin >> K;
	} while (K >= 10000 || K <= 0);
	Node** t = new Node*[K];
	for (i = 0; i < K; i++)
	{
		do {
			cout << "Count of elements (1 < N < 500) in list " << i <<": ";
			cin >> N;
		} while (N >= 500 || N <= 0);
		t[i] = new Node(0);
		add(t[i], N, 0);
		t[i] = t[i]->next;
	}
	for (i = 0; i < K; i++)
	{
		insertionSort(t[i]);
		cout << "\n List " << i << " after sorting: ";
		show(t[i]);
	}
	for (i = 0; i < K; i++)
	{
		mergeAllLists(t, K);
	}
	cout << "\n Merged list: ";
	show(t[0]);
	insertionSort(t[0]);
	cout << "\n Merged list: ";
	show(t[0]);
	for (int i = 0; i < K; i++)
	{
		delete t[i];
	}
	delete[] t;
	return 0;
}