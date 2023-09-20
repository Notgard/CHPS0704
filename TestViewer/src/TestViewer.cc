#include "TestViewer.h"


#include "ColorMaterial.h"

#include "myColorMaterial.h"
#include "myTextureMaterial.h"
#include "myPhongMaterial.h"

#include "myTextureMaterialTP2.h"

#include "TextureMaterial.h"
#include "GridMaterial.h"
#include "PhongMaterial.h"

TestViewer::TestViewer() : QGLShaderViewer ()
{}
TestViewer::~TestViewer()
{}

void TestViewer::resizeGL(int width, int height)
{
    QGLShaderViewer::resizeGL(width, height);
    this->m_framebuffer->resize(width, height);
}
void  TestViewer::init               ()
{
    this->m_framebuffer = new FBO(this->width(), this->height(), GL_RGB8);
    getCamera()->setNearAndFar( 0.01f, 100 );
    getCamera()->setView(QVector3D(0,0.2f,4), QVector3D(0,1,0), QVector3D(0,0,0) );

    startAnimation();
}
void  TestViewer::createSceneEntities()
{

    addGeometry( "cube",  new Geometry(":/3d/cube.obj") );
    addGeometry( "lapin", new Geometry(":/3d/Bunny.obj") );
    addGeometry( "sol",   new Geometry(":/3d/sol.obj") );
    addGeometry( "quad",  new Geometry(":/3d/quad.obj") );

    //Ajout du FBO comme texture à utiliser pour la geométrie
    addMaterial("fbo", new myTextureMaterial(this->m_framebuffer) );
    addMaterial( "jaune", new ColorMaterial(QVector4D(1.0f,1.f,0.f,1.0f)) );
    addMaterial( "rouge", new ColorMaterial(Qt::red) );

    //adding the custom color material
    addMaterial("blue", new myColorMaterial(QVector4D(0.0f,0.f,1.f,1.0f), QString("./data/myColorMaterial/"), "color"));

    //addMaterial( "sol",   new TextureMaterial(QString(":/textures/sol.jpg")) );

    addMaterial("sol", new myTextureMaterialTP2(QString(":/textures/sol.jpg")) );

    addMaterial( "phong", new PhongMaterial( QVector4D(0.1f,0.1f,0.1f,1.f),
                                             QVector4D(0.1f,0.9f,0.4f,1.f), 128) );

    addMaterial( "myphong", new myPhongMaterial( QVector4D(0.1f,0.1f,0.1f,1.f),
                                             QVector4D(0.1f,0.9f,0.4f,1.f), 128) );

    addMaterial( "lapinBlanc",    new TextureMaterial(QString(":/textures/bunny2.jpg")) );
    addMaterial( "grid",          new GridMaterial(2, Qt::red, 0.03f ) );


    Mesh *  mesh;

    // lapin éclairé
    mesh = new Mesh( getGeometry("lapin"), getMaterial("blue") );
    addEntityInScene("LapinJaune", mesh );
    //mesh->translate(QVector3D(0,0,-2));
    mesh->translate(QVector3D(0,1,1));



    // Lapin my phong
    mesh = new Mesh( getGeometry("lapin"), getMaterial("myphong"), true );
    addEntityInScene("lapinBlanc", mesh );
    mesh->translate(QVector3D(0,1,0));
    mesh->scale(QVector3D(3.0f,3.0f,3.0f));



    // Cube grillé
    //mesh = new Mesh( getGeometry("cube"), getMaterial("grid"), true );
    //addEntityInScene("cubeGrid", mesh );


    // Sol avec texture
    mesh = new Mesh( getGeometry("sol"), getMaterial("sol"), true);
    mesh->scale(0.3f);
    mesh->setFrozen(true);
    addEntityInScene("solTexture", mesh );


    // Lapin Phong
    mesh = new Mesh( getGeometry("lapin"), getMaterial("phong"), true );
    addEntityInScene("lapinPhong", mesh );
    mesh->scale(QVector3D(6.f,6.f,6.f));

    m_lights.push_back( PointLight( getCamera()->getPosition() + getCamera()->getRightDir()*4.f, Qt::white ) );

    this->m_cube = new Mesh(this->getGeometry("sol"), this->getMaterial("fbo"), true);
}



void  TestViewer::animate            ()
{
    if(!pause) {
        foreach (Mesh * entity, getListEntityInScene() )
        {
            entity->rotateOnSelf( 0.05f, QVector3D(1,1,1) );
        }
    }
}

void  TestViewer::drawInformation    ()
{
    glColor4f(1.,1.,0., 1.0);
    QFont font( "Arial", 10);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 1 );
    font.setStretch( 100 );

    // Affichage du texte 2D
    // ----------------------
    //   coord screen
    /// TODO - Ajouter l'affichage du texte 2D.
    ///
    int y = 0, dy = 30;
    drawText(10,  (y+=dy), QString(" - truc y(%1), dy(%2)").arg(y).arg(dy), Qt::white, font);
}



void  TestViewer::drawScene          ()
{
    glEnable(GL_DEPTH_TEST);
     drawMono();
}





// rendu monoscopic
void TestViewer::drawMono()
{
    // Creation de la vue mono
    ///*
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    foreach( Mesh * entity, getListEntityInScene() )
    {
        entity->render( getCamera(), m_lights );
    }
    //*/

    /* TP3 FBO
    this->m_framebuffer->bind();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    foreach( Mesh * entity, getListEntityInScene() )
    {
        entity->render( getCamera(), m_lights );
    }
    this->m_framebuffer->release();
    this->m_cube->render(this->getCamera(), m_lights, this->getMaterial("fbo"));
    */

}


void  TestViewer::keyPressEvent     (QKeyEvent * event)
{
    switch( event->key() )
    {
        case Qt::Key_L : qDebug() << " Vous avez taper la touche L"; break;
        case Qt::Key_P: pause = pause ? false : true;
        default: QGLShaderViewer::keyPressEvent(event); break;
    }

    qDebug() << " key : " <<  QKeySequence(event->key()).toString();

    update();
}
