/**
 * @file   meshviewer.c
 * @author Liangfu Chen <liangfu.chen@nlpr.ia.ac.cn>
 * @date   Fri Jan 24 16:25:21 2014
 * 
 * @brief  
 * 
 * 
 */
#include "meshviewer.h"

void glDrawWiredCube()
{
  float verts[]={
	-1.f, -1.f, -1.f, // 0
	-1.f,  1.f, -1.f, // 1
	 1.f,  1.f, -1.f, // 2
	 1.f, -1.f, -1.f, // 3
	-1.f, -1.f,  1.f, // 4
	-1.f,  1.f,  1.f, // 5
	 1.f,  1.f,  1.f, // 6
	 1.f, -1.f,  1.f  // 7 
  };
  int faces[]={
	0,1,2,3,
	4,5,6,7,
	0,1,5,4,
	3,2,6,7
  };
  int i,j;
  for (i=0;i<4;i++){
	glBegin(GL_LINE_LOOP);
	for (j=0;j<4;j++){glVertex3fv((verts+faces[i*4+j]*3));}
	glEnd();
  }
}
