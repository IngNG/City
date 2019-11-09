/*!
\file
\brief ������� ���������
���� �������� ��������� `Area`,
��������������� ��������� � ������� ��� ������ � ���
*/
#pragma once

/*!
\brief ������� ��������� �������
*/
struct StatusArea {
	bool mouseClickLeft  = false; ///< ������ ���
	bool mouseClickRight = false; ///< ������ ���

	bool mouseOver       = false; ///< ����� ��������� � �������
};

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
	StatusArea status; ///< ��������� �������
};

/*!
��������� ���������� ����� � �������
\param area ����������� �������
\return true - ���� ��, ����� false
*/
bool isMouseOver(AreaCoord area, int CAM_X = 0) {
	return
	In(txMouseX(),
	area.x + CAM_X,
	area.x + CAM_X + area.widht) &&
	In(txMouseY(), area.y, area.y + area.height);
}

/*!
��������� ������� ��������� �������
\param area ����������� �������
\return ������� ��������� �������
*/
StatusArea getStatusArea(AreaCoord area, int CAM_X = 0) {
	int statusMouseButton = txMouseButtons();
	StatusArea status;

	status.mouseOver = isMouseOver(area, CAM_X);
	if (status.mouseOver) {
		status.mouseClickLeft = statusMouseButton & 1;
		status.mouseClickRight = statusMouseButton & 2;
	}

	return status;
}

/*!
��������� ��������� `events` � `status` ��������� `AreaCoord`
\param area ����������� �������
*/
void updateStatusArea(AreaCoord& area, int CAM_X) {
	StatusArea newStatus = getStatusArea(area, CAM_X);
	StatusArea oldStatus = area.status;
	EventArea events;

	if (!oldStatus.mouseOver && newStatus.mouseOver) {
		events.mouseHover = true;
	}
	else if (oldStatus.mouseOver && !newStatus.mouseOver) {
		events.mouseUnHover = true;
	}

	if (!oldStatus.mouseClickLeft && newStatus.mouseClickLeft) {
		events.mouseButtonDownLeft = true;
	}
	else if (oldStatus.mouseClickLeft && !newStatus.mouseClickLeft) {
		events.mouseButtonUpLeft = true;
	}

	if (!oldStatus.mouseClickRight && newStatus.mouseClickRight) {
		events.mouseButtonDownRight = true;
	}
	else if (oldStatus.mouseClickRight && !newStatus.mouseClickRight) {
		events.mouseButtonUpRight = true;
	}

	area.events = events;
	area.status = newStatus;
}
