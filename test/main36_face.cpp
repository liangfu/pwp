/**
 * @file   main35_face.cpp
 * @author Liangfu Chen <liangfu.chen@cn.fix8.com>
 * @date   Mon Jul  8 16:14:23 2013
 * 
 * @brief  
 * 
 * 
 */
#include "cvfacedetector.h"
#include "cvtimer.h"

int main(int argc, char * argv[])
{
  int i,j;
  const char * imglist = "../data/face/imagelist.txt";
  const char * neglist = "../data/face/negative.txt";
  CvTrainSample possamples[1000],negsamples[1000];
  const int maxpossamples = sizeof(possamples)/sizeof(CvTrainSample);
  const int maxnegsamples = sizeof(negsamples)/sizeof(CvTrainSample);
  char line[1024];
  CvPoint2D32f leye,reye,nose,lmou,mmou,rmou;
  float xscale,yscale;
  int poscount=0,negcount=0;

  // load image data
  FILE * fp = fopen(imglist, "r");
  for (i=0;i<maxpossamples;i++){
    fgets(line,1024,fp);
    if (line[0]=='-'){break;}
    if (line[0]=='#'){i--;continue;}
    sscanf(line,"%s %f %f %f %f %f %f %f %f %f %f %f %f",possamples[i].fn,
           &leye.x,&leye.y,&reye.x,&reye.y,&nose.x,&nose.y,
           &lmou.x,&lmou.y,&mmou.x,&mmou.y,&rmou.x,&rmou.y);
    xscale = sqrt(pow(leye.x-reye.x,2)+pow(leye.y-reye.y,2))/12.;
    yscale = sqrt(pow((leye.x+reye.x)*.5-mmou.x,2)+
                  pow((leye.y+reye.y)*.5-mmou.y,2))/12.;
    // fprintf(stderr, "scale: %f,%f\n",xscale,yscale);
    if (xscale<2.||yscale<2.){i--;continue;}
    possamples[i].box =
        cvBox2D(nose.x,nose.y-yscale*1.,xscale*24.,yscale*24.,
                -atan2(reye.y-leye.y,reye.x-leye.x)*180./CV_PI);
        //cvRect(leye.x-6.*scale,leye.y-6.*scale,scale*24.,scale*24.);
  }
  fclose(fp);
  poscount=i;

  fp = fopen(neglist,"r");
  for (i=0;i<maxnegsamples;i++){
    fgets(line,1024,fp);
    if (line[0]=='-'){break;}
    sscanf(line,"%s",negsamples[i].fn);
  }
  fclose(fp);
  negcount=i;
  
  // fprintf(stderr, "INFO: %d positive samples!\n", i);

  CvFaceDetector detector;

#if 0
  detector.train(possamples,poscount,negsamples,negcount);

#else

  const char * fnlist[] = {
    "../data/gesturePalm_JC2-0000.png",
    "../data/gesturePalm_JC3train-204.png",
    "../data/gesturePalm_Jiang-0000.png",
    "../data/gesturePalm_Liulu-0300.png",
    "../data/gesturePalm_Steven-0000.png",
    "../data/mei-family.png",
    "",
  };

  for (j=0;strlen(fnlist[j])>0;j++)
  {
    IplImage * raw = cvLoadImage(fnlist[j],0);
    CvMat img_stub;
    CvMat * img = cvGetMat(raw,&img_stub);
    CvRect rois[1000];
CV_TIMER_START();
    int nfaces = detector.detect(img,rois);
CV_TIMER_SHOW();
    for (i=0;i<nfaces;i++){
      cvRectangle(img,cvPoint(rois[i].x,rois[i].y),
                  cvPoint(rois[i].x+rois[i].width,rois[i].y+rois[i].height),
                  cvScalarAll(255));
    }
    char label[100];sprintf(label,"nfaces: %d",nfaces);
    cvDrawLabel(img,label,cvScalarAll(128));
    // if (img->cols>1250)
    // {
    //   double scale = 1250./float(img->cols);
    //   CvMat * resized=cvCreateMat(img->rows*scale,img->cols*scale,CV_8U);
    //   cvResize(img,resized);
    //   cvShowImage("Test",resized); CV_WAIT();
    //   cvReleaseMat(&resized);
    // }else
    {
      cvShowImage("Test",img); CV_WAIT();
    }
    cvReleaseImage(&raw);
  }
#endif
  
  return 0;
}
