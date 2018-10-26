#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>

#include "../Model/model.h"

using namespace std;

/*!
 *  \brief     Logic of the software
 *  \details   Manage all the logic of the software, this class receives all the signal from the extern (user, other
               software, etc.) and store it in a list. If you need to manage event coming from the user or another software,
               you should use this class to manage it.
 *  \author    Quentin Collet
 *  \version   1.0
 *  \date      Nov 2018
 *  \pre       Must be instantiated in the Factory class (<b>only one time</b>)
 */
class Controller : public QObject
{
    Q_OBJECT

private:
    Model* pModel = nullptr;

public:

    bool executing;       /*!< Define if the application is running, if not we first initialisation */

    //! Constructor
    Controller();

    //! Destructor
    ~Controller();

    //! Link Controller with the Model. Necessary to send data to the model
    /*!
      \param pointer on the Model
    */
    void linkModel(Model *_pModel);

public slots:

    //! Called by the workerThread when it starts to run. Do all the initializiation of the software
    //! here. Only start once (checked with excuting boolean)
    /*!
      \sa workerThread, executing, Factory
    */
    void start();

    //! Last function called by the controller before to leave.
    /*!
      \sa workerThread, finished()
    */
    void stop();

signals:

    //! Signal emits when we leave the software to indicate that workerThread need to stop and instances of
    //! of Controller and Model need to be deleted
    /*!
      \sa workerThread, Model
    */
    void finished();

};
#endif // CONTROLLER_H
