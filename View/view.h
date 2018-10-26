#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include <QTextEdit>
#include <QTimer>
#include <QList>
#include <string>

#include <memory>

#include "ui_view.h"
#include "../config.h"

class Model;
class Q_DebugStream;

namespace Ui {
    class View;
}

using namespace std;


/*!
 *  \brief     Read data and display it
 *  \details   The View is in charge to interact with users and display data store by the Model.
 *  \author    Quentin Collet
 *  \version   1.0
 *  \date      Nov 2018
 *  \pre       Must be instantiated in the Factory class (<b>only one time</b>)
 */
class View : public QMainWindow, private Ui::View
{
    Q_OBJECT

private:
    Ui::View *ui;   /*!<  Point on the mainwindow creat with QtDesigner  */

    Model* dataFromModel;     /*!< reference on all the data contained in the model and needed by the View
                                   the View just need to point on this object to access
                                   elements to display
                                   \sa initDataFromModel(Model*), Model */

    //FIXME generic table ?
    //QList< shared_ptr<TabVTK> > tabs;   /*!<  Contains tab with VTK window inside \sa TabVTK  */

    QString errMsg;                 /*!< buffer for message error  */
    Q_DebugStream* consoleOutput;   /*!< Redirect stream flux of cout to the window  */
    Q_DebugStream* errorOutput;     /*!< Redirect stream flux of cerr to the window  */

    //! Add a TabPlot to the window
    /*!
      \param index of the transmission line to display
      \note it is not possible to select a reflection in v1.0
      \sa TabSimulation
    */
    //FIXME Example void addPlotView(int _indexLine);

public:
    View(QWidget *parent = nullptr);
    ~View();

    Ui::View* getUI() const;
    QTextEdit* getConsole() const;

signals:

    //! Receives from the controller when it finish to process a scan. Notifiy the tabVTK to update value
    /*!
    */
    void refresh();

public slots:

    //! Receive a pointer on the Datapackage from the datapackage
    /*!
      \param Model pointer containing all the data
      \sa Model::dataToView(Model *), Model
    */
    void initDataFromModel(Model *);

    //! Close the tab in index
    /*!
      \param index of the table
      \sa TabSimulation, TabPlot
    */
    //FIXME void closeMyTab(int);

    //! Display an error from the stream cerr in a dialog box. Close the software after we click on "Ok" button
    /*!
      \param error message to display
    */
    void errorMessage(QString _msg);

    //! Open a dialog box and exit the application if we press on "Yes"
    //! (call if the red cross or the close button are pressed)
    /*!
    */
    virtual void closeEvent(QCloseEvent *);


};

#endif // VIEW_H
