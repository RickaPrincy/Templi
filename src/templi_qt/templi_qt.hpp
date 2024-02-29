#ifndef TEMPLI_QT_HPP
#define TEMPLI_QT_HPP

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class templi_qt;
}
QT_END_NAMESPACE

class templi_qt : public QMainWindow
{
	Q_OBJECT

public:
	templi_qt(QWidget *parent = nullptr);
	~templi_qt();

private:
	Ui::templi_qt *ui;
};
#endif	// TEMPLI_QT_HPP
