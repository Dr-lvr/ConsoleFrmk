#pragma once
#include <windows.h>

class Position {

private:
	int x = 0;
	int y = 0;
public:
	Position(int x, int y) {
		this->x = x;
		this->y = y;
	};
	~Position() {
	};
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
};
class Block {

private:
	Position* myPosition;
	int size = 0;
public:
	Block(Position* p, int size) {
		myPosition = new Position(p->getX(), p->getY());
		this->size = size;
	};
	~Block() {
	};
	int getX() {
		return myPosition->getX();
	}
	int getY() {
		return myPosition->getY();
	}
	int getSize() {
		return size;
	}
};
class DrawingTool {

private:
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	COLORREF COLOR = RGB(0, 255, 255);
	COLORREF DELETE_COLOR = RGB(12, 12, 12);

public:

	DrawingTool() {
	};
	~DrawingTool() {
	};
	HDC getDc() {
		return this->mydc;
	}
};

class SpriteProvider : DrawingTool {

public:
	SpriteProvider() {
	};
	~SpriteProvider() {
	};
	void drawLine(int x, int y, COLORREF color) {
		SetPixel(getDc(), x, y, color);
	}
	void drawBlock(int x, int y, int size, COLORREF color) {
		for (int i = x; i < x + size; ++i) {

			drawLine(i, y, color);
		}
		for (int i = x; i < x + size; ++i) {

			drawLine(i, y + size, color);
		}
		for (int i = y; i < y + size; ++i) {

			drawLine(x, i, color);
		}
		for (int i = y; i < y + size; ++i) {

			drawLine(x + size, i, color);
		}
	}
	void drawBlock(Block* aBlock, COLORREF color) {
		drawBlock(aBlock->getX(), aBlock->getY(), aBlock->getSize(), color);
	}
	void fillBlock(int x, int y, int size, COLORREF color) {
		
		for (int i = x; i < x + size; ++i) {
			for (int j = y; j < y + size; ++j) {

				drawLine(i, j, color);
			}
		}
	}
	void drawTable(int x, int y, int size, int row, int col, COLORREF color) {
		int tmp = x;

		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				drawBlock(x, y, size, color);
				x += size;
			}
			x = tmp;
			y += size;
		}
	}
};

