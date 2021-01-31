#pragma once

#include <iostream>
#include <random>

#include <conio.h>

#include "SpriteProvider.h"
#include "Snake.h"


class DemoTest {

private:
	SpriteProvider spriteProvider;
public:
	void test() {

		const int blockSize = 25;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(0, 4);
		
		std::uniform_int_distribution<> distrib2(0, 25);
		std::uniform_int_distribution<> distrib3(0, 300);

		Frame* theFrame = new Frame(spriteProvider, 0, 0, blockSize, 30, 60, RGB(100, 100, 100));

		std::vector<Item*> snake3;

		std::cin.ignore();
		for (int i = 0; i < 40; ++i) {
			snake3.push_back(new Item(
				spriteProvider,
				theFrame,
				500,
				300,
				3,
				blockSize,
				RGB(distrib3(gen), distrib3(gen), distrib3(gen)))
			);
		}
		while (true) {
			for (Item* s : snake3) {

				switch (distrib(gen)) {
				case 0:
					s->oneStepUp();
					break;
				case 1:
					s->oneStepRight();
					break;
				case 2:
					s->oneStepDown();
					break;
				case 3:
					s->oneStepLeft();
					break;
				default:
					break;
				}

			}
		}
		/*
		Item* snake = new Item(
			spriteProvider, 
			theFrame, 
			0, 
			0, 
			3, 
			blockSize, 
			RGB(distrib3(gen), distrib3(gen), distrib3(gen))
		);
		Item* apple = new Item(
			spriteProvider,
			theFrame,
			190,
			110,
			1,
			blockSize,
			RGB(distrib3(gen), distrib3(gen), distrib3(gen))
		);

		char keyValue;
		while (true) {

			keyValue = _getch();
			switch (keyValue) {

			case 72:
			case 'W':
			case 'w':
				snake->oneStepUp();
				break;
			case 80:
			case 'S':
			case 's':
				snake->oneStepDown();
				break;
			case 77:
			case 'D':
			case 'd':
				snake->oneStepRight();
				break;
			case 75:
			case 'A':
			case 'a':
				snake->oneStepLeft();
				break;
			default:
				break;

			}
		}
		*/
		/*std::vector<Snake*> snake3;

		std::cin.ignore();
		for (int i = 0; i < 40; ++i) {
			snake3.push_back(new Snake(spriteProvider, theFrame, 110, 110, distrib(gen)+1, blockSize, RGB(distrib3(gen), distrib3(gen), distrib3(gen))));
		}
		while (true) {
			for (Snake* s : snake3) {

				switch (distrib(gen)) {
				case 0:
					s->oneStepUp();
					break;
				case 1:
					s->oneStepRight();
					break;
				case 2:
					s->oneStepDown();
					break;
				case 3:
					s->oneStepLeft();
					break;
				default:
					break;
				}

			}
		}*/
	}
};

