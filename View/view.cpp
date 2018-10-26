#include "view.h"
#include "q_debugstream.h"

View::View(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::View)
{
    ui->setupUi(this);
    consoleOutput = new Q_DebugStream(std::cout, this, "console"); //Redirect stream cout to QTextEdit
    errorOutput = new Q_DebugStream(std::cerr, this, "error"); //Redirect stream cerr to MessageBox

    //FIXME Example connect( ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeMyTab(int)) );
    show();
}

View::~View()
{
    cout << "Destructor view" << endl;
    delete consoleOutput;
    delete errorOutput;
    delete ui;
}

Ui::View *View::getUI() const
{
    return ui;
}

QTextEdit *View::getConsole() const
{
    return ui->txtConsole;
}

void View::initDataFromModel( Model* _pData )
{
    dataFromModel = _pData;
}

//FIXME example
/*void View::addPlotView(int _indexLine)
{
    //only add plot if he doesn't already exist
    for (int var = 0; var < tabs.size(); ++var) {
        if (tabs.at(var)->get_index() == _indexLine)
            return;
    }

    //only display plot of time signal
    if (dataFromModel->get_line(_indexLine)->get_antonly() != NULL &&
        dataFromModel->get_line(_indexLine)->get_signal()  != NULL &&
        dataFromModel->get_line(_indexLine)->get_antonly()->isTime() &&
        dataFromModel->get_line(_indexLine)->get_signal()->isTime()) {

        tabs.push_back( make_shared<TabPlot>( dataFromModel, _indexLine, this ) );
        connect( this, SIGNAL(refresh()), tabs.back().get(), SLOT(update()) );
        ui->tabWidget->addTab( tabs.last().get(),
                               QString::fromStdString( dataFromModel->get_line(_indexLine)->get_name() ) );
    }
}*/

//FIXME example
/*void View::closeMyTab(int _index)
{
    //Tab must not movable or the index doesn't correspond anymore to the index in the list
    ui->tabWidget->removeTab(_index);
    tabs.removeAt(_index);
}*/

void View::errorMessage(QString _msg)
{
    if(_msg == ""){ //wait std::endl of the message std::cerr to create the message box

        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error",errMsg);
        messageBox.setFixedSize(500,200);
        errMsg.clear();

        QApplication::quit();
    }else{
        errMsg += _msg;
    }

}

void View::closeEvent(QCloseEvent *event){
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Close",
                                                               tr("Exit application ?\n"),
                                                               QMessageBox::No | QMessageBox::Yes,
                                                               QMessageBox::Yes);

    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

