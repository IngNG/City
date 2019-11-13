/*!
\file
\brief ������� ���������
���� �������� ��������� `Area`,
��������������� ��������� � ������� ��� ������ � ���
*/
#pragma once

/*!
\brief ������� ������������ � �������
*/
struct EventArea {
	bool mouseButtonUpLeft    = false; ///< ������ ���
	bool mouseButtonUpRight   = false; ///< ������ ���

	bool mouseButtonDownLeft  = false; ///< �������� ���
	bool mouseButtonDownRight = false; ///< �������� ���

	bool mouseHover           = false; ///< ����� ������ � �������
	bool mouseUnHover         = false; ///< ����� ����� �� ������� �������
};

/*!
\brief ������� ���������
*/
struct AreaCoord {
	int        x; ///< ���������� X
	int        y; ///< ���������� Y
	int        widht; ///< ������
	int        height; ///< ������

	EventArea  events; ///< ������� ������������ � �������

	bool mouseClickLeft  ; ///< ������ ���
	bool mouseClickRight ; ///< ������ ���
	bool mouseOver       ; ///< ����� ��������� � �������
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

	EventArea events;

	bool oldMouseOver       = area.mouseOver; 		//����� ��������� � �������
	if (!oldMouseOver && mouseOver) {
		events.mouseHover = true;
	}
	else if (oldMouseOver && !mouseOver) {
		events.mouseUnHover = true;
	}

	bool oldMouseClickLeft  = area.mouseClickLeft; 	//������ ���
	if (!oldMouseClickLeft && mouseClickLeft) {
		events.mouseButtonDownLeft = true;
	}
	else if (oldMouseClickLeft && !mouseClickLeft) {
		events.mouseButtonUpLeft = true;
	}

	bool oldMouseClickRight = area.mouseClickRight; //������ ���
	if (!oldMouseClickRight && mouseClickRight) {
		events.mouseButtonDownRight = true;
	}
	else if (oldMouseClickRight && !mouseClickRight) {
		events.mouseButtonUpRight = true;
	}

	area.events = events;

	area.mouseClickLeft = mouseClickLeft; 		//������ ���
	area.mouseClickRight = mouseClickRight; 	//������ ���
	area.mouseOver = mouseOver; 				//����� ��������� � �������
}
