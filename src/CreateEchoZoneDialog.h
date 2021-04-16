#ifndef CREATE_ECHO_ZONE_H
#define CREATE_ECHO_ZONE_H

#include "effects-manager.h"


class CreateEchoZoneDialog
{

public:
	CreateEchoZoneDialog();
	
	void SetPointerToEffectsManager(EffectsManager* effects_manager);
	
	void DrawDialog();
	
	void Preview();

	void Exit();


	//function to return position of new sound producer object
	void getNewPosition(float& x, float& y, float& z);

	std::string& getNewName();

	float& getNewWidth();
	
	EchoZoneProperties& getNewProperties();
	

	bool CancelClickedOn();
	bool OkClickedOn();
	
	void resetConfig();
	
private:
	EffectsManager* m_effects_manager_ptr;
	
	int spt_selection_index;
	
	
	//properties of zone to creates
	
	std::string name;
	float xPosition;
	float yPosition;
	float zPosition;
	float width;
	
	EchoZoneProperties properties;
	
	void initPrivateVariables();
	
	bool okClicked;
	bool cancelClicked;

};



#endif
