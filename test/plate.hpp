#ifndef EASYPR_PLATE_HPP
#define EASYPR_PLATE_HPP

namespace easypr {

namespace demo {

using namespace cv;
using namespace std;

//���ƶ�λ
int test_plate_locate() {
  cout << "test_plate_locate" << endl;

  const string file = "resources/image/test.jpg";

  cout << "file path: "  << file << endl;

  cv::Mat src = imread(file);

  // TODO��ԭplateLocate��Ҫ���滻

  vector<cv::Mat> resultVec;
  CPlateLocate plate;
  plate.setDebug(1);
  plate.setLifemode(true);

  int result = plate.plateLocate(src, resultVec);

  //��λ���Ƴɹ� ������ʾ����
  if (result == 0) {
    size_t num = resultVec.size();
    for (size_t j = 0; j < num; j++) {
      cv::Mat resultMat = resultVec[j];
      imshow("plate_locate", resultMat);
      waitKey(0);
    }
    destroyWindow("plate_locate");
  }

  return result;
}

//�����ж� ͨ��kvm�жϳ��ƶ�λ��ѡ����ͼ����Щ�ǳ���
int test_plate_judge() {
  cout << "test_plate_judge" << endl;

  std::string img_path = "resources/image/plate_judge.jpg";
  cv::Mat src = imread(img_path);

  vector<cv::Mat> matVec;

  vector<cv::Mat> resultVec;

  CPlateLocate lo;
  lo.setDebug(1);
  lo.setLifemode(true);

  cout << "image path: " << img_path << endl;

  int resultLo = lo.plateLocate(src, matVec);

  if (0 != resultLo) return -1;

  cout << "plate_locate_img" << endl;
  size_t num = matVec.size();
  for (size_t j = 0; j < num; j++) {
    Mat resultMat = matVec[j];
    imshow("plate_judge", resultMat);
    waitKey(0);
  }
  destroyWindow("plate_judge");

  int resultJu = PlateJudge::instance()->plateJudge(matVec, resultVec);

  if (0 != resultJu) 
  {
  	cout << "can't find plate" << endl;
  	return -1;
  }

  cout << "plate_judge_img result" << endl;
  num = resultVec.size();
  //������ʾ�ж�Ϊ���Ƶľ���
  for (size_t j = 0; j < num; j++) {
    Mat resultMat = resultVec[j];
    imshow("plate_judge", resultMat);
    waitKey(0);
  }
  destroyWindow("plate_judge");

  return resultJu;
}

//���Ƽ�� ͨ����ɫ����Sobel��ʽ����Ƿ���ڳ���
int test_plate_detect() {
  cout << "test_plate_detect" << endl;

  std::string img_path = "resources/image/plate_detect.jpg";

  cv::Mat src = imread(img_path);

  vector<CPlate> resultVec;
  CPlateDetect pd;
  pd.setPDLifemode(true);

  
  cout << "image path: " << img_path << endl;

  int result = pd.plateDetect(src, resultVec);
  if (result == 0) {
    size_t num = resultVec.size();
    for (size_t j = 0; j < num; j++) {
      CPlate resultMat = resultVec[j];

      imshow("plate_detect", resultMat.getPlateMat());
      waitKey(0);
    }
    destroyWindow("plate_detect");
  }

  return result;
}

//����ʶ�� 
int test_plate_recognize() {
  cout << "test_plate_recognize" << endl;
  std::string img_path = "resources/image/test.jpg";
  Mat src = imread(img_path);

  CPlateRecognize pr;
  pr.setLifemode(true);
  pr.setDebug(true);

  cout << "image path: " << img_path << endl;

  vector<string> plateVec;

  int result = pr.plateRecognize(src, plateVec);
  if (result == 0) {
    size_t num = plateVec.size();
    for (size_t j = 0; j < num; j++) {
      cout << "plateRecognize: " << plateVec[j] << endl;
    }
  }

  if (result != 0) cout << "result:" << result << endl;

  return result;
}
}
}

#endif  // EASYPR_PLATE_HPP
