
#include <cassert>

#include <QEvent>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QStyleOption>

#include "WindowTitle.h"

WindowTitle::WindowTitle(QWidget *window)
	: StyleSheetWidget(window)
	, m_window(window), m_layout(NULL)
	, m_buttonMin(NULL), m_buttonMax(NULL), m_buttonRestore(NULL), m_buttonClose(NULL)
{

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addStretch(1);
	m_layout = layout;
	this->setLayout(layout);
	this->setFixedHeight(32);

	this->setStyleSheet("QWidget {"
		"background-color: gray;"
		"}");

	m_window->installEventFilter(this);

	this->initButton();
}

bool WindowTitle::isCaption(int x, int y) const
{
	if (this->rect().contains(x, y)) {
		if (!this->childAt(x, y)) {
			return true;
		}
	}
	return false;
}

bool WindowTitle::eventFilter(QObject* o, QEvent* e)
{
	if (e->type() == QEvent::WindowStateChange) {
		Qt::WindowStates states = m_window->windowState();
		if (states & Qt::WindowMaximized) {
			m_buttonMax->hide();
			m_buttonRestore->show();
		}
		else {
			m_buttonMax->show();
			m_buttonRestore->hide();
		}
		return true;
	}

	return QWidget::eventFilter(o, e);
}

void WindowTitle::initButton()
{
	assert(!(m_buttonMin || m_buttonMax || m_buttonRestore || m_buttonClose));

	// 最小化按钮
	m_buttonMin = new QPushButton("min", this);
	m_buttonMin->setObjectName("min");
	m_buttonMin->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	m_buttonMin->setStyleSheet("QPushButton { border: none; border-left: 1px solid black; background-color: red;}");
	m_buttonMin->setFixedWidth(80);
	connect(m_buttonMin, &QPushButton::clicked, [this]() {
		emit buttonClick(ButtonMin);
	});
	m_layout->addWidget(m_buttonMin);

	// 最大化按钮
	m_buttonMax = new QPushButton("max", this);
	m_buttonMax->setObjectName("max");
	m_buttonMax->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	m_buttonMax->setStyleSheet("QPushButton { border: none; border-left: 1px solid black; background-color: red;}");
	m_buttonMax->setFixedWidth(80);
	connect(m_buttonMax, &QPushButton::clicked, [this](bool) {
		emit buttonClick(ButtonMax);
	});
	m_layout->addWidget(m_buttonMax);

	// 还原按钮
	m_buttonRestore = new QPushButton("restore", this);
	m_buttonRestore->setObjectName("restore");
	m_buttonRestore->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	m_buttonRestore->setStyleSheet("QPushButton { border: none; border-left: 1px solid black; background-color: red;}");
	m_buttonRestore->setFixedWidth(80);
	m_buttonRestore->hide();
	connect(m_buttonRestore, &QPushButton::clicked, [this]() {
		emit buttonClick(ButtonRestore);
	});
	m_layout->addWidget(m_buttonRestore);

	// 关闭按钮
	m_buttonClose = new QPushButton("close", this);
	m_buttonClose->setObjectName("close");
	m_buttonClose->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	m_buttonClose->setStyleSheet("QPushButton { border: none; border-left: 1px solid black; background-color: red;}");
	m_buttonClose->setFixedWidth(80);
	connect(m_buttonClose, &QPushButton::clicked, [this]() {
		emit buttonClick(ButtonClose);
	});
	m_layout->addWidget(m_buttonClose);
}

void StyleSheetWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	QStyleOption opt;
	opt.init(this);
	this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
