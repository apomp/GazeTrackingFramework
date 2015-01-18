#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <set>

// COLORS
const cv::Scalar BLUE(255, 0, 0), 	    RED(0, 0, 255),        GREEN(0, 255, 0),
				 CYAN(255, 255, 0), 	MAGENTA(255, 0, 255),  YELLOW(0, 255, 255),
				 WHITE(255, 255, 255), 	BLACK(0, 0, 0);

inline int pow2(int n) { return 1 << n; }

template<typename T>
inline T sq(T n) { return n * n; }

template<typename T>
inline T lerp(const T& val1, const T& val2, double alpha) {
	return val1*(1-alpha) + val2*alpha;
}

int random(int min, int max);

template<typename T>
inline cv::Rect_<T> roiAround(T x, T y, T radius) {
    return cv::Rect_<T>(x - radius, y - radius, 2*radius + 1, 2*radius + 1);
}

template<typename T>
inline cv::Rect_<T> roiAround(const cv::Point_<T>& centre, T radius)
{
    return roiAround(centre.x, centre.y, radius);
}

inline cv::Rect boundingBox(const cv::Mat& img) {
    return cv::Rect(0,0,img.cols,img.rows);
}

inline cv::Point2f normVec(const cv::Point& vec)
{
	float mag = sqrt(vec.x*vec.x + vec.y*vec.y);
    return cv::Point2f(vec.x/mag, vec.y/mag);
}

template<typename T>
std::vector<T> randomSubset(const std::vector<T>& src, typename std::vector<T>::size_type size)
{
    if (size > src.size())
        throw std::range_error("Subset size out of range");

    std::vector<T> ret;
    std::set<size_t> vals;

    for (size_t j = src.size() - size; j < src.size(); ++j)
    {
        size_t idx = random(0, j); // generate a random integer in range [0, j]

        if (vals.find(idx) != vals.end())
            idx = j;

        ret.push_back(src[idx]);
        vals.insert(idx);
    }

    return ret;
}

//adopted from: http://stackoverflow.com/questions/1577475/c-sorting-and-keeping-track-of-indexes
template <typename T>
std::vector<size_t> sort_indexes(const std::vector<T> &v) {
	// initialize original index locations
	std::vector<size_t> idx(v.size());
	for (size_t i = 0; i != idx.size(); ++i){
		idx[i] = i;
	}

	// sort indexes based on comparing values in v
	sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) {
		return v[i1] > v[i2];
	});
	return idx;
}

// Drawing convenience methods for cross and plus shapes
inline void cross(cv::Mat& img, cv::Point centre, int radius, const cv::Scalar& colour, int thickness = 1, int lineType = 8, int shift = 0) {
    cv::line(img, centre + cv::Point(-radius, -radius), centre + cv::Point(radius, radius), colour, thickness, lineType, shift = 0);
    cv::line(img, centre + cv::Point(-radius, radius), centre + cv::Point(radius, -radius), colour, thickness, lineType, shift = 0);
}
inline void plus(cv::Mat& img, cv::Point centre, int radius, const cv::Scalar& colour, int thickness = 1, int lineType = 8, int shift = 0) {
    cv::line(img, centre + cv::Point(0, -radius), centre + cv::Point(0, radius), colour, thickness, lineType, shift = 0);
    cv::line(img, centre + cv::Point(-radius, 0), centre + cv::Point(radius, 0), colour, thickness, lineType, shift = 0);
}

#endif // __UTILS_H__
