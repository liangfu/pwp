/**
 * @file   compvis.h
 * @author Liangfu Chen <liangfu.chen@nlpr.ia.ac.cn>
 * @date   Tue Dec 31 09:54:18 2013
 * 
 * @brief  
 * 
 * 
 */

#ifndef __COMP_VIS_H__
#define __COMP_VIS_H__

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

typedef unsigned char uchar;

typedef struct {
  int type;
  int cols;
  int rows;
  union{uchar * ptr;short * s;double * db;float * fl;int * i;}data;
  int step;
} CvMat;

#ifdef __cplusplus
#define CV_INLINE inline
#else
#define CV_INLINE static
#endif
enum{CV_8U=1,CV_8S,CV_16S,CV_32S,CV_32F,CV_64F};
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define CV_PI 3.141592653589793
#define CV_MAT_TYPE(t) ((t)&0xff)

CV_INLINE
CvMat * cvCreateMat(int rows, int cols, int type)
{
  assert((rows>0)&&(cols>0)&&(type>0));
  CvMat * arr = (CvMat*)malloc(sizeof(CvMat));
  arr->type=type;
  arr->rows=rows;
  arr->cols=cols;
  if ((arr->type==CV_8U)||(arr->type==CV_8S)){
	arr->data.ptr=(uchar*)malloc(rows*cols);
	arr->step=cols;
  }else if (arr->type==CV_16S){
	arr->data.ptr=(uchar*)malloc(rows*cols*sizeof(short));
	arr->step=cols*sizeof(short);
  }else if (arr->type==CV_32S){
	arr->data.ptr=(uchar*)malloc(rows*cols*sizeof(int));
	memset(arr->data.ptr,0,rows*cols*sizeof(int));
	arr->step=cols*sizeof(int);
  }else if (arr->type==CV_32F){
	arr->data.ptr=(uchar*)malloc(rows*cols*sizeof(float));
	arr->step=cols*sizeof(float);
  }else if (arr->type==CV_64F){
	arr->data.ptr=(uchar*)malloc(rows*cols*sizeof(double));
	arr->step=cols*sizeof(double);
  }
  return arr;
}

CV_INLINE
CvMat cvMat(int rows, int cols, int type, void * ptr)
{
  assert((rows>0)&&(cols>0)&&(type>0));
  CvMat arr;// = (CvMat*)malloc(sizeof(CvMat));
  arr.type=type;
  arr.rows=rows;
  arr.cols=cols;
  if ((arr.type==CV_8U)||(arr.type==CV_8S)){
	arr.data.ptr=(uchar*)ptr;
	arr.step=cols;
  }else if (arr.type==CV_16S){
	arr.data.ptr=(uchar*)ptr;
	arr.step=cols*sizeof(short);
  }else if (arr.type==CV_32S){
	arr.data.ptr=(uchar*)ptr;
	arr.step=cols*sizeof(int);
  }else if (arr.type==CV_32F){
	arr.data.ptr=(uchar*)ptr;
	arr.step=cols*sizeof(float);
  }else if (arr.type==CV_64F){
	arr.data.ptr=(uchar*)ptr;
	arr.step=cols*sizeof(double);
  }
  return arr;
}

CV_INLINE
void cvReleaseMat(CvMat ** arr)
{
  if ((*arr)->data.ptr){free((*arr)->data.ptr);(*arr)->data.ptr=0;}
  if (*arr){free(*arr);*arr=0;}
}

CV_INLINE
CvMat * cvCloneMat(CvMat * src)
{
  CvMat * arr=cvCreateMat(src->rows,src->cols,src->type);
  if ((arr->type==CV_8U)||(arr->type==CV_8S)){
	memcpy(arr->data.ptr,src->data.ptr,src->rows*src->step);
	arr->step=src->step;
  }else if (arr->type==CV_16S){
	memcpy(arr->data.ptr,src->data.ptr,src->rows*src->step);
	arr->step=src->step;
  }else if (arr->type==CV_32S){
	memcpy(arr->data.ptr,src->data.ptr,src->rows*src->step);
	arr->step=src->step;
  }else if (arr->type==CV_32F){
	memcpy(arr->data.ptr,src->data.ptr,src->rows*src->step);
	arr->step=src->step;
  }else if (arr->type==CV_64F){
	memcpy(arr->data.ptr,src->data.ptr,src->rows*src->step);
	arr->step=src->step;
  }
  return arr;
}

CV_INLINE
void cvConvert(CvMat * src, CvMat * dst)
{
  int i,nr=src->rows,nc=src->cols;
  int all=nr*nc;
  assert(src->rows==dst->rows);
  assert(src->cols==dst->cols);
  if ((src->type==CV_64F)&&(dst->type==CV_32S)){
	for (i=0;i<all;i++){dst->data.i[i]=round(src->data.db[i]);}
  }else if ((src->type==CV_32F)&&(dst->type==CV_32S)){
	for (i=0;i<all;i++){dst->data.i[i]=round(src->data.fl[i]);}
  }else if ((src->type==CV_64F)&&(dst->type==CV_32F)){
	for (i=0;i<all;i++){dst->data.fl[i]=src->data.db[i];}
  }else if ((src->type==CV_32F)&&(dst->type==CV_64F)){
	for (i=0;i<all;i++){dst->data.db[i]=src->data.fl[i];}
  }else{assert(false);}
}

//-------------------------------------------------------
// interfaces
//-------------------------------------------------------

void cvAddS(CvMat * src, double val, CvMat * dst);
void normalize(float v[3]);
void ncrossprod(float v1[3], float v2[3], float cp[3]);
void triagnormal(float v1[3], float v2[3], float v3[3], float norm[3]);
void cvCalcSurfaceNormal(CvMat * verts, CvMat * faces, CvMat * norms);
void cvLoadSurface(const char * fn, CvMat ** verts, CvMat ** faces);

//-------------------------------------------------------
// implementations
//-------------------------------------------------------

CV_INLINE
void cvAddS(CvMat * src, double val, CvMat * dst)
{
  int i,nr=src->rows,nc=src->cols,type=CV_MAT_TYPE(src->type);
  int all=nr*nc;
  int ival=round(val);
  assert(CV_MAT_TYPE(src->type)==CV_MAT_TYPE(dst->type));
  assert(src->rows==dst->rows);
  assert(src->cols==dst->cols);
  switch(type){
  case CV_8U:{for(i=0;i<all;i++){dst->data.ptr[i]=src->data.ptr[i]+ival;}break;}
  case CV_32S:{for(i=0;i<all;i++){dst->data.i[i]=src->data.i[i]+ival;}break;}
  case CV_32F:{for (i=0;i<all;i++){dst->data.fl[i]=src->data.fl[i]+val;}break;}
  case CV_64F:{for (i=0;i<all;i++){dst->data.db[i]=src->data.db[i]+val;}break;}
  default:{assert(false);}
  }
}

// normalizes v
CV_INLINE
void normalize(float v[3])
{
  float d = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
  if (d == 0){fprintf(stderr, "Zero length vector in normalize\n");}
  else{v[0] /= d; v[1] /= d; v[2] /= d;}
}

// calculates a normalized crossproduct to v1, v2 
CV_INLINE
void ncrossprod(float v1[3], float v2[3], float cp[3])
{
  cp[0] = v1[1]*v2[2] - v1[2]*v2[1];
  cp[1] = v1[2]*v2[0] - v1[0]*v2[2];
  cp[2] = v1[0]*v2[1] - v1[1]*v2[0];
  normalize(cp);
}

// calculates normal to the triangle designated by v1, v2, v3 
CV_INLINE
void triagnormal(float v1[3], float v2[3], float v3[3], float norm[3])
{
  float vec1[3], vec2[3];
  vec1[0] = v3[0] - v1[0];  vec2[0] = v2[0] - v1[0];
  vec1[1] = v3[1] - v1[1];  vec2[1] = v2[1] - v1[1];
  vec1[2] = v3[2] - v1[2];  vec2[2] = v2[2] - v1[2];
  ncrossprod(vec2, vec1, norm);
}

// calculate normal vector for each triangle
#define CV_SHADING_FLAT   0
#define CV_SHADING_SMOOTH 1
void cvCalcSurfaceNormal_flat(CvMat * verts, CvMat * faces, CvMat * norms);
void cvCalcSurfaceNormal_smooth(CvMat * verts, CvMat * faces, CvMat * norms);

CV_INLINE
void cvCalcSurfaceNormal(CvMat * verts, CvMat * faces, CvMat * norms, int mode=0)
{
  typedef void (*CvCalcSurfaceNormalFunc)(CvMat * verts, CvMat * faces, CvMat * norms);
  CvCalcSurfaceNormalFunc func[2]={
	cvCalcSurfaceNormal_flat,
	cvCalcSurfaceNormal_smooth
  };
  assert((mode==CV_SHADING_FLAT)||(mode==CV_SHADING_SMOOTH));
  func[mode](verts,faces,norms);
}

CV_INLINE
void cvCalcSurfaceNormal_flat(CvMat * verts, CvMat * faces, CvMat * norms)
{
  int i;
  int nverts=verts->rows;
  int nfaces=faces->rows;
  assert(verts->cols==3);
  assert(faces->cols==3);
  assert(norms->cols==3);
  assert(faces->rows==norms->rows);
  assert((CV_MAT_TYPE(verts->type)==CV_32F)&&
		 (CV_MAT_TYPE(faces->type)==CV_32S)&&
		 (CV_MAT_TYPE(norms->type)==CV_32F));
  for (i=0;i<nfaces;i++){
	int * fptr=faces->data.i;
	float v1[3]={
	  (verts->data.fl+3*((fptr+3*i)[0]))[0],
	  (verts->data.fl+3*((fptr+3*i)[0]))[1],
	  (verts->data.fl+3*((fptr+3*i)[0]))[2]
	};
	float v2[3]={
	  (verts->data.fl+3*((fptr+3*i)[1]))[0],
	  (verts->data.fl+3*((fptr+3*i)[1]))[1],
	  (verts->data.fl+3*((fptr+3*i)[1]))[2]
	};
	float v3[3]={
	  (verts->data.fl+3*((fptr+3*i)[2]))[0],
	  (verts->data.fl+3*((fptr+3*i)[2]))[1],
	  (verts->data.fl+3*((fptr+3*i)[2]))[2]
	};
	triagnormal(v1,v2,v3,norms->data.fl+3*i);
  }
}

CV_INLINE
void cvCalcSurfaceNormal_smooth(CvMat * verts, CvMat * faces, CvMat * norms)
{
  int i,j,k;
  int nverts=verts->rows;
  int nfaces=faces->rows;
  assert(verts->cols==3);
  assert(faces->cols==3);
  assert(norms->cols==3);
  assert(verts->rows==norms->rows);
  assert((CV_MAT_TYPE(verts->type)==CV_32F)&&
		 (CV_MAT_TYPE(faces->type)==CV_32S)&&
		 (CV_MAT_TYPE(norms->type)==CV_32F));
  memset(norms->data.ptr,0,norms->rows*norms->step);
  float * vptr=verts->data.fl;
  float * nptr=norms->data.fl;
  for (i=0;i<nfaces;i++){
	int * fptr=faces->data.i;
	int idx[3]={(fptr+3*i)[0],(fptr+3*i)[1],(fptr+3*i)[2]};
	float v1[3]={(vptr+3*idx[0])[0],(vptr+3*idx[0])[1],(vptr+3*idx[0])[2]};
	float v2[3]={(vptr+3*idx[1])[0],(vptr+3*idx[1])[1],(vptr+3*idx[1])[2]};
	float v3[3]={(vptr+3*idx[2])[0],(vptr+3*idx[2])[1],(vptr+3*idx[2])[2]};
	float n[3];
	triagnormal(v1,v2,v3,n);
	for (j=0;j<3;j++){for (k=0;k<3;k++){(nptr+3*(idx[j]))[k]+=n[k];}}
  }
  for (i=0;i<nverts;i++){
	normalize(norms->data.fl+3*i);
  }
}

void cvLoadSurface(const char * fn, CvMat ** verts, CvMat ** faces)
{
  static const int MAXLEN=1024;
  if (strcmp(fn+strlen(fn)-4,".obj")){fprintf(stderr,"ERROR: not wavefont .OBJ file\n",fn);}
  FILE * fp = fopen(fn,"rt");
  if (!fp){fprintf(stderr,"ERROR: file '%s' not exist!\n",fn);}
  char line[MAXLEN];

  int nverts=0,nfaces=0;
  while(1)
  {
	fgets(line,MAXLEN,fp);
	if (feof(fp)){break;}
	// fprintf(stderr,"%s",line);
	if (line[0]=='#'){continue;}
	else if (!strncmp("v ",line,2)){nverts++;}
	else if (!strncmp("f ",line,2)){nfaces++;}
  }
  fclose(fp);

  *verts = cvCreateMat(nverts,3,CV_32F);
  *faces = cvCreateMat(nfaces,3,CV_32S);

  int i;
  int viter=0,fiter=0;
  float v[3];
  int f[3];
  fp = fopen(fn,"rt");
  while(1)
  {
	fgets(line,MAXLEN,fp);
	if (feof(fp)){break;}
	// fprintf(stderr,"%s",line);
	if (line[0]=='#'){
	  // ...
	}else if (!strncmp("v ",line,2)){
	  sscanf(line+2,"%f %f %f",&v[0],&v[1],&v[2]);
	  memcpy((*verts)->data.fl+3*viter,v,sizeof(v));
	  viter++;
	}else if (!strncmp("f ",line,2)){
	  sscanf(line+2,"%d %d %d",&f[0],&f[1],&f[2]);
	  for (i=0;i<3;i++){f[i]-=1;}
	  memcpy((*faces)->data.i+3*fiter,f,sizeof(f));
	  fiter++;
	}else{
	  assert(false);
	}
  }
  fclose(fp);
}

#if defined(__cplusplus)

class CvTimer
{
public:
  /// Constructor
  void start()	
  {
#ifdef WIN32
    QueryPerformanceFrequency(&m_CounterFrequency);
    QueryPerformanceCounter(&m_LastCount);
#else
    gettimeofday(&m_LastCount, 0);
#endif
  }
	
  /// Resets timer (difference) to zero
  inline void restart() 
  {
#ifdef WIN32
    QueryPerformanceCounter(&m_LastCount);
#else
    gettimeofday(&m_LastCount, 0);
#endif
  }					
	
  /// Get elapsed time in milliseconds
  float elapsed()
  {
    // Get the current count
#ifdef WIN32
    LARGE_INTEGER lCurrent;
    QueryPerformanceCounter(&lCurrent);

    return float((lCurrent.QuadPart - m_LastCount.QuadPart) /
                 double(m_CounterFrequency.QuadPart))*1000.0f;
#else
    timeval lcurrent;
    gettimeofday(&lcurrent, 0);
    float fSeconds = float(lcurrent.tv_sec - m_LastCount.tv_sec)*1000.0f;
    float fFraction =
        float(lcurrent.tv_usec - m_LastCount.tv_usec) * 0.001f;
    return fSeconds + fFraction;
#endif
  }	
	
 protected:
#ifdef WIN32
  LARGE_INTEGER m_CounterFrequency;
  LARGE_INTEGER m_LastCount;
#else
  timeval m_LastCount;
#endif
};

#endif // defined(__cplusplus)

#endif // __COMP_VIS_H__
