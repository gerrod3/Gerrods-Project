#include "UIClass.h"

void UIClass::confirmAlive() {
	for (int i = 0; i < uis.size(); i++) {
		if (uis.at(i)->checkAlive()) {
			if (uis.at(i)->hasParent()) {
				if (!getUI(uis.at(i)->getParent())->checkAlive()) {
					uis.at(i)->setAlive(false);
				}
			}
		}
	}
}

Ui* UIClass::getUI(int id) {
	for (int i = 0; i < uis.size(); i++) {
		if (uis.at(i)->getID() == id) {
			return uis.at(i);
		}
	}
}

void UIClass::toggleChildren(int id) {
	std::vector<int> childs = *puis->at(id)->getChilds();
	for (int i = 0; i < childs.size(); i++) {
		puis->at(childs.at(i))->setAlive(!puis->at(childs.at(i))->checkAlive());
	}

}

void UIClass::programMasters() {
	for (int i = 0; i < puis->size(); i++) {
		if (puis->at(i)->hasChild()) {
			std::vector<int> childs = *puis->at(i)->getChilds();
			for (int j = 0; j < childs.size(); j++) {
				if (puis->at(childs.at(j))->getParent() != puis->at(i)->getID()) {
					puis->at(childs.at(j))->setParent(puis->at(i)->getID());
				}
			}
		}
	}
}

void UIClass::setState(int i) {
	//-1 = -prev state
	//0 = all dead
	//1 = all alive
	for (int j = 0; j < puis->size(); j++) {

		switch (i) {
		case -1:
			puis->at(j)->setAlive(prevState.at(j));
			break;

		case 0:
			puis->at(j)->setAlive(false);
			break;

		case 1:
			puis->at(j)->setAlive(true);
			break;
		}

	}
}

void UIClass::updateState() {
	for (int j = 0; j < puis->size(); j++) {
		prevState.at(j) = puis->at(j)->checkAlive();
	}
}