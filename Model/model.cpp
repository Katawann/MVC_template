#include "model.h"

Model::Model()
{
}

Model::~Model()
{
    cout << "Destructor model" << endl;
}

void Model::init()
{
    initDataToView(this);
}



