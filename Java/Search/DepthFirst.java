package Search;

import Graphs.Node;

/**
 * 
 * This is an implementation of a Breadth First search on a directed graph
 * implementation located in the Graphs package.
 * 
 * As stated in the Breadth First Class the only reason these two are in
 * Separate classes is for the sake of organization of the packages and
 * files.
 * 
 * @author Travis Adsitt
 * 
 * 26JUL18
 *
 */
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
