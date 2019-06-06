
#include <cassert>

#include <QVBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

#include <windowsx.h>
#include <windows.h>

#include "CustomWindow.h"

CustomWindow::CustomWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	this->setAttribute(Qt::WA_TranslucentBackground, true);


	HWND hwnd = (HWND)this->winId();
	DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
    //只有在窗口拥有WS_MAXIMIZEBOX | WS_THICKFRAME样式时，"屏幕边缘自动排列"功能才有效，最好还要添加WS_CAPTION样式，否则窗口最大化会覆盖任务栏。
	::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);

	StyleSheetWidget* center = new StyleSheetWidget(this);
	this->setCentralWidget(center);

	QVBoxLayout* layout = new QVBoxLayout(center);
	layout->setMargin(0);
	layout->setSpacing(0);
	center->setLayout(layout);

	m_title = new WindowTitle(this);
	connect(m_title, SIGNAL(buttonClick(WindowTitle::ButtonStatus)), this, SLOT(titleButtonClick(WindowTitle::ButtonStatus)));
	layout->addWidget(m_title);

	QWidget* widget = new StyleSheetWidget(this);
	widget->setAutoFillBackground(true);
	QPalette palette = widget->palette();
	palette.setColor(QPalette::Background, Qt::lightGray);
	widget->setPalette(palette);
	layout->addWidget(widget, 1);
}

CustomWindow::~CustomWindow()
{

}

void CustomWindow::titleButtonClick(WindowTitle::ButtonStatus status)
{
	switch (status) {
	case WindowTitle::ButtonMin:
		this->showMinimized();
		break;

	case WindowTitle::ButtonMax:
		this->showMaximized();
		break;

	case WindowTitle::ButtonRestore:
		this->showNormal();
		break;

	case WindowTitle::ButtonClose:
		this->close();
		break;

	default:
		assert(false);
		break;
	}
}

//重载nativeEvent函数，处理WM_NCHITTEST、WM_NCCALCSIZE和WM_GETMINMAXINFO消息

bool CustomWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	MSG* msg = (MSG*)message;
	switch (msg->message) {

	case WM_NCHITTEST:
	{
		int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
		int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
		if (m_title->isCaption(xPos, yPos)) {
			*result = HTCAPTION;
			return true;
		}
	}
		break;

	case WM_NCCALCSIZE:
		return true;

	case WM_GETMINMAXINFO:
	{
		if (::IsZoomed(msg->hwnd)) {
			// 最大化时会超出屏幕，所以填充边框间距
			RECT frame = { 0, 0, 0, 0 };
			AdjustWindowRectEx(&frame, WS_OVERLAPPEDWINDOW, FALSE, 0);
			frame.left = abs(frame.left);
			frame.top = abs(frame.bottom);
			this->setContentsMargins(frame.left, frame.top, frame.right, frame.bottom);
		}
		else {
			this->setContentsMargins(2, 2, 2, 2);
		}

		*result = ::DefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);
		return true;
	}
		break;
	}

	return QMainWindow::nativeEvent(eventType, message, result);
}
