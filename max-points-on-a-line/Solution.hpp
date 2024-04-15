// https://leetcode.com/problems/max-points-on-a-line/?envType=study-plan-v2&envId=top-interview-150

struct SPoint {
    public:
        int x;
        int y;
        constexpr SPoint(const vector<int> & point):x{point[0L]}, y{point[1L]} {}
        constexpr SPoint(const int x, const int y):x{x}, y{y} {}

        constexpr bool operator==(const SPoint&) const = default;
        constexpr SPoint operator-(const SPoint & rhs) const {
            return {x - rhs.x, y - rhs.y};
        }
        constexpr inline long dot(const SPoint & rhs) const {
            return x * rhs.x + y * rhs.y;
        }
};

template<>
struct std::hash<SPoint>
{
    constexpr inline size_t operator()(const SPoint& point) const noexcept {
        return (point.x + point.y)&((1<<16) - 1);
    }
};

class Solution {
    using SPointList = unordered_set<SPoint>;

    static constexpr inline long dot(SPoint point1, SPoint point2) {
        return point1.dot(point2);
    }

    static constexpr inline SPoint inv_slope(SPoint point1, SPoint point2) {
        return {point1.y - point2.y, point2.x - point1.x};
    }

    /**
        1 <= points.length <= 300
        points[i].length == 2
        -10^4 <= xi, yi <= 10^4
        All the points are unique.
      */
    static inline int maxPointsOneBucket(SPointList& points) {
        if (points.size() <= 2L) return points.size();

        size_t max_cnt = 2L;
        for (auto it = points.begin(); it != points.end(); ++it) {
            auto it2 = it;
            for (++it2; it2 != points.end(); ++it2) {
                const SPoint ivs = inv_slope(*it, *it2);
                size_t cnt = 2L;
                
                auto it3 = it2;
                for (++it3; it3 != points.end();++it3) {
                    // Offset all points by - *it.
                    if (ivs.dot(*it3 - *it) == 0L) { // Point is on the line
                        cnt++;                        
                    }
                }
                if (max_cnt < cnt) max_cnt = cnt;
            }
        }
        return max_cnt;
    }

public:

    /**
        1 <= points.length <= 300
        points[i].length == 2
        -10^4 <= xi, yi <= 10^4
        All the points are unique.
      */
    static int maxPoints(const vector<vector<int>>& points) {
        SPointList spointList;
        for (const auto point: points) spointList.insert(point);
        return maxPointsOneBucket(spointList);
    }
};
