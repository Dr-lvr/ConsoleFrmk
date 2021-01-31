#pragma once
#include <windows.h>
#include <stdlib.h> 

#include <vector>
#include <queue>
#include <map>

#include "SpriteProvider.h"

class Frame {

private:
	SpriteProvider myProvider;
	COLORREF myColor;
	COLORREF delBlock = RGB(12, 12, 12);
	std::map<Block*, bool> logicPanel;
	std::pair<int, int> maxXY, minXY;
public:
	Frame(SpriteProvider spriteProvider, int x, int y, int blockSize, int row, int col, COLORREF color) {
		maxXY = std::make_pair(x + blockSize, y + blockSize);
		maxXY = std::make_pair((x + blockSize) * (col - 1), (y + blockSize) * (row - 1));
		myProvider = spriteProvider;
		myColor = color;
		int tmp = x;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				logicPanel.insert(std::pair<Block*, bool>(new Block(new Position(x, y), blockSize), false));
				x += blockSize;
			}
			x = tmp;
			y += blockSize;
		}
		drawFrame();
	};
	~Frame() {

	};
	std::pair<int, int> getMaxXY() {
		return maxXY;
	}
	std::pair<int, int> getMinXY() {
		return minXY;
	}
	void drawFrame() {
		for (auto& b : logicPanel) {
			myProvider.drawBlock(b.first->getX(), b.first->getY(), b.first->getSize(), myColor);
		}
	}
	bool testBlock(Block* theBlock) {

		auto it = logicPanel.find(theBlock);
		if (it != logicPanel.end()) {
			return it->second;
		}
	}
	void setBlock(Block* theBlock) {
		auto it = logicPanel.find(theBlock);
		if (it != logicPanel.end()) {
			it->second = true;
		}
		myProvider.fillBlock(theBlock->getX(), theBlock->getY(), theBlock->getSize(), RGB(125, 0, 0));
	}
	void unSetBlock(Block* theBlock) {
		auto it = logicPanel.find(theBlock);
		if (it != logicPanel.end()) {
			it->second = false;
		}
		myProvider.fillBlock(theBlock->getX(), theBlock->getY(), theBlock->getSize(), RGB(12, 12, 12));
	}
	Block* getBlock(int x, int y) {

		Block* tmp = new Block(new Position(-1, -1), -1);
		for (auto& b : logicPanel) {
			if (b.first->getX() == x && b.first->getY() == y) {
				return b.first;
			}
		}
		return tmp;
	}
	Block* getUpperBlock(Block* aBlock) {

		Block* tmp = new Block(new Position(-1, -1), -1);
		for (auto& b : logicPanel) {
			if (b.first->getX() == aBlock->getX() &&
				b.first->getY() == aBlock->getY() - aBlock->getSize()) {
				if (!testBlock(b.first)) {
					setBlock(b.first);
					return b.first;
				}
			}
		}
		return tmp;
	}
	Block* getRightBlock(Block* aBlock) {

		Block* tmp = new Block(new Position(-1, -1), -1);
		for (auto& b : logicPanel) {
			if (b.first->getX() == aBlock->getX() + aBlock->getSize() &&
				b.first->getY() == aBlock->getY()) {
				if (!testBlock(b.first)) {
					setBlock(b.first);
					return b.first;
				}
			}
		}
		return tmp;
	}
	Block* getDownBlock(Block* aBlock) {

		Block* tmp = new Block(new Position(-1, -1), -1);
		for (auto& b : logicPanel) {
			if (b.first->getX() == aBlock->getX() &&
				b.first->getY() == aBlock->getY() + aBlock->getSize()) {
				if (!testBlock(b.first)) {
					setBlock(b.first);
					return b.first;
				}
			}
		}
		return tmp;
	}
	Block* getLeftBlock(Block* aBlock) {

		Block* tmp = new Block(new Position(-1, -1), -1);
		for (auto& b : logicPanel) {
			if (b.first->getX() == aBlock->getX() - aBlock->getSize() &&
				b.first->getY() == aBlock->getY()) {
				if (!testBlock(b.first)) {
					setBlock(b.first);
					return b.first;
				}
			}
		}
		return tmp;
	}
};
class Item {

private:
	SpriteProvider myProvider;
	Frame* myFrame;
	std::deque<Block*> myPosition;
	COLORREF myColor;
	COLORREF delBlock = RGB(12, 12, 12);
public:
	Item(SpriteProvider spriteProvider, Frame* frame, int x, int y, int blocks, int blockSize, COLORREF color) {
		myProvider = spriteProvider;
		myFrame = frame;
		myColor = color;
		for (int i = 0; i < blocks; ++i) {
			myPosition.push_front(myFrame->getBlock(x, y));
			myFrame->setBlock(myFrame->getBlock(x, y));
			x += blockSize;
		}
		drawItem();
	};
	~Item() {

	};
	void drawItem() {
		for (auto b : myPosition) {
			myProvider.drawBlock(b, myColor);
		}
	}
	void moveBack() {
		myFrame->unSetBlock(myPosition.back());
		myProvider.drawBlock(myPosition.back(), RGB(100, 100, 100));
		myPosition.pop_back();
	}
	void moveFront() {

	}
	void oneStepUp() {
		Block* tmp = myFrame->getUpperBlock(myPosition.front());
		if (tmp->getSize() != -1) {
			myPosition.push_front(tmp);
			moveBack();
			drawItem();
			//Sleep(1);
		}
	}
	void oneStepRight() {
		Block* tmp = myFrame->getRightBlock(myPosition.front());
		if (tmp->getSize() != -1) {
			myPosition.push_front(tmp);
			moveBack();
			drawItem();
			//Sleep(1);
		}
	}
	void oneStepDown() {
		Block* tmp = myFrame->getDownBlock(myPosition.front());
		if (tmp->getSize() != -1) {
			myPosition.push_front(tmp);
			moveBack();
			drawItem();
			//Sleep(1);
		}
	}
	void oneStepLeft() {
		Block* tmp = myFrame->getLeftBlock(myPosition.front());
		if (tmp->getSize() != -1) {
			myPosition.push_front(tmp);
			moveBack();
			drawItem();
			//Sleep(1);
		}
	}
};