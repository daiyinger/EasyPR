#ifndef EASYPR_CHARS_HPP
#define EASYPR_CHARS_HPP

namespace easypr {

namespace demo {

//×Ö·û·Ö¸î²âÊÔ 
int test_chars_segment() {
  std::cout << "test_chars_segment" << std::endl;

  std::string img_path = "resources/image/chars_segment.jpg";

  cout << "image path :" << img_path << endl;

  cv::Mat src = cv::imread(img_path);

  std::vector<cv::Mat> resultVec;
  CCharsSegment plate;

  int result = plate.charsSegment(src, resultVec);
  if (result == 0) {
    size_t num = resultVec.size();
    for (size_t j = 0; j < num; j++) {
      cv::Mat resultMat = resultVec[j];
      cv::imshow("chars_segment", resultMat);
      cv::waitKey(0);
    }
    cv::destroyWindow("chars_segment");
  }

  return result;
}

//×Ö·û¼ø±ğ²âÊÔ 
int test_chars_identify() {
  std::cout << "test_chars_identify" << std::endl;

  std::string img_path = "resources/image/chars_identify.jpg";

  cout << "image path :" << img_path << endl;

  cv::Mat plate = cv::imread(img_path);

  std::vector<Mat> matChars;
  std::string license;

  CCharsSegment cs;

  int result = cs.charsSegment(plate, matChars);
  if (result == 0) {
    for (auto block : matChars) {
      auto character = CharsIdentify::instance()->identify(block);
      license.append(character.second);
    }
  }

  std::string plateLicense = "è‹E771H6";
#ifdef OS_WINDOWS
  plateLicense = utils::utf8_to_gbk(plateLicense.c_str());
#endif
  std::cout << "plateLicense: " << plateLicense << std::endl;
  std::cout << "plateIdentify: " << license << std::endl;

  if (plateLicense != license) {
    std::cout << "Identify Not Correct!" << std::endl;
    return -1;
  }
  std::cout << "Identify Correct!" << std::endl;

  return result;
}

int test_chars_recognise() {
  std::cout << "test_chars_recognise" << std::endl;

  std::string img_path = "resources/image/chars_recognise.jpg";
  
  cout << "image path :" << img_path << endl;

  cv::Mat src = cv::imread(img_path);
  CCharsRecognise cr;

  std::string plateLicense = "";
  int result = cr.charsRecognise(src, plateLicense);
  if (result == 0)
    std::cout << "charsRecognise: " << plateLicense << std::endl;
  return 0;
}
}
}

#endif  // EASYPR_CHARS_HPP
