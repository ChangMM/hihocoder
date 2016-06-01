#include <cstdio>
#include <cstring>
int const MAXN = 1e6 + 5;
int const MAXM = 1e4 + 5;
char s[MAXN], t[MAXM];
int next[MAXM], n;

void get_next()
{
	next[0] = -1;
	int i = 0, j = -1;
	while(t[i] != '\0')
	{
		if(j == -1 || t[i] == t[j])
		{
			i ++;
			j ++;
			next[i] = j;
		}
		else 
			j = next[j];
	}
}	

int KMP()
{
	get_next();
	int i = 0, j = 0, ans = 0, len = strlen(t);
	while(s[i])
	{
		if(j == -1 || s[i] == t[j])
		{
			i ++;
			j ++;
		}
		else
			j = next[j];
		if(j == len)
		{
			j = next[j];
			ans ++;
		}
	}
	return ans;
}	

int main()
{
	scanf("%d", &n);
	while(n --)
	{
		scanf("%s %s", t, s);
		printf("%d\n", KMP());
	}
}