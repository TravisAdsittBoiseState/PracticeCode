package Search;

import Graphs.Node;

public class DepthFirst {
	
	public String discoveryOrder = "";
	
	public void DFSearch(Node root){
		if(root == null)return;
		discoveryOrder = discoveryOrder + root.getName() + "->";
		
		root.visit();
		
		for(Node n: root.getAdjacentNodes()){
			if(!n.visited()){
				DFSearch(n);
			}
		}
		
	}
	
}
