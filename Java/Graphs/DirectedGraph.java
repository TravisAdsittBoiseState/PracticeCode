package Graphs;

import java.io.*;

/**
 * 
 * This is a Directed Graph class, there are no claims to efficiency here. It 
 * is capable of reading from an Adjacency Matrix textfile that is laid out in
 * a grid fashion with the delimiter ';' for example:
 * 
 *  ;A;B;C
 * A;-1;5;10
 * B;20;-1;2
 * C;10;5;-1
 * 
 * Will produce (if in debug mode):
 * 
 * Number of Nodes Found : 3
 *
 * Creating Nodes...
 * New Node Created! Node Name : A
 * New Node Created! Node Name : B
 * New Node Created! Node Name : C
 * 
 * Creating Edges...
 * New Edge Created! From Node : A To Node : B With Weight : 5
 * New Edge Created! From Node : A To Node : C With Weight : 10
 * New Edge Created! From Node : B To Node : A With Weight : 20
 * New Edge Created! From Node : B To Node : C With Weight : 2
 * New Edge Created! From Node : C To Node : A With Weight : 10
 * New Edge Created! From Node : C To Node : B With Weight : 5
 * 
 * This directed graph was created for the specific use of implementing 
 * Dijkstra's Algorithm, and the basic depth and breadth first searches. 
 * Though Dijksta'sAlgorithm is well known for its linear average run time, 
 * a little research shows that it is not useful for things such as 
 * "best route" for P2P road map searches on continent sized road maps. 
 * 
 * @author Travis Adsitt
 * 
 * 26JUL18
 *
 */

public class DirectedGraph {

	private boolean DEBUG = false;
	private Node nodes[];
	
	/**
	 * Resets the visited flag for all the nodes.
	 */
	public void resetVisited(){
		for(Node n: nodes){
			n.clearVisit();
		}
	}
	
	/**
	 * A way to access a node used primarily for beginning a search.
	 * 
	 * TODO make this more robust and allow selection of node.
	 * 
	 * 
	 * @return Node 0
	 */
	public Node getFirstNode(){
		return nodes[0];
	}
	
	/**
	 * 
	 * This will read from an Adjacency Matrix text file and load it into
	 * the graph form.
	 * 
	 * @param filename
	 * @throws IOException
	 */
	public void readFromAdjacencyMatrixFile(String filename) throws IOException{
		
		File file = new File(filename);
		BufferedReader br = new BufferedReader(new FileReader(file));
		
		//First line is going to contain all node names delimited by a ;
		String firstLine = br.readLine();
		
		String nodeNames[] = firstLine.split(";");
		
		//This will give us all of the node names, however there is one blank 
		//spot so we need to subtract one. Now the question is how do we extract
		//the edges from the file whilst not having created the nodes?
		
		//We could create the nodes without edges and add a helper method to the
		//node class to set the edges after the node creation, we are going to 
		//go with that for now.
		
		nodes = new Node[nodeNames.length - 1];
		debug("Number of Nodes Found : " + nodes.length);
		debug("\nCreating Nodes...");
		
		for(int i = 1; i < nodeNames.length; i++){
			nodes[i - 1] = new Node(nodeNames[i]);
			debug("New Node Created! Node Name : " + nodes[i - 1].getName());
		}
		
		debug("\nCreating Edges...");
		
		for(int i = 0; i<nodes.length; i++){
			String nextLine = br.readLine();
			
			if(nextLine == null){
				debug("Adjacency Matrix missing node information... Quitting!");
				break;
			}
			
			String to[] = nextLine.split(";");
			
			if(!to[0].equals(nodes[i].getName())){
				debug("Adjacency Matrix nodes out of order... Quitting!");
				break;
			}
			
			Node currFrom = nodes[i];
			
			for(int x = 1; x<to.length; x++){
				
				Node currTo = nodes[x - 1];
				int weight = Integer.valueOf(to[x]);
				
				if(weight>=0){
					Edge newEdge = new Edge(currFrom,currTo,weight);
					
					currFrom.addEdge(newEdge);
					
					debug("New Edge Created! From Node : " + currFrom.getName() + " To Node : " + currTo.getName() + " With Weight : " + weight);
				}
				
			}
		}
		
		br.close();
		
	}
	
	/**
	 * 
	 * Helper function to print a message to console if DEBUG is enabled.
	 * 
	 * @param message
	 */
	private void debug(String message){
		if(DEBUG){
			System.out.println(message);
		}
	}
	
}
