#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const long int maxN=100;
const long int maxV=1000;

struct joint{
	long int from;
	long int to;
	long int max_flow;
	long int cur_flow;
	joint * op_joint;
};


class Graph{
private:
	long int idA;
	long int idB;
	std::vector<joint> joints;
	std::vector<int> nodes[maxN];
	long int ranks[maxN];
	long int last_joint[maxN];
	long int Nnodes;
	long int Njoints;
public:
	Graph(long int A, long int B, long int N, long int K);
	~Graph(){};
	bool RankNetwork();
	long int FindBlockingFlow(long int id_cur, long int flow);
	long int GetMaxFlow();
	void InsertJoint(long int X, long int Y, long int val);
	
};

void Graph::InsertJoint(long int X, long int Y, long int val){
	joint f_j= {X,Y,val,0};
	joint b_j= {Y,X,0,0};
	nodes[X].push_back(joints.size());
	joints.push_back(f_j);
	nodes[Y].push_back(joints.size());
	joints.push_back(b_j);
	joints[nodes[X].back()].op_joint = &joints[nodes[Y].back()];
	joints[nodes[Y].back()].op_joint = &joints[nodes[X].back()];
	joint f2_j= {Y,X,val,0};
	joint b2_j= {X,Y,0,0};
	nodes[Y].push_back(joints.size());
	joints.push_back(f2_j);
	nodes[X].push_back(joints.size());
	joints.push_back(b2_j);
	joints[nodes[Y].back()].op_joint = &joints[nodes[X].back()];
	joints[nodes[X].back()].op_joint = &joints[nodes[Y].back()];	


}

bool Graph::RankNetwork(){
	std::queue<int> q;
	q.push(idA);
	memset(ranks,-1,Nnodes*sizeof(ranks[0]));
	ranks[idA]=0;
	while (q.size()>0 && ranks[idB]==-1){
		long int id_cur=q.front();
		q.pop();
		for(unsigned long int i=0;i<nodes[id_cur].size();++i){
			long int j_cur=nodes[id_cur][i];
			long int id_next= joints[j_cur].to;
			if(ranks[id_next] ==-1 && joints[j_cur].cur_flow < joints[j_cur].max_flow){
				q.push(id_next);
				ranks[id_next]=ranks[id_cur]+1;
			}
		}
	}
	return (ranks[idB]!=-1);
}

long int Graph::FindBlockingFlow(long int id_cur, long int flow){
	if(!flow) return 0;
	if(id_cur==idB) return flow;
	for(; last_joint[id_cur]<(long int)nodes[id_cur].size();++last_joint[id_cur]){
		long int j_next=nodes[id_cur][last_joint[id_cur]];
		long int id_next=joints[j_next].to;
		if(ranks[id_next]!=ranks[id_cur]+1) continue;
		long int next_flow=joints[j_next].max_flow-joints[j_next].cur_flow;
		long int push =FindBlockingFlow(id_next, (flow<next_flow) ? flow : next_flow);
		if(push>0) {
			joints[j_next].cur_flow+=push;
			joints[j_next].op_joint->cur_flow-=push;
			return push;
		}
	}
	return 0;

}

long int Graph::GetMaxFlow(){
	long int flow=0;
	for(;;){
		if(!RankNetwork()) break;
		memset(last_joint,0,Nnodes*sizeof(last_joint[0]));
		while(long int push = FindBlockingFlow(idA,Njoints*maxV)) flow+=push;
	}
	return flow;
}
Graph::Graph(long int A, long int B, long int N, long int K):
idA(A),
idB(B),
Nnodes(N),
Njoints(2*K)
{
}
	






int main(int argc, char ** argv){
//	const int maxN=100;
	int N,K,A,B;
	std::cin>>N>>K>>A>>B;
	Graph network(A-1,B-1,N,K);

	for(long int i=0;i<K;i++){
		long int id1,id2,val;
		std::cin>>id1>>id2>>val;
		network.InsertJoint(id1-1,id2-1,val);
		
	}
	//std::cout<<"start\n";
	long int flow = network.GetMaxFlow();
	std::cout<<flow;
	return 0;
}
