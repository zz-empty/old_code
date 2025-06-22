#include <iostream>
#include <vector>

using namespace std;
using std::cin;
using std::cout;

vector<int> find_common(vector<int> &nums1, vector<int> &nums2) {
  vector<int> result;
  size_t i = 0, j = 0;

  while (i < nums1.size() && j < nums2.size()) {
    if (nums1[i] < nums2[j]) {
      i++;
    } else if (nums1[i] > nums2[j]) {
      j++;
    } else {
      result.push_back(nums1[i]);
      i++;
      j++;
    }
  }
  return result;
}

void print_arr(vector<int> vec) {
  for (int it : vec) {
    cout << it << " ";
  }
  cout << endl;
}

int main() {
  vector<int> a = {2, 3, 6, 8, 18, 21, 34, 42};
  vector<int> b = {2, 6, 7, 9, 22, 31, 34, 78};

  cin >> a[0];

  a[0] = 1;
  print_arr(a);
  print_arr(b);

  vector<int> result = find_common(a, b);
  print_arr(result);

  return 0;
}
