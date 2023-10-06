#include <QApplication>

#include "QGLShaderViewer.h"
#include "TestViewer.h"



#ifdef prepaTP
    #include "TestStereoViewer.h"
#include "TestMultiscopicViewer.h"
#include "MultiscopicViewer.h"
#endif


int main(int argc, char *argv[])
{
    //return testWagon( argc, argv );

    QApplication app(argc, argv);
 
    // Set OpenGL Version information
    // Note: This format must be set before show() is called.
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setSamples(16);
    format.setDepthBufferSize(32);
    format.setMajorVersion(4);
    format.setMinorVersion(5);

  // Prise en charge de la stéréo
    format.setStereo(true);


 // Set the window up
//    QGLShaderViewer window;
    TestViewer window;
//    TestStereoViewer window;
    //TestMultiscopicViewer window;
//    MultiscopicViewer window;
    window.setFormat(format);
    window.resize(QSize(800, 600));
    window.show();
 
    return app.exec();
}
