package Graphs;

import java.io.IOException;

/**
 * 
 * This is simply a class to load a Directed Graph from an adjacency matrix
 * text file. If the debug flag is set in the Directed Graph class then it
 * will print out the nodes and edges added too the graph.
 * 
 * @author Travis Adsitt
 * 
 * 26JUL18
 *
 */

public class DGDriver {

	public static void main(String args[]){
		try {
			
			DirectedGraph dg = new DirectedGraph();
			
			dg.readFromAdjacencyMatrixFile("AdjacencyMatrix.txt");
		
		} catch (IOException e) {
			System.out.println("IO Exception, best guess is I couldn't find your file...");
		}
	}
}
