#ifndef INDE_H
#define INDE_H

#define PROJECT_TYPE_CPP "C/C++"
#define PROJECT_TYPE_RUBY "Ruby"
#define PROJECT_TYPE_PYTHON "Python"

#define PROJECT_BUILD_EXECUTABLE "Executable"
#define PROJECT_BUILD_STATIC "Static library"
#define PROJECT_BUILD_SHARED "Shared library"

#define PROJECT_LICENSE_NONE	0
#define PROJECT_LICENSE_GPL		1
#define PROJECT_LICENSE_LGPL	2
#define PROJECT_LICENSE_USER	100

#include <fx.h>
#include <signal.h>
#include "MainWindow.h"

class MainWindow;

/*
	Class: InDE
*/
class InDE : public FXApp
{
	FXDECLARE(InDE)

	protected:
		InDE() {};
		InDE(const InDE&);
		InDE& operator=(const InDE&);

	public:
		enum {
			ID_SELF = FXApp::ID_LAST,
			ID_LAST,
		};

	public:

		/// Constructor
		InDE(const FXString&, const FXString&);

		/// Create method
		virtual void create();

		/// Destructor
		virtual ~InDE();

};

#endif // INDE_H
