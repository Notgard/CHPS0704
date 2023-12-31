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
    //redimensionne le FBo par rapport à la taille de l'écran
    this->m_framebuffer->resize(width, height);
}
void  TestViewer::init               ()
{
    //création du FBO avec la taille initiale de l'écran de l'application
    this->m_framebuffer = new FBO(this->width(), this->height(), GL_RGB8);
    //création de la classe gérant les effets produit à partir du FBO 
    this->m_effect = new myEffect();
    //initialisation de l'état des filtres de l'effet du FBO (ON/OFF)
    this->m_effect->setFilter(this->filter);
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
                                             QVector4D(0.f,0.9f,0.f,1.f), 128) );

    addMaterial( "lapinBlanc",    new TextureMaterial(QString(":/textures/bunny2.jpg")) );
    addMaterial( "grid",          new GridMaterial(2, Qt::red, 0.03f ) );


    Mesh *  mesh;

    // lapin éclairé
    //mesh = new Mesh( getGeometry("lapin"), getMaterial("blue") );
    //addEntityInScene("LapinJaune", mesh );
    ////mesh->translate(QVector3D(0,0,-2));
    //mesh->translate(QVector3D(0,1,1));

    if(phong_render) {
        // Lapin my phong
        //mesh = new Mesh( getGeometry("lapin"), getMaterial("myphong"), true );
        //addEntityInScene("lapinBlanc", mesh );
        //mesh->translate(QVector3D(0,1.5,0));
        //mesh->scale(QVector3D(6.0f,6.0f,6.0f));
        //mesh->setFrozen(true);

        //cube avec mon modèle phong
        mesh = new Mesh( getGeometry("cube"), getMaterial("myphong"), true );
        addEntityInScene("cubePhong", mesh );
        mesh->setFrozen(true);

        // Lapin Phong
        //mesh = new Mesh( getGeometry("lapin"), getMaterial("phong"), true );
        //addEntityInScene("lapinPhong", mesh );
        //mesh->scale(QVector3D(6.f,6.f,6.f));
        //mesh->setFrozen(true);

        // Sol avec texture
        mesh = new Mesh( getGeometry("sol"), getMaterial("sol"), true);
        mesh->scale(0.3f);
        mesh->setFrozen(true);
        addEntityInScene("solTexture", mesh );
    } else {
        // Lapin blanc
        mesh = new Mesh( getGeometry("lapin"), getMaterial("lapinBlanc"), true );
        addEntityInScene("lapinBlanc", mesh );
        mesh->translate(QVector3D(0,1,0));
        mesh->scale(QVector3D(6.0f,6.0f,6.0f));
        mesh->setFrozen(true);

        // Cube grillé
        mesh = new Mesh( getGeometry("cube"), getMaterial("grid"), true );
        mesh->setFrozen(true);
        addEntityInScene("cubeGrid", mesh );


        // Sol avec texture
        mesh = new Mesh( getGeometry("sol"), getMaterial("sol"), true);
        mesh->scale(0.3f);
        mesh->setFrozen(true);
        addEntityInScene("solTexture", mesh );
    }

    m_lights.push_back( PointLight( getCamera()->getPosition() + getCamera()->getRightDir()*4.f, Qt::white ) );

    //cube utiliser pour afficher le contenu du FBO
    //this->m_cube = new Mesh(this->getGeometry("cube"), this->getMaterial("fbo"), true);
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
    //   Taille de l'écran + raccourcis clavier pour modifier le rendu graphique dans l'application
    QSize curr_size = this->size();
    drawText(450,  10, QString(" - Size : (%1, %2)").arg(curr_size.width()).arg(curr_size.height()), Qt::yellow, font);
    drawText(10,  30, QString(" - Press 'L' to enable FBO render"), Qt::green, font);
    drawText(10,  50, QString(" - Press 'M' to switch the current FBO filter"), Qt::green, font);
    drawText(10,  70, QString(" - Press 'K' to switch the current scene entities (loading may take some time...)"), Qt::green, font);
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
    if(!fbo_render) {//rendu de la scène sans l'utilisation du FBO
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        foreach( Mesh * entity, getListEntityInScene() )
        {
            entity->render( getCamera(), m_lights );
        }
    } else {//rendu de la scène avec l'utilisation du FBO (TP3)
        this->m_framebuffer->bind();
        //ajout des éléments de la scène dans le FBO
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        foreach( Mesh * entity, getListEntityInScene() )
        {
            entity->render( getCamera(), m_lights );
        }
        this->m_framebuffer->release();
        //faire le rendu des effets shaders à partir du contenu du FBO
        this->m_effect->render(0, "monFBO", this->m_framebuffer);
        //uncomment to render the FBO on each face of the cube and comment out the previous render
        //this->m_cube->render(this->getCamera(), m_lights, this->getMaterial("fbo"));
    }
}


void  TestViewer::keyPressEvent     (QKeyEvent * event)
{
    switch( event->key() )
    {
        case Qt::Key_L : //activation/désactivation du rendu avec FBO
        fbo_render = fbo_render ? false : true;
        break;
        case Qt::Key_P: pause = pause ? false : true; break; //mettre en pause le rendu de la scène
        case Qt::Key_M: //activation/désactivation des effects du rendu avec FBO
        filter = filter ? false : true;
        qDebug() << filter;
        this->m_effect->setFilter(filter);
        break;
        case Qt::Key_K: //changement des objects dans la scène à rendre

        if(phong_render) {
            removeEntityFromScene("cubePhong");
            removeEntityFromScene("solTexture");
        } else {
            removeEntityFromScene("lapinBlanc");
            removeEntityFromScene("cubeGrid");
            removeEntityFromScene("solTexture");
        }

        phong_render = phong_render ? false : true;
        createSceneEntities();
        break;
        default: QGLShaderViewer::keyPressEvent(event); break;
    }

    qDebug() << " key : " <<  QKeySequence(event->key()).toString();

    update();
}
