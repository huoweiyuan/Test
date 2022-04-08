#include <vector>
using namespace std;
class Solution {
  public:
    vector<vector<int> > floodFill(vector<vector<int> >& image, int sr, int sc, int newColor) 
    {
    int oriColor = image[sr][sc];
        image[sr][sc] = newColor;
        // 上
        if (0 < sr && image[sr - 1][sc] == oriColor)
        {
            floodFill(image, sr - 1, sc, newColor);
        }
        
        if (sr < image.size() - 1 && image[sr+1][sc] == oriColor)
        {
            floodFill(image, sr+1, sc, newColor);
        }

        if (0 < sc && image[sr][sc - 1] == oriColor)
        {
            floodFill(image, sr, sc - 1, newColor);
        }

        if (sc < image[0].size() - 1 && image[sr][sc + 1] == oriColor)
        {
            floodFill(image, sr, sc + 1, newColor);
        }
        return image;
    }
};

int main()
{
  vector<vector<int> > input{{0,0,0}, {0,1,1}};
  Solution s;
  s.floodFill(input, 1, 1, 1);
  return 0;
}
