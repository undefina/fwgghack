int d[205][205],rk[205][205],val[205],n,m,ans=INF;
int u[40005],v[40005],w[40005]; 
void floyd(){
	int i,j,k;
	for(k=1;k<=n;k++)
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				d[i][j]=min(d[i][k]+d[k][j],d[i][j]);
}
int cmp(int x,int y){
	return val[x]<val[y];
}
void core(){
	int i,j,k;
	floyd();
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			rk[i][j]=j;
			val[j]=d[i][j];
		}
		sort(rk[i]+1,rk[i]+n+1,cmp);
	}
	for(i=1;i<=n;i++) gmin(ans,d[i][rk[i][n]]*2);
	for(i=1;i<=m;i++)
		for(k=n,j=n-1;j>=1;j--)
			if(d[v[i]][rk[u[i]][j]]>d[v[i]][rk[u[i]][k]]){
				gmin(ans,d[u[i]][rk[u[i]][j]]+d[v[i]][rk[u[i]][k]]+w[i]);
				k=j; 
			}
}
mainint main(){
	qwq
    cin>>n>>m;
    mINF(d);
    for(int i=1;i<=n;i++)
        d[i][i]=0;
    for(int i=1;i<=m;++i){
        cin>>u[i]>>v[i]>>w[i];
        gmin(d[u[i]][v[i]],w[i]);
        gmin(d[v[i]][u[i]],w[i]);
    }
    core();
    cout<<ans*1.0/2;
}