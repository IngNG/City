/*!
\file
\brief ������� ���������
���� �������� ��������� `Area`,
��������������� ��������� � ������� ��� ������ � ���
*/
#pragma once

/*!
\brief ������� ���������
*/
struct AreaCoord {
	int        x; ///< ���������� X
	int        y; ///< ���������� Y
	int        widht; ///< ������
	int        height; ///< ������

	bool mouseClickLeft  ; ///< ������ ���
	bool mouseClickRight ; ///< ������ ���
	bool mouseOver       ; ///< ����� ��������� � �������

	bool mouseButtonUpLeft    ; ///< ������ ���
	bool mouseButtonUpRight   ; ///< ������ ���
	bool mouseButtonDownLeft  ; ///< �������� ���
	bool mouseButtonDownRight ; ///< �������� ���
	bool mouseHover           ; ///< ����� ������ � �������
	bool mouseUnHover         ; ///< ����� ����� �� ������� �������
};

/*!
��������� ���������� ����� � �������
\param area ����������� �������
\return true - ���� ��, ����� false
*/
bool isMouseOver(AreaCoord area, int CAM_X = 0) {
	return
	In(txMouseX(),	area.x + CAM_X,	area.x + CAM_X + area.widht) &&
	In(txMouseY(), 	area.y, 		area.y + area.height);
}

/*!
��������� ��������� `events` � `status` ��������� `AreaCoord`
\param area ����������� �������
*/
void updateStatusArea(AreaCoord& area, int CAM_X) {

	//������� ��������� �������
	bool mouseOver = isMouseOver(area, CAM_X);
	bool mouseClickLeft = mouseOver && (txMouseButtons() & 1);
	bool mouseClickRight = mouseOver && (txMouseButtons() & 2);

	//�������
	area.mouseButtonUpLeft    = false;
	area.mouseButtonUpRight   = false;
	area.mouseButtonDownLeft  = false;
	area.mouseButtonDownRight = false;
	area.mouseHover           = false;
	area.mouseUnHover         = false;

	//����� ��������� � �������
	bool oldMouseOver       = area.mouseOver;
	if (!oldMouseOver && mouseOver) {
		area.mouseHover = true;
	} else if (oldMouseOver && !mouseOver) {
		area.mouseUnHover = true;
	}

 	//������ ���
	bool oldMouseClickLeft  = area.mouseClickLeft;
	if (!oldMouseClickLeft && mouseClickLeft) {
		area.mouseButtonDownLeft = true;
	} else if (oldMouseClickLeft && !mouseClickLeft) {
		area.mouseButtonUpLeft = true;
	}

	//������ ���
	bool oldMouseClickRight = area.mouseClickRight;
	if (!oldMouseClickRight && mouseClickRight) {
		area.mouseButtonDownRight = true;
	} else if (oldMouseClickRight && !mouseClickRight) {
		area.mouseButtonUpRight = true;
	}

	//����� ��������� �������
	area.mouseClickLeft = mouseClickLeft;
	area.mouseClickRight = mouseClickRight;
	area.mouseOver = mouseOver;
}
