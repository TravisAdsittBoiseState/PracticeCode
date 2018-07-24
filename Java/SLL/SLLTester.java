

/**
 * 
 * Driver class to test the Single Linked List Class.
 * 
 * @author Travis Adsitt
 * 
 * 24JUL18
 *
 */
public class SLLTester {

	private static SLL<Character> myList;
	
	public static void main(String Args[]){
		
		myList = testAddFront_EtoA();
		System.out.println("Add to front of an empty list " + checkTest(myList.toString(),"[A]"));
		myList = testAddRear_EtoA();
		System.out.println("Add to rear of an empty list " + checkTest(myList.toString(),"[A]"));
		
		myList = testAddFront_AtoBA();
		System.out.println("Add to front of list [A] " + checkTest(myList.toString(),"[B,A]"));
		myList = testAddRear_AtoAB();
		System.out.println("Add to rear of list [A] " + checkTest(myList.toString(),"[A,B]"));
		
		myList = testAddFront_ABtoCAB();
		System.out.println("Add to front of list [A,B] " + checkTest(myList.toString(),"[C,A,B]"));
		myList = testAddRear_ABtoABC();
		System.out.println("Add to rear of list [A,B] " + checkTest(myList.toString(),"[A,B,C]"));
		
		myList = testRemoveLast_EtoE();
		System.out.println("Remove last element of an empty list " + checkTest(myList.toString(),"[]"));
		myList = testRemoveFirst_EtoE();
		System.out.println("Remove first element of an empty list " + checkTest(myList.toString(),"[]"));
		
		myList = testRemoveLast_AtoE();
		System.out.println("Remove last element of list [A] " + checkTest(myList.toString(),"[]"));
		myList = testRemoveFirst_AtoE();
		System.out.println("Remove first element of list [A] " + checkTest(myList.toString(),"[]"));
		
		myList = testRemoveLast_ABtoA();
		System.out.println("Remove last element of list [A,B] " + checkTest(myList.toString(),"[A]"));
		myList = testRemoveFirst_ABtoB();
		System.out.println("Remove first element of list [A,B] " + checkTest(myList.toString(),"[B]"));
		
		myList = testRemoveLast_ABCtoAB();
		System.out.println("Remove last element of list [A,B,C] " + checkTest(myList.toString(),"[A,B]"));
		myList = testRemoveFirst_ABCtoBC();
		System.out.println("Remove first element of list [A,B,C] " + checkTest(myList.toString(),"[B,C]"));
	}
	
	private static String checkTest(String test, String exp){
		return test.equals(exp)?"Passed":"Failed\n\tExpected : " + exp + " but got : " + test;
	}
	
	//Empty -> [A]
	private static SLL<Character> testAddFront_EtoA(){
		SLL<Character> retVal = new SLL<Character>();
		
		retVal.addToFront('A');
		
		return retVal;
	}
	
	//Empty -> [A]
	private static SLL<Character> testAddRear_EtoA(){
		SLL<Character> retVal = new SLL<Character>();

		retVal.addToRear('A');

		return retVal;
	}
	//[A] -> [B,A]
	private static SLL<Character> testAddFront_AtoBA(){
		SLL<Character> retVal = testAddFront_EtoA();

		retVal.addToFront('B');

		return retVal;
	}

	//[A] -> [A,B]
	private static SLL<Character> testAddRear_AtoAB(){
		SLL<Character> retVal = testAddFront_EtoA();

		retVal.addToRear('B');

		return retVal;
	}
	//[A,B] -> [C,A,B]
	private static SLL<Character> testAddFront_ABtoCAB(){
		SLL<Character> retVal = testAddRear_AtoAB();

		retVal.addToFront('C');

		return retVal;
	}

	//[A,B] -> [A,B,C]
	private static SLL<Character> testAddRear_ABtoABC(){
		SLL<Character> retVal = testAddRear_AtoAB();

		retVal.addToRear('C');

		return retVal;
	}
	
	//[] -> []
	private static SLL<Character> testRemoveLast_EtoE(){
		SLL<Character> retVal = new SLL<Character>();
		
		retVal.removeLast();
		
		return retVal;
	}
	
	//[] -> []
	private static SLL<Character> testRemoveFirst_EtoE(){
		SLL<Character> retVal = new SLL<Character>();

		retVal.removeFirst();

		return retVal;
	}

	//[A] -> []
	private static SLL<Character> testRemoveLast_AtoE(){
		SLL<Character> retVal = testAddRear_EtoA();

		retVal.removeLast();

		return retVal;
	}

	//[A] -> []
	private static SLL<Character> testRemoveFirst_AtoE(){
		SLL<Character> retVal = testAddRear_EtoA();

		retVal.removeFirst();

		return retVal;
	}

	//[A,B] -> [A]
	private static SLL<Character> testRemoveLast_ABtoA(){
		SLL<Character> retVal = testAddRear_AtoAB();

		retVal.removeLast();

		return retVal;
	}

	//[A,B] -> [B]
	private static SLL<Character> testRemoveFirst_ABtoB(){
		SLL<Character> retVal = testAddRear_AtoAB();

		retVal.removeFirst();

		return retVal;
	}
	
	//[A,B,C] -> [A,B]
	private static SLL<Character> testRemoveLast_ABCtoAB(){
		SLL<Character> retVal = testAddRear_ABtoABC();

		retVal.removeLast();

		return retVal;
	}

	//[A,B,C] -> [B,C]
	private static SLL<Character> testRemoveFirst_ABCtoBC(){
		SLL<Character> retVal = testAddRear_ABtoABC();

		retVal.removeFirst();

		return retVal;
	}
}
