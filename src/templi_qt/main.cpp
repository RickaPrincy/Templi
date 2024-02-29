#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "templi_qt.hpp"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTranslator translator;
	const QStringList uiLanguages = QLocale::system().uiLanguages();
for (const QString &locale : uiLanguages)
{
		const QString baseName = "templi_qt_" + QLocale(locale).name();
if (translator.load(":/i18n/" + baseName))
{
			a.installTranslator(&translator);
			break;
		}
	}
	templi_qt w;
	w.show();
	return a.exec();
}
