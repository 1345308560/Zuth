#ifndef _ADVANCED_ALGORITHM_H
#define _ADVANCED_ALGORITHM_H
#include <iostream>
#include <vector>
namespace Zuth {
	class SegmentTree {
	public:
		class SegmentNode {
		public:
			int count = 0;
			int left;
			int right;
		};
	private:
		int m;
		std::vector<SegmentNode*> segment;
	public:
		SegmentTree(int m) {
			this->m = m;
			segment.resize(4 * m);
			buildSegmentTree(1, m, 1);
		}
		void buildSegmentTree(int left, int right, int i) {
			segment[i] = new SegmentNode();
			segment[i]->left = left;
			segment[i]->right = right;
			if (left == right) return;
			int mid = left + (right - left) / 2;
			buildSegmentTree(left, mid, i * 2);
			buildSegmentTree(mid + 1, right, i * 2 + 1);
		}
		void insert(int data) {
			int left = 1, right = m;
			int i = 1;
			while (left != right) {
				segment[i]->count++;
				int mid = left + (right - left) / 2;
				if (data <= mid) {
					right = mid;
					i = i * 2;
				}
				else {
					left = mid + 1;
					i = i * 2 + 1;
				}
			}
			segment[i]->count++;
		}

		void erase(int data) {
			int left = 1, right = m;
			int i = 1;
			while (left != right) {
				int mid = left + (right - left) / 2;
				segment[i]->count--;
				if (data <= mid) {
					right = mid;
					i = i * 2;
				}
				else {
					left = mid + 1;
					i = i * 2 + 1;
				}
			}
			segment[i]->count--;
		}
		int count(int left, int right) {
			return countInternal(left, right, 1);
		}
		int countInternal(int left, int right, int i) {
			if (segment[i]->left == left && segment[i]->right == right) {
				return segment[i]->count;
			}
			int mid = segment[i]->left + (segment[i]->right - segment[i]->left) / 2;
			if (left > mid) {
				return countInternal(mid + 1, right, i * 2 + 1);
			}
			else if (right <= mid) {
				return countInternal(left, right, i * 2);
			}
			else {
				return countInternal(left, mid, i * 2) + countInternal(mid + 1, right, i * 2 + 1);
			}
		}
	};
	//  ³Ë·¨ÄæÔª
	template<typename T>
	void exgcd(T a, T b, T& x, T& y) {
		if (b == 0) {
			x = 1, y = 0;
			return;
		}
		exgcd(b, a % b, y, x);
		y -= a / b * x;
	}
}

#endif
