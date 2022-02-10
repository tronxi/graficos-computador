#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::upload(dmat4 const& modelViewMat) const 
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Abs_Entity()
{
  mMesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mMesh; mMesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}


Poligono::Poligono(GLint numLados, GLdouble rad) : Abs_Entity()
{
	mMesh = Mesh::generaPoligonoRegular(numLados, rad);
}

Poligono::~Poligono()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void Poligono::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		glColor3d(mColor.r, mColor.g, mColor.b);
		mMesh->render();
		glLineWidth(1);
		glColor3d(1, 1, 1);
	}
}
//-------------------------------------------------------------------------

TrianguloRGB::TrianguloRGB(GLdouble rad) : Abs_Entity()
{
	mMesh = Mesh::generaTrianguloRGB(rad);
}
//-------------------------------------------------------------------------

TrianguloRGB::~TrianguloRGB()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void TrianguloRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
		glColor3d(mColor.r, mColor.g, mColor.b);
		mMesh->render();
		glColor3d(1, 1, 1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h) : Abs_Entity()
{
	mMesh = Mesh::generaRectanguloRGB(w,h);
}
//-------------------------------------------------------------------------

RectanguloRGB::~RectanguloRGB()
{
	delete mMesh; mMesh = nullptr;
};
//-------------------------------------------------------------------------

void RectanguloRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
		glColor3d(mColor.r, mColor.g, mColor.b);
		mMesh->render();
		glColor3d(1, 1, 1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
 