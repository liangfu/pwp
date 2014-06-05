/**
 * @file   cvfacedetector.cpp
 * @author Liangfu Chen <liangfu.chen@cn.fix8.com>
 * @date   Mon Jul  8 15:55:57 2013
 * 
 * @brief  
 * 
 * 
 */
#include "cvfacedetector.h"
#include "cvimgwarp.h"

CvMat * get_haarclassifier_face25();
// int icvPrintClassifier(const char * fn,
//                        CvAdaBoostClassifier classifier,
//                        IcvHaarFeatureSet features,
//                        const int iter);

// CV_INLINE
// int icvIsFace(CvMat * imgIntegral, CvRect roi,
//               CvWeakClassifier k,
//               IcvHaarFeature f)
// {
//   const int winsz = 25; assert(winsz==25);
//   float scale = float(roi.width)/float(winsz);
//   int step = imgIntegral->step/sizeof(int);
//   for (int i=0;i<3;i++){
//     int xx=cvRound(float(f.rect[i].roi.x)*scale);
//     int yy=cvRound(float(f.rect[i].roi.y)*scale);
//     int ww=cvRound(float(f.rect[i].roi.width )*scale);
//     int hh=cvRound(float(f.rect[i].roi.height)*scale);
//     f.rect[i].p0 = xx+roi.x+(yy+roi.y)*step;
//     f.rect[i].p1 = xx+ww+roi.x+(yy+roi.y)*step;
//     f.rect[i].p2 = xx+roi.x+(yy+hh+roi.y)*step;
//     f.rect[i].p3 = xx+ww+roi.x+(yy+hh+roi.y)*step;
//   }
//   int fval = icvCalcHaarFeature(imgIntegral->data.i,f);
//   return ((fval*k.parity)<(k.threshold*pow(scale,2)*k.parity));
// }

CV_INLINE
int icvIsTarget(CvMat * imgIntegral, CvRect roi, float * h, const int tsize)
{
  double scale = float(roi.width)/float(tsize);
  int i,step = imgIntegral->step/sizeof(int);
  int xx,yy,ww,hh,wt[3],p0[3],p1[3],p2[3],p3[3];
  double threshold=h[0];
  double polarity =h[1];
  for (i=0;i<3;i++){
    xx=cvRound((h+2+5*i)[0]*scale);
    yy=cvRound((h+2+5*i)[1]*scale);
    ww=cvRound((h+2+5*i)[2]*scale);
    hh=cvRound((h+2+5*i)[3]*scale);
    wt[i]=cvRound((h+2+5*i)[4]);
    if (i==2){if(wt[2]==0){break;}}
    p0[i]=xx+roi.x+(yy+roi.y)*step;
    p1[i]=xx+ww+roi.x+(yy+roi.y)*step;
    p2[i]=xx+roi.x+(yy+hh+roi.y)*step;
    p3[i]=xx+ww+roi.x+(yy+hh+roi.y)*step;
  }
  int * integral_data=imgIntegral->data.i;
  double fval;
  if (wt[2]==0){
    fval =
        (integral_data[p0[0]]-integral_data[p1[0]]-
         integral_data[p2[0]]+integral_data[p3[0]])*wt[0]+
        (integral_data[p0[1]]-integral_data[p1[1]]-
         integral_data[p2[1]]+integral_data[p3[1]])*wt[1];
  }else{
    fval =
        (integral_data[p0[0]]-integral_data[p1[0]]-
         integral_data[p2[0]]+integral_data[p3[0]])*wt[0]+
        (integral_data[p0[1]]-integral_data[p1[1]]-
         integral_data[p2[1]]+integral_data[p3[1]])*wt[1]+
        (integral_data[p0[2]]-integral_data[p1[2]]-
         integral_data[p2[2]]+integral_data[p3[2]])*wt[2];
  }

  return ((fval*polarity)<(threshold*pow(scale,2)*polarity));
}

int CvFaceDetector::detect(CvMat * img, CvRect roi[])
{
  // assert(m_classifier);
  // assert(m_features);
  int nr=img->rows,nc=img->cols;
  CvMat * imgIntegral=cvCreateMat(nr+1,nc+1,CV_32S);
  cvIntegral(img,imgIntegral);
  int i,j,k,cc=0,maxcc=800;

  // int winsz = m_features->winsize.width; assert(winsz==25);
  // for (winsz=25;winsz<float(MIN(nr,nc))*.8;winsz=float(winsz)*1.2){
  // for (i=0;i<nr-winsz;i=cvRound(float(i)+2.*float(winsz)/25.)){
  // for (j=0;j<nc-winsz;j=cvRound(float(j)+2.*float(winsz)/25.)){
  // for (k=0;k<m_classifier->count;k++){
  //   if (!icvIsFace(imgIntegral,cvRect(j,i,winsz,winsz),
  //                  m_classifier->h[k],m_features->feature[k]))
  //   {break;}
  //   if (k==m_classifier->count-1){roi[cc++]=cvRect(j,i,winsz,winsz);}
  // }
  // if(cc>=maxcc){break;}
  // }
  // if(cc>=maxcc){break;}
  // }
  // }

  CvMat * haarclassifier_face25 = get_haarclassifier_face25();
  int winsz,tsize=25;
  float h[17];
  int num_classifiers=haarclassifier_face25->rows;
  for (winsz=tsize;winsz<float(MIN(nr,nc))*.8;winsz=float(winsz)*1.2){
  for (i=0;i<nr-winsz;i=cvRound(float(i)+2.*float(winsz)/float(tsize))){
  for (j=0;j<nc-winsz;j=cvRound(float(j)+2.*float(winsz)/float(tsize))){
  for (k=0;k<num_classifiers;k++){
    // extract classifier
    memcpy(h,haarclassifier_face25->data.ptr+sizeof(h)*k,sizeof(h));
    // examin the target
    if (!icvIsTarget(imgIntegral,cvRect(j,i,winsz,winsz),h,tsize)){break;}
    // not rejected yet, hah
    if (k==num_classifiers-1){roi[cc++]=cvRect(j,i,winsz,winsz);}
  }
  if(cc>=maxcc){break;}
  }
  if(cc>=maxcc){break;}
  }
  }
  
  cvReleaseMat(&imgIntegral);

  // {
  //   for (k=0;k<m_classifier->count;k++){
  //     fprintf(stderr,"%.1f,%d.0, %d.0,%d.,%d.,%d.,%d., "
  //             "%d.,%d.,%d.,%d.,%d., %d.,%d.,%d.,%d.,%d., \n",
  //             m_classifier->h[k].threshold,m_classifier->h[k].parity,
  //             m_features->feature[k].rect[0].roi.x,
  //             m_features->feature[k].rect[0].roi.y,
  //             m_features->feature[k].rect[0].roi.width,
  //             m_features->feature[k].rect[0].roi.height,
  //             m_features->feature[k].rect[0].wt,
  //             m_features->feature[k].rect[1].roi.x,
  //             m_features->feature[k].rect[1].roi.y,
  //             m_features->feature[k].rect[1].roi.width,
  //             m_features->feature[k].rect[1].roi.height,
  //             m_features->feature[k].rect[1].wt,
  //             m_features->feature[k].rect[2].roi.x,
  //             m_features->feature[k].rect[2].roi.y,
  //             m_features->feature[k].rect[2].roi.width,
  //             m_features->feature[k].rect[2].roi.height,
  //             m_features->feature[k].rect[2].wt);
  //   }exit(0);
  // }
  
  return cc;
}

// int CvFaceDetector::train(CvTrainSample * poslist, int npos,
//                           CvTrainSample * neglist, int nneg)
// {
//   IcvHaarFeatureSet * features = icvCreateHaarFeatureSet(25);
//   extractSamples(poslist,npos,neglist,nneg);
//   calcIntegrals();

//   static uchar face_data[576];
//   static int integral_data[625];
//   static CvMat face = cvMat(24,24,CV_8U,face_data);
//   static CvMat integral = cvMat(25,25,CV_32S,integral_data);
//   const int facedatasz = sizeof(face_data);
//   const int integralsz = sizeof(integral_data);
//   int i,j,iter,maxiter = 30;
//   const int numsamples = 40;
//   // CvMat * weights = cvCreateMat(features->count,1,CV_64F);
//   // CvMat * weights = cvCreateMat(numsamples,1,CV_64F);
  
//   CvAdaBoostClassifier classifier;
//   classifier.count = features->count;
//   classifier.h = new CvWeakClassifier[features->count];
//   for (i=0;i<features->count;i++){
//     classifier.h[i].featureid=i;
//     classifier.h[i].weight=1./double(features->count);
//     // weights->data.db[i]=1./double(features->count);
//   }

//   for (iter=0;iter<maxiter;iter++){
//     CvMat * epsilon = cvCreateMat(1,features->count,CV_64F);

//     // normalize weights
//     {
//       double invwtsum,wtsum = 0;//1./cvSum(weights).val[0];
//       for (i=0;i<features->count;i++){ wtsum+=classifier.h[i].weight; }
//       invwtsum = 1./wtsum;
//       // for (i=0;i<weights->rows;i++){ weights->data.db[i] *= invwtsum; }
//       for (i=0;i<features->count;i++){ classifier.h[i].weight *= invwtsum; }
//     }
    
//     // compute weight for each feature
//     for (i=0;i<features->count;i++){
//       CvMat * posRes = cvCreateMat(numsamples,1,CV_32S);
//       CvMat * negRes = cvCreateMat(numsamples,1,CV_32S);
//       double minval=0xffffff,maxval=-0xffffff;
//       double wt = classifier.h[i].weight;
//       double epsval = 0;
      
//       // for (j=0;j<m_positive->rows;j++){
//       for (j=0;j<posRes->rows;j++){
//         memcpy(integral_data,m_posIntegral->data.ptr+j*integralsz,
//                integralsz);
//         int posresval =
//             icvCalcHaarFeature(integral_data,features->feature[i]);
//         posRes->data.i[j] = posresval;
//         minval = MIN(posresval,minval);
//         maxval = MAX(posresval,maxval);
//       }
//       for (j=0;j<negRes->rows;j++){
//         memcpy(integral_data,m_negIntegral->data.ptr+j*integralsz,
//                integralsz);
//         negRes->data.i[j] =
//             icvCalcHaarFeature(integral_data,features->feature[i]);
//       }

//       double posavg = cvAvg(posRes).val[0];
//       double negavg = cvAvg(negRes).val[0];
//       if (posavg<negavg){
//         classifier.h[i].threshold=maxval;classifier.h[i].parity=1;
//       }else{
//         classifier.h[i].threshold=minval;classifier.h[i].parity=-1;
//       }

//       double threshold = classifier.h[i].threshold;
//       double parity = classifier.h[i].parity;
//       epsval=0;
//       for (j=0;j<posRes->rows;j++){
//         epsval += wt*//weights->data.db[j]*
//             fabs((((parity*posRes->data.i[j])<(parity*threshold))?1:0)-1);
//       }
//       for (j=0;j<negRes->rows;j++){
//         epsval += wt*//weights->data.db[j]*
//             fabs((((parity*negRes->data.i[j])<(parity*threshold))?1:0)-0);
//       }
//       epsilon->data.db[i]=epsval;
      
//       if (i%1000==1){fprintf(stderr, "-");}
//       cvReleaseMat(&posRes);
//       cvReleaseMat(&negRes);
//     }

//     double minval=0xffffff,maxval=-0xffffff; CvPoint minloc,maxloc;
//     //cvMinMaxLoc(epsilon,&minval,&maxval,&minloc,&maxloc);
//     for (i=iter;i<features->count;i++){
//       double epsval = epsilon->data.db[i];
//       if (epsval<minval){minval=epsval;minloc.x=i;minloc.y=0;}
//       if (epsval>maxval){maxval=epsval;maxloc.x=i;maxloc.y=0;}
//     }
//     swap(&classifier.h[iter],&classifier.h[minloc.x],
//          sizeof(CvWeakClassifier));
//     swap(&features->feature[iter],&features->feature[minloc.x],
//          sizeof(IcvHaarFeature));
//     fprintf(stderr, "minloc: %d(%f) at %dth iteration\n",
//             minloc.x,minval,iter);
//     {
//       //cvSet(&face,cvScalar(128));
//       memcpy(face_data,m_positive->data.ptr,facedatasz);
//       CvMat subface0_stub;
//       CvMat * subface0 =
//           cvGetSubRect(&face,&subface0_stub,
//             features->feature[iter].rect[0].roi);
//       cvSet(subface0,cvScalar(0));
//       CvMat subface1_stub;
//       CvMat * subface1 =
//           cvGetSubRect(&face,&subface1_stub,
//             features->feature[iter].rect[1].roi);
//       cvSet(subface1,cvScalar(255));
//     }
//     //cvShowImage("Test",&face); CV_WAIT2(10);

//     for (i=0;i<features->count;i++){
//       classifier.h[i].weight *=
//           pow(epsilon->data.db[i]/(1.-epsilon->data.db[i]),
//               1.-((i<=iter)?0:1));
//     }

//     // fprintf(stderr,"\n");
//     cvReleaseMat(&epsilon);
//   }
//   // cvReleaseMat(&weights);

//   // {
//   //   for (k=0;k<m_classifier->count;k++){
//   //     fprintf(stderr,"%.1f,%d.0, %d.0,%d.,%d.,%d.,%d., "
//   //             "%d.,%d.,%d.,%d.,%d., %d.,%d.,%d.,%d.,%d., \n",
//   //             m_classifier->h[k].threshold,m_classifier->h[k].parity,
//   //             m_features->feature[k].rect[0].roi.x,
//   //             m_features->feature[k].rect[0].roi.y,
//   //             m_features->feature[k].rect[0].roi.width,
//   //             m_features->feature[k].rect[0].roi.height,
//   //             m_features->feature[k].rect[0].wt,
//   //             m_features->feature[k].rect[1].roi.x,
//   //             m_features->feature[k].rect[1].roi.y,
//   //             m_features->feature[k].rect[1].roi.width,
//   //             m_features->feature[k].rect[1].roi.height,
//   //             m_features->feature[k].rect[1].wt,
//   //             m_features->feature[k].rect[2].roi.x,
//   //             m_features->feature[k].rect[2].roi.y,
//   //             m_features->feature[k].rect[2].roi.width,
//   //             m_features->feature[k].rect[2].roi.height,
//   //             m_features->feature[k].rect[2].wt);
//   //   }exit(0);
//   // }

//   // icvPrintClassifier("../src/cvfacedetector_data.cpp",
//   //                    classifier,*features,iter);
  
//   icvReleaseHaarFeatureSet(&features);
// }
    
// int CvFaceDetector::extractSamples(CvTrainSample * poslist, int npos,
//                                    CvTrainSample * neglist, int nneg)
// {
//   int i;
//   static uchar face_data[576];
//   const int facedatasz = sizeof(face_data);

//   // collect positive training samples
// #if 0
//   {
//   CvMat * pos = cvCreateMat(npos*2,facedatasz,CV_8U);

//   fprintf(stderr, "INFO: collecting positive samples!\n");
//   int poscount = 0;
//   for (i=0;i<npos;i++){
//     IplImage * raw = cvLoadImage(poslist[i].fn,0);
//     CvMat img_stub;
//     CvMat * img = cvGetMat(raw, &img_stub);
//     CvMat face = cvMat(24,24,CV_8U,face_data);
//     CvPoint2D32f center = poslist[i].box.center;
//     float xscale = poslist[i].box.size.width/24.;
//     float yscale = poslist[i].box.size.height/24.;
//     float radius = -poslist[i].box.angle*CV_PI/180.;
// #if 0
//     float warp_p_data[4] = {
//       xscale*cos(radius),yscale*sin(radius),
//       center.x-12.*xscale*cos(radius)+12.*yscale*sin(radius),
//       center.y-12.*xscale*sin(radius)-12.*yscale*cos(radius)
//     };
//     CvMat warp_p = cvMat(4,1,CV_32F,warp_p_data);
//     icvWarp(img,&face,&warp_p);
// #elif 1
//     float map_matrix_data[6]={
//       xscale*cos(radius),-yscale*sin(radius),
//       center.x,
//       xscale*sin(radius),yscale*cos(radius),
//       center.y
//     };
//     CvMat map_matrix = cvMat(2,3,CV_32F,map_matrix_data);
//     cvGetQuadrangleSubPix(img,&face,&map_matrix);
// #else
//     float map_matrix_data[6]={
//       xscale*cos(radius),-yscale*sin(radius),
//       center.x-12.*xscale*cos(radius)+12.*yscale*sin(radius),
//       xscale*sin(radius),yscale*cos(radius),
//       center.y-12.*xscale*sin(radius)-12.*yscale*cos(radius)
//     };
//     CvMat map_matrix = cvMat(2,3,CV_32F,map_matrix_data);
//     cvWarpAffine(img,&face,&map_matrix,
//                  CV_INTER_CUBIC+CV_WARP_FILL_OUTLIERS+
//                  CV_WARP_INVERSE_MAP,cvScalarAll(0));
// #endif
//     float avgval = cvAvg(&face).val[0];
//     // fprintf(stderr, "id: %d,avg: %f\n", i,avgval);
//     if (avgval>35) {
//       memcpy(pos->data.ptr+poscount*facedatasz,face_data,facedatasz);
//       // fprintf(stderr, "file: %s\n", poslist[i].fn);
//       // cvShowImage("Test",&face); CV_WAIT();
//       cvFlip(&face,&face,1);
//       memcpy(pos->data.ptr+poscount*facedatasz+facedatasz,face_data,
//              facedatasz);
//       poscount += 2;
//       if (i%100==1) { fprintf(stderr, "-"); }
//     }
//     cvReleaseImage(&raw);
//   }
//   fprintf(stderr, "\n");

//   assert(!m_positive);
//   m_positive = cvCreateMat(poscount,facedatasz,CV_8U);
//   memcpy(m_positive->data.ptr,pos->data.ptr,poscount*facedatasz);

//   // write to binary file
//   {
//     FILE * fp = fopen("../data/face24x24.bin","w");
//     fwrite(&m_positive->rows,4,1,fp);
//     fwrite(&m_positive->cols,4,1,fp);
//     fwrite(m_positive->data.ptr,1,poscount*facedatasz,fp);
//     fclose(fp);
//   }
  
//   cvReleaseMat(&pos);
//   }
// #else
//   // read directly from saved binary file
//   {
//     int nr,nc;
//     FILE * fp = fopen("../data/face24x24.bin","r");
//     fread(&nr,4,1,fp);
//     fread(&nc,4,1,fp);
//     assert(!m_positive);
//     assert(facedatasz==nc);
//     m_positive = cvCreateMat(nr,nc,CV_8U);
//     fread(m_positive->data.ptr,1,nr*nc,fp);
//     fclose(fp);
//   }
// #endif
//   // finish collecting positive training samples

//   // start to collect negative training samples
// #if 0
//   {
//     assert(m_positive);
//     int negcount = m_positive->rows;
//     m_negative = cvCreateMat(negcount,facedatasz,CV_8U);
//     CvRNG rng = cvRNG();
//     CvMat * pts = cvCreateMat(negcount,1,CV_32S);
//     CvMat * sizes = cvCreateMat(negcount,1,CV_32S);
//     cvRandArr(&rng,pts,CV_RAND_UNI,cvScalar(0),cvScalar(nneg));
//     cvRandArr(&rng,sizes,CV_RAND_UNI,cvScalar(30),cvScalar(80));

//     fprintf(stderr, "INFO: collecting negative samples!\n");
//     for (i=0;i<negcount;i++){
//       IplImage * raw = cvLoadImage(neglist[pts->data.i[i]].fn,0);
//       CvMat img_stub;
//       CvMat * img = cvGetMat(raw,&img_stub);
//       int nr=img->rows,nc=img->cols;
//       int xloc = cvFloor(cvRandReal(&rng)*(nc-90));
//       int yloc = cvFloor(cvRandReal(&rng)*(nr-90));
//       int winsize = sizes->data.i[i]; 
//       // winsize = MAX(winsize,nc-xloc-1);
//       // winsize = MAX(winsize,nr-yloc-1);
//       assert(winsize>=24);
//       CvMat face = cvMat(24,24,CV_8U,face_data);
//       float warp_p_data[3]={float(winsize)/24.,xloc,yloc};
//       CvMat warp_p = cvMat(3,1,CV_32F,warp_p_data);
//       icvWarp(img,&face,&warp_p);
//       memcpy(m_negative->data.ptr+i*facedatasz,face_data,facedatasz);
//       if (i%100==1) { fprintf(stderr, "-"); }
//       //cvShowImage("Test",&face); CV_WAIT();
//       cvReleaseImage(&raw);
//     }
//     fprintf(stderr, "\n");

//     cvReleaseMat(&pts);
//     cvReleaseMat(&sizes);

//     // write to binary file
//     {
//       FILE * fp = fopen("../data/nonface24x24.bin","w");
//       fwrite(&m_negative->rows,4,1,fp);
//       fwrite(&m_negative->cols,4,1,fp);
//       fwrite(m_negative->data.ptr,1,negcount*facedatasz,fp);
//       fclose(fp);
//     }
//   }
// #else
//   {
//     int nr,nc;
//     FILE * fp = fopen("../data/nonface24x24.bin","r");
//     fread(&nr,4,1,fp);
//     fread(&nc,4,1,fp);
//     assert(!m_negative);
//     assert(facedatasz==nc);
//     m_negative = cvCreateMat(nr,nc,CV_8U);
//     fread(m_negative->data.ptr,1,nr*nc,fp);
//     fclose(fp);
//   }
// #endif
  
//   fprintf(stderr, "INFO: %d positive samples!\n", m_positive->rows);
//   fprintf(stderr, "INFO: %d negative samples!\n", m_negative->rows);
//   // for (i=0;i<m_positive->rows;i++){
//   //   CvMat face = cvMat(24,24,CV_8U,face_data);
//   //   memcpy(face_data,m_positive->data.ptr+facedatasz*i,facedatasz);
//   //   cvShowImage("Test",&face); CV_WAIT();
//   // }
//   // for (i=0;i<m_negative->rows;i++){
//   //   CvMat face = cvMat(24,24,CV_8U,face_data);
//   //   memcpy(face_data,m_negative->data.ptr+facedatasz*i,facedatasz);
//   //   cvShowImage("Test",&face); CV_WAIT();
//   // }
// }

// int CvFaceDetector::calcIntegrals()
// {
//   int i;
//   static uchar face_data[576];
//   static int integral_data[625];
//   static CvMat face = cvMat(24,24,CV_8U,face_data);
//   static CvMat integral = cvMat(25,25,CV_32S,integral_data);
//   const int facedatasz = sizeof(face_data);
//   const int integralsz = sizeof(integral_data);
//   assert(integralsz==2500);
//   m_posIntegral = cvCreateMat(m_positive->rows,integralsz,CV_32S);
//   m_negIntegral = cvCreateMat(m_negative->rows,integralsz,CV_32S);

//   for (i=0;i<m_positive->rows;i++)
//   {
//     memcpy(face_data,m_positive->data.ptr+i*facedatasz,facedatasz);
//     cvIntegral(&face,&integral);
//     memcpy(m_posIntegral->data.ptr+i*integralsz,integral_data,integralsz);
//   }
//   for (i=0;i<m_negative->rows;i++)
//   {
//     memcpy(face_data,m_negative->data.ptr+i*facedatasz,facedatasz);
//     cvIntegral(&face,&integral);
//     memcpy(m_negIntegral->data.ptr+i*integralsz,integral_data,integralsz);
//   }
// }

int icvHaarFeatureExtract(int * iptr, int step, int * fptr)
{
  static struct {int x0,y0,dx0,dy0,wt0;
                 int x1,y1,dx1,dy1,wt1;
                 int x2,y2,dx2,dy2,wt2;} t;
  memcpy(&t,fptr,sizeof(t));
  return (iptr[t.y0*step+t.x0]-
          iptr[t.y0*step+t.x0+t.dx0]-
          iptr[(t.y0+t.dy0)*step+t.x0]+
          iptr[(t.y0+t.dy0)*step+t.x0+t.dx0])*t.wt0+
         (iptr[t.y1*step+t.x1]-
          iptr[t.y1*step+t.x1+t.dx1]-
          iptr[(t.y1+t.dy1)*step+t.x1]+
          iptr[(t.y1+t.dy1)*step+t.x1+t.dx1])*t.wt1+
         (iptr[t.y2*step+t.x2]-
          iptr[t.y2*step+t.x2+t.dx2]-
          iptr[(t.y2+t.dy2)*step+t.x2]+
          iptr[(t.y2+t.dy2)*step+t.x2+t.dx2])*t.wt2;
}

inline void icvHaar(int * feature,
                    int x0, int y0, int dx0, int dy0, float wt0,
                    int x1, int y1, int dx1, int dy1, float wt1,
                    int x2=0, int y2=0, int dx2=0, int dy2=0, float wt2=0)
{
  feature[0]=x0;feature[1]=y0;feature[2]=dx0;feature[3]=dy0;feature[4]=wt0;
  feature[5]=x0;feature[6]=y0;feature[7]=dx0;feature[8]=dy0;feature[9]=wt0;
  feature[10]=x0;feature[11]=y0;feature[12]=dx0;feature[13]=dy0;
  feature[14]=wt0;
}

CvMat * icvHaarFeatureInitialize(int winsize)
{
  int shiftbits=8;
  typedef struct {int d[15];} feat;
  int tmp[15];
  assert(sizeof(feat)==sizeof(tmp));
  int x,y,dx,dy,count=0,pixelstep=2;
  feat * buff = (feat*)malloc(sizeof(feat)*(1<<shiftbits));

  for (x=0;x<winsize;x+=pixelstep){
  for (y=0;y<winsize;y+=pixelstep){
  for (dx=2;dx<winsize;dx+=pixelstep){
  for (dy=2;dy<winsize;dy+=pixelstep){

  // memory re-allocation for additional feature arrays
  if ((1<<shiftbits)-10<count){
    buff = (feat*)realloc(buff,sizeof(feat)*(1<<(++shiftbits)));
    if (!buff) {
      fprintf(stderr, "ERROR: memory allocation failure!\n");exit(1);
    }
  }
          
if ((x+dx*2<winsize)&&(y+dy<winsize))
  icvHaar((int*)&buff[count++],x,y,dx*2,dy,-1,x+dx,y,dx,dy,2);
if ((x+dx*2<winsize)&&(y+dy<winsize))
  icvHaar((int*)&buff[count++],y,x,dy,dx*2,-1,y,x+dx,dy,dx,2);
if ((x+dx*3<winsize)&&(y+dy<winsize))
  icvHaar((int*)&buff[count++],x,y,dx*3,dy,-1,x+dx,y,dx,dy,3);
if ((x+dx*3<winsize)&&(y+dy<winsize))
  icvHaar((int*)&buff[count++],y,x,dy,dx*3,-1,y,x+dx,dy,dx,3);
if ((x+dx*4<winsize)&&(y+dy<winsize))
  icvHaar((int*)&buff[count++],x,y,dx*4,dy,-1,x+dx,y,dx*2,dy,2);
if ((x+dx*4<winsize)&&(y+dy<winsize))
  icvHaar((int*)&buff[count++],y,x,dy,dx*4,-1,y,x+dx,dy,dx*2,2);
if ((x+dx*2<winsize)&&(y+dy*2<winsize))
  icvHaar((int*)&buff[count++],
          x,y,dx*2,dy*2,-1,x,y,dx,dy,2,x+dx,y+dy,dx,dy,2);

  }
  }
  }
  }

  CvMat * features = cvCreateMat(count,15,CV_32S);
  memcpy(features->data.i,buff,sizeof(feat)*count);

  return features;
}

// IcvHaarFeatureSet * icvCreateHaarFeatureSet(const int wsz)
// {
//   assert(wsz==25);
//   IcvHaarFeatureSet * features = new IcvHaarFeatureSet;
//   int log2feat=8;
//   IcvHaarFeature * buff =
//       (IcvHaarFeature*)malloc(sizeof(IcvHaarFeature)*(1<<log2feat));
//   int x,y,dx,dy,count=0,pixelstep=2;

//   for (x=0;x<wsz;x+=pixelstep){
//   for (y=0;y<wsz;y+=pixelstep){
//   for (dx=2;dx<wsz;dx+=pixelstep){
//   for (dy=2;dy<wsz;dy+=pixelstep){

//   if ((1<<log2feat)-10<count){
//     buff = (IcvHaarFeature*)
//         realloc(buff,sizeof(IcvHaarFeature)*(1<<(++log2feat)));
//     if (!buff) {
//       fprintf(stderr, "ERROR: memory allocation failure!\n");
//       exit(1);
//     }
//   }
          
// if ((x+dx*2<wsz)&&(y+dy<wsz))
//   buff[count++]=icvHaarFeature("x2",wsz,x,y,dx*2,dy,-1,x+dx,y,dx,dy,2);
// if ((x+dx*2<wsz)&&(y+dy<wsz))
//   buff[count++]=icvHaarFeature("y2",wsz,y,x,dy,dx*2,-1,y,x+dx,dy,dx,2);
// if ((x+dx*3<wsz)&&(y+dy<wsz))
//   buff[count++]=icvHaarFeature("x3",wsz,x,y,dx*3,dy,-1,x+dx,y,dx,dy,3);
// if ((x+dx*3<wsz)&&(y+dy<wsz))
//   buff[count++]=icvHaarFeature("y3",wsz,y,x,dy,dx*3,-1,y,x+dx,dy,dx,3);
// if ((x+dx*4<wsz)&&(y+dy<wsz))
//   buff[count++]=icvHaarFeature("x4",wsz,x,y,dx*4,dy,-1,x+dx,y,dx*2,dy,2);
// if ((x+dx*4<wsz)&&(y+dy<wsz))
//   buff[count++]=icvHaarFeature("y4",wsz,y,x,dy,dx*4,-1,y,x+dx,dy,dx*2,2);
// if ((x+dx*2<wsz)&&(y+dy*2<wsz))
//   buff[count++]=
//       icvHaarFeature("x2y2",wsz,
//                      x,y,dx*2,dy*2,-1,x,y,dx,dy,2,x+dx,y+dy,dx,dy,2);

//   }
//   }
//   }
//   }

//   fprintf(stderr, "count: %d\n", count);

//   assert(wsz==25);
//   features->winsize=cvSize(wsz,wsz);
//   features->count   = count;
//   features->feature = new IcvHaarFeature[count];
//   memcpy(features->feature,buff,sizeof(IcvHaarFeature)*count);
//   free(buff);
  
//   return features;
// }

// void icvReleaseHaarFeatureSet(IcvHaarFeatureSet ** features)
// {
//   delete [] (*features)->feature;
//   delete (*features);
// }

// int icvPrintClassifier(const char * fn,
//                        CvAdaBoostClassifier classifier,
//                        IcvHaarFeatureSet features,
//                        const int iter)
// {
//   int i,j,cc=0;
//   assert(classifier.h!=NULL);
//   FILE * fp = fopen(fn,"w");
//   fprintf(fp,
// "/**\n"
// " * @file   cvfacedetector_data.cpp\n"
// " * @author Liangfu Chen <liangfu.chen@cn.fix8.com>\n"
// " * @date   Fri Jul 12 15:38:59 2013\n"
// " * \n"
// " * @brief  \n"
// " * \n"
// " * \n"
// " */\n"
// "#include \"cvfacedetector.h\" \n"
// "\n"
// "int CvFaceDetector::initialize()\n"
// "{\n"
// "  assert(!m_classifier);\n"
// "  m_classifier = new CvAdaBoostClassifier;\n"
// "  m_classifier->count = %d;\n"
// "  m_classifier->h = new CvWeakClassifier[m_classifier->count];\n"
// "  m_features = new IcvHaarFeatureSet;\n"
// "  m_features->winsize = cvSize(%d,%d);\n"
// "  m_features->count = %d;\n"
// "  m_features->feature = new IcvHaarFeature[m_features->count];\n"
// "\n"
// "  uchar classifierdata[%d]={\n    ",
//           iter,
//           features.winsize.width,
//           features.winsize.height,
//           iter,iter*sizeof(CvWeakClassifier));
//   for (i=0,cc=0;i<iter;i++){
//     for (j=0;j<sizeof(CvWeakClassifier);j++){
//       fprintf(fp,"0x%02x,",(int)((uchar*)&classifier.h[i])[j]);
//       if (++cc%10==0){fprintf(fp,"\n    ");}
//     }
//   }
//   fprintf(fp,
// "\n  };\n"
// "\n"
// "  uchar featuresdata[%d]={\n    ",iter*sizeof(IcvHaarFeature));
//   for (i=0,cc=0;i<iter;i++){
//     for (j=0;j<sizeof(IcvHaarFeature);j++){
//       fprintf(fp,"0x%02x,",(int)((uchar*)&features.feature[i])[j]);
//       if (++cc%10==0){fprintf(fp,"\n    ");}
//     }
//   }
//   fprintf(fp,
// "\n  };\n"
// "\n"
// "  memcpy(&m_classifier->h[0],classifierdata,\n"
// "         sizeof(classifierdata));\n"
// "  memcpy(&m_features->feature[0],featuresdata,\n"
// "         sizeof(featuresdata));\n"
// "}\n");
// }

CvMat * get_haarclassifier_face25()
{
  static float haarclassifier_face25_data[510]={
    -361.0,1.0, 4.0,0.,14.,8.,-1., 4.,2.,14.,4.,2., 0.,0.,0.,0.,0., 
    -361.0,1.0, 6.0,0.,14.,8.,-1., 6.,2.,14.,4.,2., 0.,0.,0.,0.,0., 
    1171.0,-1.0, 16.0,2.,6.,18.,-1., 16.,8.,6.,6.,3., 0.,0.,0.,0.,0., 
    -356.0,1.0, 2.0,0.,18.,8.,-1., 2.,2.,18.,4.,2., 0.,0.,0.,0.,0., 
    -425.0,1.0, 6.0,0.,12.,8.,-1., 6.,2.,12.,4.,2., 0.,0.,0.,0.,0., 
    178.0,-1.0, 18.0,4.,2.,16.,-1., 18.,8.,2.,8.,2., 0.,0.,0.,0.,0., 
    -187.0,1.0, 8.0,0.,10.,8.,-1., 8.,2.,10.,4.,2., 0.,0.,0.,0.,0., 
    -204.0,1.0, 8.0,0.,12.,8.,-1., 8.,2.,12.,4.,2., 0.,0.,0.,0.,0., 
    1568.0,-1.0, 16.0,0.,6.,24.,-1., 16.,8.,6.,8.,3., 0.,0.,0.,0.,0., 
    704.0,-1.0, 2.0,2.,6.,12.,-1., 2.,8.,6.,6.,2., 0.,0.,0.,0.,0., 
    184.0,-1.0, 4.0,2.,2.,12.,-1., 4.,8.,2.,6.,2., 0.,0.,0.,0.,0., 
    1241.0,-1.0, 14.0,2.,10.,18.,-1., 14.,8.,10.,6.,3., 0.,0.,0.,0.,0., 
    1272.0,-1.0, 16.0,2.,8.,18.,-1., 16.,8.,8.,6.,3., 0.,0.,0.,0.,0., 
    625.0,-1.0, 18.0,2.,4.,18.,-1., 18.,8.,4.,6.,3., 0.,0.,0.,0.,0., 
    477.0,-1.0, 0.0,4.,6.,12.,-1., 0.,8.,6.,4.,3., 0.,0.,0.,0.,0., 
    737.0,-1.0, 0.0,4.,8.,12.,-1., 0.,8.,8.,4.,3., 0.,0.,0.,0.,0., 
    -485.0,1.0, 4.0,0.,8.,16.,-1., 4.,0.,4.,8.,2., 8.,8.,4.,8.,2., 
    213.0,-1.0, 2.0,4.,4.,8.,-1., 2.,8.,4.,4.,2., 0.,0.,0.,0.,0., 
    295.0,-1.0, 16.0,4.,6.,8.,-1., 16.,8.,6.,4.,2., 0.,0.,0.,0.,0., 
    737.0,-1.0, 16.0,4.,8.,12.,-1., 16.,8.,8.,4.,3., 0.,0.,0.,0.,0., 
    213.0,-1.0, 18.0,4.,4.,8.,-1., 18.,8.,4.,4.,2., 0.,0.,0.,0.,0., 
    -257.0,1.0, 2.0,0.,16.,8.,-1., 2.,2.,16.,4.,2., 0.,0.,0.,0.,0., 
    -367.0,1.0, 2.0,0.,20.,8.,-1., 2.,2.,20.,4.,2., 0.,0.,0.,0.,0., 
    1568.0,-1.0, 2.0,0.,6.,24.,-1., 2.,8.,6.,8.,3., 0.,0.,0.,0.,0., 
    -380.0,1.0, 4.0,0.,16.,8.,-1., 4.,2.,16.,4.,2., 0.,0.,0.,0.,0., 
    -356.0,1.0, 4.0,0.,18.,8.,-1., 4.,2.,18.,4.,2., 0.,0.,0.,0.,0., 
    -257.0,1.0, 6.0,0.,16.,8.,-1., 6.,2.,16.,4.,2., 0.,0.,0.,0.,0., 
    -111.0,1.0, 14.0,0.,4.,8.,-1., 14.,2.,4.,4.,2., 0.,0.,0.,0.,0., 
    825.0,-1.0, 18.0,0.,4.,24.,-1., 18.,8.,4.,8.,3., 0.,0.,0.,0.,0., 
    1176.0,-1.0, 2.0,0.,18.,8.,-1., 8.,0.,6.,8.,3., 0.,0.,0.,0.,0., 
  };
  static CvMat haarclassifier_face25 =
      cvMat(30,17,CV_32F,haarclassifier_face25_data);
  return &haarclassifier_face25;
}
