#include "factory.h"

Factory::Factory() : controller(new Controller), model(new Model), view(new View)
{
}

void Factory::init()
{

    /* Link the three class with the pattern MVC

                    View
                   /    ^
              ------------------ separate thread, necessary to use connect from Qt to communicate
                  /      \
                 V        \
          Controller --> Model
    */

    /** INITIALIZATION */

    // Move all non-GUI objects in a different thread
    workerThread = new QThread;
    controller->moveToThread(workerThread);
    model->moveToThread(workerThread);

    /** VIEW <-> CONTROLLER */
    //FIXME Proper to application
    /*connect(view->getUI()->pBRelaod,SIGNAL(pressed()),controller,SLOT(reloadData()) );
    connect(view,SIGNAL(stopApplication()),polling,SLOT(stop()) );
    connect(controller, SIGNAL(relaodButton(bool)),view->getUI()->pBRelaod,SLOT(setEnabled(bool)) );
    connect(controller, SIGNAL(endScan()), view, SIGNAL(refresh()));*/
    connect(this,SIGNAL(close_MVC()),controller,SLOT(stop()) );

    /** CONTROLLER -> MODEL */
    // Possible because the two objects live in the same thread
    controller->linkModel(model);

    // FIXME notification for model
    //Notify model that controller send a new scan. Model will notify all intersections
    //connect( controller, SIGNAL(newScan()), model, SIGNAL(newScan()));


    /** MODEL -> VIEW */
    // Register the data type before to establish the connection
    qRegisterMetaType< Model* >("Model*");
    connect(model, SIGNAL(initDataToView(Model*)),
            view, SLOT(initDataFromModel(Model*)) );

    /** THREAD WORKER */
    // Run Controller after we start the workerthread
    connect(workerThread, SIGNAL(started()), controller, SLOT(start()));

    // Delete pointer on controller and model as soon as possible
    connect(controller, SIGNAL(finished()), model, SLOT(deleteLater()));
    connect(controller, SIGNAL(finished()), controller, SLOT(deleteLater()));

    // Delete worker thread as soon as possible (direct connection called immediatly)
    connect(controller, SIGNAL(finished()), workerThread, SLOT(quit()), Qt::DirectConnection);

    // Start running the software
    workerThread->start();
}

Factory::~Factory()
{
    cout << endl << "Exiting..." << endl;

    if (workerThread->isRunning()) {

        close_MVC();

        workerThread->wait(7000); // Important to wait to give the time to the worker thread to delete
                                  // all the data saved

        if (workerThread->isFinished()) // Check that the thread had time to leave
        {

            cout << "Application exits properly" << endl;
            delete workerThread;

        }else{

            // Thread is blocked somewhere (in a function ?)
            cerr << "Factory::~Factory Application doesn't exit properly !" << endl;
        }
    }

    cout << endl << "---------- END OF PROGRAM ----------" << endl;
    delete view;
}
