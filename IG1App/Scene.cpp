#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{ 
	setGL();  // OpenGL settings

	// allocate memory and load resources
    // Lights
    // Textures

    // Graphics objects (entities) of the scene
	gObjects.push_back(new EjesRGB(400.0));
	if (this->mId == 0) {
		Abs_Entity* magentaCircle = new Poligono(300, 200);
		magentaCircle->setColor({ 255.0, 0.0, 255.0, 1.0 });
		gObjects.push_back(magentaCircle);

		Abs_Entity* trianguloRGB = new TrianguloRGB(40);
		gObjects.push_back(trianguloRGB);
		trianguloRGB->setModelMat(translate(trianguloRGB->modelMat(), dvec3(200, 0, 0)));

		gObjects.push_back(new RectanguloRGB(400, 300));
	}
	else if (this->mId == 1) {
		gObjects.push_back(new CuboRGB(100));

	}	
}
//-------------------------------------------------------------------------
void Scene::free() 
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
}
//-------------------------------------------------------------------------
void Scene::setGL() 
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 

}
//-------------------------------------------------------------------------
void Scene::resetGL() 
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const 
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
	{
	  el->render(cam.viewMat());
	}
}
//-------------------------------------------------------------------------

void Scene::setState(int id) {
	if (id != this->mId) {
		this->free();
		gObjects.clear();
		this->setScene(id);
		this->init();
	}
}

void Scene::update() {
	for (Abs_Entity* obj : gObjects)
		obj->update();
}


