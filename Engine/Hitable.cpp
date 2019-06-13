#include "Hitable.h"


BVHNode::BVHNode(Hitable ** l, int n, float time0, float time1)
{



	int axis = (int)(3.0f * ((float)(rand() % RAND_MAX + 1) / (float)(RAND_MAX + 1)));
	if (axis == 0)
	{
		qsort(l, n, sizeof(Hitable*), [](const void *a, const void *b)
		{
			AABB boxLeft, boxRight;
			Hitable *ah = *((Hitable**)a);
			Hitable *bh = *((Hitable**)b);
			if (!ah->BoundingBox(0, 0, boxLeft) || !bh->BoundingBox(0, 0, boxRight)) {}
			{

			}
			if (boxLeft.minP.x() - boxRight.minP.x() < 0.0f)
			{
				return -1;
			}
			else
			{
				return 1;
			}
		}
		);
	}
	else if (axis == 1)
	{
		qsort(l, n, sizeof(Hitable*), [](const void *a, const void *b)
		{
			AABB boxLeft, boxRight;
			Hitable *ah = *((Hitable**)a);
			Hitable *bh = *((Hitable**)b);
			if (!ah->BoundingBox(0, 0, boxLeft) || !bh->BoundingBox(0, 0, boxRight)) {}
			{

			}
			if (boxLeft.minP.y() - boxRight.minP.y() < 0.0f)
			{
				return -1;
			}
			else
			{
				return 1;
			}
		}
		);
	}
	else
	{
		qsort(l, n, sizeof(Hitable*), [](const void *a, const void *b)
		{
			AABB boxLeft, boxRight;
			Hitable *ah = *((Hitable**)a);
			Hitable *bh = *((Hitable**)b);
			if (!ah->BoundingBox(0, 0, boxLeft) || !bh->BoundingBox(0, 0, boxRight)) {}
			if (boxLeft.minP.z() - boxRight.minP.z() < 0.0f)
			{
				return -1;
			}
			else
			{
				return 1;
			}
		}
		);
	}
	if (n == 1)
	{
		right = l[0];
		left = right;
	}
	else if (n == 2)
	{
		left = l[0];
		right = l[1];
	}
	else
	{
		left = new BVHNode(l, n / 2, time0, time1);
		right = new BVHNode(l + n / 2, n - n / 2, time0, time1);
	}

	AABB boxLeft, boxRight;

	if (!left->BoundingBox(time0, time1, boxLeft) || !right->BoundingBox(time0, time1, boxRight)) {}
	
	box = SurroundingBox(boxLeft, boxRight);
}
