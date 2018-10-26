#ifndef FACTORY_H
#define FACTORY_H

#include <QObject>
#include <QThread>
#include <iostream>

#include "Controller/controller.h"
#include "Model/model.h"
#include "View/view.h"

/*!
 *  \brief     Create all instance of the pattern MVC
 *  \details   This class is the only instance created by the main function at the begining and
               the last instance deleted when we leave the software.
 *  \author    Quentin Collet
 *  \version   1.0
 *  \date      Nov 2018
 *  \pre       Create an object in the main function and call the function init() to run the software
 *  \warning   It's the only class where you are authorized to create an instance of Controller, Model and View.
 */
class Factory : public QObject
{
    Q_OBJECT

public:
    Controller* controller; /*!< Receive events from View, data from extern. Send data to Model or/and View */
    Model* model;           /*!< Receive data from Controller. No process, only store data */
    View* view;             /*!< Read data from Model. Receive events from controller. Send events to Controller*/

    QThread* workerThread; /*!< The Controller and Model own to this thread, View is in the main thread (or GUI thread)
                            this thread is necessary to avoid that the screen freezes when we process data*/

public:

    //! Create an instance of Controller, Model and View (referee to the pattern MVC)
    Factory();

    /*!
       This destructor is the last one called by the software before to leave. His work is to be sure that all elements
       created are destroyed before to leave. Below, the suppression step by step:
            - delete the instance View
            - set flag mustStop from Controller
            - wait on the workerThread to finish (responsible to delete Controller and Model instances)
            - delete the workerThread
            - delete the polling timer
    */
    ~Factory();

    //! Create the thread worker. Set all the link (between timer, thread,
    //! instance of MVC) and start the workerThread which contains Controller
    /*!
      \sa Factory(), ~Factory()
    */
    void init();

signals:
    void close_MVC();

};

#endif // FACTORY_H

