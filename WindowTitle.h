
#ifndef _WINDOW_TITLE_H_
#define _WINDOW_TITLE_H_

#include <QWidget>

class QHBoxLayout;
class QPushButton;


class StyleSheetWidget : public QWidget {
public:
	StyleSheetWidget(QWidget* parent = nullptr) : QWidget(parent) {}

	virtual void paintEvent(QPaintEvent *) override;
};


class WindowTitle : public StyleSheetWidget {
	Q_OBJECT
public:
	enum ButtonStatus {
		ButtonMin = 0,
		ButtonMax,
		ButtonRestore,
		ButtonClose
	};

	WindowTitle(QWidget *window);

	bool isCaption(int x, int y) const;

protected:
	virtual bool eventFilter(QObject* o, QEvent* e) override;

	void initButton();

signals:
	void buttonClick(WindowTitle::ButtonStatus status);

private:
	QWidget* m_window;

	QHBoxLayout* m_layout;
	QPushButton* m_buttonMin;
	QPushButton* m_buttonMax;
	QPushButton* m_buttonRestore;
	QPushButton* m_buttonClose;
};


#endif