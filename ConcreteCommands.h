#include "Model.h"
#include "Command.h"

/*
	Definition de toutes les commandes concretes
	Chaque classe herite de Command et implemene la methode execute()
*/


//Mouvement vers la gauche
class Left : public Command
{
    Model* model;

public:
    Left(Model* m)
    {
        this->model = m;
    }

    void execute()
    {
		model->move(LEFT);
    }
};

//Mouvement vers la droite
class Right : public Command
{
    Model* model;

public:
    Right(Model* m)
    {
        this->model = m;
    }

    void execute()
    {
		model->move(RIGHT);
    }
};

//Mouvement vers le haut
class Up : public Command
{
    Model* model;

public:
    Up(Model* m)
    {
        this->model = m;
    }

    void execute()
    {
		model->move(UP);
    }
};

//Mouvement vers le bas
class Down : public Command
{
    Model* model;

public:
    Down(Model* m)
    {
        this->model = m;
    }

    void execute()
    {
		model->move(DOWN);
    }
};

//Zoom sur la map
class Zoom : public Command
{
    MyView* myView;

public:
    Zoom(MyView* m)
    {
        this->myView = m;
    }

    void execute()
    {
		myView->zoom();
    }
};

//Dezoom sur la map
class Dezoom : public Command
{
    MyView* myView;

public:
    Dezoom(MyView* m)
    {
        this->myView = m;
    }

    void execute()
    {
		myView->dezoom();
    }
};

//Faire un undo
class UndoCommand : public Command
{
    Model* model;

public:
    UndoCommand(Model* m)
    {
        this->model = m;
    }

    void execute()
    {
		model->Undo();
    }
};