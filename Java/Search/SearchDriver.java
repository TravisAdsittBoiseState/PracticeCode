package Search;

import java.io.IOException;

import Graphs.DirectedGraph;

public class SearchDriver {

	public static void main(String arggs[]){
		
		DirectedGraph dg = new DirectedGraph();
		
		try {
			dg.readFromAdjacencyMatrixFile("AdjacencyMatrix.txt");
		} catch (IOException e) {
			System.out.println("File not found!");
		}
		

		DepthFirst df = new DepthFirst();
		
		df.DFSearch(dg.getFirstNode());
		
		System.out.println(df.discoveryOrder);
		
	}
}
