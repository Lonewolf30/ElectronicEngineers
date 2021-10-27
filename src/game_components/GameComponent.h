#ifndef ELECTRONICENGINEERS_GAMECOMPONENT_H
#define ELECTRONICENGINEERS_GAMECOMPONENT_H

class GameComponent {
public:
	virtual void CleanUp(){};
	virtual int GetValue(){return 0;}
};

#endif
