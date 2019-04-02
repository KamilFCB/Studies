#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;


int main()
{
	int n;
	scanf("%d", &n);
	int *dist = new int[n+1];
	long long int sum = 0;

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &dist[i]);
		sum += dist[i];
	}

	long long int max_dist = 0;
	long long int tmp_dist = 0;
	int last = 1;

	for (int i = 1; last < n; i = (i + 1) % (n+1))
	{
		//printf("1: %lld \n", tmp_dist);
		tmp_dist += dist[i];
		if (tmp_dist < sum / 2)
		{
			max_dist = max(tmp_dist, max_dist);
		}
		else if (tmp_dist == sum / 2)
		{
			max_dist = tmp_dist;
			break;
		}
		else
		{
			max_dist = max(max_dist, (sum - tmp_dist));

			while (tmp_dist > sum / 2.0 && last < n)
			{
				//printf("2: %lld \n", tmp_dist);
				tmp_dist -= dist[last];
				last++;

				if (tmp_dist < sum / 2)
					max_dist = max(tmp_dist, max_dist);
				else if (tmp_dist == sum / 2)
				{
					max_dist = tmp_dist;
					last = n;
					break; 
				}
				else
					max_dist = max(max_dist, (sum - tmp_dist));
			}
		}
	}


	printf("%lld", max_dist);
	return 0;
}