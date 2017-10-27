#pragma once
#include "Ui.h"

class UIClass {

protected:
	wchar_t* spriteName;
	int BMPid;
	std::vector<Ui*> uis;
	std::vector<Ui*>* puis;
	std::vector<bool> prevState;

public:

	UIClass() {
		uis = {};
		puis = &uis;
	}

	~UIClass() {
		delete puis;
	}

	virtual wchar_t* initUI() = 0;
	virtual void Triggered(int id) = 0;
	void setBMPid(int id) { BMPid = id; }
	void linkUIs(Ui* ui1, Ui* ui2) { ui2->setParent(ui1->getID()); ui1->addChild(ui2->getID()); }
	Ui*  getUI(int id);
	void confirmAlive();
	int getBMPid() { return BMPid; }
	std::vector<Ui*>* getUIs() { return puis; }
	int getSize() { return uis.size(); }
	void toggleChildren(int id);
	void programMasters();
	void setState(int i);
	void updateState();
};


