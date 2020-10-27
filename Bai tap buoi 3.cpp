#include<iostream>
#include<string>
#include<list>
using namespace std;

typedef struct Postion {
	int x;
	int y;
	/*struct Postion(int x_, int y_) {
		x = x_;
		y = y_;
	}*/
};

class BaseObject {
protected:
	int id;
	string name;
	Postion postion;
public:
	//static int count ;
	BaseObject() {
		//count++;
		cout <<"No."/*<<count */<< ": Base Object is created!";
		this->name = "Unknown";
		id = 0;
		postion.x = 0;
		postion.y = 0;

	}
	BaseObject(int id, string name, Postion pos){
		//count++;
		cout <<"No." /*<< count */<<": Base Object is created!";
		this->id = id;
		this->name = name;
		postion.x = pos.x;
		postion.y = pos.y;
	}
	 BaseObject(BaseObject& p) {
		 //count++;
		 cout <<"No."/*<<count */<<": Base Object is created" << endl;
		this->id = p.id;
		name = string(p.name);
		postion.x = p.postion.x;
		postion.y = p.postion.y;
		
		
	}
	virtual ~BaseObject() {
		
		cout <<"No." /*<< count */<<": Base Object: Destroy!";
		//count--;
	}
	string getName() {
		return this->name;
	}
	int getid() {
		return id;
	}
	virtual void printPosition() {
		cout <<this->name<<": Postion: " << "x = " << postion.x << " " << "y= " << postion.y << endl;
	}
	virtual void move(){
		cout  << this->name << "Move?" << endl;
	}
};

class DynamicObject : public BaseObject
{
public:
	DynamicObject(): BaseObject() {
		cout << "Dynamic Object is created" << endl;
		
	}
	//DynamicObjet(BaseObject& p): BaseObject(p) {}
	DynamicObject(int id, string name, Postion pos) : BaseObject(id, name, pos) {
		cout << "Dynamic Object is created" << endl;
	}
	DynamicObject( DynamicObject& d) : BaseObject(d) {
		cout << "Dynamic Object is created" << endl;
		
	}
	virtual ~DynamicObject() {
		cout << "Dynamic Object is destroyed!" << endl;
	}
	virtual void printPostion() {
		BaseObject::printPosition();
	}
	virtual void move() {
		BaseObject::move();
	}
};

class StaticObject : public BaseObject
{
public:
	StaticObject(): BaseObject(){
		cout << "Static Object is created!" << endl;
		
	}
	StaticObject(int id, string name, Postion pos) : BaseObject(id, name, pos)  {
		cout << "Static Object is created!" << endl;
	}
	StaticObject( StaticObject& s):BaseObject(s) {
		cout << "Static Object is created!" << endl;
	}
	virtual ~StaticObject() {
		cout << "Static Object is destroyed" <<endl;
	}
	virtual void printPostion() {
		cout << "Static Object:" << this->name << ":" << "x= " << postion.x << " " << "y=" << postion.y << endl;

	}
	virtual void move() {
		BaseObject::move();
	}
};

class Tree : public StaticObject
{
public:
	Tree() : StaticObject() {
		cout << "Tree " /*<< count*/ << "is created!" << endl;
		
	}
	Tree(int id, string name, Postion pos) : StaticObject(id, name, pos) {
		cout << "Tree"/*<<count*/<< "is created!" << endl;
	}
	Tree(Tree& t) :StaticObject(t) {
		cout << "Tree"/*<<count*/<<"is created!" << endl;
	}
	~Tree() {
		cout << "Tree" <<this->name <<" is destroyed!"<<endl;
	}
	void printPostion() {
		cout << "Tree Object:" << this->name << ":" <<"Postion: x= " << postion.x << " " << "y=" << postion.y << endl;
	}
	void move() {
		StaticObject::move();
		cout << "Noooo! Never move" << endl;
	}
};
class House : public StaticObject
{
public:
	House() : StaticObject() {
		cout << "House " /*<< count*/ << "is created!" << endl;

	}
	House(int id, string name, Postion pos) : StaticObject(id, name, pos) {
		cout << "Tree" /*<< count */ << "is created!" << endl;
	}
	House(House& t) :StaticObject(t) {
		cout << "Tree" /*<< count*/ << "is created!" << endl;
	}
	~House() {
		cout << "House" << this->name << " is destroyed!" << endl;
	}
	void printPostion() {
		cout << "House Object:" << this->name << ":" << "Postion: x= " << postion.x << " " << "y=" << postion.y << endl;
	}
	void move() {
		StaticObject::move();
		cout << "Nooooo! Never move" << endl;
	}
};
class Motorbike : public DynamicObject {
public:
	Motorbike() : DynamicObject() {
		cout << "Motorbike" /*<< count */<< "is created!" << endl;
	}
	Motorbike(int id, string name, Postion pos) : DynamicObject(id,name, pos) {
		cout << "Motorbike" /*<< count*/ << "is created!" << endl;
	}
	Motorbike(Motorbike& m) : DynamicObject(m) {
		cout << "Motorbike" /*<< count*/ << "is created!" << endl;
	}
	~Motorbike() {
		cout << "Motorbike" << this->name << "is destroyed!" << endl;
	}
	void printPostion() {
		DynamicObject::printPostion();
	}
	void move() {
		DynamicObject::move();
		cout << "Grum Grummmmmm.... !" << endl;
	}
};

class Car : public DynamicObject {
public:
	Car() : DynamicObject() {
		cout << "Car" /*<< count*/ << "is created!" << endl;
	}
	Car(int id, string name, Postion pos) : DynamicObject(id, name, pos) {
		cout << "Car" /*<< count */ << "is created!" << endl;
	}
	Car(Car& c) : DynamicObject(c) {
		cout << "Car" /*<< count */<< "is created!" << endl;
	}
	~Car() {
		cout << "Car" << this->name << "is destroyed!" << endl;
	}
	void printPostion() {
		DynamicObject::printPosition();
	}
	void move() {
		DynamicObject::move();
		cout << "Pip pippppp..... !" << endl;
	}

};
int main() {
	list<BaseObject *> listObj;
	BaseObject* p_obj;
	Postion p;
	//BaseObject::count = 0;

	p_obj = new Tree();
	listObj.push_back(p_obj);
	p.x = 9;
	p.y = 99;
	p_obj = new Tree(100, "Beech", p);
	listObj.push_back(p_obj);
	//p_obj = new Tree(*p_obj);

	p_obj = new House();
	listObj.push_back(p_obj);
	p.x = 6;
	p.y = 66;
	p_obj = new House(101, "Berverly Hill",p);
	listObj.push_back(p_obj);


	p_obj = new Motorbike();
	listObj.push_back(p_obj);
	p.x = 3;
	p.y = 33;
	p_obj = new Motorbike(102, "Phantom", p);
	listObj.push_back(p_obj);

	p_obj = new Car();
	listObj.push_back(p_obj);
	p.x = 1;
	p.y = 11;
	p_obj = new Car(103, "Ducati", p);
	listObj.push_back(p_obj);

	for (auto obj : listObj) {
		obj->getName();
	}

	for (auto obj : listObj) {
		obj->move();
	}
	for (auto obj : listObj) {
		obj->printPosition();
	}
	listObj.clear();

	return 0;
}