#include "InDE.h"
#include "App.h"
#include "MainWindow.h"

int main(int argc, char** argv)
{
	App app("InDE");
	app.init(argc, argv);
	MainWindow win(&app, "InDE");
	app.create();
	return app.run();
}
