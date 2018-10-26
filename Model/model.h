#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <iostream>

using namespace std;

/*!
 *  \brief     Store all the data necessary for the software
 *  \details   Contains all the data. Contains also a DataPackage which store all the data
 *             necessary to the View
 *  \author    Quentin Collet
 *  \version   1.0
 *  \date      Nov 2018
 *  \pre       Must be instantiated in the Factory class (<b>only one time</b>)
 */
class Model : public QObject
{
    Q_OBJECT

private:

public:

    //! Need to initialize DataPackage in the construction (because he takes reference), so we must
    //! give the reference of all the objects we want to display in the view
    Model();

    //! Nothing special to destroy in the destructor
    ~Model();

    //! The initialization of the model gives a link for the view
    /*!
      \sa Model, initDataToView
    */
    void init();

signals:
    //! Send a pointer to the View to read data (without copy)
    /*!
      \param Pointer on Model who contains all the data needed by the View
      \sa View::initDataFromModel(Model *), dataToView, DataPackage
    */
    void initDataToView( Model* );

public slots:

};

#endif // MODEL_H
