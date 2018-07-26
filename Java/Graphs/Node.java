package Graphs;


/**
 * 
 * A class to hold the node's name and the edges that come from it.
 * 
 * @author Travis Adsitt
 * 
 * 26JUL18
 *
 */


public class Node {

	private Edge edges[];
	private int numEdges;
	private String name;
	private boolean visited;
	
	public Node(String name, int numEdges, Edge edges[]){
		this.name = name;
		this.edges = edges;
		this.numEdges = numEdges;
		this.visited = false;
	}
	
	public Node(String name){
		this.name = name;
		this.edges = new Edge[1];
		this.numEdges = 0;
		this.visited = false;
	}
	
	/**
	 * 
	 * Function to add an edge to the node.
	 * 
	 * @param edge
	 */
	public void addEdge(Edge edge){
		if(numEdges + 1 > edges.length){
			expandEdgeArray();
		}
		
		this.edges[numEdges++] = edge;
	}
	
	public void visit(){
		visited = true;
	}
	
	public boolean visited(){
		return visited;
	}

	/**
	 * 
	 * This is used if we don't have enough room in our edge array to 
	 * store another edge. This has a known linear run time, not very
	 * efficient TODO...
	 * 
	 */
	private void expandEdgeArray(){
		int size = edges.length;
		Edge newEdgeArray[] = new Edge[size*2];
		
		
		for(int i = 0; i<size; i++){
			newEdgeArray[i] = edges[i];
		}
		
		edges = newEdgeArray;
	}
	
	public Edge[] getEdges(){
		return edges;
	}
	
	public Node[] getAdjacentNodes(){
		Node[] retVal = new Node[numEdges];
		
		for(int i = 0; i < numEdges; i++){
			retVal[i] = edges[i].getTo();
		}
		
		return retVal;
		
	}
	
	/**
	 * 
	 * Returns the name of the node.
	 * 
	 * @return Node Name
	 */
	public String getName(){
		return name;
	}
}
