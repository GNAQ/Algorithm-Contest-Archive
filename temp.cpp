vector<Point> HalfPlaneIntersection(vector<Line> L)
{
	int len = L.size();
	sort(L.begin(), L.end());

	vector<Line> que(len + 2);
	vector<Point> poly;
	int h = 0, t = 0;

	que[0] = L[0];

	for (int i = 1; i < len; i++)
	{
		while (h < t && !OnLeft(L[i], poly[t - 1]))
			t--;
		while (h < t && !OnLeft(L[i], poly[h]))
			h++;

		que[++t] = L[i];
		while (fabs(que[t].ag - que[t - 1].ag) < eps)
		{
			t--;
			if (OnLeft(que[t], L[i].p))
				que[t] = L[i];
		}

		if (h < t)
			poly[t - 1] = GetLineIntersection(que[t - 1], que[t]);
	}

	while (h < t && !OnLeft(que[h], poly[t - 1]))
		t--;
	vector<Point> ans;
	if (t - h <= 1)
		return ans;
	poly[t] = GetLineIntersection(que[t], que[h]);
	for (int i = h; i <= t; i++)
		ans.push_back(poly[i]);
	return ans;
}