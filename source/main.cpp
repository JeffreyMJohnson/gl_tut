#include "SolarSystemApp.h"

void main()
{
	SolarSystemApp* app = new SolarSystemApp();
	if (app->StartUp())
	{
		while (app->Update())
		{
			app->Draw();
		}
		app->ShutDown();
	}
	delete app;
	return;
}