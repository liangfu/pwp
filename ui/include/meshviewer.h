/**
 * @file   meshviewer.h
 * @author Liangfu Chen <liangfu.chen@nlpr.ia.ac.cn>
 * @date   Fri Jan 24 15:52:47 2014
 * 
 * @brief  
 * 
 * 
 */
#ifndef __MESH_VIEWER_H__
#define __MESH_VIEWER_H__

#include <QtGui>
#include <QtOpenGL>
#include <GL/glu.h>

#include "compvis.h"

void glDrawWiredCube();

class MeshViewer : public QGLWidget
{
protected:
  void initializeGL()
  {
	GLfloat light0_specular[] = { .3f, .3f, .3f, 0.1f };
	GLfloat light0_ambient[] =  { 0.2f, 0.2f, 0.2f, .1f };
	GLfloat light0_diffuse[] =  { .03f, .03f, .03f, .1f };
	GLfloat light0_position[] = { 50.f, 50.f, -10.f, .1f };

	GLfloat light1_specular[] = { .3f, .3f, .3f, 0.1f };
	GLfloat light1_ambient[] = { .2f, .2f, .2f, 0.1f };
	GLfloat light1_diffuse[] = { .03f, .03f, .03f, 0.1f };
	GLfloat light1_position[] = { -50.f, -50.f, 10.f, 1.0f };

	GLfloat material_color[] = { .1f, .1f, .1f, .1f };
 
	glClearColor(0,0,0,0);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.f);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	// glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION,light0_position);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	// glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, material_color);
	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
  
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_EQUAL);
	glEnable(GL_CULL_FACE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
  }

  void resizeGL(int w, int h)
  {
	h=MAX(1,h);w=MAX(1,w);
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.f,float(w)/float(h),.1f,100.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  }

  void paintGL()
  {
	int i;
	double scale=MIN(2./m_size[0],MIN(2./m_size[1],2./m_size[2]));
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	// push
	glTranslatef(0,0,-6.f);
	glTranslatef(0,0,m_angle[2]); // zoom by mouse wheel
	glRotatef(m_angle[0],1,0,0);
	glRotatef(m_angle[1],0,1,0);
	// draw binding box
	glColor3f(1,1,1);
	if (!m_picking){glDrawWiredCube();}
	// draw surface data
	glPushMatrix();
	glScaled(scale,scale,scale);
	glRotatef(-90,1,0,0);
	drawObject();
	glPopMatrix();
	// pop
	glPopMatrix();
  }

  void drawObject(){
	if (!m_picking){
	  if (m_shading==CV_SHADING_FLAT){
		drawObject_flat();
	  }else{
		drawObject_smooth();
		drawObject_smooth_fast();
	  }
	}else{
	  drawObject_pick();
	}
  }
  void drawObject_flat(){
	int i;
	int vstep=m_verts->cols;
	float * vptr=m_verts->data.fl;
	int fstep=m_faces->cols;
	int * fptr=m_faces->data.i;
	float * nptr=m_norms->data.fl;
	int nstep=m_norms->cols;
	float * cptr=m_color->data.fl;
	glBegin(GL_TRIANGLES);
	for (i=0;i<m_faces->rows;i++){
	  int * f=fptr+fstep*i;
	  glColor3fv(cptr+i*3);
	  glNormal3fv(nptr+nstep*i);
	  glVertex3fv(vptr+vstep*f[0]);
	  glVertex3fv(vptr+vstep*f[1]);
	  glVertex3fv(vptr+vstep*f[2]);
	}
	glEnd();
  }
  void drawObject_smooth(){
	int i;
	int vstep=m_verts->cols;
	float * vptr=m_verts->data.fl;
	int fstep=m_faces->cols;
	int * fptr=m_faces->data.i;
	float * nptr=m_norms->data.fl;
	int nstep=m_norms->cols;
	float * cptr=m_color->data.fl;
	glBegin(GL_TRIANGLES);
	for (i=0;i<m_faces->rows;i++){
	  int * f=fptr+fstep*i;
	  glColor3fv(cptr+i*3);
	  glNormal3fv(nptr+nstep*f[0]);
	  glVertex3fv(vptr+vstep*f[0]);
	  glNormal3fv(nptr+nstep*f[1]);
	  glVertex3fv(vptr+vstep*f[1]);
	  glNormal3fv(nptr+nstep*f[2]);
	  glVertex3fv(vptr+vstep*f[2]);
	}
	glEnd();
  }
  void drawObject_smooth_fast(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m_verts->data.ptr);
	glNormalPointer   (GL_FLOAT, 0, m_norms->data.ptr);
	glColorPointer (3, GL_FLOAT, 0, m_color->data.ptr);
	glDrawElements(GL_TRIANGLES,m_faces->rows*3,GL_UNSIGNED_INT,m_faces->data.ptr);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
  }
  void drawObject_pick(){
	int i;
	int vstep=m_verts->cols;
	float * vptr=m_verts->data.fl;
	int fstep=m_faces->cols;
	int * fptr=m_faces->data.i;
	float * nptr=m_norms->data.fl;
	int nstep=m_norms->cols;
	glBegin(GL_TRIANGLES);
	for (i=0;i<m_faces->rows;i++){
	  int * f=fptr+fstep*i;
	  glColor3ub(((i<<1)&0xff0000)>>16,((i<<1)&0xff00)>>8,((i<<1)&0xff));
	  glVertex3fv(vptr+vstep*f[0]);
	  glVertex3fv(vptr+vstep*f[1]);
	  glVertex3fv(vptr+vstep*f[2]);
	}
	glEnd();
  }
  
  void compute_normal()
  {
	if (m_norms){cvReleaseMat(&m_norms);m_norms=NULL;}
	if (m_shading==CV_SHADING_FLAT){
	  m_norms=cvCreateMat(m_faces->rows,3,CV_32F);
	  cvCalcSurfaceNormal(m_verts,m_faces,m_norms,CV_SHADING_FLAT);
	}else if (m_shading==CV_SHADING_SMOOTH){
	  m_norms=cvCreateMat(m_verts->rows,3,CV_32F);
	  cvCalcSurfaceNormal(m_verts,m_faces,m_norms,CV_SHADING_SMOOTH);
	}else{assert(false);}
  }

  int m_shading;
  int m_picking;
  int m_width;
  int m_height;

  CvMat * m_verts;
  CvMat * m_faces;
  CvMat * m_norms;
  CvMat * m_color;

  float m_size[3];
  float m_center[3];
  float m_transform[16];
  float m_angle[3];

public:
  MeshViewer(QWidget * parent):
	QGLWidget(parent),
	m_shading(CV_SHADING_SMOOTH),m_picking(0),
	m_verts(NULL),m_faces(NULL),m_norms(NULL)
  {
	m_width =parent->width()-4;
	m_height=parent->height()-4;
  }

  void display(QString fname)
  {
	const char * tmp=fname.toAscii();
	cvLoadSurface(tmp,&m_verts,&m_faces);
	initialize();
  }

  void initialize()
  {
	int i;
	m_color=cvCreateMat(m_faces->rows,m_faces->cols,CV_32F);
	{
	  float color[3]={.3f,0.3f,0.f};
	  for (i=0;i<m_faces->rows;i++){memcpy(m_color->data.fl+3*i,color,sizeof(float)*3);}
	}

	float min[3],max[3];
	for (i=0;i<3;i++){min[i]=max[i]=m_verts->data.fl[i];}
	for (i=0;i<m_verts->rows;i++){
	  min[0]=MIN(min[0],(m_verts->data.fl+3*i)[0]);
	  max[0]=MAX(max[0],(m_verts->data.fl+3*i)[0]);
	  min[1]=MIN(min[1],(m_verts->data.fl+3*i)[1]);
	  max[1]=MAX(max[1],(m_verts->data.fl+3*i)[1]);
	  min[2]=MIN(min[2],(m_verts->data.fl+3*i)[2]);
	  max[2]=MAX(max[2],(m_verts->data.fl+3*i)[2]);
	}

	float size[3]={max[0]-min[0],max[1]-min[1],max[2]-min[2]};
	float center[3]={(max[0]+min[0])*.5,(max[1]+min[1])*.5,(max[2]+min[2])*.5};
	float transform[16]={
	  size[0],0,0,center[0],
	  0,size[1],0,center[1],
	  0,0,size[2],center[2],
	  0,0,0,1
	};
	// LOGI("size: %.1f,%.1f,%.1f",size[0],size[1],size[2]);
	// LOGI("center: %.1f,%.1f,%.1f",center[0],center[1],center[2]);

	memcpy(m_size,size,sizeof(size));
	memcpy(m_center,center,sizeof(center));
	memcpy(m_transform,transform,sizeof(transform));
	memset(m_angle,0,sizeof(m_angle));

	compute_normal();
  }

  ~MeshViewer()
  {
	if (m_verts){cvReleaseMat(&m_verts);m_verts=0;}
	if (m_faces){cvReleaseMat(&m_faces);m_faces=0;}
	if (m_norms){cvReleaseMat(&m_norms);m_norms=0;}
  }
};

#endif // __MESH_VIEWER_H__
