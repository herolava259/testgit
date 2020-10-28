#include<iostream>
#include<string>
using namespace std;

enum stateEnum {
	OPEN,
	CLOSE,
	LOCK,
	UNLOCK
};
class StateBase {
public:
	virtual StateBase* getNextState(int id) = 0;
	virtual string toString() = 0;
};

class Open :public StateBase {
public:
	virtual StateBase* getNextState(int id);
	virtual string toString() {
		string str = string("Opened");
		return str;
	}
};
class Close : public StateBase {
public:
	virtual StateBase* getNextState(int id);
	virtual string toString() {
		string str = string("Closed");
		return str;
	}
};
class Lock : public StateBase {
public:
	virtual StateBase* getNextState(int id);
	virtual string toString() {
		string str = string("Locked");
		return str;
	}
};


StateBase* Open::getNextState(int id) {
	switch (id)
	{
	case 1:
		return new Close();
	default:
		return NULL;
		break;
	}
}

StateBase* Close::getNextState(int id) {
	switch (id)
	{
	case 0:
		return new Open();
	case 2:
		return new Lock();
	default:
		return NULL;
		break;
	}
}
StateBase* Lock::getNextState(int id) {
	switch (id)
	{
	case 3:
		return new Close();
	default:
		return NULL;
		break;
	}
}

StateBase* getState(int id) {
	switch (id)
	{
	case 0:
		return new Open();
	case 1:
		return new Close();
	case 2:
		return new Lock();
	default:
		break;
	}
}

class Door {
private:
	StateBase* state;
public:
	Door() {
		state = new Lock();
	}
	Door(StateBase* state) {
		this->state = state;
	}
	~Door() {
		delete state;
	}
	void getdoorstate() {
		cout << "Current State Door is " << state->toString() << endl;
	}
	void StateChange(int id) {
		StateBase* s = state->getNextState(id);
		getdoorstate();
		if (s == NULL) {
			cout << "Invalid State Change" << endl;
		}
		else {
			delete state;
			state = s;
			cout << "The state has changed to " << state->toString() << endl;
		}
	}
};

int main() {
	int state_id = 1;
	cout << "0: Exit " << endl;
	cout << "1: Open" << endl;
	cout << "2: Close" << endl;
	cout << "3: Lock" << endl;
	cout << "4: Unlock" << endl;
	StateBase* s = getState(OPEN);
	Door* door = new Door(s);
	door->getdoorstate();
	while (state_id) {
		cout << "Enter the charater" << endl;
		cin >> state_id;
		door->StateChange(state_id - 1);
	}
	return 0;
}