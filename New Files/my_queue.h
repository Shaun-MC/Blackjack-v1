#ifndef MY_QUEUE_H_
#define MY_QUEUE_H_

#include <vector>
#include <iostream>

using namespace std;

const int kStartingQueueSize = 7;

class MyQueue
{
public:
	MyQueue();
	bool Pop();
	void Push(int value);

	int Front() const;
	int Back() const;

	int count() const;
	bool IsEmpty() const;
	friend ostream& operator<<(ostream& stream, const MyQueue& rhs);

private:
	vector<int> vec_;
	int count_;
	int back_;
	int front_;
	void doubleQueueSize();
};
#endif

