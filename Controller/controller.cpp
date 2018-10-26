#include "controller.h"

Controller::Controller(){

}

Controller::~Controller(){
    cout << "Destructor controller" << endl;
}

void Controller::linkModel(Model *_pModel)
{
    pModel = _pModel;
}

void Controller::start()
{
    // Limits the maximum number of threads used for dispatch the signals
    //cout << "Number of logical threads used: " << QThreadPool::globalInstance()->maxThreadCount() << endl;

    if(!executing){
        if(pModel == nullptr){
            //FIXME cerr << "Controller::start You need to link a model to the controller" << endl;
        }

    // Do action at start up

    executing = true;

    }else{
        cout << "The application is already running !" << endl;
    }
}

void Controller::stop(){

    // Do action before leaving

    cout << endl << "Controller emit finished signal" <<endl;
    executing = false;
    finished();
}
