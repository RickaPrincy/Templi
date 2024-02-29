#include "templi_qt.hpp"

#include "./ui_templi_qt.h"

templi_qt::templi_qt(QWidget *parent) : QMainWindow(parent), ui(new Ui::templi_qt)
{
	ui->setupUi(this);
}

templi_qt::~templi_qt()
{
	delete ui;
}
