#include "InDE.h"

int main(int argc, char** argv)
{
	App app("InDE");
	app.init(argc, argv);

	MainWindow* win = new MainWindow(&app, "InDE");

	app.addSignal(SIGINT, win, MainWindow::ID_QUIT);
	app.create();

	FXSplashWindow* splash = new FXSplashWindow(&app, new FXPNGIcon(&app, splash_png), SPLASH_SHAPED|SPLASH_DESTROY|SPLASH_OWNS_ICON, 1500);
	splash->create();
	splash->show(PLACEMENT_SCREEN);

	return app.run();
}
