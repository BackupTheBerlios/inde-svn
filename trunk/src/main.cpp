#include <fx.h>
#include "InDE.h"
#include "MainWindow.h"

int main(int argc, char** argv)
{
	InDE app("InDE", "");
	app.init(argc, argv);
	MainWindow* win = new MainWindow(&app, "InDE SVN");
	app.create();
	return app.run();
}
