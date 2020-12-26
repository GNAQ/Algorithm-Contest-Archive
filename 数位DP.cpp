int dfs(int dig,int last,bool zero,bool lim){
	if(last!=-1&&f[dig][last][zero][lim]!=-1)return f[dig][last][zero][lim];
	int l=(lim?d[n-dig+1]:9),cnt=0;
	if(dig==n+1){ 
		if(zero)return 0;
		else return 1;
	}
	if(!last&&zero)last=-3;
	for(int i=0;i<=l;i++){
		if(    )continue;
		if(i==l){
			cnt+=dfs(dig+1,i,zero&(i==0),lim&1);
		}
		else cnt+=dfs(dig+1,i,zero&(i==0),0);
	}
	f[dig][last][zero][lim]=cnt;
	return cnt;
}
