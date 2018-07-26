package Search;

import java.io.IOException;

import Graphs.DirectedGraph;

/**
 * 
 * This is an example driver that performs a depth first and breadth first
 * search then prints out the resulting discovery order.
 * 
 * @author Travis Adsitt
 * 
 * 26JUL18
 *
 */
public class SearchDriver {

	public static void main(String arggs[]){
		
		DirectedGraph dg = new DirectedGraph();
		DepthFirst df = new DepthFirst();
		BreadthFirst bf = new BreadthFirst();
		
		
		try {
			dg.readFromAdjacencyMatrixFile("AdjacencyMatrix.txt");
		} catch (IOException e) {
			System.out.println("File not found!");
		}
		
		df.DFSearch(dg.getFirstNode());
		System.out.println("Result of a depth first search:\n"+df.discoveryOrder);
		
		dg.resetVisited();
		
		bf.BFSearch(dg.getFirstNode());
		System.out.println("\nResult of a breadth first search:\n"+bf.discoveryOrder);
		
		
		
	}
}
