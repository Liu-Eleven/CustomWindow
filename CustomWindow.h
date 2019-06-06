#ifndef CUSTOMWINDOW_H
#define CUSTOMWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_CustomWindow.h"

#include "WindowTitle.h"

class CustomWindow : public QMainWindow
{
	Q_OBJECT

public:
	CustomWindow(QWidget *parent = 0);
	~CustomWindow();

public slots:
	void titleButtonClick(WindowTitle::ButtonStatus status);

protected:
	virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
	Ui::CustomWindowClass ui;

	WindowTitle* m_title;
};

#endif // CUSTOMWINDOW_H
