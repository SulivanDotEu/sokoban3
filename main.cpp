#include <iostream>
#include "Model.h"
#include "MyView.h"


int main(void){
	Model * m = Model::getInstance();
	m->newGame("levels");
	MyView* v = MyView::getInstance();
	m->setListener(v);

	v->start();
	return 0;
	
}