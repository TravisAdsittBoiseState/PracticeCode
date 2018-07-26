package Graphs;

import java.io.IOException;

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
