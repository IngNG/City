#pragma once
#include "../lib/TXLib.h"
#include "Const.h"
 
class Object {
private:
	int x;
	int y;
	int x2;
	int y2;

	int lastStatus = 0;

public:
	Object() {
		this->x = 0;
		this->y = 0;
		this->x2 = 0;
		this->y2 = 0;
	}

	Object(
		int x,
		int y,
		int x2,
		int y2
	) {
		this->x = x;
		this->y = y;
		this->x2 = x2;
		this->y2 = y2;
	}

	int getStatus() {
		bool mouseOver = this->isMouseOver();
		int statusMouseButton = txMouseButtons();
		int status = 0;

		if (mouseOver && !(this->lastStatus & MOUSE_HOVER)) {
			this->lastStatus |= MOUSE_HOVER;
			status |= MOUSE_HOVER;
		}
		if (!mouseOver && (this->lastStatus & MOUSE_HOVER)) {
			this->lastStatus ^= MOUSE_HOVER;
		}

		if (mouseOver && (statusMouseButton & 1) && !(this->lastStatus & MOUSE_DOWM_LEFT_BUTTON)) {
			this->lastStatus |= MOUSE_DOWM_LEFT_BUTTON;
			status |= MOUSE_DOWM_LEFT_BUTTON;
		}
		if (!(statusMouseButton & 1) && (this->lastStatus & MOUSE_DOWM_LEFT_BUTTON)) {
			if (mouseOver) {
				status |= MOUSE_UP_LEFT_BUTTON;
			}
			this->lastStatus ^= MOUSE_DOWM_LEFT_BUTTON;
		}

		if (mouseOver && (statusMouseButton & 2) && !(this->lastStatus & MOUSE_DOWN_RIGHT_BUTTON)) {
			this->lastStatus |= MOUSE_DOWN_RIGHT_BUTTON;
			status |= MOUSE_DOWN_RIGHT_BUTTON;
		}
		if (!(statusMouseButton & 2) && (this->lastStatus & MOUSE_DOWN_RIGHT_BUTTON)) {
			if (mouseOver) {
				status |= MOUSE_UP_RIGHT_BUTTON;
			}
			this->lastStatus ^= MOUSE_DOWN_RIGHT_BUTTON;
		}

		return status;
	}
//----------------X-----------------------
	int getX() {
		return this->x;
	}

	void setX(int x) {
		this->x = x;
	}
//----------------Y----------------------
	int getY() {
		return this->y;
	}

	void setY(int y) {
		this->y = y;
	}
//-------------X2----------------------
	int getX2() {
		return this->x2;
	}

	void setX2(int x) {
		this->x2 = x;
	}
//----------Y2------------------------
	int getY2() {
		return this->y2;
	}

	void setY2(int y) {
		this->y2 = y;
	}
//----------HEIGH--------------------
	int getHeigh() {
		return this->y2 - this->y;
	}

	void setHeigh(int heigh) {
		this->y2 = this->y + heigh;
	}
//------------WIDTH-------------------
	int getWidth() {
		return this->x2 - this->x;
	}

	void setWidth(int widht) {
		this->x2 = this->x + widht;
	}
	virtual void draw()=0;

protected:
	bool isMouseOver() {
		if (
			In(txMouseX(), this->x, this->x2) &&
			In(txMouseY(), this->y, this->y2)
		) {
			return true;
		}
		else {
			return false;
		}
	}
};