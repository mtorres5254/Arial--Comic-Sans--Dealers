#ifndef _MODULECOMBOS_H
#define _MODULECOMBOS_H

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"


class ModuleCombos : public Module
{
public:
	ModuleCombos();
	~ModuleCombos();
	
	bool Init();
	update_status Update();
	bool CleanUp();
public:

	CommandPunch pnch;

};
enum class InputCommandTypes
{
	punch,
	max
};

struct InputCommand
{
	InputCommandTypes type = InputCommandTypes::max;

	InputCommand(InputCommandTypes type) : type(type) {}

	virtual bool Check(uint past_frames) const = 0;


};

struct CommandPunch : public InputCommand
{

	CommandPunch() : InputCommand(InputCommandTypes::punch) {}
	bool Check(uint frames_past) const override;

};




#endif // !_MODULECOMBOS_H
