#include "mainview.h"
#include "ui_mainview.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>


static int PORT_NUM = 23;
static int WAIT_FOR_DATA_MS = 200;

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView),
    m_server(new QTcpServer(this)),
    m_socket(nullptr)
{
    ui->setupUi(this);
    ui->btnStopServer->setEnabled(false);
    connect(m_server, &QTcpServer::newConnection, this,
            &MainView::ExchangeData);
}

MainView::~MainView()
{
    delete ui;
}

void MainView::on_btnStartServer_clicked()
{
    if (startServer())
    {
    ui->btnStartServer->setEnabled(false);
    ui->btnStopServer->setEnabled(true);
    }
}

void MainView::on_btnStopServer_clicked()
{
    stopServer();
    ui->btnStartServer->setEnabled(true);
    ui->btnStopServer->setEnabled(false);
}

bool MainView::startServer()
{
    bool result = m_server->listen(QHostAddress::Any, PORT_NUM);
    if (!result)
    {
        QMessageBox::critical(this, tr("Echo Server"),
                              tr("Start Server Failed with error %1").arg(m_server->errorString()));
        return false;
    }
    return true;
}

void MainView::stopServer()
{
    m_server->close();
    if ((m_socket != nullptr)&& m_socket->isOpen()){
        m_socket->close();
    }


}

void MainView::ExchangeData()
{
    m_socket = m_server->nextPendingConnection();
    if (m_socket->isOpen())
    {
        connect(m_socket, &QTcpSocket::readyRead,
                this, &MainView::EchoReadData);
    }
}

void MainView::EchoReadData()
{
    m_socket->write("<echoserver>\n");
    QString result;
    while (!m_socket->atEnd())
    {
        result.append(m_socket->readAll());
        m_socket->waitForReadyRead(WAIT_FOR_DATA_MS);
    }
    m_socket->write(qPrintable(result));
    m_socket->write("\n</echoserver>\n");
}
