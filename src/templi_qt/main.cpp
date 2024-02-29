#include <QApplication>

#include "templi_qt.hpp"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	templi_qt w;
	w.show();
	return a.exec();
}
