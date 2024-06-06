#include <opencv2/opencv.hpp>
#include <opencv2/cudastereo.hpp>
#include <chrono>

int main() {
    cv::Mat left = cv::imread("tsukuba-imL.png", cv::IMREAD_GRAYSCALE);
    cv::Mat right = cv::imread("tsukuba-imR.png", cv::IMREAD_GRAYSCALE);
    cv::cuda::GpuMat d_left, d_right;
    d_left.upload(left);
    d_right.upload(right);

    int ndisp = 16;
    int iters = 40;
    int levels = 1;
    auto start = std::chrono::high_resolution_clock::now();
    cv::Ptr<cv::cuda::StereoBeliefPropagation> stereo = cv::cuda::createStereoBeliefPropagation(ndisp, iters, levels, CV_32F);
    cv::cuda::GpuMat d_disp;
    stereo->compute(d_left, d_right, d_disp);

    cv::Mat h_disp;
    d_disp.download(h_disp);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    cv::minMaxLoc(h_disp, &minVal, &maxVal, &minLoc, &maxLoc);
    std::cout << "minVal: " << minVal << ", maxVal: " << maxVal << std::endl;
    cv::imwrite("cuda.png", h_disp);

    return 0;
}