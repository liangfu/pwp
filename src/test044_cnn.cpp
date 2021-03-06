#include "ml.h"
#include "highgui.h"
#include "cxcore.h"
#include "cvext.h"

#ifdef _OPENMP
#include <omp.h>
#endif

#include "ConvNN.h"

int ReverseInt (int i)
{
  unsigned char ch1, ch2, ch3, ch4;
  ch1 = i & 255;
  ch2 = (i >> 8) & 255;
  ch3 = (i >> 16) & 255;
  ch4 = (i >> 24) & 255;
  return((int) ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}
 
CvMat * read_Mnist_Images(char * filename)
{
  FILE * fp = fopen(filename,"r");
  if (!fp){fprintf(stderr,"file loading error: %s\n",filename);return 0;}
  int magic_number = 0;
  int number_of_images = 0;
  int n_rows = 0;
  int n_cols = 0;
  fread((char*) &magic_number, sizeof(magic_number),1,fp);
  magic_number = ReverseInt(magic_number);
  fread((char*) &number_of_images,sizeof(number_of_images),1,fp);
  number_of_images = ReverseInt(number_of_images);
  fread((char*) &n_rows, sizeof(n_rows),1,fp);
  n_rows = ReverseInt(n_rows);
  fread((char*) &n_cols, sizeof(n_cols),1,fp);
  n_cols = ReverseInt(n_cols);
  CvMat * data = cvCreateMat(number_of_images,n_rows*n_cols,CV_32F);
  for(int i = 0; i < number_of_images; ++i){
  for(int r = 0; r < n_rows; ++r){
  for(int c = 0; c < n_cols; ++c){
	unsigned char temp = 0;
	fread((char*) &temp, sizeof(temp),1,fp);
	CV_MAT_ELEM(*data,float,i,r*n_cols+c)=float(temp);
  }
  }
  }
  return data;
}
 
CvMat * read_Mnist_Labels(char * filename)
{
  FILE * fp = fopen(filename,"r");
  if (!fp){fprintf(stderr,"file loading error: %s\n",filename);return 0;}
  int magic_number = 0;
  int number_of_labels = 0;
  fread((char*) &magic_number, sizeof(magic_number),1,fp);
  magic_number = ReverseInt(magic_number);
  fread((char*) &number_of_labels,sizeof(number_of_labels),1,fp);
  number_of_labels = ReverseInt(number_of_labels);
  CvMat * data = cvCreateMat(number_of_labels,1,CV_8U);
  for(int i = 0; i < number_of_labels; ++i){
	unsigned char temp = 0;
	fread((char*) &temp, sizeof(temp),1,fp);
	CV_MAT_ELEM(*data,uchar,i,0)=float(temp);
  }
  return data;
}

int main(int argc, char * argv[])
{
  // if (argc<2){fprintf(stderr,"Error: input training data is required!\n");return 1;}
#ifdef _OPENMP
  const int max_threads = MAX(1.,std::ceil(float(omp_get_max_threads())*.5));
#else
  const int max_threads = 1;
#endif
  fprintf(stderr, "MAX_THREADS=%d\n",max_threads);

  const char * training_filename = "../data/mnist/train-images-idx3-ubyte";
  const char * response_filename = "../data/mnist/train-labels-idx1-ubyte";
  const char * testing_filename = "../data/mnist/t10k-images-idx3-ubyte";
  const char * expected_filename = "../data/mnist/t10k-labels-idx1-ubyte";
  const char * pretrained_filename = "../data/mnist/pretrained.xml";

  fprintf(stderr,"Loading MNIST Images ...\n");
  CvMat * training = read_Mnist_Images((char*)training_filename);
  CvMat * response = read_Mnist_Labels((char*)response_filename);
  CvMat * testing = read_Mnist_Images((char*)testing_filename);
  CvMat * expected = read_Mnist_Labels((char*)expected_filename);
  
  int nr = sqrt(training->cols);
  int nc = nr;
  assert(training->cols==nr*nc);
  fprintf(stderr,"%d Images in %dx%d Loaded!\n",training->rows,nr,nc);

  ConvNN * cnn = new ConvNN(28,28, // input image size
                            84,10, // full connect nodes
                            0.06,  // learning rate
                            900,  // maxiter
                            2      // batch_size
                            );
  cnn->createCNN();
CV_TIMER_START();
#if 1
  cnn->trainNN(training,response,testing,expected);
  cnn->writeCNNParams(pretrained_filename);
#else
  cnn->readCNNParams(pretrained_filename);
#endif

  CNNIO * cnnio = new CNNIO();
  cnnio->init(3,1,1,cnn);
  
  int nsamples = MIN(5000,testing->rows);
  CvMat * samples = cvCreateMat(nsamples,testing->cols,CV_32F);
  CvMat * result = cvCreateMat(10,nsamples,CV_32F);
  CvMat * sorted = cvCreateMat(result->rows,result->cols,CV_32F);
  CvMat * indices = cvCreateMat(result->rows,result->cols,CV_32S);
  CvMat * indtop1 = cvCreateMat(1,result->cols,CV_32S);
  CvMat * expected_submat = cvCreateMat(nsamples,1,CV_8U);
  CvMat * expected_converted = cvCreateMat(nsamples,1,CV_32S);
  CvMat * expected_transposed = cvCreateMat(1,result->cols,CV_32S);
  CvMat * indtop1res = cvCreateMat(1,result->cols,CV_8U);
  // testing data
  cvGetRows(testing,samples,0,nsamples);
  cnn->m_cnn->predict(cnn->m_cnn,samples,result);
  cvSort(result,sorted,indices,CV_SORT_DESCENDING|CV_SORT_EVERY_COLUMN);
  cvGetRow(indices,indtop1,0);
  // expected data
  cvGetRows(expected,expected_submat,0,nsamples);
  cvConvert(expected_submat,expected_converted);
  cvTranspose(expected_converted,expected_transposed);
  cvCmp(indtop1,expected_transposed,indtop1res,CV_CMP_EQ);
#if 0
  fprintf(stderr,"expected:\n\t");
  cvPrintf(stderr,"%d,",expected_transposed);
  fprintf(stderr,"result:\n\t");
  cvPrintf(stderr,"%d,",indtop1);
#endif
  float top1=cvSum(indtop1res).val[0]/255.f;
  cvReleaseMat(&samples);
  cvReleaseMat(&result);
  cvReleaseMat(&sorted);
  cvReleaseMat(&indices);
  cvReleaseMat(&indtop1);
  cvReleaseMat(&expected_submat);
  cvReleaseMat(&expected_converted);
  cvReleaseMat(&expected_transposed);
  cvReleaseMat(&indtop1res);

  fprintf(stderr,"top-1: %.1f%%\n",float(top1*100.f)/float(nsamples));
CV_TIMER_SHOW();

  cvReleaseMat(&training);

  return 0;
}
