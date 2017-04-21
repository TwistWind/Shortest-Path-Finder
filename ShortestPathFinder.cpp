//2017NQUFan,Chen-han 
#include <iostream>
#include<fstream>
#include <list>
#include <queue>
#define INFINITO 10000000

using namespace std;

class Graph
{
private:
	int V; 

	
	list<pair<float, float> > * adj;

public:

	
	Graph(int V)
	{
		this->V = V; 
		adj = new list<pair<float, float> >[V];
	}

	
	void addLine(int v1, int v2, float custo)
	{
		adj[v1].push_back(make_pair(v2, custo));
	}


	float dijkstra(int source, int dest)
	{
		
		float dist[V];
		float visitados[V];

		
		priority_queue < pair<float, float>,
					   vector<pair<float, float> >, greater<pair<float, float> > > pq;

		
		for(int i = 0; i < V; i++)
		{
			dist[i] = INFINITO;
			visitados[i] = false;
		}

		
		dist[source] = 0;

		
		pq.push(make_pair(dist[source], source));
		
		while(!pq.empty())
		{
			pair<float, float> p = pq.top(); 
			int u = p.second; 
			pq.pop(); 
			
			if(visitados[u] == false)
			{
				
				visitados[u] = true;

				list<pair<float, float> >::iterator it;
				
				for(it = adj[u].begin(); it != adj[u].end(); it++)
				{
					
					int v = it->first;
					float total_line = it->second;
					
					if(dist[v] > (dist[u] + total_line))
					{						
						dist[v] = dist[u] + total_line;
						pq.push(make_pair(dist[v], v));
					}
				}
			}
		} 
		return 	dist[dest];

	}
};

int main(int argc, char *argv[])
{   
    float sum=0;
	char ifilename[100] ;
	char ofilename[100] ;         
	char c ;
	int line =1 ;
	int count=1;   
	
	
	cout<<"�i�t�ΰT���j�ɮצW�ٽХ[�W���ɦW�A���{���ȾA��ANSI�s�X��.txt�ɡC\n"<<endl ;
	cout<<"�п�J����J���ɮצW��:" ;
	cin>>ifilename ;
    ifstream fin(ifilename);
    if(!fin) { 
        cout << "�i�t�ΰT���j�L�kŪ�J�ɮ�,�нT�{�᭫�s�Ұʥ��{���C\n"; 
        system("pause");
        return 0;
    }	
	cout<<"�п�J��X�ɪ��ɮצW��:" ;	
	cin>>ofilename ;
	cout<<"\n" ;
	
    while(fin.get(c)){
    	if(c =='\n'){
    		line++ ;
		}
	}
    fin.close(); 
    ifstream ifile(ifilename);
    cout<<"�`�@ "<<line<<" �����|�C"<<endl ;	
    
	float num[line][4];
    for(int i=0;i<line;i++){
      for(int k=1;k<4;k++){
        ifile >> num[i][k];
      }
	  //cout<<i<<" "<<num[i][1]<<" "<<num[i][2]<<" "<<num[i][3]<<endl ;
    }
    
	float p[line] ;
	p[0]=num[0][1];
	int j=1;    
    for(int i=0;i<line;i++){
    	bool check=false ;
    	for(int k=0;k<j;k++){
    	    if(p[k]==num[i][2]){
    	       check =true ;
			   break ;
		    }
        }	 
		if(check ==false){
			p[j]=num[i][2] ;
			j++ ;
			count++ ;
		}   
	}
	
	cout<<"�`�@ "<<count<<" �Ӹ`�I�C\n"<<endl ;
    ifile.close(); 
    
    for(int i=0;i<count;i++){
    	for(int j=1;j<count-i;j++){
    		if(p[j]<p[j-1])
    		    swap(p[j],p[j-1]) ;
		}
	}
    int vcount=count ;
    for(int i=0;i<p[count-1]+1;i++){
    	bool check2=false ;
    	for(int j=0;j<count;j++){
    		if(i ==p[j]){
    			check2=true ;
				break ;
			}
		}
		if(check2==false){
            vcount++ ;		
		}
	}
	
	//cout<<"vcount="<<vcount<<endl ;
    Graph g(vcount) ;
    for(int i=0;i<p[count-1]+1;i++){
    	bool check3=false ;
    	for(int j=0;j<count;j++){
    		//cout<<i<<" "<<p[j]<<endl ;
    		if(i ==p[j]){
    			check3=true ;
    			for(int k=0;k<line;k++){
    				if(i==num[k][1]){
	    	             g.addLine(num[k][1],num[k][2],num[k][3]) ;
	    	             g.addLine(num[k][2],num[k][1],num[k][3]) ;
			             //cout<<k<<" "<<num[k][1]<<" "<<num[k][2]<<" "<<num[k][3]<<endl ;    					
					}
				}
				break ;
			}
		}
		if(check3==false){
	    	g.addLine(0,i,INFINITO) ;
			//cout<<i<<endl ;
			//cout<<i<<" 0"<<" "<<i<<" "<<"0"<<endl ;			
		}
	}

	ofstream outfile(ofilename,ios::out);
	outfile<<"�`�@ "<<line<<" �����|�B "<<count<<" �Ӹ`�I�C"<<endl ;
	for(int c=0;c<count;c++){
		for(int d=0;d<count;d++){
		    if(p[d]>p[c]){
		          outfile <<p[c]<<"��"<<p[d]<<"�̵u�Z��:"<<g.dijkstra(p[c], p[d])<<"���"<< endl;
				  cout <<p[c]<<"��"<<p[d]<<"�̵u�Z��:"<<g.dijkstra(p[c], p[d])<<"���"<< endl;  
		          sum+=g.dijkstra(p[c], p[d]);
		    }
     	}
    }
    outfile<<"�`�M�Z��:"<<sum<<"���"<<endl ;  
    cout<<"\n�`�M�Z��:"<<sum<<"���\n"<<endl ;   
    outfile.close() ;
    cout<<"�i�t�ΰT���j�w�g�J�ɮ� "<<ofilename<<endl ;
    
    system("pause") ;
	return 0;
}
