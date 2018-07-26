package Graphs;


/**
 * A class to hold the to and from nodes along with the weight of 
 * the edge connecting them.
 * 
 * @author Travis Adsitt
 * 
 * 26JUL18
 *
 */


public class Edge {

	private Node from,to;
	private int weight;
	
	public Edge(Node from, Node to, int weight){
		this.from = from;
		this.to = to;
		this.weight = weight;
	}
	
	public int getWeight(){
		return weight;
	}
	
	public Node getTo(){
		return to;
	}
	
	public Node getFrom(){
		return from;
	}
}
