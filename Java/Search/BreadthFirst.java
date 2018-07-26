package Search;

import Graphs.Node;
import Stack_Queue.Queue;

/**
 * 
 * Not entirely sure why I chose to separate the two searches, maybe for better
 * Organization. Regardless this is a Bread First Search implementation using
 * the Directed Graph in the Graphs package.
 * 
 * To see the order in which thinggs were discovered one must print out the 
 * 'discoveryOrder' variable which is of course intentionally made public...
 * (getters and setters just seemed excessive)
 * 
 * @author Travis Adsitt
 * 
 * 26JUL18
 *
 */
public class BreadthFirst {

	public String discoveryOrder = "";
	
	/**
	 * 
	 * Just need a root node to start the search.
	 * 
	 * @param root
	 */
	public void BFSearch(Node root){
		
		Queue<Node> queue = new Queue<Node>();
		
		queue.enqueue(root);
		root.visit();
		
		while(!queue.isEmpty()){
			Node currNode = queue.dequeue();
			
			discoveryOrder = discoveryOrder + currNode.getName() + "->";
			
			for(Node n: currNode.getAdjacentNodes()){
				if(!n.visited()){
					queue.enqueue(n);
					n.visit();
				}
			}
		}
		
	}
}
