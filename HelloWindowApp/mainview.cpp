#include "mainview.h"
#include "ui_mainview.h"

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    ui->btnExit->setText(tr("New Exit Now"));
//    connect(ui->btnExit, &QPushButton::clicked, this, &QMainWindow::close);

    connect(ui->btnExit, &QPushButton::clicked, this,
            [this] () {this->close();});
    ui->btnExit->disconnect();

}

MainView::~MainView()
{
    delete ui;
}
